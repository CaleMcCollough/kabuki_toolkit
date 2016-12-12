/** Kabuki Toolkit
    @file    /.../KabukiToolkit-Impl/_Com/MIDI/MIDIMap.cpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright  (C) 2016 [Cale McCollough](calemccollough.github.io)

                            All right reserved  (R).

        Licensed under the Apache License, Version 2.0  (the "License"); you may
        not use this file except in compliance with the License. You may obtain
        a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/

#include <_Com/MIDI/MIDIMap.h>

namespace _Com { namespace MIDI {

MIDIMap::MIDIMap ()
{
}

byte MIDIMap::GetState ()
{
    return 0;
}

const char* MIDIMap::SetState (byte Value)
{
    return 0;
}

const char* MIDIMap::Do (const char* Query, byte Index, Roombot* Bot)
{
    switch (Index)
    {
        case 0: return I2P::NumMembers (0);
    }
    
    return Query ? Enquery ("MIDIMap", "_Com::MIDI"): InvalidIndex ();
}

}   //< namespace MIDI
}   //< namespace _Com