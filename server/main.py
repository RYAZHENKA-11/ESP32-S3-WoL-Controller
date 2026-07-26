import paho.mqtt.client as mqtt
from datetime import datetime

# Fill in your MQTT broker credentials
BROKER = "localhost"
PORT = 1883
USER = ""
PASSWORD = ""

TOPIC_COMMAND = "esp32/command"
TOPIC_STATUS = "esp32/status"


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected!")
        client.subscribe(TOPIC_STATUS)
    else:
        print(f"Connection failed with code {rc}!")


def on_message(client, userdata, msg):
    print(f"\r[{datetime.now()}] {msg.payload.decode()}{' ' * 20}")


client = mqtt.Client()
client.username_pw_set(USER, PASSWORD)
client.on_connect = on_connect
client.on_message = on_message
client.connect(BROKER, PORT, 60)
client.loop_start()

print(f"Listening to '{TOPIC_STATUS}'. Type messages to publish (or 'Q' to exit):")

try:
    while True:
        cmd = input().strip().upper()
        if cmd == "Q":
            break
        elif cmd:
            client.publish(TOPIC_COMMAND, cmd)
except KeyboardInterrupt:
    pass
finally:
    client.loop_stop()
    client.disconnect()
