/*************************************
Written By Benyamin Delshad
**************************************/
/*
Compile & Run:
g++ -std=c++11 -c Descriptions.cpp header.h SpaceShooter.cpp 
g++ -std=c++11 -o program1 SpaceShooter.o Descriptions.o -lsfml-graphics -lsfml-window -lsfml-system
./program1
*/
#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
#include "header.h"

	
void game_run() {
	Graphics game;
	game.Run();
}
/*
void play_music() {
	sf::Music music;
	if (!music.openFromFile("Air_0.ogg"))
    	cerr << "music file could not found!" << endl;; // error
	music.play();
}
*/
int main() {
	srand(time(0));
	game_run();
	//thread first(game_run);
	//thread second(play_music);
	//first.join();
	//second.join();
	//play_music();
	return 0;
}	
