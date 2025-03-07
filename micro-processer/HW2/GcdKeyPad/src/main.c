#include <avr/io.h>
#include <util/delay.h>

#define LCD_PORT PORTC     // LCD data lines connected to PORTC
#define LCD_DDR  DDRC      // Data direction register for PORTC
#define LCD_RS   0       // Register Select pin connected to PD0
#define LCD_RW   1       // Read/Write pin connected to PD1
#define LCD_EN   2       // Enable pin connected to PD2
#define LCD_CTRL PORTD     // Control lines connected to PORTD
#define LCD_CTRL_DDR DDRD  // Data direction register for PORTD


char keypad[4][4] = {
    {'7', '8', '9','/'},
    {'4', '5', '6','*'},
    {'1', '2', '3','-'},
    {'o', '0', '=','+'}
};

void LCD_EnablePulse() {
    LCD_CTRL |= (1 << LCD_EN);  // Enable pin high
    _delay_us(2000);               // Short delay
    LCD_CTRL &= ~(1 << LCD_EN); // Enable pin low
    _delay_ms(2);     // Wait for command execution
}

void LCD_Command(unsigned char cmd) {
    LCD_PORT = cmd;              // Place command on data lines
    LCD_CTRL &= ~(1 << LCD_RS);  // RS = 0 for command
    LCD_CTRL &= ~(1 << LCD_RW);  // RW = 0 for write
    LCD_EnablePulse();
}

void LCD_Char(unsigned char data) {
    LCD_PORT = data;             // Place data on data lines
    LCD_CTRL |= (1 << LCD_RS);   // RS = 1 for data
    LCD_CTRL &= ~(1 << LCD_RW);  // RW = 0 for write
    LCD_EnablePulse();
}

void LCD_Init(void) {
    LCD_DDR = 0xFF; 
    LCD_CTRL_DDR=0xFF;
    LCD_CTRL &= ~(1<<LCD_EN);         // Set data port as output
    _delay_ms(2);               // LCD power-on delay
    LCD_Command(0x38);           // 8-bit mode, 2-line, 5x7 dots
    LCD_Command(0x0E);           // Display on, cursor off
    LCD_Command(0x01);           // Auto increment cursor
    _delay_ms(2);
    LCD_Command(0x06);           // Cursor increment, no display shift
}

void LCD_Clear(void) {
    LCD_Command(0x01);           // Send clear command
    _delay_ms(2);                // Wait for clear operation
}


void num_to_string(unsigned int num, char* buffer) {
    int i = 0;

    // Handle zero case
    if (num == 0) {
        buffer[i++] = '0';
    }

    // Extract digits from the number
    while (num > 0) {
        buffer[i++] = (num % 10) + '0'; // Get the last digit and convert to character
        num /= 10;
    }
    buffer[i] = '\0'; // Null-terminate the string

    // Reverse the string (since digits were added in reverse order)
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }
}
void LCD_String(const char* str) {
    while (*str) {
        LCD_Char(*str++);        // Send characters one by one
    }
}

void LCD_Number(unsigned int num) {
    char buffer[10];
    num_to_string(num,buffer);      // Convert number to string (base 10)
    LCD_String(buffer);          // Display the string
}



void keypad_init() {
    DDRA = 0xF0; // A0 to A3 input and A4 to A7 output 
    PORTA = 0xFF;
}
char keypad_scan() {
  unsigned char colloc,rowloc;
  do{
    PORTA=PORTA & 0x0F; // Clear A4 to A7
    colloc=PINA & 0x0F; // Read A0 to A3
  }while(colloc!=0x0F); // Wait until all keys released

  do{
    do{
      _delay_us(2);
      colloc=PINA & 0x0F; // Read A0 to A3
    }while(colloc!=0x0F); // Wait until all keys released
    _delay_us(2);
    colloc=PINA & 0x0F; // Read
  }while(colloc!=0x0F); // Wait until all keys released
  
  while(1){
    PORTA=0xEF;
    colloc=PINA & 0x0F; // Read
    if(colloc!=0x0F){
      rowloc=0;
      break;
    }
    PORTA=0xDF;
    colloc=PINA & 0x0F; // Read
    if(colloc!=0x0F){
      rowloc=1;
      break;
    }
    PORTA=0xBF;
    colloc=PINA & 0x0F; // Read
    if(colloc!=0x0F){
      rowloc=2;
      break;
    }
    PORTA=0x7F;
    colloc=PINA & 0x0F; // Read
    if(colloc!=0x0F){
      rowloc=3;
      break;
    }
  }
    if(colloc==0x0E){
      return keypad[rowloc][0];
    }
    if(colloc==0x0D){
      return keypad[rowloc][1];
    }
    if(colloc==0x0B){
      return keypad[rowloc][2];
    }
      return keypad[rowloc][3];
}

unsigned int Gcd(unsigned int First, unsigned int Second){
  while(Second!=0){
    unsigned int temp=Second;
    Second=First%Second;
    First=temp;
  }
  return First;
}

int main() {
    while (1) {
      keypad_init();
      LCD_Init();
      LCD_Clear();
      char key;
      unsigned int FirstNumber=0,SecondNumber=0;
      LCD_String("Num1:");
      while(1){
        key = keypad_scan();
        if (key>='0'&&key<='9'){
            FirstNumber=FirstNumber*10+(key-'0');
            LCD_Char(key);
          }
        else{
          if(key=='o'){
            break;
          }
        }
      }
      LCD_Clear();
      LCD_String("Num2:");
      while(1){
        key=keypad_scan();
        if(key>='0'&&key<='9'){
          SecondNumber=SecondNumber*10+(key-'0');
          LCD_Char(key);
        }
        else{
          if(key=='o'){
            break;
          }
        }
      }
      unsigned int gcd=Gcd(FirstNumber,SecondNumber);
      LCD_Clear();
      LCD_String("GCD: ");
      LCD_Number(gcd);
      _delay_ms(200);
    }
    return 0;
}
