/** Kabuki Starship
    @file       /.../Source-Impl/_Math/Fraction.cpp
    @author  Cale McCollough <https://calemccollough.github.io>
    @license Copyright 2016 (C) Cale McCollough <cale.mccollough@gmail.com>

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

#include <_Math/Fraction.h>

namespace _Math { namespace Operators {
    
Fraction_f::Fraction_f (float thisNumberator, float thisDenominator)
{
    numberator = thisNumberator;
    denominator = thisDenominator;
}

float Fraction_f::getNumberator ()
{
    return numberator;
}

void Fraction_f::getNumberator (float Value)
{
    numberator = Value;
}

float Fraction_f::getDenominator ()
{
    return denominator;
}

void Fraction_f::getDenominator (float Value)
{
    denominator = Value;
}

void Fraction_f::print (I2P::Expression& slot)
{

}

}   //< namespace Operators
}   //< namespace _Math
