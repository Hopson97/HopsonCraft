#ifndef U_OAK_SAPLING_H_INCLUDED
#define U_OAK_SAPLING_H_INCLUDED

#include <SFML/System/Clock.hpp>

#include "Updatable_Block.h"

namespace Block
{
    class U_Oak_Sapling : public Updatable_Block
    {
        public:
            U_Oak_Sapling();

            bool update     (const Block_Location& location) override;
            void breakBlock () override;

        private:
            sf::Time    m_timeToGrow;
            sf::Clock   m_growClock;
    };
}

#endif // U_OAK_SAPLING_H_INCLUDED
