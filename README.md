# termostat
https://circuits.io/circuits/5409828-termostat
esp8266
webinterface -control
mqtt - for statistics

#relay
https://www.electronics-tutorials.ws/blog/relay-switch-circuit.html\
#termistor
https://arduino.stackexchange.com/questions/36505/help-using-thermistor-with-esp8266

#libs
 <ArduinoJson.h>//https://github.com/bblanchon/ArduinoJson.git
//https://arduinojson.org

#Pins

Pin |	Function  |	ESP-8266 Pin| used
TX  |	TXD       |		TXD|
RX  |	RXD       |		RXD|
A0  |	Analog input, max 3.3V input|	A0|termistor 10k (2k to ground)
D0  |	IO        |	GPIO16|
D1  |	IO, SCL   |	GPIO5|
D2  |	IO, SDA   |	GPIO4|
D3  |	IO, 10k Pull-up|	GPIO0|
D4  |	IO, 10k Pull-up, BUILTIN_LED|	GPIO2| dht
D5  |	IO, SCK   |	GPIO14|
D6  |	IO, MISO  |	GPIO12|relay
D7  |	IO, MOSI  |	GPIO13|
D8  |	IO, 10k Pull-down, SS|	GPIO15|
G   |	Ground    |	GND|
5V  |	5V    |	-|
3V3 |	3.3V  |	3.3V|
RST |	Reset |	RST|

#termistor
(+3.3) -termistor- (A0) -resistor 3k- (GND)

#DHT
1 vcc (5V)
2 data (D4)
3 nc
4 GND (G)

#relay
d6