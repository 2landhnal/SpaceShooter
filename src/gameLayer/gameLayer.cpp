#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include "imfilebrowser.h"
#include <gl2d/gl2d.h>
#include <platformTools.h>
#include <glui/glui.h>
#include <ctime>


#include <bullet.h>
#include <vector>
#include <inputHandler.h>
#include <enemy.h>
#include <player.h>
#include <helper.h>
#include <baseObject.h>
#include <gameManager.h>
#include <renderManager.h>
#include <spriteBlueprint.h>
#include <global.h>
#include <healthBar.h>
#include <sceneManager.h>
#include <animation.h>
#include <tiledRenderer.h>
#include <itemBullet.h>
#include <itemHP.h>
#include <dataSaver.h>
#include <gameData.h>

constexpr int BACKGROUNDS = 3;

enum Mode {
	Menu, Playing, End
};

Mode gameMode = (Mode)Menu;

GameData& gameData = GameData::GetInstance();

SceneManager& sceneManager = SceneManager::GetInstance();
RenderManager& renderManager = RenderManager::GetInstance();
GameManager& gameManager = GameManager::GetInstance();
HealthBar* healthBar = new HealthBar();

Global& global = Global::GetInstance();
Player& player = Player::GetInstance();
InputHandler inputHandler;

gl2d::Renderer2D renderer;


#pragma region handle spawn enemy
Enemy* NewEnemy() {
	Enemy* e = new Enemy();
	e->SetBlueprint(global.enemyBlueprint);
	e->blueprint.texturePos = {rand()%2, rand()%2};
	e->position = player.position;
	return e;
}

void SpawnSingleEnemy()
{
	Enemy* e = NewEnemy();
	e->position = player.position;
	float disRadius = 2000;
	glm::vec2 offset(disRadius, 0);
	offset = glm::vec2(glm::vec4(offset, 0, 1) * glm::rotate(glm::mat4(1.f), glm::radians((float)(rand() % 360)), glm::vec3(0, 0, 1)));
	e->position += offset;
}

void HanldeSpawnEnemy(float deltaTime) {
	gameData.enemySpawnTime->counter -= deltaTime;
	if (gameData.enemySpawnTime->counter < 0)
	{
		gameData.enemySpawnTime->counter = gameData.enemySpawnTime->time + rand() % 2;
		SpawnSingleEnemy();
		if (rand() % 3 == 0)
		{
			SpawnSingleEnemy();
		}
	}
}

#pragma endregion

void SpawnSingleItem()
{
	ItemBullet* item = new ItemBullet();
	item->SetBlueprint(global.bulletItemBlueprint);
	item->viewDirection = GetRotateDirection(item->viewDirection, -90);
	item->position = player.position;
	float disRadius = 1000;
	glm::vec2 offset(disRadius, 0);
	offset = glm::vec2(glm::vec4(offset, 0, 1) * glm::rotate(glm::mat4(1.f), glm::radians((float)(rand() % 360)), glm::vec3(0, 0, 1)));
	item->position += offset;
}
void SpawnSingleHP()
{
	ItemHP* item = new ItemHP();
	item->SetBlueprint(global.hpItemBlueprint);
	item->viewDirection = GetRotateDirection(item->viewDirection, -90);
	item->position = player.position;
	float disRadius = 1000;
	glm::vec2 offset(disRadius, 0);
	offset = glm::vec2(glm::vec4(offset, 0, 1) * glm::rotate(glm::mat4(1.f), glm::radians((float)(rand() % 360)), glm::vec3(0, 0, 1)));
	item->position += offset;
}

void HanldeSpawnItem(float deltaTime) {
	gameData.itemSpawnCounter->counter -= deltaTime;
	if (gameData.itemSpawnCounter->counter < 0)
	{
		gameData.itemSpawnCounter->counter = gameData.itemSpawnCounter->time + rand() % 2;
		SpawnSingleItem();
		if (rand() % 3 == 0)
		{
			SpawnSingleItem();
		}
	}

	gameData.hpSpawnCounter->counter -= deltaTime;
	if (gameData.hpSpawnCounter->counter < 0)
	{
		gameData.hpSpawnCounter->counter = gameData.hpSpawnCounter->time + rand() % 2;
		SpawnSingleHP();
		if (rand() % 3 == 0)
		{
			SpawnSingleHP();
		}
	}
}

void RestartGame()
{
	renderer.currentCamera.follow(player.position
		,550, 0, 0, renderer.windowW, renderer.windowH);
	sceneManager.Restart();
	gameData.Reset();
	player.Revive();
	player.SetShooter(new BulletShooter());
}

void SpawnExplosion() {
	global.SpawnExplosion(player.position);
}

