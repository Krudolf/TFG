#include <SFML/Graphics.hpp>

#include <iostream>
#include "textura.h"

textura::textura(const std::string &url){
    if(!text.loadFromFile(url)){
        std::cout << "No se ha podido cargar la imagen " << url << std::endl;
    }
}

textura::~textura(){
}

sf::Texture& textura::getTextura(){
    return text.operator =(text);
}