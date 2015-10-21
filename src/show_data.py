import matplotlib.pyplot as plt
from math import pi
import serial

ser = serial('/dev/ttyUSB0', 115200)

f = open('dump.csv', 'r')

lines = f.readlines()

# remove picocom output,
# strip windows line endings,
# split by comma,
# remove failures,
# and turn into numbers
# sort
# split into to lists
lines = lines[2:-25]
lines = [e[:-2] for e in lines]
lines = [e.split(',')  for e in lines]
lines = [e for e in lines if e[1]!='failure']
lines = [[int(e[0]), int(e[1])] for e in lines]
lines.sort()
t = [e[0] for e in lines]
r = [e[1] for e in lines]

# reduce it to one value for each theta
data = []
i = 0
while i < len(r):
    rsum = 0
    j = i
    while (j < len(t) and t[j] == t[i]):
        rsum += r[j]
        j += 1
    avg = rsum/(j-i)
    data.append([t[i],avg])
    i = j

# also convert to radians
t = [(2*pi*e[0])/360 for e in data]
r = [e[1] for e in data]

plt.subplot(111, polar=True)
plt.plot(t,r)
plt.show()

o = open('pretty.csv', 'w')
for i in range(len(r)):
    o.write(str(t[i]))
    o.write(",")
    o.write(str(r[i]))
    o.write("\n")


