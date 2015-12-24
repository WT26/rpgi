#include "functions.hh"
#include "phasehandler.hh"
#include "player.hh"
#include "debug.hh"
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>


using namespace std;

bool start_menu(){
    vector<string> commands{"new game", "load game", "end"};
    string command;

    cout<<"Start menu: Would you like to start a new game or load game"<<endl;

    bool end_game{false};
    while(end_game != true){
        getline(cin, command);

        if(command == "new game" || command == "New game"){
            phase_1();
        }
        else if(command == "load game" || command == "Load game") {
            ifstream savefile;
            savefile.open("save_01.txt");
            string output;

            if (savefile.is_open()) {
                while (!savefile.eof()) {
                   savefile >> output;
                   vector<string> save_info;
                   save_info = split(output, ':');
                   Player player = Player(save_info[0], save_info[1], stoi(save_info[2]), stoi(save_info[3]),
                           stoi(save_info[4]), stoi(save_info[5]), stoi(save_info[6]), stoi(save_info[7]),
                           stoi(save_info[8]));
                }
            }
            savefile.close();

        }
        else if(command == "end" || command == "End"){
            return false;
        }
        else if(command == "debug"){
            Debug debug = Debug();
        }
        else{
            cout<<"Wrong command, all commands: "<<commands[0]
               <<", "<<commands[1]<<", "<<commands[2]<<endl;
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
    return 0;
}

Player main_lvl_fight(Player player){
    srand(time(NULL));

    int main_lvl = player.print_main_lvl();

    if (rand()%100 > 1){
        int enemy_lvl = main_lvl - 3 + rand()%6;
        if (rand()%100 == 26){
            vector<string> animal{"?"};
        }
        else{
            vector<string> animal{"Bird", "Dog", "Cat", "Cow", "Bat", "Mole", "Bunny", "Rabbit", "Monkey"};
            vector<string> adjective{"Mystery", "Epic", "Baby", "Little", "Weird", "Silent", "Angry", "Massive", "Gentle"};
            string enemy_name = adjective[rand()%9] + " " + animal[rand()%9];

            usleep(100000);
            int enemy_hp = rand()%enemy_lvl;
            int enemy_str = rand()%(enemy_lvl - enemy_hp);
            int enemy_spd = rand()%(enemy_lvl - enemy_hp - enemy_str);
            int enemy_handy = rand()%(enemy_lvl - enemy_hp - enemy_str - enemy_spd);
            int enemy_handy_tier;
            int player_attack_count;
            vector<string> handy_attacks;

            double const PLAYER_DMG_PERCENT{1.5};
            double const ENEMY_DMG_PERCENT{0.5};

            if(enemy_handy >= 15 && enemy_handy < 20){
                handy_attacks.push_back("hit you with stick!");
                handy_attacks.push_back("hit you with rock!");
                handy_attacks.push_back("throwed dirt at you!");
                enemy_handy_tier = 5;
            }
            else if(enemy_handy >= 20 && enemy_handy < 25){
                handy_attacks.push_back("hit you with metal stick!");
                handy_attacks.push_back("throwed firey ball at you!");
                handy_attacks.push_back("Throwed glowing rock at you!");
                enemy_handy_tier = 7;
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
                if(op(player.print_spd(), enemy_spd)){
                    cout<<"Enemy is three time faster than you so you can only have one hit per turn!"<<endl;
                    player_attack_count = 1;
                }
                else if(player.trehit_open()){
                        player_attack_count = 3;
                }
                else {
                        player_attack_count = 2;
                }

                string command{"twentysix"};
                cout<<"\nYou encounter "<<enemy_name<<"! Its lvl "<<enemy_lvl<<"!"<<endl;

                while(enemy_alive == true && player.print_current_hp() > 0){
                    cout<<"What you want to do?\ncommand >";
                    getline(cin, command);
                    if (command == "attack"){
                        int enemy_attack_count{2};
                        int player_damage{0};

                        // First attack, enemy first
                        if (enemy_spd * 3 + rand()%3 > player.print_spd() * 3 + rand()%3){
                            cout<<"Enemy was faster!\n";
                            int enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT);
                            player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                            enemy_attack_count--;

                            // Enemy so fast he does second attack too
                            if(enemy_attack_count > 0 && enemy_spd * 2 > player.print_spd() * 3 + rand()%4){
                                int enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT);
                                player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                                enemy_attack_count--;

                                //Your turn, enemy attacked already twice
                                player_damage = player_did_damage(player, PLAYER_DMG_PERCENT);
                                enemy_hp -= player_damage;
                                if ( enemy_hp_out( enemy_hp) ){
                                    player = main_fight_won(player);
                                    return player;
                                }
                                player_attack_count =  player_attack_done(enemy_hp, player_attack_count);

                                //(enemy twice, you once, now you more if you have attacks left)
                                if(player_attack_count > 0){
                                    player_damage = player_did_damage(player, PLAYER_DMG_PERCENT);
                                    enemy_hp -= player_damage;
                                    if ( enemy_hp_out(enemy_hp) ){
                                        player = main_fight_won(player);
                                        return player;
                                    }
                                    player_attack_count =  player_attack_done(enemy_hp, player_attack_count);

                                    //(enemy twice, you twice, now you more if you have attacks left)
                                    if(player_attack_count>0){
                                        player_damage = player_did_damage(player, PLAYER_DMG_PERCENT);
                                        enemy_hp -= player_damage;
                                        if ( enemy_hp_out(enemy_hp) ){
                                            player = main_fight_won(player);
                                            return player;
                                        }
                                        player_attack_count =  player_attack_done(enemy_hp, player_attack_count);
                                    }
                                }
                            }
                            // Your turn to hit 1st time(enemy once, now you)
                            else {
                                player_damage = player_did_damage(player, PLAYER_DMG_PERCENT);
                                enemy_hp -= player_damage;
                                if ( enemy_hp_out(enemy_hp) ){
                                    player = main_fight_won(player);
                                    return player;
                                }
                                player_attack_count =  player_attack_done(enemy_hp, player_attack_count);

                                //(enemy once, you once, now you more if you have attacks left)
                                if(player_attack_count>0){
                                    player_damage = player_did_damage(player, PLAYER_DMG_PERCENT);
                                    enemy_hp -= player_damage;
                                    if ( enemy_hp_out(enemy_hp) ){
                                        player = main_fight_won(player);
                                        return player;
                                    }
                                    player_attack_count =  player_attack_done(enemy_hp, player_attack_count);

                                    //(enemy once, you twice, now you more if you have attacks left)
                                    if(player_attack_count>0){
                                        player_damage = player_did_damage(player, PLAYER_DMG_PERCENT);
                                        enemy_hp -= player_damage;
                                        if ( enemy_hp_out(enemy_hp) ){
                                            player = main_fight_won(player);
                                            return player;
                                        }
                                        player_attack_count =  player_attack_done(enemy_hp, player_attack_count);
                                    }
                                }

                                //enemy first, then you(1-3times) then enemy again
                                int enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT);
                                player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                                enemy_attack_count--;
                            }

                            if(enemy_attack_count > 0){
                                int enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT);
                                player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                                enemy_attack_count--;
                            }
                        }

                        else if(player.print_spd() * 3 + rand()%3 > enemy_spd * 3 + rand()%3){
                            //Youre faster, you zero enemy zero
                            player_damage = player_did_damage(player, PLAYER_DMG_PERCENT);
                            enemy_hp -= player_damage;
                            if ( enemy_hp_out(enemy_hp) ){
                                player = main_fight_won(player);
                                return player;
                            }
                            player_attack_count =  player_attack_done(enemy_hp, player_attack_count);

                            //(You one, enemy zero)
                            int enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT);
                            player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                            enemy_attack_count--;

                            // You once, enemy once
                            if(player_attack_count > 0){
                                player_damage = player_did_damage(player, PLAYER_DMG_PERCENT);
                                enemy_hp -= player_damage;
                                if ( enemy_hp_out(enemy_hp) ){
                                    player = main_fight_won(player);
                                    return player;
                                }
                                player_attack_count =  player_attack_done(enemy_hp, player_attack_count);


                                //(you twice, enemy once)
                                int enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT);
                                player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                                enemy_attack_count--;

                                // You twice, enemy twice
                                if(player_attack_count>0){
                                    player_damage = player_did_damage(player, PLAYER_DMG_PERCENT);
                                    enemy_hp -= player_damage;
                                    if ( enemy_hp_out(enemy_hp) ){
                                        player = main_fight_won(player);
                                        return player;
                                    }
                                    player_attack_count =  player_attack_done(enemy_hp, player_attack_count);
                                }
                            }
                        }
                    }
                    else if (command == "commands" || command == "c"){
                        cout<<"\nAll commands:\nattack\nuse item\nrun\n";
                    }
                    else if (command == "use item"){
                        cout<<"Which item you want to use:\empty"<<endl;
                        while (command != "back"){
                            if (command == "commands"){
                                cout<<"All commands:\nback"<<endl;
                            }
                        }
                    }
                    else if (command == "run"){
                        cout<<"You try to run away !\n";
                        sleep(2);
                        if(rand()% 100 <= 35){
                            cout<<"You successfully ran away!\n\n";
                            return player;
                        }
                        else{
                            int enemy_damage = enemy_did_damage(enemy_str, enemy_handy_tier, ENEMY_DMG_PERCENT);
                            player = player.react_to_damage(player, enemy_damage, handy_attacks, enemy_name);
                        }
                    }
                    else if (command == "debug"){
                        Debug debug();
                    }
                    else if (command == "stats"){
                        player.show_stats();
                    }
                    else {
                        cout<<"Wrong command, see all commands 'commands'"<<endl;
                    }
                }
            }
        }
    }
    return player;
}


