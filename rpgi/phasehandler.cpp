#include "phasehandler.hh"
#include "functions.hh"
#include "debug.hh"
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
    letter_by_letter_fast("Character creation:");
    letter_by_letter_fast("\nPlease, enter your name: ");
    string name;
    getline(cin, name);
    letter_by_letter_fast("\nHey "+ name +", now choose your class. But first let me explain all the skills:");
    string answer;
    while(answer != "Curator" && answer != "Salto" && answer != "curator" && answer != "salto" &&
          answer != "Ensis" && answer != "ensis" && answer != "Piger" && answer != "piger" &&
          answer != "end" && answer != "debug"){

        letter_by_letter_slow("\nhp:");
        letter_by_letter_fast(" Your health, if it runs out you will die.");
        letter_by_letter_slow("\nstr: ");
        letter_by_letter_fast("How much a single hit will do damage.");
        letter_by_letter_slow("\nspd: ");
        letter_by_letter_fast("How quickly you will do your next hit.");
        letter_by_letter_slow("\nhandy: ");
        letter_by_letter_fast("What kind of items you can wield and use.\n\n");
        letter_by_letter_very_fast("Classes:\nSalto : hp10  str2  spd5  handy3\n"
                                   "Ensis : hp11  str5  spd3  handy1\nCurator : hp14  str1  spd2"
                                   "  handy3\nPiger : hp12  str2  spd2  handy2\nEnter one of the classes: ");
        getline(cin, answer);
    }
    if (answer == "Curator" || answer == "curator"){
        int hp = 14;
        int str = 1;
        int spd = 2;
        int handy = 3;
        string class_name = "Curator";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1, 0, 14, 0,
                               0,0,0,0,0,0,0,0,0,0);
        phase_2(player);
    }
    else if (answer == "Salto" || answer == "salto"){
        int hp = 10;
        int str = 2;
        int spd = 5;
        int handy = 3;
        string class_name = "Salto";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1, 0, 10, 0
                               ,0,0,0,0,0,0,0,0,0,0);
        phase_2(player);
    }
    else if (answer == "Ensis" || answer == "ensis"){
        int hp = 11;
        int str = 5;
        int spd = 3;
        int handy = 1;
        string class_name = "Ensis";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1, 0, 11, 0
                               ,0,0,0,0,0,0,0,0,0,0);
        phase_2(player);
    }
    else if (answer == "Piger" || answer == "piger"){
        int hp = 12;
        int str = 2;
        int spd = 2;
        int handy = 2;
        string class_name = "Piger";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1, 0, 12, 0,
                               0,0,0,0,0,0,0,0,0,0);
        phase_2(player);
    }
    else if (answer == "debug"){
        Debug debug = Debug();
    }
    else if (answer == "end" || answer == "End"){
        endGame();
    }
}
//############################################################################################
//###V######V######V######V######V###### Phase 2 ######V######V######V######V######V######V###
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
void phase_2(Player player){
    player.start_clock();
    player.update_phase(2);
    letter_by_letter_very_fast("\nYou venture outside of your little hut.\nIts bright outside and you see"
                               "a bunch of people\nof your little village gathered around.\n\n");
    bool talked = false;

    string command{"twentysix"};

    while(command != "end"){
        cout<<"command >";
        getline(cin, command);

        if (command == "items" || command == "i" || command == "1"
                || command == "1."){
            letter_by_letter_fast("Your inventory:");
            player.show_items();
        }
        else if (command == "stats" || command == "st" || command == "2"
                  || command == "2."){
            player.show_stats();
        }
        else if (command == "shop" || command == "sh"
                  || command == "Shop" || command == "3"
                  || command == "3."){
            if (talked == false){
                letter_by_letter_fast("\nShop's clercks man doesn't seem to be here.\n");
            }
            else {
                letter_by_letter_fast("\nShop's clercks man is talking with tax people.\n");
            }
        }
        else if (command == "talk" || command == "Talk"
                  || command == "4" || command == "4."
                  || command == "t"){
            if(talked == false){
                letter_by_letter_very_fast("\nYou walk to the group. You see a bunch of people that you haven't\nseen before. It appears that they are collecting some new tax moneys.\n");
                letter_by_letter_very_fast("Everyone is resisting, but then a bigger guy, calling himself");
                letter_by_letter_slow(" The Relego, ");
                letter_by_letter_very_fast("appears and\ninsists the money. Everyone quiets up and act scared.\n");
                letter_by_letter_very_fast("\nThen A little guy grabs your hand and tells you: ");
                letter_by_letter_fast("\n\n'Hey " + player.print_name() + " you've got to deal with that big guy, that tax is outrageous!'\n\n");
                talked = true;
            }
            else {
                letter_by_letter_very_fast("\nYou see the group still arguing with kindom people.\n\n");
            }
        }
        else if (command == "woods" || command == "w"
                  || command == "Woods" || command == "5"
                  || command == "5."){
            player = main_lvl_fight(player);
        }
        else if (command == "boss" || command == "Boss"
                  || command == "6." || command == "6"
                  || command == "b"){
            if(player.print_main_lvl() <= 15){
                letter_by_letter_very_fast("You're too weak to challenge him. (Suggested min. lvl is 15)\n");
            }
            else{
                    //bossfite 01  The Relego
            }
        }
        else if(command == "save" || command == "Save" || command == "save"
                 || command == "7" || command == "7."){

            while(command != "no" && command != "2" && command != "2." && command != "No"){
                letter_by_letter_fast("\n\ndo you want to save the game?\n\n1. Yes\n2. No\n");
                cout<<"\ncommand >";
                getline(cin, command);
                if(command == "yes" || command == "1" || command == "1." || command == "y"){
                    save_game(player);
                    break;
                }
                else if (command == "no" || command == "2" || command == "2." || command == "No"){
                    break;
                }
            }
        }
        else if (command == "c"|| command == "C"||
                 command == "commands" || command == "Commands"
                 || command == "8" || command == "8."){
            letter_by_letter_super_fast("\nAll commands are:\n1. items\n2. stats\n3. shop\n4. talk\n"
                                       "5. woods          (random encounter)\n6. boss\n7. save\n8. commands\n9. end\n\n");
        }
        else if (command == "end" || command =="End"
                 || command == "9" || command == "9."){
            command = "twentysix";
            while(command != "back"){
                letter_by_letter_very_fast("\nDo you really want to return to main menu? All unsaved progress will be lost."
                                           "\n1. Yes\n2. No");
                cout<<"\n\ncommand >";
                getline(cin, command);

                if(command == "yes" || command == "Yes"
                        || command == "1" || command == "1."){
                    start_menu();
                }
                else if (command == "no" || command == "No"
                         || command == "2" || command == "2."){
                    command = "back";
                }
            }
        }
        else if (command == "debug"){
            Debug debug = Debug();
        }
        else {
            letter_by_letter_very_fast("Wrong command, see all commands 'commands'\n");
        }
    }
}
//############################################################################################
//###V######V######V######V######V###### Phase 3 ######V######V######V######V######V######V###
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
void phase_3(Player player){
    cout<<"its phase 3\n";

}
//############################################################################################
//###V######V######V######V######V###### Phase 4 ######V######V######V######V######V######V###
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
void phase_4(Player player){
    cout<<"its phase 4\n";

}
//############################################################################################
//###V######V######V######V######V###### Phase 5 ######V######V######V######V######V######V###
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
void phase_5(Player player){
    cout<<"its phase 5"<<endl;

}
