/** Kabuki Software Development Kit
    @file    /.../KabukiSDK-Impl/_Id/Address.cpp
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2016 [Cale McCollough](calemccollough.github.io)

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

#include <_Id/Tag.hpp>

namespace _Id {

Tag::Tag ()
{

}

int Tag::getUID ()
{
    return 0;
}

int Tag::getUID (int I)
{
    return 0;
}

string Tag::getName ()
{
    return 0;
}

int Tag::getName (const char* S)
{
    return 0;
}

byte Password::getState ()
{
    return 0;
}

const char* Password::getState (byte Value)
{
    return 0;
}

const char* Password::op (I2P::Terminal& slot, int index, int Enq)
{
    switch (Index)
    {
        case 0: return I2P::NumMembers (0);
    }
    
    return Query ? Enquery ("Password", "_Id"): InvalidIndex ();
}
    
const char* Tag::print (I2P::Terminal& slot)
{
    return 0;
}

}   //< namespace _Id