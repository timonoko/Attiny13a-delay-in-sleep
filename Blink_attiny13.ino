#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

const int red=4;
const int green=3;
const int blue=2;

ISR(WDT_vect) {}

void nokosleep(int secs){
  while (secs>8) {
    wdt_enable(WDTO_8S);
    WDTCR |= (1<<WDTIE) ;
    sleep_mode();
    wdt_disable();
    secs=secs-9;
  }
  delay(secs*100);
 }
void setup(){
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  ADCSRA &= ~(1<<ADEN); //Disable ADC
  ACSR = (1<<ACD); //Disable the analog comparator
  DIDR0 = 0x3F; //Disable digital input buffers on all ADC0-ADC5 pins.
  sei(); // Enable global interrupts  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);// Use the Power Down sleep mode
  while (true) { 
    digitalWrite(green, HIGH);
    nokosleep(1);            
    digitalWrite(green, LOW); 
    nokosleep(30);            
    for (int i = 0; i < 5; i++) {
      digitalWrite(red, HIGH);
      nokosleep(1);            
      digitalWrite(red, LOW); 
      nokosleep(2);            
    }
  }
}


