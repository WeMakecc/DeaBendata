#include <VGA.h>

int cx, cy, sz, cl;

void line(int x1, int y1, int x2, int y2) {
  VGA.drawLine(cx + x1 * sz, cy + y1 * sz, cx + x2 * sz, cy + y2 * sz, cl);
}

void bezier(int x0, int y0, int x1, int y1, int x2, int y2) {
  VGA.drawQuadBezier(cx + x0 * sz, cy + y0 * sz, cx + x1 * sz, cy + y1 * sz, cx + x2 * sz, cy + y2 * sz, cl);
}

void circle(int x0, int y0, int r) {
  VGA.drawCircle(cx + x0 * sz, cy + y0 * sz, r * sz, cl);
}

void printNumber(int x, int y, int s, int col, int n) {
  if (n > 9) {
    if (n > 99) {
      if (n > 999) {
        printNumber(x, y, s, col, n / 1000);
        n %= 1000;
        x += s * 7;
      }
      printNumber(x, y, s, col, n / 100);
      n %= 100;
      x += s * 7;
    }
    printNumber(x, y, s, col, n / 10);
    n %= 10;
    x += s * 7;
  }
  cx = x;
  cy = y;
  sz = s;
  cl = col;
  if (n == 0) {
    bezier(2, 3, 2, 0, 4, 0);
    bezier(4, 0, 6, 0, 6, 3);
    line(6, 3, 6, 5);
    line(2, 3, 2, 5);
    bezier(2, 5, 2, 8, 4, 8);
    bezier(4, 8, 6, 8, 6, 5);

  }
  if (n == 1) {
    line(4, 0, 4, 8);
    line(2, 8, 6, 8);
    line(2, 2, 4, 0);
  }
  if (n == 2) {
    bezier(2, 2, 2, 0, 4, 0);
    bezier(4, 0, 6, 0, 6, 2);
    bezier(6, 2, 6, 4, 2, 8);
    line(2, 8, 6, 8);
  }
  if (n == 3) {
    bezier(2, 2, 2, 0, 4, 0);
    bezier(4, 0, 6, 0, 6, 2);
    bezier(6, 2, 6, 4, 4, 4);
    bezier(4, 4, 6, 4, 6, 6);
    bezier(6, 6, 6, 8, 4, 8);
    bezier(4, 8, 2, 8, 2, 6);
  }
  if (n == 4) {
    line(6, 0, 6, 8);
    line(6, 0, 2, 6);
    line(2, 6, 6, 6);
  }
  if (n == 5) {
    line(2, 0, 6, 0);
    line(2, 0, 2, 4);
    bezier(2, 4, 2, 3, 4, 3);
    bezier(4, 3, 7, 3, 7, 5);
    bezier(7, 5, 7, 8, 4, 8);
    bezier(4, 8, 2, 8, 2, 7);
  }
  if (n == 6) {
    bezier(6, 0, 2, 0, 2, 6);
    circle(4, 6, 2);
  }
  if (n == 7) {
    line(2, 0, 6, 0);
    line(6, 0, 3, 8);
  }
  if (n == 8) {
    circle(4, 2, 2);
    circle(4, 6, 2);
  }
  if (n == 9) {
    bezier(2, 8, 6, 8, 6, 2);
    circle(4, 2, 2);
  }
}

