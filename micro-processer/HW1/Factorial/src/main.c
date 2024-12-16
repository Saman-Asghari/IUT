#include<avr/io.h>

int main(){
  while(1){
    DDRB=0x00;
    DDRC=0xFF;
    unsigned char input=PINB;
    unsigned char result=1;
    for(char i=1;i<=input;i++){
      result=result*i;
    }
    PORTC=result;
  }
  return 0;
}