#include "functions.hh"
#include "phasehandler.hh"
#include "player.hh"
#include "debug.hh"
#include "item.hh"
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>


using namespace std;

bool start_menu(){
    vector<string> commands{"new game", "load game", "quit"};
    string command;
    box_message("#                   START MENU                   #");
    letter_by_letter_very_fast("\n1. New Game\n2. Load Game\n3. Quit Game\n");
    cout<<"\ncommand >";

    bool end_game{false};
    while(end_game != true){
        getline(cin, command);

        if(command == "new game" || command == "New game"
                || command == "1"|| command == "1."){
            phase_1();
        }
        else if(command == "load game" || command == "Load game"
                || command == "2" || command == "2.") {
            load_game();
        }
        else if(command == "quit" || command == "Quit"
                || command == "3"|| command == "3."){
            endGame();
            return false;
        }
        else if(command == "debug"){
            Debug debug = Debug();
        }
        else{
            letter_by_letter_very_fast("\nWrong command, all commands:\n1. new game\n2. load game\n3. quit\n");
        }
    }
    return false;
}

vector<string> split(const string& merkkijono, char erotinmerkki) {
    vector<string> tulos;

    string::size_type tutkittava_kohta{0};
    string kentan_sisalto{""};

    while ( tutkittava_kohta < merkkijono.length() ) {

        if ( merkkijono.at(tutkittava_kohta) != erotinmerkki ) {
            kentan_sisalto.push_back( merkkijono.at(tutkittava_kohta) );

        } else {

            tulos.push_back(kentan_sisalto);
            kentan_sisalto = "";
        }

        ++tutkittava_kohta;
    }

    tulos.push_back(kentan_sisalto);

    return tulos;
}

int endGame(){
    exit(0);
}

