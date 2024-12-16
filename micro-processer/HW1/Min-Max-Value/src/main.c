#include<avr/io.h>
#include<util/delay.h>

unsigned char count_ones(unsigned char n){
  unsigned char count=0;
  while(n){
    count+=n & 1;
    n>>=1;
  }
  return count;
}

int main(){
  unsigned char byteArray[]={0x29, 0xF0, 0x1C};
  unsigned char size = 3;
  unsigned char max_byte = 0;
  unsigned char min_byte = 0;
  unsigned char max_ones = 0;
  unsigned char min_ones = 8; 
  DDRB = 0xFF;
  DDRC = 0xFF;
  for(unsigned char i=0; i<size; i++){
    unsigned char ones_count = count_ones(byteArray[i]);
    //in this loop we find the byte with maximum and minimum number of ones
    if(ones_count > max_ones){
      max_ones = ones_count;
      max_byte = byteArray[i];
    }
    if(ones_count < min_ones){
      min_ones = ones_count;
      min_byte = byteArray[i];
    }
  }
  PORTB=max_byte;
  PORTC=min_byte;
  while(1){
    //we do nothing in this loop, the program will run forever
  }
}