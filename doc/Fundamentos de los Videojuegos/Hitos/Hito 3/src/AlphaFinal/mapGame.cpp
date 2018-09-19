#include <SFML/Graphics.hpp>
#include "tinyxml.h"
#include "mapGame.h"

using namespace std;

mapGame::mapGame(string urlXML, string urlTiles) {
    _numLayers = 0, _height = 0, _width = 0, frame = 0, totalP = 0;
    //Cargamos el archivo mapa.tmx para poder leerlo
    TiXmlDocument doc = loadXML(urlXML);
    std::cout << "XML se ha leido correctamente." << std::endl;
    
    //Cargamos la textura donde estan todos los tiles para poder mostrarlos
    _tilesetTexture = loadTiles(urlTiles);
    std::cout << "Tiles se ha leido correctamente." << std::endl;
    
    //Inicializamos variables para la lectura del archivo XML
    /*
    int _numLayers = 0;
    int _height = 0;
    int _width = 0;
    */
    int _tileheight = 0, _tilewidth = 0;
    int _tsw, _tsh;
    int _imgWidth, _imgHeight;
    
    /* 
     * 
     * LEEMOS EL ARCHIVO TMX Y OBTENEMOS LOS DATOS 
     *
     */
    TiXmlElement *mapa = doc.FirstChildElement("map");
    
    //Obtenemos el tamaño en ancho y largo del mapa, y el tamaño ancho y largo de los tiles.
    mapa->QueryIntAttribute("width" , &_width);
    mapa->QueryIntAttribute("height" , &_height);
    mapa->QueryIntAttribute("tilewidth" , &_tilewidth);
    mapa->QueryIntAttribute("tileheight" , &_tileheight);
    std::cout << "MAPA ------> " << "Width: " << _width << " Heiht: " << _height << " TileWidht: " << _tilewidth << " TileHeight: " << _tileheight << std::endl;
    
    //Obtenemos el tamaño de los tiles.
    TiXmlElement *tileset = mapa->FirstChildElement("tileset");
    tileset->QueryIntAttribute("tilewidth" , &_tsw);
    tileset->QueryIntAttribute("tileheight" , &_tsh);
    std::cout << "TILESET ---> " << "TileWidht: " << _tsw << " TileHeight: " << _tsh << std::endl;
    
    //Obtenemosla imagen del tileset.
    TiXmlElement *img = mapa->FirstChildElement("tileset")->FirstChildElement("image");
    const char *filename = img->Attribute("source");
    img->QueryIntAttribute("width" , &_imgWidth);
    img->QueryIntAttribute("height" , &_imgHeight);
    std::cout << "IMAGEN ----> " << "Width: " << _imgWidth << " Heiht: " << _imgHeight << std::endl;
    
    //Contamos el numero de capas que tiene el TMX.
    TiXmlElement *capa = mapa->FirstChildElement("layer");
    while(capa){
        _numLayers++;
        capa = capa->NextSiblingElement("layer");
    }
    std::cout << "NUMERO DE CAPAS: " << _numLayers << std::endl;
    
    /*
     *
     * GUARDAMOS EN UN ARRAY TODOS LOS TILES
     *
     */
    std::cout << "EMPEZAMOS BUCLE DE ARRAY DE SPRITES!"<< std::endl;
    colums = _imgWidth/_tilewidth;
    rows = _imgHeight/_tileheight;
    int pos = 0;
    sf::Sprite *_tilesetSprite=new sf::Sprite[rows*colums+1];
    for(int i=0; i<=rows-1; i++){
        for (int j=0; j<colums; j++){
            pos++;
            _tilesetSprite[pos].setTexture(_tilesetTexture);
            _tilesetSprite[pos].setTextureRect(sf::IntRect(32*j,32*i,32,32));
            //::cout << 32*j << "," << 32*i << std::endl;
            //std::cout << "(" << 32*i << "," << 32*j << ",32,32)" << std::endl;
        }
    }
    std::cout << "BUCLE DE ARRAY DE SPRITES TERMINADO!"<< std::endl;
    std::cout << "Posiciones: " << pos << std::endl;
    std::cout << "_tilemap[" << _numLayers << "][" << _height << "][" << _width << "]" << std::endl;
    
    //int _tilemap[_numLayers][_height][_width];
    
    //std::cout << "_tilemap[" << _numLayers << "][" << _height << "][" << _width << "]\nEmpezamos!" << std::endl;
    //Carga los GUID's
    TiXmlElement *data[_numLayers];
    TiXmlElement *layer;
    data[0] = mapa->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    layer = mapa->FirstChildElement("layer");
    
    _tilemap = new int**[_numLayers];
    
    for(int l = 0; l < _numLayers; l++){
        _tilemap[l] = new int*[_height];
    }    
    
    for(int l=0; l < _numLayers; l++){
        for(int y=0; y < _height; y++){
            _tilemap[l][y] = new int[_width];
            for(int x=0; x < _width; x++){
                data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                data[l] = data[l]->NextSiblingElement("tile");
            }
        }
        if(data[l]== 0){
            //data[l+1] = data[l]->Parent()->Parent()->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
            if(layer->NextSiblingElement("layer") != 0)
                layer = layer->NextSiblingElement("layer");
            
            data[l+1] = layer->FirstChildElement("data")->FirstChildElement("tile");
        }
    }
    std::cout << "Array de GUI's rellenado correctamente!" << std::endl;
    
    /*
     * 
     * Declaracion la matriz 4D [layer][width][height]
     * 
     */
    //sf::Sprite ****_tileMapSprite;
    //Reserva de memoria para la matriz 4D
    _tileMapSprite = new sf::Sprite***[_numLayers];
    
    for(int l = 0; l < _numLayers; l++){
        _tileMapSprite[l] = new sf::Sprite**[_height];
    }
    for(int l = 0; l < _numLayers; l++){
        for(int y = 0; y < _height; y++){
            _tileMapSprite[l][y] = new sf::Sprite*[_width];
            for(int x = 0; x < _width; x++){
                _tileMapSprite[l][y][x] = new sf::Sprite();
                //std::cout << "_tileMapSprite[" << l << "][" << y << "][" << x << "]" << std::endl;
                //std::cout << _tileMapSprite[l][y][x] << std::endl;
            }
        }
    }
    std::cout<< "Se acabo la reserva de la 4D" << std::endl;
    
    /*
     * 
     * Creacion del array de Sprites
     * 
     */
    int caca = 0;
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                int gid = _tilemap[l][y][x];
                if(gid >= _tsw*_tsh){
                    std::cout << "Error, gid at (l,x,y) = (" << l << "," << x << "," << y << "): "
                            << gid << " fuera del rango del tileset ("<<_tsw*_tsh<<")" << std::endl;
                }
                else if(gid > 0){
                    //std::cout << "_tileMapSprite[" << l << "][" << y << "][" << x << "]" << std::endl;
                    _tileMapSprite[l][y][x]->setTextureRect(_tilesetSprite[gid].getTextureRect());
                    _tileMapSprite[l][y][x] = new sf::Sprite(_tilesetTexture, _tilesetSprite[gid].getTextureRect());
                    _tileMapSprite[l][y][x]->setPosition(x*_tilewidth, y*_tileheight);
                    //if(l == 2)
                        //std::cout << "[" << l << "][" << y << "][" << x << "] -- " << gid << std::endl;
                }
                else{
                    _tileMapSprite[l][y][x] = NULL;
                    if(l == 2){
                        caca++;
                        
                    }
                }
            }
        }
    }
    //std::cout << "nulles: " << caca << std::endl;
    std::cout << "Se ha creado correctamente el array de Sprites" << std::endl;
    pinchos();
    pruebas();
    bolitas();
    num = 3;
}

