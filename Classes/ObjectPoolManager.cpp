#include "ObjectPoolManager.h"
#include "CellCommon.h"


ObjectPoolManager * ObjectPoolManager::_instance = nullptr;




ObjectPoolManager::ObjectPoolManager() :_size(35)
{
}


ObjectPoolManager::ObjectPoolManager(int size)
{
			_size = size;
}

ObjectPoolManager::~ObjectPoolManager()
{
			_instance->clearObject(true);
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
									while(spr->getReferenceCount ()>0)
									{
												spr->release();
									}
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
						if(!isfind)
						{
									log("0001:ObjectPoolManager-getObject-string Type is wrong:type=%s",type.c_str ());
									return nullptr;
						}
						if (_ObjectPool[type].empty())
						{
									for (int i = 0; i < 10; ++i)
									{
												auto spr = Sprite::createWithSpriteFrameName((_StringTypeFile.at(type)));
												_ObjectPool[type].pushBack(spr);
									}
						}
			}
			auto sprIter = _ObjectPool[type].front();
			_ObjectPool[type].erase(0);
			return sprIter;
}

void ObjectPoolManager::clearObject(bool isClear)
{
			for(auto objectMap:_ObjectPool)
			{
						objectMap.second.clear();
			}
			_ObjectPool.clear();
}
