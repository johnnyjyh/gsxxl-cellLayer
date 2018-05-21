#include "GamePlayScene.h"




int GamePlayerScene::gamePath[7] = {};


GamePlayerScene::GamePlayerScene()
{
			
}


GamePlayerScene::~GamePlayerScene()
{
}

Scene * GamePlayerScene::createScene(const CellConfiguration &config)
{
			auto scene = Scene::create();
			auto layer = GamePlayerScene::create(config);
			scene->addChild(layer);
			return scene;
}

GamePlayerScene * GamePlayerScene::create(const CellConfiguration &config)
{
			GamePlayerScene *pRet = new GamePlayerScene();
			if (pRet && pRet->init(config))
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

bool GamePlayerScene::init(const CellConfiguration &config)
{
			auto ret = false;
			do 
			{
						Layer::init();
						_config = const_cast<CellConfiguration *>(&config);

						loadAnimate();

						initBackGround();

						initClippingNode();

						CC_BREAK_IF(!initCellLayer());
						//createCellsForPlant();

						auto menuitem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [&](Ref *) {
									Director::getInstance()->end();
						});
						menuitem->setScale(1.0f);
						auto menu = Menu::create(menuitem, NULL);
						menu->setPosition(Vec2(winSize.width - menuitem->getBoundingBox().size.width / 2, winSize.height - menuitem->getBoundingBox().size.height / 2));

						addChild(menu);
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
						addChild(_clipNode, 2);
						ret = true;
			} while (0);
			return ret;

	
}

bool GamePlayerScene::initCellLayer()
{
			auto ret = false;
			do 
			{
						_cellLayer = CellLayer::create(*_config);
						_clipNode->addChild(_cellLayer);
						ret = true;
			} while (0);

			return ret;
}




bool GamePlayerScene::loadAnimate()
{
			auto ret = false;
			do
			{
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("battery_attack/tower_create.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower/tower_bullet_attack.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower/tower_bullet_burst.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pumpkin_walk/pumpkin_walk.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pumpkin_rest/pumpkin_reset.plist");						
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pumpkin_death/pumpkin_death.plist");			
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tiled/tiled.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower/tower_life.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("playerItem/lifeItem.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tiled/barrier.plist");
						
						ret = true;
			} while (0);
			
			return ret;
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
