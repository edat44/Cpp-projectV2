#ifndef BOX_H
#define BOX_H

#if defined(_WIN32) || defined(_WIN64)
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

template <typename T>
class Point
{
    public:
        Point() {};
        Point(T x, T y) : x(x), y(y) {};

        T x = 0;
        T y = 0;

        Point<double> ToDouble() const;
        Point<int> ToInt() const;

        bool operator==(const Point<T> &p2);
};

template <typename T>
class Rect
{
    public:
        Rect() : x(0), y(0), w(0), h(0) {};
        Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {};

        Point<T> GetPosition();
        Point<T> GetSize();
        Point<T> GetHalfSize();
        Point<T> GetMiddle();

        SDL_Rect ToSDL() const;
        Rect<double> ToDouble() const;
        Rect<int> ToInt() const;

        bool operator==(const Rect<T> &r2);

        T x = 0;
        T y = 0;
        T w = 0;
        T h = 0;
};

template <class T>
class Box
{
    public:
        Box() {};
        virtual ~Box() {};

        Rect<T> GetBox();
        Point<T> GetSize();
        Point<T> GetHalfSize();
        Point<T> GetMiddle();
        Point<T> GetPosition();
        T GetWidth();
        T GetHeight();


        void SetPosition(T x, T y, bool centered = true);
        void SetPosition(const Point<T> &pos, bool centered = true);
        void SetPosition(T x, T y, Point<int> tile_size, bool centered = true);
        void SetPosition(const Point<T> &pos, Point<int> tile_size, bool centered = true);

        void SetSize(T w, T h);
        void SetSize(const Point<T> &size);

        bool operator==(const Box<T> &b2);

    protected:
        Rect<T> m_box;
};

/**********POINT FUNCTIONS**************************************/
template <typename T>
Point<int> Point<T>::ToInt() const
{
    return Point<int> {(int)x, (int)y};
}

template <typename T>
Point<double> Point<T>::ToDouble() const
{
    return Point<double> {(double)x, (double)y};
}

/**********POINT OPERATORS**************************************/
template <typename T1, typename T2>
Point<T1> operator+(const Point<T1> &p1, const Point<T2> &p2)
{
    return Point<T1>{(T1)(p1.x + p2.x), (T1)(p1.y + p2.y)};
}

template <typename T1, typename T2>
Point<T1> operator+(const Point<T1> &p1, T2 value)
{
    return Point<T1>{(T1)(p1.x + value), (T1)(p1.y + value)};
}

template <typename T1, typename T2>
Point<T1> operator-(const Point<T1> &p1, const Point<T2> &p2)
{
    return Point<T1>{(T1)(p1.x - p2.x), (T1)(p1.y - p2.y)};
}

template <typename T1, typename T2>
Point<T1> operator-(const Point<T1> &p1, T2 value)
{
    return Point<T1>{(T1)(p1.x - value), (T1)(p1.y - value)};
}

template <typename T1, typename T2>
Point<T1> operator/(const Point<T1> &p1, const Point<T2> &p2)
{
    return Point<T1>{(T1)(p1.x / p2.x), (T1)(p1.y / p2.y)};
}

template <typename T1, typename T2>
Point<T1> operator/(const Point<T1> &p1, T2 value)
{
    return Point<T1>{(T1)(p1.x / value), (T1)(p1.y / value)};
}

template <typename T>
bool Point<T>::operator==(const Point<T> &p2)
{
    return (this->x == p2.x) && (this->y == p2.y);
}

/**********RECT FUNCTIONS**************************************/
template <typename T>
Point<T> Rect<T>::GetPosition()
{
    return Point<T>{x, y};
}

template <typename T>
Point<T> Rect<T>::GetSize()
{
    return Point<T>{w, h};
}

template <typename T>
Point<T> Rect<T>::GetHalfSize()
{
    return Point<T>{(T)(w / 2), (T)(h / 2)};
}

template <typename T>
Point<T> Rect<T>::GetMiddle()
{
    return Point<T>{x + (w / 2), y + (h / 2)};
}

template <typename T>
SDL_Rect Rect<T>::ToSDL() const
{
    return SDL_Rect {(int)x, (int)y, (int)w, (int)h};
}

template <typename T>
Rect<double> Rect<T>::ToDouble() const
{
    return Rect<double> {(double)x, (double)y, (double)w, (double)h};
}

template <typename T>
Rect<int> Rect<T>::ToInt() const
{
    return Rect<int> {(int)x, (int)y, (int)w, (int)h};
}

/**********RECT OPERATORS**************************************/
template <typename T>
bool Rect<T>::operator==(const Rect<T> &r2)
{
    return (x == r2.x) && (y == r2.y) && (w == r2.w) && (h == r2.h);
}

/**********BOX GET FUNCTIONS**************************************/
template <typename T>
Rect<T> Box<T>::GetBox()
{
    return m_box;
}

template <typename T>
Point<T> Box<T>::GetMiddle()
{
    return m_box.GetMiddle();
}

template <typename T>
Point<T> Box<T>::GetSize()
{
    return m_box.GetSize();
}

template <typename T>
Point<T> Box<T>::GetHalfSize()
{
    return m_box.GetHalfSize();
}

template <typename T>
Point<T> Box<T>::GetPosition()
{
    return m_box.GetPosition();
}

template <typename T>
T Box<T>::GetWidth()
{
    return m_box.w;
}

template <typename T>
T Box<T>::GetHeight()
{
    return m_box.h;
}

/**********BOX SET FUNCTIONS**************************************/
template <typename T>
void Box<T>::SetPosition(T x, T y, bool centered)
{
    m_box.x = x - (centered ? (m_box.w / 2) : 0);
    m_box.y = y - (centered ? (m_box.h / 2) : 0);
}

template <typename T>
void Box<T>::SetPosition(const Point<T> &pos, bool centered)
{
    SetPosition(pos.x, pos.y, centered);
}

template <typename T>
void Box<T>::SetPosition(T x, T y, Point<int> tile_size, bool centered)
{
    m_box.x = static_cast<T>(((x + 0.5f) * tile_size.x) - (centered ? (m_box.w / 2) : 0));
    m_box.y = static_cast<T>(((y + 0.5f) * tile_size.y) - (centered ? (m_box.h / 2) : 0));
}

template <typename T>
void Box<T>::SetPosition(const Point<T> &pos, Point<int> tile_size, bool centered)
{
    SetPosition(pos.x, pos.y, tile_size, centered);
}

template <typename T>
void Box<T>::SetSize(T w, T h)
{
    m_box.w = w;
    m_box.h = h;
}

template <typename T>
void Box<T>::SetSize(const Point<T> &size)
{
    m_box.w = size.x;
    m_box.h = size.y;
}

/**********BOX OPERATORS**************************************/
template <typename T>
bool Box<T>::operator==(const Box<T> &b2)
{
    return this->m_box == b2.m_box;
}

#endif // BOX_H
