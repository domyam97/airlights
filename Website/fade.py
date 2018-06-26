from send_color import *
import time

forbidden = [0, 2, 55, 95]

for i in range(0, 255):
	print(i)
	if i in forbidden:
		pass
	else:
		pass_color('#0000'+hex(i).split('x')[-1], 0, 0)
