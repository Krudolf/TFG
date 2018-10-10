#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#define ITEMS_MAIN_MENU 4 //JUGAR, INSTRUCCIONES,CREDITOS, SALIR
#define ITEMS_CREDIT_MENU 4 //JUGAR, INSTRUCCIONES,CREDITOS, SALIR
#define ITEMS_PLAYERS_MENU 2 //1 JUGADOR, aun no 2 JUGADORES, VOLVER
#define ITEMS_CHARACTERS_MENU 2 //JUGADOR 1, JUGADOR 2, JUGADOR 3
#define ITEMS_CHARACTERS_MENU_START 2 //VOLVER, EMPEZAR
#define ITEMS_INSTRUCTION_MENU 2 //INSTRUCCIONES, VOLVER

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
        void DrawNewMenu(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
        void MoveLeft();
        void MoveRight();
	int GetPressedItem() { return selected_item_menu; }
        int GetSelectedMenu() { return selected_menu; }
        int GetSelectedItemCharacter(){ return selected_item_menu_character; }
        int GetSelectedMenuCharacter(){ return characters_menu_imaginative; }
        int GetPersonaje(){ return personaje; }
        void SetSelectedMenu(int m) { selected_menu=m; }
        void SetSelectedItem(int i){ selected_item_menu=i; }
        void playSonidoMenu(){sonidoMenu.play();}
        void playSonidoEnter(){sonidoEnter.play();}
        void playMusica(){musica.play();}
        void pauseMusica(){musica.pause();}
        void playRisa(){risa.play();}
        void playGameOver(){gameover.play();}
        void playBoss(){boss.play();}
        void pauseBoss(){boss.pause(); }
        void pauseRisa(){risa.pause(); }
        bool getVolver(){ return noEstoyEnVolver;}
        int getWhatMusic(){ return whatMusicPlay;}
        void setWhatMusic(int w){ whatMusicPlay=w;}
        void playVictoria(){ if(victoriaUnaVez==0){victoria.play();} victoriaUnaVez=1;}
        
        

private:
        
        int victoriaUnaVez;
	int selected_item_menu;
        int whatMusicPlay;
        int noEstoyEnVolver;
        int selected_menu;
        int characters_menu_imaginative; //para controlar en el menu character si estoy arriba o abajo
        int selected_item_menu_character;
        bool sonido;
        int personaje;
        sf::SoundBuffer buffer1;
        sf::SoundBuffer buffer2;
        sf::SoundBuffer buffer3;
        sf::SoundBuffer buffer4;
        sf::SoundBuffer buffer5;
        sf::SoundBuffer buffer6;
        sf::SoundBuffer buffer7;
        sf::Sound victoria;
        sf::Sound musica;
        sf::Sound sonidoMenu;
        sf::Sound sonidoEnter;
        sf::Sound risa;
        sf::Sound boss;
        sf::Sound gameover; 
	sf::Font font;
	sf::Text main_menu[ITEMS_MAIN_MENU]; 
        sf::Text players_menu[ITEMS_PLAYERS_MENU];
        sf::Text credit_menu[ITEMS_CREDIT_MENU];
        sf::Sprite characters_menu[ITEMS_CHARACTERS_MENU];
        sf::Texture characters_menu_texture[ITEMS_CHARACTERS_MENU];
        sf::Text characters_menu_start[ITEMS_CHARACTERS_MENU_START];
        sf::Text instruction_menu[ITEMS_INSTRUCTION_MENU];
        
        

};