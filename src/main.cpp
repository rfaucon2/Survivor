#include "Application.h"

int main()
{
    Application app;
    app.spawn_ennemy(sf::Vector2f(10.0F, 40.0F));
    while (app.is_window_open())
    {
        int i = app.Update();
        if(i == 1)
            return 0;
        app.Draw();
    }

    return 0;
}