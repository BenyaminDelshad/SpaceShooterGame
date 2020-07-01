/*************************************
Written By Benyamin Delshad
**************************************/
#include <bits/stdc++.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <SFML/Audio.hpp>
using namespace std;
#include "header.h"

/*
Classes List:
1.  Map                      line 36
2.  Graphics                 line 902
3.  Spaceship                line 1942
4.  SpaceshipBullet          line 2140
5.  AlienBullet              line 2219
6.  Star                     line 2299
7.  SmallAlien               line 2379
8.  BigAlien                 line 2470
9.  GulAlien                 line 2564
10. Heart                    line 2679
11. Meteor                   line 2759
12. SpaceshipBullet          line 2845

*/

int level_of_game = 1;
int speed_of_game = 1;
bool is_done = false;
bool pause = false;

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 1.  Map :
Map::Map() {
	

}
Map::~Map() {

}
int Map::getSizeX() const {
	return sizeX;
}
void Map::setSizeX(int x) {
	sizeX = x;
}
int Map::getSizeY() const {
	return sizeY;
}
void Map::setSizeY(int y) {
	sizeY = y;
}
void Map::generateMeteor(sf::RenderWindow &window) {
	for(int line = 61; line < window.getSize().y; line += 100) {
		int is = rand() % 10000;
		if(is < 9925) continue;
		if(!validity(line, window)) continue;
		Meteor *m = new Meteor();
		m->setX(window.getSize().x);
		m->setY(line);
		m->setSizeX((m->getTex() ).getSize().x);
		m->setSizeY((m->getTex() ).getSize().y);
		m->setVx(-5);
		m->setVy(0);
		Meteors.push_back(m);
		Meteors[Meteors.size() - 1]->move();
	}
}
void Map::generateHeart(sf::RenderWindow &window) {
	for(int line = 61; line < window.getSize().y; line += 100) {
		int is = rand() % 10000;
		if(is < 9993) continue;
		if(!validity(line, window)) continue;
		Heart *m = new Heart();
		m->setX(window.getSize().x);
		m->setY(line);
		m->setSizeX((m->getTex() ).getSize().x);
		m->setSizeY((m->getTex() ).getSize().y);
		m->setVx(-5);
		m->setVy(0);
		Hearts.push_back(m);
		Hearts[Hearts.size() - 1]->move();
	}
}
void Map::generateStar(sf::RenderWindow &window) {
	for(int line = 61; line < window.getSize().y; line += 100) {
		int is = rand() % 10000;
		if(is < 9975) continue;
		if(!validity(line, window)) continue;
		Star *m = new Star();
		m->setX(window.getSize().x);
		m->setY(line);
		m->setSizeX((m->getTex() ).getSize().x);
		m->setSizeY((m->getTex() ).getSize().y);
		m->setVx(-5);
		m->setVy(0);
		Stars.push_back(m);
		Stars[Stars.size() - 1]->move();
	}
}
void Map::generateBigAlien(sf::RenderWindow &window) {
	for(int line = 61; line < window.getSize().y; line += 100) {
		int is = rand() % 10000;
		if(is < 9975) continue;
		if(!validity(line, window)) continue;
		BigAlien *m = new BigAlien();
		m->setX(window.getSize().x);
		m->setY(line);
		m->setSizeX((m->getTex() ).getSize().x);
		m->setSizeY((m->getTex() ).getSize().y);
		m->setVx(-2);
		m->setVy(-5);
		BigAliens.push_back(m);
		BigAliens[BigAliens.size() - 1]->move();
	}
}
void Map::generateSmallAlien(sf::RenderWindow &window) {
	for(int line = 61; line < window.getSize().y; line += 100) {
		int is = rand() % 10000;
		if(is < 9950) continue;
		if(!validity(line, window)) continue;
		SmallAlien *m = new SmallAlien();
		m->setX(window.getSize().x);
		m->setY(line);
		m->setSizeX((m->getTex() ).getSize().x);
		m->setSizeY((m->getTex() ).getSize().y);
		m->setVx(-4);
		m->setVy(0);
		SmallAliens.push_back(m);
		SmallAliens[SmallAliens.size() - 1]->move();
	}
}
void Map::generateAlienBullet(sf::RenderWindow &window, int index) {
	AlienBullet *m = new AlienBullet();
	m->setSizeX((m->getTex() ).getSize().x);
	m->setSizeY((m->getTex() ).getSize().y);
	m->setX(SmallAliens[index]->getX());
	m->setY(SmallAliens[index]->getY() + SmallAliens[index]->getSizeY() / 2 - m->getSizeY() / 2);
	m->setVx(-6);
	m->setVy(0);
	AlienBullets.push_back(m);
	AlienBullets[AlienBullets.size() - 1]->move();
}

