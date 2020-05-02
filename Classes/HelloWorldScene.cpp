#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include <ctime>
#include <stack>
#include <fstream>
#include <string>

USING_NS_CC;
#define SIZE 13
#define set_time 10

Scene* HelloWorld::createScene()
{
	//Instruction Popup
	MessageBox("Player1 has been poisoned and needs to get a magic healing potion from Player2 within 10s to survive.\n"
		"Help them meet before time runs out...\n"
		"Control Player2 with:\n   W\nA  D  S\nControl Player1 with Arrow Keys",
		"INSTRUCTIONS");
	//Create Level
	return HelloWorld::createLevel();
}

Scene* HelloWorld::createLevel()
{
	//calls init
	return HelloWorld::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
}

// CELL STRUCTURE
struct Cell
{
	bool visited;
	bool top_wall;
	bool bot_wall;
	bool left_wall;
	bool right_wall;
	char display;
};

Cell Level[SIZE][SIZE];
// set_timeIZE MAZE
void set_timeize(Cell Level[][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			Level[i][j].display = '*';
			Level[i][j].visited = false;
			Level[i][j].top_wall = true;
			Level[i][j].bot_wall = true;
			Level[i][j].left_wall = true;
			Level[i][j].right_wall = true;
		}
	}
	for (int i = 1; i < SIZE - 1; i++) {
		for (int j = 1; j < SIZE - 1; j++) {
			// Border Cells have fewer accessible walls
			Level[1][j].top_wall = false;
			Level[SIZE - 2][j].bot_wall = false;
			Level[i][1].left_wall = false;
			Level[i][SIZE - 2].right_wall = false;
		}
	}
}
// GENERATE MAZE
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int &goalY) {
	srand((unsigned)time(NULL));				        					// Pick random start cell
	int random = 0;
	int randomX = ((2 * rand()) + 1) % (SIZE - 1);						// Generate a random odd number between 1 and SIZE
	int randomY = ((2 * rand()) + 1) % (SIZE - 1);						// Generate a random odd number between 1 and SIZE
	posX = randomX;                       						// Save player's set_time X position
	posY = randomY;                      						// Save player's set_time Y position
	int visitedCells = 1;
	int totalCells = ((SIZE - 1) / 2)*((SIZE - 1) / 2);
	int percent = 0;
	std::stack<int> back_trackX, back_trackY; 						// Stack is used to trace the reverse path

	Level[randomY][randomX].display = 'S';						// Set S as the start cell
	Level[randomY][randomX].visited = true;						// Set start cell as visited;

	while (visitedCells < totalCells)
	{
		if (((Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true && Level[randomY - 2][randomX].bot_wall == true)) ||
			((Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true && Level[randomY + 2][randomX].top_wall == true)) ||
			((Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true && Level[randomY][randomX - 2].right_wall == true)) ||
			((Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true && Level[randomY][randomX + 2].left_wall == true)))
		{
			random = (rand() % 4) + 1;		// Pick a random wall 1-4 to knock down

			 // GO UP
			if ((random == 1) && (randomY > 1)) {
				if (Level[randomY - 2][randomX].visited == false) {	// If not visited
					Level[randomY - 1][randomX].display = ' ';	// Delete display
					Level[randomY - 1][randomX].visited = true;	// Mark cell as visited
					Level[randomY][randomX].top_wall = false;	// Knock down wall

					back_trackX.push(randomX); 			// Push X for back track
					back_trackY.push(randomY);			// Push Y for back track

					randomY -= 2;					// Move to next cell
					Level[randomY][randomX].visited = true;		// Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';		// Update path
					Level[randomY][randomX].bot_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			// GO DOWN
			else if ((random == 2) && (randomY < SIZE - 2)) {
				if (Level[randomY + 2][randomX].visited == false) {	// If not visited
					Level[randomY + 1][randomX].display = ' ';	// Delete display
					Level[randomY + 1][randomX].visited = true;	// Mark cell as visited
					Level[randomY][randomX].bot_wall = false;	// Knock down wall

					back_trackX.push(randomX); 			// Push X for back track
					back_trackY.push(randomY);			// Push Y for back track

					randomY += 2;					// Move to next cell
					Level[randomY][randomX].visited = true;		// Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';		// Update path
					Level[randomY][randomX].top_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			// GO LEFT
			else if ((random == 3) && (randomX > 1)) {
				if (Level[randomY][randomX - 2].visited == false) {	// If not visited
					Level[randomY][randomX - 1].display = ' ';	// Delete display
					Level[randomY][randomX - 1].visited = true;	// Mark cell as visited
					Level[randomY][randomX].left_wall = false;	// Knock down wall

					back_trackX.push(randomX); 			// Push X for back track
					back_trackY.push(randomY);			// Push Y for back track

					randomX -= 2;					// Move to next cell
					Level[randomY][randomX].visited = true;		// Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';		// Update path
					Level[randomY][randomX].right_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

			// GO RIGHT
			else if ((random == 4) && (randomX < SIZE - 2)) {
				if (Level[randomY][randomX + 2].visited == false) {	// If not visited
					Level[randomY][randomX + 1].display = ' ';	// Delete display
					Level[randomY][randomX + 1].visited = true;	// Mark cell as visited
					Level[randomY][randomX].right_wall = false;	// Knock down wall

					back_trackX.push(randomX); 			// Push X for back track
					back_trackY.push(randomY);			// Push Y for back track

					randomX += 2;					// Move to next cell
					Level[randomY][randomX].visited = true;		// Mark cell moved to as visited
					Level[randomY][randomX].display = ' ';		// Update path
					Level[randomY][randomX].left_wall = false;	// Knock down wall
					visitedCells++;					// Increase visitedCells counter
				}
				else
					continue;
			}

		}
		else {
			randomX = back_trackX.top();
			back_trackX.pop();

			randomY = back_trackY.top();
			back_trackY.pop();
		}
	}

	goalX = randomX;
	goalY = randomY;
	Level[goalY][goalX].display = 'E';
}

float _time =set_time;

bool HelloWorld::init()
{	
	int posX = 0;
	int posY = 0;
	int goalX = 0;
	int goalY = 0;
	set_timeize(Level);
	GenerateMaze(Level, posX, posY, goalX, goalY);

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize =Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//scheduling timer to call HelloWorld::ticktock every 1.0f second
	this->schedule(schedule_selector(HelloWorld::ticktock), 1.0f);


	// load the Sprite Sheet
	auto spritecache =SpriteFrameCache::getInstance();
	// the .plist file can be generated with any of the tools mentioned below
	spritecache->addSpriteFramesWithFile("SpriteSheet.plist");

	

	auto background = Sprite::createWithSpriteFrameName("images.jpg");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	background->setScale(8);
	this->addChild(background);

	
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + visibleSize.height - closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//audio
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("Storybook.mp3");
	audio->playBackgroundMusic("Storybook.mp3");

	//sprites	
	auto XSize =80;
	auto YSize =100;
	
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			Vec2 pos = Vec2(origin.x + 90 + (i+1)*20, origin.y - 5 + (j+1)*20);
			if (Level[i][j].display == '*')
			{
				//Obstruction
				auto block = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("Block.png"));
				block->setPosition(pos);
				this->addChild(block, 0, "block");
			}
			else if (Level[i][j].display == 'S')
			{
				//Start
				auto road = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("Road.png"));
				road->setPosition(pos);
				this->addChild(road, 0);
				auto Player1 = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("S_Sprite_F.png"));
				Player1->setPosition(pos);
				this->addChild(Player1, 0, "Player1");
			}
			else if (Level[i][j].display == 'E')
			{
				//End
				auto road = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("Road.png"));
				road->setPosition(pos);
				this->addChild(road, 0);
				auto Player2 = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("H_Sprite_F.png"));
				Player2->setPosition(pos);
				this->addChild(Player2, 0, "Player2");
			}
			else
			{
				//Path
				auto road = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("Road.png"));
				road->setPosition(pos);
				this->addChild(road, 0);
			}
		}
	
	//keyboard movement
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
			
			Node* p1 = event->getCurrentTarget()->getChildByName("Player1");
			Node* p2 = event->getCurrentTarget()->getChildByName("Player2");
			Vec2 loc_p2 = p2->getPosition();
			Vec2 loc_p1 = p1->getPosition();
			int i_ind, j_ind;
			Vec2 newLoc = Vec2(0, 0);
			Vec2 origin = Director::getInstance()->getVisibleOrigin();
			auto spritecache =SpriteFrameCache::getInstance();
			spritecache->addSpriteFramesWithFile("SpriteSheet.plist");
			switch (keyCode) {
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				event->getCurrentTarget()->removeChildByName("Player1");
				p1 = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("S_Sprite_L.png"));
				event->getCurrentTarget()->addChild(p1, 0, "Player1");
				newLoc = Vec2(loc_p1.x - 20, loc_p1.y);
				i_ind = (newLoc.x - origin.x - 90) / 20 - 1;
				j_ind = (newLoc.y - origin.y + 5) / 20 - 1;
				if (Level[i_ind][j_ind].display != '*')
				{
					p1->setPosition(newLoc);
				}
				else
				{
					p1->setPosition(loc_p1);
				}
				break;
			case EventKeyboard::KeyCode::KEY_A:
				event->getCurrentTarget()->removeChildByName("Player2");
				p2 = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("H_Sprite_L.png"));
				event->getCurrentTarget()->addChild(p2, 0, "Player2");
				newLoc = Vec2(loc_p2.x - 20, loc_p2.y);
				i_ind = (newLoc.x - origin.x - 90) / 20 - 1;
				j_ind = (newLoc.y - origin.y + 5) / 20 - 1;
				if (Level[i_ind][j_ind].display != '*')
				{
					p2->setPosition(newLoc);
				}
				else
				{
					p2->setPosition(loc_p2);
				}
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				event->getCurrentTarget()->removeChildByName("Player1");
				p1 =Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("S_Sprite_R.png"));
				event->getCurrentTarget()->addChild(p1, 0, "Player1");
				newLoc = Vec2(loc_p1.x + 20, loc_p1.y);
				i_ind = (newLoc.x - origin.x - 90) / 20 - 1;
				j_ind = (newLoc.y - origin.y + 5) / 20 - 1;
				if (Level[i_ind][j_ind].display != '*')
				{
					p1->setPosition(newLoc);
				}
				else
				{
					p1->setPosition(loc_p1);
				}
				break;
			case EventKeyboard::KeyCode::KEY_D:
				event->getCurrentTarget()->removeChildByName("Player2");
				p2 = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("H_Sprite_R.png"));
				event->getCurrentTarget()->addChild(p2, 0, "Player2");
				newLoc = Vec2(loc_p2.x + 20, loc_p2.y);
				i_ind = (newLoc.x - origin.x - 90) / 20 - 1;
				j_ind = (newLoc.y - origin.y + 5) / 20 - 1;
				if (Level[i_ind][j_ind].display != '*')
				{
					p2->setPosition(newLoc);
				}
				else
				{
					p2->setPosition(loc_p2);
				}
				break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				event->getCurrentTarget()->removeChildByName("Player1");
				p1 =Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("S_Sprite_B.png"));
				event->getCurrentTarget()->addChild(p1, 0, "Player1");
				newLoc = Vec2(loc_p1.x, loc_p1.y + 20);
				i_ind = (newLoc.x - origin.x - 90) / 20 - 1;
				j_ind = (newLoc.y - origin.y + 5) / 20 - 1;
				if (Level[i_ind][j_ind].display != '*')
				{
					p1->setPosition(newLoc);
				}
				else
				{
					p1->setPosition(loc_p1);
				}
				break;
			case EventKeyboard::KeyCode::KEY_W:
				event->getCurrentTarget()->removeChildByName("Player2");
				p2 = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("H_Sprite_B.png"));
				event->getCurrentTarget()->addChild(p2, 0, "Player2");
				newLoc = Vec2(loc_p2.x, loc_p2.y + 20);
				i_ind = (newLoc.x - origin.x - 90) / 20 - 1;
				j_ind = (newLoc.y - origin.y + 5) / 20 - 1;
				if (Level[i_ind][j_ind].display != '*')
				{
					p2->setPosition(newLoc);
				}
				else
				{
					p2->setPosition(loc_p2);
				}
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				event->getCurrentTarget()->removeChildByName("Player1");
				p1 =Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("S_Sprite_F.png"));
				event->getCurrentTarget()->addChild(p1, 0, "Player1");
				newLoc = Vec2(loc_p1.x, loc_p1.y - 20);
				i_ind = (newLoc.x - origin.x - 90) / 20 - 1;
				j_ind = (newLoc.y - origin.y + 5) / 20 - 1;
				if (Level[i_ind][j_ind].display != '*')
				{
					p1->setPosition(newLoc);
				}
				else
				{
					p1->setPosition(loc_p1);
				}
				break;
			case EventKeyboard::KeyCode::KEY_S:
				event->getCurrentTarget()->removeChildByName("Player2");
				p2 = Sprite::createWithSpriteFrame(spritecache->getSpriteFrameByName("H_Sprite_F.png"));
				event->getCurrentTarget()->addChild(p2, 0, "Player2");
				newLoc = Vec2(loc_p2.x, loc_p2.y - 20);
				i_ind = (newLoc.x - origin.x - 90) / 20 - 1;
				j_ind = (newLoc.y - origin.y + 5) / 20 - 1;
				if (Level[i_ind][j_ind].display != '*')
				{
					p2->setPosition(newLoc);
				}
				else
				{
					p2->setPosition(loc_p2);
				}
				break;
			}
			loc_p2 = p2->getPosition();
			loc_p1 = p1->getPosition();
			if ((loc_p2.x == loc_p1.x) && (loc_p1.y == loc_p2.y ))
			{
				_time =set_time;
				MessageBox("Mission Complete!", "SUCCESS");
				Scene* newScene =HelloWorld::createLevel();
				Director::getInstance()->replaceScene(newScene);
			}
		};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);


	return true;
}

//timer callback function
void HelloWorld::ticktock(float t) {
	Label *timer;
	if (_time == set_time)
	{
		timer = Label::createWithTTF("30", "Fonts/arial.ttf", 24);
		timer->setPosition(Vec2(90, 290));
		this->addChild(timer, 1, "timer");
	}
	_time -= t;
	CCString * value =CCString::createWithFormat("%.1f", _time);
	this->removeChildByName("timer");
	timer = Label::createWithTTF(value->getCString(), "Fonts/arial.ttf", 24);
	timer->setPosition(Vec2(90, 290));
	this->addChild(timer, 1, "timer");

	if (_time == 0.0f)
	{
		MessageBox("Sorry! Your Time is Over!", "GAME OVER"); 
		Director::getInstance()->end();
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
