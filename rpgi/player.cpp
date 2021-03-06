#include "player.hh"
#include "debug.hh"
#include "functions.hh"
#include "item.hh"
#include <unistd.h>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

Player::Player(string player_name, string class_name, int main_lvl, int hp_lvl,
               int str_lvl, int spd_lvl, int handy_lvl, int all_exp, int phase, int elapsed_time, int current_hp, int money,
               int i_1, int i_2, int i_3, int i_4, int i_5, int i_6, int i_7, int i_8, int i_9, int i_10, int caeco_visited)
{
    player_name_ = player_name;
    class_name_ = class_name;
    main_lvl_ = main_lvl;
    hp_lvl_ = hp_lvl;
    current_hp_ = current_hp;
    str_lvl_ = str_lvl;
    spd_lvl_ = spd_lvl;
    handy_lvl_ = handy_lvl;
    all_exp_ = all_exp;
    current_phase_ = phase;
    money_ = money;
    start_time_ = time(0);
    elapsed_sofar_ = elapsed_time;
    just_used_item = false;
    extra_damage_holder_;

    item_1_ = i_1;
    item_2_ = i_2;
    item_3_ = i_3;
    item_4_ = i_4;
    item_5_ = i_5;
    item_6_ = i_6;
    item_7_ = i_7;
    item_8_ = i_8;
    item_9_ = i_9;
    item_10_ = i_10;

    extra_damage_ = 0;

    if(caeco_visited == 0){
        caeco_intro_ = false;
    }
    else{
        caeco_intro_ = true;
    }
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
    if ( handy_lvl_ <=5 && handy_lvl_ >0){
        handy_tier = 1;
    }
    else if( handy_lvl_ > 5 && handy_lvl_ <= 10  ){
        handy_tier = 3;
    }
    else if( handy_lvl_ <= 15 && handy_lvl_ > 10){
        handy_tier = 6;
    }
    else if( handy_lvl_ <= 20 && handy_lvl_ > 15){
        handy_tier = 9;
    }
    else if( handy_lvl_ <= 25 && handy_lvl_ > 20){
        handy_tier = 12;
    }
    else{
        handy_tier = 15;
    }
    return handy_tier;
}

void Player::start_clock(){
    time_t start = time(0);
    start_time_ = start;
}

void Player::show_stats(){
    update_time_elapsed();
    string complete_time = player_seconds_minutes_hours();
    cout<<"\nYour stats:\nMain level: "<<main_lvl_<<"\nHp level: "<<hp_lvl_<<"\nStr level: "
       <<str_lvl_<<"\nSpd level: "<<spd_lvl_<<"\nHandy level: "<<handy_lvl_<<"\nAll experience: "
      <<all_exp_<<"\nMoney: "<<money_<<"\nCurrent hp: "<<current_hp_<<"/"<<hp_lvl_<<"\nTotal playtime: " <<complete_time<< "\n\n";
}

void Player::show_items(){
        letter_by_letter_super_fast("\n1. " + give_items_name(item_1_) + "\n2. " + give_items_name(item_2_)
                                    + "\n3. " + give_items_name(item_3_) + "\n4. " + give_items_name(item_4_)
                                    + "\n5. " + give_items_name(item_5_) + "\n6. " + give_items_name(item_6_)
                                    + "\n7. " + give_items_name(item_7_) + "\n8. " + give_items_name(item_8_)
                                    + "\n9. " + give_items_name(item_9_) + "\n10. " + give_items_name(item_10_)
                                   + "\n");
}

void Player::give_money(int amount){
    money_ += amount;
}

void Player::give_xp(int amount){
    all_exp_ += amount;
    if(all_exp_ >= 30 && main_lvl_ == 10 ){
        level_up();
    }
    else if(all_exp_ >= 60 && main_lvl_ == 11 ){
        level_up();
    }
    else if(all_exp_ >= 90 && main_lvl_ == 12 ){
        level_up();
    }
    else if(all_exp_ >= 100){
        all_exp_ -= 100;
        level_up();
    }
}

void Player::check_lvl_up(){
    if(main_lvl_ == 10 && all_exp_ >= 30){
        level_up();
    }
    else if(main_lvl_ == 11 && all_exp_ >= 60){
        level_up();
    }
    else if (main_lvl_ == 12 && all_exp_ >= 90){
        level_up();
    }
    else if (all_exp_ >= 100){
        level_up();
    }
    return;
}


double Player::seconds_elapsed(){
    double seconds_elapsed_since_start = difftime(time(0), start_time_);
    seconds_elapsed_since_start += elapsed_sofar_;
    return seconds_elapsed_since_start;
}


void Player::update_time_elapsed(){
    elapsed_sofar_ += difftime( time(0), start_time_ );
    start_time_ = time(0);
}


