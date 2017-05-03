#define battPin0 A3    // select the input pins for the batteries
#define battPin1 A2
#define battPin2 A1
#define battPin3 A0

float battWeighting = 0.1; // define a weighting to apply to our exponential moving average calculation for battery 

int abattValue0 = 0; // variable to store average value (exponential moving average) calculation
int abattValue1 = 0;
int abattValue2 = 0;
int abattValue3 = 0;

float Cell1 = 0.00; // variable to store actual cell voltages
float Cell2 = 0.00;
float Cell3 = 0.00;
float Cell4 = 0.00;

float adcVolt = 0.0048680351906158 ; // one point on the ADC equals this many volts

void setup() {
  Serial.begin(115200);
  
  // Read the battery voltage values and set up the averaging
  // require 50 reads to initialise correct ewv.
  for (int i=0; i<50; i++){
    getBattVolts();
  }
}

void loop() {
  // basic get and show voltages
  getBattVolts();
  showBattVolts();
  delay(500);                  
}

void getBattVolts() {
  // read the value from the sensor:
  abattValue0 = (analogRead(battPin0) * battWeighting) + (abattValue0 * (1-battWeighting));
  abattValue1 = (analogRead(battPin1) * battWeighting) + (abattValue1 * (1-battWeighting));
  abattValue2 = (analogRead(battPin2) * battWeighting) + (abattValue2 * (1-battWeighting));
  abattValue3 = (analogRead(battPin3) * battWeighting) + (abattValue3 * (1-battWeighting));
  // convert these values to cell voltages
  Cell1 = (adcVolt * abattValue0 * 1) ;
  Cell2 = (adcVolt * abattValue1 * 1.8298)-Cell1;
  Cell3 = (adcVolt * abattValue2 * 2.6078)-Cell2-Cell1;
  Cell4 = (adcVolt * abattValue3 * 3.7659)-Cell3-Cell2-Cell1;
}

void showBattVolts() {
  Serial.print (Cell1);
  Serial.print ("V. " );
  Serial.print (Cell2);
  Serial.print ("V. ");
  Serial.print (Cell3);
  Serial.print ("V. ");
  Serial.print (Cell4);
  Serial.print ("V. Total = " );
  Serial.println (Cell1+Cell2+Cell3+Cell4);
}
