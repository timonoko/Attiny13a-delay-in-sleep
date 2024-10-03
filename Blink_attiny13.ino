#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

const int red=4;
const int green=3;
const int blue=2;

ISR(WDT_vect) {}

void nokosleep(int secs){
  while (secs>9) {
    wdt_reset();
    wdt_enable(WDTO_8S);
    WDTCR |= (1<<WDTIE) ; 
    sleep_mode();
    secs=secs-9;
  }
  delay(secs*1000);
 }

int main(){
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  ADCSRA &= ~(1<<ADEN); //Disable ADC
  ACSR = (1<<ACD); //Disable the analog comparator
  DIDR0 = 0x3F; //Disable digital input buffers on all ADC0-ADC5 pins.
  sei(); // Enable global interrupts  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);// Use the Power Down sleep mode
  digitalWrite(red, HIGH);
  nokosleep(1);            
  digitalWrite(red, LOW); 
  nokosleep(3600);            
  while(true){
    digitalWrite(red, HIGH);
    nokosleep(1);            
    digitalWrite(red, LOW); 
    nokosleep(1);
  }
}



