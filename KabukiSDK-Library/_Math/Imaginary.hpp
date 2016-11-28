/** Kabuki Software Development Kit
    @file    /.../KabukiSDK/_Math/Imaginary.hpp
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

#pragma once

#include <FreeI2P.hpp>
#include <KabukiSDK-Config.hpp>

namespace _Math {

class _KabukiSDK Imaginary_f
/** An imaginary number stored as double types. */
{
    public:

    float A,        //< Vector A, imagined on the x-axis.
        B;          //< Vector B, imagined on the y-axis.

    Imaginary_f  ();
    /*< Constructs an uninitialized imaginary number. */

    Imaginary_f  (float Ax, float By);
    /*< Constructs an imaginary number from the given values. */

    float GetA () const;
    /*< Gets the A value. */

    float GetB () const;
    /*< Gets the A value. */

    void SetA (float Value);
    /*< Sets the A value to the new Value. */

    void SetB (float Value);
    /*< Sets the A value to the new Value. */

    float CalcAngle ();
    /*< Gets the angle between A and B. */

    float CalcMagnitude ();
    /*< Gets the magnitude of A and B. */

    void Print (I2P::Terminal& Slot);
    /*< Prints this object to the terminal. */
};

class _KabukiSDK Imaginary_d
/** An imaginary number stored as double types. */
{
    public:

    double A,       //< Vector A, imagined on the x-axis.
        B;          //< Vector B, imagined on the y-axis.

    Imaginary_d  ();
    /*< Constructs an uninitialized imaginary number. */

    Imaginary_d  (double Ax, double By);
    /*< Gets and sets the A value. */

    double GetA () const;
    /*< Gets the A value. */

    double GetB () const;
    /*< Gets the A value. */

    void SetA (double Value);
    /*< Sets the A value to the new Value. */

    void SetB (double Value);
    /*< Sets the A value to the new Value. */

    double CalcAngle ();
    /*< Gets the angle between A and B. */

    double CalcMagnitude ();
    /*< Gets the magnitude of A and B. */

    void Print (I2P::Terminal& Slot);
    /*< Prints this object to the terminal. */
};