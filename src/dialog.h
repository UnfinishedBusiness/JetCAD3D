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
#define DIALOG_TITLEBAR_COLOR (RgbaColor){ 0, 0, 240, 255 }
#define DIALOG_TITLEBAR_UNFOCUSED_COLOR (RgbaColor){ 50, 50, 50, 255 }
#define DIALOG_INPUT_BACKROUND_COLOR { 255, 255, 255, 255 }
#define DIALOG_INPUT_BORDER_OUTLINE_FOCUSED_COLOR { 255, 255, 0, 255 }
#define DIALOG_INPUT_BORDER_OUTLINE_UNFOCUSED_COLOR { 0, 0, 0, 255 }
#define DIALOG_BUTTON_COLOR (RgbaColor){ 0, 140, 0, 220 }
#define DIALOG_SOLID_BLACK (RgbaColor){ 0, 0, 0, 255 }
#define DIALOG_SOLID_WHITE (RgbaColor){ 255, 255, 255, 255 }


#define DIALOG_BUTTON_WIDGET 0
#define DIALOG_LABEL_WIDGET 1
#define DIALOG_INPUT_WIDGET 2

struct ButtonElement{
    int posx;
    int posy;
    int width;
    int height;
    std::string label;
};
struct LabelElement{
    int posx;
    int posy;
    std::string label;
};
struct InputElement{
    int posx;
    int posy;
    int width;
    int height;
    int max_length;
    std::string value;
    int id;
    bool hasFocus;
};
struct WidgetElement{
    int type;
    ButtonElement button;
    LabelElement label;
    InputElement input;
};

class Dialog{

    public:
        bool isFocused;
        Dialog(int px, int py, int w, int h, std::string t);  
        void render(UiCanvas uiCanvas);
        bool mouseEvent(Platform::MouseEvent event, int x, int y);
        bool keyboardEvent(Platform::KeyboardEvent event);
        void add_button(int px, int py, int w, int h, std::string l);
        void add_label(int px, int py, std::string l);
        void add_input(int px, int py, int width, int height, std::string value, int max_length);
    private:
        std::vector<WidgetElement> WidgetStack;
        /* Input State Variables */
        bool leftMousePressed;
        bool windowDraggingActive;
        /*************************/
        int posx;
        int posy;
        int width;
        int height;
        std::string title;
        int id;

        int lastx;
        int lasty;
};

extern std::vector <Dialog> dialogs;

#endif
