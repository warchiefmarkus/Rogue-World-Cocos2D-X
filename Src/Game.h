#ifndef GAME_H
#define GAME_H

#include <cocos2d.h>
#include <vector>
#include <Object.h>
#include <Hero.h>
#include <Level.h>
#include <Scenes/MenuLayer.h>
#include <Scenes/AboutLayer.h>
#include <Scenes/InstructionsLayer.h>
#include <Scenes/OptionsLayer.h>

USING_NS_CC;

class MenuLayer;
class AboutLayer;
class InstructionsLayer;
class OptionsLayer;



class Game
{    
public:

    // Initialize and return Main menu scene
    CCScene* init();

    //---------------------Main Menu----------------------//
    CCScene* menuScene; 
    MenuLayer* menuLayer;

    //---------------------About--------------------------//
	CCScene* aboutScene;
	AboutLayer* aboutLayer;
    void showAbout();

	//---------------------Instructions-------------------//
	CCScene* instructionsScene;
	InstructionsLayer* instructionsLayer;
	void showInstructions();

	//---------------------Options-------------------------//
	CCScene* optionsScene;
	OptionsLayer* optionsLayer;
	void showOptions();

	//---------------------New, Load Game------------------------//
	CCScene* gameScene;
    void NewGame();	
	void LoadGame();



};


#endif // GAME_H
