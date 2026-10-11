#include "values.h"
#include "json-c/json_object.h"
#include "json-c/json_tokener.h"
#include <json-c/json.h>
#include <stdio.h>

#define PI 3.14

long long cookies = 0;
double cookies_per_second = 0.0;

float cookie_width = 2.5f;
float cookie_height = 2.5f;

long long cursors = 0;
float cursors_price = 15.0f;
float cursors_base_price = 15.0f;

long long grandmas = 0;
float grandmas_price = 100.0f;
float grandmas_base_price = 100.0f;

FloatCookie float_cookies[MAX_FLOAT_COOKIES] = {0};

void load_game(unsigned long long *cookies, long long *cursors) {
  FILE *fp = fopen("/dev_hdd0/game/COOK13000/USRDIR/save.json", "r");
  if (!fp)
    return;

  char buffer[1024];
  fread(buffer, 1, sizeof(buffer), fp);
  fclose(fp);

  // parse string to object
  struct json_object *root = json_tokener_parse(buffer);
  if (!root)
    return; // parsing error

  struct json_object *val;

  // get vals
  if (json_object_object_get_ex(root, "cookies", &val)) {
    *cookies = json_object_get_int64(val);
  }
  if (json_object_object_get_ex(root, "cursors", &val)) {
    *cursors = json_object_get_int64(val);
  }

  // free memory
  json_object_put(root);
}
void save_game(unsigned long long cookies, long long cursors) {
  // create root object
  struct json_object *root = json_object_new_object();

  // add objects
  json_object_object_add(root, "cookies", json_object_new_int64(cookies));
  json_object_object_add(root, "cursors", json_object_new_int64(cursors));

  // json to string and write to file
  const char *json_str =
      json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY);
  FILE *fp = fopen("/dev_hdd0/game/COOK13000/USRDIR/save.json", "w");
  if (fp) {
    fputs(json_str, fp);
    fclose(fp);
  }

  // free memory
  json_object_put(root);
}
