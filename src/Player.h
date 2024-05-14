#ifndef PLAYER
#define PLAYER

#include "Utilitary.h"
#include "Ennemy.h"

enum class SpellType
{
    NONE = -1, // returned by Player::has_to_gen_proj when no projectile has to be fired
    CHICKEN = 0,
    STRAIGHT = 1,
    HOMMING = 2,
    BLAST = 3
};

const std::unordered_map<SpellType, std::vector<float>> spell_data
{ // {Spell, {lvl of acquisition, base dmg, base cd (in second)}}
    {SpellType::CHICKEN, {1.f, 5.f, 0.8f}},
    {SpellType::STRAIGHT, {2.f, 10.f, 1.f}},
    {SpellType::HOMMING, {4.f, 10.f, 1.2f}},
    {SpellType::BLAST, {8.f, 10.f, 1.6f}}
};


class Player
{
public: // Class constants
    const float WIDTH               = 35;
    const float HEIGHT              = 70;
    const int   BASE_MAXHP          = 100;
    const float HP_MULTIPLIER       = 1.1f;
    const int   LVL_UP_THRESH       = 100;
    const float THRESH_MULTIPLIER   = 1.3f;

private:
    // World related variables
    sf::Rect<float> m_rect;
    float           m_speed;
    float           m_walking_angle;
    // Health variables
    int             m_maxhp;
    int             m_hp;
    // Level variables
    unsigned int    m_level;
    unsigned int    m_exp;
    // Spell variables
    std::vector<SpellType>  m_available_spells;
    std::vector<float>      m_acquisition_time;
    std::vector<float>      m_spell_dmg_mult;
    std::vector<float>      m_spell_cdr_mult; // cooldown reduction multiplier

    sf::Time    m_last_hit_time;
    float       m_hit_cd; // as seconds

public:
    Player();
    
    void Update(float dt);
    void Draw(sf::RenderTarget* target);
    std::vector<SpellType> has_to_gen_proj(sf::Time since_start);

    void give_exp(unsigned int exp, sf::Time time);

    // Accessors
    sf::Vector2f get_pos() const;
    sf::Vector2f get_size() const;
    int get_hp() const;
    int get_maxhp() const;
    float get_walking_angle() const;

    bool receive_damage(int damage, sf::Time current_time);
};

class Projectile
{
public:
    static const float DISPAW_DIST;
    static const float SPEED;
    static const float WIDTH;
    static const float HEIGHT;
private:

    SpellType       m_type;
    float           m_dmg;
    sf::Vector2f    m_pos;
    sf::Vector2f    m_speed;
    sf::Sprite      m_sprite;

public:
    Projectile(sf::Vector2f start_pos, float angle, SpellType type, sf::Texture* tex);
    ~Projectile();

    void Update(float dt, Ennemy* target = nullptr);
    void Draw(sf::RenderTarget* target);

    sf::Vector2f get_pos() const;
    SpellType get_type() const;
};

#endif