
#define _LCD_TYPE 1

#include <LCD_1602_RUS_ALL.h>
#include <LiquidCrystal_I2C.h>

#include <Key.h>
#include <Keypad.h>



//Тип подключения дисплея: 1 - по шине I2C, 2 - десятиконтактное. 

LCD_1602_RUS <LiquidCrystal_I2C> lcd(0x27, 16, 2);      // Задаем адрес и размерность дисплея.  0x27 - Адрес может быть другой
                                 // Библиотека для клавиатуры

const byte ROWS = 4;                                    // 4 строки 
const byte COLS = 4;                                    // 4 ряда

char keys[ROWS][COLS] = {
  {'1','2','3','+'},  // A
  {'4','5','6','-'},  // B
  {'7','8','9','*'},  // C
  {'C','0','#','/'}   // D
};

byte rowPins[ROWS] = {12, 11, 10, 9};                   // Ардуино пины строк 
byte colPins[COLS] = {8, 7, 6, 5};                      // Ардуино пины столбцов

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 


 long Num1,Num2;
 float Number;
 char key,action;
 boolean result = false;
 
void setup() {
  Serial.begin(9600); 
  lcd.init();                                         // Инициализация lcd дисплея
  lcd.backlight();                                    // Включение подсветки дисплея
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(4,0);                                 // Устанавливаем курсор для 1 строки
  lcd.print("Простой");                              // Первая строка
  lcd.setCursor(2, 1);                                // Устанавливаем курсор для 2 строки
  lcd.print("Калькулятор");                           // Вторая строка

  delay(2000);                                       // Ждём 2 секунды и наслаждаемся надписью
  lcd.clear();                                       // Очищаем экран
}

void loop() {  
  key = kpd.getKey();                                   //сохранение значения нажатой клавиши в символьной переменной
  if (key!=NO_KEY)
  DetectButtons();
  if (result==true)
  CalculateResult();
  DisplayResult();   
}

void DetectButtons(){ 
     lcd.clear();                                     // Очищаем экран

     if (key == '1'){                                  // Если нажата цифра 1
      Serial.println ("Кнопка 1");                     // Выводим в монитор порта "Кнопка 1"
      if (Number==0)                                   // Если в первой переменной значение 0, то присваиваем ему значение 1
      Number=1;                                        // то присваиваем ему значение 1
      else                                             // в противном случае
      Number = (Number*10) + 1;                        // к старому значению прибавляем 1
    }
    
     if (key == '2'){                                  
      Serial.println ("Кнопка 2"); 
      if (Number==0)
      Number=2;
      else
      Number = (Number*10) + 2;                         
    }

     if (key == '3'){
      Serial.println ("Кнопка 3"); 
      if (Number==0)
      Number=3;
      else
      Number = (Number*10) + 3;                         
    }
            
     if (key == '4'){                                  
      Serial.println ("Button 4"); 
      if (Number==0)
      Number=4;
      else
      Number = (Number*10) + 4;                         
    }

     if (key == '5'){
      Serial.println ("Button 5"); 
      if (Number==0)
      Number=5;
      else
      Number = (Number*10) + 5;                         
    }
    
     if (key == '6'){
      Serial.println ("Button 6"); 
      if (Number==0)
      Number=6;
      else
      Number = (Number*10) + 6;                         
    }        
     if (key == '7'){                                  
      Serial.println ("Button 7");
      if (Number==0)
      Number=7;
      else
      Number = (Number*10) + 7;                         
    } 
    
     if (key == '8'){
      Serial.println ("Button 8"); 
      if (Number==0)
      Number=8;
      else
      Number = (Number*10) + 8;                         
    } 
     
     if (key == '9'){
      Serial.println ("Button 9");
      if (Number==0)
      Number=9;
      else
      Number = (Number*10) + 9;                         
    }

    if (key == '0'){
      Serial.println ("Кнопка 0");                     
      if (Number==0)
      Number=9;
      else
      Number = (Number*10) + 0;                         
    }
    
    if (key == '#'){
      Num2=Number;
      Serial.println ("СУММА: ");
      result = true;
    }
    
    if (key=='C'){                                    // Если нажата кнопка отмены
      Serial.println ("Отмена"); 
      Number = 0;                                     // Обнуляем значение переменной
      Num1 = 0;                                       // Обнуляем значение переменной
      Num2 = 0;                                       // Обнуляем значение переменной 
      result=false;
    }
    

    
  

    if (key == '+' || key == '-' || key == '*' || key == '/'){ // Проверяем какое действие выбрано
      Num1 = Number;    
      Number =0;
      if (key == '+'){
      Serial.println ("Сложение"); 
      action = '+';
      }
      if (key == '-'){
      Serial.println ("Вычитание"); 
      action = '-'; 
      }
      if (key == '*'){
      Serial.println ("Умножение"); 
      action = '*';
      }
      if (key == '/'){
      Serial.println ("Деление"); 
      action = '/';
      } 
    delay(100);
    }
  
}

void CalculateResult(){
  if (action=='+') {
    Number = Num1+Num2;
  }
  if (action=='-'){
    Number = Num1-Num2;
  }
  if (action=='*') {
    Number = Num1*Num2;
  }
  if (action=='/') {
    Number = (float)Num1 / (float)Num2;
  } 
}

void DisplayResult()
{
  lcd.setCursor(0, 0);                      // Устанавливаем курсор в 0 позицию
  lcd.print(String(Num1));                  // Выводим значение первой переменной 
  lcd.print(String(action));                // Выводим арифметическое действие 
  lcd.print(String(Num2));                  // Выводим значение второй переменной 
  if (result==true){                        // Выводим результат после знака =
    lcd.print("="); 
    lcd.print(String(Number));    
  }   
  lcd.setCursor(0, 1);                      // Вторая строка
  if (result!=true){ 
  lcd.print(String(Number,0));              // вводимое число(без нолей)
  }
  else{
    lcd.print(String("="));
    lcd.print(String(Number));                // Результат
  }
}
