#include "phasehandler.hh"

void phasehandler(Player player){
    if(player.give_phase() == 1){
        phase_1();
    }
    else if(player.give_phase() == 2){
        phase_2(player);
    }
    else if(player.give_phase() == 3){
        phase_3(player);
    }
    else if(player.give_phase() == 4){
        phase_4(player);
    }
    else if(player.give_phase() == 5){
        phase_5(player);
    }
}

// Character creation phase. Returns Player class to next phase.
Player phase_1(){
    cout<<"Character creation:\n"
}
void phase_2(Player player){

}
void phase_3(Player player){

}
void phase_4(Player player){

}
void phase_5(Player player){

}
