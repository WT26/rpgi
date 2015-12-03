#include "functions.hh"
#include "phasehandler.hh"
#include "player.hh"
#include "debug.hh"
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

void main_lvl_fight(Player player){
    int main_lvl = player.print_main_lvl();

    if (rand()%100 > 75){
        int enemy_lvl = main_lvl - 3 + rand()%6;
        if (rand()%100 == 26){
            vector<string> animal{"?"};
        }
        else{
            vector<string> animal{"Bird", "Dog", "Cat", "Cow", "Bat", "Mole", "Bunny", "Rabbit", "Monkey"};
            vector<string> adjective{"Mystery", "Epic", "Baby", "Little", "Weird", "Silent", "Angry", "Massive", "Gentle"};
            string enemy_name = adjective[rand()%9] + " " + animal[rand()%9];

            cout<<"Enemy name: "<<enemy_name<<"\nEnemy level: "<<enemy_lvl<<endl;
            usleep(100000);
            int enemy_hp = rand()%enemy_lvl;
            int enemy_str = rand()%(enemy_lvl - enemy_hp);
            int enemy_spd = rand()%(enemy_lvl - enemy_hp - enemy_str);
            int enemy_handy = rand()%(enemy_lvl - enemy_hp - enemy_str - enemy_spd);
            int handy_tier;
            int player_attack_count;
            vector<string> handy_attacks;
            if(enemy_handy >= 15 && enemy_handy < 20){
                handy_attacks.push_back("hit you with stick!");
                handy_attacks.push_back("hit you with rock!");
                handy_attacks.push_back("throwed dirt at you!");
                handy_tier = 5;
            }
            else if(enemy_handy >= 20 && enemy_handy < 25){
                handy_attacks.push_back("hit you with metal stick!");
                handy_attacks.push_back("throwed firey ball at you!");
                handy_attacks.push_back("Throwed glowing rock at you!");
                handy_tier = 7;
            }
            else {
                handy_attacks.push_back("swiped you!");
                handy_attacks.push_back("hit you!");
                handy_attacks.push_back("striked you!");
                handy_attacks.push_back("bit you!");
                handy_attacks.push_back("smashed you!");
                handy_attacks.push_back("punched you!");
                handy_tier = 1;
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
                cout<<"You encounter "<<enemy_name<<"! Its lvl "<<enemy_lvl<<"!"<<endl;

                while(enemy_alive == true && player.print_current_hp() > 0){
                    cout<<"What you want to do?"<<endl;
                    getline(cin, command);
                    if (command == "attack"){
                        int enemy_attack_count{2};
                        int player_damage;

                        // First attack, enemy first
                        if (enemy_spd * 3 + rand()%3 > player.print_spd() * 3 + rand()%3){
                            cout<<"Enemy was faster! ";
                            usleep(100000);
                            int enemy_damage;
                            enemy_damage += enemy_str - 4;
                            enemy_damage += rand()% handy_tier;
                            if(enemy_damage < 0){
                                enemy_damage = 0;
                            }
                            cout<<enemy_name<<" "<<handy_attacks[rand()% (handy_attacks.size()-1)]<<endl;
                            cout<<"Enemy did "<<enemy_damage<<" to you."<<endl;
                            player.player_lose_damage(enemy_damage);
                            cout<<"Your current hp: "<<player.print_current_hp()<<endl;
                            if(player.print_current_hp() <= 0){
                                player.player_died();
                            }
                            enemy_attack_count--;

                            // Enemy so fast he does second attack too
                            if(enemy_attack_count > 0 && enemy_spd * 2 > player.print_spd() * 3 + rand()%4){
                                cout<<"Enemy was faster! ";
                                usleep(100000);
                                int enemy_damage;
                                enemy_damage += enemy_str - 4;
                                enemy_damage += rand()% handy_tier;
                                if(enemy_damage < 0){
                                    enemy_damage = 0;
                                }
                                cout<<enemy_name<<" "<<handy_attacks[rand()% (handy_attacks.size()-1)]<<endl;
                                cout<<"Enemy did "<<enemy_damage<<" to you."<<endl;
                                player.player_lose_damage(enemy_damage);
                                cout<<"Your current hp: "<<player.print_current_hp()<<endl;
                                if(player.print_current_hp() <= 0){
                                    player.player_died();
                                }
                                enemy_attack_count--;


                                //Your turn, enemy attacked already twice
                                cout<<"You hit enemy!"<<endl;
                                usleep(100000);
                                player_damage += player.print_str() - 3;
                                player_damage += rand()% handy_tier;
                                if(player_damage < 0){
                                    player_damage = 0;
                                }
                                cout<<"You did "<<player_damage<<" to enemy."<<endl;
                                enemy_hp -= player_damage;
                                if (enemy_hp <= 0){
                                    enemy_hp = 0;
                                    cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                    cout<<"Enemy died."<<endl;
                                    return;

                                }
                                cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                usleep(100000);
                                player_attack_count--;

                                //(enemy twice, you once, now you more if you have attacks left)
                                if(player_attack_count > 0){
                                    cout<<"You hit enemy!"<<endl;
                                    usleep(100000);
                                    player_damage += player.print_str() - 3;
                                    player_damage += rand()% handy_tier;
                                    if(player_damage < 0){
                                        player_damage = 0;
                                    }
                                    cout<<"You did "<<player_damage<<" to enemy."<<endl;
                                    enemy_hp -= player_damage;
                                    if (enemy_hp <= 0){
                                        enemy_hp = 0;
                                        cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                        cout<<"Enemy died."<<endl;
                                    }
                                    cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                    usleep(100000);
                                    player_attack_count--;

                                    //(enemy twice, you twice, now you more if you have attacks left)
                                    if(player_attack_count>0){
                                        cout<<"You hit enemy!"<<endl;
                                        usleep(100000);
                                        player_damage += player.print_str() - 3;
                                        player_damage += rand()% handy_tier;
                                        if(player_damage < 0){
                                            player_damage = 0;
                                        }
                                        cout<<"You did "<<player_damage<<" to enemy."<<endl;
                                        enemy_hp -= player_damage;
                                        if (enemy_hp <= 0){
                                            enemy_hp = 0;
                                            cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                            cout<<"Enemy died."<<endl;
                                        }
                                        cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                        usleep(100000);
                                        player_attack_count--;
                                    }
                                }
                            }
                            // Your turn to hit 1st time(enemy once, now you)
                            else {
                                cout<<"You hit enemy!"<<endl;
                                usleep(100000);
                                player_damage += player.print_str() - 3;
                                player_damage += rand()% handy_tier;
                                if(player_damage < 0){
                                    player_damage = 0;
                                }
                                cout<<"You did "<<player_damage<<" to enemy."<<endl;
                                enemy_hp -= player_damage;
                                if (enemy_hp <= 0){
                                    enemy_hp = 0;
                                    cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                    cout<<"Enemy died."<<endl;
                                    return;

                                }
                                cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                usleep(100000);
                                player_attack_count--;

                                //(enemy once, you once, now you more if you have attacks left)
                                if(player_attack_count>0){
                                    cout<<"You hit enemy!"<<endl;
                                    usleep(100000);
                                    player_damage += player.print_str() - 3;
                                    player_damage += rand()% handy_tier;
                                    if(player_damage < 0){
                                        player_damage = 0;
                                    }
                                    cout<<"You did "<<player_damage<<" to enemy."<<endl;
                                    enemy_hp -= player_damage;
                                    if (enemy_hp <= 0){
                                        enemy_hp = 0;
                                        cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                        cout<<"Enemy died."<<endl;
                                    }
                                    cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                    usleep(100000);
                                    player_attack_count--;

                                    //(enemy once, you twice, now you more if you have attacks left)
                                    if(player_attack_count>0){
                                        cout<<"You hit enemy!"<<endl;
                                        usleep(100000);
                                        player_damage += player.print_str() - 3;
                                        player_damage += rand()% handy_tier;
                                        if(player_damage < 0){
                                            player_damage = 0;
                                        }
                                        cout<<"You did "<<player_damage<<" to enemy."<<endl;
                                        enemy_hp -= player_damage;
                                        if (enemy_hp <= 0){
                                            enemy_hp = 0;
                                            cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                            cout<<"Enemy died."<<endl;
                                        }
                                        cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                        usleep(100000);
                                        player_attack_count--;
                                    }
                                }
                                //enemy first, then you(1-3times) then enemy again
                                cout<<"Its enemys turn! ";
                                usleep(100000);
                                int enemy_damage;
                                enemy_damage += enemy_str - 4;
                                enemy_damage += rand()% handy_tier;
                                if(enemy_damage < 0){
                                    enemy_damage = 0;
                                }
                                cout<<enemy_name<<" "<<handy_attacks[rand()% (handy_attacks.size()-1)]<<endl;
                                cout<<"Enemy did "<<enemy_damage<<" to you."<<endl;
                                player.player_lose_damage(enemy_damage);
                                cout<<"Your current hp: "<<player.print_current_hp()<<endl;
                                if(player.print_current_hp() <= 0){
                                    player.player_died();
                                }
                                enemy_attack_count--;
                            }
                            if(enemy_attack_count > 0){
                                cout<<"Its enemys turn! ";
                                usleep(100000);
                                int enemy_damage;
                                enemy_damage += enemy_str - 4;
                                enemy_damage += rand()% handy_tier;
                                if(enemy_damage < 0){
                                    enemy_damage = 0;
                                }
                                cout<<enemy_name<<" "<<handy_attacks[rand()% (handy_attacks.size()-1)]<<endl;
                                cout<<"Enemy did "<<enemy_damage<<" to you."<<endl;
                                player.player_lose_damage(enemy_damage);
                                cout<<"Your current hp: "<<player.print_current_hp()<<endl;
                                if(player.print_current_hp() <= 0){
                                    player.player_died();
                                }
                                enemy_attack_count--;
                            }
                        }
                        else if(player.print_spd() * 3 + rand()%3 > enemy_spd * 3 + rand()%3){
                            //TODO player faster, attacks goes player player player enemy enemy
                            //Youre faster, you zero enemy zero
                            cout<<"You hit enemy!"<<endl;
                            usleep(100000);
                            player_damage += player.print_str() - 3;
                            player_damage += rand()% handy_tier;
                            if(player_damage < 0){
                                player_damage = 0;
                            }
                            cout<<"You did "<<player_damage<<" to enemy."<<endl;
                            enemy_hp -= player_damage;
                            if (enemy_hp <= 0){
                                enemy_hp = 0;
                                cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                cout<<"Enemy died."<<endl;
                                return;

                            }
                            cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                            usleep(100000);
                            player_attack_count--;

                            //(You one, enemy zero)
                            if(player_attack_count > 0){
                                cout<<"You hit enemy!"<<endl;
                                usleep(100000);
                                player_damage += player.print_str() - 3;
                                player_damage += rand()% handy_tier;
                                if(player_damage < 0){
                                    player_damage = 0;
                                }
                                cout<<"You did "<<player_damage<<" to enemy."<<endl;
                                enemy_hp -= player_damage;
                                if (enemy_hp <= 0){
                                    enemy_hp = 0;
                                    cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                    cout<<"Enemy died."<<endl;
                                }
                                cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                usleep(100000);
                                player_attack_count--;

                                //(you twice, enemy zero)
                                if(player_attack_count>0){
                                    cout<<"You hit enemy!"<<endl;
                                    usleep(100000);
                                    player_damage += player.print_str() - 3;
                                    player_damage += rand()% handy_tier;
                                    if(player_damage < 0){
                                        player_damage = 0;
                                    }
                                    cout<<"You did "<<player_damage<<" to enemy."<<endl;
                                    enemy_hp -= player_damage;
                                    if (enemy_hp <= 0){
                                        enemy_hp = 0;
                                        cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                        cout<<"Enemy died."<<endl;
                                    }
                                    cout<<"Enemy has "<<enemy_hp_<<" left."<<endl;
                                    usleep(100000);
                                    player_attack_count--;
                                }
                            }
                            cout<<"Its enemys turn! ";
                            usleep(100000);
                            int enemy_damage;
                            enemy_damage += enemy_str - 4;
                            enemy_damage += rand()% handy_tier;
                            if(enemy_damage < 0){
                                enemy_damage = 0;
                            }
                            cout<<enemy_name<<" "<<handy_attacks[rand()% (handy_attacks.size()-1)]<<endl;
                            cout<<"Enemy did "<<enemy_damage<<" to you."<<endl;
                            player.player_lose_damage(enemy_damage);
                            cout<<"Your current hp: "<<player.print_current_hp()<<endl;
                            if(player.print_current_hp() <= 0){
                                player.player_died();
                            }
                            enemy_attack_count--;

                            // Enemy so fast he does second attack too
                            if(enemy_attack_count > 0 && enemy_spd * 2 > player.print_spd() * 3 + rand()%4){
                                cout<<"Its enemys turn! ";
                                usleep(100000);
                                int enemy_damage;
                                enemy_damage += enemy_str - 4;
                                enemy_damage += rand()% handy_tier;
                                if(enemy_damage < 0){
                                    enemy_damage = 0;
                                }
                                cout<<enemy_name<<" "<<handy_attacks[rand()% (handy_attacks.size()-1)]<<endl;
                                cout<<"Enemy did "<<enemy_damage<<" to you."<<endl;
                                player.player_lose_damage(enemy_damage);
                                cout<<"Your current hp: "<<player.print_current_hp()<<endl;
                                if(player.print_current_hp() <= 0){
                                    player.player_died();
                                }
                                enemy_attack_count--;
                            }
                        }
                    }
                    else if (command == "commands"){
                        cout<<"All commands:\nattack\nuse item\nrun"<<endl;
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

                    }
                    else if (command == "debug"){
                        Debug debug();
                    }
                    else if (command == "stats"){
                        cout<<"stats"<<endl;
                    }
                    else {
                        cout<<"Wrong command, see all commands 'commands'"<<endl;
                    }
                }
            }
        }
    }
    else{
        int enemy_lvl = main_lvl - 2 + rand()%4;
        if (rand()%100 == 26){
            vector<string> animal{"?"};
        }
        else{

        }
    }
}

bool op(int compare_this, int compare_with){
    if((compare_with / compare_this) >= 3){
        return true;
    }
    else{
        return false;
    }
}

int main_fight_won_xp(Player player){
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

}

