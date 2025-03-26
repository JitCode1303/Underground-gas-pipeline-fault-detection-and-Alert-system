
#include <ESP8266WiFi.h>

String apiKey = "VZHG1VK1NBN87MAR";     // Enter your Write API key from ThingSpeak///IR56H8CTQVQA9O2E
const char* ssid = "PROJECT";         // Replace with your Wi-Fi SSID
const char* pass = "123456789";         // Replace with your Wi-Fi password
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
}

void loop() { 
if(Serial.available()>0){
  String data = Serial.readStringUntil('\n');
  Serial.println(data);

  int indexA = data.indexOf("a") + 1;
  int indexB = data.indexOf("b") + 1;
  int indexC = data.indexOf("c") + 1;
  int indexD = data.indexOf("d") + 1;
//  int indexE = data.indexOf("e") + 1;
  delay(500);
  String valueA = data.substring(indexA, indexB - 1);
  String valueB = data.substring(indexB, indexC - 1);
  String valueC = data.substring(indexC, indexD - 1);
  String valueD = data.substring(indexD);
//  String valueE = data.substring(indexE); // Assuming it goes to the end of the string

  delay(500);

  Serial.println("Value a: " + valueA);
  Serial.println("Value b: " + valueB);
  Serial.println("Value c: " + valueC);
  Serial.println("Value d: " + valueD);
//  Serial.println("Value e: " + valueE);
  delay(1000);
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=" + valueA;
    postStr += "&field2=" + valueB;
    postStr += "&field3=" + valueC;
    postStr += "&field4=" + valueD;

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    client.stop();

    // Thingspeak requires a minimum 15-second delay between updates

  }
}
  delay(5000);
}   