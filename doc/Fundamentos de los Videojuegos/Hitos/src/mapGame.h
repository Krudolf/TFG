#include <SFML/Graphics.hpp>
#include "tinyxml.h"

using namespace std;

class mapGame {
public:
    mapGame(string urlXML, string urlTiles);
    
    TiXmlDocument loadXML(string url);
    
    sf::Texture loadTiles(string url);
    
    void draw(sf::RenderWindow &window);
    
    void setActiveLayer(int layer);
    
    bool colisiona(int y, int x);
    
    void pinchos();
    
    void pruebas();
    
    void drawPinchos(sf::RenderWindow &window);
    
    void drawPruebas(sf::RenderWindow &window);
    
    void nextFrame();
    void cambioPrueba();
    
    bool colisionaPinchos(int y, int x);
    bool colisionaPruebas(int y, int x);
    
    void portal();
    void drawPortal(sf::RenderWindow &window);
    bool colisionaPortal(int y, int x);
    bool getPortal();
    void cambiarPortal(bool p);
    
    bool salirSubMapa();
    
    void bolitas();
    bool cogerBolitas(int x, int y);
    void drawBolita(sf::RenderWindow &window);
    bool getBolita();
    void bBolita(bool b);
    
    bool velSuelo(int x, int y);
private:
    int _numLayers;
    int _height;
    int _width;
    int _activeLayer;
    
    sf::Texture _tilesetTexture;
    sf::Sprite**** _tileMapSprite;
    int*** _tilemap;
    int** pos; 
    int** posPruebas; 
    int** posBolitas;
    int** posPinchos;
    //posPruebas[3][total]
    
    sf::Sprite _spritePinchos[4];
    sf::Sprite _spritePruebas[3];
    sf::Sprite _spritePortal[4];
    sf::Sprite _spriteBolitas[3];
    
    int num;
    int colums;
    int rows;
    int frame;
    int totalP;
    int totalPortal;
    int totalPruebas;
    int totalBolitas;
    int totalPinchos;
    bool estado;
    bool bolita;
};
