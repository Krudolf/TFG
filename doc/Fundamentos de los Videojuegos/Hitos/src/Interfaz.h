#include <SFML/Graphics.hpp>
#ifndef INTERFAZ_H
#define INTERFAZ_H

class Interfaz {
public:
    Interfaz();
    Interfaz(const Interfaz& orig);
    virtual ~Interfaz();
    void draw(sf::RenderWindow &window,sf::View vista);
    void quitarVida(int v){ if((vida-v)>=0){ vida=vida-v;} };
    void darVida(int v){ if((vida+v<=100)){vida=vida+v;} };
    bool haMuerto();
    int getVida(){return vida;};
    void drawReloj(sf::RenderWindow &window, sf::View vista, int tiempo);
    void rellenarVida();
    void rellenarExperiencia();
    void setOleada();
    void setEnemigos(int n);
    
private:
    int vida=100;
    int experiencia=0;
    int nivel=1;
    int oleada=1;
    int enemigos=4;
    sf::Font font;
};

#endif /* INTERFAZ_H */
