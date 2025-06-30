#include "enemy.h"

//enemy::enemy() 
//{
//}

enemy::enemy(const std::vector<sf::Texture>& rTextures, const vector<sf::Vector2f>& _rpath, float rspeed)
	: textures(rTextures), Enemysprite(textures[0]), _speed(rspeed)
{
	totalFrame = rTextures.size();
	_path = _rpath;
	Enemysprite.setPosition(_path[currentWayPoint]);
	//Enemysprite.setOrigin({ 16, 16 });
}

void enemy::Update(float deltaTime, sf::RenderWindow& window)
{
	move(deltaTime);
	animate(deltaTime);
	draw(window);
}

void enemy::draw(sf::RenderWindow& window)
{
	window.draw(Enemysprite);
}

void enemy::move(float deltaTime)
{
	//This is for debug
	sf::Vector2f s = Enemysprite.getPosition();
	std::cout << s.x << " " << s.y << "\n";
	//std::cin.get();

	if (currentWayPoint >= _path.size()) return;

	sf::Vector2f currentPosition = Enemysprite.getPosition();
	sf::Vector2f TargetPosition = _path[currentWayPoint]; //The next point it need to go to

	sf::Vector2f direction = TargetPosition - currentPosition;

	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance > 1.0f) {
		direction /= distance;
		Enemysprite.move(direction * _speed * deltaTime);
	}
	else {
		Enemysprite.setPosition(TargetPosition);
		currentWayPoint++;
	}
}

void enemy::animate(float deltaTime)
{
	timeSinceLastFrame += deltaTime; //Thoi gian giua cac Frame
	if (timeSinceLastFrame >= frameTime) { //Neu du thoi gian chuyen frame
		currentFrame = (currentFrame + 1) % totalFrame; 
		
		Enemysprite.setTexture(textures[currentFrame]);//Dat frame ke tiep
		timeSinceLastFrame = 0.0F;
	}
}