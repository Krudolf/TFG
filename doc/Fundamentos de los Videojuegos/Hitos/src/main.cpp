#include <cstdlib>
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "mapGame.h"
#include "state.h"
#include "juego.h"
#include "Menu.h"
#include "Interfaz.h"
#include <stdio.h>  

using namespace std;

void inputSiempre(sf::RenderWindow &window,state &state);
void updateGame(sf::RenderWindow &window, sf::Int32 dt, player &jugador, std::vector<enemigos> &enemigo, mapGame &mapa, state &state, sf::Texture &tAro, sf::Clock &atak, aro** aros, int &act, int maxAros, boss* boss,juego &juego,Interfaz &interfaz, int &tiempo,int &oleada,Menu &menu,int jugadorSeleccionado);
void render(sf::RenderWindow &window, float percentTick, player jugador, std::vector<enemigos> enemigo, mapGame mapa, sf::View vista, state &state,Interfaz &interfaz, aro** aros, int maxAros, boss* boss, int &tiempo);
void updateMenu (sf::RenderWindow &window,Menu &menu,int &jugadorSeleccionado,int width,int height,state &state,juego &juego, player &jugador);
void renderMenu(sf::RenderWindow &window, Menu menu);
void GameOver(sf::RenderWindow &window, state &state, sf::View &vista,Menu &menu);
void Oleadas(sf::RenderWindow &window,juego &juego,int &oleada,std::vector<enemigos> &enemigo,Interfaz &interfaz, boss* boss,player &jugador,state &state,Menu &menu);
void Pausa(sf::RenderWindow &window, state &state, sf::View &vista,int &select,Menu &menu,boss* &boss);
void Ganar(sf::RenderWindow &window, state &state, sf::View &vista,int &select,Menu &menu,boss* &boss);


int main(int argc, char** argv){
    reinicio:
    const float TICK_TIME = 25;
    
    int width = 1300, height = 800;
    unsigned int FPS = 30;
    float percentTick = 0;
    string urlXML = "resources/mapa.tmx";
    string subUrlXML = "resources/submapa.tmx";
    string urlTiles = "resources/PlantillaMapa.png";
    int gameOverOneTime=0;
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Alpha");
    window.setFramerateLimit(FPS);
    
    sf::Clock reloj, tframe;
    int tiempo=100;
    
    
    sf::Int32 time, up, lastUp, dt, elapsedTime;
    up = 0;
    lastUp = 0;
    elapsedTime = 0;
    bool haMuerto=false;
    int selectPause=0;
    
    
    state state;
    state.cambiarEstado(1); //2 es el mapa normal, el JUGAR de alex
    
    juego juego;
    int oleada=1;
    
    juego.crearJugador(width, height);
    player jugador = juego.getjugador();
    
    
    juego.crearenemigos(4,10,10);
    std::vector<enemigos> enemigo=juego.getenemigos();
    
    
    sf::Texture tAro;
    
       
    sf::Clock atak;
    int act = 0, maxAros = 10;
    juego.crearAros(maxAros, tAro);    
    aro** aros = juego.getAros();
    
    boss* boss;
    juego.crearBoss();
    boss = juego.getBoss();
    
    
    mapGame mapa(urlXML, urlTiles);
    mapGame submapa(subUrlXML, urlTiles);
    sf::View vista;
    vista.reset(sf::FloatRect(0,0,width, height));
    
    Menu menu(window.getSize().x, window.getSize().y);
   
    
    Interfaz interfaz;
    int jugadorSeleccionado=0;
    
    
    while(window.isOpen()){ 
        time = reloj.getElapsedTime().asMilliseconds();
        
        if(state.GetEstado()==8){
            Ganar(window, state,vista,selectPause,menu,boss);
        }        
        if(state.GetEstado()==7){
            Pausa(window, state,vista,selectPause,menu,boss);
        }

        if(elapsedTime > TICK_TIME){
            lastUp = up;
            up = reloj.getElapsedTime().asMilliseconds();
            dt = up - lastUp;
            if(state.GetEstado()==5){
                GameOver(window,state, vista,menu);
                if(gameOverOneTime==0){
                menu.playGameOver();
                gameOverOneTime=1;
                }
            }
            if(state.GetEstado()==6){
                goto reinicio;
            }

            if(state.GetEstado()==2 || state.GetEstado()==4){
                updateGame(window, dt, jugador, enemigo, mapa, state, tAro, atak, aros, act, maxAros, boss,juego,interfaz, tiempo,oleada,menu,jugadorSeleccionado);
            }
            else if(state.GetEstado()==3){
                updateGame(window, dt, jugador, enemigo, submapa, state, tAro, atak, aros, act, maxAros, boss,juego, interfaz, tiempo,oleada,menu,jugadorSeleccionado);
            }
            if(act >= maxAros)
                act = 0;
        }
        if(state.GetEstado()==1){       
            updateMenu(window,menu,jugadorSeleccionado,width,height,state,juego, jugador);
        }
        inputSiempre(window,state);
        elapsedTime = time - up;
        percentTick = std::min(1.f, float(elapsedTime)/TICK_TIME);
        
        if(state.GetEstado()==1){
            renderMenu(window,menu);
        }

        else if(state.GetEstado() == 2 || state.GetEstado() == 4){
            if(tframe.getElapsedTime().asMilliseconds()>700){
                tframe.restart();
                mapa.nextFrame();
            }
            render(window, percentTick, jugador, enemigo, mapa, vista, state, interfaz, aros, maxAros, boss, tiempo);
        }
        else if(state.GetEstado()==3){
            render(window, percentTick, jugador, enemigo, submapa, vista, state, interfaz, aros, maxAros, boss, tiempo);
        }
        if(state.GetEstado() != 1){
            jugador.cambiarSprite();
        }
    }
    return 0;
}

