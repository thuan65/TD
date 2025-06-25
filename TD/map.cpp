#include "map.h"



map::map() {
	/*resetMapData();*/
	makeMapData();
}

// -1 là tường, 0 là trống, 1 là tower
//void map::resetMapData() {
//	for (int i = 0; i < point::MAP_SIZE; i++) {
//		for (int j = 0; j < point::MAP_SIZE; j++) {
//			_m[i][j] = { 4 * j + point::LEFT + 2, 2 * i + point::TOP + 1, -1 };
//		}//Set tất cả thành tường
//	}
//}

bool map::ReadFile(std::string fileName) {
	std::ifstream fin(fileName);
	if (fin.fail()) {
		std::cout << "Cannot read Map";//Put throw catch here
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

void map::LoadTexture() {
	for (int i = 0; i < totalFrame; ++i) {
		sf::Texture tmpmapTexture;
		if (tmpmapTexture.loadFromFile("Pic\\4map\\Texture\\map1_Frame" + std::to_string(i) + ".png") == false) {
			std::cout << "Erorr loading map frame!";
			return;
		}
		mapTexture.push_back(tmpmapTexture);
	}
}

void map::makeMapData() {

	setTotalFrame(2); // For now it is 1 frame
	ReadFile("Pic\\4map\\Logic\\Map1.txt");
	LoadTexture();
	mapSprite.emplace_back(mapTexture[0]);//set cho khung hinh dau tien




	//_e.findPath(_m, _e.getStart(), _e.getEnd());

}



void map::Update(float deltaTime)
{
	animate(deltaTime);
}

void map::animate(float deltaTime)
{
	timeSinceLastFrame += deltaTime;

	if (timeSinceLastFrame >= frameTime) {
		currentFrame = (currentFrame + 1) % totalFrame;
		timeSinceLastFrame = 0.0F;
	}

}

void map::drawMap(sf::RenderWindow& window) {
	mapSprite[0].setTexture(mapTexture[currentFrame]);//set cho khung hinh dau tien
	window.draw(mapSprite[0]);
}

//_m[2][0].setC(0);  _m[2][1].setC(0); _m[2][2].setC(0); _m[2][3].setC(0);
//_m[2][7].setC(-2); _m[2][8].setC(-2);
//_m[3][1].setC(-2); _m[3][2].setC(-2); _m[3][3].setC(0);
//_m[3][4].setC(0); _m[3][5].setC(0); _m[3][6].setC(0);
//_m[3][7].setC(-2); _m[3][8].setC(-2);
//_m[4][1].setC(-2); _m[4][2].setC(-2); _m[4][6].setC(0);
//_m[4][7].setC(0); _m[4][8].setC(0);
//_m[5][8].setC(0);
//_m[5][6].setC(0);
//_m[6][5].setC(0);
//_m[6][8].setC(0);
//_m[7][3].setC(0); _m[7][4].setC(0); _m[7][5].setC(0); _m[7][6].setC(0);
//_m[7][7].setC(0); _m[7][8].setC(0);
//_m[8][1].setC(-2); _m[8][2].setC(-2); _m[8][3].setC(0);
//_m[9][1].setC(-2); _m[9][2].setC(-2); _m[9][3].setC(0);

//for (int i = 0; i < point::MAP_SIZE; i++) {
//	for (int j = 0; j < point::MAP_SIZE; j++) {
//		tool::GotoXY(_m[i][j].getX(), _m[i][j].getY());//Đưa con trỏ vẻ (cái nhập ký tự) tới vị trí tương ứng
//		if (_m[i][j].getC() == -1) cout << '+';
//		else if (_m[i][j].getC() == -2) cout << 'U';
//	}
//}

//tool::GotoXY(_tw.getLocation().getX(), _tw.getLocation().getY());
//cout << "T";