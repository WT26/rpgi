#include "player.hh"
#include "debug.hh"
#include "functions.hh"
#include <unistd.h>
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
    bool trehitcombo_ = false;
}

int Player::print_phase(){
    return current_phase_;
}

int Player::print_main_lvl(){
    return main_lvl_;
}

int Player::print_current_hp(){
    return current_hp_;
}

int Player::print_spd(){
    return spd_lvl_;
}

int Player::print_str(){
    return str_lvl_;
}

int Player::print_handy(){
    return handy_lvl_;
}

string Player::print_name(){
    return player_name_;
}

int Player::handy_tier(){
    int handy_tier;
    if ( handy_lvl_ <=5 ){
        handy_tier = 1;
    }
    else if( handy_lvl_ <= 10 ){
        handy_tier = 3;
    }
    else if( handy_lvl_ <= 15 ){
        handy_tier = 10;
    }
    else if( handy_lvl_ <= 20 ){
        handy_tier = 18;
    }
    else if( handy_lvl_ <= 25 ){
        handy_tier = 24;
    }
    else{
        handy_tier = 30;
    }
    return handy_tier;
}

bool Player::trehit_open(){
    if (trehitcombo_ == true){
        return true;
    }
    else {
        return false;
    }
}

void Player::show_stats(){
    cout<<"\nYour stats:\nMain level: "<<main_lvl_<<"\nHp level: "<<hp_lvl_<<"\nStr level: "
       <<str_lvl_<<"\nSpd level: "<<spd_lvl_<<"\nHandy level: "<<handy_lvl_<<"\nAll experience: "
      <<all_exp_<<"\n\n";
}

void Player::show_items(){
    cout<<"Items: none\nMoney: "<<money_<<endl;
}

void Player::give_money(int amount){
    money_ += amount;
}

void Player::give_xp(int amount){
    all_exp_ += amount;
    if(all_exp_ >= 100){
        all_exp_ -= 100;
        level_up();
    }
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

void Player::player_lose_damage(int damage){
    current_hp_ -= damage;
    if (current_hp_ < 0){
        current_hp_ = 0;
    }
}

void Player::player_died(){
    cout<<"\n"<<endl;
    usleep(200000);
    cout<<"YOU DIED"<<endl;
    usleep(400000);
    bool for_ever{true};
    while(for_ever != false){
        cout<<"main menu or end"<<endl;
        string command{"twentysix"};
        getline(cin, command);

        if(command == "main menu"){
            start_menu();
        }
        else if(command == "end"){
            endGame();
        }
        else if(command == "debug"){
            Debug debug();
        }
    }
}

Player Player::react_to_damage(Player player, int enemy_damage, vector<string> handy_attacks, string enemy_name){
        cout<<enemy_name<<" "<<handy_attacks[rand()% (handy_attacks.size()-1)]<<endl;
        cout<<"Enemy did "<<enemy_damage<<" to you."<<endl;
        player.player_lose_damage(enemy_damage);
        cout<<"Your current hp: "<<player.print_current_hp()<<endl;
        sleep(2);
        if(player.print_current_hp() <= 0){
            player.player_died();
        }
        return player;
        }

