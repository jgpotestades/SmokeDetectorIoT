#define BLYNK_TEMPLATE_ID "TMPL2Q-BQJVmG"
#define BLYNK_TEMPLATE_NAME "Smoke sensor"
#define BLYNK_AUTH_TOKEN "SvsgjMlY0yNSClq-YenSnhRf6jVjgcYN"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <LiquidCrystal_I2C.h> //LCD DISPLAY

char auth[] = BLYNK_AUTH_TOKEN;

int lcdColumns = 16;
int lcdRows = 2;
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

char ssid[] = "La_Fibre_dOrange_73D3";
char pass[] = "ATN2N95UC7DGKZR99G";


BlynkTimer timer;

const int smokeA0 = 0; //GPIO 0
//pins that works with internet
//analogRead( 39 );
//analogRead( 34 );
//analogRead( 35 );
//analogRead( 32 );
//analogRead( 33 );
int sensorThres = 100;

int data;


void sendSensor(){
 

 Blynk.virtualWrite(V0, data);
 
  //Serial.println(data);


  if(data > 300){
    //Blynk.email("test@gmail.com", "Alert", "Gas Leakage Detected!");
    Blynk.logEvent("smoke_detected","smoke detected");
    lcd.setCursor(0, 0);
    // print message
    lcd.print("Smoke Detected:");
    //Serial.println(data);
  
  }
  else {
    lcd.setCursor(0, 0);
    
    lcd.clear();
  // print message
  lcd.print("No danger:");}
}
void setup() {
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();

  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(smokeA0, INPUT);
  timer.setInterval(2500L, sendSensor);
}

void loop() {
   data = analogRead(smokeA0);
   lcd.setCursor(0,1);
   //delay(500);
  lcd.print(data);
   delay(1000);
   Serial.println(data);
  Blynk.run();
  timer.run();
}

