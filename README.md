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
2. Open the [HiveMQ web client](https://www.hivemq.com/demos/websocket-client/), click Connect, and subscribe to `usp-surbhit-iot/dht22`.
3. Click the DHT22 in Wokwi and drag the temperature slider. The new values appear in HiveMQ.

<img width="1715" height="977" alt="Screenshot 2026-10-17 210000" src="https://github.com/user-attachments/assets/5fac32a5-7843-42a2-8ac1-16ab454df16c" />
<img width="955" height="960" alt="Screenshot 2026-10-17 210016" src="https://github.com/user-attachments/assets/2e04ddf0-f413-4c1e-b0f3-bc9f9a5eedb1" />

## Files

- `sketch.ino`: ESP32 code (C++/Arduino) using the `DHT sensor library` and `PubSubClient`
- `diagram.json`: Wokwi circuit layout
- `libraries.txt`: Wokwi library list

## Notes

The HiveMQ broker is public, so anyone who knows the topic can read the messages. No private data is sent.
