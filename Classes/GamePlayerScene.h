#ifndef __GamePlayerScene_H__
#define __GamePlayerScene_H__
#include "CellCommon.h"


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
		
			//��������������� 
		
			//���������ӵ�			

			//�˳���ť

			bool initBackGround();

			//
			void GamePlayerScene::initClippingNode();

			void onEnter();  //Ԥ�����ڴ����� �����cocos��
			void onExit();//Ԥ�����ڴ����� �����cocos��


			//�����ĸ��̳������麯�����������ɿ��ƺ���
			bool onTouchBegan(Touch *touch, Event *unused_event);

			void onTouchMoved(Touch *touch, Event *unused_event);

			void onTouchEnded(Touch *touch, Event *unused_event);

			void onTouchCancelled(Touch *touch, Event *unused_event);



			float _scalesizeX;
			float _scalesizeY;



			ClippingNode *_clipNode{ nullptr };

			static int gamePath[7];

};

#endif
