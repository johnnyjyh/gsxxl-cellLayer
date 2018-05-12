#ifndef __GamePlayScene_H__
#define __GamePlayScene_H__
#include "CellLayer.h"





class GamePlayerScene :
			public Layer
{
public:
			GamePlayerScene();
			~GamePlayerScene();

			static Scene *createScene(const CellConfiguration &config);
			static GamePlayerScene *create(const CellConfiguration &config);
			static bool loadAnimate();

			//��ʼ����Ϸ����
			bool init(const CellConfiguration &config);
			//������̨
		
			//��������������� 
		
			//���������ӵ�			

			//�˳���ť

			bool initBackGround();

			//
			void GamePlayerScene::initClippingNode();

			void onEnter();  //���ڿ��Ƽ�����Ϻ�Ŀ�ʼ
			void onExit();//�������ڿ��ƽ���������Ŀ���


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
