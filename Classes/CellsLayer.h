#ifndef __CellsLayer_H__
#define __CellsLayer_H__

#include "Common.h"
#include "Cells.h"


class CellsLayer:
			public Layer
{
public:
			CellsLayer();
			~CellsLayer();
			static CellsLayer * create();
			bool init();


			//����װ�����   �� �ǿ� 7*5   ֻ��ʾ5�㣬װ��10�㣬����5�㣬�����������Ǩ�ƣ�����������װ��
			//��ʾ����
			//�ж��Ƿ��������   T/F   �������������ģ�����û���ˣ����Ҹ��ӣ���������    ��ֱ���п���������Ϊֹ,3�����������·������
			//��������
			//�������   ������ʾ���Ӻ���Ҫ�Բ���������в���
			//���ƺ��� �� begin ���濪ʼ��move�����ж�  ��end�������   ������8�������ȡ���ӣ�3��������������ѡ��·��ǰ���󣬲��ܻ��ˣ������ظ�ѡ��
			//���������� ��ӵ�һ�������ڣ��������������
			//��Ϸ����Ϊ��  ��ʾ����->�ж����� ->�˹�����->��������->������� Ȼ��ѭ��
			
			Cells *createRandCells(int random, int col, int row);
			
			bool initCells();
			//���snowblock
			auto  checkSnowBlock(std::list<Cells *> &cells);
			//���snowplate
			//���stealplate
			//���normalDiamond
			//����ڵ���
			auto checkBarrier(std::list<Cells *> &cells);
			void destroyBarrier();


			void displayCells();
			bool isCanDestroyCells();

			void destroyAndFillUpCells();
			void destroyCells();
			void supplyCells();
			bool isPreCells();
			void preCells();
			
			void preCells1();
			void preCells2();

			//�ƶ�����
			void preCellsForCol();

			//������
			void preCellsDownForCol();

			//�������ڿ��ƺ���
			void fillUpAndMoveCells(Cells *cell, float time);
			//��ѯ��Ҫ�ƶ��ĸ���
			Cells *getUsableCol(std::list<Cells *>::iterator  &souceCell, int col, int row);
			//�ƶ���Ҫ�ƶ��ĸ���
			void removeUsableCells();
			//�������ӿؼ�
			void swapCells(Cells *sourceCell,Cells *destCell);
					
			

			
			Cells *getUsableCell1(std::list<Cells *>::iterator  &souceCell, int col, int row);
			Cells *getUsableCell(std::list<Cells *>::iterator  souceCell, std::list<Cells *>::iterator  &destCellRef, std::list<Cells *>::iterator  cellBak);
			
			Cells *getUsableCell(std::list<Cells *>::iterator  &souceCell, int col, int row);

			Cells *getColRowCell(int col, int row);

			DrawNode *coverFabric(Vec2 pos);

			int computeTheOneCell(std::vector<Cells *> &cells, Cells * cellCurrent,int count);

			void restoreAction();

			bool isStalemate();

			void shffuleCellsforMenu();

			void restoreStalemate();

			Cells *findCell(int col, int row);

			Cells *getNewCellForSupCell();

			void setCellsToScreen(int col, int row);

			void linkLineInGrid(int col1,int row1,int col2,int row2);
			
			void unLinkLineInGrid(int col1, int row1, int col2, int row2);

			bool checkCells();

			Vec2 coordinateToVec2(int col, int row);
			
			int *vec2ToCoordinate(Vec2 vec);

			void showLightCells(CellsColor col);  //shader light
			
			void recoverLightCells(CellsColor col);//recover light

			void moveCell(Cells *cell,int col1, int row1, int col2, int row2);//�ƶ���ʾ�ṹ�����ı�洢λ��

			void addGreyAndLightShader();

			//�ڸǼ���
			//ѡ����clippingNode
			//deprecated attribute
			void initClippingNode();
			
			
			


			//�����ĸ��̳������麯�����������ɿ��ƺ���
			bool onTouchBegan(Touch *touch, Event *unused_event);

			void onTouchMoved(Touch *touch, Event *unused_event);

			void onTouchEnded(Touch *touch, Event *unused_event);

			void onTouchCancelled(Touch *touch, Event *unused_event);

			

			std::list<std::list<Cells *>> _displayCell;
			std::list<Cells *> _supCell;
			//std::list<Cells *> _supDisplayCell[5];
			std::list<Cells *> _desCell;
			std::list<DrawNode *> _linkLineCache;
			std::list<Cells *> _touchCells;
			std::list<Cells *> _touchMoveCells;
			std::list<Cells *> _snowBlock;
			std::list<Cells *> _hintCells;

			//�����ƶ�����
			std::vector<Cells *> _cellRemoveQueue;
			std::vector<Vec2> _cellVec2RemoveQueue;

			ClippingNode *_clipNode{nullptr};
			bool _isCanRunning{false};
			
			int _cellScore{ 0 };

			int transformArr[2];
};


#endif //__TIlesLayer_H__