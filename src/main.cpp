#include "Application.h"

int main()
{
    Application app;

    while (app.is_window_open())
    {
        app.Update();
        app.Draw();
    }

    return 0;
}