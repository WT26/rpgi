#include "debug.hh"
#include "Player.hh"
#include "phasehandler.hh"
#include <iostream>
#include <string>

using namespace std;

debug::debug()
{
    string name;
    string class_name;
    int main_lvl;
    int hp_lvl;
    int str_lvl;
    int spd_lvl;
    int handy_lvl;
    int skip_to_phase;
    cout<<"..starting debug. Name? ";
    getline(cin, name);

    cout<<"class? (Salto, Piger, Curator, ensis) ";
    getline(cin, class_name);

    cout<<"main level? ";
    getline(cin, main_lvl);

    cout<<"hp level? ";
    getline(cin, hp_lvl);

    cout<<"str level? ";
    getline(cin, str_lvl);

    cout<<"spd level? ";
    getline(cin, spd_lvl);

    cout<<"handy level? ";
    getline(cin, handy_lvl);

    cout<<"Phase? ";
    getline(cin, skip_to_phase);

    Player player = Player(name, class_name, main_lvl, hp_lvl, str_lvl, spd_lvl, handy_lvl, 0, skip_to_phase);

    phasehandler(player);
}

