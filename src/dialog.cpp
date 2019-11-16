#include "solvespace.h"
#include "dialog.h"
#include "javascript.h"
#include <string>

std::vector <Dialog> dialogs;

Dialog::Dialog(int px, int py, int w, int h, std::string t)
{
    this->posx = px;
    this->posy = py;
    this->width = w;
    this->height = h;
    this->title = t;
    this->id = dialogs.size();
    this->leftMousePressed = false;
    this->windowDraggingActive = false;
    this->isFocused = false;

    this->lastx = -1;
    this->lasty = -1;

    SS.GW.Invalidate();
}
bool Dialog::keyboardEvent(Platform::KeyboardEvent event)
{
    /* We only need to pay attention to keyboard input if a window has focus */
    if (this->isFocused == true)
    {
        if(event.key == Platform::KeyboardEvent::Key::CHARACTER)
        {
            //printf("(dialog) Recieved keypress: %c\n", event.chr);
            for (long unsigned int z = 0; z < this->WidgetStack.size(); z++)
            {
                if (this->WidgetStack[z].type == DIALOG_INPUT_WIDGET)
                {
                    if (this->WidgetStack[z].input.hasFocus == true)
                    {
                        //printf("Pressed: '%d'\n", event.chr);
                        if (event.chr == 127)
                        {
                            if (this->WidgetStack[z].input.value.size() > 0) this->WidgetStack[z].input.value.pop_back();
                            //printf("Backspace: %s\n", this->WidgetStack[z].input.value.c_str());
                        }
                        else
                        {
                            //printf("size is: %d, max_length: %d\n", this->WidgetStack[z].input.value.size(),this->WidgetStack[z].input.max_length);
                            if (this->WidgetStack[z].input.value.size() < this->WidgetStack[z].input.max_length) this->WidgetStack[z].input.value.push_back(event.chr);
                        }
                        SS.GW.Invalidate();
                        return true;
                    }
                }
            }
        }
    }
}
bool Dialog::mouseEvent(Platform::MouseEvent event, int x, int y)
{
    switch (event.type){
        case Platform::MouseEvent::Type::PRESS:{
            if(event.button == Platform::MouseEvent::Button::LEFT) {
                this->leftMousePressed = true;
                /*if (this->isFocused == false && x > this->posx && x < this->posx + this->width && y > this->posy && y < this->posy + this->height) //Make sure we are focused
                {
                    for (long unsigned int x = 0; x < dialogs.size(); x++)
                    {
                        dialogs[x].isFocused = false;
                    }
                    this->isFocused = true;
                    SS.GW.Invalidate();
                    //return true;
                }*/
                if (this->isFocused == true && x > (this->posx + this->width - 19) && x < (this->posx + this->width-1) && y < (this->posy + this->height - 1) && y > (this->posy + this->height - 19)) //Close button
                {
                    //printf("Close button clicked!\n");
                    for (long unsigned int x = 0; x < dialogs.size(); x++)
                    {
                        if (dialogs[x].id == this->id)
                        {
                            dialogs.erase(dialogs.begin() + x);
                            SS.GW.Invalidate();
                        }
                    }
                    //return true;
                }
                else if (this->isFocused == true && x > (this->posx) && x < (this->posx + this->width) && y > (this->posy + this->height - 20) && y < (this->posy + this->height)) //Title bar dragging
                {
                    //printf("Clicked inside title: %s bar!\n", this->title.c_str());
                    this->windowDraggingActive = true;
                    this->lastx = x;
                    this->lasty = y;
                }
                else if (this->isFocused == true) //Check if click is over a widget
                {
                    for (long unsigned int z = 0; z < this->WidgetStack.size(); z++)
                    {
                        if (this->WidgetStack[z].type == DIALOG_BUTTON_WIDGET)
                        {
                            if (x > this->posx + this->WidgetStack[z].button.posx && x < this->posx + this->WidgetStack[z].button.posx + this->WidgetStack[z].button.width && y > this->posy + this->WidgetStack[z].button.posy && y < this->posy + this->WidgetStack[z].button.posy + this->WidgetStack[z].button.height) 
                            {
                                //printf("Clicked button: %s\n", this->WidgetStack[z].button.label.c_str());
                                js.eval("dialog.element_clicked(\'{ \"dialog_id\":\"" + std::to_string(this->id) + "\", \"type\":\"button_click\", \"button_label\":\"" + this->WidgetStack[z].button.label + "\"}\');");
                                //return true;
                            }
                        }
                    }
                }
                if (x > this->posx && x < this->posx + this->width && y > this->posy && y < this->posy + this->height) //If we are a click in a window eat the click so noone else sees it
                {
                    //printf("Click was on a window but not a element!\n");
                    for (long unsigned int x = 0; x < dialogs.size(); x++)
                    {
                        dialogs[x].isFocused = false;
                    }
                    this->isFocused = true;
                    SS.GW.Invalidate();
                    return true;
                }
                
            } else if(event.button == Platform::MouseEvent::Button::MIDDLE ||
                      event.button == Platform::MouseEvent::Button::RIGHT) {
            }
            break;
        }
        case Platform::MouseEvent::Type::MOTION:{
            //printf("X: %d, Y: %d\n", x, y);
            if (this->leftMousePressed == true)
            {
                if (this->windowDraggingActive == true)
                {
                    this->posx -= this->lastx - x;
                    this->posy -= this->lasty - y;
                    this->lastx = x;
                    this->lasty = y;
                    SS.GW.Invalidate();
                    return true;
                }
            }
            break;
        }
        case Platform::MouseEvent::Type::DBL_PRESS:
            //printf("(dialog) Double Clicked!\n");
            break;
        case Platform::MouseEvent::Type::RELEASE:
            this->leftMousePressed = false;
            if (this->windowDraggingActive == true) this->windowDraggingActive = false;
            this->lastx = -1;
            this->lasty = -1;
            break;
        case Platform::MouseEvent::Type::SCROLL_VERT:
            break;
        case Platform::MouseEvent::Type::LEAVE:
            
            break;
    }
    return false;
}
void Dialog::add_button(int px, int py, int w, int h, std::string l)
{
    ButtonElement button;
    button.posx = px;
    button.posy = py;
    button.width = w;
    button.height = h;
    button.label = l;

    WidgetElement widget;
    widget.type = DIALOG_BUTTON_WIDGET;
    widget.button = button;
    this->WidgetStack.push_back(widget);
    SS.GW.Invalidate();
}
void Dialog::add_label(int px, int py, std::string l)
{
    LabelElement label;
    label.posx = px;
    label.posy = py;
    label.label = l;

    WidgetElement widget;
    widget.type = DIALOG_LABEL_WIDGET;
    widget.label = label;
    this->WidgetStack.push_back(widget);
    SS.GW.Invalidate();
}
void Dialog::add_input(int px, int py, int width, int height, std::string value, int max_length)
{
    InputElement input;
    input.posx = px;
    input.posy = py;
    input.width = width;
    input.height = height;
    input.value = value;
    input.max_length = max_length;
    //printf("Max Length: %d\n", input.max_length);
    input.hasFocus = true;

    WidgetElement widget;
    widget.type = DIALOG_INPUT_WIDGET;
    widget.input = input;
    this->WidgetStack.push_back(widget);
    SS.GW.Invalidate();
}
void Dialog::render(UiCanvas uiCanvas)
{
    int zindex = 0;
    if (this->isFocused) zindex = this->WidgetStack.size() * 2;
    uiCanvas.DrawRect(this->posx, this->posx + this->width, this->posy, this->posy + this->height, DIALOG_BACKPANE_COLOR, DIALOG_BACKPANE_COLOR, zindex); //Backpane
    if (this->isFocused)
    {
        uiCanvas.DrawRect(this->posx, this->posx + this->width, this->posy + this->height, this->posy + this->height - 20, DIALOG_TITLEBAR_COLOR, DIALOG_TITLEBAR_COLOR, zindex); //Titlebar
    }
    else
    {
        uiCanvas.DrawRect(this->posx, this->posx + this->width, this->posy + this->height, this->posy + this->height - 20, DIALOG_TITLEBAR_UNFOCUSED_COLOR, DIALOG_TITLEBAR_UNFOCUSED_COLOR, zindex); //Titlebar
    }
    uiCanvas.DrawBitmapText(ssprintf(this->title.c_str()), this->posx + 10, this->posy + this->height - 15, DIALOG_FONT_COLOR, zindex); //Title Text
    uiCanvas.DrawRect(this->posx + this->width - 19, this->posx + this->width-1, this->posy + this->height - 1, this->posy + this->height - 19, DIALOG_SOLID_BLACK, DIALOG_SOLID_BLACK, zindex); //Close Button Container
    uiCanvas.DrawBitmapText(ssprintf("X"), this->posx + this->width - 13, this->posy + this->height - 16, DIALOG_FONT_COLOR, zindex + 1); //Close Button Text

    for (long unsigned int x = 0; x < this->WidgetStack.size(); x++)
    {
        if (this->WidgetStack[x].type == DIALOG_BUTTON_WIDGET)
        {
            uiCanvas.DrawRect(this->posx + this->WidgetStack[x].button.posx, this->posx + this->WidgetStack[x].button.posx + this->WidgetStack[x].button.width, this->posy + this->WidgetStack[x].button.posy, this->posy + this->WidgetStack[x].button.posy + this->WidgetStack[x].button.height, DIALOG_BUTTON_COLOR, DIALOG_BUTTON_COLOR, zindex);
            uiCanvas.DrawBitmapText(ssprintf(this->WidgetStack[x].button.label.c_str()), this->posx + this->WidgetStack[x].button.posx + 10, this->posy + this->WidgetStack[x].button.posy + 10, DIALOG_FONT_COLOR, zindex);
        }
        if (this->WidgetStack[x].type == DIALOG_LABEL_WIDGET)
        {
            uiCanvas.DrawBitmapText(ssprintf(this->WidgetStack[x].label.label.c_str()), this->posx + this->WidgetStack[x].label.posx, this->posy + this->WidgetStack[x].label.posy, DIALOG_FONT_COLOR, zindex);
        }
        if (this->WidgetStack[x].type == DIALOG_INPUT_WIDGET)
        {
            uiCanvas.DrawRect(this->posx + this->WidgetStack[x].input.posx, this->posx + this->WidgetStack[x].input.posx + this->WidgetStack[x].input.width, this->posy + this->WidgetStack[x].input.posy, this->posy + this->WidgetStack[x].input.posy + this->WidgetStack[x].input.height, DIALOG_INPUT_BACKROUND_COLOR, DIALOG_INPUT_BORDER_OUTLINE_FOCUSED_COLOR, zindex);
            uiCanvas.DrawBitmapText(ssprintf(this->WidgetStack[x].input.value.c_str()), this->posx + this->WidgetStack[x].input.posx + 10, this->posy + this->WidgetStack[x].input.posy + 10, DIALOG_SOLID_BLACK, zindex);
        }
    }
}