Player main_lvl_fight(Player player){
    fight_started_message();
    srand(time(NULL));

    int main_lvl = player.print_main_lvl();
    int enemy_lvl = main_lvl - 3 + rand()%6;
    vector<string> animal{"Bird", "Dog", "Cat", "Cow", "Bat", "Mole", "Bunny", "Rabbit", "Monkey"};
    vector<string> adjective{"Mystery", "Epic", "Baby", "Little", "Weird", "Silent", "Angry", "Massive", "Gentle"};
    string enemy_name = adjective[rand()%9] + " " + animal[rand()%9];


    int enemy_hp = rand()%enemy_lvl;
    int enemy_str = rand()%(enemy_lvl - enemy_hp);
    int enemy_spd = rand()%(enemy_lvl - enemy_hp - enemy_str);
    int enemy_handy = rand()%(enemy_lvl - enemy_hp - enemy_str - enemy_spd);

    if(main_lvl <= 15){
        enemy_hp++;
        enemy_str++;
        enemy_spd++;
        enemy_handy++;
    }
    else if(main_lvl <= 20){
        enemy_hp += 3;
        enemy_str += 3;
        enemy_spd += 3;
        enemy_handy += 3;
    }
    else if(main_lvl <= 25){
         enemy_hp += 5;
         enemy_str += 5;
         enemy_spd += 5;
         enemy_handy += 5;
    }

    int enemy_handy_tier;
    int player_attack_count;
    vector<string> handy_attacks;

    double const PLAYER_DMG_PERCENT{1.2};
    double const ENEMY_DMG_PERCENT{1};
    int WAIT_TIME{2};

    if(enemy_handy >= 8 && enemy_handy < 15){
        handy_attacks.push_back("slapped you!");
        handy_attacks.push_back("tackled you!");
        enemy_handy_tier = 5;
    }
    else if(enemy_handy >= 15 && enemy_handy < 20){
        handy_attacks.push_back("hit you with stick!");
        handy_attacks.push_back("hit you with rock!");
        handy_attacks.push_back("throwed dirt at you!");
        enemy_handy_tier = 7;
    }
    else if(enemy_handy >= 20 && enemy_handy < 25){
        handy_attacks.push_back("hit you with metal stick!");
        handy_attacks.push_back("throwed firey ball at you!");
        handy_attacks.push_back("throwed glowing rock at you!");
        enemy_handy_tier = 11;
    }
    else {
        handy_attacks.push_back("swiped you!");
        handy_attacks.push_back("hit you!");
        handy_attacks.push_back("striked you!");
        handy_attacks.push_back("bit you!");
        handy_attacks.push_back("smashed you!");
        handy_attacks.push_back("punched you!");
        enemy_handy_tier = 1;
    }

    bool enemy_alive = true;

    if(enemy_alive == true && player.print_current_hp() > 0){

        string command{"twentysix"};
        letter_by_letter_fast("\nYou encounter " + enemy_name + "!" );
        letter_by_letter_very_fast(" Its lvl " + to_string(enemy_lvl) + "!\n");

        while(enemy_alive == true && player.print_current_hp() > 0){
            letter_by_letter_very_fast("\nWhat you want to do?");
            cout<<"\ncommand >";
            getline(cin, command);

            if (command == "attack" || command == "a" || command == "A" || command == "Attack"
                     || command == "1."  || command == "1"){
                int player_damage{0};
                int enemy_damage{0};


                // Enemy faster
                if (enemy_spd > player.print_spd() || rand()% 100 > 95){
                    //Enemys turn
                    enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT, WAIT_TIME);
                    player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);

                    // Players turn
                    player_damage = player_did_damage(player, PLAYER_DMG_PERCENT, WAIT_TIME);
                    enemy_hp -= player_damage;
                    if ( enemy_hp_out( enemy_hp, WAIT_TIME) ){
                        player = main_fight_won(player);
                        return player;
                    }
                    player_attack_count =  player_attack_done(enemy_hp, player_attack_count, WAIT_TIME);
                }

                // Player faster
                else {
                    // Players turn
                    player_damage = player_did_damage(player, PLAYER_DMG_PERCENT, WAIT_TIME);
                    enemy_hp -= player_damage;
                    if ( enemy_hp_out( enemy_hp, WAIT_TIME) ){
                        player = main_fight_won(player);
                        return player;
                    }
                    player_attack_count =  player_attack_done(enemy_hp, player_attack_count, WAIT_TIME);

                    //Enemys turn

                    enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT, WAIT_TIME);
                    player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                }
            }
            else if (command == "commands" || command == "c" || command == "5" || command == "5."){
                letter_by_letter_very_fast("\nAll commands:\n1. attack\n2. use item\n3. run\n4. rush\n5. commands\n6. stats\n");
            }
            else if (command == "use item" || command == "2."  || command == "2"){
                letter_by_letter_fast("Which item you want to use, use number:\n");
                player.show_items();
                while (command != "back" || command != "end" || command != "b"){

                    cout<<"\ncommand >";
                    getline(cin, command);

                    if (command == "commands"){
                        letter_by_letter_fast("All commands:\nnumbers from 1 to 10\nback\n");
                    }
                    else if(command == "1"){
                        player = use_consumable_item(player, player.give_id(1), 1);
                    }
                    else if(command == "2"){
                        player = use_consumable_item(player, player.give_id(2), 2);
                    }
                    else if(command == "3"){
                        player = use_consumable_item(player, player.give_id(3), 3);
                    }
                    else if(command == "4"){
                        player = use_consumable_item(player, player.give_id(4), 4);
                    }
                    else if(command == "5"){
                        player = use_consumable_item(player, player.give_id(5), 5);
                    }
                    else if(command == "6"){
                        player = use_consumable_item(player, player.give_id(6), 6);
                    }
                    else if(command == "7"){
                        player = use_consumable_item(player, player.give_id(7), 7);
                    }
                    else if(command == "8"){
                        player = use_consumable_item(player, player.give_id(8), 8);
                    }
                    else if(command == "9"){
                        player = use_consumable_item(player, player.give_id(9), 9);
                    }
                    else if(command == "10"){
                        player = use_consumable_item(player, player.give_id(10), 10);
                    }
                    else if(command == "back"|| command == "end" || command == "b"){
                        break;
                    }
                    else {
                        letter_by_letter_very_fast("\nWrong command, use 'commands' to see all commands");
                    }
                    if (player.have_used_item()){

                        //Enemys turn

                        int enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT, WAIT_TIME);
                        player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);

                        player.used_item(false);
                        break;
                    }
                }
            }
            else if (command == "run" || command == "3."  || command == "3"){
                letter_by_letter_fast("\nYou try to run away !");
                sleep(WAIT_TIME);
                if(rand()% 100 <= 35){
                    letter_by_letter_fast("\nYou successfully ran away!\n\n");
                    return player;
                }
                else{
                    letter_by_letter_fast("You couldn't !\n");
                    int enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT, WAIT_TIME);
                    player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                }
            }
            else if (command == "debug"){
                Debug debug();
            }
            else if (command == "4" || command == "4." || command == "rush" || command == "Rush"){
                int player_damage{0};
                int enemy_damage{0};
                while(enemy_alive){
                    if (enemy_spd > player.print_spd() || rand()% 100 > 95){
                        //Enemys turn
                        enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT, 0);
                        player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);

                        // Players turn
                        player_damage = player_did_damage(player, PLAYER_DMG_PERCENT, 0);
                        enemy_hp -= player_damage;
                        if ( enemy_hp_out( enemy_hp, 0) ){
                            enemy_alive = false;
                            player = main_fight_won(player);
                            return player;
                        }
                        player_attack_count =  player_attack_done(enemy_hp, player_attack_count, 0);
                    }

                    // Player faster
                    else {
                        // Players turn
                        player_damage = player_did_damage(player, PLAYER_DMG_PERCENT, 0);
                        enemy_hp -= player_damage;
                        if ( enemy_hp_out( enemy_hp, 0) ){
                            enemy_alive = false;
                            player = main_fight_won(player);
                            return player;
                        }
                        player_attack_count =  player_attack_done(enemy_hp, player_attack_count, 0);

                        //Enemys turn

                        enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT, 0);
                        player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                    }
                }
            }
            else if (command == "stats" || command == "6."  || command == "6"){
                player.show_all_info();
            }
            else {
                letter_by_letter_very_fast("Wrong command, see all commands 'commands'\n");
            }
        }
    }
    return player;
}


