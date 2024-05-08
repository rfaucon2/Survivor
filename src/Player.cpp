#include "Player.h"

Player::Player()
{
    // World related variables
    this->m_rect = sf::Rect<float>(0, 0, this->WIDTH, this->HEIGHT);
    this->m_speed = 1000;
    // Health variables
    this->m_maxhp = Player::BASE_MAXHP;
    this->m_hp = 100;
    // Level variables
    this->m_level = 1;
    this->m_exp = 0;
    // Spell variables
    std::vector<SpellType> m_available_spells = {SpellType::CHICKEN};
    std::vector<float> m_acquisition_time = {0.f};
    std::vector<float> m_spell_dmg_mult = {1.0};
    std::vector<float> m_spell_cdr_mult = {1.0};
}

void Player::Update(float dt)
{
    sf::Vector2f dp(0, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        dp.y -= 1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        dp.y += 1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        dp.x -= 1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        dp.x += 1;

    dp = util::normalize(dp) * dt * this->m_speed;
    this->m_rect.top += dp.y;
    this->m_rect.left += dp.x;
}
void Player::Draw(sf::RenderTarget* target)
{
    // Draw player
    sf::RectangleShape body(this->m_rect.getSize());
    body.setPosition(this->m_rect.getPosition());
    body.setFillColor(sf::Color::Cyan);
    body.setOrigin(this->m_rect.getSize() / 2.f);

    target->draw(body);

    // Draw lifebar
    sf::RectangleShape lifebar;
    const float BASE_WIDTH = this->m_rect.getSize().x * 1.6f;
    float bar_width = BASE_WIDTH * (this->m_maxhp / Player::BASE_MAXHP);
    lifebar.setFillColor(sf::Color(100, 0, 0));
    lifebar.setSize(sf::Vector2f(bar_width, 10));
    lifebar.setPosition(sf::Vector2f(body.getPosition().x - (bar_width / 2),
                                     body.getPosition().y - (Player::HEIGHT/2) - 30));
    target->draw(lifebar); // Draw the darkned part of the lifebar

    lifebar.setSize(sf::Vector2f(bar_width * ((float)this->m_hp / (float)this->m_maxhp), 10));
    lifebar.setFillColor(sf::Color(200, 0, 0));

    target->draw(lifebar); // Draw the remaining part of the lifebar

}
SpellType Player::has_to_gen_proj(sf::Time since_start)
{
    
    return SpellType::NONE;
}

void Player::give_exp(unsigned int exp, sf::Time time)
{
    // Give exp
    this->m_exp += exp;

    // Check for level up
    int thresh = int((float)Player::LVL_UP_THRESH * pow(Player::THRESH_MULTIPLIER, this->m_level - 1));
    
    if(this->m_exp >= thresh)
        return; // No level up
    

    // Update exp and level
    this->m_exp -= thresh;
    this->m_level += 1;

    // Update HP
    this->m_maxhp *= Player::HP_MULTIPLIER;
    this->m_hp *= Player::HP_MULTIPLIER;

    // Check if new spell acquiered
    int current_spell_count = this->m_available_spells.size();
    SpellType next_spell_id = static_cast<SpellType>(current_spell_count);
    
    // Check if there is no more spell to learn
    if((int)next_spell_id >= spell_data.size())
        return; // No more spell
    
    // Check if player has lhe requiered level
    std::vector<float> data = spell_data.at(next_spell_id);
    if(this->m_level >= data[0])
    {
        this->m_available_spells.push_back(next_spell_id);
        this->m_acquisition_time.push_back(time.asSeconds());
        this->m_spell_dmg_mult.push_back(1.f);
        this->m_spell_cdr_mult.push_back(1.f);
    }
}


sf::Vector2f Player::get_pos() const
{
    return this->m_rect.getPosition();
}
sf::Vector2f Player::get_size() const
{
    return this->m_rect.getSize();
}
int Player::get_hp() const
{
    return this->m_hp;
}
int Player::get_maxhp() const
{
    return this->m_maxhp;
}


Projectile::Projectile(sf::Vector2f start_pos, float angle, float dmg, SpellType type, sf::Texture* tex)
{
    this->m_pos = start_pos;
    this->m_speed = sf::Vector2f(cos(angle), sin(angle)) * Projectile::SPEED;
    this->m_dmg = dmg;
    this->m_type = type;
    
}
Projectile::~Projectile()
{

}

void Projectile::Update(float dt)
{
    this->m_pos += this->m_speed * dt;
}
void Projectile::Draw(sf::RenderTarget* target)
{

}