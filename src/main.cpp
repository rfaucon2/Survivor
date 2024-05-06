#include "Application.h"


int main()
{
    srand(time(nullptr));
    Application app;
    while (app.is_window_open())
    {
        int i = app.Update();
        if(i == 1)
            return 0;
        app.Draw();
    }

    return 0;
}