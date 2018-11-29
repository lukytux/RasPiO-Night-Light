#include<FastLED.h>
#define NUM_LEDS 8
#define DATA_PIN 7
#define CLOCK_PIN 5
int pir = 0;
int ldr = 0;
int white_bright = 200;       // default brightness for white (0-255)
int r_bright = 255;       
int g_bright = 10;      
int b_bright = 0;       
int buzz_disable = 1;         // change to 1 to switch off initial buzzer
int compteur = 0;
int ledstatus = 0;

CRGBArray<NUM_LEDS> leds;

void setup() { 
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR, DATA_RATE_MHZ(12)>(leds, NUM_LEDS);
  FastLED.setBrightness(white_bright); // Global Brightness setting max 255 

  pinMode(12, INPUT);         // PIR motion sensor read port 
  pinMode(2, OUTPUT);         // buzzer port
  pinMode(13, OUTPUT);        // LED port
  if (buzz_disable == 0) {
     digitalWrite(2, HIGH);   // buzzer ON, if not disabled        
  }
  digitalWrite(13, HIGH);     // PIR LED ON
  delay(1000);
  digitalWrite(2, LOW);       // buzzer OFF
  digitalWrite(13, LOW);      // PIR LED OFF
}

void loop() {   
      pir = digitalRead(12);                  
      ldr = analogRead(7);  // read light sensor (0 = very dark, 1023 = very bright)
      
      if (ldr > 630 && ledstatus == 1){  // LEDs off if light go on  (630 is the value when the LED's are on at 200 of brightness with 255,10,0 for the colors
        compteur = 0;                             
      } 
      if (ldr > 50 && ledstatus == 0){ // Don't put the LED on if light go off
        compteur = 0;                             
      }
      if (compteur == 0){
          FastLED.clear();                       // reset LEDs to 0,0,0
          FastLED.show();                        // lights off
      }                                              
      if (compteur > 0 && ldr <= 50) {            
        digitalWrite(13, LOW);                 
        for(int i=0; i<NUM_LEDS; i++){
            leds[i].setRGB(r_bright, g_bright, b_bright);
        }
        FastLED.show();
        ledstatus = 1;
      }
      if (pir == 1){                           
        digitalWrite(13, HIGH);               
        delay(10);                            // Delay so when dark the LED will flash on for 0.1s
        digitalWrite(13, LOW);
        compteur = 100;
      }
      else{
       // digitalWrite(13, LOW);    
        compteur--;
      }
      delay(500);  
}
