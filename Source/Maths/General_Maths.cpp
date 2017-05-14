#include "General_Maths.h"


namespace Maths
{
    /*
    float bilinearInterpolate(float q11, float q12, float q21, float q22,
                              float x1,  float x2,
                              float y1,  float y2,
                              float x,   float y)
    {
        float   x2x1,
                y2y1,
                x2x,
                y2y,
                yy1,
                xx1;

        x2x1    = x2 - x1;
        y2y1    = y2 - y1;
        x2x     = x2 - x;
        y2y     = y2 - y;
        yy1     = y - y1;
        xx1     = x - x1;

        return 1.0 / (x2x1 * y2y1) * (
            q11 * x2x * y2y +
            q21 * xx1 * y2y +
            q12 * x2x * yy1 +
            q22 * xx1 * yy1
        );
    }
    */
    float bilinearInterpolate(float bottomLeft, float topLeft, float bottomRight, float topRight,
                              float xMin,       float xMax,
                              float yMin,       float yMax,
                              float xToCalc,    float yToCalc)
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


}











