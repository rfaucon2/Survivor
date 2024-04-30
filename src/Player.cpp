#include "Player.h"

Player::Player()
{
    this->m_rect = sf::Rect<float>(0, 0, this->WIDTH, this->HEIGHT);
    this->m_speed = 1000;
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
    sf::RectangleShape rs(this->m_rect.getSize());
    rs.setPosition(this->m_rect.getPosition());
    rs.setFillColor(sf::Color::Cyan);
    rs.setOrigin(this->m_rect.getSize() / 2.f);

    target->draw(rs);
}

sf::Vector2f Player::get_pos() const
{
    return this->m_rect.getPosition();
}
sf::Vector2f Player::get_size() const
{
    return this->m_rect.getSize();
}