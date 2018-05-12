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

			//初始化游戏内容
			bool init(const CellConfiguration &config);
			//创建炮台
		
			//创建怪物，并处理动作 
		
			//创建并绑定子弹			

			//退出按钮

			bool initBackGround();

			//
			void GamePlayerScene::initClippingNode();

			void onEnter();  //用于控制加载完毕后的开始
			void onExit();//用于用于控制结束场景后的控制


			//以下四个继承来的虚函数用于来集成控制函数
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
