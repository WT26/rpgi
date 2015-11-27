#include "phasehandler.hh"
#include "functions.hh"
#include <iostream>
#include <string>

using namespace std;

void phasehandler(Player player){
    if(player.print_phase() == 1){
        phase_1();
    }
    else if(player.print_phase() == 2){
        phase_2(player);
    }
    else if(player.print_phase() == 3){
        phase_3(player);
    }
    else if(player.print_phase() == 4){
        phase_4(player);
    }
    else if(player.print_phase() == 5){
        phase_5(player);
    }
}

// Character creation phase. Returns Player class to next phase.
Player phase_1(){
    cout<<"Character creation:\nPlease, enter your name: ";
    string name;
    getline(cin, name);
    cout<<"\nHey "<<name<<", now choose your class. But first let me explain all the skills:";
    string answer;
    while(answer != "Curator" && answer != "Salto" && answer != "curator" && answer != "salto" &&
          answer != "Ensis" && answer != "ensis" && answer != "Piger" && answer != "piger" && answer != "end"){

        cout<<"\nhp: Your health, if it runs out you will die.\nstr: How much your "
                          "single hit will do damage\nspd: Speed of how quickly you will do your"
                          " next hit\nhandy: What kind of items you can wield and use.\n"
                          "Classes:\nSalto : hp10  str2  spd5  handy3\n"
                          "Ensis : hp11  str5  spd3  handy1\nCurator : hp14  str1  spd2"
                          "  handy3\nPiger : hp12  str2  spd2  handy2\nEnter one of the classes: ";
        getline(cin, answer);
    }
    if (answer == "Curator" || answer == "curator"){
        int hp = 14;
        int str = 1;
        int spd = 2;
        int handy = 3;
        string class_name = "Curator";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1);
        phase_2(player);
    }
    else if (answer == "Salto" || answer == "salto"){
        int hp = 10;
        int str = 2;
        int spd = 5;
        int handy = 3;
        string class_name = "Salto";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1);
        phase_2(player);
    }
    else if (answer == "Ensis" || answer == "Ensis"){
        int hp = 11;
        int str = 5;
        int spd = 3;
        int handy = 1;
        string class_name = "Ensis";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1);
        phase_2(player);
    }
    else if (answer == "Piger" || answer == "piger"){
        int hp = 12;
        int str = 2;
        int spd = 2;
        int handy = 2;
        string class_name = "Piger";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1);
        phase_2(player);
    }
    else if (answer == "end" || answer == "End"){
        endGame();
    }

}
void phase_2(Player player){
    cout<<"its phase 2"<<endl;
}
void phase_3(Player player){
    cout<<"its phase 3"<<endl;

}
void phase_4(Player player){
    cout<<"its phase 4"<<endl;

}
void phase_5(Player player){
    cout<<"its phase 5"<<endl;

}
