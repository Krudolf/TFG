#ifndef TEXTURA_H
#define TEXTURA_H

class textura {
public:
    textura(const std::string &url);
    virtual ~textura();
    
    sf::Texture& getTextura();
    
private:
    sf::Texture text;

};

#endif /* TEXTURA_H */