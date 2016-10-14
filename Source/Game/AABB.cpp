#include "AABB.h"

AABB::AABB(const Vector3& size)
:   m_size ( size)
{ }

void AABB::setPosition(const Vector3& position)
{
    m_position = position;

    ftl = m_position;

    ftr     = ftl;
    ftr.x   += m_size.x;


    ntl     = ftl;
    ntl.z   += m_size.z;

    ntl     = ftr;
    ntl.z   += m_size.z;

    ntr     = ntl;
    ntr.x   += m_size.x;

    fbl     = ftl;
    fbl.y   += m_size.y;

    fbr     = fbl;
    fbr.x   +=m_size.x;

    nbl     = ntl;
    nbl.y   += m_size.y;

    nbr     = nbl;
    nbr.x   += m_size.x;
}


bool AABB :: testDown ( const AABB& down )
{

}
