#pragma once

#include "Resource_Management.h"
#include "State.h"
#include "Sprite.h"
#include "Button.h"
#include "SaveSlotConfirmOverwriteState.h"
#include "GameSaver.h"
#include <fstream>

class SaveGameState : public State {

public:
	SaveGameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(float dt) override;
	void render() override;

	bool fileExist(const std::string& filePath);//Is the file exist
	void checkSaveSlots();//Check see if have save file

private:
	sf::Text saveGameText = sf::Text(Resource_Management::arialFont, "SAVE GAME");
	Sprite loadGameBackgroundSprite = Sprite(Resource_Management::mainMenuBackgroundTexture);//Change this later
	Sprite goBackArrowSprite = Sprite(Resource_Management::arrowTexture, { 36, 36 });
	Button saveSlot1Button = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f - 40.0f }, "Save Slot 1");
	Button saveSlot2Button = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f }, "Save Slot 2");
	Button saveSlot3Button = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 40.0f }, "Save Slot 3");
	Button saveSlot4Button = Button({ 200.0f, 38.0f }, { Resource_Management::WINDOW_WIDTH / 2.0f, Resource_Management::WINDOW_HEIGHT / 2.0f + 80.0f }, "Save Slot 4");

	std::string saveFileName1 = "Data\\SaveGame\\GameSave1.sav";
	std::string saveFileName2 = "Data\\SaveGame\\GameSave2.sav";
	std::string saveFileName3 = "Data\\SaveGame\\GameSave3.sav";
	std::string saveFileName4 = "Data\\SaveGame\\GameSave4.sav";

	bool isFullSaveSlot1 = false;
	bool isFullSaveSlot2 = false;
	bool isFullSaveSlot3 = false;
	bool isFullSaveSlot4 = false;
};