int enemy_did_damage(int enemy_str, int handy_tier, double const ENEMY_DAMAGE_PERCENT, int WAIT_TIME){
    letter_by_letter_very_fast("\nIts enemys turn! \n");
    sleep(WAIT_TIME);
    int enemy_damage{0};
    int minus_str = rand()% (enemy_str + 1);
    enemy_damage += (enemy_str - minus_str) * ENEMY_DAMAGE_PERCENT;
    if(handy_tier == 1){
        enemy_damage += rand()%handy_tier;
    }
    else{
        enemy_damage += handy_tier;
    }
    if(enemy_damage <= 0){
        enemy_damage = 0;
    }
    return enemy_damage;
}


int player_did_damage(Player player, double const PLAYER_DAMAGE_PERCENT, int WAIT_TIME){
    int player_damage{0};
    letter_by_letter_very_fast("\nYou hit the enemy!\n");
    sleep(WAIT_TIME);
    unsigned int minus_damage = player.print_str() - player.handy_tier();
    if(minus_damage >= 0){
        minus_damage = 1;
    }
    int random_number = rand()% 100;
    if(random_number <= 100 && random_number > 95){
        minus_damage = minus_damage * 0.01;
    }
    else if(random_number <= 95 && random_number > 85){
        minus_damage = minus_damage * 0.20;
    }
    else if(random_number <= 85 && random_number > 70){
        minus_damage = minus_damage * 0.40;
    }
    else if(random_number <= 70 && random_number > 40){
        minus_damage = minus_damage * 0.70;
    }
    else if(random_number <= 40 && random_number >= 0){
        minus_damage = minus_damage;
    }

    player_damage += (player.print_str() - minus_damage);
    player_damage += player.handy_tier();
    player_damage = player_damage * PLAYER_DAMAGE_PERCENT;
    if(player_damage < 0){
        player_damage = 0;
    }
    letter_by_letter_very_fast("You did " + to_string(player_damage) +" damage to enemy.\n");
    return player_damage;
}

bool enemy_hp_out(int enemy_hp, int WAIT_TIME){
    if (enemy_hp <= 0 ){
        enemy_hp = 0;
        letter_by_letter_very_fast("Enemy has "+ to_string(enemy_hp) + " hp left.\n");
        letter_by_letter_fast("Enemy died.\n");
        sleep(WAIT_TIME);
        return true;
    }
    else{
        return false;
    }
}

int player_attack_done(int enemy_hp, int player_attack_count, int WAIT_TIME){
    letter_by_letter_very_fast("Enemy has " + to_string(enemy_hp) + " hp left.\n");
    sleep(WAIT_TIME);
    player_attack_count--;
    return player_attack_count;
}

bool op(int compare_this, int compare_with){
    if((compare_with / compare_this) >= 3){
        return true;
    }
    else{
        return false;
    }
}

Player main_fight_won(Player player) {
    int money_drop = main_fight_won_money(player);
    int xp_drop = main_fight_won_xp(player);
    fight_ended_message();
    letter_by_letter_very_fast("\nREWARDS:\n+" + to_string(xp_drop) + " exp\n+" + to_string(money_drop) + " coins\n");
    player.give_money(money_drop);
    player.give_xp(xp_drop);
    int chance = rand()% 100;
    if(chance >= 80){
        if(!player.inventory_full()){
            letter_by_letter_very_fast("\nEnemy also dropped an item!");
            int id = possible_drop_main_lvl_fight(player);
            int free_slot = player.show_first_empty_inv_space();
            player.give_item(free_slot, id);
            string item_name = give_items_name(id);
            letter_by_letter_very_fast(" You got '" + item_name + "' !\n");
        }
    }
    return player;
}

int main_fight_won_xp(Player player) {
    double xp_drop;
    xp_drop = 12 + rand()%4;
    if(player.print_main_lvl()<20){
        xp_drop -= (player.print_main_lvl() * 0.1);
    }
    else {
        xp_drop -= (player.print_main_lvl() * 0.2);
    }
    int xp = (int) xp_drop + 0.5;
    return xp;
}

