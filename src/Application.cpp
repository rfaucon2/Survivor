#include "Application.h"

// Constructor and destructor
Application::Application()
{
    this->m_window = new sf::RenderWindow(sf::VideoMode(Application::WIDTH, Application::HEIGHT), "3d cubes", sf::Style::Close);
}
Application::~Application()
{
    delete this->m_window;
}

// Class method
void Application::Update()
{
    sf::Event ev;
    while(this->m_window->pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
            this->m_window->close();
    }
}

void Application::Draw()
{
    this->m_window->clear();

    this->m_window->display();
}

// Accessor
bool Application::is_window_open() const
{
    return this->m_window->isOpen();
}