void Map::generateSpaceshipBullet(sf::RenderWindow &window, int index) {
	SpaceshipBullet *m = new SpaceshipBullet();
	m->setSizeX((m->getTex()).getSize().x);
	m->setSizeY((m->getTex()).getSize().y);
	m->setX(Spaceships[index]->getX() + Spaceships[index]->getSizeX());
	m->setY(Spaceships[index]->getY() + Spaceships[index]->getSizeY() / 2 - m->getSizeY() / 2);
	m->setVx(5);
	m->setVy(0);
	m->setSpaceship(Spaceships[index]->getID());
	SpaceshipBullets.push_back(m);
	SpaceshipBullets[SpaceshipBullets.size() - 1]->move();
	//cerr << "Done!" << endl;
}
void Map::drawMeteor(sf::RenderWindow &window) {
	for(int i = 0; i < Meteors.size(); ++i) {
		//cerr << "Meteor Pozition: " << Meteors[i]->getX() << ' ' << Meteors[i]->getY()  << endl;
		/*if(Meteors[i]->getX() < 20 && Meteors[i]->getY() < 20) {
			cerr << "Meteor Pozition: " << Meteors[i]->getX() << ' ' << Meteors[i]->getY()  << endl;

		}*/
		window.draw(Meteors[i]->getSpr());
		if(!pause) Meteors[i]->move();
		if(! (Meteors[i]->isInside(window)) ) {
			Meteor *tmp = Meteors[i];
			Meteors.erase(Meteors.begin() + i);
			delete tmp;
			//i--;
		}
	}
}
void Map::drawHeart(sf::RenderWindow &window) {
	for(int i = 0; i < Hearts.size(); ++i) {
		//cerr << "Heart Pozition: " << Hearts[i]->getX() << ' ' << Hearts[i]->getY()  << endl;
		/*if(Hearts[i]->getX() < 20 && Hearts[i]->getY() < 20) {
			cerr << "Heart Pozition: " << Hearts[i]->getX() << ' ' << Hearts[i]->getY()  << endl;

		}*/
		window.draw(Hearts[i]->getSpr());
		if(!pause) Hearts[i]->move();
		if(! (Hearts[i]->isInside(window)) ) {
			Heart *tmp = Hearts[i];
			Hearts.erase(Hearts.begin() + i);
			delete tmp;
			//i--;
		}
	}
}
void Map::drawStar(sf::RenderWindow &window) {
	for(int i = 0; i < Stars.size(); ++i) {
		//cerr << "Star Pozition: " << Stars[i]->getX() << ' ' << Stars[i]->getY()  << endl;
		/*if(Starrs[i]->getX() < 20 && Stars[i]->getY() < 20) {
			cerr << "Star Pozition: " << Stars[i]->getX() << ' ' << Stars[i]->getY()  << endl;

		}*/
		window.draw(Stars[i]->getSpr());
		if(!pause) Stars[i]->move();
		if(! (Stars[i]->isInside(window)) ) {
			Star *tmp = Stars[i];
			Stars.erase(Stars.begin() + i);
			delete tmp;
			//i--;
		}
	}
}
void Map::drawBigAlien(sf::RenderWindow &window) {
	for(int i = 0; i < BigAliens.size(); ++i) {
		//cerr << "Big Alien Pozition: " << BigAliens[i]->getX() << ' ' << BigAliens[i]->getY()  << endl;
		/*if(BigAliens[i]->getX() < 20 && BigAliens[i]->getY() < 20) {
			cerr << "BigAlien Pozition: " << BigAliens[i]->getX() << ' ' << BigAliens[i]->getY()  << endl;

		}*/
		window.draw(BigAliens[i]->getSpr());
		if(!pause)  {
			if(!BigAliens[i]->movable(window)) {
				BigAliens[i]->setVy(BigAliens[i]->getVy() * -1);
			}
			BigAliens[i]->move();
		}
		if(! (BigAliens[i]->isInside(window)) ) {
			BigAlien *tmp = BigAliens[i];
			BigAliens.erase(BigAliens.begin() + i);
			delete tmp;
			//i--;
		}
	}
}
void Map::drawSmallAlien(sf::RenderWindow &window) {
	for(int i = 0; i < SmallAliens.size(); ++i) {
		//cerr << "SmallAlien Pozition: " << SmallAliens[i]->getX() << ' ' << SmallAliens[i]->getY()  << endl;
		/*if(SmallAliens[i]->getX() < 20 && SmallAliens[i]->getY() < 20) {
			cerr << "SmallAlien Pozition: " << SmallAliens[i]->getX() << ' ' << SmallAliens[i]->getY()  << endl;

		}*/
		window.draw(SmallAliens[i]->getSpr());
		if(!pause) SmallAliens[i]->move();
		if(!pause) {
			SmallAliens[i]->time += (SmallAliens[i]->clock).getElapsedTime();
			(SmallAliens[i]->clock).restart();
		}
		if(!pause && (SmallAliens[i]->time).asMilliseconds() > 3300) {
			generateAlienBullet(window, i);
			(SmallAliens[i]->clock).restart();
			SmallAliens[i]->time = (SmallAliens[i]->clock).getElapsedTime();
		}
		if(! (SmallAliens[i]->isInside(window)) ) {
			SmallAlien *tmp = SmallAliens[i];
			SmallAliens.erase(SmallAliens.begin() + i);
			delete tmp;
			//i--;
		}
	}
}
void Map::drawSpaceshipBullet(sf::RenderWindow &window) {
	for(int i = 0; i < SpaceshipBullets.size(); ++i) {
		//cerr << "SpaceshipBullet Pozition: " << SpaceshipBullets[i]->getX() << ' ' << SpaceshipBullets[i]->getY()  << endl;
		/*if(SpaceshipBullets[i]->getX() < 20 && SpaceshipBullets[i]->getY() < 20) {
			cerr << "SpaceshipBullet Pozition: " << SpaceshipBullets[i]->getX() << ' ' << SpaceshipBullets[i]->getY()  << endl;

		}*/
		window.draw(SpaceshipBullets[i]->getSpr());
		if(!pause) SpaceshipBullets[i]->move();
		if(! (SpaceshipBullets[i]->isInside(window)) ) {
			SpaceshipBullet *tmp = SpaceshipBullets[i];
			SpaceshipBullets.erase(SpaceshipBullets.begin() + i);
			delete tmp;
			//i--;
		}
		//if(i == 1) cerr << "Done" << endl;
	}

}
void Map::drawAlienBullet(sf::RenderWindow &window) {
	for(int i = 0; i < AlienBullets.size(); ++i) {
		//cerr << "AlienBullet Pozition: " << AlienBullets[i]->getX() << ' ' << AlienBullets[i]->getY()  << endl;
		/*if(AlienBullets[i]->getX() < 20 && AlienBullets[i]->getY() < 20) {
			cerr << "AlienBullet Pozition: " << AlienBullets[i]->getX() << ' ' << AlienBullets[i]->getY()  << endl;

		}*/
		window.draw(AlienBullets[i]->getSpr());
		if(!pause) AlienBullets[i]->move();
		if(! (AlienBullets[i]->isInside(window)) ) {
			AlienBullet *tmp = AlienBullets[i];
			AlienBullets.erase(AlienBullets.begin() + i);
			delete tmp;
			//i--;
		}
		//if(i == 1) cerr << "Done" << endl;
	}

}
void Map::generateSpaceship(sf::RenderWindow &window, int mode) {
	if(mode == 1) {
		Spaceship *s = new Spaceship(1);
		s->setSizeX((s->getTex() ).getSize().x);
		s->setSizeY((s->getTex() ).getSize().y);
		s->setVx(0);
		s->setVy(5);
		s->setX(s->getSizeX() * 2 + 10);
		s->setY((window.getSize().y / 100 ) / 2 * 100);
		s->setMode("keyboard");
		s->setName("Player1", window);
		Spaceships.push_back(s);
		Spaceships[0]->move();
	}
	else { // mode == 2
		Spaceship *s = new Spaceship(1);
		s->setSizeX((s->getTex() ).getSize().x);
		s->setSizeY((s->getTex() ).getSize().y);
		s->setVx(0);
		s->setVy(5);
		s->setX(s->getSizeX() * 2 + 10);
		s->setY((window.getSize().y / 100 ) / 3 * 100);
		s->setMode("auto");
		s->setName("Player1", window);
		Spaceships.push_back(s);
		Spaceships[0]->move();

		Spaceship *s2 = new Spaceship(2);
		s2->setSizeX((s2->getTex() ).getSize().x);
		s2->setSizeY((s2->getTex() ).getSize().y);
		s2->setVx(0);
		s2->setVy(5);
		s2->setX(s2->getSizeX() * 2 + 10);
		s2->setY((window.getSize().y / 100 ) / 3 * 300);
		s2->setMode("auto");
		s2->setName("Player2", window);
		Spaceships.push_back(s2);
		Spaceships[1]->move();


	}

}
void Map::drawSpaceship(sf::RenderWindow &window) {
	for(int i = 0; i < Spaceships.size(); ++i) {
		//cerr << "Spaceship Pozition: " << Spaceships[i]->getX() << ' ' << Spaceships[i]->getY()  << endl;
		/*if(Spaceships[i]->getX() < 20 && Spaceships[i]->getY() < 20) {
			cerr << "Spaceship Pozition: " << Spaceships[i]->getX() << ' ' << Spaceships[i]->getY()  << endl;

		}*/
		window.draw(Spaceships[i]->getSpr());
		/*
		if(! (Spaceship[i]->isInside(window)) ) {
			Meteor *tmp = Meteors[i];
			Meteors.erase(Meteors.begin() + i);
			delete tmp;
		}
		*/
		if(Spaceships.size() == 1) continue;
		//---------------------------------------------------AI of Game!--------------------------------------------------------
		for(int j = 0; j < speed_of_game; ++j)
			Spaceships[i]->time += (Spaceships[i]->clock).getElapsedTime();
		(Spaceships[i]->clock).restart();
		if((Spaceships[i]->time).asMilliseconds() >= 500) {
			(Spaceships[i]->time) = sf::milliseconds(0);
			bool is = false;
			
			if(Spaceships[i]->getY() < Spaceships[1 - i]->getY() && Spaceships[i]->getY() + Spaceships[i]->getSizeY() + 5 > Spaceships[1 - i]->getY()) {
				if(Spaceships[i]->getLive() > Spaceships[1 - i]->getLive()) {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 0;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(5);
				}
				else {
					Spaceships[i]->state_of_move = 2;
					Spaceships[i]->arrow = 0;
					Spaceships[i]->step = 1;
					Spaceships[i]->setVx(-5);
					Spaceships[i]->setVy(0);	
				}
				is = true;
			}
			if(is) break;
			if(Spaceships[i]->getY() > Spaceships[1 - i]->getY() && Spaceships[i]->getY() < Spaceships[1 - i]->getY() + Spaceships[1 - i]->getSizeY() + 5) {
				if(Spaceships[i]->getLive() > Spaceships[1 - i]->getLive()) {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 1;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(-5);
				}
				else {
					Spaceships[i]->state_of_move = 2;
					Spaceships[i]->arrow = 1;
					Spaceships[i]->step = 1;
					Spaceships[i]->setVx(-5);
					Spaceships[i]->setVy(0);	
				}
				is = true;
			}
			if(is) break;
			
			for(int j = 0; j < Meteors.size(); ++j) {
				if(Meteors[j]->getY() > Spaceships[i]->getY() + Spaceships[i]->getSizeY()) continue;
				if(Meteors[j]->getY() + Meteors[j]->getSizeY() < Spaceships[i]->getSizeY()) continue;
				if(Meteors[j]->getX() > Spaceships[i]->getX() + 3 * Spaceships[i]->getSizeX() ) continue;
				if(Meteors[j]->getX() + Meteors[j]->getSizeX() < Spaceships[i]->getX()) continue;
				if(Spaceships[i]->getY() > Meteors[j]->getY() + Meteors[j]->getSizeY() / 2) {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 0;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(5);
				}
				else {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 1;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(-5);	
				}
				is = true;
			}
			if(is) break;
			
			for(int j = 0; j < AlienBullets.size(); ++j) {
				if(AlienBullets[j]->getY() > Spaceships[i]->getY() + Spaceships[i]->getSizeY()) continue;
				if(AlienBullets[j]->getY() + AlienBullets[j]->getSizeY() < Spaceships[i]->getSizeY()) continue;
				if(AlienBullets[j]->getX() > Spaceships[i]->getX() + 6 * Spaceships[i]->getSizeX() ) continue;
				if(AlienBullets[j]->getX() + AlienBullets[j]->getSizeX() < Spaceships[i]->getX()) continue;
			
				if(Spaceships[i]->getY() > AlienBullets[j]->getY() + AlienBullets[j]->getSizeY() / 2) {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 0;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(5);
				}
				else {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 1;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(-5);	
				}
				is = true;
			}
			if(is) break;
			
			for(int j = 0; j < SmallAliens.size(); ++j) {
				if(SmallAliens[j]->getY() > Spaceships[i]->getY() + Spaceships[i]->getSizeY()) continue;
				if(SmallAliens[j]->getY() + SmallAliens[j]->getSizeY() < Spaceships[i]->getSizeY()) continue;
				if(SmallAliens[j]->getX() > Spaceships[i]->getX() + 3 * Spaceships[i]->getSizeX() ) continue;
				if(SmallAliens[j]->getX() + SmallAliens[j]->getSizeX() < Spaceships[i]->getX()) continue;
				if(Spaceships[i]->getY() > SmallAliens[j]->getY() + SmallAliens[j]->getSizeY() / 2) {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 0;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(5);
				}
				else {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 1;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(-5);	
				}
				is = true;
			}
			if(is) break;
			
			for(int j = 0; j < BigAliens.size(); ++j) {
				if(BigAliens[j]->getY() > Spaceships[i]->getY() + Spaceships[i]->getSizeY()) continue;
				if(BigAliens[j]->getY() + BigAliens[j]->getSizeY() < Spaceships[i]->getSizeY()) continue;
				if(BigAliens[j]->getX() > Spaceships[i]->getX() + 3 * Spaceships[i]->getSizeX() ) continue;
				if(BigAliens[j]->getX() + BigAliens[j]->getSizeX() < Spaceships[i]->getX()) continue;
				if(Spaceships[i]->getY() > BigAliens[j]->getY() + BigAliens[j]->getSizeY() / 2) {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 0;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(5);
				}
				else {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 1;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(-5);	
				}
				is = true;
			}
			if(is) break;
			
			for(int j = 0; j < Hearts.size(); ++j) {
				if(Hearts[j]->getY() < Spaceships[i]->getY() + Spaceships[i]->getSizeY()
					&& Hearts[j]->getY() + Hearts[j]->getSizeY() > Spaceships[i]->getY()) continue;
				if(Hearts[j]->getY() > Spaceships[i]->getY() + Spaceships[i]->getSizeY() + 25) continue;
				if(Hearts[j]->getY() + Hearts[j]->getSizeY() + 25 < Spaceships[i]->getSizeY()) continue;
				if(Hearts[j]->getX() > Spaceships[i]->getX() + 4 * Spaceships[i]->getSizeX() ) continue;
				if(Hearts[j]->getX() + Hearts[j]->getSizeX() < Spaceships[i]->getX()) continue;

				if(Spaceships[i]->getY() < Hearts[j]->getY() + Hearts[j]->getSizeY() / 2) {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 0;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(5);
				}
				else {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 1;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(-5);	
				}
				is = true;
			}
			if(is) break;
			

			for(int j = 0; j < Stars.size(); ++j) {
				if(Stars[j]->getY() < Spaceships[i]->getY() + Spaceships[i]->getSizeY()
					&& Stars[j]->getY() + Stars[j]->getSizeY() > Spaceships[i]->getY()) continue;
				if(Stars[j]->getY() > Spaceships[i]->getY() + Spaceships[i]->getSizeY() + 25) continue;
				if(Stars[j]->getY() + Stars[j]->getSizeY() + 25 < Spaceships[i]->getSizeY()) continue;
				if(Stars[j]->getX() > Spaceships[i]->getX() + 4 * Spaceships[i]->getSizeX() ) continue;
				if(Stars[j]->getX() + Stars[j]->getSizeX() < Spaceships[i]->getX()) continue;

				if(Spaceships[i]->getY() < Stars[j]->getY() + Stars[j]->getSizeY() / 2) {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 0;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(5);
				}
				else {
					Spaceships[i]->state_of_move = 1;
					Spaceships[i]->arrow = 1;
					Spaceships[i]->setVx(0);
					Spaceships[i]->setVy(-5);	
				}
				is = true;
			}
			if(is) break;
			

			if(Spaceships[i]->getY() < 40) {
				Spaceships[i]->state_of_move = 1;
				Spaceships[i]->arrow = 0;
				Spaceships[i]->setVx(0);
				Spaceships[i]->setVy(5);
				is = true;
			}
			if(is) break;
			if(Spaceships[i]->getY() + Spaceships[i]->getSizeY() > 500) {
				Spaceships[i]->state_of_move = 1;
				Spaceships[i]->arrow = 1;
				Spaceships[i]->setVx(0);
				Spaceships[i]->setVy(-5);
				is = true;
			}
			if(is) break;


			if(true) {
				Spaceships[i]->state_of_move = 3;
				generateSpaceshipBullet(window, i);
				Spaceships[i]->setVx(0);
				Spaceships[i]->setVy(0);
				is = true;
			}
			if(is) break;

		}
		else {
			if(Spaceships[i]->state_of_move == 1 && Spaceships[i]->isInside(window))
				Spaceships[i]->move();
			else if (Spaceships[i]->state_of_move == 2) {
				if(Spaceships[i]->step == 1) {
					if(Spaceships[i]->isInside(window))
						Spaceships[i]->move();
					else {
						Spaceships[i]->step = 2;
						Spaceships[i]->setVx(0);
						if(Spaceships[i]->arrow == 0)
							Spaceships[i]->setVy(5);
						else
							Spaceships[i]->setVy(-5);
					}
				}
				else if(Spaceships[i]->step == 2) {
					if(((Spaceships[i]->arrow == 0 && Spaceships[i]->getY() < Spaceships[1 - i]->getY() + Spaceships[1 - i]->getSizeY() + 5 )
						|| (Spaceships[i]->arrow == 1 && Spaceships[i]->getY() +Spaceships[i]->getSizeY() > Spaceships[1 - i]->getY() - 5) )
						 && Spaceships[i]->isInside(window))
						Spaceships[i]->move();
					else {
						Spaceships[i]->step = 3;
						Spaceships[i]->setVx(5);
						Spaceships[i]->setVy(0);
					}
				}
				else if(Spaceships[i]->step == 3) {
					if(Spaceships[i]->getX() < Spaceships[i]->getSizeX() * 2 + 10 && Spaceships[i]->isInside(window))
						Spaceships[i]->move();
					else {
						Spaceships[i]->step = 4;
						Spaceships[i]->setVx(0);
						if(Spaceships[i]->arrow == 0)
							Spaceships[i]->setVy(5);
						else
							Spaceships[i]->setVy(-5);	
					}
				}
				else {
					Spaceships[i]->move();
				}
			}
			else if(Spaceships[i]->state_of_move == 3){
				//generateSpaceshipBullet(window, i);
			}

		}






		//------------------------------------------------------------------------------------------------------------------------
	}

}
void Map::move_upSpaceship(int index, sf::RenderWindow &window) {
	Spaceships[index]->setVy(abs(Spaceships[index]->getVy()) * -1);
	if(Spaceships[index]->movable(window)) Spaceships[index]->move();

}
void Map::move_downSpaceship(int index, sf::RenderWindow &window) {
	Spaceships[index]->setVy(abs(Spaceships[index]->getVy()));
	if(Spaceships[index]->movable(window)) Spaceships[index]->move();
}
bool Map::validity(int line, sf::RenderWindow &window) {
	for(int i = 0; i < Meteors.size(); ++i) {
		if(Meteors[i]->getY() != line) continue;
		if(Meteors[i]->getX() > window.getSize().x - 3 * Meteors[i]->getSizeX()) return false;
	}
	for(int i = 0; i < Hearts.size(); ++i) {
		if(Hearts[i]->getY() != line) continue;
		if(Hearts[i]->getX() > window.getSize().x - 3 * Hearts[i]->getSizeX()) return false;
	}
	for(int i = 0; i < Stars.size(); ++i) {
		if(Stars[i]->getY() != line) continue;
		if(Stars[i]->getX() > window.getSize().x - 3 * Stars[i]->getSizeX()) return false;
	}
	for(int i = 0; i < BigAliens.size(); ++i) {
		if(BigAliens[i]->getY() != line) continue;
		if(BigAliens[i]->getX() > window.getSize().x - 3 * BigAliens[i]->getSizeX()) return false;
	}
	for(int i = 0; i < SmallAliens.size(); ++i) {
		if(SmallAliens[i]->getY() != line) continue;
		if(SmallAliens[i]->getX() > window.getSize().x - 3 * SmallAliens[i]->getSizeX()) return false;
	}
	return true;
}
void Map::check_Colision() {
	for(int i = 0; i < Spaceships.size(); ++i) {
		for(int j = 0; j < Hearts.size(); ++j) {
			if(Hearts[j]->isInside(Spaceships[i])) {
				Spaceships[i]->setLive(Spaceships[i]->getLive() + 1);
				Heart *tmp = Hearts[j];
				Hearts.erase(Hearts.begin() + j);
				delete tmp;
			}
		}
		for(int j = 0; j < Stars.size(); ++j) {
			if(Stars[j]->isInside(Spaceships[i])) {
				Spaceships[i]->setScore(Spaceships[i]->getScore() + 1);
				Star *tmp = Stars[j];
				Stars.erase(Stars.begin() + j);
				delete tmp;
			}
		}
		for(int j = 0; j < Meteors.size(); ++j) {
			if(Meteors[j]->isInside(Spaceships[i])) {
				Spaceships[i]->setLive(Spaceships[i]->getLive() - 1);
				Meteor *tmp = Meteors[j];
				Meteors.erase(Meteors.begin() + j);
				delete tmp;
				if(Spaceships[i]->getLive() == 0) {
					is_done = true;
				}
			}
		}
		for(int j = 0; j < BigAliens.size(); ++j) {
			if(BigAliens[j]->isInside(Spaceships[i])) {
				Spaceships[i]->setLive(Spaceships[i]->getLive() - 1);
				BigAlien *tmp = BigAliens[j];
				BigAliens.erase(BigAliens.begin() + j);
				delete tmp;
				if(Spaceships[i]->getLive() == 0) {
					is_done = true;
				}
			}
		}
		for(int j = 0; j < SmallAliens.size(); ++j) {
			if(SmallAliens[j]->isInside(Spaceships[i])) {
				Spaceships[i]->setLive(Spaceships[i]->getLive() - 1);
				SmallAlien *tmp = SmallAliens[j];
				SmallAliens.erase(SmallAliens.begin() + j);
				delete tmp;
				if(Spaceships[i]->getLive() == 0) {
					is_done = true;
				}
			}
		}
		for(int j = 0; j < AlienBullets.size(); ++j) {
			if(AlienBullets[j]->isInside(Spaceships[i])) {
				Spaceships[i]->setLive(Spaceships[i]->getLive() - 1);
				AlienBullet *tmp = AlienBullets[j];
				AlienBullets.erase(AlienBullets.begin() + j);
				delete tmp;
				if(Spaceships[i]->getLive() == 0) {
					is_done = true;
				}
			}
		}
		
	}
	//if(num > 1) cerr << SpaceshipBullets.size() << endl;
	//bool is = false;

	for(int i = 0; i < SpaceshipBullets.size(); ++i) {
		//is= false;
		for(int j = 0; j < Meteors.size(); ++j) {
			if(Meteors[j]->isInside(SpaceshipBullets[i])) {
				//Spaceships[i]->setLive(Spaceships[i]->getLive() - 1);
				Spaceships[SpaceshipBullets[i]->getSpaceship() - 1]->setScore(Spaceships[SpaceshipBullets[i]->getSpaceship() - 1]->getScore() + 1);
				Meteor *tmp = Meteors[j];
				Meteors.erase(Meteors.begin() + j);
				delete tmp;
				SpaceshipBullet *tmp2 = SpaceshipBullets[i];
				SpaceshipBullets.erase(SpaceshipBullets.begin() + i);
				delete tmp2;
				//i--;
				//is = true;
				//break;
				//if(Spaceships[i]->getLive() == 0) {
				//	is_done = true;
				//}
			}
		}
		//if(is) continue;
		for(int j = 0; j < BigAliens.size(); ++j) {
			if(BigAliens[j]->isInside(SpaceshipBullets[i])) {
				//Spaceships[i]->setLive(Spaceships[i]->getLive() - 1);
				Spaceships[SpaceshipBullets[i]->getSpaceship() - 1]->setScore(Spaceships[SpaceshipBullets[i]->getSpaceship() - 1]->getScore() + 1);
				BigAlien *tmp = BigAliens[j];
				BigAliens.erase(BigAliens.begin() + j);
				delete tmp;
				SpaceshipBullet *tmp2 = SpaceshipBullets[i];
				SpaceshipBullets.erase(SpaceshipBullets.begin() + i);
				delete tmp2;
				//i--;
				//break;
				//if(Spaceships[i]->getLive() == 0) {
				//	is_done = true;
				//}
			}
		}
		//if(is) continue;
		for(int j = 0; j < SmallAliens.size(); ++j) {
			if(SmallAliens[j]->isInside(SpaceshipBullets[i])) {
				//Spaceships[i]->setLive(Spaceships[i]->getLive() - 1);
				Spaceships[SpaceshipBullets[i]->getSpaceship() - 1]->setScore(Spaceships[SpaceshipBullets[i]->getSpaceship() - 1]->getScore() + 1);
				SmallAlien *tmp = SmallAliens[j];
				SmallAliens.erase(SmallAliens.begin() + j);
				delete tmp;
				SpaceshipBullet *tmp2 = SpaceshipBullets[i];
				SpaceshipBullets.erase(SpaceshipBullets.begin() + i);
				delete tmp2;
				//i--;
				//break;
				//if(Spaceships[i]->getLive() == 0) {
				//	is_done = true;
				//}
			}
		}

		for(int j = 0; j < GulAliens.size(); ++j) {
			if(GulAliens[j]->isInside(SpaceshipBullets[i])) {
				//Spaceships[i]->setLive(Spaceships[i]->getLive() - 1);
				Spaceships[SpaceshipBullets[i]->getSpaceship() - 1]->setScore(Spaceships[SpaceshipBullets[i]->getSpaceship() - 1]->getScore() + 1);
				GulAliens[j]->setLive(GulAliens[j]->getLive() - 1);
				if(GulAliens[j]->getLive() == 0) {
					is_done = true;
				}
				/*SmallAlien *tmp = SmallAliens[j];
				SmallAliens.erase(SmallAliens.begin() + j);
				delete tmp;*/
				SpaceshipBullet *tmp2 = SpaceshipBullets[i];
				SpaceshipBullets.erase(SpaceshipBullets.begin() + i);
				delete tmp2;
			}
		}
		//if(is) continue;
	}
	if(Spaceships.size() > 1) {
		if(Spaceships[0]->isInside(Spaceships[1])) {
			Spaceships[0]->setLive(Spaceships[0]->getLive() - 1);
			Spaceships[1]->setLive(Spaceships[1]->getLive() - 1);
			Spaceships[0]->setY(150);
			Spaceships[1]->setY(350);
			if(Spaceships[0]->getLive() == 0 || Spaceships[1]->getLive() == 0) {
				is_done = true;
			}	
		}
	}


}
void Map::drawDetails(sf::RenderWindow &window) {
	for(int i = 0; i < Spaceships.size(); i++) {
		window.draw(Spaceships[i]->getText());
		window.draw(Spaceships[i]->getScoreIconSpr());
		window.draw(Spaceships[i]->getLiveIconSpr());
		window.draw(Spaceships[i]->getScoreText());
		window.draw(Spaceships[i]->getLiveText());
	}
}
void Map::drawHeartDetailGulAlien(sf::RenderWindow &window) {
	window.draw(GulAliens[0]->getText());
}
void Map::remove_all() {
	while(!Stars.empty()) {
		Star *tmp = Stars[0];
		Stars.erase(Stars.begin());
		delete tmp;
	}
	while(!Meteors.empty()) {
		Meteor *tmp = Meteors[0];
		Meteors.erase(Meteors.begin());
		delete tmp;
	}
	while(!Hearts.empty()) {
		Heart *tmp = Hearts[0];
		Hearts.erase(Hearts.begin());
		delete tmp;
	}
	while(!BigAliens.empty()) {
		BigAlien *tmp = BigAliens[0];
		BigAliens.erase(BigAliens.begin());
		delete tmp;
	}
	while(!SmallAliens.empty()) {
		SmallAlien *tmp = SmallAliens[0];
		SmallAliens.erase(SmallAliens.begin());
		delete tmp;
	}
	while(!SpaceshipBullets.empty()) {
		SpaceshipBullet *tmp = SpaceshipBullets[0];
		SpaceshipBullets.erase(SpaceshipBullets.begin());
		delete tmp;
	}
	while(!AlienBullets.empty()) {
		AlienBullet *tmp = AlienBullets[0];
		AlienBullets.erase(AlienBullets.begin());
		delete tmp;
	}
}
int Map::getScore1() {
	return Spaceships[0]->getScore() + 10 * Spaceships[0]->getLive();
}
int Map::getScore2() {
	if(Spaceships.size() < 2) return -1;
	return Spaceships[1]->getScore() + 10 * Spaceships[1]->getLive();
}
string Map::getName1() {
	return Spaceships[0]->getName();
}
string Map::getName2() {
	if(Spaceships.size() < 2) return "";
	return Spaceships[1]->getName();
}
void Map::generateGulAlien(sf::RenderWindow &window) {
	GulAlien *m = new GulAlien();
	m->setSizeX((m->getTex()).getSize().x);
	m->setSizeY((m->getTex()).getSize().y);
	m->setX(window.getSize().x - m->getSizeX() - 20);
	m->setY(window.getSize().y / 2 - m->getSizeY() / 2);
	m->setVx(0);
	m->setVy(5);
	GulAliens.push_back(m);
	GulAliens[GulAliens.size() - 1]->move();
	//cerr << "Done!" << endl;
}
void Map::drawGulAlien(sf::RenderWindow &window) {
	for(int i = 0; i < GulAliens.size(); ++i) {
		window.draw(GulAliens[i]->getSpr());
		if(!pause)  {
			if(!GulAliens[i]->movable(window)) {
				GulAliens[i]->setVy(GulAliens[i]->getVy() * -1);
			}
			GulAliens[i]->move();
		}



	}	
}

