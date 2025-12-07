#include "player.h"
#include "boss.h"

void updatelife(volatile Player* p) {
    int percent = p->life / 10;
    if (percent > 10) percent = 10;
    if (percent < 0) percent = 0;

    int mask = (1 << percent) - 1;
    LED_ADDR = mask;
}

void player_attack(volatile Player* p, volatile Boss* b) // Player attacks boss
{
    change_boss_life(b, -p->damage);
}

void change_player_life(volatile Player* p, int delta) {
    p->life += delta;
    if (p->life < 0) p->life = 0; // Stoppar negativa värden
    updatelife(p);
}

void change_damage(volatile Player* p, int damage) // Change player's damage
{
    p->damage += damage;
}

void change_protection(volatile Player* p, int protection) // Change player's protection
{
    p->protection += protection;
}
