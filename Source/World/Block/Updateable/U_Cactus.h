#ifndef U_CACTUS_H_INCLUDED
#define U_CACTUS_H_INCLUDED

#include <SFML/System/Clock.hpp>

#include "Updatable_Block.h"

namespace Block
{
    class U_Cactus : public Updatable_Block
    {
        public:
            U_Cactus        ();
            bool update     (const Block_Location& location) override;

        private:
            void onBreak    () override;

            sf::Time    m_timeToGrow;
            sf::Clock   m_growClock;
    };
}

#endif // U_CACTUS_H_INCLUDED
