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
						_instance = new (std::nothrow) ObjectPoolManager;
			}
			return _instance;
}
