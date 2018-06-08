#include "CellLayer.h"



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
						addGreyAndLightShader();

						displayAll(config);
						
						_playerAcquireScoreForCell = 0;
						
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
									_plateHorizontal[i][j] = Plate::create(i, j, (CellColor)(config._plateHorizontal[i][j]));
									if (_plateHorizontal[i][j] == nullptr)
									{
												continue;
									}							
									displayCell(i, j, _plateHorizontal[i][j], 1);
						}
			}
			for (int i = 0; i < CellConfig_PlateVecticalCol; ++i)
			{

						for (int j = 0; j < CellConfig_PlateVecticalRow; ++j)
						{
									_plateVertical[i][j] = Plate::create(i, j, (CellColor)(config._plateVectical[i][j]));
									if (_plateVertical[i][j] == nullptr)
									{
												continue;
									}
									displayCell(i, j, _plateVertical[i][j], 2);
						}
			}
			//有一个checkCell 如果没有格子可以消除，则重置格子



			restoreStalemate();
			if(_isTransformPos)
			{
						restoreAction();
			}
			if(_recordCouldDesCell!=nullptr)
			{
						hintTheUsableCell(_recordCouldDesCell);
			}

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
								cell->setPosition(vc);						
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

void CellLayer::hintTheUsableCell(Cell * cell)
{
			if(cell==nullptr)
			{
						log("0005:CellLayer-hintTheUsableCell cell==nullptr!");
						return;
			}
			else
			{
						auto seq = Sequence::create(DelayTime::create(3), Blink::create(3, 5), NULL);
						seq->setTag(cell->getColumn() + cell->getRow() + blinkTag);
						cell->runAction(seq);
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
												if(cell!=nullptr &&cell->_isCanMove && cell->_isCanSelected)
												{
															cell->stopAllActions();
															//DelayTime *deltime = DelayTime::create((float)(CellConfig_CellSpeed)*(_stepOuterTime > 1 ? _stepOuterTime - 1 : 1));
															auto moveto = MoveTo::create(0.5f, coordinateToVec2(3, 2));
															auto moveback = MoveTo::create(0.5f, coordinateToVec2(cell->getColumn(), cell->getRow()));
															auto sequence_moveTo_moveBack = Sequence::create(moveto, moveback, NULL);
															cell->runAction(sequence_moveTo_moveBack);
												}												
									}
						}
						_isTransformPos = false;

			}
}



