from flask import Flask, render_template

app = Flask(__name__)


@app.route('/htmlstuff')
def htmlstuff():
	return render_template('htmlstuff.html')


@app.route('/')
def index():
	return "Hello world"

if __name__ == "__main__":
	app.run(debug=True, host='0.0.0.0')
