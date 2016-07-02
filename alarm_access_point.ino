
/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "espalarm";
const char *password = "hackme";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() { // this is the function when a client is conncted
	server.send(200, "text/html", "<h1>You are connected</h1>"); // message for the browser
  digitalWrite(4, HIGH); // turn on buzzer
  delay(60000); // wait 60 seconds
  digitalWrite(4, LOW);
  delay(20000);
  digitalWrite(4, HIGH); // turn on buzzer again for a minute
  delay(60000);
  digitalWrite(4, LOW);
}

void setup() {
	delay(1000);
  pinMode(4, OUTPUT);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}
