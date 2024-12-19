#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include<avr/interrupt.h>
#include<math.h>


#define LCD_PORT PORTC     // LCD data lines connected to PORTC
#define LCD_DDR  DDRC      // Data direction register for PORTC
#define LCD_RS   0       // Register Select pin connected to PD0
#define LCD_RW   1       // Read/Write pin connected to PD1
#define LCD_EN   2       // Enable pin connected to PD2
#define LCD_CTRL PORTD     // Control lines connected to PORTD
#define LCD_CTRL_DDR DDRD  // Data direction register for PORTD
#define BUZZER_PORT PORTB
#define BUZZER_DDR  DDRB
#define BUZZER_PIN  PB7


int StudentCount = 0;
long int StudentCodes[100];


char keypad[4][4] = {
    {'7', '8', '9','/'},
    {'4', '5', '6','*'},
    {'1', '2', '3','-'},
    {'o', '0', '=','+'}
};

int MenuChoice=0;


void LCD_EnablePulse() {
    LCD_CTRL |= (1 << LCD_EN);  // Enable pin high
    _delay_us(2000);              // Short delay
    LCD_CTRL &= ~(1 << LCD_EN); // Enable pin low
    _delay_ms(2);     // Wait for command execution
}

void LCD_Command(unsigned char cmd) {
    LCD_PORT = cmd;              // Place command on data lines
    LCD_CTRL &= ~(1 << LCD_RS);  // RS = 0 for command
    LCD_CTRL &= ~(1 << LCD_RW);  // RW = 0 for write
    LCD_EnablePulse();
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address;

    if (row == 0) {
        address = col;           // First line starts at 0x00
    } else if (row == 1) {
        address = 0x40 + col;    // Second line starts at 0x40
    }

    LCD_Command(0x80 | address); // Set DDRAM address command
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


void num_to_string(long int num, char* buffer) {
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

void LCD_Number(long int num) {
    char buffer[10];
    num_to_string(num,buffer);      // Convert number to string (base 10)
    LCD_String(buffer);          // Display the string
}

void buzzer_init() {
    BUZZER_DDR |= (1 << BUZZER_PIN);  // Set buzzer pin as output
}

void buzzer_on() {
    BUZZER_PORT |= (1 << BUZZER_PIN); // Set buzzer pin HIGH
}

void buzzer_off() {
    BUZZER_PORT &= ~(1 << BUZZER_PIN); // Set buzzer pin LOW
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

void AttendanceManagement(){
  char key;
  long int tmpStudentCode=0,StudentCode=0;
  LCD_Clear();
  LCD_SetCursor(0,0);
  LCD_String("Enter Student Code:");
  LCD_SetCursor(1,0);
  while (1)
  {
    key=keypad_scan();
    if(key!='o'){
      tmpStudentCode=tmpStudentCode*10 + (key-'0');
      LCD_Char(key);
    }
    else{
      break;
    }
  }
  _delay_ms(200);
  if(FormatChecker(tmpStudentCode)){
    StudentCode=tmpStudentCode;
    StudentCodes[StudentCount]=StudentCode;
    StudentCount++;
    LCD_Clear();
    LCD_SetCursor(0,0);
    LCD_String("Student Code Accepted!");
    return;
  }
  else{
    LCD_Clear();
    LCD_SetCursor(0,0);
    LCD_String("Student Code Not Accepted!");
    buzzer_on();
    _delay_ms(200);
    buzzer_off();
    return;
  }
}


void AttendanceInitialization(){
  char key;
  LCD_Clear();
  LCD_SetCursor(0,0);
  LCD_String("1.Submit Student Code");
  LCD_SetCursor(1,0);
  LCD_String("2.Exit");
  key=keypad_scan();
  if (key=='1')
  {
    AttendanceManagement();
  }
  return;
  
}

char FirstPage(){
  LCD_Clear();
  LCD_SetCursor(0,0);
  LCD_String("1.Attendance Initialization");
  LCD_SetCursor(1,0);
  LCD_String("2.Student Management");
}

void SecondPage(){
  LCD_Clear();
  LCD_SetCursor(0,0);
  LCD_String("3.View Present Students");
  LCD_SetCursor(1,0);
  LCD_String("4.Temperature Monitoring");
}

void ThirdPage(){
  LCD_Clear();
  LCD_SetCursor(0,0);
  LCD_String("5.Retrieve Student Data");
  LCD_SetCursor(1,0);
  LCD_String("6.Traffic Monitoring");
}

void ShowMenu(){
  char key;
  uint8_t Scroller=0;
  FirstPage();
  while(1){
    key=keypad_scan();
    if(key=='0'){
      Scroller=(Scroller+1)%3;
    }
    else if(key=='8'){
      Scroller=(Scroller-1)%3;
    }
    else{
      MenuChoice=key-'0';
      break;
    }
    if(Scroller==0){
      FirstPage();
    }
    else if(Scroller==1){
      SecondPage();
    }
    else if(Scroller==2){
      ThirdPage();
    }
  }
  

}

int FormatChecker(long int StudentNumber){
  if(StudentNumber<=40100000||StudentNumber>=40200000){
    return 0; //Invalid format
  }
  return 1; //Valid format;
}

void StudentManagement(){
  char key;
  long int StudentNumber=0;
  LCD_Clear();
  LCD_String("Enter Student Code:");
  LCD_SetCursor(1,0);
  LCD_String("Student Number: ");
  while(1){
    key=keypad_scan();
    if(key!='o'){
      StudentNumber=StudentNumber*10 + (key-'0');
      LCD_Char(key);
    }
    else{
      break;
    }
  }
  for(int i=0;i<StudentCount;i++){
    if(StudentNumber==StudentCodes[i]){
      LCD_Clear();
      LCD_String("Student Found!");
      _delay_ms(100);
      return;
    }
  }
  LCD_Clear();
  LCD_String("Student Not Found!");
  _delay_ms(100);
  return;
}

void ViewPresentStudents(){
  //View Present Students Code
  int Scroller=0;
  char key;
  LCD_Clear();
  LCD_SetCursor(0,0);
  LCD_String("Present Students:");
  LCD_Number(StudentCount);
  _delay_ms(100);
  LCD_Clear();
  LCD_SetCursor(0,0);
  LCD_Number(StudentCodes[Scroller*2]);
  LCD_SetCursor(1,0);
  LCD_Number(StudentCodes[Scroller*2+1]);
  while(1){
    key=keypad_scan();
    if(key=='0'){
      Scroller=(Scroller+1);
    }
    else if(key=='8'){
      Scroller=(Scroller-1);
    }
    else if(key=='o'){
      break;
    }
    LCD_Clear();
    if(Scroller*2<=StudentCount){
      LCD_SetCursor(0,0);
      LCD_Number(StudentCodes[Scroller*2]);
      LCD_SetCursor(1,0);
      LCD_Number(StudentCodes[Scroller*2+1]);
    }
    else{
      if(StudentCount%2==0){
        continue;
      }
      else{
      LCD_SetCursor(0,0);
      LCD_Number(StudentCodes[StudentCount-1]);
      }
    }

  }
}

int main() {
    while (1) {
      buzzer_init();
      keypad_init();
      LCD_Init();
      LCD_Clear();
      ShowMenu();
      if(MenuChoice==1){
        AttendanceInitialization();
      }
      if(MenuChoice==2){
        StudentManagement();
      }
      if(MenuChoice==3){
        //View Present Students
        ViewPresentStudents();
      }
    }
    return 0;
}
