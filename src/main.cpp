#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

const int ledPin = 32;
int ledState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis = 0;
unsigned long currentInterval = 0;
unsigned long ledBlinkOnInterval = 100;
unsigned long ledBlinkOffInterval = 2000;
#define LED_ON_STATE LOW
#define LED_OFF_STATE HIGH

void blinkLedTask(void);

//float floatVal = 0.00;
//char floatValStr[6];

void oled_LCD_write12digitDec(uint32_t value, uint8_t maxDigits, uint8_t dotPos);

void setup() {
    // put your setup code here, to run once:
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

     // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    display.display();
    delay(2000);
    display.clearDisplay();
    display.display();

    
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(2);
    //oled_LCD_write12digitDec((analogRead(PA0)*5)/4096, 4, 1);
    //display.print(floatValStr);
    /*display.print(".");
    display.print(0);
    display.print(0);
    display.print(0);*/
    

    pinMode(ledPin, OUTPUT);
    analogReadResolution(12);
}

#define DIGITS 3
#define DECIMAL_PLACE (DIGITS-1)
#define TEXT_WIDTH ((DIGITS+2)*12)

void loop() {
    // put your main code here, to run repeatedly:
    //floatVal = (analogRead(10)*5)/4096;
    //ftos(floatValStr, 1, 3, floatVal);
    /*
    display.setCursor(0,0);
    oled_LCD_write12digitDec((analogRead(PA0)*5000)/40290, DIGITS, DECIMAL_PLACE);
    display.setCursor(TEXT_WIDTH,0);
    oled_LCD_write12digitDec((analogRead(PA1)*5000)/40290, DIGITS, DECIMAL_PLACE);

    display.setCursor(TEXT_WIDTH*2,0);
    oled_LCD_write12digitDec((analogRead(PA2)*5000)/40290, DIGITS, DECIMAL_PLACE);
    display.setCursor(TEXT_WIDTH*3,0);
    oled_LCD_write12digitDec((analogRead(PA3)*5000)/40290, DIGITS, DECIMAL_PLACE);

    display.setCursor(0,8);
    oled_LCD_write12digitDec((analogRead(PA4)*5000)/40290, DIGITS, DECIMAL_PLACE);
    display.setCursor(TEXT_WIDTH,16);
    oled_LCD_write12digitDec((analogRead(PA5)*5000)/40290, DIGITS, DECIMAL_PLACE);

    display.setCursor(TEXT_WIDTH*2,16);
    oled_LCD_write12digitDec((analogRead(PA6)*5000)/40290, DIGITS, DECIMAL_PLACE);
    display.setCursor(TEXT_WIDTH*3,16);
    oled_LCD_write12digitDec((analogRead(PA7)*5000)/40290, DIGITS, DECIMAL_PLACE);*/

    display.setCursor(0,0);
    oled_LCD_write12digitDec((analogRead(PA0)*5000)/40290, DIGITS, DECIMAL_PLACE);
    display.setCursor(TEXT_WIDTH,0);
    oled_LCD_write12digitDec((analogRead(PA4)*5000)/40290, DIGITS, DECIMAL_PLACE);

    display.setCursor(0,16);
    oled_LCD_write12digitDec((analogRead(PA1)*5000)/40290, DIGITS, DECIMAL_PLACE);
    display.setCursor(TEXT_WIDTH,16);
    oled_LCD_write12digitDec((analogRead(PA5)*5000)/40290, DIGITS, DECIMAL_PLACE);

    display.setCursor(0,32);
    oled_LCD_write12digitDec((analogRead(PA2)*5000)/40290, DIGITS, DECIMAL_PLACE);
    display.setCursor(TEXT_WIDTH,32);
    oled_LCD_write12digitDec((analogRead(PA6)*5000)/40290, DIGITS, DECIMAL_PLACE);
    
    display.setCursor(0,48);
    oled_LCD_write12digitDec((analogRead(PA3)*5000)/40290, DIGITS, DECIMAL_PLACE);
    display.setCursor(TEXT_WIDTH,48);
    oled_LCD_write12digitDec((analogRead(PA7)*5000)/40290, DIGITS, DECIMAL_PLACE);
    display.display();

    //display.print(floatValStr);

    blinkLedTask();
}

void oled_LCD_write12digitDec(uint32_t value, uint8_t maxDigits, uint8_t dotPos = 0) {
    uint32_t rest = value;
    uint32_t curr = rest / 100000000000;
    //display.clearDisplay();
    if (maxDigits >= 12)
        display.print(curr);
    rest = rest % 100000000000;
    curr = rest / 10000000000;
    if (maxDigits >= 11)
        display.print(curr);
    if (dotPos == 10) display.print('.');
    rest = rest % 10000000000;
    curr = rest / 1000000000;
    if (maxDigits >= 10)
        display.print(curr);
    if (dotPos == 9) display.print('.');
    rest = rest % 1000000000;
    curr = rest / 100000000;
    if (maxDigits >= 9)
        display.print(curr);
    if (dotPos == 8) display.print('.');
    rest = rest % 100000000;
    curr = rest / 10000000;
    if (maxDigits >= 8)
        display.print(curr);
    if (dotPos == 7) display.print('.');
    rest = rest % 10000000;
    curr = rest / 1000000;
    if (maxDigits >= 7)
        display.print(curr);
    if (dotPos == 6) display.print('.');
    rest = rest % 1000000;
    curr = rest / 100000;
    if (maxDigits >= 6)
        display.print(curr);
    if (dotPos == 5) display.print('.');
    rest = rest % 100000;
    curr = rest / 10000;
    if (maxDigits >= 5)
        display.print(curr);
    if (dotPos == 4) display.print('.');
    rest = rest % 10000;
    curr = rest / 1000;
    if (maxDigits >= 4)
        display.print(curr);
    if (dotPos == 3) display.print('.');
    rest = rest % 1000;
    curr = rest / 100;
    if (maxDigits >= 3)
        display.print(curr);
    if (dotPos == 2) display.print('.');
    rest = rest % 100;
    curr = rest / 10;
    if (maxDigits >= 2)
        display.print(curr);
    if (dotPos == 1) display.print('.');
    rest = rest % 10;
    if (maxDigits >= 1)
        display.print(rest, 10);

}

void blinkLedTask(void)
{
    currentMillis = millis();
    currentInterval = currentMillis - previousMillis;
    
    if (ledState == LED_OFF_STATE)
    {
        if (currentInterval > ledBlinkOffInterval)
        {
            previousMillis = currentMillis;
            ledState = LED_ON_STATE;
            digitalWrite(ledPin, LED_ON_STATE);
        }
    }
    else
    {
        if (currentInterval > ledBlinkOnInterval)
        {
            previousMillis = currentMillis;
            ledState = LED_OFF_STATE;
            digitalWrite(ledPin, LED_OFF_STATE);
        }
    }
}