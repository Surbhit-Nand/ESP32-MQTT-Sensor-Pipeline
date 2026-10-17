# ESP32 MQTT Sensor Pipeline

A simulated ESP32 reads a DHT22 temperature and humidity sensor and publishes the readings as JSON over MQTT every 2 seconds.

This project runs in the [Wokwi](https://wokwi.com/projects/478114041706298369) simulator. It has not been run on physical hardware.

## How it works

1. The ESP32 connects to Wi-Fi (Wokwi's simulated `Wokwi-GUEST` network).
2. It connects to the public HiveMQ broker (`broker.hivemq.com`).
3. Every 2 seconds it reads the DHT22 and publishes a message like this to the topic `usp-surbhit-iot/dht22`:

```json
{"temp":24.00,"hum":40.00}
```

## Wiring (in the simulator)

| DHT22 | ESP32 |
|-------|-------|
| VCC   | 3V3   |
| GND   | GND   |
| SDA   | GPIO 15 |

## Run it

1. Open the [Wokwi project](https://wokwi.com/projects/478114041706298369) and press Play.
2. Install the library and run the subscriber on your computer: `pip install paho-mqtt`, then `python subscriber.py`. It prints each reading and appends it to `readings.csv`.
3. Or watch the messages in the [HiveMQ web client](https://www.hivemq.com/demos/websocket-client/): click Connect and subscribe to `usp-surbhit-iot/dht22`.
4. Click the DHT22 in Wokwi and drag the temperature slider. The new values appear in the terminal and in HiveMQ.

<img width="1712" height="975" alt="Screenshot 2026-10-17 232953" src="https://github.com/user-attachments/assets/f2524228-afeb-470b-9b93-b29f19fdfadd" />
<img width="1912" height="1042" alt="Screenshot 2026-10-17 232942" src="https://github.com/user-attachments/assets/82ec3e62-d24f-40b6-92ee-96f62e033062" />
<img width="955" height="960" alt="Screenshot 2026-10-17 210016" src="https://github.com/user-attachments/assets/61645d36-6e68-402d-845b-785c273ebb7c" />



## Files

- `sketch.ino`: ESP32 code (C++/Arduino) using the `DHT sensor library` and `PubSubClient`
- `subscriber.py`: Python script that subscribes to the topic, prints readings and logs them to `readings.csv`
- `diagram.json`: Wokwi circuit layout
- `libraries.txt`: Wokwi library list

## Notes

The HiveMQ broker is public, so anyone who knows the topic can read the messages. No private data is sent.
