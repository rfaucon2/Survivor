#include "Application.h"

// Constructor and destructor
Application::Application()
    : m_waves_nb(0)
{
    this->m_window = new sf::RenderWindow(sf::VideoMode(Application::WIDTH, Application::HEIGHT), "Survivor", sf::Style::Close);
    this->m_viewport = sf::View(sf::Vector2f(0, 0), sf::Vector2f(Application::WIDTH, Application::HEIGHT));

    this->m_window->setView(this->m_viewport);

    this->m_background_image.loadFromFile("resources/background.jpeg");
    this->m_background = sf::Sprite(this->m_background_image);
    this->m_background.setColor(sf::Color(0xcccccccc));

    this->m_player = new Player();
    this->m_projectile_texture_place_holder.loadFromFile("resources/placeholder_bullet.png");
    this->m_projectiles.push_back(Projectile(this->m_player->get_pos(), M_PI_2, SpellType::CHICKEN, &this->m_projectile_texture_place_holder));
}
Application::~Application()
{
    delete this->m_window;
    delete this->m_player;
}

// Class method
int Application::Update()
{
    // Update time variables
    float dt = (this->m_clock.getElapsedTime()-this->m_elapsed).asSeconds();
    this->m_elapsed = this->m_clock.getElapsedTime();
    
    // Process events
    sf::Event ev;
    while(this->m_window->pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {
            this->m_window->close();
            return 1;
        }
    }

    // Handle ennemy generation
    this->_update_ennemy_generation();

    this->m_player->Update(dt);
    // Handle viewport movement
    this->_update_viewport_movement();

    // Update all ennemies
    for(Ennemy &ennemy : this->m_ennemies){
        ennemy.update(dt, this->m_player->get_pos());
    }

    // Update all projectiles
    this->_update_projectiles(dt);

    // Check if new projectiles have to be created
    this->_update_projectile_creation();
    this->_update_collisions();

    return 0;
}
void Application::_update_ennemy_generation()
{
    if (roundf(this->m_elapsed.asSeconds()/7) > this->m_waves_nb)
    {
        this->m_waves_nb += 1;
        for (int i = 0; i < m_waves_nb; i++)
        {
            sf::Vector2f pos(rand()-0x3fff, rand()-0x3fff);
            pos = ((rand() % 100) + 800.0f) * util::normalize(pos);
            this->spawn_ennemy(pos + this->m_player->get_pos(),
                               static_cast<e_monsters>(rand() % int(e_monsters::SIZE)));
        }
    }
}
void Application::_update_viewport_movement()
{
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
}
void Application::_update_projectile_creation()
{
    std::vector<SpellType> new_proj = this->m_player->has_to_gen_proj(this->m_elapsed);
    if(new_proj != std::vector<SpellType>())
    {
        for(int i = 0; i < new_proj.size(); i++)
        {
            if(new_proj[i] != SpellType::HOMING || (new_proj[i] == SpellType::HOMING && this->m_ennemies.size() > 0))
                this->m_projectiles.push_back(Projectile(this->m_player->get_pos(), this->m_player->get_walking_angle(), new_proj[i], &this->m_projectile_texture_place_holder));
        }
    }
}
void Application::_update_projectiles(float dt)
{
    for(int i = 0; i < this->m_projectiles.size(); i++){
        if(this->m_projectiles[i].get_type() == SpellType::HOMING)
        {
            // If there are ennemies
            if(this->m_ennemies.size() > 0)
            {
                // Get closest ennemy
                Ennemy closest = this->m_ennemies[0];

                for(Ennemy e: this->m_ennemies)
                    if(util::size(this->m_projectiles[i].get_pos() - e.get_pos()) < util::size(this->m_projectiles[i].get_pos() - closest.get_pos()))
                        closest = e;  

                this->m_projectiles[i].Update(dt, &closest);
            }
            else
            {
                this->m_projectiles[i].Update(dt);
            }
        }
        else
        {
            this->m_projectiles[i].Update(dt);
        }

        float dist_to_player = util::size(this->m_projectiles[i].get_pos() - this->m_player->get_pos());
        // Delete projectile if too far away
        if(dist_to_player > this->m_projectiles[i].DISPAW_DIST)
            this->m_projectiles.erase(this->m_projectiles.begin()+(i--));
        
    }
}
void Application::_update_collisions()
{
    // Ennemy to Player collision
    for (Ennemy& ennemy : this->m_ennemies)
    {
        if (util::square_sdf(this->m_player->get_pos(), this->m_player->get_size()/2.f, ennemy.get_pos()) < Ennemy::BASE_RADIUS/2)
        {
            if (this->m_player->receive_damage(ennemy.get_dmg(), this->m_elapsed)) this->m_window->close();
        }
    }

    // Projectile to Enney collision
    std::vector<Ennemy>::iterator       e;
    std::vector<Projectile>::iterator   p;

    for (e = this->m_ennemies.begin(); e != this->m_ennemies.end(); e++)
    {
        for (p = this->m_projectiles.begin(); p != this->m_projectiles.end(); p++)
        {
            if (util::square_sdf(p->get_pos(), sf::Vector2f(p->WIDTH, p->HEIGHT)/2.f, e->get_pos()) < Ennemy::BASE_RADIUS/2)                                                                                                      
            {
                if (e->deal_damage(p->get_dmg()))
                {
                    
                    this->m_ennemies.erase(e);
                    e--;
                }
                this->m_projectiles.erase(p);
                p--;
            }
        }
    }
    
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

    for (Ennemy ennemy : this->m_ennemies)
        ennemy.draw(this->m_window);
    
    for(Projectile proj : this->m_projectiles)
        proj.Draw(this->m_window);

    this->m_player->Draw(this->m_window);
    
    // Display exp bar

    this->m_window->display();
}

void Application::spawn_ennemy(sf::Vector2f pos, e_monsters type)
{
    this->m_ennemies.push_back(Ennemy(pos, Ennemy::BASE_SPEED, Ennemy::BASE_RADIUS, type));
}

// Accessor
bool Application::is_window_open() const
{
    return this->m_window->isOpen();
}