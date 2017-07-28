#ifndef GENERAL_MATHS_H_INCLUDED
#define GENERAL_MATHS_H_INCLUDED


template<typename T, typename R>
bool inRange(T var, R low, R high) noexcept
{
    return  var <= high &&
            var >= low;
}

template<typename T, typename L>
bool lessThan(T var, L val) noexcept
{
    return var < val;
}

/**
*   \brief Perform bilinear interpolation between 4 points in 2D space
*
*   This function should generally be called in a nested for loop, going from
*   xMin -> xMax in the xToCalc
*   yMin -> yMax in the yToCalc
*
*   \param bottomLeft   The bottom-left value to interpolate between
*   \param topLeft      The top-left value to interpolate between
*   \param bottomRight  The bottom-right value to interpolate between
*   \param topRight     The top-right value to interpolate between
*   \param xMin         Base start, used to calculate area of interpolation
*   \param xMax         Base end
*   \param xToCalc      Local x-position within the area to calculate the interpolation value
*   \param yToCalc      Local y-position within the area to calculate the interpolation value
*/
float bilinearInterpolate(float bottomLeft, float topLeft, float bottomRight, float topRight,
                          float xMin,       float xMax,
                          float yMin,       float yMax,
                          float xToCalc,    float yToCalc) noexcept;



#endif // GENERAL_MATHS_H_INCLUDED
