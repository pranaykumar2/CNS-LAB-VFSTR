def permute_8bits(input_bits, permutation):
    return [input_bits[p - 1] for p in permutation]

def generate_keys(key):
    key_p10 = [3, 5, 2, 7, 4, 10, 1, 9, 8, 6]
    key_p8 = [6, 3, 7, 4, 8, 5, 10, 9]

    # Apply P10 permutation
    key_10 = permute_8bits(key, key_p10)

    # Split into two 5-bit halves
    left_half = key_10[:5]
    right_half = key_10[5:]

    # Perform circular left shifts
    left_half = left_half[1:] + [left_half[0]]
    right_half = right_half[1:] + [right_half[0]]

    # Combine and apply P8 permutation to generate key K1
    key_1 = permute_8bits(left_half + right_half, key_p8)

    # Perform double left shifts on the split halves
    left_half = left_half[2:] + left_half[:2]
    right_half = right_half[2:] + right_half[:2]

    # Combine and apply P8 permutation to generate key K2
    key_2 = permute_8bits(left_half + right_half, key_p8)

    return key_1, key_2

def initial_permutation(input_bits):
    ip = [2, 6, 3, 1, 4, 8, 5, 7]
    return permute_8bits(input_bits, ip)

def inverse_initial_permutation(input_bits):
    ip_inv = [4, 1, 3, 5, 7, 2, 8, 6]
    return permute_8bits(input_bits, ip_inv)

def expansion(input_bits):
    exp = [4, 1, 2, 3, 2, 3, 4, 1]
    return permute_8bits(input_bits, exp)

def substitution(input_bits, s_box):
    row = int(''.join(map(str, [input_bits[0], input_bits[3]])), 2)
    col = int(''.join(map(str, input_bits[1:3])), 2)
    value = s_box[row][col]
    return list(map(int, bin(value)[2:].zfill(2)))

def f_function(input_bits, subkey):
    # Expansion
    expanded_bits = expansion(input_bits)

    # XOR with subkey
    xor_result = [a ^ b for a, b in zip(expanded_bits, subkey)]

    # S-Box substitution
    s_box_output = substitution(xor_result[:4], S0) + substitution(xor_result[4:], S1)

    # P4 permutation
    p4 = [2, 4, 3, 1]
    return permute_8bits(s_box_output, p4)

def fk(input_bits, subkey):
    left_half = input_bits[:4]
    right_half = input_bits[4:]

    # F-function
    f_output = f_function(right_half, subkey)

    # XOR with left half
    new_right_half = [a ^ b for a, b in zip(left_half, f_output)]

    return right_half + new_right_half

def switch(input_bits):
    return input_bits[4:] + input_bits[:4]

def sdes_encrypt(plaintext, key):
    key_1, key_2 = generate_keys(key)

    # Initial permutation
    initial_perm = initial_permutation(plaintext)

    # Round 1
    round_1 = fk(initial_perm, key_1)

    # Switch
    switch_output = switch(round_1)

    # Round 2
    round_2 = fk(switch_output, key_2)

    # Inverse initial permutation
    encrypted_bits = inverse_initial_permutation(round_2)

    return encrypted_bits

def sdes_decrypt(ciphertext, key):
    key_1, key_2 = generate_keys(key)

    # Initial permutation
    initial_perm = initial_permutation(ciphertext)

    # Round 1
    round_1 = fk(initial_perm, key_2)

    # Switch
    switch_output = switch(round_1)

    # Round 2
    round_2 = fk(switch_output, key_1)

    # Inverse initial permutation
    decrypted_bits = inverse_initial_permutation(round_2)

    return decrypted_bits

# Example usage:
plaintext = [1, 0, 1, 0, 0, 0, 1, 0]
key = [1, 0, 0, 0, 0, 1, 0, 0, 1, 0]

# Define S-Boxes
S0 = [
    [1, 0, 3, 2],
    [3, 2, 1, 0],
    [0, 2, 1, 3],
    [3, 1, 3, 2]
]

S1 = [
    [0, 1, 2, 3],
    [2, 0, 1, 3],
    [3, 0, 1, 0],
    [2, 1, 0, 3]
]

# Encryption
encrypted_bits = sdes_encrypt(plaintext, key)
print("Encrypted Bits:", encrypted_bits)

# Decryption
decrypted_bits = sdes_decrypt(encrypted_bits, key)
print("Decrypted Bits:", decrypted_bits)
