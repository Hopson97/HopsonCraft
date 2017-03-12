#include "Frustum.h"

//Credit: https://www.gamedev.net/resources/_/technical/general-programming/frustum-culling-r4613

#include <cmath>
#include <algorithm>

namespace
{
    enum FrustumSide
    {
        Right	= 0, // The RIGHT side of the frustum
        Left	= 1, // The LEFT	 side of the frustum
        Bottom	= 2, // The BOTTOM side of the frustum
        Top		= 3, // The TOP side of the frustum
        Back	= 4, // The BACK	side of the frustum
        Front	= 5  // The FRONT side of the frustum
    };

    enum PlaneData
    {
        A = 0,				// The X value of the plane's normal
        B = 1,				// The Y value of the plane's normal
        C = 2,				// The Z value of the plane's normal
        D = 3				// The distance the plane is from the origin
    };

    void normalizePlane(Vector4& planes)
    {
        float magnitude = (float)sqrt(planes[A] * planes[A] + planes[B] * planes[B] + planes[C] * planes[C]);
        planes[A] /= magnitude;
        planes[B] /= magnitude;
        planes[C] /= magnitude;
        planes[D] /= magnitude;
    }
}

void Frustum::update(const Matrix4& viewMatrix, const Matrix4& projMatrix)
{
	const float   *proj = glm::value_ptr(projMatrix);
	const float   *modl = glm::value_ptr(viewMatrix);
    float   clip[16]; //clipping planes

	clip[0] = modl[0] * proj[0] + modl[1] * proj[4] + modl[2] * proj[8] + modl[3] * proj[12];
	clip[1] = modl[0] * proj[1] + modl[1] * proj[5] + modl[2] * proj[9] + modl[3] * proj[13];
	clip[2] = modl[0] * proj[2] + modl[1] * proj[6] + modl[2] * proj[10] + modl[3] * proj[14];
	clip[3] = modl[0] * proj[3] + modl[1] * proj[7] + modl[2] * proj[11] + modl[3] * proj[15];

	clip[4] = modl[4] * proj[0] + modl[5] * proj[4] + modl[6] * proj[8] + modl[7] * proj[12];
	clip[5] = modl[4] * proj[1] + modl[5] * proj[5] + modl[6] * proj[9] + modl[7] * proj[13];
	clip[6] = modl[4] * proj[2] + modl[5] * proj[6] + modl[6] * proj[10] + modl[7] * proj[14];
	clip[7] = modl[4] * proj[3] + modl[5] * proj[7] + modl[6] * proj[11] + modl[7] * proj[15];

	clip[8] = modl[8] * proj[0] + modl[9] * proj[4] + modl[10] * proj[8] + modl[11] * proj[12];
	clip[9] = modl[8] * proj[1] + modl[9] * proj[5] + modl[10] * proj[9] + modl[11] * proj[13];
	clip[10] = modl[8] * proj[2] + modl[9] * proj[6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[8] * proj[3] + modl[9] * proj[7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[0] + modl[13] * proj[4] + modl[14] * proj[8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[1] + modl[13] * proj[5] + modl[14] * proj[9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[2] + modl[13] * proj[6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[3] + modl[13] * proj[7] + modl[14] * proj[11] + modl[15] * proj[15];

	frustum_planes[Right][A] = clip[3] - clip[0];
	frustum_planes[Right][B] = clip[7] - clip[4];
	frustum_planes[Right][C] = clip[11] - clip[8];
	frustum_planes[Right][D] = clip[15] - clip[12];
	normalizePlane(frustum_planes[Right]);

	frustum_planes[Left][A] = clip[3] + clip[0];
	frustum_planes[Left][B] = clip[7] + clip[4];
	frustum_planes[Left][C] = clip[11] + clip[8];
	frustum_planes[Left][D] = clip[15] + clip[12];
	normalizePlane(frustum_planes[Left]);

	frustum_planes[Bottom][A] = clip[3] + clip[1];
	frustum_planes[Bottom][B] = clip[7] + clip[5];
	frustum_planes[Bottom][C] = clip[11] + clip[9];
	frustum_planes[Bottom][D] = clip[15] + clip[13];
	normalizePlane(frustum_planes[Bottom]);

	frustum_planes[Top][A] = clip[3] - clip[1];
	frustum_planes[Top][B] = clip[7] - clip[5];
	frustum_planes[Top][C] = clip[11] - clip[9];
	frustum_planes[Top][D] = clip[15] - clip[13];
	normalizePlane(frustum_planes[Top]);

	frustum_planes[Back][A] = clip[3] - clip[2];
	frustum_planes[Back][B] = clip[7] - clip[6];
	frustum_planes[Back][C] = clip[11] - clip[10];
	frustum_planes[Back][D] = clip[15] - clip[14];
	normalizePlane(frustum_planes[Back]);

	frustum_planes[Front][A] = clip[3] + clip[2];
	frustum_planes[Front][B] = clip[7] + clip[6];
	frustum_planes[Front][C] = clip[11] + clip[10];
	frustum_planes[Front][D] = clip[15] + clip[14];
	normalizePlane(frustum_planes[Front]);
}

bool Frustum::inFrustum(const Vector4& min, const Vector4& max)
{
    bool inside = true;

    for (int32_t i = 0; i < 6; i++)
    {
        float distance = std::max(min.x * frustum_planes[i].x, max.x * frustum_planes[i].x) +
                         std::max(min.y * frustum_planes[i].y, max.y * frustum_planes[i].y) +
                         std::max(min.z * frustum_planes[i].z, max.z * frustum_planes[i].z) +
                         frustum_planes[i].w;

        inside &= distance > 0;
    }
    return inside;
}
