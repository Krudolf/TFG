#include <iostream>
#include <math.h>
#include "enemigos.h"
#include "sprite.h"
#include "vector2f.h"
#include <SFML/Graphics.hpp>

enemigos::enemigos(float posX, float posY, sf::Texture &t_Enemigo, int f){
    pos_Enemigo = new vector2f(posX, posY);
    lastPosEnemigo = new vector2f(posX, posY);
    posInter = new vector2f(0,0);
    
    vel_Enemigo = 0.22;
    fuerza=f;
    vida=10;
    
    s_Enemigo = new sprite(t_Enemigo);
    s_Enemigo->setOrigin(128/2,128/2);
    s_Enemigo->setPosition(pos_Enemigo->getVector2f().x, pos_Enemigo->getVector2f().y);
    s_Enemigo->setScale(0.5,0.5);
}

void enemigos::mover(sf::Vector2f direccion, float dt,int i, std::vector<enemigos> &enemigo){
    sf::Vector2f direc = normalize(direccion - pos_Enemigo->getVector2f());
    for(int j=0;j<enemigo.size();j++){
        if(i!=j){
            Vector2f source = pos_Enemigo->getVector2f() - enemigo[j].getPosition();
            float distancia = sqrt((source.x * source.x) + (source.y * source.y));
            if(distancia<70){
            direc += normalize(pos_Enemigo->getVector2f() - enemigo[j].getPosition());
            }
        }
    }
    float x = lastPosEnemigo->getVector2f().x + vel_Enemigo * dt * direc.x;
    float y = lastPosEnemigo->getVector2f().y + vel_Enemigo * dt * direc.y;
    pos_Enemigo->setVector2f(x,y);
}

Vector2f enemigos::normalize(const sf::Vector2f& source){
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

sf::Vector2f enemigos::getPosition(){
    return pos_Enemigo->getVector2f();
}

void enemigos::update(){
    lastPosEnemigo->setVector2f(pos_Enemigo->getVector2f().x, pos_Enemigo->getVector2f().y);
}

void enemigos::draw(sf::RenderWindow &window, float incTime){
    float x = lastPosEnemigo->getVector2f().x * (1.f - incTime) + pos_Enemigo->getVector2f().x * incTime;
    float y = lastPosEnemigo->getVector2f().y * (1.f - incTime) + pos_Enemigo->getVector2f().y * incTime;
    posInter->setVector2f(x,y);
    
    s_Enemigo->setPosition(posInter->getVector2f().x, posInter->getVector2f().y);
    window.draw(s_Enemigo->getSprite());
}

FloatRect enemigos::bounding(){
    return s_Enemigo->getLocalBounds();
}

void enemigos::danyo(int danyo){
    vida-=danyo;
    std::cerr<<vida;
}

int enemigos::getFuerza(){
    return fuerza;
}

bool enemigos::getclock(){
    bool ataque;
    if(relojillo.getElapsedTime().asMilliseconds()>500){
        ataque =true;
        relojillo.restart();
    }else{
        ataque=false;
    }
    return ataque;
}


void enemigos::restarvida(int n){
    vida -=n;
}

int enemigos::getvida(){
    return vida;
}