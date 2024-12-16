#include<avr/io.h>
#include<util/delay.h>

unsigned char calculate_gcd(unsigned char a, unsigned char b) {
    while (b != 0) {
        unsigned char temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main(void){
   DDRA = 0x00; 
   DDRB = 0x00; 
   DDRC = 0xFF; 
   while (1) {
        unsigned char number1 = PINA;
        unsigned char number2 = PINB;
        unsigned char gcd = calculate_gcd(number1, number2);
        PORTC = gcd;
    }

    return 0;
}