#include "ObjectPoolManager.h"
#include "CellCommon.h"
#include "CommonConfig.h"
#include "DefenseCommon.h"


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
									if(spr->getReferenceCount ()>0)
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
												if(spr!=nullptr)
												{
															spr->retain();
															_ObjectPool[config.first].pushBack(spr);
												}
												else
												{
															log("0010:ObjectPoolManager-getObject:_spr==nullptr!");
												}
												
									}
						}
						log("11111111111111111111111111");
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
												spr->retain();
												_ObjectPool[type].pushBack(spr);
									}
						}
			}
			auto sprIter = _ObjectPool[type].back();
			_ObjectPool[type].popBack();
			return sprIter;
}

void ObjectPoolManager::clearObject(bool isClear)
{
			if (!isClear)
			{
						return;
			}
						
			for(auto objectMap:_ObjectPool)
			{
						for(auto spr: objectMap.second )
						{
									if (spr->getReferenceCount() > 0)
									{
												spr->release();
									}
						}
						objectMap.second.clear();
						objectMap.second.reserve(0);					
			}
			_ObjectPool.clear();			
			//_ObjectPool.r
}
