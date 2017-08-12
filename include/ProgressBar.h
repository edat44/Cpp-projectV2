#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "LRect.h"

class ProgressBar : Box<int>
{
    public:
        ProgressBar(int w, int h, double max_val);
        virtual ~ProgressBar();

        void Render(SDL_Rect &camera, int x, int y);

        void Update(int val);

    private:
        double m_max;
        double m_val;
        std::unique_ptr<LRect> m_green_rect;
        std::unique_ptr<LRect> m_red_rect;

};

#endif // PROGRESSBAR_H
