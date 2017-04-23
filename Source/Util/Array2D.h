#ifndef ARRAY2D_H_INCLUDED
#define ARRAY2D_H_INCLUDED

#include <array>
#include <cstdlib>

//A 2D array with constant width and height
template<typename T, uint32_t Size>
class Array2D
{
    public:
        T& at(uint32_t xPos, uint32_t yPos)
        {
            return m_array[xPos + yPos * Size];
        }

        const T& at(uint32_t xPos, uint32_t yPos) const
        {
            return m_array[xPos + yPos * Size];
        }

        template<typename Vector>
        T& at(const Vector& pos)
        {
            return at(pos.x, pos.y);
        }

        template<typename Vector>
        const T& at(const Vector& pos) const
        {
            return at(pos.x, pos.y);
        }

    private:
        std::array<T, Size * Size> m_array;
};

#endif // ARRAY2D_H_INCLUDED
