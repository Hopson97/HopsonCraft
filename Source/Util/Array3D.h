#ifndef ARRAY3D_H_INCLUDED
#define ARRAY3D_H_INCLUDED

#include <array>
#include <cstdlib>

//A 3D array with constant width, height and depth
template<typename T, int Size>
class Array3D
{
    public:
        T& at(int xPos, int yPos, int zPos)
        {
            return m_array[yPos *
                           m_AREA + zPos *
                           m_SIZE + xPos];
        }

        const T& at(int xPos, int yPos, int zPos) const
        {
            return m_array[yPos *
                           m_AREA + zPos *
                           m_SIZE + xPos];
        }

        template<typename Vector>
        T& at(const Vector& pos)
        {
            return at(pos.x, pos.y, pos.z);
        }

        template<typename Vector>
        const T& at(const Vector& pos) const
        {
            return at(pos.x, pos.y, pos.z);
        }

        template<typename Vector>
        int getIndex(const Vector& pos)
        {
            return  pos.y *
                    m_AREA + pos.z *
                    m_SIZE + pos.z;
        }

        std::array<T, Size * Size * Size>& getRaw()
        {
            return m_array;
        }

    private:
        std::array<T, Size * Size * Size> m_array;

        int m_VOLUME = Size * Size * Size;
        int m_AREA   = Size * Size;
        int m_SIZE   = Size;
};

#endif // ARRAY3D_H_INCLUDED
