#include "GamePlayScene.h"
#include "CommonConfig.h"





int GamePlayerScene::gamePath[7] = {};


GamePlayerScene::GamePlayerScene()
{

}


GamePlayerScene::~GamePlayerScene()
{
}

Scene * GamePlayerScene::createScene(const CellConfiguration &config, const DefenseConfiguration &defenConfig)
{
			auto scene = Scene::create();
			auto layer = GamePlayerScene::create(config,defenConfig);
			scene->addChild(layer);
			return scene;
}

GamePlayerScene * GamePlayerScene::create(const CellConfiguration &config, const DefenseConfiguration &defenConfig)
{
			GamePlayerScene *pRet = new GamePlayerScene();
			if (pRet && pRet->init(config,defenConfig))
			{
						pRet->autorelease();
			}
			else
			{
						delete pRet;
						pRet = nullptr;
			}
			return pRet;
}

bool GamePlayerScene::init(const CellConfiguration &config, const DefenseConfiguration &defenConfig)
{
			auto ret = false;
			do 
			{

						Layer::init();					
						
						m_cell_config = const_cast<CellConfiguration *>(&config);
						m_defense_config = const_cast<DefenseConfiguration *>(&defenConfig);



						initBackGround();

						initClippingNode();

						CC_BREAK_IF(!initCellLayer());

						CC_BREAK_IF(!initDefenseLayer());
						//createCellsForPlant();


					
						
						
						auto menuitem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [&](Ref *) {
									Director::getInstance()->end();
						});
						menuitem->setScale(1.0f);
						auto menu = Menu::create(menuitem, NULL);
						menu->setPosition(Vec2(winSize.width - menuitem->getBoundingBox().size.width / 2, winSize.height - menuitem->getBoundingBox().size.height / 2));

						addChild(menu);

					


						scheduleUpdate();
						ret = true;
			} while (0);
		
			return ret;
}









bool GamePlayerScene::initBackGround()
{
			auto ret = false;
			do
			{
						auto spr =  Sprite::create("operating_scenes.jpg");
						spr->setAnchorPoint(Vec2(0,0));
						auto dx = spr->getTextureRect().getMaxX();
						auto dy = spr->getTextureRect().getMaxY();
						auto wx = winSize.width;
						auto wy = winSize.height;
						_scalesizeX = wx / dx;
						_scalesizeY = wy / dy;
						spr->setScaleX((float)(wx / dx));
						spr->setScaleY((float)(wy / dy));
						//log("%lf ,%lf", spr->getTextureRect().getMaxX(), spr->getTextureRect().getMaxY());
						spr->setPosition(Vec2::ZERO);
						addChild(spr,-1,"backGround");
						ret = true;
			} while (0);
			return true;
}

bool GamePlayerScene::initClippingNode()
{
			auto ret = false;
			do 
			{
						_clipNode = ClippingNode::create();

						_clipNode->setInverted(false);

						_clipNode->setAlphaThreshold(0.0f);

						auto stencil = Node::create();

						auto drawnode = DrawNode::create();
						float coverY = towerArea - 10;
						Vec2 point[4]{ Vec2(0,0),Vec2(0,coverY),Vec2(winSize.width,coverY),Vec2(winSize.width,0) };
						drawnode->drawPolygon(point, 4, Color4F(1, 0, 0, 1), 1, Color4F(0, 1, 0, 1));

						stencil->addChild(drawnode, 1);

						_clipNode->setStencil(stencil);
						//_clipNode->setGlobalZOrder(10000);
						addChild(_clipNode);
						ret = true;
			} while (0);
			return ret;

	
}

bool GamePlayerScene::initCellLayer()
{
			auto ret = false;
			do 
			{
						_cellLayer = CellLayer::create(*m_cell_config);
						_clipNode->addChild(_cellLayer,10);
						ret = true;
			} while (0);

			return ret;
}

bool GamePlayerScene::initDefenseLayer()
{
			auto ret = false;
			do 
			{
						_defenseLayer = DefenseLayer::create(*m_defense_config);
						//_defenseLayer->setAnchorPoint(Point::ZERO);
						
						addChild(_defenseLayer,10);
						ret = true;
			} while (0);
			return ret;
}






bool GamePlayerScene::loadAnimate()
{
			return true;
}



void GamePlayerScene::onEnter()
{
			Layer::onEnter();
			do 
			{
						//CC_BREAK_IF();
			} while (0);
			
}

void GamePlayerScene::onExit()
{
			Layer::onExit();
			unscheduleUpdate();
			removeAllChildrenWithCleanup(true);		
}



bool GamePlayerScene::onTouchBegan(Touch * touch, Event * unused_event)
{
			return true;
}

void GamePlayerScene::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void GamePlayerScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}

void GamePlayerScene::onTouchCancelled(Touch * touch, Event * unused_event)
{
}

void GamePlayerScene::update(float dt)
{
			if(_cellLayer->getPlayerScore()!= m_recordCellScore && _defenseLayer->m_DefenseGameLogic!=nullptr)
			{
						_defenseLayer->m_DefenseGameLogic->acceptScore(_cellLayer->getPlayerScore() - m_recordCellScore);
						m_recordCellScore = _cellLayer->getPlayerScore();
			}
}
