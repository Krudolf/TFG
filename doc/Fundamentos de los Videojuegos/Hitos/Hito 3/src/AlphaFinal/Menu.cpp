#include "Menu.h"
using namespace std;
#include <iostream>
#include <SFML/Audio.hpp>




Menu::Menu(float width, float height)
{
    victoriaUnaVez=0;
    noEstoyEnVolver=false;
	if (!font.loadFromFile("resources/arial.ttf"))
	{
		// handle error
	}
            
      sf::Color color(30, 212, 234); 
      
//std::cout<<selected_item_menu<<std::endl;
      personaje=0;
           if(!buffer1.loadFromFile("resources/boton.wav")){
          std::cout<<"--------------------No hay sonidillos que valgan"<<std::endl;
      }
      
       if(!buffer2.loadFromFile("resources/enter.wav")){
          std::cout<<"--------------------No hay sonidillos que valgan"<<std::endl;
      }
     
         if(!buffer3.loadFromFile("resources/cancion.ogg")){
          std::cout<<"--------------------No hay sonidillos que valgan"<<std::endl;
      }
         if(!buffer4.loadFromFile("resources/risa.wav")){
          std::cout<<"--------------------No hay sonidillos que valgan"<<std::endl;
      }
         if(!buffer5.loadFromFile("resources/gameover.wav")){
          std::cout<<"--------------------No hay sonidillos que valgan"<<std::endl;
      }
         if(!buffer6.loadFromFile("resources/boss.ogg")){
          std::cout<<"--------------------No hay sonidillos que valgan"<<std::endl;
      }
        if(!buffer7.loadFromFile("resources/victoria.ogg")){
          std::cout<<"--------------------No hay sonidillos que valgan"<<std::endl;
      }
      sonidoMenu.setBuffer(buffer1);
      sonidoEnter.setBuffer(buffer2);
      musica.setBuffer(buffer3);
      risa.setBuffer(buffer4);
      gameover.setBuffer(buffer5);
      boss.setBuffer(buffer6);
      victoria.setBuffer(buffer7);
      whatMusicPlay=0;
      
	main_menu[0].setFont(font);
	main_menu[0].setColor(color);
	main_menu[0].setString("Jugar");
        main_menu[0].setOrigin(main_menu[0].getGlobalBounds().width/2,main_menu[0].getGlobalBounds().height);        
	main_menu[0].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MAIN_MENU + 3) * 1+130));

	main_menu[1].setFont(font);
	main_menu[1].setColor(sf::Color::White);
	main_menu[1].setString("Instrucciones");
        main_menu[1].setOrigin(main_menu[1].getGlobalBounds().width/2,main_menu[1].getGlobalBounds().height);        
	main_menu[1].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MAIN_MENU + 3) * 2+130));
        
        main_menu[2].setFont(font);
	main_menu[2].setColor(sf::Color::White);
	main_menu[2].setString("Creditos");
        main_menu[2].setOrigin(main_menu[2].getGlobalBounds().width/2,main_menu[2].getGlobalBounds().height);       
	main_menu[2].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MAIN_MENU + 3) * 3+130));

	main_menu[3].setFont(font);
	main_menu[3].setColor(sf::Color::White);
	main_menu[3].setString("Salir");
        main_menu[3].setOrigin(main_menu[3].getGlobalBounds().width/2,main_menu[3].getGlobalBounds().height);        
	main_menu[3].setPosition(sf::Vector2f(width / 2, height / (ITEMS_MAIN_MENU + 3) * 4+130));
        
        musica.setLoop(true);
        boss.setLoop(true);
        victoria.setLoop(true);
        
        
	selected_item_menu = 0;
        selected_menu=1;
        sonido=true;
}




Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
    
     //std::cout<<selected_item_menu<<std::endl;
    
          sf::Texture imagenLogo;
          imagenLogo.loadFromFile("resources/alpha.png"); //controlar error?
          sf::Sprite logo(imagenLogo);
          logo.setScale(0.5,0.5);
          logo.setOrigin(logo.getLocalBounds().width/2,logo.getLocalBounds().height/2);
          logo.setPosition(window.getSize().x/2,80);
          
          
          
          sf::Texture imagenFondo;
          imagenFondo.loadFromFile("resources/background2.jpg"); //controlar error?
          sf::Sprite fondo(imagenFondo);
          fondo.setScale(0.8,0.8);
          fondo.setOrigin(fondo.getLocalBounds().width/2,fondo.getOrigin().y);
          fondo.setPosition(window.getSize().x/2,-100);
         
         
          window.draw(fondo);
          window.draw(logo);
    
    if(selected_menu==1){ //dibujo el main menu
	for (int i = 0; i < ITEMS_MAIN_MENU; i++)
	{
		window.draw(main_menu[i]);
	}
    }
    else if(selected_menu==3){ //dibujo el menu instrucciones
        /* sf::Texture imagenFondo;
          imagenFondo.loadFromFile("tron.png"); //controlar error?
          sf::Sprite fondo(imagenFondo);
          fondo.setScale(0.75,0.75);
          
          window.draw(fondo);*/
          
          sf::Text controles;
          controles.setFont(font);
          controles.setColor(sf::Color::White);
          controles.setString("ESC para pausar el videojuego\n"
          "W para ir hacia arriba \n"
          "A para ir hacia la izquierda \n"
          "S para ir hacia abajo \n"
          "D para ir hacia la derecha \n"
          "Usa las flechas de direccion para disparar \n"
          "Numeros del 1 al 3 para seleccionar habilidades");
          controles.setCharacterSize(25);
          controles.setOrigin(controles.getGlobalBounds().width/2,controles.getGlobalBounds().height/2);
          controles.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
          
          window.draw(controles);
         
        for (int i = 0; i < ITEMS_INSTRUCTION_MENU; i++)
	{       
		window.draw(instruction_menu[i]);
	}
    }
         
    else if(selected_menu==2){ //dibujo el menu players
        /* sf::Texture imagenFondo;
          imagenFondo.loadFromFile("tron.png"); //controlar error?
          sf::Sprite fondo(imagenFondo);
          fondo.setScale(0.75,0.75);
          
          window.draw(fondo);*/
        
           sf::Text modo;
          modo.setFont(font);
          modo.setColor(sf::Color::White);
          modo.setString("MODO DE JUEGO");
          modo.setOrigin(modo.getGlobalBounds().width/2,modo.getGlobalBounds().height/2);
          modo.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_PLAYERS_MENU+1)*1));
          window.draw(modo);
         
         
        for (int i = 0; i < ITEMS_PLAYERS_MENU; i++)
	{       
		window.draw(players_menu[i]);
	}
    }
          
    else if(selected_menu==5){ //dibujo el menu credit
         sf::Texture imagenFondo;
          imagenFondo.loadFromFile("resources/creditos.png"); //controlar error?
          sf::Sprite fondo(imagenFondo);
          fondo.setScale(0.5,0.5);
          fondo.setOrigin(fondo.getLocalBounds().width/2,fondo.getLocalBounds().height/2);
          fondo.setPosition(window.getSize().x/2,window.getSize().y/2);
          
          window.draw(fondo);
        
          /* sf::Text modo;
          modo.setFont(font);
          modo.setColor(sf::Color::White);
          modo.setString("MODO DE JUEGO");
          modo.setPosition(sf::Vector2f(window.getSize().x / 2.5, window.getSize().y / (ITEMS_PLAYERS_MENU+1)*1));
          window.draw(modo);*/
         
         
        for (int i = 0; i < ITEMS_PLAYERS_MENU; i++)
	{       
		window.draw(credit_menu[i]);
	}
    }
          
    else if(selected_menu==4){ //dibujo el menu characters
        /* sf::Texture imagenFondo;
          imagenFondo.loadFromFile("tron.png"); //controlar error?
          sf::Sprite fondo(imagenFondo);
          fondo.setScale(0.75,0.75);
          
          window.draw(fondo);*/
        
           sf::Text modo;
          modo.setFont(font);
          modo.setColor(sf::Color::White);
          modo.setString("SELECCIONA UN PERSONAJE");
          modo.setOrigin(modo.getGlobalBounds().width/2,modo.getGlobalBounds().height);
          modo.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_PLAYERS_MENU+1)*0.9));
          window.draw(modo);
          
       
        for (int i = 0; i < ITEMS_CHARACTERS_MENU; i++)
	{       
                characters_menu[i].setTexture(characters_menu_texture[i]);
		window.draw(characters_menu[i]);
	}
         for (int j = 0; j < ITEMS_CHARACTERS_MENU_START; j++)
	{       
		window.draw(characters_menu_start[j]);
	}
    }
    
}

