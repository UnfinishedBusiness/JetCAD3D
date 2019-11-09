//-----------------------------------------------------------------------------
// The interface bewteen JetCAD and Javascript counter parts
//-----------------------------------------------------------------------------
#ifndef JAVASCRIPT_H
#define JAVASCRIPT_H

#include "duktape.h"
#include <string>

class Javascript{

    public:
        void init();
        void destroy();
        void refresh();
        std::string eval(std::string exp);
        void eval_file(std::string file);
    private:
        duk_context *ctx;
};

extern Javascript js;

#endif
