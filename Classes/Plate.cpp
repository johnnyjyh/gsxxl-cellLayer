#include "Plate.h"
#include "ObjectPoolManager.h"


Plate::Plate()
{
}


Plate::~Plate()
{
}

Plate * Plate::create(int col, int row, PlateColor color)
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
						case PlateColor::nullPlate:
									return ret;
									break;
						case PlateColor::snowPlate:
									_colorStr = "snowPlate";
									_isCanSelected = false;
									_isCanMove = false;
									_life = 1;
									break;
						case PlateColor::stellPlate:
									_colorStr = "stellPlate";
									_isCanSelected = false;
									_isCanMove = false;
									_life = 10000;
									break;
						default:
									log("0003:Plate-init-color is wrong:%d",_color);
									return ret;
									break;
						}
						
						_spr = ObjectPoolManager::getInstance()->getObject(_colorStr);
						if(_spr==nullptr)
						{
									return ret;
						}
						if(_color==PlateColor::stellPlate)
						{
									setRotation(270.0);
						}
						else
						{
									setRotation(180.0);
						}
						setScale(0.5f);
						addChild(_spr);
						ret = true;
			} while (0);
			return ret;
}

void Plate::destroy()
{
			ObjectPoolManager::getInstance()->pushObject(_colorStr, _spr);
			removeChild(_spr);
}