#include <SFML/Graphics.hpp>
#include "Interfaz.h"

Interfaz::Interfaz() {
    
    vida=100;
    experiencia=0;
    nivel=1;
    oleada=1;
    enemigos=4;

}

void Interfaz::rellenarExperiencia(){
    experiencia +=10;
}

void Interfaz::setOleada(){
    oleada +=1;
}

void Interfaz::setEnemigos(int n){
    enemigos+=n;
}

bool Interfaz::haMuerto(){
    if(vida==0){
        return true;
    }
    else{
        false;
    }
}
void Interfaz::draw(sf::RenderWindow &window,sf::View vista) {
    
    if (!font.loadFromFile("resources/arial.ttf"))
	{
		// handle error
	}
 
sf::Color color(30, 212, 234); //vida
sf::Color color4(255, 109, 0); //experiencia
sf::Color color5(155, 186,186); //fondo nivel
sf::Color color2(23, 164, 181); //fondo vida
sf::Color color3(178,77,0); //fondo experiencia
 

 
 float vidaRestante=vida*1.0;
 sf::RectangleShape vidaPersonaje(sf::Vector2f(vidaRestante*1.5,15));
 vidaPersonaje.setFillColor(color);
 vidaPersonaje.setPosition(vista.getCenter().x-450,vista.getCenter().y-375); //100 35
 

 sf::RectangleShape fondoVidaPersonaje(sf::Vector2f(100*1.5,15));
 fondoVidaPersonaje.setFillColor(color2);
 fondoVidaPersonaje.setPosition(vista.getCenter().x-450,vista.getCenter().y-375); //100 35
 
 
float experienciaRestante=experiencia*1.0;
sf::RectangleShape experienciaPersonaje(sf::Vector2f(experienciaRestante*1.5,7.5));
experienciaPersonaje.setFillColor(color4);
experienciaPersonaje.setPosition(vista.getCenter().x-450,vista.getCenter().y-360); //100 50

sf::RectangleShape fondoExperienciaPersonaje(sf::Vector2f(100*1.5,7.5));
fondoExperienciaPersonaje.setFillColor(color3);
fondoExperienciaPersonaje.setPosition(vista.getCenter().x-450,vista.getCenter().y-360); //100 50

 sf::CircleShape nivelFondo(15);
 nivelFondo.setFillColor(color5);
 nivelFondo.setPosition(vista.getCenter().x-480,vista.getCenter().y-378.5); //70 31.5

sf::Text nivelPersonaje;
nivelPersonaje.setFont(font);
std::string lv = "";
lv= std::to_string(nivel);
nivelPersonaje.setString(lv);
nivelPersonaje.setCharacterSize(20);
nivelPersonaje.setColor(sf::Color::White);
nivelPersonaje.setPosition(vista.getCenter().x-472.5,vista.getCenter().y-376); //78.5 34

/*sf::Texture h1;
h1.loadFromFile("resources/discos.png");
sf::Sprite habilidad1(h1);
habilidad1.setScale(0.06,0.06);
habilidad1.setPosition(vista.getCenter().x-448,vista.getCenter().y-325); //102 70

sf::Texture h2;
h2.loadFromFile("resources/discos.png");
sf::Sprite habilidad2(h2);
habilidad2.setScale(0.06,0.06);
habilidad2.setPosition(vista.getCenter().x-408,vista.getCenter().y-325); //142 70

sf::Texture h3;
h3.loadFromFile("resources/discos.png");
sf::Sprite habilidad3(h3);
habilidad3.setScale(0.06,0.06);
habilidad3.setPosition(vista.getCenter().x-368,vista.getCenter().y-325); //182 70
*/
sf::Text tOleada;
tOleada.setFont(font);
tOleada.setString("Oleada");
tOleada.setPosition(vista.getCenter().x+200,vista.getCenter().y-375); //1000 34
tOleada.setCharacterSize(20);

sf::Text numOleada;
numOleada.setFont(font);
std::string ol = "";
ol= std::to_string(oleada);
numOleada.setString(ol);
numOleada.setCharacterSize(20);
numOleada.setColor(sf::Color::White);
numOleada.setPosition(vista.getCenter().x+200,vista.getCenter().y-345); //1025 60

sf::Text tEnemigos;
tEnemigos.setFont(font);
tEnemigos.setString("Enemigos");
tEnemigos.setPosition(vista.getCenter().x+350,vista.getCenter().y-375); //1100 34
tEnemigos.setCharacterSize(20);

sf::Text numEnemigos;
numEnemigos.setFont(font);
std::string en = "";
en= std::to_string(enemigos);
numEnemigos.setString(en);
numEnemigos.setCharacterSize(20);
numEnemigos.setColor(sf::Color::White);
numEnemigos.setPosition(vista.getCenter().x+350,vista.getCenter().y-345); //1128 60


 window.draw(nivelFondo);
 window.draw(fondoVidaPersonaje);
 window.draw(vidaPersonaje);
 window.draw(fondoExperienciaPersonaje);
 window.draw(experienciaPersonaje);
 window.draw(nivelPersonaje);
 /*window.draw(habilidad1);
 window.draw(habilidad2);
 window.draw(habilidad3);*/
 window.draw(numOleada);
 window.draw(tOleada);
 window.draw(numEnemigos);
 window.draw(tEnemigos);
    
    
}

void Interfaz::drawReloj(sf::RenderWindow &window, sf::View vista, int tiempo){
    sf::Text tReloj;
    tReloj.setFont(font);
    std::string t = "";
    t = std::to_string(tiempo);
    tReloj.setString(t);
    tReloj.setPosition(vista.getCenter().x,vista.getCenter().y-380); //1000 34
    tReloj.setCharacterSize(50);
    window.draw(tReloj);
}


Interfaz::Interfaz(const Interfaz& orig) {
}

Interfaz::~Interfaz() {
}

void Interfaz::rellenarVida(){
    vida=100;
}





