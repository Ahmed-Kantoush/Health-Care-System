#define USE_ARDUINO_INTERRUPTS true
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <PulseSensorPlayground.h>

#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

const int PulseWire = 0;
const int LED13 = 13;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

//Constants
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Variables
float hum, temp;
float co, co2;
float body_temp;
int bpm;

void setup()
{
  Serial.begin(9600);
  
  dht.begin();
  sensors.begin();

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold);
  pulseSensor.begin();
}

void loop()
{
  hum = dht.readHumidity();
  temp= dht.readTemperature();
  
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  body_temp = sensors.getTempCByIndex(0);

  for (int i=0; i < 10; i++){
    co += analogRead(A1);
    co2 += analogRead(A2);
  }
  co /= 10;
  co2 /= 10;
  co -= 25;
  co2 -= 80;
  co = map(co, 0, 1023, 0, 2000);
  co2 = map(co2, 0, 1023, 350, 2000);

  if (pulseSensor.sawStartOfBeat())
    bpm = pulseSensor.getBeatsPerMinute();  

  Serial.print(hum);
  Serial.print(" ");
  Serial.print(temp);
  Serial.print(" ");
  Serial.print(body_temp);
  Serial.print(" ");
  Serial.print(co);
  Serial.print(" ");
  Serial.print(co2);
  Serial.print(" ");
  Serial.print(bpm);
  delay(1000);
}

   
