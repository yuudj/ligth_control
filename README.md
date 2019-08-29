# Light Control

Control multiple light relays with an ESP32 using touch inputs or MQTT.

## Context

Every time a turn on the lights in my living room 8 light bulbs turn on. The electrical pipes in my apartment are to small to put a switch and a cable for each light. In a previous iteration of this project I tried to use i2c to control each light but is easier, cheaper and faster to control the relays directly via multi-par cable.

## Features

- [x] 8 relay outputs
- [x] 9 touch inputs (8 for the relays and the 9th to activate de display and show some data)
- [x] dht22 sensor
- [ ] i2c OLED display.
- [x] MQTT connection
- [ ] 3d printed case
- [ ] use recycled aluminum soda cans to make the touch buttons

## Connection

| GPIO | INPUT      | OUTPUT | NOTES                                 | CONFIG  |
| ---- | ---------- | ------ | ------------------------------------- | ------- |
| 0    | PULLED OUT | OK     | Outputs PWM signal at boot            | TOUCH 1 |
| 1    | TX pin     | OK     | Debug output at boot                  |         |
| 2    | OK         | OK     | Connected to on-board LED             | TOUCH 2 |
| 3    | OK         | RX PIN | HIGH at boot                          |         |
| 4    | OK         | OK     |                                       | TOUCH 0 |
| 5    | OK         | OK     | outputs PWM signal at boot            | RELAY 1 |
| 6    | X          | X      | Connected to the integrated SPI flash |         |
| 7    | X          | X      | Connected to the integrated SPI flash |         |
| 8    | X          | X      | Connected to the integrated SPI flash |         |
| 9    | X          | X      | Connected to the integrated SPI flash |         |
| 10   | X          | X      | Connected to the integrated SPI flash |         |
| 11   | X          | X      | Connected to the integrated SPI flash |         |
| 12   | OK         | OK     | Boot fail if pulled high              | TOUCH 5 |
| 13   | OK         | OK     |                                       | TOUCH 4 |
| 14   | OK         | OK     | Outputs PWM signal at boot            | TOUCH 6 |
| 15   | OK         | OK     | Outputs PWM signal at boot            | TOUCH 3 |
| 16   | OK         | OK     |                                       | RELAY 2 |
| 17   | OK         | OK     |                                       | RELAY 3 |
| 18   | OK         | OK     |                                       | RELAY 4 |
| 19   | OK         | OK     |                                       | RELAY 5 |
| 21   | OK         | OK     |                                       | I2C     |
| 22   | OK         | OK     |                                       | I2C     |
| 23   | OK         | OK     |                                       | RELAY 6 |
| 25   | OK         | OK     |                                       | RELAY 7 |
| 26   | OK         | OK     |                                       | RELAY 8 |
| 27   | OK         | OK     |                                       | TOUCH 7 |
| 32   | OK         | OK     |                                       | TOUCH 9 |
| 33   | OK         | OK     |                                       | TOUCH 8 |
| 34   | OK         |        | INPUT ONLY                            |         |
| 35   | OK         |        | INPUT ONLY                            |         |
| 36   | OK         |        | INPUT ONLY                            |         |
| 39   | OK         |        | INPUT ONLY                            |         |

## Logic

Touch inputs are hooked up to interruptions to be as fast as possible in the activation / deactivation of the relays.

WIFI / MQTT Resilient logic, the device must recover from connection lost avoiding infinite loops.

Initial config , via bluetooth? to much? as a http hot-spot? need to sort out this

OTA would be nice but is not the primary goal of this.

## Config

Create a io.adafruit.com account ,create a group and two feeds in it.
Must create a secrets.h file like this and complete with the correct data

```cpp
#define WLAN_SSID       "MI WIFI SSID"
#define WLAN_PASS       "MI WIFI PASS"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "ADAFRUI IO USER"
#define AIO_KEY       "ADAFUIT IO KEY"
```
