#include "Level.h"
#include "Hero.h"
#include "Object.h"
#include "Npc.h"
#include "Wall.h"
#include "Floor.h"
#include "Monster.h"
#include "Box.h"

// ---------- Initialization of Level ----------
bool Level::init()
{
    if ( !CCLayer::init() )
    {
            return false;
    }
    this->setAnchorPoint(ccp(0,0));
	this->setIsTouchEnabled(true); 
	//------------------------------------Load Game Data----------------------------------//
	loadGameData();
	//--------------------Create SpriteBatch which content all sprites--------------------//
	batch = CCSpriteBatchNode::batchNodeWithTexture(gameData->SpriteSheet);
	batch->setAnchorPoint(ccp(0,0));
	this->addChild(batch);
	
	
	
	// Highlight clicked cell
	float cell_num = 11;
	cellHighlight = CCSprite::spriteWithTexture(gameData->SpriteSheet,CCRect((cell_num*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
	cellHighlight->setAnchorPoint(ccp(0,0));
	batch->addChild(cellHighlight,5);
	cellHighlight->setIsVisible(false);

    return true;
}

//--------------------Load Game Data---------------//
void Level::loadGameData()
{
	gameData = new GameData();

	// Load Sprite Sheet
	gameData->SpriteSheet = CCSprite::spriteWithFile("Resources//SpriteSheet.png")->getTexture();
}

//--------------------New Game--------------------//
void Level::newGame()
{
	DGenerator dgenerator;
	loadGame(dgenerator.generate(50,50));
}

void Level::loadGame(std::string filename)
{

}

void Level::loadGame(MMap map)
{
	
	Width = map.width;
	Height = map.height;

    TMap = new Map(Width, Height); // create Map

	for (int k=0; k < map.width; k++)
	{
		for (int i=0; i< map.height; i++)
		{
		    //-----------------------------GROUND-----------------------------//
			if (map.cells[k][i].ground == npc)
			{
				Object* obj = createObject(npc);			
				TMap->addObj(obj,Point(k,i),GROUND);
			}
			if (map.cells[k][i].ground == wall)
			{
				Object* obj = createObject(wall);			
				TMap->addObj(obj,Point(k,i),GROUND);
			}
			if (map.cells[k][i].ground == flor)
			{
				Object* obj = createObject(flor);			
				TMap->addObj(obj,Point(k,i),GROUND);
			}
			if (map.cells[k][i].ground == monster)
			{
				Object* obj = createObject(monster);			
				TMap->addObj(obj,Point(k,i),GROUND);
			}
			if (map.cells[k][i].ground == box)
			{
				Object* obj = createObject(box);			
				TMap->addObj(obj,Point(k,i),GROUND);
			}
			if (map.cells[k][i].ground == empty)
			{
				Object* obj = createObject(empty);
				TMap->addObj(obj,Point(k,i),GROUND);				
			}
			//-----------------------------ENIVORMENT-----------------------------//
			if (map.cells[k][i].eniv == npc)
			{
				Object* obj = createObject(npc);
				TMap->addObj(obj,Point(k,i),ENIVORMENT);
			}
			if (map.cells[k][i].eniv == wall)
			{
				Object* obj = createObject(wall);
				TMap->addObj(obj,Point(k,i),ENIVORMENT);
			}
			if (map.cells[k][i].eniv == flor)
			{
				Object* obj = createObject(flor);
				TMap->addObj(obj,Point(k,i),ENIVORMENT);
			}
			if (map.cells[k][i].eniv == monster)
			{
				Object* obj = createObject(monster);
				TMap->addObj(obj,Point(k,i),ENIVORMENT);
			}
			if (map.cells[k][i].eniv == box)
			{
				Object* obj = createObject(box);
				TMap->addObj(obj,Point(k,i),ENIVORMENT);
			}
			if (map.cells[k][i].eniv == empty)
			{
				Object* obj = createObject(empty);
				TMap->addObj(obj,Point(k,i),ENIVORMENT);				
			}
			//-----------------------------NPC-----------------------------//
			if (map.cells[k][i].npc == npc)
			{
				Object* obj = createObject(npc);
				TMap->addObj(obj,Point(k,i),NPC);
			}
			if (map.cells[k][i].npc == wall)
			{
				Object* obj = createObject(wall);
				TMap->addObj(obj,Point(k,i),NPC);
			}
			if (map.cells[k][i].npc == flor)
			{
				Object* obj = createObject(flor);
				TMap->addObj(obj,Point(k,i),NPC);
			}
			if (map.cells[k][i].npc == monster)
			{
				Object* obj = createObject(monster);
				TMap->addObj(obj,Point(k,i),NPC);
				
			}
			if (map.cells[k][i].npc == box)
			{
				Object* obj = createObject(box);
				TMap->addObj(obj,Point(k,i),NPC);
			}
			if (map.cells[k][i].npc == empty)
			{
				Object* obj = createObject(empty);
				TMap->addObj(obj,Point(k,i),NPC);				
			}
		}
	}

	MHero = createHero();
	MHero->setPos(0,0);
}

Hero* Level::createHero()
{
	Hero* obj = Hero::node(); // create new object			
	obj->initialize(gameData);		
	this->batch->addChild(obj,NPC); // add it to map
	return obj; // return pointer to new object    
}

Object* Level::createObject(ObjectType type)
{
    switch (type)
    {
	case npc:
		{			
			Npc* obj = Npc::node(); // create new object
			obj->initialize(NPC, gameData); 
			this->batch->addChild(obj,NPC); // add it to map	
			return obj; // return pointer to new object
		}
	case wall:
		{
			Wall* obj = Wall::node(); 
	        obj->initialize(GROUND, gameData);			
			this->batch->addChild(obj,GROUND); 	
			return obj; 
		}
	case flor:
		{
			Floor* obj = Floor::node(); 
			obj->initialize(GROUND, gameData);			
			this->batch->addChild(obj, GROUND); 		
			return obj; 
		}

	case monster:
		{
			Monster* obj = Monster::node(); 
			obj->initialize(NPC, gameData);
			this->batch->addChild(obj, NPC); 		
			return obj; 
		}

	case box:
		{
			Box* obj = Box::node();
			obj->initialize(ENIVORMENT, gameData);
			this->batch->addChild(obj, ENIVORMENT);		
			return obj; 
		}
	case empty:
		{
			Object* obj = Object::node();
			obj->initialize(gameData);
			obj->type = empty;
			return obj;
		}

    default:
    {
        return Object::node(); // if no type return new default Object
    }
    }
}

void Level::ScrollToHero()
{
	/*batch->setPosition(
		ccp(
		(MHero->getPosition().x-int(CCDirector::sharedDirector()->getWinSize().width/2)),
		(MHero->getPosition().y-int(CCDirector::sharedDirector()->getWinSize().height/2))
		)
		);*/
}

// Next step function of game
void Level::nextStep()
{
	
	ScrollToHero();
	
	for (int i=0; i<Width; i++){
		for (int k=0; k<Height; k++){
			if (TMap->getObject(i,k,NPC)->type == npc ){
				// Call nextStep function of object				
				TMap->getObject(i,k,NPC)->nextStep();
			}
		}
	}
}

void Level::ccTouchesBegan(CCSet *touches, CCEvent *event)
{
	CCTouch* touch = (CCTouch*)( touches->anyObject() );

	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);

	
	cellHighlight->setPosition(CCPoint((int(location.x/CELL_WIDTH)*CELL_WIDTH), (int (location.y/CELL_HEIGHT)*CELL_HEIGHT)));
	cellHighlight->setIsVisible(true);

	std::cout << "ccTouchBegan";
}

void Level::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	
	cellHighlight->setIsVisible(false);

	CCTouch* touch = (CCTouch*)( touches->anyObject() );

	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);

    std::cout << "ccTouchEnded";


	if (((int(location.x/CELL_WIDTH)!=MHero->getPos().X)&(int(location.x/CELL_HEIGHT)!=MHero->getPos().Y)))
	{
		MHero->MoveTo(int(location.x/CELL_WIDTH) ,int(location.y/CELL_HEIGHT));
		nextStep();
	}
	else 
	{
		std::cout << " POSITION SIMILAR";
	}
	
}




































