#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include "player.hh"
#include <vector>
#include <string>

using namespace std;

    bool start_menu();
    bool op(int compare_this, int compare_with);
    bool enemy_hp_out(int enemy_hp, int WAIT_TIME);
    vector<string> split(const string& stringToSplit, char charToSplit);
    int endGame();

    Player main_lvl_fight(Player player);
    Player main_fight_won(Player player);
    Player item_shop(Player player);

    int main_fight_won_money(Player player);
    int main_fight_won_xp(Player player);
    int enemy_did_damage(int enemy_str, int handy_tier, double const ENEMY_DAMAGE_PERCENT, int WAIT_TIME);
    int player_did_damage(Player player, double const PLAYER_DAMAGE_PERCENT, int WAIT_TIME);
    int player_attack_done(int enemy_hp, int player_attack_count, int WAIT_TIME);

    string give_spaces(int amount);

    void letter_by_letter_slow(string string_to_print);
    void letter_by_letter_very_slow(string string_to_print);
    void letter_by_letter_fast(string string_to_print);
    void letter_by_letter_very_fast(string string_to_print);
    void letter_by_letter_super_fast(string string_to_print);

    void fight_started_message();
    void fight_ended_message();
    void box_message(string message);

    void cart_talk_tree(Player player);

    Player boss_fight_1(Player player);
    bool boss_1_hp_out(int enemy_hp, int WAIT_TIME);
    void boss_fight_1_won(Player player);

    string seconds_minutes_hours(int seconds);

    bool file_exists(string file_name);

    void save_game(Player player);
    void load_game();

    Player relego_turn(Player player, int enemy_turn);
#endif // FUNCTIONS_HH
