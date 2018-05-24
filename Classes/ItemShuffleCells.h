#ifndef __ItemShuffleCells_H__
#define __ItemShuffleCells_H__
#include "ItemBase.h"
#include "CellLayer.h"

class ItemShuffleCells :public ItemBase
{
public:
			ItemShuffleCells();
			~ItemShuffleCells();
			static ItemShuffleCells *create();
			bool init();
			void bindLayerCell(CellLayer* _lay);
			void updateRecordTimes();

			CellLayer *_layCells{nullptr};
			Label *_recordTimeLabel{nullptr};
			CC_SYNTHESIZE(int, _recordTimes, RecordTime);

};

#endif// __ItemShuffleCells_H__