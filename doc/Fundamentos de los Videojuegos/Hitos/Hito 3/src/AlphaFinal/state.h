#ifndef STATE_H
#define STATE_H

#pragma once
#include <SFML/Graphics.hpp>

class state {
public:
    state();
    state(const state& orig);
    virtual ~state();
    void cambiarEstado(int estado);
    int GetEstado();
    int GetEstadoAnterior(){ return estadoAnt;}
    void setEstadoAnterior(int ea){ estadoAnt=ea;}
private:
    int numState; //1 MENU 2 PLAY
    int estadoAnt;
};

#endif /* STATE_H */

