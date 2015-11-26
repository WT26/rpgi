#ifndef SAVE_HH
#define SAVE_HH

#include <string>
#include <vector>

using namespace std;

class save
{
public:
    save(int phase, string player_name, string class_name, int main_lvl, int hp_lvl,
         int str_lvl, int spd_lvl, int handy_lvl, int all_exp);

private:
    string player_name_;
    string class_name_;
    int main_lvl_;
    int hp_lvl_;
    int str_lvl_;
    int spd_lvl_;
    int handy_lvl_;
    int all_exp_;
};

#endif // SAVE_HH
