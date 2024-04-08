#include <stdio.h>
#include "termlib.h"
#include <unistd.h>

int main() {
  framebuffer_t buff = init();
  setcc(buff, 'o');
  settlc(buff, 'l');
  settrc(buff, 'l');
  setblc(buff, 'l');
  setbrc(buff, 'l');
  while (1) {
    update(buff);
  }
  return 0;
}
