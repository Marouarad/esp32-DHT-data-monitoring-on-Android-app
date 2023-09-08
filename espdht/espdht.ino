#include <time.h>       // include library for time functions
#include <WiFi.h>       // include library for WiFi connectivity
#include <FirebaseESP32.h>  // include library for Firebase ESP32
#include "DHTesp.h"     // include library for DHT sensor
#include<stdlib.h>      // include library for standard library functions
 
#define DHTpin 4        // define the DHT sensor pin
DHTesp dht;             // create a DHT object
 
char buff[10];          // create a buffer for converting floats to strings
#define FIREBASE_HOST "https://...."     // set the Firebase host URL
#define FIREBASE_AUTH "****"            // set the Firebase authentication token
#define WIFI_SSID "your ssid"           // set the WiFi SSID
#define WIFI_PASSWORD "your pass"       // set the WiFi password
 
FirebaseData firebaseData;      // create a FirebaseData object
FirebaseJson json;              // create a FirebaseJson object
 
String mytemp;      // create a String object for the temperature
String myhum;       // create a String object for the humidity

void setup()
{
  Serial.begin(115200);   // initialize serial communication at 115200 baud

  // Initialize the DHT sensor
  dht.setup(DHTpin, DHTesp::DHT11);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);   // start WiFi connection
  Serial.print("Connecting to Wi-Fi");    // print status message
  while (WiFi.status() != WL_CONNECTED)   // wait until connected to WiFi
  {
    Serial.print(".");      // print a dot every 300ms while waiting for the connection to be established
    delay(300);
  }
  Serial.println();         // print new line
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());   // print local IP address
  Serial.println();

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // start Firebase connection
  Firebase.reconnectWiFi(true);       // enable WiFi reconnection

  // Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);

  // Set write size limit and timeout to "tiny" (1s)
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
 
  Serial.println("--------------------------------");
  Serial.println("Connected...");
}

void loop()
{
  // Read data from the DHT sensor
  delay(dht.getMinimumSamplingPeriod());    // wait for the sensor to stabilize
  
  float humidity = dht.getHumidity();       // get the humidity reading
  float temperature = dht.getTemperature(); // get the temperature reading
  myhum = dtostrf(humidity,3,2,buff);       // convert humidity to a String
  mytemp = dtostrf(temperature,3,2,buff);   // convert temperature to a String

  // Print the temperature and humidity to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(mytemp);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(myhum);
  Serial.println(" %");

  // Get the current date and time
  time_t now;                 // create a time_t object for the current time
  struct tm * timeinfo;       // create a tm object for the current time
  char datetime[20];          // create a char array for the formatted date/time string

  time(&now);                 // get the current time
  timeinfo = localtime(&now);

  // Format the date and time as "YYYY-MM-DD HH:MM:SS"
  sprintf(datetime, "%04d-%02d-%02d %02d:%02d:%02d", 
    timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
    timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  // Add the temperature, humidity, and date/time to the Firebase JSON object
  json.clear();
  json.set("/hum", myhum);
  json.set("/temp", mytemp);
  json.set("/datetime", datetime);

  // Update the Firebase database with the JSON object
  Firebase.updateNode(firebaseData,"/DHTSensor",json);

  // Wait for 5 seconds before reading the sensor again
  delay(5000); 
}
