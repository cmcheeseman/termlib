#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "termlib.h"


void fillbuff(char *chararr, int size) {
  for (int i = 0; i < size; i++) {
    chararr[i] = ' ';
  }
}

void getposes(framebuffer_t *target) {
  if ((target->cols % 2) == 0) {
    target->middle.x = (int)(target->cols / 2);
  } else {
    target->middle.x = (int)((target->cols / 2) + 0.5);
  }
  if ((target->rows % 2) == 0) {
    target->middle.y = (int)(target->rows / 2);
  } else {
    target->middle.y = (int)((target->rows / 2) + 0.5);
  }
  target->tlc.x = 1;
  target->tlc.y = 1;
  target->trc.x = target->cols;
  target->trc.y = 1;
  target->blc.x = 1;
  target->blc.y = target->rows;
  target->brc.x = target->cols;
  target->brc.y = target->rows;
}

framebuffer_t init() {
  initscr();
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  char *chararr = malloc((w.ws_col * w.ws_row) + 1);
  framebuffer_t framebuffer;
  framebuffer.cols = w.ws_col;
  framebuffer.rows = w.ws_row;
  framebuffer.arr = chararr;
  framebuffer.total = w.ws_col * w.ws_row;
  framebuffer.arr[framebuffer.total] = '\0';
  getposes(&framebuffer);
  fillbuff(chararr, w.ws_col * w.ws_row);
  return framebuffer;
}

void update(framebuffer_t target) {
//  printf("\e[1;1H\e[100J");
//  printf("%s", target.arr);
  printw("%s", target.arr);
  refresh();
}

int setc(framebuffer_t target, int x, int y, char dat) {
  int total = (x - 1) + ((y - 1) * target.cols);
  if (total >= target.total) {
    return 1;
  }
  target.arr[total] = dat;
  return 0;
}

int setcc(framebuffer_t target, char dat) {
  int total = (target.middle.x - 1) + ((target.middle.y - 1) * target.cols);
  target.arr[total] = dat;
  return 0;
}

int settlc(framebuffer_t target, char dat) {
  target.arr[0] = dat;
  return 0;
}

int settrc(framebuffer_t target, char dat) {
  int total = (target.trc.x - 1) + ((target.trc.y - 1) * target.cols);
  target.arr[total] = dat;
  return 0;
}

int setblc(framebuffer_t target, char dat) {
  int total = (target.blc.x - 1) + ((target.blc.y - 1) * target.cols);
  target.arr[total] = dat;
  return 0;
}

int setbrc(framebuffer_t target, char dat) {
  int total = (target.brc.x - 1) + ((target.brc.y - 1) * target.cols);
  target.arr[total] = dat;
  return 0;
}
