#include "Plate.h"
#include "ObjectPoolManager.h"


Plate::Plate()
{
}


Plate::~Plate()
{
}

Plate * Plate::create(int col, int row, CellColor color)
{
			auto plate = new (std::nothrow) Plate;
			plate->setCellColor(color);
			plate->setColumn(col);
			plate->setRow(row);
			if(plate && plate->init())
			{

						plate->autorelease();
			}
			else
			{
						CC_SAFE_DELETE(plate);
			}

			return plate;
}

bool  Plate::init()
{
			auto ret = false;
			do
			{

						switch (_color)
						{
						case CellColor::nullPlate:
									_colorStr = "nullPlate";
									return ret;
									break;
						case CellColor::snowPlate:
									//_colorStr = "snowPlate";
									_isCanSelected = false;
									_isCanMove = false;
									_isCanBeAtteckted = true;
									_life = PlateLife::snowPlateLife;
									break;
						case CellColor::stellPlate:
									//_colorStr = "stellPlate";
									_isCanSelected = false;
									_isCanMove = false;
									_isCanBeAtteckted = false;
									_life = PlateLife::stellPlateLife;
									break;
						default:
									log("0003:Plate-init-color is wrong:%d",_color);
									return ret;
									break;
						}
						int enumIndex = static_cast<int>(_color);
						_colorStr = _EnumTypeFromStringCell.at(enumIndex);
						_spr = ObjectPoolManager::getInstance()->getObject(_colorStr);
						if(_spr==nullptr)
						{
									return ret;
						}
						if(_color==CellColor::stellPlate)
						{								
									setRotation(270.0);
						}
						else if(_color==CellColor::snowPlate)
						{
									setRotation(180.0);
						}
						else
						{
									log("0008:Plate-init-CellColor :wrong!");
									return ret;
						}
						setScale(getSingleTiledSize.x / _spr->getContentSize().width);
						addChild(_spr);
						ret = true;
			} while (0);
			return ret;
}

void Plate::destroy()
{
			ObjectPoolManager::getInstance()->pushObject(_colorStr, _spr);
			removeChild(_spr);
			_spr = nullptr;
}

void Plate::setNewColor(const int color)
{
}
