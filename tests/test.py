import random
import os
import time
lines = 1000000

types = ["sveikasis","nesveikasis","dvejetaine","siulas","raide"]

f = open("./tests/test.sa","w+")

for x in range(0,lines):
    type = types[random.randint(0,3)]
    data = type + " "
    for w in range(0,10):
        data += chr(random.randint(97,122))
    data += " = "
    if(type == "siulas"):
        data += '"'
        for w in range(0,4):
            data += chr(random.randint(97,122))
        data += '"'
    elif(type == "nesveikasis" or type == "sveikasis"):
        for w in range(0,4):
            data += str(random.randint(0, 4))
    else:
        for w in range(0, 4):
            data += chr(random.randint(97, 122))
    data += "\n"
    f.write(data)

if(os.system("./main ./tests/test.sa") != 0):
    print("ERROR")
    exit(-1)
f.close()
exit(1)
