#ifndef APPLICATION
#define APPLICATION

#include "Utilitary.h"
#include "Player.h"
#include "Ennemy.h"

class Application
{
public:
    const unsigned int  WIDTH = 1080;
    const unsigned int  HEIGHT = 720;
    
private:
    sf::RenderWindow*       m_window;
    sf::Clock               m_clock;
    sf::Time                m_elapsed;
    sf::View                m_viewport;

    sf::Texture             m_background_image;
    sf::Sprite              m_background;

    Player*                 m_player;
    sf::Texture             m_projectile_texture_place_holder;
    std::vector<Projectile> m_projectiles;

    std::vector<Ennemy>     m_ennemies;
    int                     m_waves_nb;

public:
    // Constructor and destructor 
    Application();
    ~Application();

    // Class method
    int Update();
    void _update_ennemy_generation();
    void _update_viewport_movement();
    void _update_projectile_creation();
    
    void Draw();

    void spawn_ennemy(sf::Vector2f pos);

    // Accessor
    bool is_window_open() const;
};

#endif