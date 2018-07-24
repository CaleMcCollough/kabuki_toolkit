// experiments.cpp : Defines the entry point for the console application.
//

#include <stdafx.h>
#include <cstdio>
#include <iostream>

using namespace std;

template <typename UI>
void PrintBinary(UI value) {
  for (int i = 0; i < sizeof(UI) * 8; ++i) {
    std::cout << (char)('0' + (value >> (sizeof(UI) * 8 - 1)));
    value = value << 1;
  }
}

int main() {
  cout << "\n\n\nTesting bit shifitng negative numbers for unsigned values:";

  uint32_t uvalue, upattern = 0x01010101;

  PrintBinary<uint32_t>(upattern);

  cout << "\n\nvalue = uvalue << -1 = ";

  uvalue = upattern << -1;

  PrintBinary<uint32_t>(uvalue);

  cout << "\n\nvalue = uvalue >> -1 = ";

  uvalue = upattern >> -1;

  PrintBinary<uint32_t>(uvalue);

  cout << "\n\n\nTesting bit shifitng negative numbers for signed values:";

  int32_t svalue, spattern = 0x01010101;

  PrintBinary<uint32_t>((uint32_t)spattern);

  cout << "\n\nvalue = uvalue << -1 = ";

  uvalue = spattern << -1;

  PrintBinary<uint32_t>((uint32_t)uvalue);

  cout << "\n\nvalue = uvalue >> -1 = ";

  uvalue = spattern >> -1;

  PrintBinary<uint32_t>((uint32_t)uvalue);

  system("PAUSE");

  return 0;
}
