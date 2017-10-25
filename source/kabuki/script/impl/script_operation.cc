/** kabuki::script
    @version 0.x
    @file    ~/source/kabuki/script/impl/script_operation.cc
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2017 Cale McCollough <calemccollough.github.io>;
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

#include <stdafx.h>
#include "../include/operation.h"
#include "../include/args.h"

namespace _ {

const uint_t* NumOperations (std::uintptr_t value) {
    return reinterpret_cast<const uint_t*> (value);
}

const uint_t* FirstOperation (uint_t value) {
    uintptr_t index = value;
    return reinterpret_cast<const uint_t*>(index);
}

uintptr_t Index (const void* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

uintptr_t CountCoperations (const Operation* op) {
    return Index (op->params);
}

void OperationPrint (const Operation* operand) {
    if (operand == nullptr)
        return;

    const uint_t* result = operand->result;

    if (Index (result) < 256) {
        // Print Operation Star
        std::cout << "\n| Num Operations:  " << CountCoperations (operand)
                  << "\n| Metadata:        " << operand->metadata << '\n';
    }

    std::cout << "| Name:         " << operand->name;
    ParamsPrint (operand->params);
    std::cout << '\n';
    ParamsPrint (operand->result);
    std::cout << "\n| Metadata:   " << operand->metadata << '\n';
}
uintptr_t ToUInt (Operand* operand) {
    if (operand == nullptr) return 0;
    const Operation* ope = operand->Star (0, nullptr);
    return ope == nullptr?0:
        reinterpret_cast<uintptr_t> (ope->params);
}

bool IsGroup (const Operation* ope) {
    if (!ope)
        return false;
    return (reinterpret_cast<uintptr_t> (ope->result) < ' ');
}

void OperandPrint (Operand* operand) {
    std::cout << "| Operation:        ";
    if (operand == nullptr) {
        std::cout << "null";
        PrintLine ("|", '_');
        return;
    }
    printf ("0x%p ", operand);
    const Operation* ope = operand->Star (0, nullptr);   //< Get Star header.
    std::cout << ope->name
        << "\n| NumOperations:  " << CountCoperations (ope)
        << "\n| Description:    " << ope->metadata << '\n';
    uintptr_t index      = Index (ope->result),
              stop_index = index + Index (ope->params);
    std::cout << "| FirstOperation: " << index << " LastOperation: "
        << stop_index;
    PrintLine ("|", '-');
    for (; index < stop_index; ++index) {
        ope = operand->Star (index, nullptr);
        if (ope != nullptr) {
            std::cout << "| " << index << ": " << ope->name << '\n'
                << "| input:   ";
            ParamsPrint (ope->params);
            std::cout << "| result:   ";
            ParamsPrint (ope->result);
            std::cout << "| Description: " << ope->metadata;
            if (index == stop_index)
                PrintLine ("|", '_');
            else
                PrintLine ("|", '-');
        } else {
            std::cout << "| " << index << ": null\n";
        }
    }
    //system ("PAUSE");
}

void PrintAddress (const byte* address, Operand* root) {
    if (address == nullptr)
        return;
    if (root == nullptr)
        return;
    int index = *address++;
    const Operation* ope = root->Star (index, nullptr);
    std::cout << ope->name;
    index = *address++;
    while (index) {
        ope = root->Star (index, nullptr);
        if (ope == nullptr)
            return;
        std::cout << '.' << ope->name;
        index = *address++;
    }
}

}   //< namespace _
