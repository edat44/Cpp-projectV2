#include "ItemFrame.h"

ItemFrame::ItemFrame(int x, int y, int size)
    : LRect(x, y, size, size)
{
    SetColor(ItemFrame::GRAY, ItemFrame::GRAY, ItemFrame::GRAY, ItemFrame::ALPHA);
}

ItemFrame::~ItemFrame()
{
}

void ItemFrame::Render()
{
    this->LRect::Render();
}