void updateGame(sf::RenderWindow &window, sf::Int32 dt, player &jugador, std::vector<enemigos> &enemigo, mapGame &mapa, state &state, sf::Texture &tAro, sf::Clock &atak, aro** aros, int &act, int maxAros, boss* boss, juego &juego, Interfaz &interfaz, int &tiempo, int &oleada,Menu &menu, int jugadorSeleccionado){
    int x = jugador.getPosition().x/32;
    int y = jugador.getPosition().y/32;
    

    for(int i=0; i<enemigo.size() && state.GetEstado()==2; i++){
        enemigo[i].update();
    }
    
    for(int n = 0; n < maxAros; n++){
        if(jugadorSeleccionado==0){
            if(!tAro.loadFromFile("resources/aroazul.png")){
        exit(0);
        }
            aros[n]->setTextura(tAro);
        }else{
          if(!tAro.loadFromFile("resources/aroverde.png")){
        exit(0);
        }
          aros[n]->setTextura(tAro);
        }
        aros[n]->setPosEspecial(jugador.getPosition());
        aros[n]->update();
        
    }
    
     
    if(state.GetEstado() == 4 && boss->getVivo()){
        boss->update();
        boss->movimiento(jugador.getPosition(), dt, jugador.bounding());
        jugador.quitaVida(boss->getGolpe());
        interfaz.quitarVida(boss->getGolpe());
        for(int n = 0; n < maxAros; n++){
            Vector2f s = boss->getPosition() - aros[n]->getPosicion();
            float dist = sqrt((s.x * s.x) + (s.y * s.y));
            if(dist < 30){
                boss->quitarVida(jugador.getFuerza());
            }
        }
        if(boss->getVivo()==false){
            state.cambiarEstado(8);
        }
    }
    
    if(mapa.colisiona(y,x)){
        jugador.update1();
    }else{
        if(mapa.colisionaPinchos(y,x)){
            jugador.quitaVida(1);
            interfaz.quitarVida(1);
        }
        if(mapa.colisionaPortal(y,x) && mapa.getPortal()){
            mapa.cambiarPortal(false);
            state.cambiarEstado(3);
            jugador.setPosition(400,400);
        }
        if(mapa.cogerBolitas(x, y) && mapa.getBolita()==false){
            std::cout<<"bolitAAAA"<<std::endl;
            jugador.rellenarVida();
            interfaz.rellenarVida();
            mapa.bBolita(true);
        }
        if(mapa.velSuelo(x,y)){
            //std::cout<<"mas rapidooooo"<<std::endl;
            jugador.setVel(0.3);
        }
        else{
            jugador.setVel(0.2);
        }
        jugador.update();
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        jugador.moverArriba(dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        jugador.moverIzquierda(dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        jugador.moverAbajo(dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        jugador.moverDerecha(dt);
    }

    if(atak.getElapsedTime().asMilliseconds() > 250){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            aros[act]->activar(jugador.getPosition(), 'w');
            act++;
        }else
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            aros[act]->activar(jugador.getPosition(), 'a');
            act++;
        }else
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            aros[act]->activar(jugador.getPosition(), 's');
            act++;
        }else
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            aros[act]->activar(jugador.getPosition(), 'd');
            act++;
        }else
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
            aros[act]->activar(jugador.getPosition(), 'g');
            act++;
        }
        atak.restart();
    }
    for(int n = 0; n < maxAros; n++){
        aros[n]->mover(dt);
        if(aros[n]->getTime() > 2000 && aros[n]->getEstado()){
            aros[n]->desactivar();
        }
    }
    
    /*COLISIOOOOOOOOOON*/
    /*COLISION ENEMIGO CON JUGADOR*/
       for(int i=0;i<enemigo.size();i++){
            Vector2f source = jugador.getPosition() - enemigo[i].getPosition();
            float distancia = sqrt((source.x * source.x) + (source.y * source.y));
            if(distancia<20){
                if(enemigo[i].getclock()){
                jugador.quitaVida(enemigo[i].getFuerza());
                interfaz.quitarVida(enemigo[i].getFuerza());
                }
            }
        }
    
    /*COLISION ARO CON ENEMIGO*/
    for(int i=0;i<enemigo.size();i++){
        for(int j=0;j<juego.getNumAros();j++){
            Vector2f source = enemigo[i].getPosition() - aros[j]->getPosicion();
            float distancia = sqrt((source.x * source.x) + (source.y * source.y));
            if(distancia<20){
                //juego.restarvidaenemigo(i);
                enemigo[i].restarvida(jugador.getFuerza());
                //cout<<enemigo[i].getvida()<<endl;
            }
        }
    }
    /*COLISIOOOOOOOOOON*/
    //juego.compararMuerteMaligna();
    
    for(int i=0;i<enemigo.size();i++){
        //cout << "VIDA " << i <<": " << enemigo[i].getvida() << std::endl;
        if(enemigo[i].getvida()<=0){
            std::cout << "MUERTEEEE" << std::endl;
            //malignos.erase(malignos.begin()+(i-1));
            std::swap(enemigo[i], enemigo[enemigo.size()-1]);
            enemigo.pop_back();   
        }
    }
    
    
    if(enemigo.size()==0 && oleada<=5){
        int ex;
        jugador.setExperiencia();
        interfaz.rellenarExperiencia();
        interfaz.setOleada();
        cout<<"LA EXPERIENCIA ES:"<<jugador.getExperiencia()<<endl;
        oleada +=1;
        cout<<"OLEADAAAAA"<<oleada<<endl;
        Oleadas(window,juego,oleada,enemigo,interfaz,boss,jugador,state,menu);
        mapa.portal();
        mapa.cambiarPortal(true);
        mapa.bBolita(false);
    }
    
    
    
    
    
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M) && tiempo==100){
        mapa.portal();
        mapa.cambiarPortal(true);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
        mapa.cambiarPortal(false);
        jugador.setPosition(500,500);
        state.cambiarEstado(2);
        mapa.pruebas();
        //tiempo=100;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
        //aparece el boss
        state.cambiarEstado(4);
        boss->setPosition(jugador.getPosition());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        jugador.rellenarVida();
        interfaz.rellenarVida();
    }
    

    for(int i=0; i<enemigo.size() && state.GetEstado()!=3; i++){
        enemigo[i].mover(jugador.getPosition(),dt,i,enemigo);
    }
    for(int i=0; i<enemigo.size() && state.GetEstado()!=3; i++){
        int f=enemigo[i].getFuerza();
        if(enemigo[i].bounding().intersects(jugador.bounding())){
            jugador.quitaVida(f);
            //std::cout<<jugador.getVida();
        }
    }
    
    
    if(state.GetEstado()==3){
        tiempo--;
        if(tiempo==0 || mapa.salirSubMapa()){
            if(mapa.salirSubMapa()){
                jugador.rellenarVida();
                interfaz.rellenarVida();
                std::cout<<"rellenandoooo"<<std::endl;
            }
            jugador.setPosition(500,500);
            state.cambiarEstado(2);
            mapa.pruebas();
            tiempo=100;
        }
        if(mapa.colisionaPruebas(y,x)){
            //std::cout<<"Colisiona pruebas"<<std::endl;
        }
    }
    if(interfaz.getVida()==0){ //muere el jugador    
        state.cambiarEstado(5);
    }
}

