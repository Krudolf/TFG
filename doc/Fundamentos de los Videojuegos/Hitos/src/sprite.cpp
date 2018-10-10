#include <SFML/Graphics.hpp>

#include <iostream>
#include "sprite.h"

sprite::sprite(const sf::Texture &text){
    sp.setTexture(text);
}

sprite::~sprite() {
}

void sprite::setTexture(const sf::Texture &text){
    sp.setTexture(text);
}

void sprite::setScale(float x, float y){
    sp.setScale(x,y);
}

sf::Sprite sprite::getSprite(){
    return sp;
}
/*const int &left, const int &top, const int &width, const int &height*/
void sprite::setTextureRect(int left, int top, int width, int height){
    sp.setTextureRect(sf::IntRect(left, top, width, height));
}

void sprite::setPosition(float x, float y){
    sp.setPosition(x, y);
}

void sprite::setOrigin(float x, float y){
    sp.setOrigin(x, y);
}

const sf::Vector2f& sprite::getPosition(){
    return sp.getPosition();
}

sf::FloatRect sprite::getLocalBounds(){
    return sp.getLocalBounds();
    //std::cout << "Bounding: " << aroBoss->bounding().left << ", " << aroBoss->bounding().top << ", " << aroBoss->bounding().width << ", " << aroBoss->bounding().height << std::endl;
}

void sprite::move(float x, float y){
    sp.move(x, y);
}