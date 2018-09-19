#ifndef SPRITE_H
#define SPRITE_H

class sprite {
public:
    sprite(const sf::Texture &text);
    virtual ~sprite();
    
    void setTexture(const sf::Texture &text);
    void setScale(float x, float y);
    void setTextureRect(int left, int top, int width, int height);
    void setPosition(float x, float y);
    void setOrigin(float x, float y);
    
    const sf::Vector2f& getPosition();
    
    void move(float x, float y);
    
    sf::Sprite getSprite();
    sf::FloatRect getLocalBounds();
private:
    sf::Sprite sp;
    sf::Texture text;
};

#endif /* SPRITE_H */