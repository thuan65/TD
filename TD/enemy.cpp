#include "enemy.h"

//Default constructer
enemy::enemy() {
	setTotalFrame(3);//3 frame for now
	LoadTexture();
	sprite.emplace_back(textures[0]);
	sprite[0].setScale({ 0.08, 0.08 });
	sprite[0].setOrigin({ 16, 16 });

	_speed = 3;
}

enemy::enemy(const vector<sf::Vector2f>& _rpath)
{
	_path = _rpath;
	setTotalFrame(3);//3 frame for now
	LoadTexture();
	sprite.emplace_back(textures[0]);
	sprite[0].setPosition(_path[currentWayPoint]);
	//sprite[0].setOrigin({ 16, 16 });
	
}

//enemy::enemy(point tstart, point tend, point tcurr) : enemy() {
//	_start = tstart;
//	_end = tend;
//	_curr = tcurr;
//}

void enemy::LoadTexture() {
	textures.resize(totalFrame);
	textures[0].loadFromFile("Pic\\3enemy\\MageSleame\\Mage Sleame1.png");
	textures[1].loadFromFile("Pic\\3enemy\\MageSleame\\Mage Sleame2.png");
	textures[2].loadFromFile("Pic\\3enemy\\MageSleame\\Mage Sleame3.png");
}

void enemy::Update(float deltaTime)
{
	move(deltaTime);
	animate(deltaTime);
}

void enemy::draw(sf::RenderWindow& window)
{
	window.draw(sprite[0]);
}

void enemy::move(float deltaTime)
{
	//sf::Vector2f s = sprite[0].getPosition();
	//std::cout << s.x << " " << s.y << "\n";
	//std::cin.get();

	if (currentWayPoint >= _path.size()) return;

	sf::Vector2f currentPosition = sprite[0].getPosition();
	sf::Vector2f TargetPosition = _path[currentWayPoint]; //The next point it need to go to

	sf::Vector2f direction = TargetPosition - currentPosition;

	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance > 1.0f) {
		direction /= distance;
		sprite[0].move(direction * speed * deltaTime);
	}
	else {
		sprite[0].setPosition(TargetPosition);
		currentWayPoint++;
	}
}

void enemy::animate(float deltaTime)
{
	timeSinceLastFrame += deltaTime;
	if (timeSinceLastFrame >= frameTime) {
		currentFrame = (currentFrame + 1) % totalFrame;
		
		sprite[0].setTexture(textures[currentFrame]);
		timeSinceLastFrame = 0.0F;
	}
}