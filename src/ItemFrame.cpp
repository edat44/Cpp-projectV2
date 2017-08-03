#include "ItemFrame.h"

ItemFrame::ItemFrame(int x, int y, int size)
{
    this->m_rect = new LRect();

    this->m_rect->SetColor(ItemFrame::GRAY, ItemFrame::GRAY, ItemFrame::GRAY, ItemFrame::ALPHA);
    this->m_rect->SetSize(size, size);
    this->m_pos.x = x;
    this->m_pos.y = y;
}

ItemFrame::~ItemFrame()
{
    if (this->m_rect != nullptr)
        delete this->m_rect;
}

void ItemFrame::Render()
{
    this->m_rect->Render(this->m_pos.x, this->m_pos.y);
}
