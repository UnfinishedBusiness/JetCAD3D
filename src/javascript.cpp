#include "solvespace.h"
#include "duktape.h"
#include "duk_module_duktape.h"
#include "javascript.h"
#include <string>

static void push_file_as_string(duk_context *ctx, const char *filename) {
    FILE *f;
    size_t len;
    char buf[16384];

    f = fopen(filename, "rb");
    if (f) {
        len = fread((void *) buf, 1, sizeof(buf), f);
        fclose(f);
        duk_push_lstring(ctx, (const char *) buf, (duk_size_t) len);
    } else {
        duk_push_undefined(ctx);
    }
}
static duk_ret_t print(duk_context *ctx) {
  printf("%s", duk_to_string(ctx, 0));
  return 0;  /* no return value (= undefined) */
}
static duk_ret_t include(duk_context *ctx) {
  push_file_as_string(ctx, duk_to_string(ctx, 0));
  if (duk_peval(ctx) != 0) {
    printf("[Javascript::include] Error: %s\n", duk_safe_to_string(ctx, -1));
  }
  duk_pop(ctx);  /* ignore result */
  return 0;  /* no return value (= undefined) */
}


std::string Javascript::eval(std::string exp)
{
    duk_push_string(ctx, exp.c_str());
    if (duk_peval(ctx) != 0)
    {
        printf("[Javascript::eval] (%s) eval failed: %s\n",exp.c_str(), duk_safe_to_string(ctx, -1));
    }
    else
    {
        if (!strcmp(duk_safe_to_string(ctx, -1), "undefined") == 0)
        {
        //makV printf("[scriptEval] result is: %s\n", duk_safe_to_string(ctx, -1));
        }
    }
	std::string ret = std::string(duk_get_string(ctx, -1));
    duk_pop(ctx);  /* pop result */
	return ret;
}
void Javascript::eval_file(std::string file)
{
    push_file_as_string(ctx, file.c_str());
    if (duk_peval(ctx) != 0) {
        printf("[Javascript::eval_file] Error: %s\n", duk_safe_to_string(ctx, -1));
    }
    duk_pop(ctx);  /* ignore result */
}
void Javascript::init()
{
    printf("*INIT* Javascript Engine!\n");
    ctx = duk_create_heap_default();
    
    duk_push_c_function(ctx, print, 1 /*nargs*/);
    duk_put_global_string(ctx, "print");

    duk_push_c_function(ctx, include, 1 /*nargs*/);
    duk_put_global_string(ctx, "include");

    duk_module_duktape_init(ctx);
    eval_file("scripts/loader.js");
}