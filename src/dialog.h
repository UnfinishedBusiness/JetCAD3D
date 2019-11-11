//-----------------------------------------------------------------------------
// The interface bewteen JetCAD and Javascript counter parts
//-----------------------------------------------------------------------------
#ifndef DIALOG_H
#define DIALOG_H

#include "solvespace.h"
#include <string>
#include <vector>

#define DIALOG_FONT_COLOR (RgbaColor){ 255, 255, 255, 255 } 
#define DIALOG_BACKPANE_COLOR (RgbaColor){ 0, 0, 0, 200 }
#define DIALOG_TITLEBAR_COLOR (RgbaColor){ 0, 0, 240, 200 }

class Dialog{

    public:
        Dialog(int px, int py, int w, int h, std::string t);  
        void render(UiCanvas uiCanvas);
        bool mouseEvent(Platform::MouseEvent event, int x, int y);
    private:
        /* Input State Variables */
        bool leftMousePressed;
        bool windowDraggingActive;
        /*************************/

        int posx;
        int posy;
        int width;
        int height;
        std::string title;

        int lastx;
        int lasty;
};

extern std::vector <Dialog> dialogs;

#endif
