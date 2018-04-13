/** Kabuki Toolkit
    @version 0.x
    @file    ~/source/crabs/center.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough@gmail.com>;
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS,
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License.
*/

#pragma once
#include <stdafx.h>

#if MAJOR_SEAM >= 1 && MINOR_SEAM >= 2

#include "printer.h"

#if USING_PRINTER

#ifndef HEADER_FOR_CRABS_CENTER
#define HEADER_FOR_CRABS_CENTER

namespace _ {

/** Utility class for printing hex with operator<<. */
class Center {
    public:

    char* string;      //< String to print center aligned.
    int   num_columns; //< Number of columns to center.

    /** Constructor saves value for use with operator overloads. */
    Center (char* string, int num_columns) :
        string (string),
        num_columns (num_columns) {
    }

    Printer& Print (Printer& printer) {
        return printer;
    }
};

/** Prints the given char centered with a horizontal page bar to the left
    and right of the row.
    @param input The value to print.
    @param num_columns */
KABUKI char* PrintCentered (const char* string, int num_columns, char* text,
                            char* text_end, char delimiter = 0);
}       //< namespace _

/** Writes a nil-terminated UTF-8 or ASCII string to the
    printer. */
inline _::Printer& operator<< (_::Printer& printer, _::Center center) {
    printer.cursor = _::Print (center.string, printer.cursor, printer.end);
    return printer;
}

#endif  //< HEADER_FOR_CRABS_CENTER
#endif  //< USING_PRINTER
#endif  //< #if MAJOR_SEAM >= 1 && MINOR_SEAM >= 2
