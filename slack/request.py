import os
from slackclient import SlackClient
from flask import Flask, request, Response


app = Flask(__name__)

SLACK_WEBHOOK_SECRET = 'k5YMCRQC83zzqJpoVs88osHo'
SLACK_TOKEN = 'xoxp-93150447840-248175250817-248752504436-7658a8821b4560ead3dab961b084a038'


slack_client = SlackClient(SLACK_TOKEN)

print(SLACK_WEBHOOK_SECRET)


def send_message(channel_id, message):
    slack_client.api_call(
        "chat.postMessage",
        channel=channel_id,
        text=message,
        username='Airlights Bot',
        icon_emoji=':robot_face:'
    )
    

@app.route('/slack', methods=['POST'])
def inbound():
    if request.form.get('token') == SLACK_WEBHOOK_SECRET:
        channel = request.form.get('channel_name')
        username = request.form.get('user_name')
        text = request.form.get('text')
        inbound_message = username + " in " + channel + " says: " + text
        print(inbound_message)
        send_message(request.form.get('channel_id'), 'Received: ' + str(text))
    return Response(), 200


@app.route('/', methods=['GET'])
def test():
    return Response('It works!')


if __name__ == "__main__":
    app.run(debug=True)
