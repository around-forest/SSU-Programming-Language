import time
import math

n = 0

while True:
    try:
        n = int(input(">> Input the number of numbers to process: "))
    except ValueError:
        print("*Warnning* number of numbers should be between 2 to 30")
    if n not in range(2, 30):
        print("*Warnning* number of numbers should be between 2 to 30")
    else:
        break


array = list(map(int, input(">> Input the numbers to be processed : ").split()))

start = time.time()

array.sort()

for i in range(0, n-1):
    count = 0

    if array[i] == array[i+1]:
        continue

    for j in range(array[i] , array[i+1]):
        temp = 0
        for k in range(2, j-1):
            if (j%k) == 0:
                temp += 1
        if temp==0:
            count += 1
    print("Number of prime number between", array[i], ", ", array[i+1], ": ", count)

end = time.time()
print(f"Total execution time using python is {end - start:.5f} seconds")



