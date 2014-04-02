#include <VGA.h>
#include "Numbers.h"

int NUMERI = 139;

int width = 40;
int height = 25;

uint32_t trueRandom()
{
  static bool enabled = false;
  if (!enabled) {
    pmc_enable_periph_clk(ID_TRNG);
    TRNG->TRNG_IDR = 0xFFFFFFFF;
    TRNG->TRNG_CR = TRNG_CR_KEY(0x524e47) | TRNG_CR_ENABLE;
    enabled = true;
  }

  while (! (TRNG->TRNG_ISR & TRNG_ISR_DATRDY))
    ;
  return TRNG->TRNG_ODATA;
}

int estrai() {
  uint32_t mask = -1;
  while ((mask >> 1) > NUMERI)
    mask >>= 1;
  //Serial.println(mask);
  uint32_t N;
  do {
    N = trueRandom() & mask;
  } while (N == 0 || N > NUMERI);
  return N;
}

void setup() {
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);
  
  Serial.begin(9600);
  VGA.begin(320, 240, VGA_COLOUR);
  mainScreen();
}

void printCentered(String title, int row) {
  VGA.moveCursor((width - title.length()) / 2, row);
  VGA.print(title);
}

int waitChar() {
  int c;
  while (Serial.available() == 0)
    if (digitalRead(12)==LOW)
      return -1;
  return Serial.read();
}

//int num() {
//  int n = waitChar() - '0';
//  Serial.println(n);
//  return n;
//}

void mainScreen() {
  VGA.clear();
  printCentered("La Dea Bendata.", 4);
  printCentered("I'm going to choose a", 7);
  printCentered("random number between", 9);
  printNumber(140, 88, 4, 7, 1);
  printCentered("and", 16);
  printNumber(112, 144, 4, 7, NUMERI);
}

void readyScreen() {
  VGA.clear();
  printCentered("Ready?", 9);
}

void loop() {
  if (digitalRead(12) == LOW) {
    readyScreen();
    delay(4000);
    lottery();
  }
  
  int c = waitChar();
  if (c == '0')
    mainScreen();
  if (c == '1')
    readyScreen();
  if (c == '2')
    lottery();

  //  if (c == 'c')
  //    VGA.clear();
  //  if (c == 'l')
  //    line(num(), num(), num(), num());
  //  if (c == 'b')
  //    bezier(num(), num(), num(), num(), num(), num());
  //  if (c == 'C')
  //    circle(num(), num(), num());
}

void lottery() {
  int i;
  VGA.clear(0);
  for (i = 0; i < 500; i++) {
    int n = estrai();
    VGA.waitSync();
    printNumber(random(380) - 60, random(280) - 40, 4, random(255), n);
  }

  int winner = estrai();
  int x = 140;
  if (winner > 100)
    x -= 14;
  if (winner > 10)
    x -= 14;

  int color = random(255);
  for (int a = 0; a < 360; a++) {
    if (a % 10 == 0)
      color = random(255);

    int x2 = 160 + sin(a * PI / 180.0) * 300;
    int y2 = 160 + cos(a * PI / 180.0) * 300;

    VGA.drawLine(160, 120, x2, y2, color);
    printNumber(x, 100, 4, random(255), winner);
  }

  for (int dx = -2; dx < 3; dx++)
    for (int dy = -2; dy < 3; dy++)
      printNumber(x + dx, 100 + dy, 4, 0, winner);
  printNumber(x, 100, 4, 255, winner);
}


