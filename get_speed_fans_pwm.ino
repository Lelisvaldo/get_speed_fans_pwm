  
  #include <Arduino.h>
  #include <Wire.h>
  #include <MicroLCD.h>
  
  //LCD_SH1106 lcd; /* for SH1106 OLED module */
  LCD_SSD1306 lcd; /* for SSD1306 OLED module */
  
  const int fan_control_pin = 9; //Blue Wire on Fan (about 25kHz PWM)
  int pulseFan1 = 0, pulseFan2 = 0, pulseFan3 = 0;
  unsigned long start_time;
  int fanArray[] = {0,0,0};
   
  void setup() {
    Serial.begin(9600);
    lcd.begin();
    //TCCR1A = 0; // undo the configuration done by...
    //TCCR1B = 0; // ...the Arduino core library
    //TCNT1 = 0; // reset timer
    //TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11); //Undo default timers
    //TCCR1B = _BV(WGM13) | _BV(CS10); //for pins 9 & 10
    //ICR1 = 320; // PWM will be 0 to 320 instead of 0 to 255
    //pinMode( fan_control_pin, OUTPUT);
    //OCR1A = 0;  //set pwm to 0 out of 320 on pin 9
    //OCR1B = 0;  //set pwm to 0 out of 320 on pin 10
    attachInterrupt(digitalPinToInterrupt(2), pulseCounterFan1, RISING); //Yello Wire with 5V pullup
    attachInterrupt(digitalPinToInterrupt(4), pulseCounterFan2(), RISING); //Yello Wire with 5V pullup
    attachInterrupt(digitalPinToInterrupt(7), pulseCounterFan3(), RISING); //Yello Wire with 5V pullup
  }
  
  void loop() {
      pulseFan1 = 0;
      start_time = millis();
      while((millis() - start_time) < 1000){}
      lcd.clear();
      lcd.setFontSize(FONT_SIZE_MEDIUM);
      fanArray[0] = pulseFan1 * 30;  //60/2
      fanArray[1] = pulseFan2 * 30;  //60/2
      fanArray[2] = pulseFan3 * 30;  //60/2
//          Serial.print("FAN -> ");
//          Serial.print(fanArray[i]);
//          Serial.print(" RPM");
//          Serial.println();
          
          //FAN1
          lcd.setCursor(0, 0);
          lcd.print(fanArray[0]);
          lcd.setCursor(40, 0);
          lcd.print("RPM");
          //FAN2
          lcd.setCursor(0, 3);
          lcd.print(fanArray[1]);
          lcd.setCursor(40, 3);
          lcd.print("RPM");
          //FAN3
          lcd.setCursor(0, 6);
          lcd.print(fanArray[2]);
          lcd.setCursor(40, 6);
          lcd.print("RPM");
  }
  
  void pulseCounterFan1() {
    pulseFan1++;
  }
  int  pulseCounterFan2(){
    pulseFan2 = random(100);
    return pulseFan2;
  }
  int  pulseCounterFan3(){
    pulseFan3 = random(100);
    return pulseFan3;
  }