int main_fight_won_money(Player player) {
    int money_drop;
    money_drop = 26 + rand()%10;
    if (player.print_main_lvl() > 20){
        money_drop += 50;
    }
    return money_drop;
}


void save_game(Player player){

    string command{"twentysix"};

    while(command != "back" || command != "end" || command != "" || command != " "){
        letter_by_letter_very_fast("\n\nWhich file you want to save to? ('back' or 'end' to return)\n\n");

        for(int i{1}; i != 11; i++){
            string save_file_name{"save_"};
            save_file_name += to_string(i) + ".txt";

            cout<<i<<". ";
            if( file_exists(save_file_name) ){
                ifstream file;
                file.open(save_file_name);
                string output;
                file >> output;
                vector<string> save_info;
                save_info = split(output, ':');


                int seconds = stoi(save_info[9]);
                string time = seconds_minutes_hours(seconds);

                cout<<"Name: " <<save_info[0] <<"  Class: "<<save_info[1]
                   <<"  Main level: "<<save_info[2]<<"  Playtime: "<<time<<"\n";
            }
            else{
                cout<<"\n";
            }
        }

        cout<<"\ncommand >";

        getline(cin, command);

        if (command == "1") {
            string save_file_name{"save_"};
            save_file_name += to_string(1) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";
        }
        else if (command == "2" || command == "2.") {
            string save_file_name{"save_"};
            save_file_name += to_string(2) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";

        }
        else if (command == "3" || command == "3.") {
            string save_file_name{"save_"};
            save_file_name += to_string(3) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";

        }
        else if (command == "4" || command == "4.") {
            string save_file_name{"save_"};
            save_file_name += to_string(4) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";

        }
        else if (command == "5" || command == "5.") {
            string save_file_name{"save_"};
            save_file_name += to_string(5) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";


        }
        else if (command == "6" || command == "6.") {
            string save_file_name{"save_"};
            save_file_name += to_string(6) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";

        }
        else if (command == "7" || command == "7.") {
            string save_file_name{"save_"};
            save_file_name += to_string(7) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";

        }
        else if (command == "8" || command == "8.") {
            string save_file_name{"save_"};
            save_file_name += to_string(8) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";

        }
        else if (command == "9" || command == "9.") {
            string save_file_name{"save_"};
            save_file_name += to_string(9) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";


        }
        else if (command == "10" || command == "10.") {
            string save_file_name{"save_"};
            save_file_name += to_string(10) + ".txt";
            ofstream a_file(save_file_name);
            a_file<<player.get_save_info();
            cout<<"\nGAME SAVED\n\n";

        }
        else if (command == "end" || command == "" || command == " " || command == "back"){
            break;
        }
    }
}

void load_game(){
    string command{"twentysix"};

    while(command != "back" || command != "end" || command != "" || command != " "){

        ifstream savefile;
        letter_by_letter_very_fast("What file do you want to load?\n\n");

        for(int i{1}; i != 11; i++){
            string save_file_name{"save_"};
            save_file_name += to_string(i) + ".txt";

            cout<<i<<". ";
            if( file_exists(save_file_name) ){
                ifstream file;
                file.open(save_file_name);
                string output;
                file >> output;
                vector<string> save_info;
                save_info = split(output, ':');

                int seconds = stoi(save_info[9]);
                string time = seconds_minutes_hours(seconds);

                cout<<"Name: " <<save_info[0] <<"  Class: "<<save_info[1]
                   <<"  Main level: "<<save_info[2]<<"  Playtime: "<<time<<"\n";
            }
            else{
                cout<<"\n";
            }
        }

        cout<<"\ncommand >";
        getline(cin, command);

        if(command == "1" || command == "2" || command == "3" ||
                command == "4" || command == "5" || command == "6" ||
                command == "7" || command == "8" || command == "9" ||
                command == "10"){

            string file;
            file = "save_" + command + ".txt";
            savefile.open(file);
            string output;

            if (savefile.is_open()) {
                while (!savefile.eof()) {
                   savefile >> output;
                   vector<string> save_info;
                   save_info = split(output, ':');
                   if (save_info.size() != 23){
                       letter_by_letter_very_fast("\nYou tried to load a old version of the game.\n");
                   }
                   else{
                       Player player = Player(save_info[0], save_info[1], stoi(save_info[2]), stoi(save_info[3]),
                               stoi(save_info[4]), stoi(save_info[5]), stoi(save_info[6]), stoi(save_info[7]),
                               stoi(save_info[8]), stoi(save_info[9]), stoi(save_info[10]), stoi(save_info[11]),
                               stoi(save_info[12]), stoi(save_info[13]), stoi(save_info[14]), stoi(save_info[15]),
                               stoi(save_info[16]), stoi(save_info[17]), stoi(save_info[18]), stoi(save_info[19]),
                               stoi(save_info[20]), stoi(save_info[21]), stoi(save_info[22]));
                       savefile.close();
                       phasehandler(player);
                   }
                }
            }
            else{
                letter_by_letter_very_fast("\nFile you chose doesn't exist.\n\n");
            }
        }
        else if (command == "back" || command == "end"
                 || command == "Back" || command == "End"){
            return;
        }
        else {
            letter_by_letter_very_fast("\nWrong command, all commands are:\nNumbers 1-10\nback\n");
        }
    }
}

