#include "enemy.h"

//enemy::enemy() 
//{
//}

enemy::enemy(const std::vector<sf::Texture>& rTextures, const vector<sf::Vector2f>& _rpath)
	: textures(rTextures), Enemysprite(textures[0]), speed(30)//for now speed is 3
{
	totalFrame = rTextures.size();
	_path = _rpath;
	Enemysprite.setPosition(_path[currentWayPoint]);
	//Enemysprite[0].setOrigin({ 16, 16 });
}

void enemy::LoadTexture() {

}

void enemy::Update(float deltaTime)
{
	move(deltaTime);
	animate(deltaTime);
}

void enemy::draw(sf::RenderWindow& window)
{
	window.draw(Enemysprite);
}

void enemy::move(float deltaTime)
{
	//sf::Vector2f s = sprite[0].getPosition();
	//std::cout << s.x << " " << s.y << "\n";
	//std::cin.get();

	if (currentWayPoint >= _path.size()) return;

	sf::Vector2f currentPosition = Enemysprite.getPosition();
	sf::Vector2f TargetPosition = _path[currentWayPoint]; //The next point it need to go to

	sf::Vector2f direction = TargetPosition - currentPosition;

	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance > 1.0f) {
		direction /= distance;
		Enemysprite.move(direction * speed * deltaTime);
	}
	else {
		Enemysprite.setPosition(TargetPosition);
		currentWayPoint++;
	}
}

void enemy::animate(float deltaTime)
{
	timeSinceLastFrame += deltaTime;
	if (timeSinceLastFrame >= frameTime) {
		currentFrame = (currentFrame + 1) % totalFrame;
		
		Enemysprite.setTexture(textures[currentFrame]);
		timeSinceLastFrame = 0.0F;
	}
}