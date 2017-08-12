#include "ProgressBar.h"

ProgressBar::ProgressBar(int w, int h, double max_val)
    : Box()
{
    m_max = max_val;
    printf("Max val: %f\n", m_max);
    m_val = m_max;

    SetSize(w, h);

    m_green_rect = std::unique_ptr<LRect>(new LRect(w, h));
    m_green_rect->SetColor(0x00, 0xFF, 0x00);

    m_red_rect = std::unique_ptr<LRect>(new LRect(0, h));
    m_red_rect->SetColor(0xFF, 0x00, 0x00);
}

ProgressBar::~ProgressBar()
{
    //dtor
}

void ProgressBar::Render(SDL_Rect &camera, int x, int y)
{
    SetPosition(x, y - m_box.h, false);
    int green_width = static_cast<int>((double)(m_val / m_max) * m_box.w);
    int red_width = m_box.w - green_width;
    m_green_rect->SetSize(green_width, m_box.h);
    m_red_rect->SetSize(red_width, m_box.h);

    m_green_rect->Render(camera, m_box.x, m_box.y);
    m_red_rect->Render(camera, m_box.x + green_width, m_box.y);
}

void ProgressBar::Update(int val)
{
    m_val = val;

}
