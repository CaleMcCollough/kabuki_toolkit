/* TypeCraft - Teaching Typing through Mining and Crafting.
@link    https://github.com/kabuki-starship/kabuki-toolkit
@file    /project/typecraft/a.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#ifndef INCLUDED_TYPECRAFT_A
#define INCLUDED_TYPECRAFT_A 1

#include "../../../kabuki-toolkit/kabuki/crabs/public.h"

namespace typecraft {

/* The A in A*B.
 */
struct A : public _::Room {
 public:
  A() : A(1024) {}
};

}  // namespace typecraft
#endif