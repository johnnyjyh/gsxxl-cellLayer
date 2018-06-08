#ifndef __GamePlayScene_H__
#define __GamePlayScene_H__
#include "CellLayer.h"
#include "DefenseLayer.h"






class GamePlayerScene :
			public Layer
{
public:
			GamePlayerScene();
			~GamePlayerScene();

			static Scene *createScene(const CellConfiguration &config,const DefenseConfiguration &defenConfig);
			static GamePlayerScene *create(const CellConfiguration &config, const DefenseConfiguration &defenConfig);
			static bool loadAnimate();


			//��ʼ����Ϸ����
			bool init(const CellConfiguration &config, const DefenseConfiguration &defenConfig);
			//������̨
		
			//��������������� 
		
			//���������ӵ�			

			//�˳���ť

			bool initBackGround();

			//
			bool initClippingNode();

			bool initCellLayer();

			bool initDefenseLayer();

			

			void onEnter();  //���ڿ��Ƽ�����Ϻ�Ŀ�ʼ
			void onExit();//�������ڿ��ƽ���������Ŀ���


			//�����ĸ��̳������麯�����������ɿ��ƺ���
			bool onTouchBegan(Touch *touch, Event *unused_event);

			void onTouchMoved(Touch *touch, Event *unused_event);

			void onTouchEnded(Touch *touch, Event *unused_event);

			void onTouchCancelled(Touch *touch, Event *unused_event);
			
			void update(float dt);


			float _scalesizeX;
			float _scalesizeY;


			int m_recordCellScore{ 0 };
			ClippingNode *_clipNode{ nullptr };
			CellConfiguration *m_cell_config{nullptr};
			DefenseConfiguration *m_defense_config{ nullptr };
			CellLayer *_cellLayer{nullptr};
			DefenseLayer *_defenseLayer{ nullptr };
		
			static int gamePath[7];
			
		
};

#endif
