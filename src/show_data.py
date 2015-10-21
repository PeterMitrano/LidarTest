import matplotlib.pyplot as plt
import serial

f = open('dump.csv', 'r')

lines = f.readlines()

# remove picocom output,
# strip windows line endings,
# split by comma,
# remove failures,
# and turn into numbers
lines = lines[2:-25]
lines = [e[:-2] for e in lines]
lines = [e.split(',')  for e in lines]
lines = [e for e in lines if e[1]!='failure']
t = [e[0] for e in lines]
r = [e[1] for e in lines]

plt.subplot(111, polar=True)
plt.scatter(t,r)
