typedef struct {
  int x;
  int y;
} cordinate_t;

typedef struct {
  int cols;
  int rows;
  int total;
  cordinate_t middle;
  cordinate_t tlc;
  cordinate_t trc;
  cordinate_t blc;
  cordinate_t brc;
  char *arr;
} framebuffer_t;

framebuffer_t init();

void update(framebuffer_t target);

int setc(framebuffer_t target, int x, int y, char dat);

int setcc(framebuffer_t target, char data);

int settlc(framebuffer_t target, char dat);

int settrc(framebuffer_t target, char dat);

int setblc(framebuffer_t target, char dat);

int setbrc(framebuffer_t target, char dat);
