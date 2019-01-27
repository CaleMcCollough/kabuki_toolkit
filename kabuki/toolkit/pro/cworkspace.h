/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    /kabuki/features/pro/cworkspace.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-19 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>
#if SEAM >= KABUKI_TOOLKIT_PRO_1
#ifndef INCLUDED_KABUKI_TOOLKIT_PRO_PROJECT
#define INCLUDED_KABUKI_TOOLKIT_PRO_PROJECT 1

#include "cwidget.h"

namespace _ {

/*  */
class SDK Project {
 public:
  /* Constructor. */
  Project();

  /* Copy constructor copies the other ojbect. */
  Project(const Project& p);

  /* Destructor. */
  virtual ~Project();

  /* Adds the given controller to the workspace. */
  void Add(Widget* w);

  /* Gets the number of widgets in the project. */
  SI4 GetNumWidgets();

  /* Prints this object to the terminal. */
  _::Utf& Print(_::Utf& print);

 private:
  _::TArray<Widget*> widgets;  //< The array of Widgets.
};

}  // namespace _
#endif
#endif