#pragma region menu
void NextSkin() {
	gameData.currentSkinIndex++;
	gameData.currentSkinIndex %= global.playerBlueprints.size();
	player.SetBlueprint(global.playerBlueprints[gameData.currentSkinIndex]);
}

void PrevSkin() {
	gameData.currentSkinIndex--;
	gameData.currentSkinIndex += global.playerBlueprints.size();
	gameData.currentSkinIndex %= global.playerBlueprints.size();
	player.SetBlueprint(global.playerBlueprints[gameData.currentSkinIndex]);
}

void menu(float deltaTime, int w, int h) {
	// show tutor
	if (
		isClickOn(global.prevCor, w, h) ||
		platform::isButtonPressedOn(platform::Button::A) ||
		platform::isButtonPressedOn(platform::Button::Left)
		)
	{
		PrevSkin();
	}
	if (
		isClickOn(global.nextCor, w, h) ||
		platform::isButtonPressedOn(platform::Button::D) ||
		platform::isButtonPressedOn(platform::Button::Right)
		)
	{
		NextSkin();
	}
	// ui
	glui::RendererUi ui;
	if (isClickOn(global.playButtonCor, w, h) || platform::isButtonPressedOn(platform::Button::Enter)) {
		gameMode = Playing;
		RestartGame();
	}
}

#pragma endregion

#pragma region gameUpdate
void gameUpdate(float deltaTime) {
#pragma region spawn enemy
	HanldeSpawnItem(deltaTime);
	HanldeSpawnEnemy(deltaTime);
#pragma endregion

#pragma region update
	if (player.hp <= 0) {
		if (gameData.score > DataSaver::GetInstance().highScore) {
			time(&(gameData.timestamp));
			DataSaver::GetInstance().highScore = gameData.score;
		}
		DataSaver::GetInstance().Save();

		gameMode = End;
		return;
	}

	gameManager.RemoveMarkedForDelete();
	for (int i = 0; i < gameManager.objects.size(); i++) {
		try {
			gameManager.objects[i]->Update(deltaTime);
		}
		catch(...){
			cout << "baseObj null\n";
		}
	}
#pragma endregion
}

#pragma region end
void end(float deltaTime, int w, int h) {
	if (
		isClickOn(global.menuButtonCor, w, h) ||
		platform::isButtonPressedOn(platform::Button::Space) ||
		platform::isButtonPressedOn(platform::Button::Enter)
		)
	{
		RestartGame();
		gameMode = Menu;
	}
}
#pragma endregion


bool initGame()
{
	DataSaver::GetInstance().Load();
	srand(time(NULL));
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	global.InitSpriteConfig();

	// MUSIC
	Sound music = Global::GetInstance().music;
	PlaySound(music);

	// load space ship texture
	player.SetBlueprint(global.playerBlueprints[0]);
	player.speed *= 3.0f;
	// load bg 
	int bgLayers = global.backGroundBlueprint.size();
	for (int i = 0; i < bgLayers; i++) {
		TiledRenderer* tiledBg = new TiledRenderer();
		tiledBg->SetBlueprint(global.backGroundBlueprint[i]);
		tiledBg->paralaxStrength = i * (1.0f / bgLayers);
	}
	// load ug
	int ugLayers = global.upGroundBlueprint.size();
	for (int i = 0; i < ugLayers; i++) {
		TiledRenderer* tiledUg = new TiledRenderer();
		tiledUg->SetBlueprint(global.upGroundBlueprint[i]);
		tiledUg->paralaxStrength = 1 + i * (1.0f / ugLayers);
	}

	sceneManager.StartCounting();
	RestartGame();
	return true;
}



bool gameLogic(float deltaTime)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h
		
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen

	renderer.updateWindowMetrics(w, h);
#pragma endregion

	switch (gameMode) {
	case Menu:
		menu(deltaTime, w, h);
		break;
	case Playing:
		gameUpdate(deltaTime);
		break;
	case End:
		end(deltaTime, w, h);
		break;
	}
#pragma region follow
	renderer.currentCamera.zoom = 0.5;
	// renderer.currentCamera.rotation = fromDirectionToDegree(player.viewDirection)+90;
	renderer.currentCamera.follow(player.position
		, deltaTime * 550, 1, 150, w, h);
#pragma endregion

#pragma region render base
	for (int i = 0; i < renderManager.objects.size(); i++) {
		for (SpriteRenderer* e : renderManager.objects[i]) {
			e->Render(renderer);
		}
	}
#pragma endregion

