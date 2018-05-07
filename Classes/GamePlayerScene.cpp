#include "GamePlayerScene.h"
#include "PlayerData.h"



int GamePlayerScene::gamePath[7] = {};


GamePlayerScene::GamePlayerScene()
{
			
}


GamePlayerScene::~GamePlayerScene()
{
}

Scene * GamePlayerScene::createScene()
{
			auto scene = Scene::create();
			auto layer = GamePlayerScene::create();
			scene->addChild(layer);
			return scene;
}

GamePlayerScene * GamePlayerScene::create()
{
			GamePlayerScene *pRet = new GamePlayerScene();
			if (pRet && pRet->init())
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

bool GamePlayerScene::init()
{
			Layer::init();	
			srand((unsigned int)(time(NULL)));

			//Ԥ���ض���
			loadAnimate();
		
			//��ʼ�������Ϣ
			{
						_playerInstance = PlayerData::getInstancePlayerData();
						
						addChild(_playerInstance,20);
			}

			//���background
			
			initBackGround();

			initClippingNode();
			
			//��ʼ��������ģ��
			createCellsForPlant();
		


			
			
			
			
			
			
			////����ʼ��-->�ӵ�Ԥ����	
			createTower();
	
			////���޳�ʼ��
			createMonster();
	
			////����ӵ�
			//createAndBindBullet();
			//static int __i = 0;
			//schedule([&] (float dt){			
			//			++__i;
			//			_layerTower->moveTower(__i);
			//			if (__i == 4)
			//			{
			//						__i = -1;
			//			}
			//}, 2.0f,-1,2.0f,"moveTower");
			//
			////��Ӵ���

			{
						//��ӵ���
						_playerInstance->addShuffleCellMenu(_layerCells);
			}		
			scheduleUpdate();

			auto menuitem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [&](Ref *) {
						Director::getInstance()->end();
			});
			menuitem->setScale(1.0f);
			auto menu = Menu::create(menuitem, NULL);
			menu->setPosition(Vec2(winSize.width - menuitem->getBoundingBox().size.width / 2, winSize.height - menuitem->getBoundingBox().size.height / 2));

			addChild(menu);
			return true;
}

bool GamePlayerScene::createTower()
{
			auto ret = false;
			do
			{
						auto tower = LayerTower::create();
						tower->setTag(1100);
						addChild(tower, 20,"ToweLay");
						_layerTower = tower;
					
						ret = true;
			} while (0);
			return ret;
}





bool GamePlayerScene::createMonster()
{
			auto ret = false;
			do
			{
						auto mons = LayerMonster::create();
						addChild(mons, 10);
						_layerMonster = mons;
						ret = true;
			} while (0);
			return ret;
}

bool GamePlayerScene::createAndBindBullet()
{
			auto ret = false;
			do
			{
						
						ret = true;
			} while (0);

			return ret;
}

bool GamePlayerScene::createCellsForPlant()
{
			auto ret = false;
			do 
			{

						auto cellLayer = CellsLayer::create();
						_clipNode->addChild(cellLayer,200);
						cellLayer->setPosition(_clipNode->convertToNodeSpace(Point::ZERO) );
						_layerCells = cellLayer;
						
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
						addChild(spr,1,"backGround");
						ret = true;
			} while (0);
			return true;
}

void GamePlayerScene::initClippingNode()
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

			addChild(_clipNode, 2);
	
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
			
}

void GamePlayerScene::onExit()
{
			Layer::onExit();
}