bool file_exists (string file_name) {
    struct stat buffer;
    return (stat (file_name.c_str(), &buffer) == 0);
}


void letter_by_letter_slow(string string_to_print){
    for(char& c : string_to_print){
        cout<<c;
        usleep(200000);
    }
}

void letter_by_letter_very_slow(string string_to_print){
    for(char& c : string_to_print){
        cout<<c;
        sleep(1);
    }
}


void letter_by_letter_fast(string string_to_print){
    for(char& c : string_to_print){
        cout<<c;
        usleep(50000);
    }
}


void letter_by_letter_very_fast(string string_to_print){
    for(char& c : string_to_print){
        cout<<c;
        usleep(20000);
    }
}


void letter_by_letter_super_fast(string string_to_print){
    for(char& c : string_to_print){
        cout<<c;
        usleep(5000);
    }
}


string seconds_minutes_hours(int seconds){
    int total_seconds = seconds;
    int hours = total_seconds / 60 / 60;
    total_seconds -= 60 * 60 * hours;
    int minutes = total_seconds / 60;
    total_seconds -= minutes * 60;

    string complete_string = "Hours: " + to_string(hours) + "  Minutes: " + to_string(minutes) + "  Seconds: " + to_string(total_seconds);
    return complete_string;
}


Player boss_fight_1(Player player){
    box_message("#                   THE RELEGO                   #");
    srand(time(NULL));

    int player_attack_count;

    double const PLAYER_DMG_PERCENT{1.5};
    int WAIT_TIME{2};

    int enemy_hp{15};
    int enemy_spd{4};
    int enemy_turn{0};

    bool enemy_alive = true;

    if(enemy_alive == true && player.print_current_hp() > 0){

        string command{"twentysix"};
        letter_by_letter_fast("\nYou encounter The Relego!" );

        while(enemy_alive == true && player.print_current_hp() > 0){
            letter_by_letter_very_fast("\nWhat you want to do?");
            cout<<"\ncommand >";
            getline(cin, command);

            if (command == "attack" || command == "a" || command == "A" || command == "Attack"
                    || command == "1." || command == "1"){
                int player_damage{0};

                // Enemy faster
                if (enemy_spd > player.print_spd() || rand()% 100 > 95){
                    //Enemys turn
                    player = relego_turn(player, enemy_turn);
                    enemy_turn++;

                    // Players turn
                    player_damage = player_did_damage(player, PLAYER_DMG_PERCENT, WAIT_TIME);
                    enemy_hp -= player_damage;
                    if ( boss_1_hp_out( enemy_hp, WAIT_TIME) ){
                        fight_ended_message();
                        boss_fight_1_won(player);
                        phase_3(player);
                    }
                    player_attack_count =  player_attack_done(enemy_hp, player_attack_count, WAIT_TIME);
                }

                // Player faster
                else {
                    // Players turn
                    player_damage = player_did_damage(player, PLAYER_DMG_PERCENT, WAIT_TIME);
                    enemy_hp -= player_damage;
                    if ( boss_1_hp_out( enemy_hp, WAIT_TIME) ){
                        fight_ended_message();
                        boss_fight_1_won(player);
                        phase_3(player);
                    }
                    player_attack_count = player_attack_done(enemy_hp, player_attack_count, WAIT_TIME);

                    //Enemys turn
                    player = relego_turn(player, enemy_turn);
                    enemy_turn++;
                }
            }
            else if (command == "commands" || command == "c"){
                letter_by_letter_very_fast("\nAll commands:\n1. attack\n2. use item\n3. run\n4. stats\n");
            }
            else if (command == "use item"){
                letter_by_letter_fast("Which item you want to use, use number:\n");
                player.show_items();
                while (command != "back" || command != "end" || command != "b"){

                    cout<<"\ncommand >";
                    getline(cin, command);

                    if (command == "commands"){
                        letter_by_letter_fast("All commands:\nnumbers from 1 to 10\nback\n");
                    }
                    else if(command == "1"){
                        player = use_consumable_item(player, player.give_id(1), 1);
                    }
                    else if(command == "2"){
                        player = use_consumable_item(player, player.give_id(2), 2);
                    }
                    else if(command == "3"){
                        player = use_consumable_item(player, player.give_id(3), 3);
                    }
                    else if(command == "4"){
                        player = use_consumable_item(player, player.give_id(4), 4);
                    }
                    else if(command == "5"){
                        player = use_consumable_item(player, player.give_id(5), 5);
                    }
                    else if(command == "6"){
                        player = use_consumable_item(player, player.give_id(6), 6);
                    }
                    else if(command == "7"){
                        player = use_consumable_item(player, player.give_id(7), 7);
                    }
                    else if(command == "8"){
                        player = use_consumable_item(player, player.give_id(8), 8);
                    }
                    else if(command == "9"){
                        player = use_consumable_item(player, player.give_id(9), 9);
                    }
                    else if(command == "10"){
                        player = use_consumable_item(player, player.give_id(10), 10);
                    }
                    else if(command == "back"|| command == "end" || command == "b"){
                        break;
                    }
                    else {
                        letter_by_letter_very_fast("\nWrong command, use 'commands' to see all commands");
                    }
                    if (player.have_used_item()){

                        //Enemys turn
                        player = relego_turn(player, enemy_turn);
                        enemy_turn++;
                        player.used_item(false);
                        break;
                    }
                }
            }
            else if (command == "run" || command == "Run" || command == "3."  || command == "3"){
                letter_by_letter_fast("\nYou try to run away !");
                sleep(WAIT_TIME);
                if(rand()% 100 <= 35){
                    letter_by_letter_fast("\nYou successfully ran away!\n\n");
                    return player;
                }
                else{
                    letter_by_letter_fast("You couldn't !\n");
                    player = relego_turn(player, enemy_turn);
                    enemy_turn++;
                }
            }
            else if (command == "debug"){
                Debug debug();
            }
            else if (command == "stats" || command == "4."  || command == "4"){
                player.show_stats();
            }
            else {
                letter_by_letter_very_fast("Wrong command, see all commands 'commands'\n");
            }
        }
    }
    return player;
}


