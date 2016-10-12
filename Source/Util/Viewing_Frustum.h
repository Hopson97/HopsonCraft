#ifndef VIEWING_FRUSTUM_H_INCLUDED
#define VIEWING_FRUSTUM_H_INCLUDED

class Plane
{

};

class Frustum
{
    enum
    {
        Top,
        Botttom,
        Left,
        Right,
        Near_Plane,
        Far_Plane
    };

    public:
        static enum
        {
            Inside,
            Outside,
            Intersect
        };

    private:
};

#endif // VIEWING_FRUSTUM_H_INCLUDED