//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 3.  Graphics :
Graphics::Graphics() {
	setLevel(0);
	StartGame = false;
	window.create(sf::VideoMode(960, 540), "Space Shooter Game!");
	window.setVerticalSyncEnabled(true);

	if(!font.loadFromFile("arial.ttf")) {
		cerr << "Arial Font in Graphics can not be Loaded!" << endl;
	}

	Time_text.setString("0");
	Time_text.setColor(sf::Color::Red);
	Time_text.setFont(font);
	Time_text.setPosition(sf::Vector2f(window.getSize().x / 2 - 20 , 5) );
	Time_text.setCharacterSize(30);

	Speed_text.setString(to_string(speed_of_game));
	Speed_text.setColor(sf::Color::Green);
	Speed_text.setFont(font);
	Speed_text.setPosition(sf::Vector2f(window.getSize().x / 2 - 10 , window.getSize().y - 35) );
	Speed_text.setCharacterSize(30);
	
}
Graphics::~Graphics() {

}
void Graphics::setLevel(int l) {
	Level = l;
}
int Graphics::getLevel() const {
	return Level;
}
void Graphics::Run() {
	//state = false;
	StartGame = draw_menu();
	if(!StartGame) {
		window.close();
		return;
	}
	map = new Map();
	setLevel(getLevel() + 1);
	bool next_level;
	next_level = draw_Level1();
	if(!next_level) {
		draw_EndGame();
		return;
	}
	draw_NextLevel();
	setLevel(getLevel() + 1);
	next_level = draw_Level2();
	if(!next_level) {
		draw_EndGame();
		return;
	}
	draw_NextLevel();
	setLevel(getLevel() + 1);
	next_level = draw_Level3();
	if(!next_level|| mode == 2) {
		draw_EndGame();
		return;
	}
	draw_NextLevel();
	setLevel(getLevel() + 1);
	next_level = draw_Level4();
	if(!next_level) {
		draw_EndGame();
		return;
	}
	//setLevel(getLevel() + 1);
	//state = true;
	draw_EndGame();
}
bool Graphics::draw_menu() {
	window.clear();
	sf::Texture background_tex;
	if(!background_tex.loadFromFile("Wallpaper2.png")) {
		cerr << "Backgrund of Menu can not be Loaded!" << endl;
		//return -1;
	}
	background_tex.setSmooth(true);
	sf::Sprite background_spr;
	background_spr.setTexture(background_tex);

	Menu menu(window.getSize().x, window.getSize().y);
	while (window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				case sf::Keyboard::Up:
					menu.move_up();
					break;
				case sf::Keyboard::Down:
					menu.move_down();
					break;
				case sf::Keyboard::Return:
					switch(menu.getPressedItemID()) {
					case 0:
						mode = 1;
						return true;
						break;
					case 1:
						mode = 2;
						return true;
						break;
					case 3:
						return false;
						break;
					case 2:
						drawAboutHow();
						break;
					}
					break;
				}
				break;
			}
		}
		window.clear();
		window.draw(background_spr);
		menu.draw(window);
		window.display();
	}
	
}
bool Graphics::draw_Level1() {
	window.clear();

	sf::Texture background_tex;
	if(!background_tex.loadFromFile("Level1BackGround.png")) {
		cerr << "Backgrund of Level one can not be Loaded!" << endl;
		//return -1;
	}
	background_tex.setSmooth(true);
	sf::Sprite background_spr;
	background_spr.setTexture(background_tex);

	map->generateSpaceship(window, mode);
	//******************************* for testing nexl level:
	//return true;
	//******************************* end testing 

	//sf::Clock clock;
	//sf::Time time;
	sf::Clock clock;
	sf::Time time;
	sf::Time time2;
	while (window.isOpen()) {
		sf::Event event;
		while(!move_spaceship && window.pollEvent(event)) {
			//cerr << "ey baba ..." << endl;
			switch(event.type) {
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				case sf::Keyboard::Space:
					if(mode == 1 && !pause) {
						map->generateSpaceshipBullet(window, 0);
					}
					break;
				case sf::Keyboard::Up:
					if(!pause && mode == 1) {
						move_spaceship = true;
						move_arrow = "up";
					}
					/*if(mode == 1) {
						map->move_upSpaceship(0);
						//cerr << "Move Up Spaceship" << endl;
					}*/
					break;
				case sf::Keyboard::Down:
					if(!pause && mode == 1) {
						move_spaceship = true;
						move_arrow = "down";
					}
					/*if(mode == 1) {
						map->move_downSpaceship(0);
						//cerr << "Move Down Spaceship" << endl;
					}*/
					break;
				case sf::Keyboard::S:
					/*if(speed_of_game == 4) {
						cerr << "End High speed at time: " << time.asMilliseconds() << endl;
						cerr << "qmount of Highspeed time: " << time.asMilliseconds() - start_time_of_highspeed << endl;
						time += sf::milliseconds(3 * (time.asMilliseconds() - start_time_of_highspeed)); 
						cerr << "Now time: " << time.asMilliseconds() << endl;
					}
					else {
						cerr << "Start High speed at time: " << time.asMilliseconds() << endl;
						start_time_of_highspeed = time.asMilliseconds();
					}*/
					speed_of_game = 5 - speed_of_game;
					break;
				case sf::Keyboard::P:
					if(pause) pause = false;
					else pause = true;
					break;
				case sf::Keyboard::Return:

					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code) {
					case sf::Keyboard::Up:
						move_spaceship = false;
						break;
					case sf::Keyboard::Down:
						move_spaceship = false;
						break;
				}
				break;
			}
		}
		while(move_spaceship && window.pollEvent(event)) {
			switch(event.type) {
			/*case sf::Event::Closed :
				window.close();
				break;*/
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				/*case sf::Keyboard::Up:
					move_spaceship = true;
					move_arrow = "up";
					break;
				case sf::Keyboard::Down:
					move_spaceship = true;
					move_arrow = "down";
					break;
				*/
				case sf::Keyboard::Space:
					if(mode == 1 && !pause) {
						map->generateSpaceshipBullet(window, 0);
					}
					break;
				case sf::Keyboard::S:
					speed_of_game = 5 - speed_of_game;
					break;
				/*case sf::Keyboard::Return:

					break;*/
				}
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code) {
					case sf::Keyboard::Up:
						move_spaceship = false;
						break;
					case sf::Keyboard::Down:
						move_spaceship = false;
						break;
				}
				break;
			}
		}
		

		if(mode == 1 && move_spaceship) {
			if(move_arrow == "up") {
				map->move_upSpaceship(0, window);
				//cerr << "Move Up Spaceship" << endl;
			}
			else {
				map->move_downSpaceship(0, window);
				//cerr << "Move Down Spaceship" << endl;
			}
		}
		//time = clock.getElapsedTime();
		//if(time.asMilliseconds() < 30) continue;
		//clock.restart();
		this_thread::sleep_for (std::chrono::milliseconds(6 * (5 - speed_of_game)));

		window.clear();
		window.draw(background_spr);
		time2 = clock.getElapsedTime();
		clock.restart();
		if(!pause)
			for(int i = 0; i < speed_of_game; ++i)
				time += time2;
		drawTime(time.asMilliseconds());
		drawSpeedGame();
		map->drawDetails(window);
		drawMap();
		window.display();
		if(!pause)
			map->check_Colision();
		if(is_done) return false;
		if(time.asMilliseconds() >= 120 * 1000) {
			map->remove_all();
			move_spaceship = false;
			return true;
		}
	}

}
bool Graphics::draw_Level2() {
window.clear();
	//return true;

	sf::Texture background_tex;
	if(!background_tex.loadFromFile("Level2BackGround.png")) {
		cerr << "Backgrund of Level two can not be Loaded!" << endl;
		//return -1;
	}
	background_tex.setSmooth(true);
	sf::Sprite background_spr;
	background_spr.setTexture(background_tex);

	//map->generateSpaceship(window, mode);

	sf::Clock clock;
	sf::Time time;
	sf::Time time2;
	while (window.isOpen()) {
		sf::Event event;
		while(!move_spaceship && window.pollEvent(event)) {
			//cerr << "ey baba ..." << endl;
			switch(event.type) {
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				case sf::Keyboard::Up:
					if(!pause && mode == 1) {
						move_spaceship = true;
						move_arrow = "up";
					}
					/*if(mode == 1) {
						map->move_upSpaceship(0);
						//cerr << "Move Up Spaceship" << endl;
					}*/
					break;
				case sf::Keyboard::Down:
					if(!pause && mode == 1) {
						move_spaceship = true;
						move_arrow = "down";
					}
					/*if(mode == 1) {
						map->move_downSpaceship(0);
						//cerr << "Move Down Spaceship" << endl;
					}*/
					break;
				case sf::Keyboard::S:
					/*if(speed_of_game == 4) {
						cerr << "End High speed at time: " << time.asMilliseconds() << endl;
						cerr << "qmount of Highspeed time: " << time.asMilliseconds() - start_time_of_highspeed << endl;
						time += sf::milliseconds(3 * (time.asMilliseconds() - start_time_of_highspeed)); 
						cerr << "Now time: " << time.asMilliseconds() << endl;
					}
					else {
						cerr << "Start High speed at time: " << time.asMilliseconds() << endl;
						start_time_of_highspeed = time.asMilliseconds();
					}*/
					speed_of_game = 5 - speed_of_game;
					break;
				case sf::Keyboard::P:
					if(pause) pause = false;
					else pause = true;
					break;
				case sf::Keyboard::Space:
					if(mode == 1 && !pause) {
						map->generateSpaceshipBullet(window, 0);
					}
					break;
				case sf::Keyboard::Return:

					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code) {
					case sf::Keyboard::Up:
						move_spaceship = false;
						break;
					case sf::Keyboard::Down:
						move_spaceship = false;
						break;
				}
				break;
			}
		}
		while(move_spaceship && window.pollEvent(event)) {
			switch(event.type) {
			/*case sf::Event::Closed :
				window.close();
				break;*/
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				/*case sf::Keyboard::Up:
					move_spaceship = true;
					move_arrow = "up";
					break;
				case sf::Keyboard::Down:
					move_spaceship = true;
					move_arrow = "down";
					break;
				*/
				case sf::Keyboard::S:
					speed_of_game = 5 - speed_of_game;
					break;
				/*case sf::Keyboard::Return:

					break;*/
				case sf::Keyboard::Space:
					if(mode == 1 && !pause) {
						map->generateSpaceshipBullet(window, 0);
					}
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code) {
					case sf::Keyboard::Up:
						move_spaceship = false;
						break;
					case sf::Keyboard::Down:
						move_spaceship = false;
						break;
				}
				break;
			}
		}
		

		if(mode == 1 && move_spaceship) {
			if(move_arrow == "up") {
				map->move_upSpaceship(0, window);
				//cerr << "Move Up Spaceship" << endl;
			}
			else {
				map->move_downSpaceship(0, window);
				//cerr << "Move Down Spaceship" << endl;
			}
		}
		//time = clock.getElapsedTime();
		//if(time.asMilliseconds() < 30) continue;
		//clock.restart();
		this_thread::sleep_for (std::chrono::milliseconds(6 * (5 - speed_of_game)));

		window.clear();
		window.draw(background_spr);
		time2 = clock.getElapsedTime();
		clock.restart();
		if(!pause)
			for(int i = 0; i < speed_of_game; ++i)
				time += time2;
		drawTime(time.asMilliseconds());
		drawSpeedGame();
		map->drawDetails(window);
		drawMap();
		window.display();
		if(!pause)
			map->check_Colision();
		if(is_done) return false;
		if(time.asMilliseconds() >= 120 * 1000) {
			map->remove_all();
			move_spaceship = false;
			return true;
		}

	}

}
bool Graphics::draw_Level3() {
	//return true;
	
	sf::Texture background_tex;
	if(!background_tex.loadFromFile("Level3BackGround.png")) {
		cerr << "Backgrund of Level three can not be Loaded!" << endl;
		//return -1;
	}
	background_tex.setSmooth(true);
	sf::Sprite background_spr;
	background_spr.setTexture(background_tex);

	//map->generateSpaceship(window, mode);

	sf::Clock clock;
	sf::Time time;
	sf::Time time2;
	while (window.isOpen()) {
		sf::Event event;
		while(!move_spaceship && window.pollEvent(event)) {
			//cerr << "ey baba ..." << endl;
			switch(event.type) {
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				case sf::Keyboard::Up:
					if(!pause && mode == 1) {
						move_spaceship = true;
						move_arrow = "up";
					}
					/*if(mode == 1) {
						map->move_upSpaceship(0);
						//cerr << "Move Up Spaceship" << endl;
					}*/
					break;
				case sf::Keyboard::Down:
					if(!pause && mode == 1) {
						move_spaceship = true;
						move_arrow = "down";
					}
					/*if(mode == 1) {
						map->move_downSpaceship(0);
						//cerr << "Move Down Spaceship" << endl;
					}*/
					break;
				case sf::Keyboard::S:
					/*if(speed_of_game == 4) {
						cerr << "End High speed at time: " << time.asMilliseconds() << endl;
						cerr << "qmount of Highspeed time: " << time.asMilliseconds() - start_time_of_highspeed << endl;
						time += sf::milliseconds(3 * (time.asMilliseconds() - start_time_of_highspeed)); 
						cerr << "Now time: " << time.asMilliseconds() << endl;
					}
					else {
						cerr << "Start High speed at time: " << time.asMilliseconds() << endl;
						start_time_of_highspeed = time.asMilliseconds();
					}*/
					speed_of_game = 5 - speed_of_game;
					break;
				case sf::Keyboard::P:
					if(pause) pause = false;
					else pause = true;
					break;
				case sf::Keyboard::Space:
					if(mode == 1 && !pause) {
						map->generateSpaceshipBullet(window, 0);
					}
					break;
				case sf::Keyboard::Return:

					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code) {
					case sf::Keyboard::Up:
						move_spaceship = false;
						break;
					case sf::Keyboard::Down:
						move_spaceship = false;
						break;
				}
				break;
			}
		}
		while(move_spaceship && window.pollEvent(event)) {
			switch(event.type) {
			/*case sf::Event::Closed :
				window.close();
				break;*/
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				/*case sf::Keyboard::Up:
					move_spaceship = true;
					move_arrow = "up";
					break;
				case sf::Keyboard::Down:
					move_spaceship = true;
					move_arrow = "down";
					break;
				*/
				case sf::Keyboard::S:
					speed_of_game = 5 - speed_of_game;
					break;
				/*case sf::Keyboard::Return:

					break;*/
				case sf::Keyboard::Space:
					if(mode == 1 && !pause) {
						map->generateSpaceshipBullet(window, 0);
					}
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code) {
					case sf::Keyboard::Up:
						move_spaceship = false;
						break;
					case sf::Keyboard::Down:
						move_spaceship = false;
						break;
				}
				break;
			}
		}
		

		if(mode == 1 && move_spaceship) {
			if(move_arrow == "up") {
				map->move_upSpaceship(0, window);
				//cerr << "Move Up Spaceship" << endl;
			}
			else {
				map->move_downSpaceship(0, window);
				//cerr << "Move Down Spaceship" << endl;
			}
		}
		//time = clock.getElapsedTime();
		//if(time.asMilliseconds() < 30) continue;
		//clock.restart();
		this_thread::sleep_for (std::chrono::milliseconds(6 * (5 - speed_of_game)));

		window.clear();
		window.draw(background_spr);
		time2 = clock.getElapsedTime();
		clock.restart();
		if(!pause)
			for(int i = 0; i < speed_of_game; ++i)
				time += time2;
		drawTime(time.asMilliseconds());
		drawSpeedGame();
		map->drawDetails(window);
		drawMap();
		window.display();
		if(!pause)
			map->check_Colision();
		if(is_done) return false;
		if(time.asMilliseconds() >= 120 * 1000) {
			map->remove_all();
			move_spaceship = false;
			return true;
		}

	}

}
bool Graphics::draw_Level4() {

	sf::Texture background_tex;
	if(!background_tex.loadFromFile("Level4BackGround.png")) {
		cerr << "Backgrund of Level four can not be Loaded!" << endl;
		//return -1;
	}
	background_tex.setSmooth(true);
	sf::Sprite background_spr;
	background_spr.setTexture(background_tex);

	//map->generateSpaceship(window, mode);

	map->generateGulAlien(window);

	sf::Clock clock;
	sf::Time time;
	sf::Time time2;
	while (window.isOpen()) {
		sf::Event event;
		while(!move_spaceship && window.pollEvent(event)) {
			//cerr << "ey baba ..." << endl;
			switch(event.type) {
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				case sf::Keyboard::Up:
					if(!pause && mode == 1) {
						move_spaceship = true;
						move_arrow = "up";
					}
					/*if(mode == 1) {
						map->move_upSpaceship(0);
						//cerr << "Move Up Spaceship" << endl;
					}*/
					break;
				case sf::Keyboard::Down:
					if(!pause && mode == 1) {
						move_spaceship = true;
						move_arrow = "down";
					}
					/*if(mode == 1) {
						map->move_downSpaceship(0);
						//cerr << "Move Down Spaceship" << endl;
					}*/
					break;
				case sf::Keyboard::S:
					/*if(speed_of_game == 4) {
						cerr << "End High speed at time: " << time.asMilliseconds() << endl;
						cerr << "qmount of Highspeed time: " << time.asMilliseconds() - start_time_of_highspeed << endl;
						time += sf::milliseconds(3 * (time.asMilliseconds() - start_time_of_highspeed)); 
						cerr << "Now time: " << time.asMilliseconds() << endl;
					}
					else {
						cerr << "Start High speed at time: " << time.asMilliseconds() << endl;
						start_time_of_highspeed = time.asMilliseconds();
					}*/
					speed_of_game = 5 - speed_of_game;
					break;
				case sf::Keyboard::P:
					if(pause) pause = false;
					else pause = true;
					break;
				case sf::Keyboard::Space:
					if(mode == 1 && !pause) {
						map->generateSpaceshipBullet(window, 0);
					}
					break;
				case sf::Keyboard::Return:

					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code) {
					case sf::Keyboard::Up:
						move_spaceship = false;
						break;
					case sf::Keyboard::Down:
						move_spaceship = false;
						break;
				}
				break;
			}
		}
		while(move_spaceship && window.pollEvent(event)) {
			switch(event.type) {
			/*case sf::Event::Closed :
				window.close();
				break;*/
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				/*case sf::Keyboard::Up:
					move_spaceship = true;
					move_arrow = "up";
					break;
				case sf::Keyboard::Down:
					move_spaceship = true;
					move_arrow = "down";
					break;
				*/
				case sf::Keyboard::S:
					speed_of_game = 5 - speed_of_game;
					break;
				/*case sf::Keyboard::Return:

					break;*/
				case sf::Keyboard::Space:
					if(mode == 1 && !pause) {
						map->generateSpaceshipBullet(window, 0);
					}
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code) {
					case sf::Keyboard::Up:
						move_spaceship = false;
						break;
					case sf::Keyboard::Down:
						move_spaceship = false;
						break;
				}
				break;
			}
		}
		

		if(mode == 1 && move_spaceship) {
			if(move_arrow == "up") {
				map->move_upSpaceship(0, window);
				//cerr << "Move Up Spaceship" << endl;
			}
			else {
				map->move_downSpaceship(0, window);
				//cerr << "Move Down Spaceship" << endl;
			}
		}
		//time = clock.getElapsedTime();
		//if(time.asMilliseconds() < 30) continue;
		//clock.restart();
		this_thread::sleep_for (std::chrono::milliseconds(6 * (5 - speed_of_game)));

		window.clear();
		window.draw(background_spr);
		time2 = clock.getElapsedTime();
		clock.restart();
		if(!pause)
			for(int i = 0; i < speed_of_game; ++i)
				time += time2;
		drawTime(time.asMilliseconds());
		drawSpeedGame();
		map->drawDetails(window);
		map->drawHeartDetailGulAlien(window);
		drawMap();
		window.display();
		if(!pause)
			map->check_Colision();
		if(is_done) return false;
		if(time.asMilliseconds() >= 120 * 1000) {
			map->remove_all();
			move_spaceship = false;
			return true;
		}

	}

}

