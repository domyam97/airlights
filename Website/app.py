from flask import Flask, render_template, request, Response, redirect
import logging
from send_color import *
from colors import colors 

app = Flask(__name__)


global background        
background = '#202020' 
    
@app.route('/')
def website():
	global background
	return render_template('index.html', currentBackground=background)

@app.route("/colors", methods=['POST'])
def color_in():
	global background
	print('Got: ' + str(request.form))
	if 'submit_string' in request.form:
		color = request.form.get("color")
		print("String color: " + str(color))
		result = pass_color(color, 0, 0)
		current = color   
		print('#'+str(hex(colors[color]))[2:]) 
		background = str('#'+str(hex(colors[color]))[2:])

	elif 'submit_hex' in request.form:
		redStr = request.form.get('red')
		greenStr = request.form.get('green')
		blueStr = request.form.get('blue')

		if(redStr == ''):
			redStr = 1
		if(greenStr == ''):
			greenStr = 1
		if(blueStr == ''):
			blueStr = 1

		try:
			red = int(redStr)
			green = int(greenStr)
			blue = int(blueStr)
		except:
			red = 0
			green = 0
			blue = 0
		
		if(red > 255):
			red = 255
		if(blue > 255):
			blue = 255
		if(green > 255):
			green = 255

		try:
			redHex ="{:02x}".format(red)
		except:
			redHex = '00'
		try:
			greenHex = "{:02x}".format(green)
		except:
			greenHex = '00'
		try:
			blueHex = "{:02x}".format(blue) 
		except:
			blueHex = '00'

		packet = ("#"+str(redHex)+str(greenHex)+str(blueHex)) 
		print("Hex color: " + str(packet))
		result = pass_color(packet, 0, 0)
		current = packet
		background = packet		

	elif 'loop' in request.form:
		print('Loop')
		result = pass_color('#000000', 0, 0)
		current = 'loop'
		background = 'loop'

	return redirect('/')
        
if __name__ == "__main__":
	app.run(debug=True, host='192.168.50.24')


        
	
