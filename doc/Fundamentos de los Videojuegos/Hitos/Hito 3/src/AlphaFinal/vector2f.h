#ifndef VECTOR2F_H
#define VECTOR2F_H

class vector2f {
public:
    vector2f(float px, float py);
    virtual ~vector2f();
    
    sf::Vector2f getVector2f();
    
    void setVector2f(float px, float py);
    void setVector2fX(float px);
    void setVector2fY(float py);
private:
    sf::Vector2f vector;
};

#endif /* VECTOR2F_H */