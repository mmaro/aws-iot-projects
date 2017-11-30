
#include "SparkFunBME280.h"
#include "SparkFunCCS811.h"
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// For Bluetooth Communication to Raspberry Pi
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#include "rgb_lcd.h"


rgb_lcd lcd;


// DFRobot Digital Buzzer
const int dfrobotDigitalBuzzPin = 6;

int waterSensorValue = 0;   // variable for reading the water sensor status

/***************************** ENVIRONMENTAL SENSOR CCS811 ******************/
#define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address

CCS811 myCCS811Sensor(CCS811_ADDR);
/***************************** ENVIRONMENTAL SENSOR CCS811 ******************/

/***************************** ENVIRONMENTAL SENSOR BME280 ******************/
//Global sensor object
BME280 myBME280Sensor;
/***************************** ENVIRONMENTAL SENSOR BME280 ******************/

/***************************** GPS SENSOR ******************/
// If using software serial, keep this line enabled
// (you can change the pin numbers to match your wiring):
SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences. 
#define GPSECHO  false

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy
/***************************** GPS SENSOR ******************/


/***************************** BLE ******************/
// Create the bluefruit object, either software serial...uncomment these lines
//SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

//Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
//                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
/*Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);           

#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"                      

 // A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
} */                    
/***************************** BLE ******************/

/***************************** PUSH BUTTON ******************/
// constants won't change. They're used here to
// set pin number
const int buttonPin = 7;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

/***************************** PUSH BUTTON ******************/

// LED
const int ledPin =  13;      // the number of the LED pin


void setup() {
  // put your setup code here, to run once:

  Serial.begin (115200);

 /***************************** BLE SETUP ******************/

  /* Initialise the module */
 /* Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /* Disable command echo from Bluefruit */
 /* ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
 /* ble.info();

  Serial.println();   

  //ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  /*while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("******************************"));

  // LED Activity command is only supported from 0.6.6
  /*if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  } */

  // Set module to DATA mode
  /*Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************")); */

 /***************************** BLE SETUP ******************/ 
 
  /***************************** DF ROBOT Digital Buzzer ******************/
  
  // INPUT_PULLUP defaults it to HIGH.
  pinMode(dfrobotDigitalBuzzPin, OUTPUT);  // configures the Digital Buzzer Pin as an OUTPUT
  
  /***************************** DF ROBOT Digital Buzzer ******************/

  /***************************** PUSH BUTTON ******************/
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  /***************************** PUSH BUTTON ******************/

  /***************************** LED ******************/
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  /***************************** LED ******************/



  /***************************** WATER SENSOR ******************/


  /***************************** CCS811 SENSOR SETUP ******************/
  // INPUT_PULLUP defaults it to HIGH.
  // digitalWrite(dfrobotDigitalBuzzPin, LOW);   // configures the Digital Buzzer Pin as an OUTPUT
  
  /***************************** WATER SENSOR ******************/

  //It is recommended to check return status on .begin(), but it is not
  //required.
  CCS811Core::status returnCode = myCCS811Sensor.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    Serial.println(".begin() returned with an error.");
    while (1); //Hang if there was a problem.
  }

  /***************************** CCS811 SENSOR SETUP ******************/

  
  /***************************** BME280 SENSOR SETUP ******************/

  //Initialize BME280
  //For I2C, enable the following and disable the SPI section
  myBME280Sensor.settings.commInterface = I2C_MODE;
  myBME280Sensor.settings.I2CAddress = 0x77;
  myBME280Sensor.settings.runMode = 3; //Normal mode
  myBME280Sensor.settings.tStandby = 0;
  myBME280Sensor.settings.filter = 4;
  myBME280Sensor.settings.tempOverSample = 5;
  myBME280Sensor.settings.pressOverSample = 5;
  myBME280Sensor.settings.humidOverSample = 5;

  //Calling .begin() causes the settings to be loaded
  delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
  byte id = myBME280Sensor.begin(); //Returns ID of 0x60 if successful
  if (id != 0x60)
  {
    Serial.println("Problem with BME280");
  }
  else
  {
    //Serial.println("BME280 online");
  }

  /***************************** BME280 SENSOR SETUP ******************/

  /***************************** GPS SENSOR SETUP ******************/

  //Serial.println("Adafruit GPS library basic test!");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
  
  /***************************** GPS SENSOR SETUP ******************/

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // in milliseconds
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // Water Sensor: read the input on analog pin 0:
  waterSensorValue = analogRead(A0);
  Serial.print(",watersensorvalue,");
  Serial.print(waterSensorValue);

  lcd.setCursor(0, 0);
  delay(1);        // delay in between reads for stability
  lcd.print(waterSensorValue);
  delay(1);

  /***************************** DF ROBOT Digital Buzzer ******************/

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  } 


  if (waterSensorValue < 150 && buttonState == HIGH) {
    // turn DF ROBOT Digital Buzzer off: 
    digitalBuzzer();
  } else 
  if (waterSensorValue > 150) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // start buzzing:
    digitalWrite(dfrobotDigitalBuzzPin, HIGH);
    delay(1); 
  } 

  /***************************** DF ROBOT Digital Buzzer ******************/

  /***************************** GAS SENSOR ******************/

    
    //Serial.print("The gas density is in everlasting loop ");
    readGasSensor();

  /***************************** GAS SENSOR ******************/

  printCCS811SensorData();
  printBME280SensorData();

  dfrobotPIRMotionSensorData();
  //mdMotionSensorData();


  gpsSensorData();

 delay(1000);
  
}
  
