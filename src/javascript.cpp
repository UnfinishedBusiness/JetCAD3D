#include "solvespace.h"
#include "duktape.h"
#include "duk_module_duktape.h"
#include "javascript.h"
#include "libdxfrw.h"
#include "libdwgr.h"
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
/* Javascript binding functions */
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
static duk_ret_t add_line(duk_context *ctx)
{

    Vector p0;
    p0.x = duk_to_number(ctx, 0) * SS.exportScale;
    p0.y = duk_to_number(ctx, 1) * SS.exportScale;
    Vector p1;
    p1.x = duk_to_number(ctx, 2) * SS.exportScale;
    p1.y = duk_to_number(ctx, 3) * SS.exportScale;
    hStyle style;

    hRequest hr = SS.GW.AddRequest(Request::Type::LINE_SEGMENT, /*rememberForUndo=*/false);
    SK.GetEntity(hr.entity(1))->PointForceTo(p0);
    SK.GetEntity(hr.entity(2))->PointForceTo(p1);

    Request *r = SK.GetRequest(hr);
    r->construction = duk_to_boolean(ctx, 4);
    r->style = style;
    return 0;  /* no return value (= undefined) */
}
static duk_ret_t add_circle(duk_context *ctx)
{
    /* Scale points by import/export scale */
    hStyle style;
    Vector center;
    center.x = duk_to_number(ctx, 0) * SS.exportScale;
    center.y = duk_to_number(ctx, 1) * SS.exportScale;
    double radius = duk_to_number(ctx, 2) * SS.exportScale;
    hRequest hr = SS.GW.AddRequest(Request::Type::CIRCLE, /*rememberForUndo=*/false);
    SK.GetEntity(hr.entity(1))->PointForceTo(center);
    SK.GetEntity(hr.entity(64))->DistanceForceTo(radius);

    Request *r = SK.GetRequest(hr);
    r->construction = duk_to_boolean(ctx, 3);
    r->style = style;
    return 0;  /* no return value (= undefined) */
}
static duk_ret_t add_arc(duk_context *ctx)
{
    hStyle style;
    hRequest hr = SS.GW.AddRequest(Request::Type::ARC_OF_CIRCLE, /*rememberForUndo=*/false);
    double radius = duk_to_number(ctx, 4) * SS.exportScale;
    double sa = duk_to_number(ctx, 2);
    double ea = duk_to_number(ctx, 3);
    Vector c = Vector::From(duk_to_number(ctx, 0) * SS.exportScale, duk_to_number(ctx, 1) * SS.exportScale, 0);
    Vector rvs = Vector::From(radius * cos(sa), radius * sin(sa), 0).Plus(c);
    Vector rve = Vector::From(radius * cos(ea), radius * sin(ea), 0).Plus(c);

    SK.GetEntity(hr.entity(1))->PointForceTo(c);
    SK.GetEntity(hr.entity(2))->PointForceTo(rvs);
    SK.GetEntity(hr.entity(3))->PointForceTo(rve);

    Request *r = SK.GetRequest(hr);
    r->construction = duk_to_boolean(ctx, 5);
    r->style = style;
    return 0;  /* no return value (= undefined) */
}
static duk_ret_t text_window_printf(duk_context *ctx)
{
    SS.TW.Printf(false, duk_to_string(ctx, 0));
    return 0;  /* no return value (= undefined) */
}
static duk_ret_t text_window_clear_screen(duk_context *ctx)
{
    SS.TW.ClearScreen();
    //SS.GW.ForceTextWindowShown();
    return 0;  /* no return value (= undefined) */
}
static duk_ret_t text_window_show_screen(duk_context *ctx)
{
    SS.GW.ForceTextWindowShown();
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
    //printf("*INIT* Javascript Engine!\n");
    ctx = duk_create_heap_default();
    
    duk_push_c_function(ctx, print, 1 /*nargs*/);
    duk_put_global_string(ctx, "print");

    duk_push_c_function(ctx, include, 1 /*nargs*/);
    duk_put_global_string(ctx, "include");

    duk_push_c_function(ctx, add_line, 5 /*nargs*/);
    duk_put_global_string(ctx, "add_line");

    duk_push_c_function(ctx, add_circle, 4 /*nargs*/);
    duk_put_global_string(ctx, "add_circle");

    duk_push_c_function(ctx, add_arc, 6 /*nargs*/);
    duk_put_global_string(ctx, "add_arc");

    duk_push_c_function(ctx, text_window_printf, 1 /*nargs*/);
    duk_put_global_string(ctx, "text_window_printf");

    duk_push_c_function(ctx, text_window_clear_screen, 0 /*nargs*/);
    duk_put_global_string(ctx, "text_window_clear_screen");

    duk_push_c_function(ctx, text_window_clear_screen, 0 /*nargs*/);
    duk_put_global_string(ctx, "text_window_show_screen");

    duk_module_duktape_init(ctx);
    eval_file("scripts/loader.js");
}
void Javascript::destroy()
{
    duk_destroy_heap(ctx);
}
void Javascript::refresh()
{
    if (ctx != NULL)
    {
        destroy();
    }
    init();
}