TiXmlDocument mapGame::loadXML(string url){
    TiXmlDocument doc;
    if(!doc.LoadFile(url)){
        std::cout << "No se ha podido cargar el archivo .tmx" << std::endl;
        exit(0);
    }
    return doc;
}

sf::Texture mapGame::loadTiles(string url){
    sf::Texture tile;
    if (!tile.loadFromFile(url)){
        std::cerr << "Error cargando la textura .png";
        exit(0);
    }
    return tile;
}

void mapGame::draw(sf::RenderWindow &window){
    for(int y=0; y < _height; y++){
        for(int x=0; x < _width; x++){
            if(_tileMapSprite[_activeLayer][y][x] != NULL){
                window.draw(*(_tileMapSprite[_activeLayer][y][x]));

            }
        }
    }
}

void mapGame::setActiveLayer(int layer){
    _activeLayer = layer;
}

bool mapGame::colisiona(int y, int x){
    bool caca=false;
    //std::cout << "_parametros[" << l << "][" << y << "][" << x << "]" << std::endl;
    if(_tileMapSprite[1][y][x] != NULL){
        caca=true;
    }
    return caca;
}

void mapGame::pinchos(){
    int i=8; //(fila)
    int j=14; //(columna)
    for(int pos=0; pos<4; pos++){
        _spritePinchos[pos].setTexture(_tilesetTexture);
        _spritePinchos[pos].setTextureRect(sf::IntRect(32*j,32*i,32,32));
        j=j-3;
    }
    totalPinchos=0;
    for(int y=0; y<_height; y++){
        for(int x=0; x<_width; x++){
            if(_tileMapSprite[2][y][x] != NULL && _tilemap[2][y][x]==143){
                totalPinchos++;
            }
        }
    }
    posPinchos=new int *[2];
    
    for (int i=0; i<2; i++){
        posPinchos[i]=new int[totalPinchos];
    }
    
    int aux=0;
    for(int x=0; x<_width; x++){
        for(int y=0; y<_height; y++){
            if(_tileMapSprite[2][y][x]!=NULL && _tilemap[2][y][x]==143){
                posPinchos[0][aux]=x*32;
                posPinchos[1][aux]=y*32;
                aux++;
            }
        }
    }
}
void mapGame::drawPinchos(sf::RenderWindow &window){
    for(int j=0; j<totalPinchos; j++){
        _spritePinchos[frame].setPosition(posPinchos[0][j],posPinchos[1][j]);
        window.draw(_spritePinchos[frame]);
    }
}

