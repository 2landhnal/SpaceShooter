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

#include <bullet.h>
#include <vector>
#include <inputHandler.h>
#include <enemy.h>
#include <player.h>
#include <helper.h>
#include <baseObject.h>
#include <gameManager.h>
#include <spriteRenderer.h>
#include <renderManager.h>
#include <spriteBlueprint.h>
#include <global.h>

#include <tiledRenderer.h>

constexpr int BACKGROUNDS = 3;

RenderManager& renderManager = RenderManager::GetInstance();
GameManager& gameManager = GameManager::GetInstance();
Player& player = Player::GetInstance();
Global& global = Global::GetInstance();
InputHandler inputHandler;

gl2d::Renderer2D renderer;

gl2d::Texture backgroundTexture[BACKGROUNDS];
TiledRenderer tiledRenderer[BACKGROUNDS];

gl2d::Texture upperBackgroundTexture;
TiledRenderer upperTiledRenderer;

// bullet
gl2d::Texture bulletsTexture;
gl2d::TextureAtlasPadding bulletsAtlas;

void SpawnEnemy() {
	Enemy* e = new Enemy();
	e->markedForDeletion = false;
	e->spriteRenderer.SetBlueprint(global.enemyBlueprint);
	*(e->Position()) = *player.Position();
}

void restartGame()
{
	renderer.currentCamera.follow(*player.Position()
		,550, 0, 0, renderer.windowW, renderer.windowH);
	renderManager.Clear();
	gameManager.Clear();
	renderManager.AddObject(&player.spriteRenderer);
	gameManager.AddObject(&player);
}


bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	global.InitSpriteConfig();

	// load space ship texture
	player.spriteRenderer.SetBlueprint(global.playerBlueprint);
	// load bg texture
	backgroundTexture[0].loadFromFile(RESOURCES_PATH "background/bg1.png", true);
	backgroundTexture[1].loadFromFile(RESOURCES_PATH "background/bg2.png", true);
	backgroundTexture[2].loadFromFile(RESOURCES_PATH "background/bg3.png", true);
	// upper
	upperBackgroundTexture.loadFromFile(RESOURCES_PATH "background/bg4.png", true);

	// paralax setup
	for (int i = 0; i < BACKGROUNDS; i++) {
		tiledRenderer[i].paralaxStrength = i*(1.0f/ BACKGROUNDS);
	}

	// set up tiled renderer
	for (int i = 0; i < BACKGROUNDS; i++) {
		tiledRenderer[i].texture = backgroundTexture[i];
	}

	// upper
	upperTiledRenderer.texture = upperBackgroundTexture;

	restartGame();
	
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

#pragma region update
	inputHandler.Update(deltaTime);

	gameManager.RemoveMarkedObjects();
	for (BaseObject* b : gameManager.objects) {
		b->Update(deltaTime);
	}
#pragma endregion

#pragma region render background
	for (int i = 0; i < BACKGROUNDS; i++)
	{
		tiledRenderer[i].render(renderer);
	}
#pragma endregion

#pragma region follow
	renderer.currentCamera.zoom = 0.5;
	renderer.currentCamera.follow(*player.Position()
		, deltaTime * 550, 1, 150, w, h);
#pragma endregion

#pragma region render base
	for (int i = 0; i < renderManager.objects.size(); i++) {
		for (SpriteRenderer* e : renderManager.objects[i]) {
			e->Render(renderer);
		}
	}
#pragma endregion

#pragma region render upper bg
	upperTiledRenderer.render(renderer);
#pragma endregion

#pragma region ui
	renderer.pushCamera();
	{
		glui::Frame f({ 0,0, w, h });
		glui::Box healthBox = glui::Box().xLeftPerc(0.65).yTopPerc(0.1).
			xDimensionPercentage(0.3).yAspectRatio(1.f / 8.f);
		renderer.renderRectangle(healthBox, global.healthBar);
		glm::vec4 newRect = healthBox();
		newRect.z *= player.hp;
		glm::vec4 textCoords = { 0,1,1,0 };
		textCoords.z *= player.hp;
		renderer.renderRectangle(newRect, global.health, Colors_White, {}, {},
			textCoords);
	}
	renderer.popCamera();
#pragma endregion

	renderer.flush();


	//ImGui::ShowDemoWindow();

	ImGui::Begin("debug");
	ImGui::Text("BaseObject count: %d", gameManager.objects.size());
	ImGui::Text("View rect: (%f, %f)", (*player.Position()).x, (*player.Position()).y);
	if (ImGui::Button("Spawn enemy"))
	{
		SpawnEnemy();
	}
	if (ImGui::Button("Reset game"))
	{
		restartGame();
	}
	ImGui::SliderFloat("Player Health", &player.hp, 0, 1);

	ImGui::End();

	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{



}
