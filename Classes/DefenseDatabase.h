#pragma once
#include "DefenseCommon.h"

class DefenseDatabase
{
public:
			DefenseDatabase();
			~DefenseDatabase();

			virtual inline int getLife() noexcept { return _life; };
			virtual inline void setLife(int life)noexcept { _life = life; };
			virtual inline void loseLife()noexcept { --_life; };
			virtual inline int getPos() noexcept { return _pos; };
			virtual inline void setPos(int pos) noexcept { _pos = pos; };
			virtual inline double getAttack()noexcept { return _attack; };
			virtual inline void setAttack(double att)noexcept { _attack = att; };
			virtual inline double getSpeed()noexcept { return _speed; };
			virtual inline void setSpeed(double spd)noexcept { _speed = spd; };
			virtual inline double getAccSpeed()noexcept { return _accSpeed; };
			virtual inline void setAccSpeed(double accSpd)noexcept { _accSpeed = accSpd; };
			virtual inline int getType() noexcept { return _type; };
			virtual inline void setType(int type) noexcept { _type = type; };			
			virtual  void destroy() = 0;

			virtual void setSignNumber() {
						_signNumber = DefenseDatabase::m_dataBaseNumber;
									++DefenseDatabase::m_dataBaseNumber;
			};
			virtual inline uint64_t getSignNumber() { return _signNumber; };

			CC_SYNTHESIZE(bool, _isDead, IsDead);
			CC_SYNTHESIZE(bool, m_isTransform, DataTransForm);
			CC_SYNTHESIZE(bool, _isCanAttack, CanAttack);
			CC_SYNTHESIZE(bool, _isMoving, Moving);
			CC_SYNTHESIZE(bool, _isCanMove, CanMove);
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _col, Column);
			uint64_t  _signNumber{ 0 };
			int _life{ 0 };
			int _pos{ 0 };
			int _type{ 0 };
			static uint64_t m_dataBaseNumber;

			double _attack{ 0 };
			double _speed{ 0 };
			double _accSpeed{ 0 };
};

