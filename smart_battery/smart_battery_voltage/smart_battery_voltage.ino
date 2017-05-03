////////////////////////////////////////////////////////////
//	SMART BATTERY - Voltage meter mk1                 //
//			Fran Zekan, 21.02.2016, 23:07     //
////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(4);

uint8_t lipo[3] = {A0, A1, A2};
uint8_t s = 2;

uint8_t read_temp;
float voltage[3];

uint8_t led = 13;

void start()
{
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,10);
	display.print("SMART BATTERY mk1");

	display.display();
	Serial.println("SMART BATTERY mk1");

	digitalWrite(led, 1);
	delay(500);
	digitalWrite(led, 0);
	delay(500);
}

////////////////////////////////////////////////////////////////////////////////////
//			      		 SETUP					  //
////////////////////////////////////////////////////////////////////////////////////
void setup()
{
	Serial.begin(9600);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	for(int i = 0; i<s; i++)
	{
		pinMode(lipo[i], INPUT);	
	}

	pinMode(led, OUTPUT);

	start();
}

////////////////////////////////////////////////////////////////////////////////////
//			         	LOOP					  //
////////////////////////////////////////////////////////////////////////////////////
void loop()
{
	for(int i = 0; i<s; i++)
	{
		voltage[i] = analogRead(lipo[i]) * (5.0 / 1023.0);	
	}		

	display.clearDisplay();	
	display.setTextSize(2);
	display.setCursor(0, 0);

	for(int i = 0; i<s; i++)
	{
		display.print(voltage[i]);
		display.println(" V");	
	}

	for(int i = 0; i<s; i++)
	{
		Serial.print(voltage[i]); 
		Serial.print(" V ");
	}
	Serial.println("");

	display.display();
	delay(50);
}
