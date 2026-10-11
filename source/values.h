extern long long cookies;
extern double cookies_per_second;

#define MAX_FLOAT_COOKIES 64

typedef struct {
  int active;
  float x, y;   // pos
  float w, h;   // size of small cookie
  int life;     // last frames
  int max_life; // full life time
} FloatCookie;

extern FloatCookie float_cookies[MAX_FLOAT_COOKIES];
extern float cookie_width;
extern float cookie_height;

extern long long cursors;
extern float cursors_price;
extern float cursors_base_price;

extern long long grandmas;
extern float grandmas_price;
extern float grandmas_base_price;

void save_game(unsigned long long cookies, long long cursors);
void load_game(unsigned long long *cookies, long long *cursors);
