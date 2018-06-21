import colors
import smbus

forbidden = [2, 55, 95]

def send_to_AVR(color_array):    
    device_bus = 1
    addr = 0x69
    bus = smbus.SMBus(device_bus)
    bus.write_block_data(addr, 0x00, color_array)
    pass	

def pass_color(color_in):
	color = color_in;
	## determine whether color is hex or string // default type is color
	if color[:1] == '#' :
		# Decode the hex to integers
		red = int(color[1:3], 16)
		green = int(color[3:5], 16)
		blue = int(color[5:7], 16)

		if(red in forbidden):
			red = red+1
		if(blue in forbidden):
			blue = blue+1
		if(green in forbidden):
			green = green+1
	
		# Form packet to send single color
		packet = [55, 0, 0, 2, red, green, blue, 95]

		# Send packet to AVR
		send_to_AVR(packet)

	else:
		color = color.lower()
		if color in colors.colors:
			hex_col = colors.colors[color]
			hexColString = str('0x{:06X}'.format(hex_col))[1:]

                        # Decode the hex to integers
                        red = int(hexColString[1:3], 16)
                        green = int(hexColString[3:5], 16)
                        blue = int(hexColString[5:7], 16)


                        # Form packet to send single color
                        packet = [55, 0, 0, 2, red, green, blue, 95]

                        # Send packet to AVR
                        send_to_AVR(packet)