bool mapGame::colisionaPinchos(int y, int x){
    bool caca=false;
    //std::cout << "_parametros[" << l << "][" << y << "][" << x << "]" << std::endl;
    if(_tileMapSprite[2][y][x] != NULL && _tilemap[2][y][x]==143){
        caca=true;
        //std::cout << "colisionnn"<< std::endl;
    }
    return caca;
}

void mapGame::pruebas(){
    int i=10;
    int j=6;
    for(int pos=0; pos<3; pos++){
        _spritePruebas[pos].setTexture(_tilesetTexture);
        _spritePruebas[pos].setTextureRect(sf::IntRect(32*j,32*i,32,32));
        _spritePruebas[pos].setScale(1.5,1.5);
        j++;
    }
    
    int total=0;
    for(int y=0; y<_height; y++){
        for(int x=0; x<_width; x++){
            if(_tileMapSprite[2][y][x] != NULL && _tilemap[2][y][x]==166){
                total++;
            }
        }
    }
    posPruebas = new int *[3];
    for(int i=0; i<3; i++){
        posPruebas[i] = new int[total];
    }
    totalPruebas=total;
    
    int aux=0;
    for(int x=0; x<_width; x++){
        for(int y=0; y<_height; y++){
            if(_tileMapSprite[2][y][x]!=NULL && _tilemap[2][y][x]==166){
                posPruebas[0][aux]=x*32;
                posPruebas[1][aux]=y*32;
                posPruebas[2][aux]=0;
                aux++;
            }
        }
    }
    estado=false;
}

void mapGame::drawPruebas(sf::RenderWindow &window){
    int aux=0;
    for(int j=0; j<totalPruebas; j++){
        if(posPruebas[2][j]==1){
            _spritePruebas[2].setPosition(posPruebas[0][j],posPruebas[1][j]);
            window.draw(_spritePruebas[2]);
            aux++;
        }else{
            _spritePruebas[0].setPosition(posPruebas[0][j],posPruebas[1][j]);
            window.draw(_spritePruebas[0]);
        }
    }
}

bool mapGame::colisionaPruebas(int y, int x){
    bool caca=false;
    //std::cout << "_parametros[" << l << "][" << y << "][" << x << "]" << std::endl;
    if(_tileMapSprite[2][y][x] != NULL && _tilemap[2][y][x]==166){
        caca=true;
        //std::cout << "colisionnn"<< std::endl;
        for(int i=0; i<totalPruebas; i++){
            if(posPruebas[0][i]/32==x && posPruebas[1][i]/32==y){
                posPruebas[2][i]=1;
            }
        }
    }
    return caca;
}

void mapGame::nextFrame(){
    frame++;
    if(frame>3){
        frame=0;
    }
}

