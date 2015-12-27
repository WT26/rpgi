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
    int main_fight_won_money(Player player);
    int main_fight_won_xp(Player player);
    int enemy_did_damage(int enemy_str, int handy_tier, double const ENEMY_DAMAGE_PERCENT, int WAIT_TIME);
    int player_did_damage(Player player, double const PLAYER_DAMAGE_PERCENT, int WAIT_TIME);
    int player_attack_done(int enemy_hp, int player_attack_count, int WAIT_TIME);

    bool file_exists(string file_name);

    void save_game(Player player);

#endif // FUNCTIONS_HH
