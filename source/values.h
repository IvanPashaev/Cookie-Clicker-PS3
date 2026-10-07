extern long long cookies;
extern double cookies_per_second;

#define MAX_FLOAT_COOKIES 64

typedef struct {
  int active;
  float x, y;   // позиция
  float w, h;   // размер маленькой печеньки
  int life;     // осталось кадров жизни
  int max_life; // полное время жизни
} FloatCookie;

extern FloatCookie float_cookies[MAX_FLOAT_COOKIES];

void save_game(unsigned long long cookies, int cursors);
void load_game(unsigned long long *cookies, int *cursors);