void Menu::DrawNewMenu(sf::RenderWindow &window)
{
    sf::Color color(30, 212, 234); 
    
    if(selected_menu==5){ //creo el credit 
      /*  instruction_menu[0].setFont(font);
        instruction_menu[0].setScale(1.15,1.15);
	instruction_menu[0].setColor(sf::Color::White);
	instruction_menu[0].setString("INSTRUCCIONES");
	instruction_menu[0].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_INSTRUCTION_MENU + 1) * 1));*/
   
       
	credit_menu[0].setFont(font);
	credit_menu[0].setColor(color);
	credit_menu[0].setString("Volver");
        credit_menu[0].setOrigin(credit_menu[0].getGlobalBounds().width/2,credit_menu[0].getGlobalBounds().height/2);
	credit_menu[0].setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y / (ITEMS_INSTRUCTION_MENU + 1) * 2.5));
    }
    
   if(selected_menu==3){ //creo el menu instrucciones
      /*  instruction_menu[0].setFont(font);
        instruction_menu[0].setScale(1.15,1.15);
	instruction_menu[0].setColor(sf::Color::White);
	instruction_menu[0].setString("INSTRUCCIONES");
	instruction_menu[0].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_INSTRUCTION_MENU + 1) * 1));*/
   
       
	instruction_menu[0].setFont(font);
	instruction_menu[0].setColor(color);
	instruction_menu[0].setString("Volver");
        instruction_menu[0].setOrigin(instruction_menu[0].getGlobalBounds().width/2,instruction_menu[0].getGlobalBounds().height/2);
	instruction_menu[0].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_INSTRUCTION_MENU + 1) * 2.5));
    }
    if(selected_menu==1){ //creo el main menu
        main_menu[0].setFont(font);
	main_menu[0].setColor(color);
	main_menu[0].setString("Jugar");
        main_menu[0].setOrigin(main_menu[0].getGlobalBounds().width/2,main_menu[0].getGlobalBounds().height);
        main_menu[0].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_MAIN_MENU + 3) * 1+130));
        
	main_menu[1].setFont(font);
	main_menu[1].setColor(sf::Color::White);
	main_menu[1].setString("Instrucciones");
        main_menu[1].setOrigin(main_menu[1].getGlobalBounds().width/2,main_menu[1].getGlobalBounds().height);
        main_menu[1].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_MAIN_MENU + 3) * 2+130));
        
        main_menu[2].setFont(font);
	main_menu[2].setColor(sf::Color::White);
	main_menu[2].setString("Creditos");
        main_menu[2].setOrigin(main_menu[2].getGlobalBounds().width/2,main_menu[2].getGlobalBounds().height);
        main_menu[2].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_MAIN_MENU + 3) * 3+130));

	main_menu[3].setFont(font);
	main_menu[3].setColor(sf::Color::White);
	main_menu[3].setString("Salir");
        main_menu[3].setOrigin(main_menu[3].getGlobalBounds().width/2,main_menu[3].getGlobalBounds().height);
        main_menu[3].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_MAIN_MENU + 3) * 4+130));
    }
    
      if(selected_menu==2){ //creo el players menu
        players_menu[0].setFont(font);
	players_menu[0].setColor(color);
	players_menu[0].setString("1 jugador");
        players_menu[0].setOrigin(players_menu[0].getGlobalBounds().width/2,players_menu[0].getGlobalBounds().height);
	players_menu[0].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_PLAYERS_MENU + 1) * 1.5));

	players_menu[1].setFont(font);
	players_menu[1].setColor(sf::Color::White);
	players_menu[1].setString("Volver");
        players_menu[1].setOrigin(players_menu[1].getGlobalBounds().width/2,players_menu[1].getGlobalBounds().height);
	players_menu[1].setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / (ITEMS_PLAYERS_MENU + 1) * 2));
    }
    
      if(selected_menu==4){ //creo el characters menu
          
        selected_item_menu_character=0;
        characters_menu_start[0].setFont(font);
	characters_menu_start[0].setColor(sf::Color::White);
	characters_menu_start[0].setString("Volver");
        characters_menu_start[0].setOrigin(characters_menu_start[0].getGlobalBounds().width/2,characters_menu_start[0].getGlobalBounds().height/2);
	characters_menu_start[0].setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / (ITEMS_PLAYERS_MENU + 1) * 2.5));

	characters_menu_start[1].setFont(font);
	characters_menu_start[1].setColor(sf::Color::White);
	characters_menu_start[1].setString("Empezar");
        characters_menu_start[1].setOrigin(characters_menu_start[1].getGlobalBounds().width/2,characters_menu_start[1].getGlobalBounds().height/2);        
	characters_menu_start[1].setPosition(sf::Vector2f(window.getSize().x / 3*2, window.getSize().y / (ITEMS_PLAYERS_MENU + 1) * 2.5));
        
        
      
        characters_menu_texture[0].loadFromFile("resources/personaje1.png");
        characters_menu[0].setScale(0.9,0.9);
        //characters_menu[0].setOrigin(characters_menu[0].getLocalBounds().width/2,characters_menu[0].getLocalBounds().height/2);
        characters_menu[0].setPosition(window.getSize().x/4*1,window.getSize().y/2.5);
     
        characters_menu_texture[1].loadFromFile("resources/personaje2.png");
        characters_menu[1].setScale(0.8,0.8);
       // characters_menu[1].setOrigin(characters_menu[1].getLocalBounds().width/2,characters_menu[1].getLocalBounds().height/2);
        characters_menu[1].setPosition(window.getSize().x/4*2.3,window.getSize().y/2.5);
       
        /*characters_menu_texture[2].loadFromFile("resources/personaje3.png");
        characters_menu[2].setScale(0.8,0.8);
        //characters_menu[2].setOrigin(characters_menu[2].getLocalBounds().width/2,characters_menu[2].getLocalBounds().height/2);   
        characters_menu[2].setPosition(window.getSize().x/5*3,window.getSize().y/2.5);*/
        
        characters_menu_imaginative=1;
 
        
      
    }
    
    
}
////////////////////////////////////MOVERSER POR EL MENU SEGUN EL QUE ESTE SELECCIONADO
void Menu::MoveUp()
{

       sf::Color color(30, 212, 234); 

        if (selected_item_menu - 1 == -1 && selected_menu==1)
	{
		main_menu[selected_item_menu].setColor(sf::Color::White);
		selected_item_menu=ITEMS_MAIN_MENU-1;
		main_menu[selected_item_menu].setColor(color);
               
	}
     
       else if (selected_item_menu - 1 >= 0 && selected_menu==1)
	{
		main_menu[selected_item_menu].setColor(sf::Color::White);
		selected_item_menu--;
		main_menu[selected_item_menu].setColor(color);
               
	}
       
       
        if (selected_item_menu - 1 == -1 && selected_menu==2)
	{
		players_menu[0].setColor(sf::Color::White);
		players_menu[1].setColor(color);
                selected_item_menu=1;
               
               
	}
     
       else if (selected_item_menu - 1 >= 0 && selected_menu==2)
	{
		players_menu[1].setColor(sf::Color::White);
		players_menu[0].setColor(color);
                selected_item_menu=0;
               
	}
       
        if(characters_menu_imaginative<1 && selected_menu==4){
         characters_menu_start[selected_item_menu].setColor(sf::Color::White);
              /*if(selected_item_menu==0){
            characters_menu_texture[0].loadFromFile("personaje1.png");
            characters_menu[0].setScale(0.9,0.9);
            characters_menu[0].setPosition(100,250);
         }
         else if(selected_item_menu==1){
            characters_menu_texture[1].loadFromFile("personaje2.png");
            characters_menu[1].setScale(0.9,0.9);
            characters_menu[1].setPosition(400,250);
         }
         else if(selected_item_menu==2){
            characters_menu_texture[2].loadFromFile("personaje3.png");
            characters_menu[2].setScale(0.9,0.9);
            characters_menu[2].setPosition(700,250);
         }*/
          characters_menu_imaginative++;
           noEstoyEnVolver=false;
          selected_item_menu=selected_item_menu_character;
         
    }
       
      
       /* if (selected_item_menu - 1 >= 0 && selected_menu==3)
	{
		instruction_menu[selected_item_menu].setColor(sf::Color::White);
		selected_item_menu--;
		instruction_menu[selected_item_menu].setColor(sf::Color::Red);
	}*/
        
        
}

