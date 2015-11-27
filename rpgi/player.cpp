#include "Player.hh"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

Player::Player(string player_name, string class_name, int main_lvl, int hp_lvl,
               int str_lvl, int spd_lvl, int handy_lvl, int all_exp, int phase)
{
    player_name_ = player_name;
    class_name_ = class_name;
    main_lvl_ = main_lvl;
    hp_lvl_ = hp_lvl;
    current_hp_ = hp_lvl_;
    str_lvl_ = str_lvl;
    spd_lvl_ = spd_lvl;
    handy_lvl_ = handy_lvl;
    all_exp_ = all_exp;
    current_phase_ = phase;
    money_ = 0;
}

int Player::print_phase(){
    return current_phase_;
}

int Player::print_main_lvl(){
    return main_lvl_;
}

void Player::show_stats(){
    cout<<"Your stats:\nMain level: "<<main_lvl_<<"\nHp level: "<<hp_lvl_<<"\nStr level: "
       <<str_lvl_<<"\nSpd level: "<<spd_lvl_<<"\nHandy level: "<<handy_lvl_<<"\nAll experience: "
      <<all_exp_<<endl;
}

void Player::show_items(){
    cout<<"Items: none\nMoney: "<<money_<<endl;
}

void Player::give_money(int amount){
    money_ += amount;
}

void Player::check_lvl_up(){
    if (all_exp_ >= 100){
        level_up();
    }
}

void Player::level_up(){
    cout<<"LEVEL UP!\nWhat you want to level up?"<<"\nHp level: "<<hp_lvl_<<"\nStr level: "
       <<str_lvl_<<"\nSpd level: "<<spd_lvl_<<"\nHandy level: "<<handy_lvl_<<endl;
    string answer;
    bool answered = false;
    while(answered == false){
        getline(cin, answer);

        if(answer == "hp" || answer == "Hp"){
            hp_lvl_ ++;
            answered = true;
        }

        else if(answer == "str" || answer == "Str"){
            str_lvl_ ++;
            answered = true;
        }

        else if(answer == "spd" || answer == "Spd"){
            spd_lvl_ ++;
            answered = true;
        }

        else if(answer == "handy" || answer == "Handy"){
            handy_lvl_ ++;
            answered = true;
        }

        else{
            cout<<"Enter one of the levels: hp, str, spd or handy."<<endl;
        }
    }
}
