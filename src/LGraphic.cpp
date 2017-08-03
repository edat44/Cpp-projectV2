#include "LGraphic.h"

LGraphic::LGraphic()
{
    //ctor
}

LGraphic::~LGraphic()
{
    this->Free();
}

void LGraphic::Free()
{
    this->m_width = 0;
    this->m_height = 0;
}

int LGraphic::GetWidth()
{
    return this->m_width;
}

int LGraphic::GetHeight()
{
    return this->m_height;
}

void LGraphic::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    this->SetColor(red, green, blue);
    this->SetAlpha(alpha);
}

