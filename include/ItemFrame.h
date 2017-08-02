#ifndef ITEMFRAME_H
#define ITEMFRAME_H

#include "wSDL.h"
#include "LRect.h"

class ItemFrame
{
    public:
        ItemFrame(int x, int y, int size);
        virtual ~ItemFrame();

        void Render();

    private:
        LRect* m_rect;
        Point m_pos;

        static const uint8_t GRAY = 0x55;
        static const uint8_t ALPHA = 0xAA;

};

#endif // ITEMFRAME_H
