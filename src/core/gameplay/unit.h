#pragma once

// project includes
#include "core/drawable.h"

// STL includes
#include <cstdint>
#include <string>

namespace core
{
    namespace gameplay
    {
        class unit : public drawable
        {
        };

        typedef std::shared_ptr<unit> unit_p;

        template< class T, typename... Args >
        unit_p create_unit( Args... args )
        {
            static_assert( std::is_base_of<unit, T>::value );
            return unit_p( new T( args... ) );
        }
    }
}


