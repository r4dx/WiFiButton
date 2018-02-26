# WiFiButton
Button that sends requests over HTTP(s) using ESP8266

# Pins

1. D0 is used as input for button (HIGH means it's pressed)
1. 3V and GND is connected in parallel with button and EEPROM
1. D1 and D2 is used to connect EEPROM via I2C

# Connect Flow

1. When device starts up it tries to read WiFi SSID and password from config stored in EEPROM
1. If it fails it starts up as WiFi access point - in that case connect to it (WiFiButton) and configure the device using this URL: http://192.168.4.1/setup.html
1. If it finds WiFi configs it tries to connect to it
1. If it fails it starts as WiFi access point - see above
1. If it succeeds - it's ready to serve button presses

# Requirements

1. ESP8266-based development board
1. Button + 10k resistor
1. [AT24C64](http://www.switchdoc.com/wp-content/uploads/2015/01/doc0336.pdf) - 8Kb of EEPROM to store configuration
2. [Platform IO](http://platformio.org/) to get dependencies, compile and upload