string Player::get_save_info(){
    update_time_elapsed();
    string save_info;
    save_info += player_name_ + ":" + class_name_ + ":" + to_string(main_lvl_) + ":" + to_string(hp_lvl_) + ":"
            + to_string(str_lvl_) + ":" + to_string(spd_lvl_) + ":" + to_string(handy_lvl_) + ":" + to_string(all_exp_) +
            ":" + to_string(current_phase_) + ":" + to_string(elapsed_sofar_) + ":" + to_string(current_hp_)
            + ":" + to_string(money_) + ":" + to_string(item_1_) + ":" + to_string(item_2_) + ":" + to_string(item_3_)
             + ":" + to_string(item_4_) + ":" + to_string(item_5_) + ":" + to_string(item_6_) + ":" + to_string(item_7_)
             + ":" + to_string(item_8_) + ":" + to_string(item_9_) + ":" + to_string(item_10_);
    return save_info;
}


void Player::level_up(){
    letter_by_letter_slow("\n\nLEVEL UP ! ! You are now level " + to_string(main_lvl_ + 1) + "!");
    letter_by_letter_fast("\nWhat you want to level up?");
    letter_by_letter_very_fast("\n1. Hp level: " + to_string(hp_lvl_) + "\n2. Str level: " + to_string(str_lvl_) +
                               "\n3. Spd level: " + to_string(spd_lvl_) + "\n4. Handy level: " + to_string(handy_lvl_) + "\n");
    string answer;
    bool answered = false;
    while(answered == false){
        getline(cin, answer);

        if(answer == "hp" || answer == "Hp" || answer == "1"
                || answer == "1."){
            hp_lvl_ ++;
            main_lvl_++;
            answered = true;
        }

        else if(answer == "str" || answer == "Str" || answer == "2"
                || answer == "2."){
            str_lvl_ ++;
            main_lvl_++;
            answered = true;
        }

        else if(answer == "spd" || answer == "Spd" || answer == "3"
                || answer == "3.."){
            spd_lvl_ ++;
            main_lvl_++;
            answered = true;
        }

        else if(answer == "handy" || answer == "Handy" || answer == "4"
                || answer == "4."){
            handy_lvl_ ++;
            main_lvl_++;
            answered = true;
        }

        else{
            letter_by_letter_very_fast("Enter one of the levels: hp, str, spd or handy.\n");
        }
    }
    current_hp_ = hp_lvl_;
}


void Player::player_lose_damage(int damage){
    current_hp_ -= damage;
    if (current_hp_ < 0){
        current_hp_ = 0;
    }
}


void Player::player_died(){
    cout<<"\n\n";
    usleep(200000);
    letter_by_letter_slow("YOU DIED\n");
    usleep(400000);
    bool for_ever{true};
    while(for_ever != false){
        letter_by_letter_fast("\n1. Main Menu\n2. End\n\ncommand >");
        string command{"twentysix"};
        getline(cin, command);

        if(command == "main menu" || command == "Main menu" || command == "1."
                || command  == "1"){
            start_menu();
        }
        else if(command == "end" || command == "e" || command == "2."
                || command == "2"){
            endGame();
        }
        else if(command == "debug"){
            Debug debug();
        }
    }
}

Player Player::react_to_damage(Player player, int enemy_damage, vector<string> handy_attacks, string enemy_name){
        letter_by_letter_fast(enemy_name + " " + handy_attacks[rand()% (handy_attacks.size()-1)] + "\n") ;
        letter_by_letter_fast("Enemy did " + to_string(enemy_damage) + " to you.\n");
        player.player_lose_damage(enemy_damage);
        letter_by_letter_fast("Your current hp: " + to_string(player.print_current_hp()));
        cout<<"\n";
        sleep(2);
        if(player.print_current_hp() <= 0){
            player.player_died();
        }
        return player;
}

string Player::save_header(){
    return string {"  Name: " + player_name_ + "  Main Level: " + to_string(main_lvl_)};
}


void Player::update_phase(int phase_number){
    current_phase_ = phase_number;
}

string Player::player_seconds_minutes_hours(){
    int total_seconds = elapsed_sofar_;
    int hours = total_seconds / 60 / 60;
    total_seconds -= 60 * 60 * hours;
    int minutes = total_seconds / 60;
    total_seconds -= minutes * 60;

    string complete_string = "Hours: " + to_string(hours) + "  Minutes: " + to_string(minutes) + "  Seconds: " + to_string(total_seconds);
    return complete_string;
}


 void Player::give_hp(int amount){
    current_hp_ += amount;
    if (current_hp_ >= hp_lvl_){
        current_hp_ = hp_lvl_;
    }
}

void Player::used_item(bool booolean){
    just_used_item = booolean;
}


bool Player::have_used_item(){
    return just_used_item;
}


int Player::give_id(int item_slot){
    if(item_slot == 1){
        return item_1_;
    }
    else if(item_slot == 2){
        return item_2_;
    }
    else if(item_slot == 3){
        return item_3_;
    }
    else if(item_slot == 4){
        return item_4_;
    }
    else if(item_slot == 5){
        return item_5_;
    }
    else if(item_slot == 6){
        return item_6_;
    }
    else if(item_slot == 7){
        return item_7_;
    }
    else if(item_slot == 8){
        return item_8_;
    }
    else if(item_slot == 10){
        return item_9_;
    }
    else if(item_slot == 10){
        return item_10_;
    }
    else{
        return 0;
    }
}


