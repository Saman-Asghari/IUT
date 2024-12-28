#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include<avr/interrupt.h>
#include<math.h>
#include<avr/eeprom.h>
#include<string.h>

//#define F_CPU 4000000UL  // Define CPU frequency
#define LCD_PORT PORTC     // LCD data lines connected to PORTC
#define LCD_DDR  DDRC      // Data direction register for PORTC
#define LCD_RS   0       // Register Select pin connected to PD0
#define LCD_RW   1       // Read/Write pin connected to PD1
#define LCD_EN   2       // Enable pin connected to PD2
#define LCD_CTRL PORTD     // Control lines connected to PORTD
#define LCD_CTRL_DDR DDRD  // Data direction register for PORTD
#define BUZZER_PORT PORTA
#define BUZZER_DDR  DDRA
#define BUZZER_PIN  PA7
#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)
uint16_t EEPROM_START_ADDRESS = 0; // Starting EEPROM address
#define US_PORT PORTA
#define US_DDR  DDRA
#define US_PIN  PINA
#define US_TRIG_POS PA1  
#define US_ECHO_POS PA2
#define US_ERROR -1
#define US_NO_OBSTACLE -2


int StudentCount = 0;
long int StudentCodes[100];


char keypad[4][3] = {
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'},
    {'o', '0', '='}
};

int MenuChoice=0;

void HCSR04Init() {
    US_DDR |= (1 << US_TRIG_POS); // Trigger pin as output
    US_DDR &= ~(1 << US_ECHO_POS); // Echo pin as input
}

void HCSR04Trigger() {
    US_PORT |= (1 << US_TRIG_POS); // Set trigger pin high
    _delay_us(15);                  // Wait for 15 microseconds
    US_PORT &= ~(1 << US_TRIG_POS); // Set trigger pin low
}

