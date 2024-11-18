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

constexpr int BACKGROUNDS = 3;

struct Counter {
	float time;
	float counter;
	Counter(float time) {
		this->time = rand()%(int)time;
		this->counter = counter;
	}
};

struct GameData {
	int score=0;
	Counter* enemySpawnTime, *itemSpawnCounter, *hpSpawnCounter;
	time_t timestamp;

	void Reset() {
		score = 0;
		enemySpawnTime = new Counter(5);
		itemSpawnCounter = new Counter(30);
		hpSpawnCounter = new Counter(30);
		time(&timestamp);
	}
};
bool pauseGame = false;

GameData gameData;

SceneManager& sceneManager = SceneManager::GetInstance();
RenderManager& renderManager = RenderManager::GetInstance();
GameManager& gameManager = GameManager::GetInstance();

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
}

void SpawnExplosion() {
	global.SpawnExplosion(player.position);
}


bool initGame()
{
	srand(time(NULL));
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	global.InitSpriteConfig();

	// load space ship texture
	player.SetBlueprint(global.playerBlueprint);
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

	if (!pauseGame) {
#pragma region spawn enemy
		HanldeSpawnItem(deltaTime);
		HanldeSpawnEnemy(deltaTime);
#pragma endregion

#pragma region update
		if (player.hp <= 0) {
			RestartGame();
			return true;
		}

		gameManager.RemoveMarkedForDelete();
		for (BaseObject* b : gameManager.objects) {
			b->Update(deltaTime);
		}
#pragma endregion

#pragma region follow
		renderer.currentCamera.zoom = 0.5;
		// renderer.currentCamera.rotation = fromDirectionToDegree(player.viewDirection)+90;
		renderer.currentCamera.follow(player.position
			, deltaTime * 550, 1, 150, w, h);
#pragma endregion
	}

#pragma region render base
	for (int i = 0; i < renderManager.objects.size(); i++) {
		for (SpriteRenderer* e : renderManager.objects[i]) {
			e->Render(renderer);
		}
	}
#pragma endregion

#pragma region ui
	RenderHealthBar(renderer, player, w, h);
#pragma endregion

	renderer.flush();


	//ImGui::ShowDemoWindow();

	ImGui::Begin("debug");
	ImGui::Text("BaseObject count: %d", gameManager.objects.size());
	ImGui::Text("View rect: (%f, %f)", player.position.x, player.position.y);
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
		pauseGame = !pauseGame;
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