/***************************** DF ROBOT Digital Buzzer ******************/

void digitalBuzzer()                     
{
  digitalWrite(dfrobotDigitalBuzzPin, LOW); 
  delay(1);        
}

/***************************** DF ROBOT Digital Buzzer ******************/



/***************************** DF ROBOT PIR Motion SENSOR ******************/


void dfrobotPIRMotionSensorData() {
  int sensorValuePIRMotion = analogRead(A2);
  //Serial.print("motion state: ");
  Serial.print(",pirmotiondat,");
  Serial.print(sensorValuePIRMotion);
  Serial.println(",stop");

  delay(3);
  
}

/***************************** DF ROBOT PIR Motion SENSOR ******************/

/***************************** MD Motion SENSOR ******************/


void mdMotionSensorData() {
  int sensorValueOrdinaryMotion = analogRead(A1);
  //Serial.print("Ordinary motion state: ");
  Serial.print(",mdmotiondat,");
  Serial.print(sensorValueOrdinaryMotion);
  Serial.println(",stop");

  delay(3);
}

  
/***************************** MD Motion SENSOR ******************/


/***************************** GAS SENSOR ******************/

void readGasSensor() 
{
    float vol;
    int sensorValue = analogRead(A3);
    vol=(float)sensorValue/1024;
    //Serial.print("The gas density is ");
    Serial.print(",gas,");
    Serial.print(vol);
    
    delay(1);
}

/***************************** GAS SENSOR ******************/

/***************************** ENVIRONMENTAL SENSOR ******************/

void printCCS811SensorData()
{
  //Check to see if data is ready with .dataAvailable()
  if (myCCS811Sensor.dataAvailable())
  {
    //If so, have the sensor read and calculate the results.
    //Get them later
    myCCS811Sensor.readAlgorithmResults();

    Serial.print(",co2,");
    Serial.print(myCCS811Sensor.getCO2());

    Serial.print(",tvoc,");
    Serial.print(myCCS811Sensor.getTVOC());

    /*Serial.print("CO2[");
    //Returns calculated CO2 reading
    Serial.print(myCCS811Sensor.getCO2());
    Serial.print("] tVOC[");
    //Returns calculated TVOC reading
    Serial.print(myCCS811Sensor.getTVOC());
    Serial.print("] millis[");
    //Simply the time since program start
    Serial.print(millis());
    Serial.print("]"); */
    //Serial.println();
  }

  delay(10);
}

void printBME280SensorData()
{

  float tempVal;

  tempVal = (float) myBME280Sensor.readTempC();
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0): 
  lcd.setCursor(0, 1);
    
  delay(1);
    
  lcd.print(tempVal);

 
  Serial.print(",temp,");
  Serial.print(tempVal, 1);

  Serial.print(",pressure,");
  Serial.print(myBME280Sensor.readFloatPressure(), 2);

  Serial.print(",humidity,");
  Serial.print(myBME280Sensor.readFloatHumidity(), 0);

  /*Serial.print(" temp[");
  Serial.print(myBME280Sensor.readTempC(), 1);
  Serial.print("]C");

  //Serial.print(" temp[");
  //Serial.print(myBME280Sensor.readTempF(), 1);
  //Serial.print("]F");

  Serial.print(" pressure[");
  Serial.print(myBME280Sensor.readFloatPressure(), 2);
  Serial.print("]Pa");

  Serial.print(" humidity[");
  Serial.print(myBME280Sensor.readFloatHumidity(), 0);
  Serial.print("]%");

  Serial.println(); */

  delay(10);

}

/*
void printData()
{
  Serial.print(" CO2[");
  Serial.print(myCCS811Sensor.getCO2());
  Serial.print("]ppm");

  Serial.print(" TVOC[");
  Serial.print(myCCS811Sensor.getTVOC());
  Serial.print("]ppb");

  Serial.print(" temp[");
  Serial.print(myBME280Sensor.readTempC(), 1);
  Serial.print("]C");

  //Serial.print(" temp[");
  //Serial.print(myBME280Sensor.readTempF(), 1);
  //Serial.print("]F");

  Serial.print(" pressure[");
  Serial.print(myBME280Sensor.readFloatPressure(), 2);
  Serial.print("]Pa");

  Serial.print(" humidity[");
  Serial.print(myBME280Sensor.readFloatHumidity(), 0);
  Serial.print("]%");

  Serial.println();

  delay(10);
} */

