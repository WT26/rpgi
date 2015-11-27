#include "functions.hh"
#include "phasehandler.hh"
#include "Player.hh"
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

            int enemy_hp = rand()%enemy_lvl;
            int enemy_str = rand()%(enemy_lvl - enemy_hp);
            int enemy_spd = rand()%(enemy_lvl - enemy_hp - enemy_str);
            int enemy_handy = rand()%(enemy_lvl - enemy_hp - enemy_str - enemy_spd);

            vector<string> normal_attacks{"swiped", "hit", "striked", "bit", "smashed", "punched"};

            if(enemy_handy >= 15 && enemy_handy < 20){
                vector<string> handy_attacks{"hit you with stick!", "hit you with rock!", "throwed dirt at you!"};
            }
            else if(enemy_handy >= 20 && enemy_handy < 25){
                vector<string> handy_attacks{"hit you with metal stick!", "throwed firey ball at you!", "Throwed glowing rock at you!"};
            }

            bool enemy_alive = true;
            if(enemy_alive == true && player.print_current_hp() < 0){
                if(op(player.print_spd, enemy_spd)){
                    cout<<"Enemy is three time faster than you so you can only have one hit per turn!"<<endl;
                }
                else if(player.trehit_open()){
                        int player_attack_count{3};
                }
                else {
                        int player_attack_count{2};
                }

                string command{twentysix};
                cout<<"You encounter "<<enemy_name<<"! Its lvl "<<enemy_lvl<<"!"<<endl;
                while(enemy_alive == true && player.print_current_hp() < 0){
                    cout<<"What you want to do?"<<endl;
                    if (command == "attack"){

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

bool op(int number_to_compare, int compare_it_with_this){
    if((compare_it_with_this / number_to_compare) >= 3){
        return true;
    }
    else{
        return false;
    }
}


