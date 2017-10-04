import os
from slackclient import SlackClient

SLACK_TOKEN = 'xoxp-93150447840-248175250817-248752504436-7658a8821b4560ead3dab961b084a038'
#SLACK_WEBHOOK_SECRET = '

slack_client = SlackClient(SLACK_TOKEN)

#print(slack_client.api_call("api.test"))
#print(slack_client.api_call("api.test")['ok'])

def list_channels():
    channels_call = slack_client.api_call("channels.list")
    if channels_call.get('ok'):
            return channels_call['channels']
    return None


def send_message(channel_id, message):
    slack_client.api_call(
        "chat.postMessage",
        channel=channel_id,
        text=message,
        username='Airlights Bot',
        icon_emoji=':robot_face:'
    )
        

channels = list_channels()
print(channels)
if channels:
    print("Channels: ")
    for c in channels:
        print(c['name'] + " (" + c['id'] + ")")
else:
    print "ERORR"
    
send_message('C2R4ED864', "Sorry 'Erik' is not a valid name")
