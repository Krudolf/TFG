#ifndef BOSS_H
#define BOSS_H
#include <SFML/Graphics.hpp>

#include "aro.h"
#include "textura.h"
#include "sprite.h"
#include "vector2f.h"

using namespace sf;

class boss {
public:
    boss();
    void draw(sf::RenderWindow &window, float incTime);
    void update();
    void movimiento(sf::Vector2f pos_Player, float dt, FloatRect bound);
    void atBasico(Vector2f direccion, float dt);
    void movimiento1(Vector2f direccion, float dt);
    void movimiento2(Vector2f direccion, float dt, Vector2f pos_Player, FloatRect bound);
    Vector2f normalize(const Vector2f& source);
    Vector2f getPosition();
    void setPosition(sf::Vector2f posJug);
    void mover(sf::Vector2f direccion, float dt);
    Vector2f invertirDir(Vector2f direccion);
    
    void drawAtaque(sf::RenderWindow &window, float pt);
    
    int getGolpe();
    void quitarVida(int dam);
    
    void restartClocks();
    
    sf::FloatRect getBounding();
    
    bool getVivo();
    void setVivo(bool v);
    
private:
    textura* textBoss;
    textura* tAroBoss;
    sprite* spriteBoss;
    vector2f* position;
    vector2f* posAnterior;
    vector2f* posInter;
    float velMovimiento;
    float distancia;
    sf::Clock clock, bas;
    sf::Clock at1, at2;
    int ata1, ata2, ata3;
    bool atak1, atak2;
    
    aro *aroBoss;
    int golpe;
    
    int vida;
    sf::FloatRect bounding;
    
    bool vivo;
};

#endif /* BOSS_H */
