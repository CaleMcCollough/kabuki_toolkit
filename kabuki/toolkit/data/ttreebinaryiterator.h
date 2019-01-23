/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    /kabuki/toolkit/data/ttreebinaryiterator.h
@author  Cale McCollough <cale.mccollough@gmail.com>
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
#if SEAM >= KABUKI_TOOLKIT_DATA_1
#ifndef INCLUDED_KABUKI_TOOLKIT_DATA_TREEBINARYITERATOR
#define INCLUDED_KABUKI_TOOLKIT_DATA_TREEBINARYITERATOR

#include "iterator.h"

namespace _ {

/** @warning This is some of the first code I EVER wrote; please don't make fun
of me for how bad this is. */

template <typename T>
class TTreeBinaryIterator {
 public:
  BinaryTreeIterator() { current = root_; }
  void* CurrentObject() { return current->data(); }
  void* NextObject() {
    void* nextObj = current->data();
    if (left != nullptr) current;
  }
  void* PrevObject() {
    prevIndex = index;
    index--;
    if (index < 1) {
      index = size();
      current = head;
    }
    current = current->prev;
    return current->data;
  }

  Link Current() { return current; }

  Link GetNext() {
    prevIndex = index;
    index++;
    if (index > size()) {
      index = 1;
      current = head;
    }
    current = current->next;
    return current;
  }

  Link* Prev() {
    prevIndex = index;
    index--;
    if (index < 1) {
      index = size();
      current = head;
    }
    current = current->prev;
    return current;
  }

  bool IsNotDone() {
    if (index > prevIndex)  // iterating forwards
    {
      if (current->next == head) return false;
    } else  // iterating backwards
    {
      if (current->prev == head) return false;
    }
    return true;
  }
  bool IsNotDone(SI4 forwardsOrBackwards)  // Value to be < or > 0
  {
    if (forwardsOrBackwards > 0)  // iterating forwards
    {
      if (current->next == head) return false;
    } else  // iterating backwards
    {
      if (current->prev == head) return false;
    }
    return true;
  }
  void removeLastObject() {
    if (index > prevIndex)  // iterating forwards
    {
      remove(current->prev);

      BinaryTreeIterator iteration = new BinaryTreeIterator();
      iteration.SetIndex(index - 1);
    } else {
      remove(current->next);
      Iterator iteration = new Iterator();
      iteration.SetIndex(index);
    }
  }

  void replaceLastObject(void* withThis) { current->prev.data = withThis; }

  void insertObject(void* ptr) { add(ptr, current); }

  SI4 direction()  // returns Point if last iteration went forwards
  {
    if (index > prevIndex)  // and -1 if the last iteration was backwards
      return 1;

    return -1;
  }

  void SetDirection(SI4 value) {
    if (value < 0)
      prevIndex = prevIndex + 1;
    else
      prevIndex = prevIndex - 1;
  }

  bool SetIndex(SI4 toHere) {
    if (toHere < 1 || toHere > size) return false;
    if (toHere > index) {
      if (toHere < index - toHere) {
        for (SI4 i = index; i < toHere; i++) current = current->next;
      } else {
        current = linkAtIndex(toHere);
      }
    } else {
      if (toHere < toHere - index) {
        for (SI4 i = index; i > toHere; i--) current = current->prev;
      } else {
        current = linkAtIndex(toHere);
      }
    }
    return true;
  }

  SI4 index() { return index; }

  SI4 size() { return size; };
}  // namespace _
}  // namespace _
#endif  //< INCLUDED_KABUKI_TOOLKIT_DATA_TREEBINARYITERATOR
#endif
