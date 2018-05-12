#include "ObjectPoolManager.h"


ObjectPoolManager * ObjectPoolManager::_instance = nullptr;

ObjectPoolManager::ObjectPoolManager() :_size(15)
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
						_instance = new (std::nothrow) ObjectPoolManager);
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

void ObjectPoolManager::pushObject(constexpr std::string &type, Sprite *spr)
{
			if (spr == nullptr)
			{
						return;
			}
			if (_ObjectPool.empty())
			{
						_ObjectPool[type].pushBack(spr);
						spr->retain();
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

void ObjectPoolManager::getObject(constexpr std::string & type)
{
			if (_ObjectPool.empty())
			{
						//≥ı ºªØ
			}
			else
			{
						if (_ObjectPool[type].empty())
						{

						}
						else
						{

						}
			}
}
