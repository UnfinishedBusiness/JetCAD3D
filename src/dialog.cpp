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
    this->id = dialogs.size() - 1;
    this->leftMousePressed = false;
    this->windowDraggingActive = false;

    this->lastx = -1;
    this->lasty = -1;

    SS.GW.Invalidate();
}
bool Dialog::mouseEvent(Platform::MouseEvent event, int x, int y)
{
    switch (event.type){
        case Platform::MouseEvent::Type::PRESS:{
            if(event.button == Platform::MouseEvent::Button::LEFT) {
                this->leftMousePressed = true;
                if (x > (this->posx + this->width - 19) && x < (this->posx + this->width-1) && y < (this->posy + this->height - 1) && y > (this->posy + this->height - 19)) //Close button
                {
                    //printf("Close button clicked!\n");
                    for (long unsigned int x = 0; x < dialogs.size(); x++)
                    {
                        if (dialogs[x].id == this->id)
                        {
                            dialogs.erase(dialogs.begin() + x);
                        }
                    }
                    return true;
                }
                else if (x > (this->posx) && x < (this->posx + this->width) && y > (this->posy + this->height - 20) && y < (this->posy + this->height)) //Title bar dragging
                {
                    //printf("Clicked inside title: %s bar!\n", this->title.c_str());
                    this->windowDraggingActive = true;
                    this->lastx = x;
                    this->lasty = y;
                }
                else //Check if click is over a widget
                {
                    for (long unsigned int z = 0; z < this->WidgetStack.size(); z++)
                    {
                        if (this->WidgetStack[z].type == DIALOG_BUTTON_WIDGET)
                        {
                            if (x > this->posx + this->WidgetStack[z].button.posx && x < this->posx + this->WidgetStack[z].button.posx + this->WidgetStack[z].button.width && y > this->posy + this->WidgetStack[z].button.posy && y < this->posy + this->WidgetStack[z].button.posy + this->WidgetStack[z].button.height) 
                            {
                                //printf("Clicked button: %s\n", this->WidgetStack[z].button.label.c_str());
                                js.eval("dialog.element_clicked(\'{ \"dialog_id\":\"" + std::to_string(z) + "\", \"type\":\"button_click\", \"button_label\":\"" + this->WidgetStack[z].button.label + "\"}\');");
                                return true;
                            }
                        }
                        
                    }
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
}
void Dialog::render(UiCanvas uiCanvas)
{
    uiCanvas.DrawRect(this->posx, this->posx + this->width, this->posy, this->posy + this->height, DIALOG_BACKPANE_COLOR, DIALOG_BACKPANE_COLOR); //Backpane
    uiCanvas.DrawRect(this->posx, this->posx + this->width, this->posy + this->height, this->posy + this->height - 20, DIALOG_TITLEBAR_COLOR, DIALOG_TITLEBAR_COLOR); //Titlebar
    uiCanvas.DrawBitmapText(ssprintf(this->title.c_str()), this->posx + 10, this->posy + this->height - 15, DIALOG_FONT_COLOR); //Title Text
    uiCanvas.DrawRect(this->posx + this->width - 19, this->posx + this->width-1, this->posy + this->height - 1, this->posy + this->height - 19, DIALOG_SOLID_BLACK, DIALOG_SOLID_BLACK); //Close Button Container
    uiCanvas.DrawBitmapText(ssprintf("X"), this->posx + this->width - 13, this->posy + this->height - 16, DIALOG_FONT_COLOR, 1); //Close Button Text

    for (long unsigned int x = 0; x < this->WidgetStack.size(); x++)
    {
        if (this->WidgetStack[x].type == DIALOG_BUTTON_WIDGET)
        {
            uiCanvas.DrawRect(this->posx + this->WidgetStack[x].button.posx, this->posx + this->WidgetStack[x].button.posx + this->WidgetStack[x].button.width, this->posy + this->WidgetStack[x].button.posy, this->posy + this->WidgetStack[x].button.posy + this->WidgetStack[x].button.height, DIALOG_BUTTON_COLOR, DIALOG_BUTTON_COLOR);
            uiCanvas.DrawBitmapText(ssprintf(this->WidgetStack[x].button.label.c_str()), this->posx + this->WidgetStack[x].button.posx + 10, this->posy + this->WidgetStack[x].button.posy + 10, DIALOG_FONT_COLOR);
        }
    }
}