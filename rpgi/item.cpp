#include "item.hh"
#include "player.hh"
#include "functions.hh"
#include <string>
#include <vector>

using namespace std;

/*
 %%%%%%%%%%%%%%%%% ITEM ID's %%%%%%%%%%%%%%%%%%%
0. none

Consumables are items 1-3

1. Healing potion 1
2. Damage maker 1
3. Level upper

IDEAS:
-See enemys stats
-all six elemental attacks, all three swiping attacks

*/

string give_items_name(int id){
    vector<string> all_items{"" ,"Healing potion 1", "Damage maker 1", "Level upper"};
    return all_items[id];
}


Player use_consumable_item(Player player, int id, int slot){
    if ( id == 0){
        letter_by_letter_fast("\nYou dont have any item on that slot.");
        player.used_item(false);
        return player;
    }
    // 1. Healing potion 1
    else if( id == 1 ){
        player.give_hp(10);
        player.used_item(true);
        player.delete_item(slot);
        letter_by_letter_super_fast("\nYou used healing potion 1 !\n");
        return player;
    }

    // 2. Damage maker 1
    else if( id == 2){
        player.used_item(true);
        player.give_extra_damage(25);
        player.delete_item(slot);

        return player;
    }

    // 3. Level upper
    else if( id == 3 ){
        player.used_item(true);
        player.level_up();
        player.delete_item(slot);

        return player;
    }
    else {
        player.used_item(false);
    }
}


int possible_drop_main_lvl_fight(Player player){
    if(player.print_main_lvl() <= 15){
        return (rand()% 1) + 1;
    }
    else if(player.print_main_lvl() <= 20){
        return (rand()% 2) + 1;
    }
    else {
        return (rand()% 2) + 1;
    }
}
