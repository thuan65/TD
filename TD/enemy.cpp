#include "enemy.h"

enemy::enemy(const std::vector<sf::Texture>& rTextures, const vector<sf::Vector2f>& _rpath, int rMaxHealth, float rspeed, int rBounty) // thêm max_Health
	: textures(rTextures),
	Enemysprite(textures[0]),
	_speed(rspeed),
	maxHealth(rMaxHealth), // Khởi tạo máu tối đa
	_health(rMaxHealth), bounty(rBounty)    // Máu hiện tại bắt đầu bằng máu tối đa
{
	totalFrame = rTextures.size();
	_path = _rpath;
	if (!_path.empty()) {
		Enemysprite.setPosition(_path[0] - sf::Vector2f{ 32.0, 0.0 });//Sau sẽ có chỉnh sai số
	}

	// --- KHỞI TẠO THANH MÁU ---
	// Thanh nền (màu đỏ)
	healthBarBackground.setSize(sf::Vector2f(32.f, 5.f)); // Chiều dài 32, cao 5
	healthBarBackground.setFillColor(sf::Color::Red);

	// Thanh máu hiện tại (màu xanh)
	healthBarForeground.setSize(sf::Vector2f(32.f, 5.f));
	healthBarForeground.setFillColor(sf::Color::Green);
}

enemy::enemy(const std::vector<sf::Texture>& rTextures, const vector<sf::Vector2f>& _rpath, std::string enemyType, int rMaxHealth, float rspeed, int rBounty)
	: textures(rTextures),
Enemysprite(textures[0]),
enemyType(enemyType),
_speed(rspeed),
maxHealth(rMaxHealth), // Khởi tạo máu tối đa
_health(rMaxHealth), bounty(rBounty)    // Máu hiện tại bắt đầu bằng máu tối đa
{
	totalFrame = rTextures.size();
	_path = _rpath;
	if (!_path.empty()) {
		Enemysprite.setPosition(_path[0] - sf::Vector2f{ 32.0, 0.0 });//Sau sẽ có chỉnh sai số
	}

	// --- KHỞI TẠO THANH MÁU ---
	// Thanh nền (màu đỏ)
	healthBarBackground.setSize(sf::Vector2f(32.f, 5.f)); // Chiều dài 32, cao 5
	healthBarBackground.setFillColor(sf::Color::Red);

	// Thanh máu hiện tại (màu xanh)
	healthBarForeground.setSize(sf::Vector2f(32.f, 5.f));
	healthBarForeground.setFillColor(sf::Color::Green);
}

enemy::enemy(const std::vector<sf::Texture>& rTextures, const std::vector<sf::Texture>& hurt_texture, const std::vector<sf::Texture>& dead_texture, const vector<sf::Vector2f>& _rpath, int rMaxHealth, float rspeed, int rBounty)
	: textures(rTextures),
	Enemysprite(textures[0]),
	_speed(rspeed),
	maxHealth(rMaxHealth), // Khởi tạo máu tối đa
	_health(rMaxHealth), bounty(rBounty)    // Máu hiện tại bắt đầu bằng máu tối đa

{
	totalFrame = rTextures.size();
	_path = _rpath;
	if (!_path.empty()) {
		Enemysprite.setPosition(_path[0] - sf::Vector2f{ 32.0, 0.0 });//Sau sẽ có chỉnh sai số
	}

	// --- KHỞI TẠO THANH MÁU ---
	// Thanh nền (màu đỏ)
	healthBarBackground.setSize(sf::Vector2f(32.f, 5.f)); // Chiều dài 32, cao 5
	healthBarBackground.setFillColor(sf::Color::Red);

	// Thanh máu hiện tại (màu xanh)
	healthBarForeground.setSize(sf::Vector2f(32.f, 5.f));
	healthBarForeground.setFillColor(sf::Color::Green);
}

sf::Vector2f enemy::getPositionAfter(float time) {

	sf::Vector2f currentPosition = getPosition();
	int index = currentWayPoint;

	while (time > 0.0f && index + 1 < _path.size()) {
		sf::Vector2f nextPosition = _path[index + 1];//The next place that the enemy have to stay on
		sf::Vector2f deltaVector = nextPosition - currentPosition; //Vector huong tu diem A - B
		float distance = std::sqrt(deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y); //Cong thuc do dai vector la sqrt(a*a + b*b), to avoid sqrt Binh Phuong len

		if (distance == 0.0f) {
			++index;
			continue;
		}

		float timeToNextPosition = distance / _speed;

		if (time >= timeToNextPosition) {
			time -= timeToNextPosition;
			index++;
			currentPosition = nextPosition;
		}
		else {
			float ratio = time / timeToNextPosition;
			return currentPosition + deltaVector * ratio;
		}
	}
	return currentPosition;
}

void enemy::damageTake(int rdamage) {
	hurt();
	_health -= rdamage;
	if (_health < 0) {
		_health = 0;
	}

	// CẬP NHẬT CHIỀU DÀI THANH MÁU KHI NHẬN SÁT THƯƠNG
	float healthPercent = static_cast<float>(_health) / maxHealth;
	healthBarForeground.setSize(sf::Vector2f(32.f * healthPercent, 5.f));
}

bool enemy::isEnemyAlive() {
	if (_health <= 0) return false;
	return true;
}

void enemy::Update(float deltaTime) {
	move(deltaTime);
	animate(deltaTime);

	// CẬP NHẬT VỊ TRÍ THANH MÁU THEO VỊ TRÍ CỦA ENEMY
	// Đặt thanh máu ngay phía trên sprite của enemy
	sf::Vector2f enemyPos = Enemysprite.getPosition();

	// Update the code to use sf::Vector2f for setPosition to fix the error
	healthBarBackground.setPosition(sf::Vector2f(enemyPos.x, enemyPos.y - 10.f)); // -10.f để nó ở trên đầu
	healthBarForeground.setPosition(sf::Vector2f(enemyPos.x, enemyPos.y - 10.f));
}

void enemy::draw(sf::RenderWindow& window) {
	window.draw(Enemysprite);

	// VẼ CẢ THANH MÁU
	window.draw(healthBarBackground);
	window.draw(healthBarForeground);
}



bool enemy::reachedEnd() {
	if (Enemysprite.getPosition() == _path.back()) return true;
	return false;
}

void enemy::move(float deltaTime) {
	//This is for debug
	//sf::Vector2f s = Enemysprite.getPosition();
	//std::cout << s.x << " " << s.y << "\n";
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

void enemy::animate(float deltaTime) {
	timeSinceLastFrame += deltaTime; //Thoi gian giua cac Frame
	if (timeSinceLastFrame >= frameTime) { //Neu du thoi gian chuyen frame
		currentFrame = (currentFrame + 1) % totalFrame;

		Enemysprite.setTexture(textures[currentFrame]);//Dat frame ke tiep
		timeSinceLastFrame = 0.0F;
	}

	if (inHurt) {
		durationOfAnimation -= deltaTime;
		if (durationOfAnimation < 1e-9) {
			inHurt = false;
		}
	}

}

//Kich hoat animation trúng sát thương của enemy
void enemy::hurt() {
	inHurt = true;
	//textures = Resource_Management::getTexture("Ghast_Hurt");
	durationOfAnimation = 0.5F;
}

std::ostream& operator<<(std::ostream& oDev, enemy& cenemy) {//Use this for save file
	oDev << cenemy.enemyType << " " << cenemy.maxHealth << " " << cenemy._speed << " " << cenemy.bounty << "\n";
	return oDev;
}
