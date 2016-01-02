#ifndef ITEM_HH
#define ITEM_HH

#include <string>
#include <player.hh>

using namespace std;

string give_items_name(int id);
Player use_consumable_item(Player player, int id, int slot);
int possible_drop_main_lvl_fight(Player player);

#endif // ITEM_HH