void CellLayer::restoreStalemate()
{
			//打乱格子排序
			if (!isStalemate())
			{
						++_stalemateCellCount;
						if(_stalemateCellCount>=10)
						{
									return;
						}
						std::vector<Cell *> mytestbak;
						for (auto col = 0; col < CellConfig_LocalCellCol; ++col)
						{
									for (auto row = 0; row < CellConfig_LocalCellRow; ++row)
									{
												if (_cellsLogic[col][row]!=nullptr &&_cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->_isCanSelected)
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
												if(_cellsLogic[col][row]!=nullptr && _cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->_isCanSelected)
												{
															(*iter)->setColumn(col);
															(*iter)->setRow(row);
															_cellsLogic[col][row] = *iter;
															++iter;
												}
									}
						}				
						restoreStalemate();		
						_isTransformPos = true;
						_stalemateCellCount = 0;
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
						int maxline =0;
						auto re = cellCurrent;					
						auto re2 = cells.begin();
						
						for (; re2 != cells.end(); ++re2)
						{
								
									auto cellnow = *re2;
									auto cellpre = cellCurrent;
									if (cellnow->getLife() > 0  && pow(cellnow->getRow() - cellpre->getRow(), 2) + pow(cellnow->getColumn() - cellpre->getColumn(), 2) <= 2)
									{
												
												if (cellnow->getRow() == cellpre->getRow() && cellnow->getColumn() == cellpre->getRow())
												{
															continue;
												}
												if ((std::abs(cellnow->getColumn() - cellpre->getColumn()) + std::abs(cellnow->getRow() - cellpre->getRow())) == 1)
												{
															if (cellnow->getColumn() == cellpre->getColumn())
															{
																		auto maxrow = cellnow->getRow() > cellpre->getRow() ? cellnow->getRow() : cellpre->getRow();
																		if (_plateHorizontal[cellnow->getColumn()][maxrow] != nullptr)
																		{
																					continue;
																		}
															}
															else if (cellnow->getRow() == cellpre->getRow())
															{
																		auto maxcol = cellnow->getColumn() > cellpre->getColumn() ? cellnow->getColumn() : cellpre->getColumn();
																		if (_plateVertical[maxcol][cellnow->getRow()] != nullptr)
																		{
																					continue;
																		}

															}
												}
												else
												{
															if (cellpre->getRow() > cellnow->getRow())
															{
																		if (cellpre->getColumn() > cellnow->getColumn())
																		{
																					if (!TouchCellCanMoveLeft(cellpre))
																					{
																								continue;
																					}
																		}
																		else if (cellpre->getColumn() < cellnow->getColumn())
																		{
																					if (!TouchCellCanMoveRight(cellpre))
																					{
																								continue;
																					}
																		}
															}
															else if (cellpre->getRow() < cellnow->getRow())
															{
																		if (cellpre->getColumn() > cellnow->getColumn())
																		{
																					if (!TouchCellCanMoveRight(cellnow))
																					{
																								continue;
																					}
																		}
																		else if (cellpre->getColumn() < cellnow->getColumn())
																		{
																					if (!TouchCellCanMoveLeft(cellnow))
																					{
																								continue;
																					}
																		}
															}
												}












												if (cellnow->_isUsedLogic == false)
												{					
															auto numbak = num;
															cellnow->_isUsedLogic = true;
															num += computeTheOneCell(cells, cellnow, count);
															if(num>maxline)
															{
																		maxline = num;
																		if(maxline>=3)
																		{
																					break;
																		}
															}
															num = numbak;
															cellnow->_isUsedLogic = false;														
												}
												//回归初始状态
												

												/*if (((*re2)->getRow() == re->getRow() || (*re2)->getColumn() == re->getColumn()) && (*re2)->_isUsedLogic == false)
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
												}*/
									}
						}

						if (maxline > count)
						{
									count = maxline;
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
															if (_cellsLogic[col][row]!=nullptr &&_cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->_isCanSelected && static_cast<int>(_cellsLogic[col][row]->getCellColor()) == colorRe)
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
												sameColorCell[i]->_isUsedLogic = false;
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

void CellLayer::linkLineInGrid(int col1, int row1, int col2, int row2)
{
			Vec2 pos1, pos2;
			pos1.set(coordinateToVec2(col1, row1));
			pos2.set(coordinateToVec2(col2, row2));
			auto line = DrawNode::create();
			line->drawLine(pos1, pos2, Color4F::BLACK);
			_linkLineCache.push_back(line);
			addChild(line, LineZorder::line);
}

void CellLayer::unLinkLineInGrid(int col1, int row1, int col2, int row2)
{
			if (!_linkLineCache.size())
			{
						return;
			}
			auto & line = _linkLineCache.back();
			if (line)
			{
						line->removeFromParentAndCleanup(true);
			}
			_linkLineCache.pop_back();
}




Cell * CellLayer::getCellFromTable(int col, int row) noexcept
{

			if (col<0 || col>CellConfig_LocalCellCol - 1 || row<0 || row>CellConfig_LocalCellRow-1)
			{
						return nullptr;
			}
			return _cellsLogic[col][row];

}

void CellLayer::grantAttackTypeForCell()
{
			std::vector<Cell *>cellsKeeper;
			for (const auto &cells : _cellsLogic)
			{
						for (const auto &cell : cells)
						{									
									if(cell!=nullptr && cell->getLife()>0 && (static_cast<int>(cell->getCellColor())>0&& static_cast<int>(cell->getCellColor()) <=CellEliminateKind)&&cell->_iAttack==1)
									{
												cellsKeeper.push_back(cell);
									}
						}
			}
			std::default_random_engine eng;
			std::default_random_engine eng2;
			std::uniform_int_distribution<int> distype(2, 4);
			std::uniform_int_distribution<int> discell(0, cellsKeeper.size()-1);
			auto attacktype = std::bind(distype, eng);
			auto cellnum = std::bind(discell, eng2);
			int num = cellnum();
			//int type = attacktype();
		
			srand((unsigned)time(NULL));
			cellsKeeper[num]->_iAttack = random(2, 4);

			//处理动作
			Sprite *spr = nullptr;
			if(cellsKeeper[num]->_iAttack ==2)
			{
						spr = Sprite::createWithSpriteFrameName("operating_obstacle_008.png");
			}
			else if(cellsKeeper[num]->_iAttack ==3)
			{
						spr = Sprite::createWithSpriteFrameName("operating_obstacle_006.png");
			}
			else if(cellsKeeper[num]->_iAttack ==4)
			{
						spr = Sprite::createWithSpriteFrameName("operating_obstacle_007.png");
			}
			//spr->setScale(getSingleTiledSize.x / spr->getContentSize().width);
			//spr->retain();
			/*auto func = CallFuncN::create([=](Node *node) {
						node->addChild(spr);
			});		*/
			//DelayTime *deltime = DelayTime::create((float)0.32*(CellConfig_CellSpeed)*(_stepOuterTime > 1 ? _stepOuterTime - 1 : 1));
		//	auto seq = Sequence::create( func, NULL);
			cellsKeeper[num]->addChild(spr, ItemGlobalZorder::itemZorder + cellsKeeper[num]->getCellColor());
			cellsKeeper.clear();
}

void CellLayer::attackFromSource()
{
			//for(const auto &cells:_cellsLogic)
			//{
			//			for(const auto&cell:cells)
			//			{
			//						if(cell!=nullptr&&cell->getLife()>0)
			//						{
			//									for (const auto &desCell : _touchMoveCells)
			//									{
			//												if(cell->getRow()==desCell->getRow() &&cell->getColumn()==desCell->getColumn())
			//												{
			//															continue;
			//												}
			//												if (desCell->_iAttack == 1)
			//												{
			//															if (cell->getCellColor()>CellEliminateKind&&cell->_isCanBeAtteckted&&std::abs(cell->getRow() - desCell->getRow()) + std::abs(cell->getColumn() - desCell->getColumn()) == 1)
			//															{
			//																		cell->loseLife();
			//															}
			//												}
			//												else if(desCell->_iAttack==2)
			//												{
			//															if(cell->getRow()==desCell->getRow()&&std::abs(cell->getColumn()-desCell->getColumn())<=2 )
			//															{
			//																		cell->loseLife();
			//															}
			//															for(const auto &plates:_plateVertical)
			//															{
			//																		for(const auto &plate:plates)
			//																		{
			//																					if(plate!=nullptr&&plate->_isCanBeAtteckted&&plate->getLife()>0&&plate->getRow()==desCell->getRow()&&std::abs(plate->getColumn()-desCell->getColumn())<=2)
			//																					{
			//																								plate->loseLife();
			//																					}
			//																		}
			//															}

			//												}
			//												else if(desCell->_iAttack==3)
			//												{
			//															if(cell->getColumn()==desCell->getColumn() &&std::abs(cell->getRow()-desCell->getRow())<=2)
			//															{
			//																		cell->loseLife();
			//															}
			//															for(const auto &plates:_plateHorizontal)
			//															{
			//																		for(const auto &plate:plates)
			//																		{
			//																					if(plate!=nullptr &&plate->_isCanBeAtteckted&& plate->getLife()>0 && plate->getColumn()==desCell->getColumn() &&std::abs(plate->getRow()-desCell->getRow())<=2)
			//																					{
			//																								plate->loseLife();
			//																					}
			//																		}
			//															}
			//												}
			//												else if(desCell->_iAttack==4)
			//												{

			//												}
			//												//其他攻击
			//									}
			//						}
			//						else
			//						{
			//									continue;
			//						}
			//						
			//			}
			//}

			//for(const auto &plates:_plateVertical)
			//{
			//			for(const auto &plate:plates)
			//			{
			//						if(plate!=nullptr&&plate->_isCanBeAtteckted&&plate->getLife()>0)
			//						{
			//									for(const auto &desCell:_touchMoveCells)
			//									{
			//												if((plate->getColumn()==desCell->getColumn() || plate->getColumn()==desCell->getColumn()+1)&&plate->getRow()==desCell->getRow())
			//												{
			//															plate->loseLife();
			//												}
			//									}
			//						}
			//			}

			//}

			//for (const auto &plates : _plateHorizontal)
			//{
			//			for (const auto &plate : plates)
			//			{
			//						if (plate != nullptr&&(plate->_isCanBeAtteckted && plate->getLife()>0))
			//						{
			//									for (const auto &desCell : _touchMoveCells)
			//									{
			//												if (plate->getColumn() == desCell->getColumn() && (plate->getRow() == desCell->getRow()|| plate->getRow()==desCell->getRow()+1))
			//												{
			//															plate->loseLife();
			//												}
			//									}
			//						}
			//			}

			//}
			for(const auto &desCell:_touchMoveCells)
			{
						if(desCell!=nullptr && desCell->getLife()>0&&desCell->_isCanBeAtteckted)
						{
									attackFromDesCell(desCell);
						}
			}
			
}

Cell * CellLayer::getVerticalPlate(int col, int row)
{
			if(col<0||col>=CellConfig_PlateVecticalCol||row<0||row>=CellConfig_PlateVecticalRow)
			{
						return nullptr;
			}
			return _plateVertical[col][row];
}

Cell * CellLayer::getHorizontalPlate(int col, int row)
{
			if(col<0|| col>=CellConfig_PlateHorizontalCol || row<0||row>=CellConfig_PlateHorizontalRow)
			{
						return nullptr;
			}
			return _plateHorizontal[col][row];
}

void CellLayer::attackFromDesCell(Cell * cell)
{
			if(cell==nullptr)
			{
						return;
			}
			else
			{
						if(cell->_iAttack==1)
						{
									Cell *beattcell = nullptr;
									Cell *beattPlate = nullptr;
									int verCol = 0;
									int verColMax = 0;
									beattPlate = getVerticalPlate(cell->getColumn(), cell->getRow());
									if(beattPlate!=nullptr&&beattPlate->getLife()>0)
									{
												verCol = 0;
												if(beattPlate->_isCanBeAtteckted)
												{
															beattPlate->loseLife();
												}
									}
									else
									{
												verCol = -1;
									}
									beattPlate = getVerticalPlate(cell->getColumn() + 1, cell->getRow());
									if (beattPlate != nullptr&&beattPlate->getLife() > 0)
									{
												verColMax = 0;
												if (beattPlate->_isCanBeAtteckted)
												{
															beattPlate->loseLife();
												}
									}
									else
									{
												verColMax = 1;
									}
									for(int i=cell->getColumn()+verCol;i<= cell->getColumn() + verColMax;++i)
									{
												beattcell = getCellFromTable(i, cell->getRow());
												if(beattcell!=nullptr &&static_cast<int>(beattcell->getCellColor())>CellEliminateKind &&beattcell->getLife()>0 && beattcell->_isCanBeAtteckted)
												{
															beattcell->loseLife();
												}
									}
									
									/////////////////////////////////////
									int honRow = 0;
									int honRowMax = 0;

									beattcell = nullptr;
									beattPlate = getHorizontalPlate(cell->getColumn(), cell->getRow());									
									if (beattPlate != nullptr&&beattPlate->getLife() > 0)
									{
												honRow = 0;
												if (beattPlate->_isCanBeAtteckted)
												{
															beattPlate->loseLife();
												}
									}
									else
									{
												honRow = -1;
									}
									beattPlate = getHorizontalPlate(cell->getColumn() , cell->getRow()+1);
									if (beattPlate != nullptr&&beattPlate->getLife() > 0)
									{
												honRowMax = 0;
												if (beattPlate->_isCanBeAtteckted)
												{
															beattPlate->loseLife();
												}
									}
									else
									{
												honRowMax = 1;
									}
									for (int i = cell->getRow()+ honRow; i <= cell->getRow() + honRowMax; ++i)
									{
												beattcell = getCellFromTable(cell->getColumn(),i);
												if (beattcell != nullptr &&static_cast<int>(beattcell->getCellColor()) > CellEliminateKind &&beattcell->getLife() > 0 && beattcell->_isCanBeAtteckted)
												{
															beattcell->loseLife();
												}
									}
									
						}
						else if(cell->_iAttack==2)
						{
									Cell *beattcell = nullptr;
									Cell *beattPlate = nullptr;
									for(int i=cell->getColumn()-2;i<=cell->getColumn()+2;++i)
									{
												beattcell = getCellFromTable(i, cell->getRow());
												if(beattcell!=nullptr&&beattcell->getLife()>0&&beattcell->_isCanBeAtteckted)
												{
															beattcell->loseLife();
															if(beattcell->_iAttack>0)
															{
																		attackFromDesCell(beattcell);
															}
												}
												beattPlate = getVerticalPlate(i, cell->getRow());
												if (beattPlate != nullptr&&beattPlate->getLife() > 0 && beattPlate->_isCanBeAtteckted)
												{
															beattPlate->loseLife();
												}											
									}
						}
						else if(cell->_iAttack==3)
						{
									Cell *beattcell = nullptr;
									Cell *beattPlate = nullptr;
									for (int i = cell->getRow() - 2; i <= cell->getRow() + 2; ++i)
									{
												beattcell = getCellFromTable(cell->getColumn(), i);
												if (beattcell != nullptr&&beattcell->getLife() > 0 && beattcell->_isCanBeAtteckted)
												{
															beattcell->loseLife();
															if (beattcell->_iAttack >0)
															{
																		attackFromDesCell(beattcell);
															}
												}
												beattPlate = getHorizontalPlate(cell->getColumn(), i);
												if (beattPlate != nullptr&&beattPlate->getLife() > 0 && beattPlate->_isCanBeAtteckted)
												{
															beattPlate->loseLife();
												}
									}
						}
						else if(cell->_iAttack==4)
						{
									Cell *beattcell = nullptr;
									for(int i=cell->getColumn()-1;i<=cell->getColumn()+1;++i)
									{
												for(int j=cell->getRow()-1;j<=cell->getRow()+1;++j)
												{
															beattcell = getCellFromTable(i, j);
															if(i==cell->getColumn() && j==cell->getRow())
															{																		
																		continue;
															}
															if(beattcell!=nullptr&&beattcell->getLife()>0 && (static_cast<int>(beattcell->getCellColor())>0&&static_cast<int>(beattcell->getCellColor())<=7)&&beattcell->_iAttack>0)
															{
																		beattcell->setNewColor(static_cast<int>(cell->getCellColor()));
															}
												}
									}
									
						}
						if (cell->getLife() > 0)
						{
									cell->loseLife();
						}
			}
}

void CellLayer::fillUpCellOnTop()
{
			bool transform = false;
			for(int i=0;i<CellConfig_LocalCellCol;++i)
			{
						if(_cellsLogic[i][CellConfig_LocalCellRow-1]->getLife()<1 &&_plateHorizontal[i][CellConfig_PlateHorizontalRow-1]==nullptr )
						{
									//开始补格子
									auto pos = coordinateToVec2(i, CellConfig_LocalCellRow);								
									//补格子
									_cellsLogic[i][CellConfig_LocalCellRow - 1]=srandColorForNewCell(_cellsLogic[i][CellConfig_LocalCellRow - 1]);
									
									if(_cellsLogic[i][CellConfig_LocalCellRow - 1]!=nullptr)
									{
												_cellsLogic[i][CellConfig_LocalCellRow - 1]->setPosition(Vec2(pos.x, pos.y + 20));
												//创建移动步伐
												auto moveto = MoveTo::create((float)CellConfig_CellSpeed, coordinateToVec2(_cellsLogic[i][CellConfig_LocalCellRow - 1]->getColumn(), _cellsLogic[i][CellConfig_LocalCellRow - 1]->getRow()));
												DelayTime *deltime = nullptr;
												if (!_cellsLogic[i][CellConfig_LocalCellRow - 1]->_moveActionVec.empty())
												{
															deltime = DelayTime::create(0);
												}
												else
												{
															deltime = DelayTime::create((float)0.65*(CellConfig_CellSpeed)*(_stepOuterTime>1?_stepOuterTime-1:1));
												}												
												auto seq = Sequence::create(deltime, moveto, NULL);
												_cellsLogic[i][CellConfig_LocalCellRow - 1]->_moveActionVec.pushBack(seq);
												transform = true;
									}
									else
									{
												log("0009:CellLayer-fillUpCellOnTop-_cellsLogic[i][CellConfig_LocalCellRow - 1]==nullptr!");
									}
								
						}
			}
			if(transform)
			{
						controlDrop();
						fillUpCellOnTop();
			}
}

void CellLayer::coorVecClear()
{

}

void CellLayer::swapCell(int sourceCol, int sourceRow, int destCol, int destRow)
{
			if(getCellFromTable(sourceCol,sourceRow) ==nullptr || getCellFromTable(destCol,destRow)==nullptr)
			{
						return;
			}
			Cell *cellbak = _cellsLogic[sourceCol][sourceRow];
			int colbak = _cellsLogic[sourceCol][sourceRow]->getColumn();
			int rowbak = _cellsLogic[sourceCol][sourceRow]->getRow();

			_cellsLogic[sourceCol][sourceRow]->setRow(_cellsLogic[destCol][destRow]->getRow());
			_cellsLogic[sourceCol][sourceRow]->setColumn(_cellsLogic[destCol][destRow]->getColumn());

			_cellsLogic[destCol][destRow]->setRow(rowbak);
			_cellsLogic[destCol][destRow]->setColumn(colbak);

			_cellsLogic[sourceCol][sourceRow] = _cellsLogic[destCol][destRow];
			_cellsLogic[destCol][destRow] = cellbak;


}

void CellLayer::controlDrop()
{
			//开始i降落
			dropDownCell();
			//获取移动队列动画,按步数播放移动队列
			if(!_cellMoveToCoor.empty())
			{
						for(unsigned int i=0;i<_cellMoveToCoor.size();++i)
						{
									auto moveto = MoveTo::create((float)CellConfig_CellSpeed, coordinateToVec2(_cellMoveToCoor[i]._destCol, _cellMoveToCoor[i]._destRow));									
									DelayTime *deltime = nullptr;
									if(!_cellMoveToCoor[i]._sourceCell->_moveActionVec.empty())
									{
												deltime = DelayTime::create(0);
									}
									else
									{
												deltime = DelayTime::create((float)0.65*(CellConfig_CellSpeed)*(_cellMoveToCoor[i]._stepsLev));
									}
									auto seq = Sequence::create(deltime,moveto,NULL);
									_cellMoveToCoor[i]._sourceCell->_moveActionVec.pushBack(seq);	
						}

						_cellMoveToCoor.clear();
						
			}
			
}

void CellLayer::animateControl()
{
			for (const auto &cells : _cellsLogic)
			{
						for (const auto &cell : cells)
						{
									if (!cell->_moveActionVec.empty())
									{
										
												cell->stopAllActions();
												auto seq = Sequence::create(cell->_moveActionVec);
												cell->runAction(seq);
												cell->_moveActionVec.clear();
												
									}
						}
			}



}

void CellLayer::dropDownCell()
{
			//调用逻辑类 计算结果
			//返回结果 操作格子移动
			_dropDownTransformPos = false;
			for(auto col=0;col<CellConfig_LocalCellCol;++col)
			{									
						for(auto row = 0;row<CellConfig_LocalCellRow;++row)
						{
									if(_cellsLogic[col][row]!=nullptr && _cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->getLife()>0)
									{					
												getDrowDownTrackCell(_cellsLogic[col][row]);
											
									}
						}					
			}
		
			if(_dropDownTransformPos)
			{
						++_stepOuterTime;
						dropDownCell();
			}
			else
			{
						dropRightCell();
			}
}

void CellLayer::dropLeftCell()
{
			_dropDownTransformPos = false;
			for (auto col = 0; col < CellConfig_LocalCellCol; ++col)
			{
						for (auto row = 0; row < CellConfig_LocalCellRow; ++row)
						{
									if (_cellsLogic[col][row] != nullptr && _cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->getLife() > 0)
									{												
												getDrowLeftTrackCell(_cellsLogic[col][row]);	
												if (_dropDownTransformPos)
												{
															++_stepOuterTime;
															dropDownCell();
															return;
												}
									}
						}
			}
			return;
			
}

void CellLayer::dropRightCell()
{
			_dropDownTransformPos = false;
			for (auto col = 0; col < CellConfig_LocalCellCol; ++col)
			{
						for (auto row = 0; row < CellConfig_LocalCellRow; ++row)
						{
									if (_cellsLogic[col][row] != nullptr && _cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->getLife() > 0)
									{
												getDrowRightTrackCell(_cellsLogic[col][row]);	
												if (_dropDownTransformPos)
												{
															++_stepOuterTime;
															dropDownCell();
															return;
												}
									}
						}
			}
			dropLeftCell();			
}



void CellLayer::getDrowDownTrackCell(Cell * cell)
{
			if (cell == nullptr)
			{
						return;
			}
			else
			{

						Coor nextcoor;
						if (cellCanMoveDown(cell))
						{
									nextcoor._SourceCol = cell->getColumn();
									nextcoor._SourceRow = cell->getRow();
									nextcoor._destCol = cell->getColumn();
									nextcoor._destRow = cell->getRow() - 1;
									nextcoor._stepsLev = _stepOuterTime;
									nextcoor._sourceCell = cell;
									_cellMoveToCoor.push_back(nextcoor);
									swapCell(nextcoor._SourceCol, nextcoor._SourceRow, nextcoor._destCol, nextcoor._destRow);
									_dropDownTransformPos = true;
						}			
						return;
			}
}

void CellLayer::getDrowLeftTrackCell(Cell * cell)
{
			if (cell == nullptr)
			{
						return;
			}
			else
			{

					
						Coor nextcoor;
						if (cellCanMoveLeft(cell))
						{
									nextcoor._SourceCol = cell->getColumn();
									nextcoor._SourceRow = cell->getRow();
									nextcoor._destCol = cell->getColumn() - 1;
									nextcoor._destRow = cell->getRow() - 1;
									nextcoor._stepsLev = _stepOuterTime;
									nextcoor._sourceCell = cell;
									_cellMoveToCoor.push_back(nextcoor);
									swapCell(nextcoor._SourceCol, nextcoor._SourceRow, nextcoor._destCol, nextcoor._destRow);
									_dropDownTransformPos = true;
						}						
						return;
			}
}

void CellLayer::getDrowRightTrackCell(Cell * cell)
{
			if (cell == nullptr)
			{
						return;
			}
			else
			{

						
						Coor nextcoor;					
						if (cellCanMoveRight(cell))
						{
									nextcoor._SourceCol = cell->getColumn();
									nextcoor._SourceRow = cell->getRow();
									nextcoor._destCol = cell->getColumn() + 1;
									nextcoor._destRow = cell->getRow() - 1;
									nextcoor._stepsLev = _stepOuterTime;
									nextcoor._sourceCell = cell;
									_cellMoveToCoor.push_back(nextcoor);		
									swapCell(nextcoor._SourceCol, nextcoor._SourceRow, nextcoor._destCol, nextcoor._destRow);
									_dropDownTransformPos = true;
						}
						return;
			}
}

bool CellLayer::cellCanMoveDown(Cell * cell) noexcept
{
			auto ret = false;
			do 
			{
						if(cell==nullptr)
						{
									return ret;
						}
						auto belowcell = getCellFromTable(cell->getColumn(), cell->getRow() - 1);
						//钢铁判断
						if(belowcell==nullptr||belowcell->getLife()>0||_plateHorizontal[cell->getColumn()][cell->getRow()]!=nullptr)
						{
									return ret;
						}
						ret = true;
			} while (0);
			return ret;
}

bool CellLayer::cellCanMoveLeft(Cell * cell) noexcept
{
			auto ret = false;
			do
			{
						if (cell == nullptr)
						{
									return ret;
						}
						auto leftcell = getCellFromTable(cell->getColumn() - 1, cell->getRow() - 1);
						if (leftcell == nullptr || leftcell->getLife() > 0 ||((_plateVertical[cell->getColumn()][cell->getRow()]!=nullptr||_plateHorizontal[cell->getColumn()-1][cell->getRow()]!=nullptr)&&(_plateVertical[cell->getColumn()][cell->getRow()-1]!=nullptr || _plateHorizontal[cell->getColumn()][cell->getRow()]!=nullptr)))
						{
									return ret;
						}
						ret = true;
			} while (0);
			return ret;
}

bool CellLayer::cellCanMoveRight(Cell * cell) noexcept
{
			auto ret = false;
			do
			{
						if (cell == nullptr)
						{
									return ret;
						}
						auto rightcell = getCellFromTable(cell->getColumn() + 1, cell->getRow() - 1);
						if (rightcell == nullptr || rightcell->getLife() > 0 || ((_plateHorizontal[cell->getColumn()+1][cell->getRow()]!=nullptr || _plateVertical[cell->getColumn()+1][cell->getRow()]!=nullptr)&&(_plateHorizontal[cell->getColumn()][cell->getRow()]!=nullptr||_plateVertical[cell->getColumn()+1][cell->getRow()-1]!=nullptr)))
						{
									return ret;
						}
						ret = true;
			} while (0);
			return ret;
}


bool CellLayer::TouchCellCanMoveDown(Cell * cell) noexcept
{
			auto ret = false;
			do
			{
						if (cell == nullptr)
						{
									return ret;
						}
						auto belowcell = getCellFromTable(cell->getColumn(), cell->getRow() - 1);
						//钢铁判断
						if ( _plateHorizontal[cell->getColumn()][cell->getRow()] != nullptr)
						{
									return ret;
						}
						ret = true;
			} while (0);
			return ret;
}

bool CellLayer::TouchCellCanMoveLeft(Cell * cell) noexcept
{
			auto ret = false;
			do
			{
						if (cell == nullptr)
						{
									return ret;
						}
					
						if ( ((_plateVertical[cell->getColumn()][cell->getRow()] != nullptr || _plateHorizontal[cell->getColumn() - 1][cell->getRow()] != nullptr) && (_plateVertical[cell->getColumn()][cell->getRow() - 1] != nullptr || _plateHorizontal[cell->getColumn()][cell->getRow()] != nullptr)))
						{
									return ret;
						}
						ret = true;
			} while (0);
			return ret;
}

bool CellLayer::TouchCellCanMoveRight(Cell * cell) noexcept
{
			auto ret = false;
			do
			{
						if (cell == nullptr)
						{
									return ret;
						}
						
						if ( ((_plateHorizontal[cell->getColumn() + 1][cell->getRow()] != nullptr || _plateVertical[cell->getColumn() + 1][cell->getRow()] != nullptr) && (_plateHorizontal[cell->getColumn()][cell->getRow()] != nullptr || _plateVertical[cell->getColumn() + 1][cell->getRow() - 1] != nullptr)))
						{
									return ret;
						}
						ret = true;
			} while (0);
			return ret;
}

Cell *CellLayer::srandColorForNewCell(Cell * cell)

{
			//std::default_random_engine eng(time(NULL));
			//std::uniform_int_distribution<int> dis(1, CellEliminateKind);
			//auto func = std::bind(dis, eng);
			int num = random(1, 9);
			if(num==8)
			{
						num = 1;
			}
			auto color = static_cast<CellColor>(num);
			auto col = cell->getColumn();
			auto row = cell->getRow();		
			//cell->stopAllActions();
			cell->setVisible(true);
			removeChild(cell);
			cell = Block::create(col, row, color);
			if(cell!=nullptr)
			{
						displayCell(col, row, cell, 0);
			}
			

			return cell;
}






void CellLayer::destroyAndFillUpCells()
{
				
		
			if (_touchMoveCells.size() >2)
			{
						_isCanRunning = false;
						CCASSERT(_touchMoveCells.size() <= 35, "0007:CellLayer-destroyAndFillUpCells-_touchMoveCells.size() >=35!");			
						if (_recordCouldDesCell != nullptr)
						{
									auto blink = _recordCouldDesCell->getActionByTag(_recordCouldDesCell->getColumn() + _recordCouldDesCell->getRow() + blinkTag);
									if (blink != nullptr)
									{
												_recordCouldDesCell->stopAction(blink);
												blink->release();
												_recordCouldDesCell->setVisible(true);
									}
									_recordCouldDesCell = nullptr;

						}
						
						
						
						//处理伤害逻辑
						attackFromSource();
						//消除被消除的格子，并减去血量，把血量为0的格子制空格子属性
						destroyCells();
					
						

						_stepOuterTime = 0;
						//计算向下移动格子，并生成下落动画
						controlDrop();
						//计算需要补的格子，并生成动画
						//_stepOuterTime = 0;
						fillUpCellOnTop();

						if (_cellPowerNum >= 5)
						{
									grantAttackTypeForCell();
									_cellPowerNum = 0;
						}

						//播放动画
						animateControl();

						//检测格子
						restoreStalemate();
						if (_isTransformPos)
						{
									restoreAction();
						}
	
						if(_recordCouldDesCell!=nullptr)
						{
									hintTheUsableCell(_recordCouldDesCell);									
						}
						
						_isCanRunning = true;
			}
			else
			{
						return;
			}

			
}

void CellLayer::destroyCells()
{
			
			for (auto &desCells : _touchMoveCells)
			{							
						if(desCells->getLife()>0)
						{
									desCells->loseLife();
						}								
			}

			for (auto &cells : _cellsLogic)
			{
						for(const auto &cell:cells)
						{
									if (cell->getLife() < 1)
									{											
												//cell->stopAllActions();
												cell->initCellToNull();
												_playerAcquireScoreForCell += cell->getScore();


												_cellPowerNum += cell->getScore();


												log("score:%d", _playerAcquireScoreForCell);
									}
						}
										
			}

			//垂直plate
			for ( auto &plates : _plateVertical)
			{
						for ( auto &plate : plates)
						{
									if (plate != nullptr&&plate->getLife() <1)
									{												
												plate->initCellToNull();
												removeChild(plate);
												plate = nullptr;

									}
						}

			}
			//horizontal plate
			for (auto &plates : _plateHorizontal)
			{
						for (auto &plate : plates)
						{
									if (plate != nullptr && plate->getLife() <1)
									{												
												plate->initCellToNull();
												removeChild(plate);
												plate = nullptr;
									}
						}

			}


}

void CellLayer::showLightCells(CellColor col)
{
			for (const auto &cells : _cellsLogic)
			{
						for (const auto &cell : cells)
						{
									if (cell == nullptr)
									{
												continue;
									}
									if (cell->getCellColor() == col && cell->_isCanSelected && cell->_isCanMove)
									{
												if (!cell->_isSelected)
												{
															_touchCells.push_back(cell);
												}	
												
												GLProgramCache::getInstance()->addGLProgram(cell->getCellSprite()->getGLProgram(), "normal_effect");
												cell->getCellSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("light_effect"));
												
									}
									else
									{

												if (cell->_isCanSelected && cell->_isCanMove)
												{
															
															GLProgramCache::getInstance()->addGLProgram(cell->getCellSprite()->getGLProgram(), "dis_normal_effect");
															cell->getCellSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("grey_effect"));
															
												}
									}
						}
			}
}

void CellLayer::recoverLightCells(CellColor col)
{
			for (const auto &cells : _cellsLogic)
			{
						for (const auto &cell : cells)
						{
									if (cell == nullptr)
									{
												continue;
									}

									if (cell->getCellColor() == col&& cell->_isCanSelected && cell->_isCanMove)
									{
												
												cell->_isSelected = false;
												cell->getCellSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("normal_effect"));
												//GLProgramCache::getInstance()->addGLProgram(cell->getCellSprite()->getGLProgram(), "normal_effect");

									}
									else
									{
												if (cell->_isCanSelected && cell->_isCanMove)
												{
															
															cell->getCellSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("dis_normal_effect"));
												}
									}
						}
			}
}



