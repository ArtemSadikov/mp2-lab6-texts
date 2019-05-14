#pragma once

#include "ttext.h"

class TTextViewer {
public:
    static void Insert(PTText pText);
    static void Delete(PTText pText);
    static void Navigation(PTText pText);
    static void Interface(PTText pText);
};