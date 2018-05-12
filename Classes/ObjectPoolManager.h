#pragma once
#include "cocos2d.h"


class ObjectPoolManager
{
public:

			ObjectPoolManager()=default;
			ObjectPoolManager(int size) ;
			
			~ObjectPoolManager();
			static ObjectPoolManager *getInstance();
			
			
			constexpr int getSize() { return _size; };
			

			static ObjectPoolManager *_instance;

			std::map<std::string,Vector<Sprite *>>  _ObjectPool;

			int _size{0};

};

