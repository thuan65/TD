#include "game.h"
#include "WaveManager.h"
#include "TowerManager.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Resource_Management.h"
#include "PathFinder.h"
#include <thread>
#include <iostream>

//void ThreadFunc2(game&);
//void ThreadFunc1(game&);

float Vector_Length(sf::Vector2f rVector) {
	return sqrt(rVector.x * rVector.x + rVector.y * rVector.y);
}



int main() {

	game cg;
	cg.Run();

	return 0;
}

//////////////////////This is how we deal with mouse//////////////////
//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
	//	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	//	sf::Vector2f ReadlCord = window.Map_GamePixelToCoords(pixelPos);
	//	int row = ReadlCord.y / point::TileSize;
	//	int col = ReadlCord.x / point::TileSize;
	// if (
	//	if (row >= 0 && row < _Map_GameLogic.size() && col >= 0 && col < _Map_GameLogic[0].size()) {
	//		//std::cout << "Row: " << row << " " << "Col: " << col << "\n";
	//		if (_Map_GameLogic[row][col].getC() == -2) {
	//			tower1.setLocation({ col,row,0 });
	//		}
	//	}
	//}
//////////////////////This is how we deal with mouse//////////////////

//cin.get();
//tool::ShowConsoleCursor(false);
//game cg;
///*cg.startGame();*/
//
//enemy& EnemyS = cg.getMap_Game().getEnemy();
//point* p = EnemyS.getP();
//
//
//for (int i = 0; i < 25; i++) {
//	cout << p[i].getX() << " " << p[i].getY() << endl;
//}

//thread t1(ThreadFunc2, std::ref(cg));
//thread t2(ThreadFunc1, std::ref(cg));
//t1.join();
//t2.join();

//tool::GotoXY(0, 20);



//void ThreadFunc2(game& cg) {//Xử lý viên đạn
//	int i = 0;
//	enemy& e = cg.getMap_Game().getEnemy(); //Lấy con enemy ra
//	point _ENEMY;
//	bullet& b = cg.getMap_Game().getTower().getBullet(); //Lấy cái viên đạn ra
//
//	int _SPEED = b.getSpeed(), _NBULLET = b.getN();
//	point* _BULLET1_P = b.getP();
//	point _BULLET1 = b.getCurr();
//
//	while (!cg.getIsExist1()) {
//		tool::Draw((char*)"o", i, _BULLET1_P, _BULLET1);
//		b.setCurr(_BULLET1);
//		_ENEMY = e.getCurr();
//
//		if (_BULLET1.getX() == _ENEMY.getX() && _BULLET1.getY() == _ENEMY.getY()) {
//			tool::Draw((char*)" ", i, _BULLET1_P, _BULLET1);
//			cg.setIsExist1(true);
//			break;
//		}
//		else i++;
//		Sleep(1000 / _SPEED);
//		tool::Draw((char*)" ", i - 1, _BULLET1_P, _BULLET1);
//		if (i == _NBULLET)i = 0;
//
//	}
//	cg.setIsExist2(true);
//}

//void ThreadFunc1(game& cg) {//Xử lý enemy
//	int i = 0;
//	enemy& e = cg.getMap_Game().getEnemy();
//	point _ENEMY = e.getCurr(), _END = e.getEnd(); int SPEED = e.getSpeed();
//
//	point* _p = e.getP(); //Lấy cái Map_Game đi của con enemy
//	bullet& b = cg.getMap_Game().getTower().getBullet(); // Lấy viên đạn
//	point _BULLET1;
//
//	while (!cg.getIsExist1()) {
//		tool::Draw((char*)"K", i, _p, _ENEMY);
//		e.setCurr(_ENEMY);
//		_BULLET1 = b.getCurr();
//
//		if (_ENEMY.getX() == _END.getX() && _ENEMY.getY() == _END.getY()) {
//			break;
//		}
//		else if (_ENEMY.getX() == _BULLET1.getX() && _ENEMY.getY() == _BULLET1.getY()) {
//			tool::Draw((char*)" ", i, _p, _ENEMY);
//			break;
//		}
//		else i++;
//		Sleep(1000 / SPEED);
//		tool::Draw((char*)" ", i - 1, _p, _ENEMY);
//	}
//	cg.setIsExist1(true);
//}