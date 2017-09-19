from math import pi,sin,cos
import serial
import re
import Tkinter

def dtr(x):
  return (2*pi*x)/360

def convert_to_points(canvas, s, a, b, scale = 1, polar=True):
  i=0
  points = []
  while i<len(a):
    x = -1
    y = -1
    if polar:
      x = cos(a[i]) * b[i]
      y = sin(a[i]) * b[i]
    else:
      x=a[i]
      y=b[i]
    x*=scale
    y*=scale
    canvas.create_rectangle(s/2+x,s/2-y,s/2+x+1,s/2-y+1)
    i += 1

ser = serial.Serial('/dev/ttyUSB1', 115200)


if __name__ == "__main__":
  BUFFER_SIZE = 100
  s = 800
  m_scale = 0.25
  r = [0] * 360
  t = [dtr(e) for e in range(360)]
  window = Tkinter.Tk()
  canvas = Tkinter.Canvas(window,width=s,height=s)


  while True:

    raw = ""
    while ser.inWaiting() <= BUFFER_SIZE:
      pass

    data = ser.read(BUFFER_SIZE).split('\r\n')
    canvas.delete("all")
    for point in data:
      splt = point.split(',')
      try:
        theta = int(splt[0])
        radius = int(splt[1])

        t[theta] = dtr(theta)
        r[theta] = radius
      except (ValueError, IndexError):
        pass
        #data got cut off

    convert_to_points(canvas, s, t, r, scale = m_scale)

    canvas.pack()
    window.update()
