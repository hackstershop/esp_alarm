#include <ESP8266WiFi.h>
const char* ssid     = "espalarm"; // acces point name
const char* password = "hackme"; // password of esp access point
const char* host = "192.168.4.1"; // default ip to serve content
boolean button_state = false; // global variable of button state 
boolean alarm_ready = false; // global variable of alarm_ready
int count = 0; // counter of motion sensor
void setup() {  
  //Serial.begin(115200);
  pinMode(4, INPUT); // motion sensor input pin
  pinMode(5, INPUT); // button input pin
  pinMode(16, OUTPUT); // led pin
  delay(10);
  
 
}

void loop() {
    if (digitalRead(5) == HIGH){ // if button pressed
        button_state = !button_state; // toggle button_state
        delay(300); // debounce button with delay
        //Serial.println("button pressed state changed");
        digitalWrite(16, HIGH); // blink twice
            delay(500);
            digitalWrite(16, LOW);
            delay(500);
            digitalWrite(16, HIGH);
            delay(500);
            digitalWrite(16, LOW);
            delay(500);
      }
      if (!alarm_ready && button_state){ // check if button_state is on , do it only if alarm is not yet ready 
        //Serial.println("if state is on turn on led and wait 30 seconds");
          digitalWrite(16, HIGH); // turn led on
          delay(30000); // delay 30 seconds
           digitalWrite(16, LOW); // turn led off
          alarm_ready = true; // now alarm is ready 
          //Serial.println("alarm_ready true");
        }
        else if(!state){ // if button is pressed again turn alarm_ready off
            alarm_ready = false;
            count = 0; // reset counter
           // Serial.println("alarm_ready false");
            
          }
    if (alarm_ready && digitalRead(4) == HIGH ){ // if alarm_ready check for motion in the car
        count+=1; // add to counter
     // Serial.println(count);
     
      if (count > 20){ // if counter is bigger than threshold
         //Serial.println("alarm_ready and sensor detected - connect to esp");
         WiFi.begin(ssid,password);
       while (WiFi.status() != WL_CONNECTED) {
       delay(500);
   }
       WiFiClient client;
        const int httpPort = 80;
        //String url = "/input.php";
 
        if (client.connect(host, httpPort)){
          delay(10);
          if(client.print(String("GET ") + "/" +" HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n") ){
          delay(10);
        //Serial.println("detected");
          state = false;
          alarm_ready = false;
          count = 0;
        }
    } 
  }
  }
  delay(1000);
}
