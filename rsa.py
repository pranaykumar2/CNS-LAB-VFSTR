from math import sqrt
import random
from random import randint as rand


def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)


def mod_inverse(a, m):
    for x in range(1, m):
        if (a * x) % m == 1:
            return x
    return -1

def generate_keypair(p, q):

    print(p, q)
    n = p * q
    phi = (p - 1) * (q - 1)

    e = random.randrange(1, phi)
    g = gcd(e, phi)

    while True:
        e = random.randrange(1, phi)
        g = gcd(e, phi)
        d = mod_inverse(e, phi)
        if g == 1 and e != d:
            break

    return ((e, n), (d, n))


def encrypt(msg_plaintext, package):
    e, n = package
    msg_ciphertext = [pow(ord(c), e, n) for c in msg_plaintext]
    return msg_ciphertext


def decrypt(msg_ciphertext, package):
    d, n = package
    msg_plaintext = [chr(pow(c, d, n)) for c in msg_ciphertext]
    return (''.join(msg_plaintext))

p = int(input('Enter p : '))
q = int(input('Enter q : '))
print("Running RSA...")
print("Generating public/private keypair...")
public, private = generate_keypair(p, q)
print("Public Key: ", public)
print("Private Key: ", private)
msg = input("Write msg: ")
#print([ord(c) for c in msg])
encrypted_msg = encrypt(msg, public)
print("Encrypted msg: ")
print(''.join(map(lambda x: str(x), encrypted_msg)))
print("Decrypted msg: ")
print(decrypt(encrypted_msg, private))
