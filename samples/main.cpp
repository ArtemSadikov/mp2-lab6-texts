// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// Copyright (c) Гергель В.П. 28.07.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//

#include <iostream>

#include "../include/ttext.h"
#include "../include/textviewer.h"

using namespace std;

int main()
{
  PTText pText;
  TTextLink::InitMemSystem(50);
  pText = new TText(new TTextLink((char*)"Header"));
  TTextViewer::Interface(pText);
  return 0;
}
