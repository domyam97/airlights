from flask import Flask, render_template
from send_color import *

app = Flask(__name__)
        
        
@app.route('/')

def htmlstuff():
	return render_template('htmlstuff.html')



def website():
	return render_template('index.html')


@app.route("/colors", methods=['POST'])
def color_in():
        color = request.form.get("color")
        pass_color(color)
        print color
        return 200
        
        
if __name__ == "__main__":
	app.run(debug=True, host='0.0.0.0')


        
	
