#include <SFML/Graphics.hpp>
#include "sprite.h"
#include "textura.h"
#include "vector2f.h"

using namespace sf;

class player {
public:
    player(float posX, float posY, int perso);

    void moverDerecha(sf::Int32 dt);
    
    void moverIzquierda(sf::Int32 dt);
    
    void moverArriba(sf::Int32 dt);
    
    void moverAbajo(sf::Int32 dt);
    
    bool haMuerto();
    
    sf::Vector2f getPosition();
    
    void update();
    void update1();
    
    void draw(sf::RenderWindow &window, float incTime);
    
    void setPosition(int x, int y);
    
    void quitaVida(int danyo);
    int getVida();
    FloatRect bounding();
    
    void cambiarSprite();
    
    void rellenarVida();
    
    void setVel(float vel);
   
    void setExperiencia();
    int getExperiencia();
    
    int getFuerza();
    void setPersonaje(int per);
    int getPersonaje();
private:
    vector2f* pos_Player;
    vector2f* lastPosPlayer;
    vector2f* posInter;
    
    float vel_Player;
    
    sprite* s_Player;
    textura* tPlayer;
    
    sf::Clock changeSprite;
    
    int vida;
    int fuerza; 
    int experiencia;
    
    int tipoSprite;
    int abroCierro;
    
    int personaje;
};