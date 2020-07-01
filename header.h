/*************************************
Written By Benyamin Delshad
**************************************/
#ifndef HEADER_H
#define HEADER_H

#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

class Spaceship {
public:
	Spaceship(int);
	~Spaceship();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getX() const;
	void setX(int);
	int getY() const;
	void setY(int);
	int getVx() const;
	void setVx(int);
	int getVy() const;
	void setVy(int);
	sf::Sprite & getSpr();
	sf::Texture & getTex();
	void updateSpr();
	void move();
	bool isInside(sf::RenderWindow &);
	bool isInside(Spaceship *);
	string getMode() const;
	void setMode(string);
	int getID() const;
	void setID(int);
	int getHeart() const;
	void setHeart(int);
	int getScore() const;
	void setScore(int);
	int getLive() const;
	void setLive(int);
	string getName() const;
	void setName(string , sf::RenderWindow &);
	sf::Text & getText();
	sf::Text & getScoreText();
	sf::Text & getLiveText();
	sf::Sprite & getScoreIconSpr();
	sf::Sprite & getLiveIconSpr();
	bool movable(sf::RenderWindow &);

	sf::Clock clock;
	sf::Time time;
	int state_of_move; // 1: no sebghat 2: sebghat 3:shoot
	int step; // 1:back 2: down/up 3: foreard
	int arrow; // 0:down 1: up
private:

	int sizeX, sizeY;
	int X, Y;
	int Vx, Vy;
	sf::Texture Spaceship_tex;
	sf::Sprite Spaceship_spr;
	int mode; // 0: auto 1: keyboard
	int id;
	int live, score;
	string name;
	sf::Text name_text;
	sf::Font font;
	sf::Texture Score_tex;
	sf::Sprite Score_spr;
	sf::Texture Live_tex;
	sf::Sprite Live_spr;
	sf::Text Score_text;
	sf::Text Live_text;

};
class SpaceshipBullet {
public:
	SpaceshipBullet();
	~SpaceshipBullet();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getX() const;
	void setX(int);
	int getY() const;
	void setY(int);
	int getVx() const;
	void setVx(int);
	int getVy() const;
	void setVy(int);
	sf::Sprite & getSpr();
	sf::Texture & getTex();
	void updateSpr();
	void move();
	bool isInside(sf::RenderWindow &);
	int getSpaceship() const;
	void setSpaceship(int);

private:
	int sizeX, sizeY;
	int X, Y;
	int Vx, Vy;
	sf::Texture SpaceshipBullet_tex;
	sf::Sprite SpaceshipBullet_spr;
	int id;

};
class AlienBullet {
public:
	AlienBullet();
	~AlienBullet();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getX() const;
	void setX(int);
	int getY() const;
	void setY(int);
	int getVx() const;
	void setVx(int);
	int getVy() const;
	void setVy(int);
	sf::Sprite & getSpr();
	sf::Texture & getTex();
	void updateSpr();
	void move();
	bool isInside(sf::RenderWindow &);
	bool isInside(Spaceship *);

private:
	int sizeX, sizeY;
	int X, Y;
	int Vx, Vy;
	sf::Texture AlienBullet_tex;
	sf::Sprite AlienBullet_spr;

};
class Star {
public:
	Star();
	~Star();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getX() const;
	void setX(int);
	int getY() const;
	void setY(int);
	int getVx() const;
	void setVx(int);
	int getVy() const;
	void setVy(int);
	sf::Sprite & getSpr();
	sf::Texture & getTex();
	void updateSpr();
	void move();
	bool isInside(sf::RenderWindow &);
	bool isInside(Spaceship *);

private:
	int sizeX, sizeY;
	int X, Y;
	int Vx, Vy;
	sf::Texture Star_tex;
	sf::Sprite Star_spr;

};
class SmallAlien {
public:
	SmallAlien();
	~SmallAlien();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getX() const;
	void setX(int);
	int getY() const;
	void setY(int);
	int getVx() const;
	void setVx(int);
	int getVy() const;
	void setVy(int);
	sf::Sprite & getSpr();
	sf::Texture & getTex();
	void updateSpr();
	void move();
	bool isInside(sf::RenderWindow &);
	bool isInside(Spaceship *);
	bool isInside(SpaceshipBullet *);

	sf::Clock clock;
	sf::Time time;
private:

	int sizeX, sizeY;
	int X, Y;
	int Vx, Vy;
	sf::Texture SmallAlien_tex;
	sf::Sprite SmallAlien_spr;
	

};
class BigAlien {
public:
	BigAlien();
	~BigAlien();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getX() const;
	void setX(int);
	int getY() const;
	void setY(int);
	int getVx() const;
	void setVx(int);
	int getVy() const;
	void setVy(int);
	sf::Sprite & getSpr();
	sf::Texture & getTex();
	void updateSpr();
	void move();
	bool isInside(sf::RenderWindow &);
	bool isInside(Spaceship *);
	bool isInside(SpaceshipBullet *);
	bool movable(sf::RenderWindow &);

private:

