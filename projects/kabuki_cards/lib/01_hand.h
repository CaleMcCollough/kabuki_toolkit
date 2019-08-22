/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /projects/kabuki_cards/lib/00_hand.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-9 Cale McCollough <<calemccollough.github.io>>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>

#include "cards/hand.h"

#if SEAM == SCRIPT2_UNIPRINTER
#include <script2/module_debug.inl>
#else
#include <script2/module_release.inl>
#endif

using namespace _;

namespace kabuki_cards {
inline const CH1* Uniprinter(const CH1* args) {
#if SEAM >= SCRIPT2_UNIPRINTER
  A_TEST_BEGIN;
  D_COUT("Creating deck...");

  Deck pack(Deck::Culture Deck::kFrench, Deck::kAcesHighOrLow,
            Deck::kDoesNotContainJokers);

  CardStack deck = CardStack(pack);

  deck.Shuffle();

  D_COUT("Creating playerHand");

  Hand playerHand(deck.TakeNextCard(), deck.TakeNextCard()),
      dealersHand(deck.TakeNextCard(), deck.TakeNextCard());

  D_COUT("Testing string Hard::tostring ()...");
  D_COUT(playerHand.tostring);
  D_COUT(dealersHand.tostring);

  D_COUT(
      "Creating Hands Player{Ace of Hearts, Ace of Clubs) Dealer{ King of "
      "Hearts, Nine of Diamonds } ...");

  players_hand.SetCards();

#endif
  return 0;
}

}  // namespace kabuki_cards
