#include <SFML/System/Vector2.hpp>

#include "vector2f.h"

vector2f::vector2f(float px, float py){
    vector.x = px;
    vector.y = py;
}

vector2f::~vector2f() {
}

sf::Vector2f vector2f::getVector2f(){
    return vector;
}

void vector2f::setVector2f(float px, float py){
    vector.x = px;
    vector.y = py;
}

void vector2f::setVector2fX(float px){
    vector.x = px;
}

void vector2f::setVector2fY(float py){
    vector.y = py;
}