void Menu::MoveDown()
{//std::cout<<selected_item_menu<<endl;
    sf::Color color(30, 212, 234); 
    if(selected_menu==1){
	if (selected_item_menu + 1 < ITEMS_MAIN_MENU)
	{
		main_menu[selected_item_menu].setColor(sf::Color::White);
		selected_item_menu++;
		main_menu[selected_item_menu].setColor(color);
	}
        else if(selected_item_menu + 1 == ITEMS_MAIN_MENU){
                main_menu[selected_item_menu].setColor(sf::Color::White);
		selected_item_menu=0;
		main_menu[selected_item_menu].setColor(color);
        }
    }
    
       if(selected_menu==2){
	if (selected_item_menu + 1 < ITEMS_PLAYERS_MENU)
	{
		players_menu[0].setColor(sf::Color::White);
                players_menu[1].setColor(color);
		selected_item_menu=1;
		
	}
        else if(selected_item_menu + 1 == ITEMS_PLAYERS_MENU){
                players_menu[1].setColor(sf::Color::White);
		players_menu[0].setColor(color);
                selected_item_menu=0;
        }
    }
    
     if(characters_menu_imaginative-1==0 && selected_menu==4){
         characters_menu_start[0].setColor(color);
         characters_menu_imaginative--;
         selected_item_menu_character=selected_item_menu;
         selected_item_menu=0;
         
         /*if(selected_item_menu==0){
            characters_menu_texture[0].loadFromFile("personaje1.png");
            characters_menu[0].setScale(0.8,0.8);
            characters_menu[0].setPosition(100,250);
         }
         else if(selected_item_menu==1){
            characters_menu_texture[1].loadFromFile("personaje2.png");
            characters_menu[1].setScale(0.8,0.8);
            characters_menu[1].setPosition(400,250);
         }
         else if(selected_item_menu==2){
            characters_menu_texture[2].loadFromFile("personaje3.png");
            characters_menu[2].setScale(0.8,0.8);
            characters_menu[2].setPosition(700,250);
         }*/
          
           noEstoyEnVolver=true;
         
    }
    
    
  
     /*if(selected_menu==3){
	if (selected_item_menu + 1 < ITEMS_INSTRUCTION_MENU)
	{
		instruction_menu[selected_item_menu].setColor(sf::Color::White);
		selected_item_menu++;
		instruction_menu[selected_item_menu].setColor(sf::Color::Red);
	}
    }*/
}