void CellLayer::addGreyAndLightShader()
{
			std::string shader1 = FileUtils::getInstance()->getStringFromFile("example_GreyScale.fsh");
			GLProgramCache::getInstance()->addGLProgram(GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, shader1.c_str()), "grey_effect");
			std::string shader2 = FileUtils::getInstance()->getStringFromFile("example_LightScale.fsh");
			GLProgramCache::getInstance()->addGLProgram(GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, shader2.c_str()), "light_effect");
}



void CellLayer::shffuleCellsforMenu()
{
			_isCanRunning = false;
			std::vector<Cell *> mytestbak;
			for (auto col = 0; col < CellConfig_LocalCellCol; ++col)
			{
						for (auto row = 0; row < CellConfig_LocalCellRow; ++row)
						{
									if (_cellsLogic[col][row] != nullptr &&_cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->_isCanSelected)
									{
												mytestbak.push_back(_cellsLogic[col][row]);
									}
						}
			}
			std::default_random_engine defaultEngine;
			std::shuffle(mytestbak.begin(), mytestbak.end(), defaultEngine);
			auto iter = mytestbak.begin();


			for (auto col = 0; col < CellConfig_LocalCellCol; ++col)
			{
						for (auto row = 0; row < CellConfig_LocalCellRow; ++row)
						{
									if (_cellsLogic[col][row] != nullptr && _cellsLogic[col][row]->_isCanMove && _cellsLogic[col][row]->_isCanSelected)
									{
												(*iter)->setColumn(col);
												(*iter)->setRow(row);
												_cellsLogic[col][row] = *iter;
												++iter;
									}
						}
			}
			//restoreStalemate();			
			restoreAction();
			if(_recordCouldDesCell!=nullptr)
			{
						hintTheUsableCell(_recordCouldDesCell);
			}
			_isCanRunning = true;
}

