#include "phasehandler.hh"
#include "functions.hh"
#include "debug.hh"
#include "item.hh"
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
    box_message("#               CHARACTER CREATION               #");

    letter_by_letter_fast("\nPlease, enter your name: ");
    string name;
    getline(cin, name);
    letter_by_letter_fast("\nHey "+ name +", now choose your class. But first let me explain all the skills:\n");
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
                               0,0,0,0,0,0,0,0,0,0,0);
        phase_2(player);
    }
    else if (answer == "Salto" || answer == "salto"){
        int hp = 10;
        int str = 2;
        int spd = 5;
        int handy = 3;
        string class_name = "Salto";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1, 0, 10, 0
                               ,0,0,0,0,0,0,0,0,0,0,0);
        phase_2(player);
    }
    else if (answer == "Ensis" || answer == "ensis"){
        int hp = 11;
        int str = 5;
        int spd = 3;
        int handy = 1;
        string class_name = "Ensis";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1, 0, 11, 0
                               ,0,0,0,0,0,0,0,0,0,0,0);
        phase_2(player);
    }
    else if (answer == "Piger" || answer == "piger"){
        int hp = 12;
        int str = 2;
        int spd = 2;
        int handy = 2;
        string class_name = "Piger";
        Player player = Player(name, class_name, 10, hp, str, spd, handy, 0, 1, 0, 12, 0,
                               0,0,0,0,0,0,0,0,0,0,0);
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
    box_message("#            UNSETTLED LITTLE TOWNEY             #");
    player.start_clock();
    player.update_phase(2);
    letter_by_letter_very_fast("\nYou venture outside of your little hut.\nIts bright outside and you see"
                               "a bunch of people\nof your little village gathered around.\n\n");
    bool talked = false;

    string command{"twentysix"};

    while(command != "end"){
        cout<<"command >";
        getline(cin, command);

        if (command == "inventory" || command == "inv" || command == "1"
                || command == "1."){
            letter_by_letter_fast("Your inventory:");
            player.show_items();
        }
        else if(command == "use item" || command == "use" || command == "2"
                || command == "2."){

            while (command != "back" || command != "end" || command != "b"){
                letter_by_letter_fast("Which item you want to use, use number:\n");
                player.show_items();

                cout<<"\ncommand >";
                getline(cin, command);

                if (command == "commands" || command == "c"){
                    letter_by_letter_fast("All commands:\n> numbers from 1 to 10\n> back\n");
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
                    letter_by_letter_very_fast("\nWrong command, use 'commands' to see all commands\n");
                }
                if (player.have_used_item()){
                    player.used_item(false);
                    break;
                }
            }
        }

        else if (command == "stats" || command == "st" || command == "3"
                  || command == "3."){
            player.show_all_info();
        }

        else if (command == "shop" || command == "sh"
                  || command == "Shop" || command == "4"
                  || command == "4."){
            if (talked == false){
                letter_by_letter_fast("\nShop's clercks man doesn't seem to be here.\n");
            }
            else {
                letter_by_letter_fast("\nShop's clercks man is talking with tax people.\n");
            }
        }

        else if (command == "talk" || command == "Talk"
                  || command == "5" || command == "5."
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
                letter_by_letter_very_fast("\nYou see the group still arguing with kingdom people.\n\n");
            }
        }

        else if (command == "woods" || command == "w"
                  || command == "Woods" || command == "6"
                  || command == "6."){
            player = main_lvl_fight(player);
        }

        else if (command == "boss" || command == "Boss"
                          || command == "7." || command == "7"
                          || command == "b"){
                    if(player.print_main_lvl() < 14){
                        letter_by_letter_very_fast("You're too weak to challenge him. (Suggested min. lvl is 15)\n");
                    }
                    else{
                        player =boss_fight_1(player);
                    }
                }

        else if(command == "save" || command == "Save" || command == "save"
                 || command == "8" || command == "8."){

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
                 || command == "9" || command == "9."){
            letter_by_letter_super_fast("\nAll commands are:\n1. inventory\n2. use item\n3. stats\n4. shop\n5. talk\n"
                                       "6. woods          (random encounter)\n7. boss\n8. save\n9. commands\n10. end\n\n");
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
    box_message("#                  LITTLE TOWNEY                 #");
    player.update_phase(3);
    letter_by_letter_fast("\nCollapsed Relego gathers himself up, and start walking towards escaping kingdom men\n"
                               "They leave the village to north. Everyone around you celebrates\na bit and one by one comes to thank you. You found a letter\n"
                               "where the Relego collapsed, it says: \n'By any means, collect\nmoney from all over the land and quickly bring them to me\n"
                               "The King of yours: Ater'\nIt seems King has a sudden urge of money and is collecting it illegally. You decide to take action "
                               "against it.\n");

    bool talked_cart = false;
    bool talked_littleguy = false;

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
            player =  item_shop(player);
        }

        else if (command == "talk" || command == "Talk"
                  || command == "4" || command == "4."
                  || command == "t"){

            letter_by_letter_fast("\nWho do you want to talk to?\n1. Guy next to horse and a cart\n2. Little guy\n");
            command = "twentysix";
            cout<<"command >";
            getline(cin, command);
            if(command == "littleguy" || command == "2." || command == "2" || command == "little guy" || command == "Little guy"){
                letter_by_letter_fast("\n'So you're going to Caeco? Walking is an option, but I'd persuadeo the cart guy.'\n\n");
                talked_littleguy = true;
            }
            else if((command == "1." || command == "1" || command == "Guy" || command == "Guy next to horse and a cart" || command == "guy next to")
                    && talked_littleguy == true && talked_cart == false){
                cart_talk_tree(player);
            }
            else if((command == "1." || command == "1" || command == "Guy" || command == "Guy next to horse and a cart" || command == "guy next to")
                    && talked_littleguy == false){
                letter_by_letter_fast("\n'Good day sir. Quite a lovely day it is.'\n\n");
            }
        }
        else if (command == "windmill"
                  || command == "Windmill" || command == "5"
                  || command == "5."){
            player = main_lvl_fight(player);
        }

        else if(command == "save" || command == "Save" || command == "save"
                 || command == "6" || command == "6."){

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
                 || command == "7" || command == "7."){
            letter_by_letter_super_fast("\nAll commands are:\n1. items\n2. stats\n3. shop\n4. talk\n"
                                       "5. windmill          (random encounter)\n6. save\n7. commands\n8. end\n\n");
        }

        else if (command == "end" || command =="End"
                 || command == "8" || command == "8."){
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
//###V######V######V######V######V###### Phase 4 ######V######V######V######V######V######V###
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
void phase_4(Player player){
    player.update_phase(4);
    if(player.give_caeco_intro() == false){
        box_message("#                  ROAD TO CAECO                 #");
        letter_by_letter_fast("\nYou jump to the cart and you take off out of the village.\n");
        letter_by_letter_slow("\n\n. . . . Road is long and sun starts to fall so you decide to take a nap.\n\n. . . . . ");
        player.caeco_intro_change();
    }
    if(player.give_caeco_intro() == true){
        box_message("#                   CAECO MARKET                 #");
        letter_by_letter_very_fast("\nYou wake up, and it seems that you've arrived to the center of the Caeco.\n"
                                    "You jump off the cart and see lots of people doing their daily chores.\nThere seems to be "
                                   "a little panic in everyones face, and you decide that its good opportunity\nto sneak in and talk with"
                                   "the king.\n");
    }


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

        /*
        else if (command == "shop" || command == "sh"
                  || command == "Shop" || command == "3"
                  || command == "3."){
            player =  item_shop(player);
        }
        */
        else if (command == "boss" || command == "Boss"
                  || command == "4" || command == "4."
                  || command == "b"){

            //bossfight = first figth with guard then you can save again and then fight with boss
        }
        else if (command == "windmill"
                  || command == "Windmill" || command == "5"
                  || command == "5."){
            player = main_lvl_fight(player);
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
                                       "5. windmill          (random encounter)\n6. boss\n7. save\n8. commands\n9. end\n\n");
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
//###V######V######V######V######V###### Phase 5 ######V######V######V######V######V######V###
//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
void phase_5(Player player){
    cout<<"its phase 5"<<endl;

}
