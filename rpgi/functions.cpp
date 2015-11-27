#include "functions.hh"
#include "phasehandler.hh"
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
        int enemy_lvl = main_lvl - 3 + rand(6);
    }
    else{
        int enemy_lvl = main_lvl -2 + rand(4);
    }

    if (rand()%100 == 26){
        vector<string> animal{"?"};
    }
    else{
        vector<string> animal{"Bird", "Dog", "Cat", "Cow", "Bat", "Mole"};
        vector<string> adjective{"Mystery", "Epic", "Baby", "Little", "Weird", "Silent", "Angry", "Massive"};
        string enemy_name = adjective[rand()%8] + " " + animal[rand()%6];

    }
}


