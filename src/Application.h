#ifndef APPLICATION
#define APPLICATION

#include "Utilitary.h"
#include "Player.h"
#include "Ennemy.h"
#include <vector>

class Application
{
public:
    const unsigned int  WIDTH = 1080;
    const unsigned int  HEIGHT = 720;
    
private:
    sf::RenderWindow*       m_window;
    sf::Clock               m_clock;
    sf::View                m_viewport;

    sf::Texture             m_background_image;
    sf::Sprite              m_background;

    Player*                 m_player;

    std::vector<Ennemy*>    m_ennemies;

public:
    // Constructor and destructor 
    Application();
    ~Application();

    // Class method
    int Update();
    void Draw();

    void spawn_ennemy(sf::Vector2f pos);

    // Accessor
    bool is_window_open() const;
};

#endif