#include "state.h"

state::state() {
}

state::state(const state& orig) {
}

state::~state() {
}

void state::cambiarEstado(int estado){ 
    numState=estado; 
}

int state::GetEstado(){
    return numState;
}