	int sizeX, sizeY;
	int X, Y;
	int Vx, Vy;
	sf::Texture BigAlien_tex;
	sf::Sprite BigAlien_spr;
	

};
class GulAlien {
public:
	GulAlien();
	~GulAlien();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getX() const;
	void setX(int);
	int getY() const;
	void setY(int);
	int getVx() const;
	void setVx(int);
	int getVy() const;
	void setVy(int);
	sf::Sprite & getSpr();
	sf::Texture & getTex();
	void updateSpr();
	void move();
	bool isInside(sf::RenderWindow &);
	bool isInside(Spaceship *);
	bool isInside(SpaceshipBullet *);
	bool movable(sf::RenderWindow &);
	int getLive() const;
	void setLive(int);
	sf::Text &getText();

private:

	int sizeX, sizeY;
	int X, Y;
	int Vx, Vy;
	sf::Texture GulAlien_tex;
	sf::Sprite GulAlien_spr;
	int live;
	sf::Text live_text;
	sf::Font font;

};
class Heart {
public:
	Heart();
	~Heart();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getX() const;
	void setX(int);
	int getY() const;
	void setY(int);
	int getVx() const;
	void setVx(int);
	int getVy() const;
	void setVy(int);
	sf::Sprite & getSpr();
	sf::Texture & getTex();
	void updateSpr();
	void move();
	bool isInside(sf::RenderWindow &);
	bool isInside(Spaceship *);

private:
	int sizeX, sizeY;
	int X, Y;
	int Vx, Vy;
	sf::Texture Heart_tex;
	sf::Sprite Heart_spr;

};
class Meteor {
public:
	Meteor();
	~Meteor();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getX() const;
	void setX(int);
	int getY() const;
	void setY(int);
	int getVx() const;
	void setVx(int);
	int getVy() const;
	void setVy(int);
	sf::Sprite & getSpr();
	sf::Texture & getTex();
	void updateSpr();
	void move();
	bool isInside(sf::RenderWindow &);
	bool isInside(Spaceship *);
	bool isInside(SpaceshipBullet *);
private:
	int sizeX, sizeY;
	int X, Y;
	int Vx, Vy;
	sf::Texture Meteor_tex;
	sf::Sprite Meteor_spr;
	
};
class Menu {
public:
	Menu(int , int);
	~Menu();
	void draw(sf::RenderWindow &);
	void move_up();
	void move_down();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	int getPressedItemID() const;

private:
	const int MAX_ITEM;
	int SelectedItem, sizeX, sizeY;
	sf::Text *button;
	sf::Font font;



};
class Map {
public:
	Map();
	~Map();
	int getSizeX() const;
	void setSizeX(int);
	int getSizeY() const;
	void setSizeY(int);
	void generateMeteor(sf::RenderWindow &);
	void generateHeart(sf::RenderWindow &);
	void generateStar(sf::RenderWindow &);
	void generateBigAlien(sf::RenderWindow &);
	void generateSmallAlien(sf::RenderWindow &);
	void generateAlienBullet(sf::RenderWindow &, int);
	void generateSpaceshipBullet(sf::RenderWindow &, int);
	void drawSpaceshipBullet(sf::RenderWindow &);

	void drawMeteor(sf::RenderWindow &);
	void drawHeart(sf::RenderWindow &);
	void drawStar(sf::RenderWindow &);
	void drawBigAlien(sf::RenderWindow &);
	void drawSmallAlien(sf::RenderWindow &);
	void drawAlienBullet(sf::RenderWindow &);

	void generateSpaceship(sf::RenderWindow &, int);
	void drawSpaceship(sf::RenderWindow &);
	void move_upSpaceship(int, sf::RenderWindow &);
	void move_downSpaceship(int, sf::RenderWindow &);
	bool validity(int , sf::RenderWindow &);
	void check_Colision();
	void drawDetails(sf::RenderWindow &);
	void remove_all();

	int getScore1();
	int getScore2();
	string getName1();
	string getName2();
	
	void generateGulAlien(sf::RenderWindow &);
	void drawGulAlien(sf::RenderWindow &);
	void drawHeartDetailGulAlien(sf::RenderWindow &);

private:
	int sizeX, sizeY;
	//int **map;
	vector<Meteor *>Meteors;
	vector<Spaceship *>Spaceships;
	vector<Heart *>Hearts;
	vector<Star *>Stars;
	vector<BigAlien *>BigAliens;
	vector<SmallAlien *>SmallAliens;
	vector<SpaceshipBullet *>SpaceshipBullets;
	vector<AlienBullet *>AlienBullets;
	vector<GulAlien *>GulAliens;
	//vector< *>;
	
	


};
class Graphics {
public:
	Graphics();
	~Graphics();
	void setLevel(int);
	int getLevel() const;
	void Run();
	bool draw_menu();
	bool draw_Level1();
	bool draw_Level2();
	bool draw_Level3();
	bool draw_Level4();
	void draw_EndGame();
	void draw_NextLevel();
	void drawMap();
	void drawTime(int);
	void drawSpeedGame();
	void drawAboutHow();

	//Meteor *createMeteor();
private:
	int Level; // 0: Menu 
	int mode; // 1: 1 player 2: 2 player
	bool StartGame;
	bool state; // false: Game Over (Player1 win)/ true: win (player2 win)
	sf::RenderWindow window;
	Map *map;
	sf::Text Time_text;
	sf::Text Speed_text;
	sf::Font font;
	int start_time_of_highspeed;
	bool move_spaceship;
	string move_arrow;


};

#endif