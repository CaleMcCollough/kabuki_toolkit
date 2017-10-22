/** Kabuki Starship
    @file    /.../Source/_id/TagLibrary.h
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

#include <string>
#include <vector>

namespace _id {

/** A container of strings sorted alphabetically.
    This object owns the memory for the strings. Each time a patch is added,
    each tag is added, a pointer to the string is passed back.
*/
class TagLibrary
{
    public:

    /** Constructs an empty tag library. */
    TagLibrary ();

    /** Gets the tag string, and adds it to the collection if it doesn't exist.
        @return Gets null if the tags list doesn't contatin the Tag, and 
            non-null if the Tag was added successfully. */
    string GetOrAddTag (string tag);
    
    /** Sorts the tags alphabetically for fast binary search. */
    void S ();
    
    /** Gets the number of tags. */
    int GetNumTags ();

    /** Prints this object to a Expression. */
    inline void Print ();
    
    private:
    
    vector<string> tags;     //< Collection of tag strings.
};
}   //  _id

