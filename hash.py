import hashlib

def hash_fn(msg, alg):
    obj = hashlib.new(alg)
    obj.update(msg.encode('utf-8'))
    value = obj.hexdigest()

    return value

msg = input("Enter the message : ")
alg = input("Enter the algorithm (lower case) : ")
print(f"Hash value : {hash_fn(msg, alg)}")
