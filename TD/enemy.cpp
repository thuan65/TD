#include "enemy.h"

enemy::enemy(const std::vector<sf::Texture>& rTextures, const vector<sf::Vector2f>& _rpath, std::string enemyType, int rMaxHealth, float rspeed, int rBounty) // thêm max_Health
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
	addAnimation();
}

enemy::enemy(const std::vector<sf::Texture>& rTextures, const vector<sf::Vector2f>& _rpath, std::string enemyType, int rMaxHealth, int rHealth, float rspeed, int rBounty, float x, float y, int currentWayPoint)//This is constructor for load Enemey
	: textures(rTextures),
Enemysprite(textures[0]),
enemyType(enemyType),
_speed(rspeed),
maxHealth(rMaxHealth), // Khởi tạo máu tối đa
_health(rHealth), bounty(rBounty),    // Máu hiện tại bắt đầu bằng máu tối đa
currentWayPoint(currentWayPoint)
{
	totalFrame = rTextures.size();
	_path = _rpath;
	if (!_path.empty()) {
		Enemysprite.setPosition(sf::Vector2f(x,y));//Sau sẽ có chỉnh sai số
	}

	// --- KHỞI TẠO THANH MÁU ---
	// Thanh nền (màu đỏ)
	healthBarBackground.setSize(sf::Vector2f(32.f, 5.f)); // Chiều dài 32, cao 5
	healthBarBackground.setFillColor(sf::Color::Red);

	// Thanh máu hiện tại (màu xanh)
	healthBarForeground.setSize(sf::Vector2f(32.f, 5.f));
	healthBarForeground.setFillColor(sf::Color::Green);
	addAnimation();
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

bool enemy::isEnemyAlive() {
	return !((enemyState == EnemyState::Dead) && deadAnimationFinished);
}

void enemy::damageTake(int rdamage) {
	//if (enemyState == EnemyState::Dead) return;
	_health -= rdamage;

	if (_health < 0.1f) {//If the enemy is dead, play hurt Animation then dead animation
		//_health = 0;
		hurtTimer = durationOfHurtAnimation;
		enemyState = EnemyState::Dead;
		frameTime = hurtFrameTime;
		currentFrame = 0;
		totalFrame = hurt_textures.size();
	}
	else {//Play hurt animation
		hurtTimer = durationOfHurtAnimation;
		enemyState = EnemyState::Hurt;
		frameTime = hurtFrameTime;
		currentFrame = 0;
		totalFrame = hurt_textures.size();
	}

	// CẬP NHẬT CHIỀU DÀI THANH MÁU KHI NHẬN SÁT THƯƠNG
	if (_health <= 0) {
		healthBarForeground.setSize(sf::Vector2f(32.f * 0, 5.f));
		return;
	}
	float healthPercent = static_cast<float>(_health) / maxHealth;
	healthBarForeground.setSize(sf::Vector2f(32.f * healthPercent, 5.f));
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

	if (enemyState == EnemyState::Hurt && hurtTimer < 0.0f) {//If the hurt Animation is over
		if (enemyState != EnemyState::Dead) {//enemy still have some hp leaft
			enemyState = EnemyState::Walk;
			frameTime = walkFrameTime;
			currentFrame = 0;
			totalFrame = textures.size();
		}
	}
	
}



void enemy::animate(float deltaTime) {
	if (enemyState == EnemyState::Dead) {//Enemy Death, play dead animation only
		playLastAnimation(deltaTime);
		return;
	}

	timeSinceLastFrame += deltaTime; //Thoi gian giua cac Frame

	if (timeSinceLastFrame >= frameTime) { //Neu du thoi gian chuyen frame

		currentFrame = (currentFrame + 1) % totalFrame;
		timeSinceLastFrame = 0.0F;

		if (enemyState == EnemyState::Walk) {
			Enemysprite.setTexture(textures[currentFrame]);//Dat frame ke tiep
			Enemysprite.setColor(sf::Color::White);
		}
		else if (enemyState == EnemyState::Hurt) {
			Enemysprite.setColor(sf::Color(255, 180, 180));
			Enemysprite.setTexture(hurt_textures[currentFrame]);
			hurtTimer -= deltaTime;
		}
	}

}

void enemy::playLastAnimation(float deltaTime) {
	timeSinceLastFrame += deltaTime; //Thoi gian giua cac Frame

	//if (!LastHurtAnimation) {
	//	// Chạy hurt animation
	//	if (timeSinceLastFrame >= frameTime) {
	//		timeSinceLastFrame = 0.0f;
	//		currentFrame++;

	//		if (currentFrame >= hurt_textures.size()) {
	//			currentFrame = hurt_textures.size() - 1; // Giữ frame cuối
	//		}

	//		Enemysprite.setTexture(hurt_textures[currentFrame]);
	//		Enemysprite.setColor(sf::Color(255, 180, 180)); // Hiệu ứng hurt
	//	}

	//	hurtTimer -= deltaTime;
	//	if (hurtTimer <= 0.0f) {
	//		// Chuyển sang dead animation
	//		LastHurtAnimation = true;
	//		Enemysprite.setColor(sf::Color(255, 255, 255)); // Reset màu
	//		//currentFrame = 0;
	//		timeSinceLastFrame = 0.0f;
	//	}
	//}
	
		// Chạy dead animation
		if (timeSinceLastFrame >= deadFrameTime) {
			timeSinceLastFrame = 0.0f;
			DeadCurrentFrame++;

			if (DeadCurrentFrame < dead_textures.size()) {
				Enemysprite.setTexture(dead_textures[DeadCurrentFrame]);
				//Enemysprite.setTextureRect(sf::IntRect({ 0, 14 }, { 38, 32 }));
			}
			else {
				deadAnimationFinished = true;
			}
		}

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
	if (enemyState == EnemyState::Dead) return; //If enemy is dead, it won't move

	sf::Vector2f currentPosition = Enemysprite.getPosition();
	sf::Vector2f TargetPosition = _path[currentWayPoint]; //The next point it need to go to

	sf::Vector2f direction = TargetPosition - currentPosition;

	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	//std::cout << "Speed: " << _speed << "\n";
	if (distance > 1.0f) {
		direction /= distance;
		Enemysprite.move(direction * _speed * deltaTime);
	}
	else {
		Enemysprite.setPosition(TargetPosition);
		currentWayPoint++;
	}
}

void enemy::addAnimation() {
	hurt_textures = Resource_Management::getTexture(enemyType + "_Hurt");
	dead_textures = Resource_Management::getTexture(enemyType + "_Dead");
}



