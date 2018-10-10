#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "renderWindow.h"

renderWindow::renderWindow(int width, int height){
    window.create(sf::VideoMode(width, height), "Alpha");
}

renderWindow::renderWindow(const renderWindow& orig) {
}

renderWindow::~renderWindow() {
}

void renderWindow::create(int width, int height){
    window.create(sf::VideoMode(width, height), "Alpha");
}

void renderWindow::clear(){
    window.clear();
}

void renderWindow::display(){
    window.display();
}

void renderWindow::draw(sf::Sprite sprite){
    window.draw(sprite);
}

void renderWindow::close(){
    window.close();
}

void renderWindow::setFrames(unsigned int FPS){
    window.setFramerateLimit(FPS);
}

bool renderWindow::isOpen(){
    return window.isOpen();
}

bool renderWindow::pollEvent(sf::Event &event){
    return window.pollEvent(event);
}

void renderWindow::setView(sf::View vista){
    window.setView(vista);
}

sf::Vector2u renderWindow::getSize(){
    window.getSize();
}