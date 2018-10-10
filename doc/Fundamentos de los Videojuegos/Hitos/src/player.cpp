#include <iostream>
#include "player.h"
#include "sprite.h"

player::player(float posX, float posY, int perso){
    vel_Player = 0.2;
    
    pos_Player = new vector2f(posX/2, posY/2);
    lastPosPlayer = new vector2f(posX/2, posY/2);
    posInter = new vector2f(0,0);
    
    personaje = perso;
    
    vida=100;
    fuerza = 5;
    experiencia=0;
    
    //std::cout << "PERSONAJE ELEGIDO: " << perso << std::endl;
    
    tipoSprite=1;
    abroCierro=0;
}

bool player::haMuerto(){
    if(vida==0){
        return true;
    }
    else{
        false;
    }
}

void player::moverDerecha(sf::Int32 dt){
    pos_Player->setVector2fX(lastPosPlayer->getVector2f().x+vel_Player*dt);
    s_Player->setTextureRect(128*2, 128, 128, 128);
    tipoSprite = 2;
    changeSprite.restart();
}

void player::moverIzquierda(sf::Int32 dt){
    pos_Player->setVector2fX(lastPosPlayer->getVector2f().x-vel_Player*dt);
    s_Player->setTextureRect(128*3, 128, 128, 128);
    tipoSprite = 3;
    changeSprite.restart();
}

void player::moverArriba(sf::Int32 dt){
    pos_Player->setVector2fY(lastPosPlayer->getVector2f().y-vel_Player*dt);
    s_Player->setTextureRect(128*1, 128, 128, 128);
    tipoSprite = 4;
    changeSprite.restart();
}

void player::moverAbajo(sf::Int32 dt){
    pos_Player->setVector2fY(lastPosPlayer->getVector2f().y+vel_Player*dt);
    s_Player->setTextureRect(128*0, 128, 128, 128);
    tipoSprite = 1;
    changeSprite.restart();
}

sf::Vector2f player::getPosition(){
    return pos_Player->getVector2f();
}

void player::update(){
    lastPosPlayer->setVector2f(pos_Player->getVector2f().x,pos_Player->getVector2f().y);
    //std::cout << "Posicion(" << pos_Player.x << "," << pos_Player.y << ")" << std::endl;
}
void player::update1(){
    pos_Player->setVector2f(lastPosPlayer->getVector2f().x,lastPosPlayer->getVector2f().y);
    //std::cout << "Posicion(" << pos_Player.x << "," << pos_Player.y << ")" << std::endl;
}

void player::draw(sf::RenderWindow &window, float incTime){
    float posX=lastPosPlayer->getVector2f().x * (1.f - incTime) + pos_Player->getVector2f().x * incTime;
    float posY=lastPosPlayer->getVector2f().y * (1.f - incTime) + pos_Player->getVector2f().y * incTime;    
    
    posInter->setVector2f(posX,posY);
    
    s_Player->setPosition(posInter->getVector2f().x, posInter->getVector2f().y);
    window.draw(s_Player->getSprite());
}
void player::setPosition(int x, int y){
    pos_Player->setVector2f(x,y);
}

FloatRect player::bounding(){
    return s_Player->getLocalBounds();
}

void player::quitaVida(int danyo){
    if((vida-danyo)>=0){
        vida-=danyo;
    }
}

int player::getVida(){
    return vida;
}

void player::cambiarSprite(){
    if(changeSprite.getElapsedTime().asMilliseconds() > 500){
        if(tipoSprite==1){
            if(abroCierro==0){
                s_Player->setTextureRect(128*0, 128*0, 128, 128);
                abroCierro=1;
            }else{
                s_Player->setTextureRect(128*0, 128, 128, 128);
                abroCierro=0;
            }
        }
        else if(tipoSprite==2){
            if(abroCierro==0){
                s_Player->setTextureRect(128*2, 128*0, 128, 128);
                abroCierro=1;
            }else{
                s_Player->setTextureRect(128*2, 128, 128, 128);
                abroCierro=0;
            }
        }
        else if(tipoSprite==3){
            if(abroCierro==0){
                s_Player->setTextureRect(128*3, 128*0, 128, 128);
                abroCierro=1;
            }else{
                s_Player->setTextureRect(128*3, 128, 128, 128);
                abroCierro=0;
            }
        }
        else if(tipoSprite==4){
            if(abroCierro==0){
                s_Player->setTextureRect(128*1, 128*0, 128, 128);
                abroCierro=1;
            }else{
                s_Player->setTextureRect(128*1, 128, 128, 128);
                abroCierro=0;
            }  
        }
    changeSprite.restart();
    }
}

void player::rellenarVida(){
    vida=100;
}

void player::setVel(float vel){
    vel_Player=vel;
}

void player::setExperiencia(){
    experiencia +=10;
}

int player::getExperiencia(){
    return experiencia;
}

int player::getFuerza(){
    return fuerza;
}

void player::setPersonaje(int per){
    personaje = per;
    
    if(per == 0)
        tPlayer = new textura("resources/azulfinal.png");
    else
        tPlayer = new textura("resources/verdefinal.png");
    
    std::cout << "\n\n Personaje elegido: " << per << "\n\n" << std::endl;
    
    s_Player = new sprite(tPlayer->getTextura());
    //s_Player = new sprite(tPl->getTextura());
    s_Player->setOrigin(128/2,128/2);
    s_Player->setTextureRect(128*0, 128, 128, 128);
    s_Player->setScale(0.5,0.5);
    s_Player->setPosition(pos_Player->getVector2f().x, pos_Player->getVector2f().y);
}

int player::getPersonaje(){
    return personaje;
}