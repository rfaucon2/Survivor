#include "Application.h"

// Constructor and destructor
Application::Application()
{
    this->m_window = new sf::RenderWindow(sf::VideoMode(Application::WIDTH, Application::HEIGHT), "Survivor", sf::Style::Close);
    this->m_viewport = sf::View(sf::Vector2f(0, 0), sf::Vector2f(Application::WIDTH, Application::HEIGHT));

    this->m_window->setView(this->m_viewport);

    this->m_background_image.loadFromFile("resources/download.jpeg");
    this->m_background = sf::Sprite(this->m_background_image);

    this->m_player = new Player();
}
Application::~Application()
{
    delete this->m_window;
    delete this->m_player;
}

// Class method
int Application::Update()
{
    float dt = this->m_clock.restart().asSeconds();
    sf::Event ev;
    while(this->m_window->pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {
            this->m_window->close();
            return 1;
        }
    }

    this->m_player->Update(dt);

    // Check if the viewport has to be moved
    sf::Vector2f delta = this->m_player->get_pos() - this->m_viewport.getCenter();
    int w = Application::WIDTH / 6;
    int h = Application::HEIGHT / 6;
    if(delta.x > w)
        this->m_viewport.move(delta.x - w, 0);
    else if(delta.x < -w)
        this->m_viewport.move(delta.x + w, 0);

    if(delta.y > h)
        this->m_viewport.move(0, delta.y - h);
    else if(delta.y < -h)
        this->m_viewport.move(0, delta.y + h);
    
    this->m_window->setView(this->m_viewport);


    for (Ennemy* ennemy : this->m_ennemies)
        ennemy->update(dt, this->m_player->get_pos());
    return 0;
}

void Application::Draw()
{
    this->m_window->clear(sf::Color(0x1f1f1fff));

    // Apply background
    sf::Vector2f img_size = this->m_background.getGlobalBounds().getSize();
    sf::Vector2f view_pos = this->m_viewport.getCenter();
    sf::Vector2f tl = sf::Vector2f(int(view_pos.x / img_size.x) * img_size.x, int(view_pos.y / img_size.y) * img_size.y);
    
    int nx = ceil(this->m_window->getSize().x / img_size.x) + 1;
    int ny = ceil(this->m_window->getSize().y / img_size.y) + 1;

    for(int i = -nx/2 - 1; i <= nx/2; i++)
    {
        for(int j = -ny/2 - 1; j <= ny/2; j++)
        {
            this->m_background.setPosition(tl + sf::Vector2f(img_size.x * i, img_size.y * j));
            this->m_window->draw(this->m_background);
        }
    }

    for (Ennemy* ennemy : this->m_ennemies)
        ennemy->draw(this->m_window);

    this->m_player->Draw(this->m_window);

    this->m_window->display();
}

void Application::spawn_ennemy(sf::Vector2f pos)
{
    this->m_ennemies.push_back(new Ennemy(sf::Vector2f(100.0f, 100.0f)));
}

// Accessor
bool Application::is_window_open() const
{
    return this->m_window->isOpen();
}