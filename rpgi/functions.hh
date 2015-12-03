#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include "Player.hh"
#include <vector>
#include <string>

using namespace std;

    bool start_menu();
    bool op(int compare_this, int compare_with);
    vector<string> split(const string& stringToSplit, char charToSplit);
    int endGame();
    void main_lvl_fight(Player player);

#endif // FUNCTIONS_HH
