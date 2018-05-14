#include "CellLayer.h"
#include "ObjectPoolManager.h"


CellLayer::CellLayer()
{
}


CellLayer::~CellLayer()
{
}

CellLayer * CellLayer::create(const CellConfiguration &config)
{
			auto celllayer = new (std::nothrow) CellLayer;
			if (celllayer && celllayer->init(config))
			{
						celllayer->autorelease();
			}
			else
			{
						delete celllayer;
						celllayer = nullptr;
			}
			return celllayer;
}

bool CellLayer::init(const CellConfiguration &config)
{
			auto ret = false;
			do 
			{
						displayAll(config);
						
						addGreyAndLightShader();
						
						auto listen = EventListenerTouchOneByOne::create();
						listen->onTouchBegan = CC_CALLBACK_2(CellLayer::onTouchBegan, this);
						listen->onTouchMoved = CC_CALLBACK_2(CellLayer::onTouchMoved, this);
						listen->onTouchEnded = CC_CALLBACK_2(CellLayer::onTouchEnded, this);
						listen->onTouchCancelled = CC_CALLBACK_2(CellLayer::onTouchCancelled, this);
						_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
						listen->setSwallowTouches(false);
						ret = true;
			} while (0);
			return ret;
}







void CellLayer::displayAll(const CellConfiguration & config)
{
			for (int i = 0; i < CellConfig_LocalCellCol; ++i)
			{

						for (int j = 0; j < CellConfig_LocalCellRow; ++j)
						{
									_cellsLogic[i][j] = Block::create(i, j, (CellColor)(config._localCell[i][j]));
									if (_cellsLogic[i][j] == nullptr)
									{
												continue;
									}
									displayCell(i, j, _cellsLogic[i][j], 0);
						}
			}
			for (int i = 0; i < CellConfig_PlateHorizontalCol; ++i)
			{

						for (int j = 0; j < CellConfig_PlateHorizontalRow; ++j)
						{
									_plateHorizontal[i][j] = Plate::create(i, j, (PlateColor)(config._plateHorizontal[i][j]));
									if (_plateHorizontal[i][j] == nullptr)
									{
												continue;
									}							
									//displayCell(i, j, _plateHorizontal[i][j], 1);
						}
			}
			for (int i = 0; i < CellConfig_PlateVecticalCol; ++i)
			{

						for (int j = 0; j < CellConfig_PlateVecticalRow; ++j)
						{
									_plateVertical[i][j] = Plate::create(i, j, (PlateColor)(config._plateVectical[i][j]));
									if (_plateVertical[i][j] == nullptr)
									{
												continue;
									}
									//displayCell(i, j, _plateVertical[i][j], 2);
						}
			}
			//有一个checkCell 如果没有格子可以消除，则重置格子
			restoreStalemate();
			if(_isTransformPos)
			{
						restoreAction();
			}
			auto seq = Sequence::create(DelayTime::create(3), Blink::create(3, 5), NULL);
			_recordCouldDesCell->runAction(seq);
			_isCanRunning = true;
}

void CellLayer::displayCell(int col, int row,Cell * cell, int orientation)
{
		if(cell==nullptr)
		{
					return;
		}
		else
		{
					Vec2 vc = coordinateToVec2(col, row);
					switch (orientation)
					{
					case 0:
								cell->setPosition(coordinateToVec2(col, row));						
								break;
					case 1:							
								cell->setPosition(vc.x, vc.y - row*(PlateVerticalLeftIdx));
								break;
					case 2:
								cell->setRotation(cell->getRotation()+90.0f);								
								cell->setPosition((vc.x - col*(PlateVerticalLeftIdx)), vc.y);
								break;
					default:
								log("0002:CellLayer-displayCell-type is wrong: %d", orientation);
								return;
								break;
					}
					addChild(cell, cell->getCellColor() + CellGlobalZorder::cellZorder);
		}
}

void CellLayer::restoreAction()
{
			if (!_isCanRunning)
			{
						for (auto &cells : _cellsLogic)
						{
									for (auto &cell : cells)
									{
												if(cell->_isCanMove && cell->_isCanSelected)
												{
															cell->stopAllActions();
															auto moveto = MoveTo::create(0.5f, coordinateToVec2(3, 2));
															auto moveback = MoveTo::create(0.5f, coordinateToVec2(cell->getColumn(), cell->getRow()));
															auto sequence_moveTo_moveBack = Sequence::create(moveto, moveback, NULL);
															cell->runAction(sequence_moveTo_moveBack);
												}												
									}
						}

			}
}



