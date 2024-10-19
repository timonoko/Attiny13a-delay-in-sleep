#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

const int green=PB3;
const int red=PB4;

const int vauhti=8;

ISR(WDT_vect) {}

void nokosleep(int secs){
  while (secs>vauhti) {
    wdt_enable(WDTO_8S);
    WDTCR |= (1<<WDIE) ;
    sleep_mode();
    wdt_disable();
    secs=secs-vauhti-1;
  }
  delay(secs*100);
 }

void setup(){
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  // ADCSRA &= ~(1<<ADEN); //Disable ADC
  //ACSR = (1<<ACD); //Disable the analog comparator
  //DIDR0 = 0x3F; //Disable digital input buffers on all ADC0-ADC5 pins.
  sei(); // Enable global interrupts  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);// Use the Power Down sleep mode
  while (true) {
    digitalWrite(green, HIGH);
    delay(100);            
    digitalWrite(green, LOW); 
    nokosleep(30);
    for (int i = 0; i < 10; i++) {
      digitalWrite(red, HIGH);
      delay(100);            
      digitalWrite(red, LOW); 
      delay(100);
    }
  }
}
/*

void setup() {                
  pinMode(1, OUTPUT);      // LED on Model A   
}

void loop() {
  digitalWrite(1, HIGH);
  delay(100);             // Wait for a second
  digitalWrite(1, LOW); 
  delay(8000);             // Wait for a second
}
*/
