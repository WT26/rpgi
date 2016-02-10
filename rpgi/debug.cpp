#include "debug.hh"
#include "player.hh"
#include "phasehandler.hh"
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

Debug::Debug()
{
    debugger();
}

void Debug::debugger(){
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

    string temporary;

    cout<<"main level? ";
    getline(cin, temporary);
    main_lvl = stoi(temporary);

    cout<<"hp level? ";
    getline(cin, temporary);
    hp_lvl = stoi(temporary);

    cout<<"str level? ";
    getline(cin, temporary);
    str_lvl = stoi(temporary);

    cout<<"spd level? ";
    getline(cin, temporary);
    spd_lvl = stoi(temporary);

    cout<<"handy level? ";
    getline(cin, temporary);
    handy_lvl = stoi(temporary);

    cout<<"Phase? ";
    getline(cin, temporary);
    skip_to_phase = stoi(temporary);

    time_t elapsed_time = time(0);
    int current_hp = hp_lvl;

    cout<<"Money? ";
    getline(cin, temporary);
    int money = stoi(temporary);

    cout<<"Items? ";
    getline(cin, temporary);
    int item = stoi(temporary);
    Player player = Player(name, class_name, main_lvl, hp_lvl, str_lvl, spd_lvl,
                           handy_lvl, 0, skip_to_phase, elapsed_time, current_hp, money,
                           item, item, item, item, item, item, item, item, item, item, 0);

    phasehandler(player);
}

