#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ObjectPoolManager
{
public:

			ObjectPoolManager();
			ObjectPoolManager(int size) ;		
			~ObjectPoolManager();
			static ObjectPoolManager *getInstance();
						
			bool init();

			void pushObject(const std::string &type,Sprite *spr);
			Sprite *getObject(const std::string &type);

			const int getSize() { return _size; };

			
			std::map<std::string,Vector<Sprite *>>  _ObjectPool;
			int _size{ 0 };
			static ObjectPoolManager *_instance;

};

