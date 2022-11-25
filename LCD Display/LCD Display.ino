#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define random_analog 0
#define size 10
#define delay_sec 15

String train[size] = {"SHATABDI", "AVANTIKA", "SHIPRA", "GKP PUNE", "BL PURI", "NAVYUG", "GKP YPR", "TULSI", "PUSHPAK", "KONGU"};
String str = " ";
int random_hour[size], random_min[size], plt[size];
int cp;
bool first, blink;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  randomSeed(analogRead(random_analog));
	lcd.begin();
	lcd.backlight();

  generate_rand();
  shuffle();
  start_screen();

  first = true;
  blink = true;

  for (int i = 0; i < 20; i++){
    str += " ";
  }
}

void loop()
{
  if (cp>6){
    cp = 0;
    if (!first){
      generate_rand();
      shuffle();
      start_screen();
    }
  } else {
    if (!first){
      change_screen();
    }
    first = false;
  }
  
  for (int i = 0; i < delay_sec*2; i++){
    delay(600);
    if (blink) {
      for (int j = 1; j < 4; j++){
        lcd.setCursor(12, j);
        lcd.print(" ");
      }
      blink = false;
    }
    else {
      for (int j = 1; j < 4; j++){
        lcd.setCursor(12, j);
        lcd.print(":");
      }
      blink = true;
    }
  }
}


void generate_rand()
{
  for (int i = 0; i < size; i++){
    random_hour[i] = random(random(1, 12), 24);
    random_min[i] = random(random(1, 30), 60);
    plt[i] = random(1, 6);
  }

  qsort(random_hour, size, sizeof(random_hour[0]), sort_asc);
}


void start_screen()
{
  lcd.setCursor(0, 0);
  lcd.print("TRAIN");
  lcd.setCursor(10, 0);
  lcd.print("TIME");
  lcd.setCursor(17, 0);
  lcd.print("PLT");

  for (int i = 0; i < 20; i++){
    for (int j = 1; j < 4; j++){
      lcd.setCursor(0, j);
      lcd.print(str.substring(0, i+1));
    }
    delay(1);

    if (i > 18){
      for (int j = 0; j < 8; j++){
        for (int k = 1; k < 4; k++){
          lcd.setCursor(0, k);
          lcd.print(train[(k-1)].substring(0, j+1));
        }
        delay(50);
      }

      delay(50);
      for (int j = 0; j < 3; j++){
        lcd.setCursor(10, j+1);
        if (random_hour[j] < 10) {
          lcd.print(0);
          lcd.setCursor(11, 1+j);
          lcd.print(random_hour[j]);
        } else {
          lcd.print(random_hour[j]);
        }
      }
    
      delay(50);
      for (int j = 0; j < 3; j++){  
        lcd.setCursor(12, 1+j);
        lcd.print(":");
      }

      delay(50);
      for (int j = 0; j < 3; j++){
        if (random_hour[j] == random_hour[j+1]){
          qsort(random_min, size, sizeof(random_min[0]), sort_asc);
        } else {
          if (j == 2) shuffle_int();
        }

        lcd.setCursor(13, j+1);
        if (random_min[j] < 10) {
          lcd.print(0);
          lcd.setCursor(14, 1+j);
          lcd.print(random_min[j]);
        } else {
          lcd.print(random_min[j]);
        }
      }

      delay(50);
      for (int j = 0; j < 3; j++){  
        lcd.setCursor(17, j+1);
        lcd.print(0);
        lcd.setCursor(18, j+1);
        lcd.print(plt[j]);
      }
    }
  }

  cp = 3;
}


void change_screen()
{
  if (cp<7) {
    int a = 3;
    if ((size-cp-1)<a) a = (size-cp-1);

    for (int i = 0; i < 20; i++){
      for (int j = 1; j < 4; j++){
        lcd.setCursor(0, j);
        lcd.print(str.substring(0, i+1));
      }
      delay(1);

      if (i > 18){
        for (int j = 0; j < 8; j++){
          for (int k = 1; k < 4; k++){
            lcd.setCursor(0, k);
            lcd.print(train[cp+k-1].substring(0, j+1));
          }
          delay(50);
        }

        delay(50);
        for (int j = 0; j < 3; j++){
          lcd.setCursor(10, j+1);
          if (random_hour[cp+j] < 10) {
            lcd.print(0);
            lcd.setCursor(11, 1+j);
            lcd.print(random_hour[cp+j]);
          } else {
            lcd.print(random_hour[cp+j]);
          }
        }
      
        delay(50);
        for (int j = 0; j < 3; j++){  
          lcd.setCursor(12, 1+j);
          lcd.print(":");
        }

        delay(50);
        for (int j = 0; j < 3; j++){
          if (random_hour[cp+j] == random_hour[cp+j+1]){
            qsort(random_min, size, sizeof(random_min[0]), sort_asc);
          } else {
            if (j == 2) shuffle_int();
          }

          lcd.setCursor(13, j+1);
          if (random_min[cp+j] < 10) {
            lcd.print(0);
            lcd.setCursor(14, 1+j);
            lcd.print(random_min[cp+j]);
          } else {
            lcd.print(random_min[cp+j]);
          }
        }

        delay(50);
        for (int j = 0; j < 3; j++){  
          lcd.setCursor(17, j+1);
          lcd.print(0);
          lcd.setCursor(18, j+1);
          lcd.print(plt[cp+j]);
        }
      }
    }
    cp += 3;
  }
}


void shuffle()
{
  for (int i = 0; i < size; i++){
    int c = random(10);
    String a = train[i];
    String b = train[c];
    train[i] = b;
    train[c] = a;
  }
}


void shuffle_int()
{
  for (int i = 0; i < size; i++){
    int c = random(10);
    int a = random_min[i];
    int b = random_min[c];
    random_min[i] = b;
    random_min[c] = a;
  }
}


int sort_asc(const void *a, const void *b)
{
  return *((int *)a) - *((int *)b);
}