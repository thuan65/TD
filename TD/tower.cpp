#include "tower.h"
tower::tower(const std::vector<sf::Texture>& rtowerTexture, int row, int col)
	: towerTexture(rtowerTexture), towerSprite(towerTexture[0])
{
	towerSprite.setPosition(sf::Vector2f(col * point::TileSize, row * point::TileSize));
}

void tower::draw(sf::RenderWindow& window)
{
	window.draw(towerSprite);
}

//void tower::setMap_GameForBullet(point a[][point::Map_Game_SIZE]) {//Update mapTowerDefense_Game dữa trên cái mapTowerDefense_Game mình tạo ra
//	for (int i = 0; i < point::Map_Game_SIZE; i++) {
//		for (int j = 0; j < point::Map_Game_SIZE; j++) {
//			_b.UpdateMap_Game(i, j, a[i][j]);//Cập nhật đường đi cho viên đạn
//		}
//	}
//}