void Graphics::draw_EndGame() {
	window.clear();
	sf::Texture background_tex;
	if(!background_tex.loadFromFile("Wallpaper2.png")) {
		cerr << "Backgrund of Menu can not be Loaded!" << endl;
		//return -1;
	}
	background_tex.setSmooth(true);
	sf::Sprite background_spr;
	background_spr.setTexture(background_tex);

	sf::Text end_text;
	end_text.setString("    Game Over! Press Enter to Exit!");
	end_text.setColor(sf::Color::Green);
	end_text.setFont(font);
	end_text.setCharacterSize(55);
	end_text.setPosition(sf::Vector2f(10 , window.getSize().y / 4));

	int score1 = map->getScore1();
	int score2;
	if(mode == 2) score2 = map->getScore2();
	string name1 = map->getName1(), name2;
	if(mode == 2) name2 = map->getName2();

	sf::Text score1_text;
	score1_text.setString("Score of " + name1 + ": " + to_string(score1));
	score1_text.setColor(sf::Color::White);
	score1_text.setFont(font);
	score1_text.setCharacterSize(30);
	score1_text.setPosition(sf::Vector2f(10 , window.getSize().y / 4 * 2));

	sf::Text score2_text;
	if(mode == 2) {
		score2_text.setString("Score of " + name2 + ": " + to_string(score2));
		score2_text.setColor(sf::Color::White);
		score2_text.setFont(font);
		score2_text.setCharacterSize(30);
		score2_text.setPosition(sf::Vector2f(window.getSize().x - 330 , window.getSize().y / 4 * 2));
	}

	sf::Text winner_text;
	if(mode == 2) {
		if(score1 > score2)
			winner_text.setString("Winner: " + name1);
		if(score2 > score1)
			winner_text.setString("Winner: " + name2);
		if(score1 == score2)
			winner_text.setString(name1 + " & " + name2 + " Are Equals!");
		winner_text.setColor(sf::Color::Blue);
		winner_text.setFont(font);
		winner_text.setCharacterSize(30);
		winner_text.setPosition(sf::Vector2f(window.getSize().x / 2 - 100 , window.getSize().y / 4 * 3));
	}

	while (window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				case sf::Keyboard::Up:
					
					break;
				case sf::Keyboard::Down:
					
					break;
				case sf::Keyboard::Return:
					window.close();
					break;
				}
				break;
			}
		}
		window.clear();
		window.draw(background_spr);
		window.draw(end_text);
		window.draw(score1_text);
		if (mode == 2) window.draw(score2_text);
		if (mode == 2) window.draw(winner_text);
		window.display();
	}
}
void Graphics::draw_NextLevel() {
	window.clear();
	sf::Texture background_tex;
	if(!background_tex.loadFromFile("Wallpaper2.png")) {
		cerr << "Backgrund of Menu can not be Loaded!" << endl;
		//return -1;
	}
	background_tex.setSmooth(true);
	sf::Sprite background_spr;
	background_spr.setTexture(background_tex);
	
	sf::Text nextlevel_text;
	nextlevel_text.setString("Nice! Press Enter to Start Next Level!");
	nextlevel_text.setColor(sf::Color::Green);
	nextlevel_text.setFont(font);
	nextlevel_text.setCharacterSize(55);
	nextlevel_text.setPosition(sf::Vector2f(10 , window.getSize().y / 4));

	bool is = false;
	
	while (!is && window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				case sf::Keyboard::Up:		
					break;
				case sf::Keyboard::Down:
					
					break;
				case sf::Keyboard::Return:
					is = true;
					break;
				}
				break;
			}
		}
		window.clear();
		window.draw(background_spr);
		window.draw(nextlevel_text);
		window.display();
	}
	return;
}
void Graphics::drawMap() {
	if(getLevel() == 1 || getLevel() == 3) {
		map->generateMeteor(window);
		map->drawMeteor(window);
		
		map->generateStar(window);
		map->drawStar(window);

		map->drawSpaceshipBullet(window);
	
	}
	if(getLevel() == 2 || getLevel() == 3) {
		map->generateSmallAlien(window);
		map->drawSmallAlien(window);

		map->generateBigAlien(window);
		map->drawBigAlien(window);

		map->drawSpaceshipBullet(window);
		map->drawAlienBullet(window);
	}
	if(getLevel() == 4) {
		map->drawSpaceshipBullet(window);
		map->drawAlienBullet(window);

		map->generateBigAlien(window);
		map->drawBigAlien(window);

		map->generateSmallAlien(window);
		map->drawSmallAlien(window);

		map->generateMeteor(window);
		map->drawMeteor(window);

		map->drawGulAlien(window);
	
	}
	if(getLevel() != 4) {
		map->generateHeart(window);
		map->drawHeart(window);
	}
	map->drawSpaceship(window);
}
void Graphics::drawTime(int t) {
	string str = to_string(t / 1000) + " : " + to_string(t % 1000);
	Time_text.setString(str);
	window.draw(Time_text);
}
void Graphics::drawSpeedGame() {
	string str = to_string(speed_of_game) + "X";
	Speed_text.setString(str);
	window.draw(Speed_text);	
}
void Graphics::drawAboutHow() {
	window.clear();
	sf::Texture background_tex;
	if(!background_tex.loadFromFile("HowAbout.png")) {
		cerr << "Backgrund of Details can not be Loaded!" << endl;
		//return -1;
	}
	background_tex.setSmooth(true);
	sf::Sprite background_spr;
	background_spr.setTexture(background_tex);
	
	bool is = false;
	
	while (!is && window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::KeyPressed :
				switch(event.key.code) {
				case sf::Keyboard::Up:		
					break;
				case sf::Keyboard::Down:
					
					break;
				case sf::Keyboard::Return:
					is = true;
					break;
				}
				break;
			}
		}
		window.clear();
		window.draw(background_spr);
		window.display();
	}

}

