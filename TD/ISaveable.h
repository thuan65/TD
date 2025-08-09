#pragma once
#include <iostream>

enum class SaveableType {
	TowerManager,
	WaveManager,
	MapID
};

//This is a interface class (or abstract class)
class ISaveable {
public:
	virtual void save(std::ostream& oDev) const  = 0;//Save everything to file
	virtual void loadSave(std::istream& iDev) = 0;
	virtual ~ISaveable() {};

};

