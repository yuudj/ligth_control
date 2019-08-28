# Light Control

Control multiple light relays with an ESP32 using touch inputs or MQTT.

## Context

Every time a turn on the lights in my living room 8 light bulbs turn on. The electrical pipes in my apartment are to small to put a switch and a cable for each light. In a previous iteration of this project I tried to use i2c to control each light but is easier, cheaper and faster to control the relays directly via multi-par cable.

## Features

- 8 relay outputs
- 9 touch inputs (8 for the relays and the 9th to activate de display and show some data)
- dht22 sensor 
- i2c OLED display.
- MQTT connection
- 3d printed case
- use recycled aluminum soda cans to make the touch buttons

## Connection

| GPIO | INPUT      | OUTPUT | NOTES                                 | CONFIG    |
| ---- | ---------- | ------ | ------------------------------------- | --------- |
| 0    | PULLED OUT | OK     | Outputs PWM signal at boot            | TOUCH IN  |
| 1    | TX pin     | OK     | Debug output at boot                  |           |
| 2    | OK         | OK     | Connected to on-board LED             | TOUCH IN  |
| 3    | OK         | RX PIN | HIGH at boot                          |           |
| 4    | OK         | OK     |                                       | TOUCH IN  |
| 5    | OK         | OK     | outputs PWM signal at boot            | RELAY OUT |
| 6    | X          | X      | Connected to the integrated SPI flash |           |
| 7    | X          | X      | Connected to the integrated SPI flash |           |
| 8    | X          | X      | Connected to the integrated SPI flash |           |
| 9    | X          | X      | Connected to the integrated SPI flash |           |
| 10   | X          | X      | Connected to the integrated SPI flash |           |
| 11   | X          | X      | Connected to the integrated SPI flash |           |
| 12   | OK         | OK     | Boot fail if pulled high              | TOUCH IN  |
| 13   | OK         | OK     |                                       | TOUCH IN  |
| 14   | OK         | OK     | Outputs PWM signal at boot            | TOUCH IN  |
| 15   | OK         | OK     | Outputs PWM signal at boot            | TOUCH IN  |
| 16   | OK         | OK     |                                       | RELAY OUT |
| 17   | OK         | OK     |                                       | RELAY OUT |
| 18   | OK         | OK     |                                       | RELAY OUT |
| 19   | OK         | OK     |                                       | RELAY OUT |
| 20   | OK         | OK     |                                       | DHT22     |
| 21   | OK         | OK     |                                       | I2C       |
| 22   | OK         | OK     |                                       | I2C       |
| 23   | OK         | OK     |                                       | RELAY OUT |
| 25   | OK         | OK     |                                       | RELAY OUT |
| 26   | OK         | OK     |                                       | RELAY OUT |
| 27   | OK         | OK     |                                       | TOUCH IN  |
| 32   | OK         | OK     |                                       | TOUCH IN  |
| 33   | OK         | OK     |                                       | TOUCH IN  |
| 34   | OK         |        | INPUT ONLY                            |           |
| 35   | OK         |        | INPUT ONLY                            |           |
| 36   | OK         |        | INPUT ONLY                            |           |
| 39   | OK         |        | INPUT ONLY                            |           |

## Logic

Touch inputs are hooked up to interruptions to be as fast as possible in the activation / deactivation of the relays.

WIFI / MQTT Resilient logic, the device must recover from connection lost avoiding infinite loops.

Initial config , via bluethooth? to much? as a http hot-spot?  need to sort out this

OTA would be nice but is not the primary goal of this. 