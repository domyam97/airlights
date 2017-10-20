from flask import Flask, render_template
from send_color import *

app = Flask(__name__)


@app.route('/')
def website():
	return render_template('index.html')

if __name__ == "__main__":
	app.run(debug=True, host='0.0.0.0')

@app.route("/colors", methods=['POST'])
def color_in():
	
