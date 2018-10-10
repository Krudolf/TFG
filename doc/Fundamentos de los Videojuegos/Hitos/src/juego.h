#ifndef JUEGO_H
#define JUEGO_H
#include "aro.h"
#include "player.h"
#include "enemigos.h"
#include "boss.h"

#include <vector>
#include <SFML/Graphics.hpp>

#include "textura.h"

using namespace sf;
using namespace std;

class juego {
public:
    juego();
    virtual ~juego();
    
    void comprobarcolisiones(enemigos e);
    void crearenemigos(int n,int vida,int fuerza);
    player getjugador();
    void crearJugador(float x, float y);
    void colisionenemigos();
    void setPersonaje(int p);
   
    std::vector<enemigos> getenemigos();
    
    void crearAros(int num, sf::Texture& _tAro);
    aro** getAros();
    int getNumAros();
    
    void crearBoss();
    boss* getBoss();
    
    void colisionAro();
 
    void compararMuerteMaligna();
    
    void restarvidaenemigo(int n);
    
private:

    std::vector<enemigos> malignos;
    player* jugador1; //Variable de instancia donde se almacena el jugador
    int personaje;
    sf::Texture t_Enemigo, tAro;
   
    textura* tPlayer;
    
    aro** _aros;
    int numAros;
    
    boss* _boss;
};

#endif /* JUEGO_H */
