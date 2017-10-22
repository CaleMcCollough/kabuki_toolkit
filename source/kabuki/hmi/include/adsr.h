/** Kabuki Starship
    @file    ~/Source/_hmi/Components/ADSR.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <https://calemccollough.github.io>

                            All right reserved (R).

        Licensed under the Apache License, Version 2.0 (the "License"); you may
        not use this file except in compliance with the License. You may obtain
        a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/

#pragma once

#include <KabukiTheater-Config.h>

namespace _hmi { namespace Components {

class _KabukiTheater_ ADSR: public _::IDevice
/*< An ADSR filter. */
{
    ADSR ();
    /*< Constructs an ADSR with all zeroed out controls. */
    
    const _::Member* op (_::Expression* io, byte index) override;
    /*< Inter-process operations. */
};

}   //< Components
}   //< _hmi
