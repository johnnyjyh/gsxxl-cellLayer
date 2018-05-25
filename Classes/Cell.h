#pragma once
#include "CellCommon.h"

class Cell:public Node
{
public:

			//static Cell *create(int col,int row,CellColor color);
			virtual bool init()=0;
			virtual void destroy() = 0;
			virtual inline void setCellColor(const int color) { _color = static_cast<CellColor>(color); };
			virtual inline int getCellColor() const { return static_cast<const int>(_color); };
			virtual inline void setLife(const int life) { _life = life; };
			virtual inline  int getLife() const { return _life; };
			virtual inline Sprite * getCellSprite() const { return _spr;};
			virtual Rect getBoundingBox() noexcept ;
			virtual inline void loseLife() noexcept { --_life; };
			virtual  void initCellToNull()noexcept;
			virtual double getSpeed() noexcept { return _speed; };
			virtual int getScore() noexcept { return _score; };
			virtual void setScore(int score) noexcept { _score = score; };
			virtual void onEnter() { Node::onEnter();
			};
			virtual void onExit() { Node::onExit(); 
			};
			virtual void setNewColor(const int color) =0;

			bool _isSelected{ false }; //是否被选择
			bool _isCanSelected{ false };//是否能选择
			bool _isUsedLogic{ false };//是否用于计算
			bool _isTouchBack{ false };//是否触摸返回
			bool _isMoving{ false };//是否在移动
			bool _isCanMove{ true };//是否可以移动
			bool _isCanBeAtteckted{false};
			int _iAttack{ 0 };//0无攻击,1普通攻击，2横排攻击，3纵排攻击，4周围一圈变成同色
			int _score{ 0 };
			
			
			Sprite* _spr{nullptr};

			std::string _colorStr;
			
			int _life{ 0 };
			CellColor _color;
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);
			
			double _speed{ 0.0 };
			
			std::vector<Vec2> _moveVec;
			Vector<FiniteTimeAction *> _moveActionVec;
};

