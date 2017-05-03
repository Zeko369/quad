////////////////////////////////////////////////////////////
//	ALTITUDE METER - BMP altitude                     //
//			Fran Zekan, 26.02.2016, 20:00     //
////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

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

	start();

	if(!bmp.begin())
        {
          /* There was a problem detecting the BMP085 ... check your connections */
          Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");

	  display.clearDisplay();
	  display.setCursor(0, 0);
	  display.setTextSize(1);
	  display.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
	  display.display();
          while(1);
        }

	pinMode(led, OUTPUT);


}

void loop()
{
	display.clearDisplay();
	display.setTextSize(1);
	display.setCursor(0, 0);

	sensors_event_t event;
        bmp.getEvent(&event);

	if (event.pressure)
        {
          display.print("Pressure:    ");
          display.print(event.pressure);
          display.println(" hPa");

          float temperature;
          bmp.getTemperature(&temperature);
          display.print("Temperature: ");
          display.print(temperature);
          display.println(" C");

          float seaLevelPressure = 1019;
          display.print("Altitude:    ");
          display.print(bmp.pressureToAltitude(seaLevelPressure,
                                              event.pressure));
          display.println(" m");
          display.println("");
        }
        else
        {
          display.println("Sensor error");
        }

	display.display();
	delay(1000);
}
