#include <SFML/Graphics.hpp>
#include "sprite.h"
#include "vector2f.h"


using namespace sf;

class enemigos {
public:
    friend class juego;
    enemigos(float posX, float posY, sf::Texture &t, int f);
    
    void mover(Vector2f pos_Player, float dt,int i,std::vector<enemigos> &enemigo);
    Vector2f normalize(const sf::Vector2f& source);
    
    Vector2f getPosition();

    void update();
    
    void draw(RenderWindow &window, float incTime);
    
    int getFuerza();
    
    FloatRect bounding();
    
    void danyo(int danyo);
    bool getclock();
    void restarvida(int n);
    int getvida();
    
private:
    vector2f* pos_Enemigo;
    vector2f* lastPosEnemigo;
    vector2f* posInter;
    
    float vel_Enemigo;

    sprite* s_Enemigo;
    
    int vida;
    int fuerza;
    int frame;
    
    sf::Clock relojillo;
};