void mapGame::portal(){
    int i=11;
    int j=5;
    
    for(int pos=0; pos<3; pos++){
        _spritePortal[pos].setTexture(_tilesetTexture);
        _spritePortal[pos].setTextureRect(sf::IntRect(32*j,32*i,96,96));
        j=j+3;
    }
    _spritePortal[3].setTexture(_tilesetTexture);
    _spritePortal[3].setTextureRect(sf::IntRect(32*(j-6),32*i,96,96));
    
    totalPortal=0;
    for(int y=0; y<_height; y++){
        for(int x=0; x<_width; x++){
            if(_tileMapSprite[1][y][x] != NULL && _tilemap[1][y][x]==54){
                totalPortal++;
            }
        }
    }
    //std::cout<<"total:"<<total<<std::endl;
    
    pos = new int *[2];
    
    for(int i=0; i<2;  i++){
        pos[i] = new int[totalPortal];
    }
    
    int aux=0;
    for(int x=0; x<_width; x++){
        for(int y=0; y<_height; y++){
            if(_tileMapSprite[1][y][x]!=NULL && _tilemap[1][y][x]==54){
                pos[0][aux]=x*32;
                pos[1][aux]=y*32;
                aux++;
            }
        }
    }
}

void mapGame::drawPortal(sf::RenderWindow& window){
    for(int j=0; j<totalPortal; j++){
        _spritePortal[frame].setPosition(pos[0][j],pos[1][j]);
        window.draw(_spritePortal[frame]);
    }
}

bool mapGame::colisionaPortal(int y, int x){
    bool caca=false;
    for(int j=0; j<totalPortal; j++){
        //std::cout << "X: " << pos[0][j]/32+1 << ", " << x << std::endl;
        //std::cout << "Y: " << pos[1][j]/32+2 << ", " << y << std::endl;
        if(pos[0][j]/32+1==x && pos[1][j]/32+2==y){
            caca=true;
        }
    }
    return caca;
}

bool mapGame::getPortal(){
    return estado;
}
void mapGame::cambiarPortal(bool p){
    estado = p;
}

bool mapGame::salirSubMapa(){
    bool salir=false;
    
    if(totalPruebas!=0){
        salir=true;
    
        for(int i=0; i<totalPruebas; i++){
            if(posPruebas[2][i]!=1){
                salir = false;
            }
        }
    }
    return salir;
}

void mapGame::bolitas(){
    int i=5;
    int j=2;
    
    for(int pos=0; pos<3; pos++){
        _spriteBolitas[pos].setTexture(_tilesetTexture);
        _spriteBolitas[pos].setTextureRect(sf::IntRect(32*j,32*i,32,32));
        j++;
    }
    
    totalBolitas=0;
    for(int y=0; y<_height; y++){
        for(int x=0; x<_width; x++){
            if(_tileMapSprite[2][y][x] != NULL && _tilemap[2][y][x]==83){
                totalBolitas++;
            }
        }
    }
    std::cout<<"total:"<<totalBolitas<<std::endl;
    
    posBolitas = new int *[2];
    
    for(int i=0; i<2;  i++){
        posBolitas[i] = new int[totalBolitas];
    }
    
    int aux=0;
    for(int x=0; x<_width; x++){
        for(int y=0; y<_height; y++){
            if(_tileMapSprite[2][y][x]!=NULL && _tilemap[2][y][x]==83){
                posBolitas[0][aux]=x*32;
                posBolitas[1][aux]=y*32;
                aux++;
            }
        }
    }
    bolita=false;
}

bool mapGame::cogerBolitas(int x, int y){
    bool si=false;
    for(int j=0; j<totalBolitas; j++){
        //std::cout << "X: " << pos[0][j]/32+1 << ", " << x << std::endl;
        //std::cout << "Y: " << pos[1][j]/32+2 << ", " << y << std::endl;
        if(posBolitas[0][j]/32==x && posBolitas[1][j]/32==y){
            si=true;
            num = rand() % totalBolitas;
        }
    }
    return si;
}

void mapGame::drawBolita(sf::RenderWindow& window){
    for(int i=0; i<totalBolitas; i++){
        _spriteBolitas[0].setPosition(posBolitas[0][num],posBolitas[1][num]);
        window.draw(_spriteBolitas[0]);
    }
}

bool mapGame::getBolita(){
    return bolita;
}

void mapGame::bBolita(bool b){
    bolita=b;
}

bool mapGame::velSuelo(int x, int y){
    bool si=false;
    //std::cout << "_parametros[" << l << "][" << y << "][" << x << "]" << std::endl;
    if(_tileMapSprite[0][y][x] != NULL && _tilemap[0][y][x]==1){
        si=true;
    }
    return si;
}