//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 3.  Spaceship : 
Spaceship::Spaceship(int i) {
	setID(i);
	setLive(5);
	setScore(0);
	
	if(!font.loadFromFile("arial.ttf")) {
		cerr << "Arial Font in Spaceship can not be Loaded!" << endl;
	}

	if(getID() == 1) {
		if(!Spaceship_tex.loadFromFile("Spaceship1.png")) {
			cerr << "Spaceship1.png can not be Loaded!" << endl;
			//return -1;
		}
	}
	else {
		if(!Spaceship_tex.loadFromFile("Spaceship2.png")) {
			cerr << "Spaceship2.png can not be Loaded!" << endl;
			//return -1;
		}	
	}
	Spaceship_tex.setSmooth(true);
	Spaceship_spr.setTexture(Spaceship_tex);

	if(!Score_tex.loadFromFile("ScoreIcon.png")) {
		cerr << "ScoreIcon.png could not be loaded!" << endl;
	}
	Score_tex.setSmooth(true);
	Score_spr.setTexture(Score_tex);

	if(!Live_tex.loadFromFile("LiveIcon.png")) {
		cerr << "LiveIcon.png could not be loaded!" << endl;
	}
	Live_tex.setSmooth(true);
	Live_spr.setTexture(Live_tex);


	Score_text.setColor(sf::Color::Yellow);
	Score_text.setFont(font);
	Score_text.setCharacterSize(25);
		
	Live_text.setColor(sf::Color::Yellow);
	Live_text.setFont(font);
	Live_text.setCharacterSize(25);

	clock.restart();
	time = clock.getElapsedTime() + sf::milliseconds(100);
}
Spaceship::~Spaceship() {

}
int Spaceship::getSizeX() const {
	return sizeX;
}
void Spaceship::setSizeX(int x) {
	sizeX = x;
}
int Spaceship::getSizeY() const {
	return sizeY;
}
void Spaceship::setSizeY(int y) {
	sizeY =	y;
}
int Spaceship::getX() const {
	return X;
}
void Spaceship::setX(int x) {
	X = x;
}
int Spaceship::getY() const {
	return Y;
}
void Spaceship::setY(int y) {
	Y = y;
}
int Spaceship::getVx() const {
	return Vx;
}
void Spaceship::setVx(int vx) {
	Vx = vx;
}
int Spaceship::getVy() const {
	return Vy;
}
void Spaceship::setVy(int vy) {
	Vy = vy;
}
sf::Sprite & Spaceship::getSpr() {
	return Spaceship_spr;
}
sf::Texture & Spaceship::getTex() {
	return Spaceship_tex;
}
void Spaceship::updateSpr() {
 	Spaceship_spr.setPosition(getX(), getY());
}
void Spaceship::move() {
	if(getX() + getSizeX() + getVx() > 960) return;
	if(getX() + getVx() < 0) return;
	if(getY() + getSizeY() + getVy() > 540) return;
	if(getY() + getVy() < 0) return;
	
	setX(getX() + getVx());
	setY(getY() + getVy());
	updateSpr();
}
bool Spaceship::isInside(sf::RenderWindow &window) {
	if(getX() + getVx() > window.getSize().x) return false;
	if(getY() + getVy() > window.getSize().y) return false;
	if(getX() + getVx() + getSizeX() < 0) return false;
	if(getY() + getVx() + getSizeY() < 0) return false;
	return true;
}
bool Spaceship::isInside(Spaceship * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}
string Spaceship::getMode() const {
	if(mode == 0) return "auto";
	else return "keyboard";
}
void Spaceship::setMode(string s) {
	if(s == "auto") mode = 0;
	else mode = 1;
}
int Spaceship::getID() const {
	return id;
}
void Spaceship::setID(int i) {
	id = i;
}
int Spaceship::getLive() const {
	return live;
}
void Spaceship::setLive(int l) {
	live = l;
	Live_text.setString(to_string(live));
}
int Spaceship::getScore() const {
	return score;
}
void Spaceship::setScore(int h) {
	score = h;
	Score_text.setString(to_string(h));
}
string Spaceship::getName() const {
	return name;
}
void Spaceship::setName(string str, sf::RenderWindow &window) {
	int tmp = 75;
	name = str;
	name_text.setString(name);
	name_text.setColor(sf::Color::Yellow);
	name_text.setFont(font);
	name_text.setCharacterSize(25);
	if(getID() == 1) {
		name_text.setPosition(sf::Vector2f(5, 5));
		Score_spr.setPosition(100, 5);
		Score_text.setPosition(sf::Vector2f(130,5));
		Live_spr.setPosition(200, 5);
		Live_text.setPosition(sf::Vector2f(230,5));
	}
	else {
		name_text.setPosition(sf::Vector2f(window.getSize().x - 350 + tmp , 5));
		Score_spr.setPosition(window.getSize().x - 250 + tmp, 5);
		Score_text.setPosition(sf::Vector2f(window.getSize().x - 220 + tmp,5));
		Live_spr.setPosition(window.getSize().x - 150 + tmp, 5);
		Live_text.setPosition(sf::Vector2f(window.getSize().x - 120 + tmp, 5));
	}
}
sf::Text & Spaceship::getText() {
	return name_text;
}
sf::Text & Spaceship::getScoreText() {
	return Score_text;
}
sf::Text & Spaceship::getLiveText() {
	return Live_text;
}
sf::Sprite & Spaceship::getLiveIconSpr() {
	return Live_spr;
}
sf::Sprite & Spaceship::getScoreIconSpr() {
	return Score_spr;
}
bool Spaceship::movable(sf::RenderWindow &window) {
	if(getX() + getSizeX() + getVx() > window.getSize().x) return false;
	if(getY() + getSizeY() + getVy() > window.getSize().y) return false;
	if(getX() + getVx() < 0) return false;
	if(getY() + getVy() < 0) return false;
	return true;	
}
//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 4.  SpaceshipBullet :
SpaceshipBullet::SpaceshipBullet() {
	if(!SpaceshipBullet_tex.loadFromFile("SpaceshipBullet.png")) {
		cerr << "SpaceshipBullet.png can not be Loaded!" << endl;
		//return -1;
	}
	SpaceshipBullet_tex.setSmooth(true);
	SpaceshipBullet_spr.setTexture(SpaceshipBullet_tex);
}
SpaceshipBullet::~SpaceshipBullet() {

}
int SpaceshipBullet::getSizeX() const {
	return sizeX;
}
void SpaceshipBullet::setSizeX(int x) {
	sizeX = x;
}
int SpaceshipBullet::getSizeY() const {
	return sizeY;
}
void SpaceshipBullet::setSizeY(int y) {
	sizeY =	y;
}
int SpaceshipBullet::getX() const {
	return X;
}
void SpaceshipBullet::setX(int x) {
	X = x;
}
int SpaceshipBullet::getY() const {
	return Y;
}
void SpaceshipBullet::setY(int y) {
	Y = y;
}
int SpaceshipBullet::getVx() const {
	return Vx;
}
void SpaceshipBullet::setVx(int vx) {
	Vx = vx;
}
int SpaceshipBullet::getVy() const {
	return Vy;
}
void SpaceshipBullet::setVy(int vy) {
	Vy = vy;
}
sf::Sprite & SpaceshipBullet::getSpr() {
	return SpaceshipBullet_spr;
}
sf::Texture & SpaceshipBullet::getTex() {
	return SpaceshipBullet_tex;
}
void SpaceshipBullet::updateSpr() {
 	SpaceshipBullet_spr.setPosition(getX(), getY());
}
void SpaceshipBullet::move() {
	setX(getX() + getVx());
	setY(getY() + getVy());
	updateSpr();
}
bool SpaceshipBullet::isInside(sf::RenderWindow &window) {
	if(getX() > window.getSize().x) return false;
	if(getY() > window.getSize().y) return false;
	if(getX() + getSizeX() < 0) return false;
	if(getY() + getSizeY() < 0) return false;
	return true;
}
int SpaceshipBullet::getSpaceship() const {
	return id;
}
void SpaceshipBullet::setSpaceship(int t) {
	id = t;
}
	