void Menu::MoveLeft()
{
       sf::Color color(30, 212, 234); 
    
       if (selected_item_menu - 1 == -1 && selected_menu==4 && characters_menu_imaginative==1)
	{
		characters_menu[selected_item_menu].setScale(0.8,0.8);
		selected_item_menu=ITEMS_CHARACTERS_MENU-1;
		characters_menu[selected_item_menu].setScale(0.9,0.9);
                personaje=selected_item_menu;
               
	}
     
       else if (selected_item_menu - 1 >= 0 && selected_menu==4 && characters_menu_imaginative==1)
	{
		characters_menu[selected_item_menu].setScale(0.8,0.8);
		selected_item_menu--;
		characters_menu[selected_item_menu].setScale(0.9,0.9);
                personaje=selected_item_menu;
               
	}
       
        if (selected_item_menu - 1 == -1 && selected_menu==4 && characters_menu_imaginative==0)
	{
            
               characters_menu_start[selected_item_menu].setColor(sf::Color::White);
               selected_item_menu=1;
                characters_menu_start[selected_item_menu].setColor(color);
                
	}
     
       else if (selected_item_menu - 1 >= 0 && selected_menu==4 && characters_menu_imaginative==0)
	{
            characters_menu_start[selected_item_menu].setColor(sf::Color::White);
              selected_item_menu--;
                characters_menu_start[selected_item_menu].setColor(color);
                
		
               
	}
}


