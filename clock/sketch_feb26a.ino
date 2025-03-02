#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Настройка пинов для DS1302
ThreeWire myWire(7, 6, 8);
RtcDS1302<ThreeWire> Rtc(myWire);

// Настройка дисплея
LiquidCrystal_I2C lcd(0x27, 16, 2);

void printDayOfWeek(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int K = year % 100;
    int J = year / 100;
    int h = (day + (13 * (month + 1)) / 5 + K + (K / 4) + (J / 4) + (5 * J)) % 7;
    int dow = ((h + 5) % 7) + 1; // Приводим к формату: 1 - Monday, ..., 7 - Sunday
    
    char* days[] = {"Mond", "Tuesd", "Wens", "Thusd", "Frid", "Satu", "Sund"};
    lcd.print(days[dow-1]);
}

void printMonth(int month) {
    char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    lcd.print(months[month-1]);
}


void setup() {
    Serial.begin(9600);
    lcd.init();            // Инициализация LCD
    lcd.backlight();       // Включение подсветки
    Rtc.Begin();           // Инициализация RTC

    // Проверка работы RTC
    if (!Rtc.GetIsRunning()) {
        Serial.println("RTC не работает, устанавливаю время!");
        Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
    }
}

void loop() {
    RtcDateTime now = Rtc.GetDateTime();

    int month = now.Month(), day = now.Day(), year = now.Year();
    lcd.setCursor(0, 0);
    if (month < 10) lcd.print("0");
    lcd.print(month);
    lcd.print(".");
    if (day < 10) lcd.print("0");
    lcd.print(day);
    lcd.print(".");
    lcd.print(year);
    lcd.setCursor(11, 0);
    printDayOfWeek(day, month, year);
    lcd.setCursor(0, 1);
    if (now.Hour() < 10) lcd.print("0");
    lcd.print(now.Hour());
    lcd.print(":");
    if (now.Minute() < 10) lcd.print("0");
    lcd.print(now.Minute());
    lcd.print(":");
    if (now.Second() < 10) lcd.print("0");
    lcd.print(now.Second());
    lcd.setCursor(9, 1);
    printMonth(month);

    delay(1000); 
}