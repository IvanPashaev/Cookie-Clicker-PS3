extern double cookies;
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

extern long long farms;
extern float farms_price;
extern float farms_base_price;

extern long long mines;
extern float mines_price;
extern float mines_base_price;

void save_game(double cookies, long long cursors, long long grandmas,
               long long farms, long long mines);
void load_game(double *cookies, long long *cursors, long long *grandmas,
               long long *farms, long long *mines);
