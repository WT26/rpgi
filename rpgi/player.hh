#ifndef PLAYER_HH
#define PLAYER_HH

#include <time.h>
#include <string>
#include <vector>

using namespace std;

class Player
{
public:
    Player(string player_name, string class_name, int main_lvl, int hp_lvl,
           int str_lvl, int spd_lvl, int handy_lvl, int all_exp, int phase,
           int elapsed_time, int current_hp, int money,
           int i_1, int i_2, int i_3, int i_4, int i_5, int i_6, int i_7, int i_8, int i_9, int i_10);



    int print_phase();
    int print_main_lvl();
    int print_current_hp();
    int print_spd();
    int print_str();
    int print_handy();
    int handy_tier();
    int give_id(int item_slot);
    int show_first_empty_inv_space();

    string print_name();

    void used_item(bool booolean);

    void start_clock();
    void show_stats();
    void show_items();
    void give_money(int amount);
    void give_xp(int amount);
    void give_hp(int amount);
    void check_lvl_up();
    void level_up();
    void player_lose_damage(int damage);
    void player_died();
    void update_time_elapsed();
    string player_seconds_minutes_hours();
    void give_extra_damage(int amount);
    void delete_item(int slot);
    void give_item(int slot, int id);
    void show_all_info();
    void pay(int amount);

    bool have_used_item();
    bool inventory_full();
    bool enough_money(int amount);

    double seconds_elapsed();

    void update_phase(int phase_number);

    string save_header();
    string get_save_info();

    Player react_to_damage(Player player, int enemy_damage, vector<string> handy_attacks, string enemy_name);
    Player react_to_boss_damage(Player player, int enemy_damage);



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
    int elapsed_sofar_;
    int extra_damage_holder_;
    time_t start_time_;

    bool just_used_item;

    int total_commands_;

    int item_1_;
    int item_2_;
    int item_3_;
    int item_4_;
    int item_5_;
    int item_6_;
    int item_7_;
    int item_8_;
    int item_9_;
    int item_10_;

    int extra_damage_;

    int carry_enemy_health_;


};

#endif // PLAYER_HH
