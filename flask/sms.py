from flask import Flask, request, Response
from twilio import twiml

app = Flask(__name__)

@app.route("/twilio", methods=["POST"])
def inbound():
	inbound_message = request.form.get("Body")
	print(inbound_message)
	return Response("Received", mimetype="application/xml"), 200



if __name__ == "__main__":
	app.run(debug=True)
