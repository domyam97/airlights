from flask import Flask, render_template, request, Response
import logging
from send_color import *

app = Flask(__name__)
        
        
@app.route('/')
def website():
	background = '#FFFFFF'
	return render_template('index.html', currentBackground=background)

@app.route("/colors", methods=['POST'])
def color_in():
	print('Got: ' + str(request.form))
	if 'submit_string' in request.form:
		color = request.form.get("color")
		print("String color: " + str(color))
		result = pass_color(color, 0, 0)
		current = color    
		background = color

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

	return render_template('index.html', currentBackground=background, current=current)
        
        
if __name__ == "__main__":
	app.run(debug=True, host='192.168.50.24')


        
	
