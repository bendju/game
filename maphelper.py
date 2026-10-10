"""

data = [
    [
      0,
      0,
      0,
      0,
      301,
      107,
      107,
      107,
      107,
      304,
      0,
      0,
      0,
      0,
      0
    ],
    [
      0,
      0,
      301,
      107,
      111,
      122,
      171,
      170,
      123,
      110,
      304,
      0,
      0,
      0,
      0
    ],
    [
      0,
      301,
      111,
      121,
      121,
      5,
      5,
      5,
      5,
      121,
      110,
      304,
      0,
      0,
      0
    ],
    [
      0,
      108,
      121,
      5,
      5,
      5,
      5,
      4,
      5,
      5,
      121,
      110,
      304,
      0,
      0
    ],
    [
      0,
      111,
      5,
      5,
      3,
      5,
      5,
      5,
      5,
      5,
      5,
      121,
      102,
      0,
      0
    ],
    [
      0,
      121,
      5,
      5,
      5,
      5,
      5,
      5,
      5,
      5,
      0,
      5,
      0,
      0,
      0
    ],
    [
      0,
      0,
      0,
      8,
      5,
      0,
      5,
      5,
      0,
      5,
      0,
      0,
      0,
      0,
      0
    ],
    [
      0,
      0,
      0,
      0,
      5,
      0,
      0,
      5,
      0,
      0,
      0,
      0,
      0,
      0,
      0
    ],
    [
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0
    ],
    [
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0
    ]
  ]



with open('mapdata.txt', 'w') as w:
    w.write('{\n')
    for row in data:
        w.write('{')
        for j, val in enumerate(row):
            w.write(str(val))
            if j != len(row) - 1:
                w.write(',')
        w.write('},\n')
    w.write('}')




"""
from PIL import Image
import math

WIDTH = 1920
HEIGHT = 1080

RADIUS = 440

img = Image.new("RGBA", (WIDTH, HEIGHT))
pixels = img.load()

center_x = WIDTH / 2
center_y = HEIGHT / 2

for y in range(HEIGHT):
    for x in range(WIDTH):
        dx = x - center_x
        dy = y - center_y

        dist = math.sqrt(dx * dx + dy * dy)

        t = min(dist / RADIUS, 1.0)

        # Szebb átmenet
        alpha = int(255 * (t * t))

        pixels[x, y] = (0, 0, 0, alpha)

img.save("narrow_light.png")

print("narrow_light.png elkészült")