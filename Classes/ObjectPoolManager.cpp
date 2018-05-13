#include "ObjectPoolManager.h"
#include "CellCommon.h"


ObjectPoolManager * ObjectPoolManager::_instance = nullptr;


const std::map<std::string, std::string> _StringTypeFile
{
			{ "red", "operating_red.png" },
			{ "pink", "operating_pink.png" },
			{ "yellow", "operating_yellow.png" },
			{ "green","operating_ green.png" },
			{ "blue","operating_blue.png" },
			{ "blueand", "operating_blueand.png" },
			{ "purple","operating_ purple.png" },
			{ "snowBlock", "operating_obstacle_004.png" },
			{ "normalDiamond","operating_obstacle_005.png" },
			{ "grass","operating_obstacle_009.png" },
};

ObjectPoolManager::ObjectPoolManager() :_size(35)
{
}


ObjectPoolManager::ObjectPoolManager(int size)
{
			_size = size;
}

ObjectPoolManager::~ObjectPoolManager()
{
			delete _instance;
			_instance = nullptr;
}

ObjectPoolManager * ObjectPoolManager::getInstance()
{
			if (_instance == nullptr)
			{
						_instance = new (std::nothrow) ObjectPoolManager;
			}
			return _instance;
}


bool ObjectPoolManager::init()
{
			do 
			{

			} while (0);
			return true;
}

void ObjectPoolManager::pushObject(const std::string &type, Sprite *spr)
{
			if (spr == nullptr)
			{
						return;
			}
			if (_ObjectPool.empty())
			{
						_ObjectPool[type].pushBack(spr);
			}
			else
			{
						if (_ObjectPool[type].size() < _size)
						{
									_ObjectPool[type].pushBack(spr);
						}
						else
						{
									spr->release();									
						}
			}
}

Sprite *ObjectPoolManager::getObject(const std::string &type)
{
			if (_ObjectPool.empty())
			{
						//≥ı ºªØ
						for (auto &config : _StringTypeFile)
						{
									for (int i = 0; i < _size; ++i)
									{
												auto spr = Sprite::createWithSpriteFrameName(config.second);
												_ObjectPool[config.first].pushBack(spr);
									}
						}
			}
			else
			{			
						auto isfind = false;
						for (auto &strFileName : _StringTypeFile)
						{
									if (strFileName.first == type)
									{
												isfind = true;
												break;
									}
						}
						CCASSERT(isfind, "0001:Pool get type wrong!");
						if (_ObjectPool[type].empty())
						{
									for (int i = 0; i < 10; ++i)
									{
												auto spr = Sprite::createWithSpriteFrameName((_StringTypeFile[type]));
												_ObjectPool[type].pushBack(spr);
									}
						}
			}
			auto sprIter = _ObjectPool[type].erase(0);
			return *sprIter;
}