void printDriverError( CCS811Core::status errorCode )
{
  switch ( errorCode )
  {
    case CCS811Core::SENSOR_SUCCESS:
      Serial.print("SUCCESS");
      break;
    case CCS811Core::SENSOR_ID_ERROR:
      Serial.print("ID_ERROR");
      break;
    case CCS811Core::SENSOR_I2C_ERROR:
      Serial.print("I2C_ERROR");
      break;
    case CCS811Core::SENSOR_INTERNAL_ERROR:
      Serial.print("INTERNAL_ERROR");
      break;
    case CCS811Core::SENSOR_GENERIC_ERROR:
      Serial.print("GENERIC_ERROR");
      break;
    default:
      Serial.print("Unspecified error.");
  }
}

/***************************** ENVIRONMENTAL SENSOR ******************/


/***************************** GPS SENSOR ******************/

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();
void gpsSensorData()                     // run over and over again
{
  // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
  }
  
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer
    
    /*Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);  */
    if (GPS.fix) {

      Serial.print(",latLocation,");
      Serial.print(GPS.latitudeDegrees, 4);

      Serial.print(",lonLocation,");
      Serial.print(GPS.longitudeDegrees, 4);
      
      /*Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", "); 
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", "); 
      Serial.println(GPS.longitudeDegrees, 4);
      
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites); */
    }
  }
}

/***************************** GPS SENSOR ******************/

/***************************** SEND ALL SENSOR DATA FROM ARDUINO TO RPi  ******************/
/*void bleSendAllDataUserInput(void)
{
  // Display command prompt
  Serial.print(F("AT > "));

  // Check for user input and echo it back if anything was found
  char command[BUFSIZE+1];
  getUserInput(command, BUFSIZE);

  // Send command
  ble.println(command);

  // Check response status
  ble.waitForOK();
}

/**************************************************************************/
/*!
    @brief  Checks for user input (via the Serial Monitor)
*/
/**************************************************************************/
/*void getUserInput(char buffer[], uint8_t maxSize)
{
  memset(buffer, 0, maxSize);
  while( Serial.available() == 0 ) {
    delay(1);
  }

  uint8_t count=0;

  do
  {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while( (count < maxSize) && !(Serial.available() == 0) );
}

/***************************** SEND ALL SENSOR DATA FROM ARDUINO TO RPi  ******************/



/***************************** ENVIRONMENTAL SENSOR OUT ******************/
//#include "SparkFunBME280.h"
//#include "SparkFunCCS811.h"
// sketch_nov25a
/*
 #define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address

//Global sensor objects
CCS811 myCCS811(CCS811_ADDR);
BME280 myBME280;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Apply BME280 data to CCS811 for compensation.");

  //This begins the CCS811 sensor and prints error status of .begin()
  CCS811Core::status returnCode = myCCS811.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    Serial.println("Problem with CCS811");
    //printDriverError(returnCode);
  }
  else
  {
    Serial.println("CCS811 online");
  }

  //Initialize BME280
  //For I2C, enable the following and disable the SPI section
  myBME280.settings.commInterface = I2C_MODE;
  myBME280.settings.I2CAddress = 0x77;
  myBME280.settings.runMode = 3; //Normal mode
  myBME280.settings.tStandby = 0;
  myBME280.settings.filter = 4;
  myBME280.settings.tempOverSample = 5;
  myBME280.settings.pressOverSample = 5;
  myBME280.settings.humidOverSample = 5;

  //Calling .begin() causes the settings to be loaded
  delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
  byte id = myBME280.begin(); //Returns ID of 0x60 if successful
  if (id != 0x60)
  {
    Serial.println("Problem with BME280");
  }
  else
  {
    Serial.println("BME280 online");
  }
}


void loop()
{
  //Check to see if data is available
  if (myCCS811.dataAvailable())
  {
    //Calling this function updates the global tVOC and eCO2 variables
    myCCS811.readAlgorithmResults();
    //printData fetches the values of tVOC and eCO2
    //printData();

    float BMEtempC = myBME280.readTempC();
    float BMEhumid = myBME280.readFloatHumidity();

    Serial.print("Applying new values (deg C, %): ");
    Serial.print(BMEtempC);
    Serial.print(",");
    Serial.println(BMEhumid);
    Serial.println();

    //This sends the temperature data to the CCS811
    myCCS811.setEnvironmentalData(BMEhumid, BMEtempC);
  }
  else if (myCCS811.checkForStatusError())
  {
    Serial.println(myCCS811.getErrorRegister()); //Prints whatever CSS811 error flags are detected
  }

  delay(2000); //Wait for next reading
}


 /***************************** ENVIRONMENTAL SENSOR OUT ******************/


 /***************************** ULTRASONIC1 SENSORS OUT ******************/


 
 /***************************** ULTRASONIC1 SENSORS OUT ******************/
