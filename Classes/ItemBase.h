#ifndef __ItemBase_H__
#define __ItemBase_H__
#include "CellCommon.h"

class ItemBase :public Node
{
public:
			ItemBase();
			~ItemBase();
			virtual ItemBase *createItem() ;
};

#endif // __ItemBase_H__

