////////////////////////////////////////////////////////////
//	SMART BATTERY - Voltage to % meter mk1            //
//			Fran Zekan, 21.02.2016, 23:07     //
////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(4);

uint8_t lipo[3] = {A0, A1, A2};
uint8_t s = 2;

uint8_t read_temp;
uint8_t prec_pre_cell[3];
uint16_t precAll;
float voltage[3];

uint8_t led = 13;

uint8_t led_ind[4] = {10, 9, 8, 7};
uint8_t button = 6;

void start()
{
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,10);
	display.print("SMART BATTERY mk1");

	display.display();
	Serial.println("SMART BATTERY mk1");

	killLeds();
	pinModes();

	digitalWrite(led, 1);
	delay(500);
	digitalWrite(led, 0);
	delay(500);
}

void drawBattery(int x, int y, int prec)
{
	uint8_t battFill =  prec/5;
        display.drawRect(x,    y,   20, 8, 1);
        display.drawRect(x+20, y+2, 2, 4, 1);
        display.fillRect(x,    y+1, battFill, 6, 1);{
}

void blinkLED(int prec)
{
	if(digitalRead(button) == 0)
	{
		for(int i = 0; i<100/prec; i++)
		{
			digitalWrite(led_ind[i], HIGH);	
		}	

		delay(1000);
		killLeds();
	}
}

void killLeds()
{
	for(int i = 0; i<4; i++)
	{
		digitalWrite(led_ind[i], LOW);		
	}
}

void pinModes()
{
	for(int i = 0; i<s; i++)
	{
		pinMode(lipo[i], INPUT);	
	}

	pinMode(led, OUTPUT);
	
	pinMode(button, INPUT_PULLUP);

	for(int i = 0; i<4; i++)
	{
		pinMode(led_ind[i], OUTPUT);	
	}
}

////////////////////////////////////////////////////////////////////////////////////
//			      		 SETUP					  //
////////////////////////////////////////////////////////////////////////////////////
void setup()
{
	Serial.begin(9600);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	start();
}

////////////////////////////////////////////////////////////////////////////////////
//			      		LOOP					  //
////////////////////////////////////////////////////////////////////////////////////
void loop()
{
	for(int i = 0; i<s; i++)
	{
		voltage[i] = analogRead(lipo[i]) * (5.0 / 1023.0);	
		prec_pre_cell[i] = map(voltage[i], 3.7, 4.2, 0, 100);
		precAll += prec_pre_cell[i];
	}		

	precAll /= s;

	display.clearDisplay();	
	display.setTextSize(2);
	display.setCursor(0, 0);

	for(int i = 0; i<s; i++)
	{
		display.setCursor(0, s*20);
		display.print(voltage[i]);
		display.print(" V");	
		display.println(map(voltage[i], 3.7, 4.2, 0, 100));

		drawBattery(100, s*20, precAll); 
	}

	for(int i = 0; i<s; i++)
	{
		Serial.print(voltage[i]); 
		Serial.print(" V ");
		Serial.print(map(voltage[i], 3.7, 4.2, 0, 100));
		Serial.print(" ");
	}
	Serial.println("");

	display.display();
	delay(50);
}
