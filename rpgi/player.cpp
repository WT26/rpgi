#include "Player.hh"

Player::Player(string player_name, string class_name, int main_lvl, int hp_lvl,
               int str_lvl, int spd_lvl, int handy_lvl, int all_exp, int phase)
{
    player_name_ = player_name;
    class_name_ = class_name;
    main_lvl_ = main_lvl;
    hp_lvl_ = hp_lvl;
    str_lvl_ = str_lvl;
    spd_lvl_ = spd_lvl;
    handy_lvl_ = handy_lvl;
    all_exp_ = all_exp;
    current_phase_ = phase;
}

int Player::give_phase(){
    return current_phase_;
}

