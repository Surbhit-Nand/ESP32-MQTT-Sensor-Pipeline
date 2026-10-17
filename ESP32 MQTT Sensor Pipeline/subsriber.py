import json
import csv
from datetime import datetime
import paho.mqtt.client as mqtt

BROKER = "broker.hivemq.com"
TOPIC = "usp-surbhit-iot/dht22"

def on_connect(client, userdata, flags, reason_code, properties):
    print("Connected to broker, waiting for readings...")
    client.subscribe(TOPIC)

def on_message(client, userdata, msg):
    data = json.loads(msg.payload.decode())
    now = datetime.now().strftime("%H:%M:%S")
    print(f"{now}  Temperature: {data['temp']} C  Humidity: {data['hum']} %")
    with open("readings.csv", "a", newline="") as f:
        csv.writer(f).writerow([now, data["temp"], data["hum"]])

client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message
client.connect(BROKER, 1883)
client.loop_forever()