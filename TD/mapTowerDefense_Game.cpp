#include "mapTowerDefense_Game.h"



mapTowerDefense_Game::mapTowerDefense_Game(const std::vector<sf::Texture>& rMap_GameTexture)
	: Map_GameTexture(rMap_GameTexture), Map_GameSprite(Map_GameTexture[0]) //set cho khung hinh dau tien
{
	makeMap_GameData();
}

// -1 là tường, 0 là trống, 1 là tower

bool mapTowerDefense_Game::ReadFile(std::string fileName) {
	std::ifstream fin(fileName);
	if (fin.fail()) {
		std::cout << "Cannot read Map_Game logic matrix";//Put throw catch here
		return false;
	}

	int row, col;
	fin >> row >> col;

	_m.resize(row, std::vector<point>(col));
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			int c;
			fin >> c;
			_m[i][j].setC(c);
		}
	}
	fin.close();
	return true;
}

void mapTowerDefense_Game::makeMap_GameData() {

	setTotalFrame(Map_GameTexture.size()); // For now it is 1 frame
	ReadFile("Data\\4map\\Logic\\Map1.txt");;
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
	Map_GameSprite.setTexture(Map_GameTexture[currentFrame]);//set cho khung hinh dau tien
	window.draw(Map_GameSprite);
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