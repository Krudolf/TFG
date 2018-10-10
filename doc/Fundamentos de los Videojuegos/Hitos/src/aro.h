#include <SFML/Graphics.hpp>
#include "sprite.h"
#include "textura.h"
#include "vector2f.h"

#ifndef ARO_H
#define ARO_H

class aro {
public:
    aro(sf::Texture &tAro);
    aro(sf::Vector2f posBoss, sf::Texture &tAroBoss);
    
    virtual ~aro();
    
    void draw(sf::RenderWindow &window, float pt);
    
    void update();
    
    void setPosition(sf::Vector2f posJ);
    sf::Vector2f getPosicion();
    
    void mover(sf::Int32 dt);
    
    sf::Int32 getTime();
    
    void activar(sf::Vector2f posJug, char dir);
    void desactivar();
    bool getEstado();
    
    void habilidad1();
    
    float getAngle();
    void setAngle(float ang);
    float getVel();
    float setVel(float num);
    void rotar(int a);
    void volver();
    void drawHab(sf::RenderWindow &window);
    sf::FloatRect bounding();
    
    
    void lanzarAtaque(sf::Vector2f dir, float dt);
    void setTextura(sf::Texture& tAro);
    void setPosEspecial(sf::Vector2f aqui);
    
    
    
private:
    vector2f* posicion;
    vector2f* lastPos;
    vector2f* posInter;
    
    sf::Vector2f posJug1;
    
    sprite* sAro;
    
    sf::Clock clock, hab;
    
    bool dibujar;
    
    char dirAro;
    float velocidad;
    
    float length=5;
    float x,y;
    float angle;
    float angle_stepsize;
    float pi = 3.1415927;
    int jugadorSeleccionado;
    
    
};

#endif /* ARO_H */
