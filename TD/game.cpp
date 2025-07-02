#include "game.h"



//game::game(){
//	_ISEXIT1 = _ISEXIT2 = false;
//}
//
//void game::startGame() {
//	system("cls");
//
//}

game::game()
	:window(sf::VideoMode({ 540, 360 }), "GAME"), gameMap(Resource_Management::getTexture("Map_Game1"))
{
	vector<vector<point>> _Map_GameLogic = gameMap.getMap_Game(); //Put all of this in mapTowerDefense_Game
	point s = { 1,0,0 }, e = { 8 , 15 ,0 };//All of this
	PathFinder::setStart(s); PathFinder::setEnd(e);//All of this
	PathFinder::findPath(_Map_GameLogic);//All of this

}

game::~game()
{
}

void game::Run() {
	////////////////////////All of this will be put in mapTowerDefense_Game to deal with this
	vector<vector<point>> _Map_GameLogic = gameMap.getMap_Game();
	WaveManager wave1;
	TowerManager towerControl;
	////////////////////////
	
	wave1.startNewWave();
	sf::Clock clock;//Đồng hồ để đếm thời gian (dùng để nhận biết giữa các frame)
	while (window.isOpen()) {

		if (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {//check if left mouse button click 
			wave1.startNewWave();//Click chuột trái khi wave hết để sang wave kế

			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f ReadlCord = window.mapPixelToCoords(pixelPos);
			int row = ReadlCord.y / point::TileSize;
			int col = ReadlCord.x / point::TileSize;

			if (row >= 0 && row < _Map_GameLogic.size() && col >= 0 && col < _Map_GameLogic[0].size()) {
				//std::cout << "Row: " << row << " " << "Col: " << col << "\n";
				if (_Map_GameLogic[row][col].getC() == point::Empty_Tile) {
					towerControl.buildTower(row, col);
					
				}
			}

		}

		gameMap.Update(deltaTime);
		wave1.update(deltaTime);

		window.clear();
		gameMap.draw(window);
		towerControl.draw(window);
		wave1.draw(window);
		window.display();

	}
}
