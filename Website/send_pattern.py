import colors
import smbus


def send_to_AVR(color_array):    
    device_bus = 1
    addr = 0x69
    bus = smbus.SMBus(device_bus)
    bus.write_block_data(addr, 0x00, color_array)
    pass


forbidden = [2, 55, 95]

def pass_pattern(pattern_in, step, speed):
	# pattern_in is of form [[R, G, B], [R, G, B] ...]

	# Check if the speed or step is forbidden
	forbidden = [0, 2, 55, 95]
	if(step in forbidden):
		step = step + 1
	if(speed in forbidden):
		speed = speed + 1

	# Create the beginning of the packet
	packet = [55, step, speed]

	# Fill the packet with the colors
	for item in pattern_in:
		packet.append(2)
		for color in item:
			if(color in forbidden):
				color = color + 1
			packet.append(color)


	# Add the end key
	packet.append(95)
	print(packet)

	# Send packet
	send_to_AVR(packet)
