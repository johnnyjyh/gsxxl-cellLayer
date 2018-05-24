#include "Cell.h"

Rect Cell::getBoundingBox() noexcept
{
			if(_spr==nullptr)
			{
						log("0006:Cell-getBoundingBox-_spr==nullptr!");
						return Rect(0, 0, 0, 0);
			}
			double scaleFactor = getSingleTiledSize.x / _spr->getContentSize().width;
			auto rectbak = _spr->getBoundingBox();
			auto pos = convertToWorldSpace(rectbak.origin);
			return Rect(pos.x + rectbak.size.width / 6*scaleFactor, pos.y + rectbak.size.height / 6*scaleFactor, rectbak.size.width / 1.5*scaleFactor, rectbak.size.height / 1.5*scaleFactor);
}

void Cell::initCellToNull() noexcept
{
			destroy();
			removeAllChildren();
			_life = 0;
			_isSelected = false;
			_isCanSelected = false;
			_isUsedLogic = false;
			_isTouchBack = false;
			_isMoving = false;
			_isCanMove = true;
			_isCanBeAtteckted = false;
			_iAttack = 0;//0: 不攻击，1:攻击 横竖距离为1的单位 ，2: 九方格一圈 ，3: 横条，左右各为3的单位，4:纵条 上下为2的单位
			//_colorStr.clear();
}