void inputSiempre(sf::RenderWindow &window,state &state){
    sf::Event evento;
    while(window.pollEvent(evento)){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            if(state.GetEstado()!=5 && state.GetEstado()!=8){
                state.setEstadoAnterior(state.GetEstado());
                state.cambiarEstado(7);
            }
        }
        if(evento.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
            window.close();
        }
    }
}

void render(sf::RenderWindow &window, float pT, player jugador, std::vector<enemigos> enemigo, mapGame mapa, sf::View vista, state &state, Interfaz &interfaz, aro** aros, int maxAros, boss* boss, int &tiempo){
    window.clear();
    
    mapa.setActiveLayer(0);
    mapa.draw(window);
    mapa.setActiveLayer(1);
    mapa.draw(window);
    
    if(state.GetEstado()==2 || state.GetEstado()==4){
        mapa.drawPinchos(window);
        for(int n = 0; n < maxAros; n++){
            aros[n]->draw(window,pT);
        }
        if(mapa.getPortal()){
            mapa.drawPortal(window);
        }
        if(!mapa.getBolita()){
            mapa.drawBolita(window);
        }
        if(state.GetEstado()==2){
            for(int i=0; i<enemigo.size(); i++){
                enemigo[i].draw(window, pT);
            }
        }else if(state.GetEstado()==4 && boss->getVivo()){
            boss->draw(window, pT);
            boss->drawAtaque(window, pT);
            
        }
    }else if(state.GetEstado()==3){
        mapa.drawPruebas(window);
    }
    
    jugador.draw(window, pT);
    
    vista.setCenter(jugador.getPosition());
    window.setView(vista);
    if(state.GetEstado()==3){
        interfaz.drawReloj(window, vista, tiempo);
    }
    interfaz.draw(window, vista);
    window.display();
}

