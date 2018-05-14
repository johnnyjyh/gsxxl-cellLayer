#include "Block.h"
#include "ObjectPoolManager.h"




Block * Block::create(int col, int row, CellColor color)
{
			auto block = new (std::nothrow) Block;	
			block->setColumn(col);
			block->setRow(row);
			block->setCellColor(color);
			if(block && block->init ())
			{

						block->autorelease();
			}
			else
			{
						CC_SAFE_DELETE(block);
			}
			return block;
}


//red = 1,
//pink,
//yellow,
//green,
//blue,
//blueand,
//purple,//6
//snowBlock,//7
//normalDiamond,//8
//grass,//9

//bool _isSelected{ false }; //�Ƿ�ѡ��
//bool _isCanSelected{ false };//�Ƿ���ѡ��
//bool _isUsedLogic{ false };//�Ƿ����ڼ���
//bool _isTouchBack{ false };//�Ƿ�������
//bool _isMoving{ false };//�Ƿ����ƶ�


bool Block::init()
{
			auto ret = false;
			do 
			{
						
						switch (_color)
						{
						case CellColor::nullCell:
									_colorStr = "nullCell";
									return ret;
									break;
						case CellColor::red:
									_colorStr = "red";
									_isCanMove = true;
									_isCanSelected = true;
									_life = 1;
									break;
						case CellColor::pink:
									_colorStr = "pink";
									_isCanMove= true ;
									_isCanSelected= true ;
									_life = 1;
									break;
						case CellColor::yellow:
									_colorStr = "yellow";
									_isCanMove = true;
									_isCanSelected = true;
									_life = 1;
									break;
						case CellColor::green:
									_colorStr = "green";
									_isCanMove = true;
									_isCanSelected = true;
									_life = 1;
									break;
						case CellColor::blue:
									_colorStr = "blue";
									_isCanMove = true;
									_isCanSelected = true;
									_life = 1;
									break;
						case CellColor::blueand:
									_colorStr = "blueand";
									_isCanMove = true;
									_isCanSelected = true;
									_life = 1;
									break;
						case CellColor::purple:
									_colorStr = "purple";
									_isCanMove = true;
									_isCanSelected = true;
									_life = 1;
									break;
						case CellColor::snowBlock:
									_colorStr = "snowBlock";			
									_life = 1;
									break;
						case CellColor::normalDiamond:
									_colorStr = "normalDiamond";
									_isCanMove=true;
									_life = 1;
									break;
						case CellColor::grass:
									_colorStr = "grass";
									_life = 0;
									break;
						default:
									log("0004:Block-init-color is wrong:%d", _color);
									return ret;
									break;
						}
						_spr = ObjectPoolManager::getInstance()->getObject(_colorStr);
						if(_spr==nullptr)
						{
									return ret;
						}						
						setScale(0.5);
						addChild(_spr);
						ret = true;
			} while (0);
			return ret;
}

void Block::destroy()
{
			ObjectPoolManager::getInstance()->pushObject(_colorStr, _spr);
			removeChild(_spr);
		
}
