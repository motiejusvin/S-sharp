import random
import os
import time
lines = 200
runs = 100000

types = ["sveikasis","nesveikasis","dvejetaine","siulas","raide"]
f = open("test.sa","w+")
for x in range(0,runs):
    for y in range(0,lines):
        type = types[random.randint(0,3)]
        data = type + " "
        for w in range(0,10):
            data += chr(random.randint(92,120))
        data += " = "
        for w in range(0,4):
            data += chr(random.randint(72,120))
        data += "\n"
        f.write(data)

    #time.sleep(0.01)
    if(os.system("../src/compiler/main ./test.sa") != 0):
        print("ERROR IN " + str(x))
        exit(1)
    print("\nTEST "+ str(x))
    f.truncate(0)