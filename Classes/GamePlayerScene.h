#ifndef __GamePlayerScene_H__
#define __GamePlayerScene_H__
#include "Common.h"
#include "LayerMonster.h"
#include "LayerTower.h"
#include "LayerBullet.h"
#include "CellsLayer.h"
#include "PlayerData.h"

class GamePlayerScene :
			public Layer
{
public:
			GamePlayerScene();
			~GamePlayerScene();

			static Scene *createScene();
			static GamePlayerScene *create();		
			static bool loadAnimate();

			//��ʼ����Ϸ����
			bool init();
			//������̨
			bool createTower();
			//��������������� 
			bool createMonster();
			//���������ӵ�
			bool createAndBindBullet();
			//
			bool createCellsForPlant();
			
			//�˳���ť

			bool initBackGround();

			//
			void GamePlayerScene::initClippingNode();

			void onEnter();  //Ԥ�����ڴ����� �����cocos��
			void onExit();//Ԥ�����ڴ����� �����cocos��
			void update(float dt);
			
						//�����ĸ��̳������麯�����������ɿ��ƺ���
			bool onTouchBegan(Touch *touch, Event *unused_event);

			void onTouchMoved(Touch *touch, Event *unused_event);

			void onTouchEnded(Touch *touch, Event *unused_event);

			void onTouchCancelled(Touch *touch, Event *unused_event);
			

			LayerTower *_layerTower;
			LayerMonster *_layerMonster;
			CellsLayer *_layerCells;
			PlayerData *_playerInstance;

			float _scalesizeX;
			float _scalesizeY;
		


			ClippingNode *_clipNode{ nullptr };
			
			static int gamePath[7];

};

#endif
