#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include "player.hh"
#include <vector>
#include <string>

using namespace std;

    bool start_menu();
    bool op(int compare_this, int compare_with);
    vector<string> split(const string& stringToSplit, char charToSplit);
    int endGame();
    void main_lvl_fight(Player player);
    void main_fight_won(Player player);
    int main_fight_won_money(Player player);
    int main_fight_won_xp(Player player);

#endif // FUNCTIONS_HH