Player relego_turn(Player player, int enemy_turn){
    if( enemy_turn == 0 || enemy_turn == 6 || enemy_turn == 12){
        letter_by_letter_very_fast("Its The Relego's turn!\n");
        letter_by_letter_very_fast("Relego swinged his sword at you!\nRelego did 3 damage at you!\n");
        player = player.react_to_boss_damage(player, 3);
    }
    else if( enemy_turn == 1 || enemy_turn == 7 || enemy_turn == 13){
        letter_by_letter_very_fast("Its The Relego's turn!\n");
        letter_by_letter_very_fast("Relego swinged his sword at you!\nRelego did 3 damage at you!\n");
        player = player.react_to_boss_damage(player, 3);
    }
    else if( enemy_turn == 2 || enemy_turn == 8 || enemy_turn == 14){
        letter_by_letter_very_fast("Its The Relego's turn!\n");
        letter_by_letter_very_fast("Relego's swords started glowing slightly white\nHe jumps and hits you with a massive 5 damage!\n");
        player = player.react_to_boss_damage(player, 5);
    }
    else if( enemy_turn == 3 || enemy_turn == 9 || enemy_turn == 15){
        letter_by_letter_very_fast("Its The Relego's turn!\n");
        letter_by_letter_very_fast("Relego catches his breath and smirks at you!\n");
    }
    else if( enemy_turn == 4 || enemy_turn == 10 || enemy_turn == 16){
        letter_by_letter_very_fast("Its The Relego's turn!\n");
        letter_by_letter_very_fast("Relego catches his breath and smirks at you!\n");
    }
    else if( enemy_turn == 5 || enemy_turn == 11 || enemy_turn == 17){
        letter_by_letter_very_fast("Its The Relego's turn!\n");
        letter_by_letter_very_fast("Relego catches his breath and smirks at you!\n");
    }
    else{
        letter_by_letter_very_fast("Its The Relego's turn!\n");
        letter_by_letter_very_fast("Relego swinged his sword at you!\nRelego did 3 damage at you!\n");
        player = player.react_to_boss_damage(player, 3);
    }
    return player;
}


bool boss_1_hp_out(int enemy_hp, int WAIT_TIME){
    if (enemy_hp <= 0 ){
        enemy_hp = 0;
        letter_by_letter_very_fast("The Relego doesn't have any hp left.\n");
        letter_by_letter_fast("The Relego has been beaten.\n");
        sleep(WAIT_TIME);
        return true;
    }
    else{
        return false;
    }
}


void boss_fight_1_won(Player player){
    int xp_drop{75};
    int money_drop{200};
    letter_by_letter_fast("You got " + to_string(xp_drop) + "xp and " + to_string(money_drop) + "money !\n");
    player.give_money(money_drop);
    player.give_xp(xp_drop);
    phase_3(player);
}


void fight_started_message(){
    cout<<"##################################################\n";
    usleep(5000);
    cout<<"#                                                #\n";
    usleep(5000);
    cout<<"#                 FIGHT STARTED                  #\n";
    usleep(5000);
    cout<<"#                                                #\n";
    usleep(5000);
    cout<<"##################################################\n";
    usleep(5000);
}