void Menu::MoveRight()
{
       sf::Color color(30, 212, 234); 
        if(selected_menu==4 && characters_menu_imaginative==1){
	if (selected_item_menu + 1 < ITEMS_CHARACTERS_MENU)
	{
                characters_menu[selected_item_menu].setScale(0.8,0.8);
		selected_item_menu++;
		characters_menu[selected_item_menu].setScale(0.9,0.9);
	}
        else if(selected_item_menu + 1 == ITEMS_CHARACTERS_MENU){
                characters_menu[selected_item_menu].setScale(0.8,0.8);
		selected_item_menu=0;
		characters_menu[selected_item_menu].setScale(0.9,0.9);
        }
        personaje=selected_item_menu;
    }
        
     if(selected_menu==4 && characters_menu_imaginative==0){
	if (selected_item_menu + 1 < ITEMS_CHARACTERS_MENU_START)
	{
                characters_menu_start[selected_item_menu].setColor(sf::Color::White);
               
                selected_item_menu++;
                characters_menu_start[selected_item_menu].setColor(color);
	}
        else if(selected_item_menu + 1 == ITEMS_CHARACTERS_MENU_START){
                characters_menu_start[selected_item_menu].setColor(sf::Color::White);
               
                selected_item_menu=0;
                characters_menu_start[selected_item_menu].setColor(color);
                
        }
        
    }
    
}