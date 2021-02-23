#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans12pt7b.h>

#define SCREEN_WIDTH 128 // largura da tela OLED, em pixels
#define SCREEN_HEIGHT 32 // altura da tela OLED, em pixels

// Declaração para um monitor SSD1306 conectado ao I2C (pinos SDA, SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const unsigned char PROGMEM fan0 [] = {0x03, 0xC0, 0x07, 0xC0, 0x27, 0x9C, 0x67, 0x7E, 0x77, 0xFE, 0xFE, 0x7F, 0xFD, 0xB0, 0x7D, 0xDC, 0x3B, 0xDE, 0x8C, 0xBF, 0xFF, 0xEF, 0x7E, 0xEE, 0x7D, 0xE6, 0x11, 0xE4, 0x03, 0xE0, 0x03, 0xC0};

const int fan_control_pin = 9; //Blue Wire on Fan (about 25kHz PWM)
int pulseFan1 = 0, pulseFan2 = 0, pulseFan3 = 0;
unsigned long start_time;
int fanArray[] = {0, 0, 0};

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), pulseCounterFan1, RISING); //Yello Wire with 5V pullup
  attachInterrupt(digitalPinToInterrupt(4), pulseCounterFan2(), RISING); //Yello Wire with 5V pullup
  attachInterrupt(digitalPinToInterrupt(7), pulseCounterFan3(), RISING); //Yello Wire with 5V pullup

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Endereço 0x3D para 128x64
    Serial.println(F("Falha na alocação SSD1306"));
    for (;;);
  }
  display.clearDisplay();
  //display.setTextSize(1);
  display.setFont(&FreeSans12pt7b);
  display.setTextColor(WHITE);
}

void loop() {
  pulseFan1 = 0;
  start_time = millis();
  while ((millis() - start_time) < 900) {}
  fanArray[0] = pulseFan1 * 30;  //60/2
  fanArray[1] = pulseFan2 * 30;  //60/2
  fanArray[2] = pulseFan3 * 30;  //60/2
  //    //Serial.print("FAN -> ");
  //    //Serial.print(fanArray[i]);
  //    //Serial.print(" RPM");
  //    //Serial.println();

  //FAN1
  //iconFan1(0, 0, 0);
  display.drawBitmap(0, 0, fan0, 16, 16, 1);
  display.display();
  display.setCursor(20, 16);
  display.println(fanArray[0]);
  display.display();
  display.setCursor(70, 16);
  display.println(" RPM");
  display.display();
  display.clearDisplay();

  //FAN2
  //iconFan1(0, 10, 0);
  //  display.drawBitmap(0, 10, fan0, 8, 8, 1);
  //  display.display();
  //  display.setCursor(15,10);
  //  display.println(fanArray[1]);
  //  display.display();
  //  display.setCursor(40,10);
  //  display.println(" RPM");
  //  display.display();


  //FAN3
  //iconFan1(0, 20, 0);
  //  display.drawBitmap(0, 20, fan0, 8, 8, 1);
  //  display.display();
  //  display.setCursor(15,20);
  //  display.println(fanArray[2]);
  //  display.display();
  //  display.setCursor(40, 20);
  //  display.println(" RPM");
  //  display.display();

  display.clearDisplay();
}

void pulseCounterFan1() {
  pulseFan1++;
}
int  pulseCounterFan2() {
  pulseFan2 = random(100);
  return pulseFan2;
}
int  pulseCounterFan3() {
  pulseFan3 = random(100);
  return pulseFan3;
}