#pragma region ui

	// render text
	renderer.pushCamera();
	{
		if (gameMode == Playing) {
			std::string scoreText = "Score: " + std::to_string(gameData.score);
			healthBar->RenderHealthBar(renderer, w, h);
			renderer.renderText({ w * 8 / 10, h / 10 }, scoreText.c_str(), global.font, Colors_White, 0.5f * w / 1920);
			scoreText = "High score: " + std::to_string((int)max(gameData.score, DataSaver::GetInstance().highScore));
			renderer.renderText({ w * 8 / 10, h / 7 }, scoreText.c_str(), global.font, Colors_White, 0.5f * w / 1920);
		}

		if (gameMode == Menu) {
			glui::Frame f({ 0,0, w, h });
			glui::Box playBtnBox = glui::Box().xLeftPerc(global.playButtonCor.x).yTopPerc(global.playButtonCor.y).
				xDimensionPercentage(global.playButtonCor.z).yDimensionPercentage(global.playButtonCor.w);
			renderer.renderRectangle(playBtnBox, global.playButton);

			glui::Box prevBtnBox = glui::Box().xLeftPerc(global.prevCor.x).yTopPerc(global.prevCor.y).
				xDimensionPercentage(global.prevCor.z).yDimensionPercentage(global.prevCor.w);
			renderer.renderRectangle(prevBtnBox, global.playButton);

			glui::Box nextBtnBox = glui::Box().xLeftPerc(global.nextCor.x).yTopPerc(global.nextCor.y).
				xDimensionPercentage(global.nextCor.z).yDimensionPercentage(global.nextCor.w);
			renderer.renderRectangle(nextBtnBox, global.playButton);

			renderer.renderText({ (global.playButtonCor.x + global.playButtonCor.z / 2) * w , (global.playButtonCor.y + global.playButtonCor.w / 2.5) * h }, "Play", global.font, Colors_White, 0.7f * w / 1920);
			renderer.renderText({ (global.prevCor.x + global.prevCor.z / 2) * w , (global.prevCor.y + global.prevCor.w / 2.5) * h }, "Prev", global.font, Colors_White, 0.7f * w / 1920);
			renderer.renderText({ (global.nextCor.x + global.nextCor.z / 2) * w , (global.nextCor.y + global.nextCor.w / 2.5) * h }, "Next", global.font, Colors_White, 0.7f * w / 1920);

			renderer.renderText({0.5*w, 0.2*h}, "Space Shooter", global.font, Colors_White, 1.f * w / 1920);
		}

		if (gameMode == End) {
			glui::Frame f({ 0,0, w, h });
			glui::Box menuBtnBox = glui::Box().xLeftPerc(global.playButtonCor.x).yTopPerc(global.playButtonCor.y).
				xDimensionPercentage(global.playButtonCor.z).yDimensionPercentage(global.playButtonCor.w);
			renderer.renderRectangle(menuBtnBox, global.playButton);
			renderer.renderText({ (global.menuButtonCor.x + global.menuButtonCor.z / 2) * w , (global.menuButtonCor.y + global.menuButtonCor.w / 2.5) * h }, "Menu", global.font, Colors_White, 0.7f * w / 1920);
			renderer.renderText({ 0.5 * w, 0.2 * h }, "Loser!!!", global.font, Colors_White, 1.f * w / 1920);
			std::string scoreText = "Score " + std::to_string(gameData.score);
			renderer.renderText({ 0.5 * w, 0.3 * h }, scoreText.c_str(), global.font, Colors_White, .5f * w / 1920);
		}
	}
	renderer.popCamera();
#pragma endregion

	renderer.flush();


	//ImGui::ShowDemoWindow();

	ImGui::Begin("Analyzing...");
	ImGui::Text("BaseObject count: %d", gameManager.objects.size());
	ImGui::Text("View rect: (%f, %f)", player.position.x, player.position.y);
	glm::vec2 v = platform::getRelMousePosition();
	ImGui::Text("Mouse relPos: (%f, %f)", v.x, v.y);
	ImGui::Text("Player layer: %d", player.blueprint.layer);
	ImGui::Text("Ship count: %d", global.ships.size());
	ImGui::Text("Ship angle: %f", fromDirectionToDegree(player.viewDirection));
	ImGui::Text("Render layer 10: %d", renderManager.objects[10].size());
	if (ImGui::Button("Spawn explosion"))
	{
		SpawnExplosion();
	}
	if (ImGui::Button("Spawn item"))
	{
		SpawnSingleItem();
	}
	if (ImGui::Button("Reset game"))
	{
		RestartGame();
	}
	if (ImGui::Button("Pause game"))
	{
		gameMode = End;
	}
	ImGui::SliderFloat("Player Health", &player.hp, 0, player.maxHp);

	ImGui::End();

	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{



}