void updateMenu (sf::RenderWindow &window,Menu &menu,int &jugadorSeleccionado,int width,int height,state &state,juego &juego, player &jugador){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        //juego.setPersonaje(0);  
        jugador.setPersonaje(0);
        state.cambiarEstado(2);
    }
    
    sf::Event event;
    while (window.pollEvent(event)){
        switch (event.type){
        
            case sf::Event::KeyReleased:
                switch (event.key.code){

                    case sf::Keyboard::Up:
                        menu.MoveUp();
                          menu.playSonidoMenu();
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                          menu.playSonidoMenu();
                        break;
                
                    case sf::Keyboard::Left:
                        menu.MoveLeft();
                         menu.playSonidoMenu();
                        //if(menu.GetSelectedMenuCharacter()==1){}
                        break;
                
                    case sf::Keyboard::Right:
                        menu.MoveRight();   
                         menu.playSonidoMenu();
                        //if(menu.GetSelectedMenuCharacter()==1){
                        jugadorSeleccionado=menu.GetPersonaje(); //recojo el jugador seleccionado
                        //jugador=player(width, height,jugadorSeleccionado); //le doy a jugador el jugador seleccionado
                        //}
                        break;
                    
                    case sf::Keyboard::Return:
                        int menu_item=menu.GetPressedItem();
                        int selected_menu=menu.GetSelectedMenu();
                         menu.playSonidoEnter();
                         if(jugadorSeleccionado==0 && selected_menu==4 && menu.getVolver()==false){
                                     std::cout<<"-------------------"<<std::endl;
                                        //jugador=player(width, height,jugadorSeleccionado); //le doy a jugador el jugador seleccionado
                                        //juego.setPersonaje(jugadorSeleccionado);
                                        jugador.setPersonaje(jugadorSeleccionado);
                                        menu.playMusica();
                                        state.cambiarEstado(2); //CAMBIO ESTADO A MODO JUGAR
                                        //menu.SetSelectedItem(0); //inicializo a 0 el item del menu seleccionado
                                        // menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                        window.clear();
                                        window.display();
                             }
                             else if(jugadorSeleccionado==1 && selected_menu==4 && menu.getVolver()==false){
                                     std::cout<<"-------------------"<<std::endl;
                                        //jugador=player(width, height,jugadorSeleccionado); //le doy a jugador el jugador seleccionado
                                        //juego.setPersonaje(jugadorSeleccionado);
                                        jugador.setPersonaje(jugadorSeleccionado);
                                        menu.playMusica();
                                        state.cambiarEstado(2); //CAMBIO ESTADO A MODO JUGAR
                                        //menu.SetSelectedItem(0); //inicializo a 0 el item del menu seleccionado
                                        // menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                        window.clear();
                                        window.display();
                             }

                        if(selected_menu==1) //MAIN MENU (1)
                        {
                            switch(menu_item){
                                case 0:
                                    menu.SetSelectedMenu(2); //Al presionar voy al PLAY MENU
                                    menu.SetSelectedItem(0); //inicializo a 0 el item del menu seleccionado
                                    menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                    break;
                                case 1:
                                    menu.SetSelectedMenu(3); //Al presionar voy al INSTRUCTIONS MENU
                                    menu.SetSelectedItem(1); //inicializo a 0 el item del menu seleccionado
                                    menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                    break;

                                 case 2:
                                    menu.SetSelectedMenu(5); //Al presionar voy al CREDITS MENU
                                    menu.SetSelectedItem(1); //inicializo a 0 el item del menu seleccionado
                                    menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                    break;

                                case 3:
                                    window.close(); //presiono salir y el juego se sale
                                    break;
                                }
                        }
                        else if(selected_menu==3) //INSTRUCTIONS MENU
                        {
                            switch(menu_item){
                                case 1:
                                    menu.SetSelectedMenu(1); //Al presionar voy al MAIN MENU
                                    menu.SetSelectedItem(0); //inicializo a 0 el item del menu seleccionado
                                    menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                    break;
                                }
                        } 
                        else if(selected_menu==2) //PLAYERS MENU
                        {
                            switch(menu_item){
                                case 0:
                                    menu.SetSelectedMenu(4); //Al presionar voy al CHARACTERS MENU
                                    menu.SetSelectedItem(0); //inicializo a 0 el item del menu seleccionado
                                    menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                    break;

                                 case 1:
                                    menu.SetSelectedMenu(1); //Al presionar voy al MAIN MENU
                                    menu.SetSelectedItem(0); //inicializo a 0 el item del menu seleccionado
                                    menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                    break;    
                            }
                        }
                        else if(selected_menu==4) //CHARACTERS MENU
                        {
                            switch(menu_item){
                                case 0:
                                    if(menu.GetSelectedMenuCharacter()==0){
                                        menu.SetSelectedMenu(2); //Volver
                                        menu.SetSelectedItem(0); //inicializo a 0 el item del menu seleccionado
                                        menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                    }
                                    break;

                                case 1:
                                    if(menu.GetSelectedMenuCharacter()==0){
       
                                        //jugador=player(width, height,jugadorSeleccionado); //le doy a jugador el jugador seleccionado
                                     jugador.setPersonaje(jugadorSeleccionado);
                                         menu.playMusica();
                                        state.cambiarEstado(2); //CAMBIO ESTADO A MODO JUGAR
                                        //menu.SetSelectedItem(0); //inicializo a 0 el item del menu seleccionado
                                        // menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                        window.clear();
                                        window.display();
                                    }
                                    break;
                            }
                        }
                        else if(selected_menu==5) //CREDIT MENU
                        {
                            switch(menu_item){
                                 case 1:
                                    menu.SetSelectedMenu(1); //Al presionar selecciono al primer personaje
                                    menu.SetSelectedItem(0); //inicializo a 0 el item del menu seleccionado
                                    menu.DrawNewMenu(window); //dibujo el nuevo menu seleccionado
                                    break;
                            }
                        }
                        break;
                }
                break;
                
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}

void renderMenu(sf::RenderWindow &window, Menu menu){
    window.clear();
    menu.draw(window);
    window.display();
}
void GameOver(sf::RenderWindow &window, state &state, sf::View &vista,Menu &menu){
    sf::Font font;
     sf::Font font2;
    sf::Text gameover;
    sf::Text gameover2;
   
    menu.pauseMusica();
    menu.pauseBoss();
 
    
     if (!font.loadFromFile("resources/arial.ttf"))
	{
		// handle error
	}
    
     if (!font2.loadFromFile("resources/arial.ttf"))
	{
		// handle error
	}
   
    gameover.setFont(font);
    gameover2.setFont(font2);
    gameover.setColor(sf::Color::White);
    gameover2.setColor(sf::Color::White);
    gameover.setString("GAME OVER");
    gameover2.setString("Pulsa c para continuar");
    gameover.setCharacterSize(100);
    gameover2.setCharacterSize(25);
    gameover.setOrigin(gameover.getGlobalBounds().width/2,gameover.getGlobalBounds().height/2);
    gameover2.setOrigin(gameover2.getGlobalBounds().width/2,gameover2.getGlobalBounds().height/2);
    gameover.setPosition(vista.getCenter().x/2,vista.getCenter().y/2-100); //78.5 34
    gameover2.setPosition(vista.getCenter().x/2,vista.getCenter().y/2+10); //78.5 34
                       
    sf::Texture imagenFondo;
    imagenFondo.loadFromFile("resources/background2.jpg"); //controlar error?
    sf::Sprite fondo(imagenFondo);
    fondo.setScale(0.8,0.8);
    fondo.setOrigin(fondo.getLocalBounds().width/2,fondo.getLocalBounds().height/2);
    fondo.setPosition(vista.getCenter().x/2,vista.getCenter().y/2);
       
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
       state.cambiarEstado(6);
    }
    vista.setCenter(vista.getCenter().x/2,vista.getCenter().y/2);
    window.setView(vista);
    window.clear();
    window.draw(fondo);
    window.draw(gameover);
    window.draw(gameover2);
    window.display();
}

