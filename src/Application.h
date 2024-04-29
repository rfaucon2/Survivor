#ifndef APPLICATION
#define APPLICATION

#include <SFML/Graphics.hpp>

class Application
{
public:
    const unsigned int WIDTH = 1080;
    const unsigned int HEIGHT = 720;
private:
    sf::RenderWindow* m_window;

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