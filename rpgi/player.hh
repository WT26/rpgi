#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

using namespace std;

class Player
{
public:
    Player(string player_name, string class_name, int main_lvl, int hp_lvl,
           int str_lvl, int spd_lvl, int handy_lvl, int all_exp, int phase);
    int print_phase();
    int print_main_lvl();
    int print_current_hp();
    int print_spd();
    int print_str();
    int print_handy();
    void show_stats();
    void show_items();
    void give_money(int amount);
    void check_lvl_up();
    void level_up();
    bool trehit_open();



private:
    string player_name_;
    string class_name_;
    int main_lvl_;
    int hp_lvl_;
    int current_hp_;
    int str_lvl_;
    int spd_lvl_;
    int handy_lvl_;
    int all_exp_;
    int current_phase_;
    int money_;
    bool trehitcombo_;
};

#endif // PLAYER_HH