void Player::give_extra_damage(int amount){
    extra_damage_holder_ = amount;
}


void Player::delete_item(int item_slot){
    if(item_slot == 1){
        item_1_ = 0;
    }
    else if(item_slot == 2){
        item_2_ = 0;
    }
    else if(item_slot == 3){
        item_3_ = 0;
    }
    else if(item_slot == 4){
        item_4_ = 0;
    }
    else if(item_slot == 5){
        item_5_ = 0;
    }
    else if(item_slot == 6){
        item_6_ = 0;
    }
    else if(item_slot == 7){
        item_7_ = 0;
    }
    else if(item_slot == 8){
        item_8_ = 0;
    }
    else if(item_slot == 10){
        item_9_ = 0;
    }
    else if(item_slot == 10){
        item_10_ = 0;
    }
}

bool Player::inventory_full(){
    if(item_1_ != 0 && item_2_ != 0 &&
       item_3_ != 0 && item_4_ != 0 &&
       item_5_ != 0 && item_6_ != 0 &&
       item_7_ != 0 && item_8_ != 0 &&
       item_9_ != 0 && item_10_ != 0){
        return true;
    }
    else {
        return false;
    }
}


int Player::show_first_empty_inv_space(){
    if(item_1_ == 0){
        return 1;
    }
    else if(item_2_ == 0){
        return 2;
    }
    else if(item_3_ == 0){
        return 3;
    }
    else if(item_4_ == 0){
        return 4;
    }
    else if(item_5_ == 0){
        return 5;
    }
    else if(item_6_ == 0){
        return 6;
    }
    else if(item_7_ == 0){
        return 7;
    }
    else if(item_8_ == 0){
        return 8;
    }
    else if(item_9_ == 0){
        return 9;
    }
    else if(item_10_ == 0){
        return 10;
    }
}



void Player::give_item(int item_slot, int id){
    if(item_slot == 1){
        item_1_ = id;
    }
    else if(item_slot == 2){
        item_2_ = id;
    }
    else if(item_slot == 3){
        item_3_ = id;
    }
    else if(item_slot == 4){
        item_4_ = id;
    }
    else if(item_slot == 5){
        item_5_ = id;
    }
    else if(item_slot == 6){
        item_6_ = id;
    }
    else if(item_slot == 7){
        item_7_ = id;
    }
    else if(item_slot == 8){
        item_8_ = id;
    }
    else if(item_slot == 10){
        item_9_ = id;
    }
    else if(item_slot == 10){
        item_10_ = id;
    }
}


Player Player::react_to_boss_damage(Player player, int enemy_damage){
    player.player_lose_damage(enemy_damage);
    letter_by_letter_fast("Your current hp: " + to_string(player.print_current_hp()));
    cout<<"\n";
    sleep(2);
    if(player.print_current_hp() <= 0){
        player.player_died();
    }
    return player;
}


void Player::show_all_info(){
    cout<<"\n########################INFO######################\n";
    usleep(5000);
    int space_count = 50 - player_name_.length() - class_name_.length() - 18;
    string spaces = give_spaces(space_count);
    cout<<"# Name: "<<player_name_<<spaces<<" Class: "<<class_name_<<" #\n";
    usleep(5000);
    space_count = 50 - 16 - to_string(main_lvl_).length();
    spaces = give_spaces(space_count);
    cout<<"# Main level: "<<main_lvl_<<spaces<<" #\n";
    usleep(5000);
    space_count = 50 - 25 - to_string(hp_lvl_).length() - to_string(str_lvl_).length();
    spaces = give_spaces(space_count);
    cout<<"# Hp level: "<<hp_lvl_<<spaces<<"Str level: "<<str_lvl_<<" #\n";
    usleep(5000);
    space_count = 50 - 28 - to_string(spd_lvl_).length() - to_string(handy_lvl_).length();
    spaces = give_spaces(space_count);
    cout<<"# Spd level: "<<spd_lvl_<<spaces<<"Handy level: "<<handy_lvl_<<" #\n";
    usleep(5000);
    space_count = 50 - 23 - to_string(current_hp_).length() - to_string(hp_lvl_).length() - to_string(all_exp_).length();
    spaces = give_spaces(space_count);
    cout<<"# HP LEFT: "<<current_hp_<<"/"<<hp_lvl_<<spaces<<"ALL EXP: "<<all_exp_<<" #\n";
    usleep(5000);
    space_count = 50 - 11 - to_string(money_).length();
    spaces = give_spaces(space_count);
    cout<<"# Money: "<<money_<<spaces<<" #\n";
    usleep(5000);
    cout<<"####################INVENTORY#####################";
    usleep(5000);
    show_items();
    cout<<"##################################################\n\n";
    usleep(5000);
}


bool Player::enough_money(int amount){
    if(amount > money_){
        return false;
    }
    else{
        return true;
    }
}


void Player::pay(int amount){
    money_ -= amount;
}

bool Player::give_caeco_intro(){
    return caeco_intro_;
}

void Player::caeco_intro_change(){
    caeco_intro_ = true;
}