void Oleadas(sf::RenderWindow &window, juego &juego, int &oleada,std::vector<enemigos> &enemigo, Interfaz &interfaz, boss* boss, player &jugador, state &state,Menu &menu){
    if(oleada==2){
       int n=1;
       juego.crearenemigos(n,10,10);
       enemigo=juego.getenemigos();
       interfaz.setEnemigos(n);
       
    }
    
    if(oleada==3){
        int n=2;
       juego.crearenemigos(n,10,10); 
       enemigo=juego.getenemigos();
       interfaz.setEnemigos(n);
    }
    
    if(oleada==4){
        int n=3;
       juego.crearenemigos(n,10,10);
       enemigo=juego.getenemigos();
       interfaz.setEnemigos(n);
    }
    
    if(oleada==5){
        //crearboss
        menu.setWhatMusic(1);
        menu.pauseMusica();
        menu.playBoss();
        menu.playRisa();
        state.cambiarEstado(4);
        boss->setPosition(jugador.getPosition());
        boss->setVivo(true);
        boss->restartClocks();
        
    }
}


void Pausa(sf::RenderWindow &window, state &state, sf::View &vista,int &select,Menu &menu,boss* &boss){
    
    int whatMusic=menu.getWhatMusic();
    int whatEstado= state.GetEstadoAnterior();
    if(whatMusic==0){
      menu.pauseMusica();
    }
    else{
        menu.pauseBoss();
        menu.pauseRisa();
    }
    sf::Font font;
     sf::Font font2;
    sf::Text gameover;
    sf::Text gameover2;
    sf::Texture imagenLogo;

    sf::Color color(30, 212, 234); 
    
     if (!font.loadFromFile("resources/arial.ttf"))
	{
		// handle error
	}
    
     if (!font2.loadFromFile("resources/arial.ttf"))
	{
		// handle error
	}
    
          
          imagenLogo.loadFromFile("resources/alpha.png"); //controlar error?
          sf::Sprite logo(imagenLogo);
          logo.setScale(0.5,0.5);
          
         
    gameover.setFont(font);
     gameover2.setFont(font2);
     if(select==0){
    gameover.setColor(color);
      gameover2.setColor(sf::Color::White);
     }
     else{
       gameover2.setColor(color);
      gameover.setColor(sf::Color::White);
     }
   
    gameover.setString("Reanudar");
        gameover2.setString("Salir");
    gameover.setCharacterSize(40);
        gameover2.setCharacterSize(40);
    gameover.setOrigin(gameover.getGlobalBounds().width/2,gameover.getGlobalBounds().height/2);
     gameover2.setOrigin(gameover2.getGlobalBounds().width/2,gameover2.getGlobalBounds().height/2);
     logo.setOrigin(logo.getLocalBounds().width/2,logo.getLocalBounds().height/2);
    gameover.setPosition(vista.getCenter().x/2,vista.getCenter().y/2-100); //78.5 34
          gameover2.setPosition(vista.getCenter().x/2,vista.getCenter().y/2+10); //78.5 34
           logo.setPosition(vista.getCenter().x/2,vista.getCenter().y-325);
          
                 
          sf::Texture imagenFondo;
          imagenFondo.loadFromFile("resources/background2.jpg"); //controlar error?
          sf::Sprite fondo(imagenFondo);
          fondo.setScale(0.8,0.8);
          fondo.setOrigin(fondo.getLocalBounds().width/2,fondo.getLocalBounds().height/2);
          fondo.setPosition(vista.getCenter().x/2,vista.getCenter().y/2);
          
         
       
 
    
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
         if(select==0){
         /*gameover.setColor(sf::Color::White);
         gameover2.setColor(color);
         select=1;*/
         }
         else{
           gameover.setColor(color);
           gameover2.setColor(sf::Color::White);
           select=0;
           menu.playSonidoMenu();
         }
          
    }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
           if(select==1){
         /*gameover2.setColor(sf::Color::White);
         gameover.setColor(color);
         select=0;*/
               
         }
         else{
           gameover2.setColor(color);
           gameover.setColor(sf::Color::White);
           select=1;
           menu.playSonidoMenu();
         }
           
      }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                exit(0);
            }
          
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
           if(select==0){
               if(whatMusic==0){
                menu.playMusica();
                if(whatEstado==2){
                     state.cambiarEstado(2);
                    }
                else if(whatEstado==3){
                   state.cambiarEstado(3);
                 }
               }else{
                   menu.playBoss();
                   if(boss->getVivo()==true){
                    menu.playRisa();
                   }
                   state.cambiarEstado(4);
               }
               
           }
           else{
               state.cambiarEstado(6);
           }
            menu.playSonidoEnter();
       }
    vista.setCenter(vista.getCenter().x/2,vista.getCenter().y/2);
    window.setView(vista);
    window.clear();
    window.draw(fondo);
    window.draw(gameover);
    window.draw(gameover2);
    window.draw(logo);
    window.display();
}

