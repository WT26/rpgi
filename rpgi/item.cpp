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
*/

string give_items_name(int id){
    vector<string> all_items{"" ,"Healing potion 1", "Damage maker 1", "Level upper"};
    return all_items[id];
}


Player use_consumable_item(Player player, int id, int slot){
    if ( id == 0){
        letter_by_letter_fast("\nYou dont have any item on that slot");
        player.used_item(false);
    }
    // 1. Healing potion 1
    else if( id == 1 ){
        player.give_hp(10);
        player.used_item(true);
        player.delete_item(slot);
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