int enemy_did_damage(int enemy_str, int handy_tier, double const ENEMY_DAMAGE_PERCENT){
    cout<<"\nIts enemys turn! ";
    sleep(2);
    int enemy_damage{0};
    enemy_damage += (enemy_str - rand()% enemy_str) * ENEMY_DAMAGE_PERCENT;
    enemy_damage += rand()% handy_tier;
    if(enemy_damage < 0){
        enemy_damage = 0;
    }
    return enemy_damage;
}


int player_did_damage(Player player, double const PLAYER_DAMAGE_PERCENT){
    int player_damage{0};
    cout<<"\nYou hit enemy!"<<endl;
    sleep(2);
    player_damage += ( player.print_str() - rand()% player.print_str() ) * PLAYER_DAMAGE_PERCENT;
    player_damage += rand()% player.handy_tier();
    if(player_damage < 0){
        player_damage = 0;
    }
    cout<<"You did "<<player_damage<<" to enemy."<<endl;
    return player_damage;
}

bool enemy_hp_out(int enemy_hp){
    if (enemy_hp <= 0 ){
        enemy_hp = 0;
        cout<<"Enemy has "<<enemy_hp<<" left."<<endl;
        cout<<"Enemy died."<<endl;
        sleep(2);
        return true;
    }
    else{
        return false;
    }
}

int player_attack_done(int enemy_hp, int player_attack_count){
    cout<<"Enemy has "<<enemy_hp<<" left."<<endl;
    sleep(2);
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
    cout<<"You got "<<xp_drop<<"xp and "<<money_drop<<"money!"<<endl;
    player.give_money(money_drop);
    player.give_xp(xp_drop);
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

