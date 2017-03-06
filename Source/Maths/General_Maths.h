#ifndef GENERAL_MATHS_H_INCLUDED
#define GENERAL_MATHS_H_INCLUDED

#include "../OpenGL/GL_Maths.h"

namespace Maths
{
    constexpr static double PI = 3.14159265359;

    double getDistance (const Vector3& p1, const Vector3& p2);

    double getLength (const Vector3& vect);

}//namespace maths

#endif // GENERAL_MATHS_H_INCLUDED
