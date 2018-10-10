#include "juego.h"
#include <sstream>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

juego::juego(){
    
    personaje = 0;
    
    t_Enemigo.loadFromFile("resources/malo-sprite.png");    
    
    if(!tAro.loadFromFile("resources/aroazul.png"))
        std::cout << "No se ha podido cargar la textura aro.png" << std::endl;    
}

juego::~juego() {
    delete jugador1;
}

void juego::setPersonaje(int p){
    personaje = p;
    std::cout<<"--------jugadorseleccionado-----------"<<std::endl;
    std::cout<<p<<std::endl;
    
    if(personaje!=jugador1->getPersonaje()){
        crearJugador(1300,800);
    }
    
}

void juego::crearenemigos(int n, int vida, int fuerza){
    for(int i=0; i<n; i++){
        //Crear posciones aleatorias para pasarlo al contructor
        malignos.push_back(enemigos(1300/(i+1),900/(i+1),t_Enemigo,fuerza));
    }
}

void juego::comprobarcolisiones(enemigos e){
    if (e.bounding().intersects(jugador1->bounding())){
        std::cerr << "HAN CHOCADO\n";
    }
}

std::vector<enemigos> juego::getenemigos(){
    return malignos;
    
}

player juego::getjugador(){
    return *jugador1;
}

void juego::colisionenemigos(){
    for(int i=0; i< malignos.size();i++){
        for(int j=0; j< malignos.size();j++){  
            if(i!=j && malignos[i].bounding().intersects(malignos[j].bounding())){
                //malignos[i].setvelocidad();
                std:cerr<< "Colisiona enemigo "<< i <<" con enemigo " <<j<<endl;
            }
        }
    }
}

void juego::colisionAro(){
    for(int i=0; i< malignos.size();i++){
        for(int j=0; j<numAros;j++){  
            if(malignos[i].bounding().intersects(_aros[j]->bounding())){
                std:cerr<< "Colisiona enemigo "<< i <<" con aro " <<j<<endl;
            }
        }
    }
}

void juego::crearJugador(float x, float y){
    jugador1 = new player(x, y, personaje);
}

void juego::crearAros(int num, sf::Texture& _tAro){
    numAros = num;
    _aros = new aro*[num];
    for(int n = 0; n < num; n++){
        _aros[n] = new aro(_tAro);
    }
}

aro** juego::getAros(){
    return _aros;
}

int juego::getNumAros(){
    return numAros;
}


void juego::crearBoss(){
    _boss = new boss();
}

boss* juego::getBoss(){
    return _boss;
}
 
void juego::compararMuerteMaligna(){
    for(int i=0;i<malignos.size();i++){
        //cout << "VIDA " << i <<": " << malignos[i].getvida() << std::endl;
        if(malignos[i].getvida()<=0){
            std::cout << "MUERTEEEE" << std::endl;
            //malignos.erase(malignos.begin()+(i-1));
            std::swap(malignos[i], malignos[malignos.size()-1]);
            malignos.pop_back();
            
        }
        
    }
}


void juego::restarvidaenemigo(int n){
    
    malignos[n].restarvida(1);
}