void GamePlayerScene::update(float dt)
{


			{

						//if (_layerMonster->_monsterVec.size())
						//{
						//			auto layerbul = static_cast<LayerBullet *>(_layerTower->_bulletLayer);
						//			auto mons = _layerMonster->_monsterVec.front();
						//			//auto pos = amendMonsterPositon(_layerMonster->_monsterVec.front()->getPos());
						//			//DrawSpriteFrame::drawSpriteFrame(mons->getSprite());
						//			
						//			
						//			if (_layerCells->_cellScore >= 0 && ! (_layerTower->_tower->getIsAttacked()) && mons->getLife()>0)
						//			{
						//						log("mos: %d", _layerMonster->_monsterVec.size());
						//						log("bullet : %d", _layerTower->_bulletLayer->_bulletVec.size());
						//						_layerCells->_cellScore = 0;
						//						_layerTower->moveTower(mons->getPos());
						//			}
						//			if (layerbul->_bulletVec.size())
						//			{										
						//					
						//						/*auto draw1 = DrawNode::create();
						//						draw1->drawRect(Vec2(layerbul->_bulletVec.front()->getBoundingBox().getMinX(), layerbul->_bulletVec.front()->getBoundingBox().getMinY()), Vec2(layerbul->_bulletVec.front()->getBoundingBox().getMaxX(), layerbul->_bulletVec.front()->getBoundingBox().getMaxY()), Color4F::GREEN);
						//						layerbul->_bulletVec.front()->addChild(draw1);*/
						//						for (auto bullet : layerbul->_bulletVec)
						//						{
						//									if (bullet->getBoundingBox().intersectsRect(mons->getBoundingBox()) && (bullet->getLife() > 0) && (mons->getLife()>0))
						//									{
						//												bullet->loseLife();
						//												auto score = _layerMonster->updateMonsLife(mons, 1);
						//												_playerInstance->addScore(score);
						//												break;
						//									}
						//						}


						//						

						//									//if (layerbul->_bulletVec.back()->getBoundingBox().intersectsRect(mons->getBoundingBox())&& layerbul->_bulletVec.front()->getLife()>0)
						//									//{

						//									//			/*auto draw2 = DrawNode::create();
						//									//			draw2->drawRect(Vec2(mons->getBoundingBox().getMinX(), mons->getBoundingBox().getMinY()), Vec2(mons->getBoundingBox().getMaxX(), mons->getBoundingBox().getMaxY()), Color4F::GREEN);
						//									//			mons->addChild(draw2);*/

						//									//			
						//									//			layerbul->_bulletVec.back()->loseLife();
						//									//			auto score=_layerMonster->monsterDeath(mons);
						//									//			_playerInstance->addScore(score);
						//									//}												
						//			}
						//			/*if (_layerTower->_tower->getBoundingBox().intersectsRect(mons->getBoundingBox()) && mons->getLife() > 0)
						//			{
						//						
						//						_layerMonster->updateMonsLife(mons, 1);
						//						_layerTower->_tower->loseLife();
						//			}*/
						//}



						/////////////////////////////////////////////////////////////////////////////////////////////////////////
						//test for move tower
						/*if (_layerCells->_cellScore >= 3 && !(_layerTower->_tower->getIsAttacked()) && _layerMonster->_monsterVec.size())
						{
									Monster *monsfront=nullptr;
									for (auto mons: _layerMonster->_monsterVec)
									{
												if (mons->getLife() > 0)
												{
															monsfront = mons;
															break;
												}
									}
									if (monsfront == nullptr)
									{
												return;
									}
									_layerCells->_cellScore -=3;
									_layerTower->moveTower(monsfront->getPos());

						}
						if (_layerMonster->_monsterVec.size() && _layerTower->_bulletLayer->_bulletVec.size())
						{
									for (auto mons : _layerMonster->_monsterVec)
									{
												for (auto bullet : _layerTower->_bulletLayer->_bulletVec)
												{

															if (static_cast<Monster *>(mons)->getLife() > 0 && (static_cast<Bullet*> (bullet)->getLife() > 0))
															{
																		if (bullet->getBoundingBox().intersectsRect(mons->getBoundingBox()))
																		{
																					bullet->loseLife();
																					auto score = _layerMonster->updateMonsLife(mons, 1);
																					_playerInstance->addScore(score);
																					break;
																		}
															}


												}
									}
						}

						for (auto mons : _layerMonster->_monsterVec)
						{
									if (_layerTower->_tower->getBoundingBox().intersectsRect(mons->getBoundingBox()) && mons->getLife() > 0)
									{

												_layerMonster->updateMonsLife(mons, 1);
												_layerTower->_tower->loseLife();
									}
						}*/
						///////////////////////////////////////////////////////////////////////////////////////////////
						//test for 5 build tower
						if ( _layerMonster->_monsterVec.size())
						{								
									for (auto mons : _layerMonster->_monsterVec)
									{
												if (mons->getLife() > 0 && _layerCells->_cellScore >= 3)
												{																											
															if (_layerTower->chechTowerPosAndAttack(mons->getPos()))
															{
																		_layerCells->_cellScore -= 3;
															}
												}
									}
						}
						if (_layerMonster->_monsterVec.size() && _layerTower->_bulletLayer->_bulletVec.size())
						{
									for (auto mons : _layerMonster->_monsterVec)
									{
												for (auto bullet : _layerTower->_bulletLayer->_bulletVec)
												{

															if (static_cast<Monster *>(mons)->getLife() > 0 && (static_cast<Bullet*> (bullet)->getLife() > 0))
															{
																		if (bullet->getBoundingBox().intersectsRect(mons->getBoundingBox()))
																		{
																					bullet->loseLife();
																					_layerTower->_bulletLayer->bulletCrashWithMonster(bullet, mons->getSprite()->getPosition());
																					auto score = _layerMonster->updateMonsLife(mons, 1);
																					_playerInstance->addScore(score);
																					break;
																		}
															}


												}
									}
						}

						for (auto mons : _layerMonster->_monsterVec)
						{
									for (auto tow : _layerTower->_towerVec)
									{
												if (tow->getLife() >= 0 && mons->getLife() > 0 && tow->getBoundingBox().intersectsRect(mons->getBoundingBox()))
												{

															_layerMonster->updateMonsLife(mons, 1);
															tow->loseLife();
												}
									}

						}



			}

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