void CellLayer::onEnter()
{
			Layer::onEnter();
}

void CellLayer::onExit()
{
			Layer::onExit();
			removeAllChildrenWithCleanup(true);
}

bool CellLayer::onTouchBegan(Touch * touch, Event * unused_event)
{
			auto ret = false;
			do 
			{
						if(!_isCanRunning)
						{
									return ret;
						}
						else
						{
								
									for (const auto &cells : _cellsLogic)
									{
												for (const auto &cell : cells)
												{

															if (cell !=nullptr && cell->getLife() > 0 && (cell->getBoundingBox().containsPoint(touch->getLocation())))
															{
																		//
																		log("touch  cell life :%d  col:%d,row:%d", cell->getLife(), cell->getColumn(), cell->getRow());
																		//
																		if(cell->_isCanMove && cell->_isCanSelected)
																		{
																					cell->_isSelected = true;
																					showLightCells((CellColor)(cell->getCellColor()));
																					_touchCells.push_back(cell);
																					_touchMoveCells.push_back(cell);
																					return true;
																		}
																		return false;
															}
												}
									}
						}
						ret = true;
			} while (0);
			return ret;
}

void CellLayer::onTouchMoved(Touch * touch, Event * unused_event)
{
			//移动中，如果没有选择格子，那么不做任何事情
			//如果是格子，判断颜色是否相同，如果相同，加入链表，并继续判断，否则不作处理
			if (!_isCanRunning)
			{
						
						return;
			}

			for (auto &touchlist : _touchCells)
			{
						if (touchlist->getBoundingBox().containsPoint(touch->getLocation()))
						{
									/*if (touchlist->getLife() <= 0 || touchlist->_isSelected || pow(touchlist->getRow() - _touchMoveCells.back()->getRow(), 2) + pow(touchlist->getColumn() - _touchMoveCells.back()->getColumn(), 2) > 2)
									{
												break;
									}*/

									//添加触摸控制条件
									
									if(touchlist->getLife()>0 && ! (touchlist->_isSelected) && pow(touchlist->getRow() - _touchMoveCells.back()->getRow(), 2) + pow(touchlist->getColumn() - _touchMoveCells.back()->getColumn(), 2)<=2)
									{

												auto cellnow = touchlist;
												auto cellpre = _touchMoveCells.back();
												if ((std::abs(cellnow->getColumn()-cellpre->getColumn())+std::abs(cellnow->getRow()-cellpre->getRow()))==1)
												{
															if(cellnow->getColumn()==cellpre->getColumn())
															{
																		auto maxrow = cellnow->getRow() > cellpre->getRow() ? cellnow->getRow() : cellpre->getRow();
																		if(_plateHorizontal[cellnow->getColumn()][maxrow]!=nullptr)
																		{
																					break;
																		}
															}
															else if(cellnow->getRow()==cellpre->getRow())
															{
																		auto maxcol = cellnow->getColumn() > cellpre->getColumn() ? cellnow->getColumn() : cellpre->getColumn();
																		if(_plateVertical[maxcol][cellnow->getRow()]!=nullptr)
																		{
																					break;
																		}

															}
												}
												else 
												{
															if(cellpre->getRow()>cellnow->getRow())
															{
																		if(cellpre->getColumn()>cellnow->getColumn())
																		{
																					if(!TouchCellCanMoveLeft(cellpre))
																					{
																								break;
																					}
																		}
																		else if(cellpre->getColumn()<cellnow->getColumn())
																		{
																					if(!TouchCellCanMoveRight(cellpre))
																					{
																								break;
																					}
																		}
															}
															else if(cellpre->getRow()<cellnow->getRow())
															{
																		if (cellpre->getColumn() > cellnow->getColumn())
																		{
																					if (!TouchCellCanMoveRight(cellnow))
																					{
																								break;
																					}
																		}
																		else if(cellpre->getColumn() < cellnow->getColumn())
																		{
																					if (!TouchCellCanMoveLeft(cellnow))
																					{
																								break;
																					}
																		}
															}
												}





												touchlist->_isTouchBack = false;
												touchlist->_isSelected = true;
												linkLineInGrid(touchlist->getColumn(), touchlist->getRow(), _touchMoveCells.back()->getColumn(), _touchMoveCells.back()->getRow());
												_touchMoveCells.push_back(touchlist);
												break;
									}			
						}
			}
			if (!_touchMoveCells.empty() && !(_touchMoveCells.back()->getBoundingBox().containsPoint(touch->getLocation())))
			{
						_touchMoveCells.back()->_isTouchBack = !(_touchMoveCells.back()->_isTouchBack);
			}
			if (_touchMoveCells.size() >= 2)
			{
						auto cellEnd2 = ++_touchMoveCells.rbegin();
						if ((*cellEnd2)->getBoundingBox().containsPoint(touch->getLocation()) && _touchMoveCells.back()->_isTouchBack)
						{

									_touchMoveCells.back()->_isSelected = false;
									unLinkLineInGrid(0, 0, 0, 0);
									_touchMoveCells.pop_back();
						}
			}
}

void CellLayer::onTouchEnded(Touch * touch, Event * unused_event)
{
			if (!_touchCells.empty())
			{
						recoverLightCells((CellColor)(_touchCells.front()->getCellColor()));
						_touchCells.clear();
			}
			if (!_linkLineCache.empty())
			{
						for (auto &line : _linkLineCache)
						{
									line->removeFromParentAndCleanup(true);
						}
						_linkLineCache.clear();
			}
			if (!_touchCells.empty())
			{
						_touchCells.clear();
			}
			if (!_touchMoveCells.empty())
			{
						//进入消除判断
						destroyAndFillUpCells();
						_touchMoveCells.clear();
			}
}

void CellLayer::onTouchCancelled(Touch * touch, Event * unused_event)
{
			if (!_touchCells.empty())
			{
						recoverLightCells((CellColor)(_touchCells.back()->getCellColor()));
						_touchCells.clear();
			}
			if (!_linkLineCache.empty())
			{
						for (auto &line : _linkLineCache)
						{
									line->removeFromParentAndCleanup(true);
						}
						_linkLineCache.clear();
			}
			if (!_touchCells.empty())
			{
						_touchCells.clear();
			}
			if (!_touchMoveCells.empty())
			{
						_touchMoveCells.clear();
			}
}
