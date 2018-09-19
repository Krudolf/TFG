#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <math.h>
#include "aro.h"

aro::aro(sf::Texture &tAro){
    posicion = new vector2f(0,0);
    lastPos = new vector2f(0,0);
    posInter = new vector2f(0,0);
    
    velocidad = 0.5;
    jugadorSeleccionado=0;
    angle=0.0;
    angle_stepsize=0.6;
    
    dibujar = false;
    
    sAro = new sprite(tAro);
    
    sAro->setTextureRect(0, 0, 128, 128);
    sAro->setOrigin(128/2, 128/2);
    sAro->setPosition(posicion->getVector2f().x, posicion->getVector2f().y);
    sAro->setScale(0.5,0.5);
}
aro::aro(sf::Vector2f posBoss, sf::Texture& tAroBoss){
    posicion = new vector2f(posBoss.x, posBoss.y);
    lastPos = new vector2f(posBoss.x, posBoss.y);
    posInter = new vector2f(0,0);
    
    velocidad = 1;
    
    dibujar = true;
    
    sAro = new sprite(tAroBoss);
    
    sAro->setTextureRect(0, 0, 128, 128);
    sAro->setOrigin(128/2, 128/2);
    sAro->setPosition(posicion->getVector2f().x, posicion->getVector2f().y);
    sAro->setScale(0.5,0.5);
}
aro::~aro(){
    delete this;
}

void aro::draw(sf::RenderWindow& window, float pt){
    if(dibujar){
        float x = lastPos->getVector2f().x * (1.f - pt) + posicion->getVector2f().x * pt;
        float y = lastPos->getVector2f().y * (1.f - pt) + posicion->getVector2f().y * pt;
        posInter->setVector2f(x,y);
        
        sAro->setPosition(posInter->getVector2f().x, posInter->getVector2f().y);
        window.draw(sAro->getSprite());    
    }
}

void aro::setTextura(sf::Texture& tAro){
    sAro->setTexture(tAro);
}

void aro::update(){
    lastPos->setVector2f(posicion->getVector2f().x, posicion->getVector2f().y);
}

void aro::activar(sf::Vector2f posJug, char dir){
    dibujar = true;
    posicion->setVector2f(posJug.x, posJug.y);
    lastPos->setVector2f(posJug.x, posJug.y);
    dirAro = dir;
    clock.restart();
}
void aro::desactivar(){
    dibujar = false;
    posicion->setVector2f(0,0);
    lastPos->setVector2f(0,0);
    dirAro = 'x';
}
bool aro::getEstado(){
    return dibujar;
}

void aro::setPosition(sf::Vector2f posJ){
    sAro->setPosition(posJ.x, posJ.y);
}

void aro::mover(sf::Int32 dt){
    if(dirAro == 'w'){
        posicion->setVector2fY(lastPos->getVector2f().y - velocidad * dt);
        sAro->setTextureRect(128, 0, 128, 128);
    }else if(dirAro == 's'){
        posicion->setVector2fY(lastPos->getVector2f().y + velocidad * dt);
        sAro->setTextureRect(128, 0, 128, 128);
    }else if(dirAro == 'd'){
        posicion->setVector2fX(lastPos->getVector2f().x + velocidad * dt);
    }else if(dirAro == 'a'){
        posicion->setVector2fX(lastPos->getVector2f().x - velocidad * dt);
    }else if(dirAro == 'g'){
        posicion->setVector2fX(posJug1.x + (length * cos(angle))*10);
        posicion->setVector2fY(posJug1.y + (length * sin(angle))*10);
        angle += angle_stepsize;
    }
}

sf::Int32 aro::getTime(){
    return clock.getElapsedTime().asMilliseconds();
}

void aro::setPosEspecial(sf::Vector2f aqui){
    posJug1=aqui;
}

sf::FloatRect aro::bounding(){
    return sAro->getLocalBounds();
}

sf::Vector2f aro::getPosicion(){
    return posicion->getVector2f();
}

void aro::lanzarAtaque(sf::Vector2f dir, float dt){
    float x = lastPos->getVector2f().x + velocidad * dir.x * dt;
    float y = lastPos->getVector2f().y + velocidad * dir.y * dt;
    posicion->setVector2f(x,y);
}