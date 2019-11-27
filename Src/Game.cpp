#include "Game.h"



CCScene* Game::init()
{
    // Create Main menu scene and layer
    menuScene = CCScene::node();
    menuLayer = MenuLayer::node();
    menuScene->addChild(menuLayer);
    menuLayer->game = this;
    // Return Main menu scene
    return menuScene;
}

void Game::showAbout()
{
    aboutScene = CCScene::node();
    aboutLayer = AboutLayer::node();
    aboutScene->addChild(aboutLayer);
    CCDirector::sharedDirector()->pushScene(aboutScene);
}

void Game::showInstructions()
{
	instructionsScene = CCScene::node();
	instructionsLayer = InstructionsLayer::node();
	instructionsScene->addChild(instructionsLayer);
	CCDirector::sharedDirector()->pushScene(instructionsScene);
}

void Game::showOptions()
{
	optionsScene = CCScene::node();
	optionsLayer = OptionsLayer::node();
	optionsScene->addChild(optionsLayer);
	CCDirector::sharedDirector()->pushScene(optionsScene);
}

void Game::NewGame()
{
	Level* level = Level::node();
    gameScene = CCScene::node();
    gameScene->addChild(level);
    CCDirector::sharedDirector()->pushScene(gameScene);
	level->newGame(); // Start new game
}

void Game::LoadGame()
{
	Level* level = Level::node();
	gameScene = CCScene::node();
	gameScene->addChild(level);
	CCDirector::sharedDirector()->pushScene(gameScene);
	//level->loadGame(); // Continue game
}