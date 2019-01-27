/* Kabuki Toolkit @version 0.x
@link    https://github.com/kabuki-starship/kabuki-toolkit.git
@file    /kabuki/features/touch/touch_control_midi.h
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
#if SEAM >= KABUKI_FEATURES_TOUCH_1
#ifndef HEADER_FOR_KT_HMI_MIDICONTROL
#define HEADER_FOR_KT_HMI_MIDICONTROL

#include "parameter.h"

namespace _ {

/* A controller for MIDI signals.
    


*/
class SDK MidiControl : public Parameter<SI4> {
 public:
  enum {
    NumChannels = 16  //< Number of MIDI channels.
  };

  /* Constructor. */
  MidiControl(const string& label = "", SI4 cc = 0, SI4 channel = 0,
              SI4 init_value = 0, SI4 newMinValue = 0, SI4 min_value = 127,
              SI4 word_size = 7, SI4 type = Parameter<SI4>::MidiControl);

  /* Copy constructor. */
  MidiControl(const MidiControl& o);

  /* Virtual destructor. */
  virtual ~MidiControl() {}

  /* gets the MIDI control change (CC) parameter. */
  SI4 GetCc() const;

  /* sets the control change (CC) parameter. */
  void SetCc(SI4 value);

  /* Sets the min and max values. */
  void SetMinMaxValues(SI4 newMin, SI4 newMax) override;

  /* sets the min value to the value. */
  void SetMinValue(SI4 value) override;

  /* sets the max value to the value. */
  void SetMaxValue(SI4 value) override;

  /* Triggers the Parameter<SI4> to fire. */
  virtual void Trigger();

  /* gets the header for toStringRow (). */
  virtual void PrintHeaderString() const;

  /* gets a column of the values without the labels. */
  void PrintRow() const override;

  /* Prints this object to the stdout. */
  ::_::Utf& Print(_::Utf& print) const;

 private:
  uint16_t cc_;  //< The control change (CC) parameter.
};

}  // namespace _
#endif  //< HEADER_FOR_KT_HMI_MIDICONTROL
#endif  //< #if SEAM >= KABUKI_FEATURES_TOUCH_1