uint16_t GetPulseWidth() {
    uint32_t i, result;

    // Wait for rising edge on Echo pin
    for (i = 0; i < 600000; i++) {
        if (!(US_PIN & (1 << US_ECHO_POS)))
            continue;
        else
            break;
    }

    if (i == 600000)
        return US_ERROR; // Timeout error if no rising edge detected

    // Start timer with prescaler 8
    TCCR1A = 0x00;
    TCCR1B = (1 << CS11);
    TCNT1 = 0x00; // Reset timer

    // Wait for falling edge on Echo pin
    for (i = 0; i < 600000; i++) {
        if (!(US_PIN & (1 << US_ECHO_POS)))
            break;  // Falling edge detected
        if (TCNT1 > 60000)
            return US_NO_OBSTACLE; // No obstacle in range
    }

    result = TCNT1; // Capture timer value
    TCCR1B = 0x00; // Stop timer

    if (result > 60000)
        return US_NO_OBSTACLE;
    else
        return (result >> 1); // Return the measured pulse width
}


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
      DDRB = 0xF0; // A0 to A3 input and A4 to A7 output 
      PORTB = 0xFF;
  }
  char keypad_scan() {
    unsigned char colloc,rowloc;
    do{
      PORTB=PORTB & 0x0F; // Clear A4 to A7
      colloc=PINB & 0x0F; // Read A0 to A3
    }while(colloc!=0x0F); // Wait until all keys released

    do{
      do{
        _delay_us(2);
        colloc=PINB & 0x0F; // Read A0 to A3
      }while(colloc!=0x0F); // Wait until all keys released
      _delay_us(2);
      colloc=PINB & 0x0F; // Read
    }while(colloc!=0x0F); // Wait until all keys released
    
    while(1){
      PORTB=0xEF;
      colloc=PINB & 0x0F; // Read
      if(colloc!=0x0F){
        rowloc=0;
        break;
      }
      PORTB=0xDF;
      colloc=PINB & 0x0F; // Read
      if(colloc!=0x0F){
        rowloc=1;
        break;
      }
      PORTB=0xBF;
      colloc=PINB & 0x0F; // Read
      if(colloc!=0x0F){
        rowloc=2;
        break;
      }
      PORTB=0x7F;
      colloc=PINB & 0x0F; // Read
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


void saveStudentCodesToEEPROM() {
    for (uint16_t i = 0; i < 100; i++) {
        eeprom_write_dword((uint32_t *)(EEPROM_START_ADDRESS + i * sizeof(long int)), StudentCodes[i]);
    }
}

void loadStudentCodesFromEEPROM() {
  EEPROM_START_ADDRESS =0;
    for (uint16_t i = 0; i < 100; i++) {
        StudentCodes[i] = eeprom_read_dword((const uint32_t *)(EEPROM_START_ADDRESS + i * sizeof(long int)));
    }
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
  while(1){
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
    else{
      saveStudentCodesToEEPROM();
      return;
    }
  }
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



void USART_init(unsigned int ubrr) {
    UBRRL = (unsigned char)ubrr;
    UBRRH = (unsigned char)(ubrr >> 8);
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << UCSZ1) | (1 << UCSZ0); // Set UCSZ1 and UCSZ0 for 8-bit data
}

void USART_Transmit(unsigned char data)
{
    while(!(UCSRA &(1<<UDRE)));
    UDR = data; 
}
void ADC_init() {
  ADMUX = (1 << REFS0);              // ولتاژ مرجع AVCC
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // فعال‌سازی ADC و Prescaler = 64
}

int ADC_read(int channel) {
               // انتظار برای پایان تبدیل
  return ADC;       
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


void TemperatureMonitoring(){
  //Temperature Monitoring Code
  LCD_Clear();
  char key;
  int temp=0;
  ADMUX=0xE0;
  ADCSRA=0x87;
  _delay_ms(10);                         
  while(1){
    ADCSRA |= (1 << ADSC);                    
    while ((ADCSRA & (1 << ADIF))==0);
    if(ADCH != temp || 1){
      temp=ADCH;
      LCD_Number(temp);
      LCD_SetCursor(1,0);
      LCD_String("1.continue or 2.exit");
      key=keypad_scan();
      if(key=='2'){
        return ;
      }                                     
    }
    LCD_Clear();
  }
}

void longToString(long int num, char *str) {
    int i = 0;
    int isNegative = 0;

    // Handle negative numbers
    if (num < 0) {
        isNegative = 1;
        num = -num; // Make the number positive
    }

    // Extract digits in reverse order
    do {
        str[i++] = (num % 10) + '0'; // Convert digit to character
        num /= 10;
    } while (num > 0);

    // Add '-' for negative numbers
    if (isNegative) {
        str[i++] = '-';
    }

    // Add null terminator to the end of the string
    str[i] = '\0';

    // Reverse the string to correct the digit order
    int start = 0, end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void USART_send_Long_array(long int arr[], int size){
  char buffer[10];
  for(int i=0;i<size;i++){
    if(arr[i]==0) 
      continue;
    longToString(arr[i], buffer);
    LCD_Clear();
    LCD_String("Student Code: ");
    LCD_SetCursor(1,0);
    LCD_String(buffer);
    for(int j=0;j<8;j++){
      USART_Transmit(buffer[j]);
      _delay_ms(100);
    }
    USART_Transmit('\r');
    _delay_ms(100);
  }
}

void retrieveStudentData(){
  //Retrieve Student Data Code
  loadStudentCodesFromEEPROM();
  for(int i=0;i<5;i++){
    LCD_Clear();
    LCD_SetCursor(0,0);
    LCD_Number(StudentCodes[i]);
    _delay_ms(500);
  }
  USART_send_Long_array(StudentCodes,100);
}

void TrafficMonitoring(){
  uint16_t pulseWidth;    // Pulse width from echo
  int distance;           // Calculated distance
  int previous_count = -1;
  while(1){
    _delay_ms(100);
    HCSR04Trigger();
    pulseWidth = GetPulseWidth();
    if(pulseWidth==US_ERROR){
      LCD_Clear();
      LCD_String("Error: Echo timeout");
      _delay_ms(300);
    }
    else if(pulseWidth ==US_NO_OBSTACLE){
      LCD_Clear();
      LCD_String("No Obstacle Detected");
      _delay_ms(300);
    }
    else{
          distance = (int)((pulseWidth * 0.034 / 2) + 0.5);
          LCD_Clear();
          LCD_Number(distance);
    }
  }
}

int main() {
    while (1) {
      DDRA=0xFF; // All pins of PORTB as output
      //PORTA=0xF0; // All pins of PORTB as input with pull-up resistors
      //DDRA &= ~(1 << PA5); // تنظیم PA5 به عنوان ورودی (ADC5)
      //PORTA = 0x00; // خاموش کردن تمامی COMها
      DDRA=0x00;
      USART_init(0x33); // Initialize USART with the correct baud rate
      buzzer_init();
      HCSR04Init();
      ADC_init();
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
      if(MenuChoice==4){
        //Tempreture Monitoring
        //LCD_Clear();
       // LCD_SetCursor(0,0);
        //LCD_String("Temperature Monitoring");
        TemperatureMonitoring();
      }
      if(MenuChoice==5){
        //function to display in virtual terminal
        retrieveStudentData();
      }
      if(MenuChoice==6){
        TrafficMonitoring();
      }
    }
    return 0;
}
