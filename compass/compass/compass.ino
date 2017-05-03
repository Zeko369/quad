////////////////////////////////////////////////////////////
//	    COMPASS mk1			                  //
//			Fran Zekan, 27.02.2016, 17:00     //
////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//ONE
//#include "I2Cdev.h"
//#include "HMC5883L.h"

//HMC5883L mag;
//int16_t mx, my, mz;

//TWO
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

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
	Wire.begin();
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//	mag.initialize();
	mag.begin();

	pinMode(led, OUTPUT);

	start();
}

void loop()
{
	display.clearDisplay();
	display.setTextSize(1);
	display.setCursor(0, 0);

//	one();
	two();

	display.display();
	delay(250);
}

/*void one()
{
	mag.getHeading(&mx, &my, &mz);
	display.print(mx);
	display.print(" ");
	display.print(my);
	display.print(" ");
	display.print(mz);
	display.println();
	display.println();

	float heading = atan2(my, mx);
	if(heading < 0)
		heading += 2 * M_PI;

	display.setTextSize(3);
	display.println(heading * 180/M_PI);
}*/

void two()
{
	sensors_event_t event; 
	mag.getEvent(&event);
 
	display.print("X: "); display.print(event.magnetic.x); display.println();
	display.print("Y: "); display.print(event.magnetic.y); display.println();
	display.print("Z: "); display.print(event.magnetic.z); display.println();

	float heading = atan2(event.magnetic.y, event.magnetic.x);
	  
	float declinationAngle = 0.0523598775;
	heading += declinationAngle;
	  
	if(heading < 0)
		heading += 2*PI;
	if(heading > 2*PI)
		heading -= 2*PI;
	   
	float headingDegrees = heading * 180/M_PI; 

	display.setTextSize(2);
	display.println();
	display.print(headingDegrees);
}
