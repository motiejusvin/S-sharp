import random
import os
lines = 10000

types = ["sveikasis", "nesveikasis", "dvejetaine", "siulas", "raide"]

f = open("./tests/test.sa", "w+")

for x in range(0, lines):
    type = types[random.randint(0, 4)]
    data = type + " "
    for w in range(0, 10):
        data += chr(random.randint(97, 122))
    data += " = "
    if(type == "siulas"):
        data += '"'
        for w in range(0, 4):
            data += chr(random.randint(97, 122))
        data += '"'
    elif(type == "nesveikasis" or type == "sveikasis"):
        for w in range(0, 4):
            data += str(random.randint(0, 4))
    elif(type == "raide"):
        data += "'"
        data += chr(random.randint(97, 122))
        data += "'"
    else:
        for w in range(0, 4):
            data += chr(random.randint(97, 122))
    data += "\n"
    f.write(data)
f.close()
if (os.system("./main ./tests/test.sa") != 0):
    print("ERROR")
exit(0)
