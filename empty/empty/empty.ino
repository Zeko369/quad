////////////////////////////////////////////////////////////
//	SMART BATTERY - Voltage meter mk1                 //
//			Fran Zekan, 21.02.2016, 23:07     //
////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(4);

uint8_t led = 13;

void start()
{
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,10);
	display.print("Altitude BMP 180 mk1");

	display.display();
	Serial.println("Altitude BMP 180 mk1");

	digitalWrite(led, 1);
	delay(500);
	digitalWrite(led, 0);
	delay(500);
}

void setup()
{
	Serial.begin(9600);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	pinMode(led, OUTPUT);

	start();
}

void loop()
{
	display.clearDisplay();
	display.setTextSize(1);
	display.setCursor(0, 0);

	display.display();
	delay(1000);
}