void Ganar(sf::RenderWindow &window, state &state, sf::View &vista,int &select,Menu &menu,boss* &boss){
    sf::Font font;
    sf::Font font2;
    sf::Text gameover;
    sf::Text gameover2;
   
    menu.pauseMusica();
    menu.pauseBoss();
    menu.playVictoria();
 
    
    if(!font.loadFromFile("resources/arial.ttf")){
		// handle error
    }    
    if(!font2.loadFromFile("resources/arial.ttf")){
		// handle error
    }
   
    gameover.setFont(font);
    gameover2.setFont(font2);
    gameover.setColor(sf::Color::White);
    gameover2.setColor(sf::Color::White);
    gameover.setString("HAS GANADO");
    gameover2.setString("Pulsa c para continuar");
    gameover.setCharacterSize(100);
    gameover2.setCharacterSize(25);
    gameover.setOrigin(gameover.getGlobalBounds().width/2,gameover.getGlobalBounds().height/2);
    gameover2.setOrigin(gameover2.getGlobalBounds().width/2,gameover2.getGlobalBounds().height/2);
    gameover.setPosition(vista.getCenter().x/2,vista.getCenter().y/2-100); //78.5 34
    gameover2.setPosition(vista.getCenter().x/2,vista.getCenter().y/2+10); //78.5 34
          
                 
    sf::Texture imagenFondo;
    imagenFondo.loadFromFile("resources/background2.jpg"); //controlar error?
    sf::Sprite fondo(imagenFondo);
    fondo.setScale(0.8,0.8);
    fondo.setOrigin(fondo.getLocalBounds().width/2,fondo.getLocalBounds().height/2);
    fondo.setPosition(vista.getCenter().x/2,vista.getCenter().y/2);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
       state.cambiarEstado(6);
    }
    vista.setCenter(vista.getCenter().x/2,vista.getCenter().y/2);
    window.setView(vista);
    window.clear();
    window.draw(fondo);
    window.draw(gameover);
    window.draw(gameover2);
    window.display();
}