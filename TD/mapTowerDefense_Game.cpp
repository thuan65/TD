#include "mapTowerDefense_Game.h"

/*
To do
set a new path for map matrix logic
set the new start and end point for pathfinder

*/


mapTowerDefense_Game::mapTowerDefense_Game(const std::vector<sf::Texture>& rMap_GameTexture)
	: Map_GameTexture(rMap_GameTexture), startPos({ 3,0,0 }), endDes({ 8 , 15 ,0 }), Map_GameSprite(Map_GameTexture[0]) //set cho khung hinh dau tien
{//The default of the startPos and endDes will be the matrix of the first map
	//makeMap_GameData();

	// Tính toán đường đi ban đầu
	//PathFinder::findPath(_Map_Game_Logic);
}

// -1 là tường, 0 là trống

bool mapTowerDefense_Game::ReadFile(std::string fileName) {
	std::ifstream fin(fileName);
	if (fin.fail()) {
		throw std::runtime_error("Cannot read Map_Game logic matrix");//Put throw catch here
		return false;
	}

	int row, col;
	fin >> row >> col;

	_Map_Game_Logic.resize(row, std::vector<point>(col));
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			int c;
			fin >> c;
			_Map_Game_Logic[i][j].setC(c);
		}
	}
	fin.close();

	fin.open(filePathForStartEndPosition);//Read the start and end of the walking path
	if (fin.fail()) {
		throw std::runtime_error("Cannot Read Start/End Path");
	}
	fin >> startPos >> endDes;
	fin.close();
	return true;
}

void mapTowerDefense_Game::setFilePath(const std::string& rfilePath) {
	filePathForMatrixLogic = rfilePath;
}

void mapTowerDefense_Game::setFilePathForStartEnd(const std::string& rfilePath) {
	filePathForStartEndPosition = rfilePath;
}

void mapTowerDefense_Game::reset() {
	// Reset the map to the original state

	makeMap_GameData();
	PathFinder::findPath(_Map_Game_Logic);//Find a new path
	currentFrame = 0; // Reset animation frame
	timeSinceLastFrame = 0.0F; // Reset animation timer
}

void mapTowerDefense_Game::makeMap_GameData() {

	setTotalFrame(Map_GameTexture.size());//Set the total frame for animation
	ReadFile(filePathForMatrixLogic);
	PathFinder::setStart(startPos); PathFinder::setEnd(endDes);
}



void mapTowerDefense_Game::Update(float deltaTime)
{
	animate(deltaTime);
}

void mapTowerDefense_Game::animate(float deltaTime)
{
	timeSinceLastFrame += deltaTime;

	if (timeSinceLastFrame >= frameTime) {
		currentFrame = (currentFrame + 1) % totalFrame;
		timeSinceLastFrame = 0.0F;
	}

}

void mapTowerDefense_Game::draw(sf::RenderWindow& window) {
	Map_GameSprite.setTexture(Map_GameTexture[currentFrame]);//set khung hinh
	window.draw(Map_GameSprite);
}

void mapTowerDefense_Game::setTexture(const std::vector<sf::Texture>& rMap_GameTexture) {
	Map_GameTexture = rMap_GameTexture;
	Map_GameSprite.setTexture(Map_GameTexture[0]);
}

//for (int i = 0; i < point::Map_Game_SIZE; i++) {
//	for (int j = 0; j < point::Map_Game_SIZE; j++) {
//		tool::GotoXY(_m[i][j].getX(), _m[i][j].getY());//Đưa con trỏ vẻ (cái nhập ký tự) tới vị trí tương ứng
//		if (_m[i][j].getC() == -1) cout << '+';
//		else if (_m[i][j].getC() == -2) cout << 'U';
//	}
//}

//tool::GotoXY(_tw.getLocation().getX(), _tw.getLocation().getY());
//cout << "T";