//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 5.  AlienBullet :
AlienBullet::AlienBullet() {
	if(!AlienBullet_tex.loadFromFile("AlienBullet.png")) {
		cerr << "AlienBullet.png can not be Loaded!" << endl;
		//return -1;
	}
	AlienBullet_tex.setSmooth(true);
	AlienBullet_spr.setTexture(AlienBullet_tex);
}
AlienBullet::~AlienBullet() {

}
int AlienBullet::getSizeX() const {
	return sizeX;
}
void AlienBullet::setSizeX(int x) {
	sizeX = x;
}
int AlienBullet::getSizeY() const {
	return sizeY;
}
void AlienBullet::setSizeY(int y) {
	sizeY =	y;
}
int AlienBullet::getX() const {
	return X;
}
void AlienBullet::setX(int x) {
	X = x;
}
int AlienBullet::getY() const {
	return Y;
}
void AlienBullet::setY(int y) {
	Y = y;
}
int AlienBullet::getVx() const {
	return Vx;
}
void AlienBullet::setVx(int vx) {
	Vx = vx;
}
int AlienBullet::getVy() const {
	return Vy;
}
void AlienBullet::setVy(int vy) {
	Vy = vy;
}
sf::Sprite & AlienBullet::getSpr() {
	return AlienBullet_spr;
}
sf::Texture & AlienBullet::getTex() {
	return AlienBullet_tex;
}
void AlienBullet::updateSpr() {
 	AlienBullet_spr.setPosition(getX(), getY());
}
void AlienBullet::move() {
	setX(getX() + getVx());
	setY(getY() + getVy());
	updateSpr();
}
bool AlienBullet::isInside(sf::RenderWindow &window) {
	if(getX() > window.getSize().x) return false;
	if(getY() > window.getSize().y) return false;
	if(getX() + getSizeX() < 0) return false;
	if(getY() + getSizeY() < 0) return false;
	return true;
}
bool AlienBullet::isInside(Spaceship * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}
	
