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

			void pushObject(constexpr std::string &type,Sprite *spr);
			void getObject(constexpr std::string &type);

			constexpr int getSize() { return _size; };

			
			std::map<std::string,Vector<Sprite *>>  _ObjectPool;
			int _size{ 0 };
			static ObjectPoolManager *_instance;

};

