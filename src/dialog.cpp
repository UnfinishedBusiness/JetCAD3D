#include "solvespace.h"
#include "dialog.h"
#include <string>

std::vector <Dialog> dialogs;

Dialog::Dialog(int px, int py, int w, int h, std::string t)
{
    this->posx = px;
    this->posy = py;
    this->width = w;
    this->height = h;
    this->title = t;

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
                if (x > (this->posx) && x < (this->posx + this->width) && y > (this->posy + this->height - 20) && y < (this->posy + this->height))
                {
                    //printf("Clicked inside title: %s bar!\n", this->title.c_str());
                    this->windowDraggingActive = true;
                    this->lastx = x;
                    this->lasty = y;
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
void Dialog::render(UiCanvas uiCanvas)
{
    uiCanvas.DrawRect(posx, posx + width, posy, posy + height, DIALOG_BACKPANE_COLOR, DIALOG_BACKPANE_COLOR); //Backpane
    uiCanvas.DrawRect(posx, posx + width, posy + height, posy + height - 20, DIALOG_TITLEBAR_COLOR, DIALOG_TITLEBAR_COLOR); //Titlebar
    uiCanvas.DrawBitmapText(ssprintf(title.c_str()), posx + 10, posy + height - 15, DIALOG_FONT_COLOR);
}