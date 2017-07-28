#include "General.h"

float bilinearInterpolate(float bottomLeft, float topLeft, float bottomRight, float topRight,
                          float xMin,       float xMax,
                          float yMin,       float yMax,
                          float xToCalc,    float yToCalc) noexcept
{
    float   width,          //x2x1
            height,         //y2y1
            xDistanceToMax, //x2x
            yDistanceToMax, //y2y
            xDistanceToMin, //yy1
            yDistanceToMin; //xx1

    width   = xMax - xMin;
    height  = yMax - yMin;
    xDistanceToMax = xMax - xToCalc;
    yDistanceToMax = yMax - yToCalc;

    xDistanceToMin = xToCalc - xMin;
    yDistanceToMin = yToCalc - yMin;

    return 1.0f / (width * height) *
    (
        bottomLeft  * xDistanceToMax * yDistanceToMax +
        bottomRight * xDistanceToMin * yDistanceToMax +
        topLeft     * xDistanceToMax * yDistanceToMin +
        topRight    * xDistanceToMin * yDistanceToMin
    );
}











