#ifndef VECTOR_H
#define VECTOR_H

struct Vector2i
{
    Vector2i ( int x, int y );

    bool operator < ( const Vector2i& other ) const;
    bool operator > ( const Vector2i& other ) const;

    int x;
    int y;

    private:
        int m_id;

        static int id;
};

#endif // VECTOR_H
