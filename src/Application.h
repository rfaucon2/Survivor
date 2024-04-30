#ifndef APPLICATION
#define APPLICATION

#include "Utilitary.h"
#include "Player.h"

class Application
{
public:
    const unsigned int  WIDTH = 1080;
    const unsigned int  HEIGHT = 720;
private:
    sf::RenderWindow*   m_window;
    Player*             m_player;
    sf::Clock           m_clock;
    sf::Texture         m_background_image;
    sf::Sprite          m_background;

public:
    // Constructor and destructor 
    Application();
    ~Application();

    // Class method
    void Update();
    void Draw();

    // Accessor
    bool is_window_open() const;
};

#endif