void fight_ended_message(){
    cout<<"##################################################\n";
    usleep(5000);
    cout<<"#                                                #\n";
    usleep(5000);
    cout<<"#                  FIGHT ENDED                   #\n";
    usleep(5000);
    cout<<"#                                                #\n";
    usleep(5000);
    cout<<"##################################################\n";
    usleep(5000);
}


void box_message(string message){
    cout<<"##################################################\n";
    usleep(5000);
    cout<<"#                                                #\n";
    usleep(5000);
    cout<<message<<"\n";
    usleep(5000);
    cout<<"#                                                #\n";
    usleep(5000);
    cout<<"##################################################\n";
    usleep(5000);
}


string give_spaces(int amount){
    string space_string{""};
    for(int i{0};i != amount; i++){
        space_string += " ";
    }
    return space_string;
}


void cart_talk_tree(Player player){
    string command{"twentysix"};
    letter_by_letter_fast("\n'Oh you want me to take you to Caeco? That would be 600 coins thank you.'");
    letter_by_letter_super_fast("\n1. Pay 600 coins\n2. You will get your money when we get there\n"
                                "3. Thats outrageous, I'll pay 200\n4. I thought you'd go there by yourself because of the market\n5. commands\n6. back\n\n");
    while(command != "exit"){
        command = "twentysix";
        cout<<"command >";
        getline(cin, command);

        if(command == "1." || command == "1" || command == "Pay 600 coins" || command == "pay"){
            if(player.enough_money(600)){
                player.pay(600);
                phase_3(player);
            }
            else {
                letter_by_letter_fast("\n'You dont have enough money!'\n");

            }
        }
        else if(command == "2." || command == "2"){
            letter_by_letter_fast("\n'Im sorry, but I cannot trust you that much.'\n");

        }
        else if(command == "3." || command == "3"){
            letter_by_letter_fast("\n'Haha, Im not stupid.'\n");

        }
        else if(command == "4." || command == "4"){
            letter_by_letter_fast("\n'What market?'\n");
            letter_by_letter_super_fast("\n1. Sale of carts!\n2. Market where comes people from all over the Alacer\n"
                                        "3. Okay, okay. I just need a ride to Caeco to talk to king\n4. commands\n5. back\n\n");

            while(command != "exit"){
                command = "twentysix";
                cout<<"command >";
                getline(cin, command);


                if(command == "1" || command == "1."){
                    letter_by_letter_fast("\n'But I have a Fine cart right here!'\n");

                }
                else if (command == "2" || command == "2."){
                    letter_by_letter_fast("\n'Well that sound interesting.. What kind of people?'\n");
                    letter_by_letter_super_fast("\n1. Political minds\n2. Customers\n"
                                                "3. Creative art people\n4. commands\n5. back\n\n");
                    while(command != "exit"){
                        command = "twentysix";
                        cout<<"command >";
                        getline(cin, command);

                        if(command == "1" || command == "1."){
                            letter_by_letter_fast("\n'I don't really care about that kind of stuff.'\n");
                        }
                        else if (command == "2" || command == "2."){
                            letter_by_letter_fast("\n'Well I could try to sell some of my crops.. Sure lets go.'\n");

                            letter_by_letter_fast("\n\nDo you really want to leave to Caeco?\n\n1. Yes\n2. No\n\n");
                            while(command != "exit"){
                                command = "twentysix";
                                cout<<"command >";
                                getline(cin, command);

                                if(command == "1" || command == "1." || command == "yes" || command == "Yes"){
                                    phase_4(player);
                                }
                                else if (command == "2." || command == "2" || command == "no" || command == "No"){
                                    command = "exit";
                                }
                                else if (command == "back" || command == "Back"){
                                    break;
                                }
                                else if (command == "c" || command == "commands"){
                                    letter_by_letter_super_fast("\n1. Yes\n2. No\n\n");
                                }
                                else{
                                    letter_by_letter_very_fast("Wrong command, see all commands 'commands'\n");
                                }
                            }
                        }
                        else if (command == "3" || command == "3."){
                            letter_by_letter_fast("\n'Do I look like a guy who paints alot? Im not.'\n");
                        }
                        else if (command == "4" || command == "4." || command == "commands" || command == "c"){
                            letter_by_letter_fast("\n1. Political minds\n2. Customers\n"
                                                  "3. Creative art people\n4. commands\n5. back\n\n");

                        }
                        else if (command == "5" || command == "5." || command == "back"){
                            break;
                        }
                        else{
                            letter_by_letter_very_fast("Wrong command, see all commands 'commands'\n");
                        }
                    }
                }
                else if (command == "3" || command == "3."){
                    letter_by_letter_fast("\n'I know, but I can't do it for free.'\n");

                }
                else if (command == "4" || command == "4." || command == "commands" || command == "c"){
                    letter_by_letter_fast("\n1. Sale of carts!\n2. Market where comes people from all over the Alacer\n"
                                          "3. Okay, okay. I just need a ride to Caeco to talk to king\n4. commands\n5. back\n\n");

                }
                else if (command == "5" || command == "5." || command == "back"){
                    break;
                }
                else{
                    letter_by_letter_very_fast("Wrong command, see all commands 'commands'\n");
                }
            }
        }
        else if(command == "5." || command == "5" || command == "c" || command == "commands"){
            letter_by_letter_super_fast("\n1. Pay 600 coins\n2. You will get your money when we get there\n"
                                        "3. Thats outrageous, I'll pay 200\n4. I thought you'd go there by yourself because of the market\n5. commands\n6. back\n");
        }
        else if(command == "6." || command == "6" || command == "back"){
            break;
        }
        else{
            letter_by_letter_very_fast("Wrong command, see all commands 'commands'\n");
        }
    }
}


