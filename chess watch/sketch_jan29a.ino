#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Адрес дисплея, количество символов в строке, количество строк

const int buttonPlayer1 = 2; // Кнопка для управления таймером первого игрока
const int buttonPlayer2 = 3; // Кнопка для управления таймером второго игрока

bool player1Turn = true; // Первый игрок начинает
int player1Minutes = 5;  // Время игры для каждого игрока (в минутах)
int player1Seconds = 0;
int player2Minutes = 5;
int player2Seconds = 0;
bool gameStarted = false; // Флаг, указывающий на начало игры

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(buttonPlayer1, INPUT_PULLUP);
  pinMode(buttonPlayer2, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(buttonPlayer1), switchPlayer1, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPlayer2), switchPlayer2, FALLING);
}

void loop() {
  if (gameStarted) {
    updateTimer();
    displayTime();
  }
}

void switchPlayer1() {
  if (!gameStarted) {
    gameStarted = true;
  }
  player1Turn = !player1Turn;
}

void switchPlayer2() {
  if (!gameStarted) {
    gameStarted = true;
  }
  player1Turn = !player1Turn;
}

void updateTimer() {
  static unsigned long previousMillis = 0;
  const long interval = 1000; // 1 секунда
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    if (player1Turn) {
      if (player1Seconds > 0) {
        player1Seconds--;
      } else {
        if (player1Minutes > 0) {
          player1Minutes--;
          player1Seconds = 59;
        } else {
          gameStarted = false;
          displayWinner("Player 2");
        }
      }
    } else {
      if (player2Seconds > 0) {
        player2Seconds--;
      } else {
        if (player2Minutes > 0) {
          player2Minutes--;
          player2Seconds = 59;
        } else {
          gameStarted = false;
          displayWinner("Player 1");
        }
      }
    }
  }
}

void displayTime() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Player 1: ");
  lcd.print(player1Minutes);
  lcd.print(":");
  if (player1Seconds < 10) lcd.print("0");
  lcd.print(player1Seconds);
  
  lcd.setCursor(0, 1);
  lcd.print("Player 2: ");
  lcd.print(player2Minutes);
  lcd.print(":");
  if (player2Seconds < 10) lcd.print("0");
  lcd.print(player2Seconds);
}

void displayWinner(const char* winner) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(winner);
  lcd.print(" wins!");
  
  lcd.setCursor(0, 1);
  lcd.print("Game over");
}