//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 6.  Star :
Star::Star() {
	if(!Star_tex.loadFromFile("Star1.png")) {
		cerr << "Star1.png can not be Loaded!" << endl;
		//return -1;
	}
	Star_tex.setSmooth(true);
	Star_spr.setTexture(Star_tex);
}
Star::~Star() {

}
int Star::getSizeX() const {
	return sizeX;
}
void Star::setSizeX(int x) {
	sizeX = x;
}
int Star::getSizeY() const {
	return sizeY;
}
void Star::setSizeY(int y) {
	sizeY = y;
}
int Star::getX() const {
	return X;
}
void Star::setX(int x) {
	X = x;
}
int Star::getY() const {
	return Y;
}
void Star::setY(int y) {
	Y = y;
}
int Star::getVx() const {
	return Vx;
}
void Star::setVx(int vx) {
	Vx = vx;
}
int Star::getVy() const {
	return Vy;
}
void Star::setVy(int vy) {
	Vy = vy;
}
sf::Sprite & Star::getSpr() {
	return Star_spr;
}
sf::Texture & Star::getTex() {
	return Star_tex;
}
void Star::updateSpr() {
	Star_spr.setPosition(getX(), getY());
}
void Star::move() {
	setX(getX() + getVx());
	setY(getY() + getVy());
	updateSpr();
}
bool Star::isInside(sf::RenderWindow &window) {
	if(getX() > window.getSize().x) return false;
	if(getY() > window.getSize().y) return false;
	if(getX() + getSizeX() < 0) return false;
	if(getY() + getSizeY() < 0) return false;
	return true;
}
bool Star::isInside(Spaceship * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 7.  SmallAlien :
SmallAlien::SmallAlien() {
	if(!SmallAlien_tex.loadFromFile("SmallAlien.png")) {
		cerr << "SmallAlien.png can not be Loaded!" << endl;
		//return -1;
	}
	SmallAlien_tex.setSmooth(true);
	SmallAlien_spr.setTexture(SmallAlien_tex);

	clock.restart();
	time = clock.getElapsedTime() + sf::milliseconds(2900);
}
SmallAlien::~SmallAlien() {

}
int SmallAlien::getSizeX() const {
	return sizeX;
}
void SmallAlien::setSizeX(int x) {
	sizeX = x;
}
int SmallAlien::getSizeY() const {
	return sizeY;
}
void SmallAlien::setSizeY(int y) {
	sizeY = y;
}
int SmallAlien::getX() const {
	return X;
}
void SmallAlien::setX(int x) {
	X = x;
}
int SmallAlien::getY() const {
	return Y;
}
void SmallAlien::setY(int y) {
	Y = y;
}
int SmallAlien::getVx() const {
	return Vx;
}
void SmallAlien::setVx(int vx) {
	Vx = vx;
}
int SmallAlien::getVy() const {
	return Vy;
}
void SmallAlien::setVy(int vy) {
	Vy = vy;
}
sf::Sprite & SmallAlien::getSpr() {
	return SmallAlien_spr;
}
sf::Texture & SmallAlien::getTex() {
	return SmallAlien_tex;
}
void SmallAlien::updateSpr() {
	SmallAlien_spr.setPosition(getX(), getY());
}
void SmallAlien::move() {
	setX(getX() + getVx());
	setY(getY() + getVy());
	updateSpr();
}
bool SmallAlien::isInside(sf::RenderWindow &window) {
	if(getX() > window.getSize().x) return false;
	if(getY() > window.getSize().y) return false;
	if(getX() + getSizeX() < 0) return false;
	if(getY() + getSizeY() < 0) return false;
	return true;
}
bool SmallAlien::isInside(Spaceship * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}
bool SmallAlien::isInside(SpaceshipBullet * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}


//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 8.  BigAlien :
BigAlien::BigAlien() {
	if(!BigAlien_tex.loadFromFile("BigAlien.png")) {
		cerr << "BigAlien.png can not be Loaded!" << endl;
		//return -1;
	}
	BigAlien_tex.setSmooth(true);
	BigAlien_spr.setTexture(BigAlien_tex);
}
BigAlien::~BigAlien() {

}
int BigAlien::getSizeX() const {
	return sizeX;
}
void BigAlien::setSizeX(int x) {
	sizeX = x;
}
int BigAlien::getSizeY() const {
	return sizeY;
}
void BigAlien::setSizeY(int y) {
	sizeY = y;
}
int BigAlien::getX() const {
	return X;
}
void BigAlien::setX(int x) {
	X = x;
}
int BigAlien::getY() const {
	return Y;
}
void BigAlien::setY(int y) {
	Y = y;
}
int BigAlien::getVx() const {
	return Vx;
}
void BigAlien::setVx(int vx) {
	Vx = vx;
}
int BigAlien::getVy() const {
	return Vy;
}
void BigAlien::setVy(int vy) {
	Vy = vy;
}
sf::Sprite & BigAlien::getSpr() {
	return BigAlien_spr;
}
sf::Texture & BigAlien::getTex() {
	return BigAlien_tex;
}
void BigAlien::updateSpr() {
	BigAlien_spr.setPosition(getX(), getY());
}
void BigAlien::move() {
	setX(getX() + getVx());
	setY(getY() + getVy());
	updateSpr();
}
bool BigAlien::isInside(sf::RenderWindow &window) {
	if(getX() > window.getSize().x) return false;
	if(getY() > window.getSize().y) return false;
	if(getX() + getSizeX() < 0) return false;
	if(getY() + getSizeY() < 0) return false;
	return true;
}
bool BigAlien::isInside(Spaceship * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}
bool BigAlien::isInside(SpaceshipBullet * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}
bool BigAlien::movable(sf::RenderWindow &window) {
	//if(getX() + getSizeX() + getVx() > window.getSize().x) return false;
	if(getY() + getSizeY() + getVy() > window.getSize().y) return false;
	//if(getX() + getVx() < 0) return false;
	if(getY() + getVy() < 0) return false;
	return true;	
}

//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 9.  GulAlien :
GulAlien::GulAlien() {
	if(!GulAlien_tex.loadFromFile("GulAlien.png")) {
		cerr << "GulAlien.png can not be Loaded!" << endl;
		//return -1;
	}
	GulAlien_tex.setSmooth(true);
	GulAlien_spr.setTexture(GulAlien_tex);
	setLive(10);


	if(!font.loadFromFile("arial.ttf")) {
		cerr << "Arial Font in GulAlien can not be Loaded!" << endl;
	}

	live_text.setColor(sf::Color::Yellow);
	live_text.setFont(font);
	live_text.setCharacterSize(25);
	live_text.setPosition(sf::Vector2f(960 /*window.getSize().x*/ - 220 - 125,5));
}
GulAlien::~GulAlien() {

}
int GulAlien::getSizeX() const {
	return sizeX;
}
void GulAlien::setSizeX(int x) {
	sizeX = x;
}
int GulAlien::getSizeY() const {
	return sizeY;
}
void GulAlien::setSizeY(int y) {
	sizeY = y;
}
int GulAlien::getX() const {
	return X;
}
void GulAlien::setX(int x) {
	X = x;
}
int GulAlien::getY() const {
	return Y;
}
void GulAlien::setY(int y) {
	Y = y;
}
int GulAlien::getVx() const {
	return Vx;
}
void GulAlien::setVx(int vx) {
	Vx = vx;
}
int GulAlien::getVy() const {
	return Vy;
}
void GulAlien::setVy(int vy) {
	Vy = vy;
}
sf::Sprite & GulAlien::getSpr() {
	return GulAlien_spr;
}
sf::Texture & GulAlien::getTex() {
	return GulAlien_tex;
}
void GulAlien::updateSpr() {
	GulAlien_spr.setPosition(getX(), getY());
}
void GulAlien::move() {
	setX(getX() + getVx());
	setY(getY() + getVy());
	updateSpr();
}
bool GulAlien::isInside(sf::RenderWindow &window) {
	if(getX() > window.getSize().x) return false;
	if(getY() > window.getSize().y) return false;
	if(getX() + getSizeX() < 0) return false;
	if(getY() + getSizeY() < 0) return false;
	return true;
}
bool GulAlien::isInside(Spaceship * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}
bool GulAlien::isInside(SpaceshipBullet * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}
bool GulAlien::movable(sf::RenderWindow &window) {
	//if(getX() + getSizeX() + getVx() > window.getSize().x) return false;
	if(getY() + getSizeY() + getVy() > window.getSize().y) return false;
	//if(getX() + getVx() < 0) return false;
	if(getY() + getVy() < 0) return false;
	return true;	
}
int GulAlien::getLive() const {
	return live;
}
void GulAlien::setLive(int h) {
	live = h;
}
sf::Text &GulAlien::getText() {
	live_text.setString("Health of Gul Alien: " + to_string(getLive() * 10) + " / 100");
	return live_text;
}
	
//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 10.  Heart :
Heart::Heart() {
	if(!Heart_tex.loadFromFile("Heart1.png")) {
		cerr << "Heart1.png can not be Loaded!" << endl;
		//return -1;
	}
	Heart_tex.setSmooth(true);
	Heart_spr.setTexture(Heart_tex);
}
Heart::~Heart() {

}
int Heart::getSizeX() const {
	return sizeX;
}
void Heart::setSizeX(int x) {
	sizeX = x;
}
int Heart::getSizeY() const {
	return sizeY;
}
void Heart::setSizeY(int y) {
	sizeY = y;
}
int Heart::getX() const {
	return X;
}
void Heart::setX(int x) {
	X = x;
}
int Heart::getY() const {
	return Y;
}
void Heart::setY(int y) {
	Y = y;
}
int Heart::getVx() const {
	return Vx;
}
void Heart::setVx(int vx) {
	Vx = vx;
}
int Heart::getVy() const {
	return Vy;
}
void Heart::setVy(int vy) {
	Vy = vy;
}
sf::Sprite & Heart::getSpr() {
	return Heart_spr;
}
sf::Texture & Heart::getTex() {
	return Heart_tex;
}
void Heart::updateSpr() {
	Heart_spr.setPosition(getX(), getY());
}
void Heart::move() {
	setX(getX() + getVx());
	setY(getY() + getVy());
	updateSpr();
}
bool Heart::isInside(sf::RenderWindow &window) {
	if(getX() > window.getSize().x) return false;
	if(getY() > window.getSize().y) return false;
	if(getX() + getSizeX() < 0) return false;
	if(getY() + getSizeY() < 0) return false;
	return true;
}
bool Heart::isInside(Spaceship * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}

//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 11.  Meteor :
Meteor::Meteor() {
	if(!Meteor_tex.loadFromFile("Meteor1.png")) {
		cerr << "Meteor1.png can not be Loaded!" << endl;
		//return -1;
	}
	Meteor_tex.setSmooth(true);
	Meteor_spr.setTexture(Meteor_tex);
}
Meteor::~Meteor() {

}
int Meteor::getSizeX() const {
	return sizeX;
}
void Meteor::setSizeX(int x) {
	sizeX = x;
}
int Meteor::getSizeY() const {
	return sizeY;
}
void Meteor::setSizeY(int y) {
	sizeY = y;
}
int Meteor::getX() const {
	return X;
}
void Meteor::setX(int x) {
	X = x;
}
int Meteor::getY() const {
	return Y;
}
void Meteor::setY(int y) {
	Y = y;
}
int Meteor::getVx() const {
	return Vx;
}
void Meteor::setVx(int vx) {
	Vx = vx;
}
int Meteor::getVy() const {
	return Vy;
}
void Meteor::setVy(int vy) {
	Vy = vy;
}
sf::Sprite & Meteor::getSpr() {
	return Meteor_spr;
}
sf::Texture & Meteor::getTex() {
	return Meteor_tex;
}
void Meteor::updateSpr() {
	Meteor_spr.setPosition(getX(), getY());
}
void Meteor::move() {
	setX(getX() + getVx());
	setY(getY() + getVy());
	updateSpr();
}
bool Meteor::isInside(sf::RenderWindow &window) {
	if(getX() > window.getSize().x) return false;
	if(getY() > window.getSize().y) return false;
	if(getX() + getSizeX() < 0) return false;
	if(getY() + getSizeY() < 0) return false;
	return true;
}
bool Meteor::isInside(Spaceship * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}
bool Meteor::isInside(SpaceshipBullet * sps) {
	if(sps->getX() >= getX() + getSizeX() ) return false;
	if(sps->getX() + sps->getSizeX() <= getX()) return false;
	if(sps->getY() >= getY() + getSizeY() ) return false;
	if(sps->getY() + sps->getSizeY() <= getY()) return false;
	return true;
}
//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Area 12. Menu
Menu::Menu(int x, int y) :
MAX_ITEM(4)
{	
	if(!font.loadFromFile("arial.ttf")) {
		cerr << "Arial Font in Menu can not be Loaded!" << endl;
	}
	setSizeX(x);
	setSizeY(y);
	
	SelectedItem = 0;
	button = new sf::Text[MAX_ITEM];

	button[0].setString("Start 1 Player");
	button[0].setColor(sf::Color::Green);
	button[0].setFont(font);
	//button[0].setSize(getSizeX() / 5);
	button[0].setPosition(sf::Vector2f(getSizeX() / 2 - getSizeX() / 10, getSizeY() / (MAX_ITEM + 1) * 1));

	button[1].setString("Start 2 Player");
	button[1].setColor(sf::Color::Red);
	button[1].setFont(font);
	//button[1].setSize(getSizeX() / 5);
	button[1].setPosition(sf::Vector2f(getSizeX() / 2 - getSizeX() / 10, getSizeY() / (MAX_ITEM + 1) * 2));

	button[2].setString("How to Play & About");
	button[2].setColor(sf::Color::Red);
	button[2].setFont(font);
	//button[2].setSize(getSizeX() / 5);
	button[2].setPosition(sf::Vector2f(getSizeX() / 2 - getSizeX() / 10 , getSizeY() / (MAX_ITEM + 1) * 3));

	button[3].setString(".: Exit :.");
	button[3].setColor(sf::Color::Red);
	button[3].setFont(font);
	//button[3].setSize(getSizeX() / 5);
	button[3].setPosition(sf::Vector2f(getSizeX() / 2 - getSizeX() / 10 , getSizeY() / (MAX_ITEM + 1) * 4));

}
Menu::~Menu() {

}
void Menu::draw(sf::RenderWindow &window) {
	for(int i = 0; i < MAX_ITEM; ++i) {
		window.draw(button[i]);
	}
}
void Menu::move_up() {
	if(SelectedItem != 0) {
		button[SelectedItem].setColor(sf::Color::Red);
		SelectedItem--;
		button[SelectedItem].setColor(sf::Color::Green);
	}
}
void Menu::move_down() {
	if(SelectedItem != MAX_ITEM - 1) {
		button[SelectedItem].setColor(sf::Color::Red);
		SelectedItem++;
		button[SelectedItem].setColor(sf::Color::Green);
	}
}
int Menu::getSizeX() const {
	return sizeX;
}
void Menu::setSizeX(int x) {
	sizeX = x;
}
int Menu::getSizeY() const {
	return sizeY;
}
void Menu::setSizeY(int y) {
	sizeY = y;
}
int Menu::getPressedItemID() const {
	return SelectedItem;
}
//---------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------------------------
// Area 


//---------------------------------------------------------------------------------------------------------------------------------------
