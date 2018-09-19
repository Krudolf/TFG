#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

class renderWindow{
public:
    renderWindow(int width, int height);
    renderWindow(const renderWindow& orig);
    virtual ~renderWindow();
    
    void create(int width, int height);
    
    void useWindow();
    
    void clear();
    void display();
    void draw(sf::Sprite sprite);
    void close();
    
    void setFrames(unsigned int FPS);
    
    bool isOpen();
    
    bool pollEvent(sf::Event &event);
    
    void setView(sf::View vista);
    
    sf::Vector2u getSize();
    
private:
    sf::RenderWindow window;
};

#endif /* RENDERWINDOW_H */