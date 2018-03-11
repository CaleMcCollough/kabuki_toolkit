/** Kabuki Toolkit
    @file    ~/source/kabuki/data/data_server.cc
    @author  Cale McCollough <calemccollough.github.io>
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

#include <stdafx.h>

#include "server.h"

using namespace _;

namespace kabuki { namespace data {

Server::Server ():
    Room ("kabuki.security.Server") {

}

const Op* Server::Star (wchar_t index, Expr* expr) {
    static const Op This = { "kabuki.security.Server",
        OpFirst ('A'), OpLast ('A'),
        "Datagram security server.", 0 };
    //void* args[1];
    switch (index) {
        case '?': return ExprQuery (expr, &This);
        case 'A': {
            static const Op kOpA = { "foo",
                Bsq<0> (), Bsq<0> (),
                "Why does everyone use foo?", 0 };
            if (!expr) return &kOpA;
        }
    }
    return nullptr;
}

}       //< security
}       //< kabuki