#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
DHT dht(D5, DHT11);
#define LED_GREEN D2
#define LED_YELLOW D3
#define LED_RED D4
#define MQ_135 A0
int ppm=0;
int gas_sensor;
float m = -0.3376; //Slope
float b = 0.7165; //Y-Intercept
float R0 = 3.12; //Sensor Resistance in fresh air from previous code
WiFiClient client;
long myChannelNumber = 123456; // Channel id
const char myWriteAPIKey[] = "API_Key";
void setup() {
 // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LED_GREEN,OUTPUT);
pinMode(LED_YELLOW,OUTPUT);
pinMode(LED_RED,OUTPUT);
pinMode(MQ_135, INPUT);
WiFi.begin("WiFi_Name", "WiFi_Password");
while(WiFi.status() != WL_CONNECTED)
 {
delay(200);
Serial.print(".");
 }
Serial.println();
Serial.println("NodeMCU is connected!");
Serial.println(WiFi.localIP());
dht.begin();
ThingSpeak.begin(client);
}
void loop() {
 float sensor_volt; //Define variable for sensor voltage
 float RS_gas; //Define variable for sensor resistance
 float ratio; //Define variable for ratio
 int sensorValue;//Variable to store the analog values from MQ-135
 float h;
 float t;
 float ppm_log; //Get ppm value in linear scale according to the the ratio value
 float ppm; //Convert ppm value to log scale
 h = dht.readHumidity();
delay(4000);
 t = dht.readTemperature();
delay(4000);
sensorValue = analogRead(gas_sensor); //Read analog values of sensor
sensor_volt = sensorValue*(5.0/1023.0); //Convert analog values to voltage
RS_gas = ((5.0*1.0)/sensor_volt)-1.0; //Get value of RS in a gas
 ratio = RS_gas/R0; // Get ratio RS_gas/RS_air
ppm_log = (log10(ratio)-b)/m; //Get ppm value in linear scale according to the ratio value
 ppm = pow(10, ppm_log); //Convert ppm value to log scale
Serial.println("Temperature: " + (String) t);
Serial.println("Humidity: " + (String) h);
Serial.println("Our desired PPM = "+ (String) ppm);
ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
delay(20000);
ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
delay(20000);
ThingSpeak.writeField(myChannelNumber, 3, ppm, myWriteAPIKey);
delay(20000);
 if(ppm<=100)
 {
digitalWrite(LED_GREEN,HIGH);
digitalWrite(LED_YELLOW,LOW);
digitalWrite(LED_RED,LOW);
 }
 else if(ppm<=200)
 {
digitalWrite(LED_GREEN,LOW);
digitalWrite(LED_YELLOW,HIGH);
digitalWrite(LED_RED,LOW);
 }
 else
 {
digitalWrite(LED_GREEN,LOW);
digitalWrite(LED_YELLOW,LOW);
digitalWrite(LED_RED,HIGH);
 }
delay(2000);}
