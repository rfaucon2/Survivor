#include "Application.h"

// Constructor and destructor
Application::Application()
{
    this->m_window = new sf::RenderWindow(sf::VideoMode(Application::WIDTH, Application::HEIGHT), "3d cubes", sf::Style::Close);
    this->m_player = new Player();
    sf::Texture t;
    t.loadFromFile("resources/background.jpg");
    this->m_background.setTexture(t);
}
Application::~Application()
{
    delete this->m_window;
    delete this->m_player;
}

// Class method
void Application::Update()
{
    float dt = this->m_clock.restart().asSeconds();
    sf::Event ev;
    while(this->m_window->pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
            this->m_window->close();
    }
    this->m_player->Update(dt);
}

void Application::Draw()
{
    this->m_window->clear(sf::Color(0x1f1f1fff));

    this->m_window->draw(this->m_background);

    this->m_player->Draw(this->m_window);

    this->m_window->display();
}

// Accessor
bool Application::is_window_open() const
{
    return this->m_window->isOpen();
}