#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  while (1)
  {
    DDRA=0x00;
    DDRB=0xFF;
    char input = PINA;
    char sum =0;
    //check if input is within the range -50 to 50 and calculate sum of digits
    if(input>=-50&&input<=50){
      if(input>0){
        while(input){
        sum += input%10;
        input /= 10;
      }
      }
      else{
        input = -input;
        while(input){
        sum += input%10;
        input /= 10;
      }
      
    }
    }
    else{
      sum = 128;
    }
    PORTB = sum;
  }
  return 0;
}