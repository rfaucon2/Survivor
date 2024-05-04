#include "Player.h"

Player::Player()
{
    this->m_rect = sf::Rect<float>(0, 0, this->WIDTH, this->HEIGHT);
    this->m_speed = 1000;
    this->m_maxhp = Player::BASE_MAXHP;
    this->m_hp = 100;
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