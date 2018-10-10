#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include "boss.h"

using namespace sf;

boss::boss() {
    position = new vector2f(0,0);
    posAnterior = new vector2f(0,0);
    posInter = new vector2f(0,0);
    
    velMovimiento = 0.15;
    ata1 = 0;
    ata2 = 0;
    ata3 = 0;
    
    atak1 = false;
    atak2 = false;
    
    golpe = 0;
    
    vida = 100;
    vivo = false;
    
    textBoss =new textura("resources/boss.png");
    
    tAroBoss = new textura("resources/balaboss.png");
    
    spriteBoss=new sprite(textBoss->getTextura());
    spriteBoss->setOrigin(128/2,128/2);
    spriteBoss->setTextureRect(128*0, 128*0, 128, 128);
    spriteBoss->setScale(1,1);
}

void boss::draw(sf::RenderWindow &window, float incTime){
    float x = posAnterior->getVector2f().x * (1.f-incTime)+position->getVector2f().x*incTime;
    float y = posAnterior->getVector2f().y * (1.f-incTime)+position->getVector2f().y*incTime;
    
    posInter->setVector2f(x,y);
    
    spriteBoss->setPosition(posInter->getVector2f().x, posInter->getVector2f().y);
    
    window.draw(spriteBoss->getSprite());
}

void boss::movimiento(sf::Vector2f pos_Player, float dt, sf::FloatRect bound){
    sf::Vector2f direccion = normalize(pos_Player - position->getVector2f());
    
    if(at1.getElapsedTime().asMilliseconds() > 4000)
        ata1 = 1;
    if(at2.getElapsedTime().asMilliseconds() > 10000)
        ata2 = 1;
    
    golpe = 0;
    if(ata1 == 1 && !atak2){
        if(distancia > 200 && !atak1){
            atak1 = true;
            clock.restart();
        }
        if(atak1){
            movimiento1(direccion, dt);
            if(clock.getElapsedTime().asMilliseconds() > 3000){
                atak1 = false;
                ata1 = 0;
                at1.restart();
            }
        }
    }

    if(ata2 == 1 && !atak1){
        if(distancia > 40 && !atak2){
            atak2 = true;
            clock.restart();
            aroBoss = new aro(position->getVector2f(), tAroBoss->getTextura());
        }
        if(atak2){
            movimiento2(direccion, dt, pos_Player, bound);
            atBasico(direccion, dt);
            if(clock.getElapsedTime().asMilliseconds() > 2000){
                atak2 = false;
                ata2 = 0;
                at2.restart();
            }
        }
    }    
    if(!atak1 && !atak2){
        if(distancia < 500){
            direccion = invertirDir(direccion);
        }
        atBasico(direccion, dt);        
    }
}

void boss::atBasico(sf::Vector2f direccion, float dt){
    //movimiento como el de un enemigo normal
    velMovimiento = 0.05;
    mover(direccion, dt);
    if(bas.getElapsedTime().asMilliseconds() >= 250 && distancia < 20){
        golpe = 5;
        bas.restart();
    }
}

void boss::movimiento1(sf::Vector2f direccion, float dt){
    //movimiento de velocidad ultra hacia el jugador cuando esta proximo (*2->acelracion)
    velMovimiento = 0.35;
    mover(direccion, dt);
    if(distancia < 20){
        std::cout << "Jugador dañado" << std::endl;
        golpe = 10;
    }
}

void boss::movimiento2(sf::Vector2f direccion, float dt, sf::Vector2f pos_Player, sf::FloatRect bound){
    aroBoss->lanzarAtaque(direccion, dt);
    //std::cout << "Bounding: " << aroBoss->bounding().left << ", " << aroBoss->bounding().top << ", " << aroBoss->bounding().width << ", " << aroBoss->bounding().height << std::endl;
    if(aroBoss->bounding().intersects(bound)){
        golpe = 1;
    }
}

Vector2f boss::normalize(const sf::Vector2f& source){
    distancia = sqrt((source.x * source.x) + (source.y * source.y));
    //std::cout << "Distancia: " << distancia << std::endl;
    if (distancia != 0){
        sf::Vector2f direccion(source.x / distancia, source.y / distancia);
        return direccion;
    }else
        return source;
}

void boss::update(){
    posAnterior->setVector2f(position->getVector2f().x, position->getVector2f().y);
    if(atak2){
        aroBoss->update();
    }
}

sf::Vector2f boss::getPosition(){
    return position->getVector2f();
}

void boss::setPosition(sf::Vector2f posJug){
    position->setVector2f(posJug.x+200, posJug.y);
}

void boss::mover(sf::Vector2f direccion, float dt){
    float x = posAnterior->getVector2f().x+velMovimiento*dt*direccion.x;
    float y = posAnterior->getVector2f().y +velMovimiento*dt*direccion.y;
    
    position->setVector2f(x,y);
}

int boss::getGolpe(){
    return golpe;
}

void boss::quitarVida(int dam){
    vida -= dam;
    if(vida <= 0){
        vivo = false;
        std::cout << "EL BOSS HA MUERTO!" << std::endl;
    }
}

bool boss::getVivo(){
    return vivo;
}

void boss::setVivo(bool v){
    vivo = v;
}

sf::Vector2f boss::invertirDir(Vector2f direccion){
    direccion.x = std::abs(direccion.x);
    direccion.y = std::abs(direccion.y);
    direccion = -direccion;
    
    return direccion;
}

void boss::drawAtaque(sf::RenderWindow &window, float pt){
    if(atak2){
        aroBoss->draw(window, pt);
    }
}

void boss::restartClocks(){
    clock.restart();
    bas.restart();
    at1.restart();
    at2.restart();
}

sf::FloatRect boss::getBounding(){
    //return spriteBoss.getLocalBounds();
}