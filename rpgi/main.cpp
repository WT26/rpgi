#include <iostream>
#include "functions.hh"

using namespace std;

int main()
{
    bool game_is_on = true;
    while(game_is_on == true){
        if (start_menu() == false){
            game_is_on = false;
        }
    }
}

