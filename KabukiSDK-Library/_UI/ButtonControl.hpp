/** Kabuki Software Development Kit
    @file    /.../KabukiSDK/_UI/ButtonControl.hpp
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

#include <KabukiSDK-Config.hpp>
#include <FreeI2P.hpp>
#include "AVControl.hpp"

namespace _Dev { namespace Controls {

class _KabukiSDK ButtonControl
/** A hardware or GUI button.
    Buttons need to be able to control both MIDI/DMX devices, and system control functions.
    A button can be linked to a physical hardware button, a software button, or both. A button can serve one of the 
    following functions:
    - Trigger a MIDI event.
    - Load a op-page.
    - Switch modes.
    - Do nothing.
*/
{
	    public:

    static const double MinDoubleClickTime,  //< The min double click time period in seconds.
        MaxDoubleClickTime,                  //< The max double click time period in seconds.
        DefaultDoublePressTime;              //< The default double press time period in seconds.

    /** An enumerated list of the differnt types of actions ButtonControls can perform. */
    enum Actions { Momentary = 0, Latching, PresureSensitive  };

    static const char* ActionStrings[];    //< An array of strings that corrispond to the Actions enum list.

    ButtonControl  (int newButtonAction = Momentary, int newStepSize = 0, double newDoublePressTime = 
        DefaultDoublePressTime);
    /*< Default constructor. */

    ButtonControl  (const ButtonControl  &O);
    /*< Copy constructor. */
    
    virtual ~ButtonControl () {}
    //< Destructor.

    void ProcessPress ();
    //< Processes the press logic before calling press ();
    
    void ProcessDepress ();
    //< Processes the depress logic before calling depress ();

    bool IsPressed () const;
    //< Gets true if the button is in a pressed state.
    void SetState  (bool buttonState);
    //< Sets the is_pressed variable to the new buttonState.

    double LastTimePressed () const;
    //< Gets th last time the button was pressed.

    int StepSize () const;
    /*< Gets this buttons step_Size.
        The step size is the increment that is added to the AVControl::value () every time the button is pressed. When 
        the value goes over the AVControl::maxValue (), it is reset to the AVControl::mixValue (). */
    
    void SetStepSize  (int value);
    //< Sets the _stepSize to the value.

    virtual void Toggle ();
    //< Toggles the state of the _isPressed if the type is latching. 

    int ButtonAction () const;
    //< The type of action this button performs: Momentary or latching.
    
    void SetButtonAction  (int newAction);
    //< Sets the button Action to the newAction.
    
    const char* ActionString () const;
    /*< Gets a string version of the buttonAction ().
        @see    Actions */

    // Pure virtual functions.

    virtual int MaxWordValue () const = 0;  //< Gets th max valu of a AVControl word.

    virtual void Press () = 0;              //< Triggered when a mode button is pressed.
    virtual void Depress () = 0;            //< Triggered when a mode button is depressed.
    virtual void Depress () = 0;        //< Triggered when a user "double clicks" a button.

    virtual const char* Label () const = 0;      //< Gets th label.
    /** Sets the label to the new label.
        @return Gets 0 upon success and 1 if the newLabel is too long.
        @see    Label::IsValid  (char). */
    virtual int SetLabel  (const char* newLabel) = 0;
    
    void Print (I2P::Terminal& Slot);
    /*< Prints this object to a terminal. */
    
    private:

    int buttonAction,                       //< The type of action this button performs  (i.e. momentary, latching, ect).
        stepSize;                           //< The step size of the button.
    
    bool isPressed;						    //< Variable represents if this button is pressed.

    double doublePressTime,                 //< The timespace of a double press in seconds.
       lastTimePressed;                     /*< The last time that the mode button was depressed.
												Used to calculate if the button was double clicked. */
};
}   //< namespace Controls
}   //< namespace _Dev