void CellLayer::restoreStalemate()
{
			//打乱格子排序
			if (!isStalemate())
			{
						std::vector<Cell *> mytestbak;
						for (auto col = 0; col < CellConfig_LocalCellCol; ++col)
						{
									for (auto row = 0; row < CellConfig_LocalCellRow; ++row)
									{
												if (_cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->_isCanSelected)
												{
															mytestbak.push_back(_cellsLogic[col][row]);
												}
									}
						}
						std::default_random_engine defaultEngine;
						std::shuffle(mytestbak.begin(), mytestbak.end(), defaultEngine);
						auto iter = mytestbak.begin();
						

						for(auto col=0;col<CellConfig_LocalCellCol;++col)
						{
									for(auto row=0;row<CellConfig_LocalCellRow;++row)
									{
												if(_cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->_isCanSelected)
												{
															(*iter)->setColumn(col);
															(*iter)->setRow(row);
															_cellsLogic[col][row] = *iter;
															++iter;
												}
									}
						}
						_isTransformPos = true;
						restoreStalemate();
			}
			else
			{
						return;
			}
}



//能否消除
int CellLayer::computeTheOneCell(std::vector<Cell *> &cells, Cell * cellCurrent, int count)
{
			if (cellCurrent == nullptr )
			{
						return count;
			}
			else
			{
						int num = 1;
						auto re = cellCurrent;					
						auto re2 = cells.begin();
						
						for (; re2 != cells.end(); ++re2)
						{
									if (((*re2)->getRow() == re->getRow() || (*re2)->getColumn() == re->getColumn()) && (*re2)->_isUsedLogic == false)
									{
												if (abs((*re2)->getColumn() - re->getColumn()) == 1 || abs((*re2)->getRow() - re->getRow()) == 1)
												{
															(*re2)->_isUsedLogic = true;
															re->_isUsedLogic = true;
															num += computeTheOneCell(cells, *re2, count);
												}
									}
									else if (((*re2)->getColumn() != re->getColumn() && (*re2)->getRow() != re->getRow()) && (*re2)->_isUsedLogic == false)
									{
												if (abs((*re2)->getColumn() - re->getColumn()) + abs((*re2)->getRow() - re->getRow()) == 2)
												{
															(*re2)->_isUsedLogic = true;
															re->_isUsedLogic = true;
															num += computeTheOneCell(cells, *re2, count);
												}
									}
									else
									{
												continue;
									}
						}


						if (num > count)
						{
									count = num;
						}
						return count;
			}
}


bool CellLayer::isStalemate()
{
			auto ret = false;
			do 
			{
						_recordCouldDesCell = nullptr;
						int reBak = 0;
						for(int colorRe=1; colorRe <=CellEliminateKind;++colorRe)
						{
									std::vector<Cell *> sameColorCell;
									sameColorCell.reserve(CellConfig_LocalCellCol*CellConfig_LocalCellRow);
									for (auto col = 0; col < CellConfig_LocalCellCol; ++col)
									{
												for (auto row = 0; row < CellConfig_LocalCellRow; ++row)
												{
															if (_cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->_isCanSelected && static_cast<int>(_cellsLogic[col][row]->getCellColor()) == colorRe)
															{
																		sameColorCell.push_back(_cellsLogic[col][row]);
															}
												}
									}

									auto isCan = 0;
									auto isCanBak = 0;
									//std::vector<Cells *> recordCell;

									for (unsigned int i = 0; i < sameColorCell.size(); ++i)
									{
												isCanBak = computeTheOneCell(sameColorCell, sameColorCell[i], 0);
												if (isCanBak > isCan)
												{
															isCan = isCanBak;
												}
												//log("color %d:  isCan %d", colorRe, isCanBak);
												if (isCan >= 3)
												{
															_recordCouldDesCell = sameColorCell[i];
															break;
												}
												isCanBak = 0;
												
									}


									for (auto &numtemp : sameColorCell)
									{
												numtemp->_isUsedLogic = false;
									}
									sameColorCell.clear();
									if (isCan >= 3)
									{
												ret = true;
												break;
									}
								
						}					
			} while (0);
			return ret;
}




void CellLayer::addGreyAndLightShader()
{
			std::string shader1 = FileUtils::getInstance()->getStringFromFile("example_GreyScale.fsh");
			GLProgramCache::getInstance()->addGLProgram(GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, shader1.c_str()), "grey_effect");
			std::string shader2 = FileUtils::getInstance()->getStringFromFile("example_LightScale.fsh");
			GLProgramCache::getInstance()->addGLProgram(GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, shader2.c_str()), "light_effect");
}

void CellLayer::onEnter()
{
			Layer::onEnter();
}

void CellLayer::onExit()
{
			Layer::onExit();
}

bool CellLayer::onTouchBegan(Touch * touch, Event * unused_event)
{
			auto ret = false;
			do 
			{
						
						ret = true;
			} while (0);
			return ret;
}

void CellLayer::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void CellLayer::onTouchEnded(Touch * touch, Event * unused_event)
{
}

void CellLayer::onTouchCancelled(Touch * touch, Event * unused_event)
{
}