Player item_shop(Player player){
    string command{"twentysix"};

    box_message("#                    ITEM SHOP                   #");


    letter_by_letter_very_fast("\n'Welcome welcome! What would you like to do?'\n");
    letter_by_letter_super_fast("\n1. Buy\n2. Sell\n3. Talk\n4. Exit\n5. Commands\n\n");

    while(command != "exit"){
        cout<<"command >";
        getline(cin, command);


        if(command == "1" || command == "1." || command == "buy" || command == "Buy"){
            while(command != "exit"){
                command="twentysix";

                letter_by_letter_super_fast("\n\n-Buying-\n\n1. Health Potion 1          (120 coins)\n2. Damage Maker 1          (150 coins)\n3. Level Upper               (1000 coins)\n4. Back\n5. Commands\n\n");
                cout<<"command >";
                getline(cin, command);

                if(command == "1" || command == "1." || command == "health potion" || command == "Health Potion 1"){
                    if(player.enough_money(120)){
                        int free_slot = player.show_first_empty_inv_space();
                        player.give_item(free_slot, 1);
                        string item_name = give_items_name(1);
                        letter_by_letter_very_fast(" You got '" + item_name + "' !\n");
                        player.pay(120);
                    }
                    else {
                        letter_by_letter_fast("\n'You dont have enough money!'\n");
                    }
                }
                else if(command == "2" || command == "2." || command == "damage maker" || command == "Damage Maker 1"){
                    if(player.enough_money(150)){
                        int free_slot = player.show_first_empty_inv_space();
                        player.give_item(free_slot, 2);
                        string item_name = give_items_name(2);
                        letter_by_letter_very_fast(" You got '" + item_name + "' !\n");
                        player.pay(150);
                    }
                    else {
                        letter_by_letter_fast("\n'You dont have enough money!'\n");
                    }
                }
                else if (command == "3" || command == "3." || command == "level upper" || command == "Lever Upper"){
                    if(player.enough_money(1000)){
                        int free_slot = player.show_first_empty_inv_space();
                        player.give_item(free_slot, 3);
                        string item_name = give_items_name(3);
                        letter_by_letter_very_fast(" You got '" + item_name + "' !\n");
                        player.pay(1000);
                    }
                    else {
                        letter_by_letter_fast("\n'You dont have enough money!'\n");
                    }
                }
                else if(command == "4" || command == "4" || command == "Back" || command == "back"){
                    break;
                }
                else if(command == "5" || command == "5." || command == "commands" || command == "c"
                        || command == "Commands"){
                    letter_by_letter_super_fast("\n\n-Buying-\n\n1. Health Potion 1          (120 coins)\n2. Damage Maker 1          (150 coins)\n3. Level Upper               (1000 coins)\n4. Back\n5. Commands\n\n");
                }
                else{
                    letter_by_letter_very_fast("Wrong command, see all commands 'commands'\n");
                }
            }
        }
        else if(command == "2" || command == "2." || command == "sell" || command == "Sell"){

        }
        else if(command == "3" || command == "3." || command == "talk" || command == "Talk"){
            letter_by_letter_fast("\n'Have you seen any magnets laying around?\nI couldn't find any of mine after those military people rambled by.'\n\n");
            command = "twentysix";

        }
        else if(command == "4" || command == "4." || command == "exit" || command == "Exit"){
            return player;
        }
        else if(command == "5" || command == "5." || command == "commands" || command == "c"
                || command == "Commands"){
            letter_by_letter_super_fast("\nAll commands:\n1. Buy\n2. Sell\n3. Talk\n4. Exit\n5. Commands\n\n ");
            command = "twentysix";
        }
        else{
            letter_by_letter_very_fast("Wrong command, see all commands 'commands'\n");
        }
    }
}
