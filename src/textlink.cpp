#include "../include/textlink.h"
#include "../include/ttext.h"

TTextMem TTextLink::MemHeader;

void TTextLink::InitMemSystem(int size) { // инициализация данных
    MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink) * size];
    MemHeader.pFree  = MemHeader.pFirst;
    MemHeader.pLast  = MemHeader.pFirst + (size - 1);
    PTTextLink pLink = MemHeader.pFirst;

    for (int i = 0; i < size - 1; i++, pLink++) // размерка памяти
        pLink->pNext = pLink + 1;
    pLink->pNext = NULL;
}
/*=========================================*/
void TTextLink::PrintFreeLink() { // печать свободных звеньев
    PTTextLink pLink = MemHeader.pFree;
    cout << "List of free links" << endl;
    for ( ; pLink != NULL; pLink = pLink->pNext)
        cout << pLink->Str << endl;
}
/*=========================================*/
void * TTextLink::operator new(size_t size) { // выеделение звена
    PTTextLink pLink = MemHeader.pFree;
    if (MemHeader.pFree != NULL)
        MemHeader.pFree = pLink->pNext;
    return pLink;
}
/*=========================================*/
void TTextLink::operator delete(void *pM) { // освобождение звена
    PTTextLink pLink = (PTTextLink)pM;
    pLink->pNext = MemHeader.pFree;
    MemHeader.pFree = pLink;
}
/*=========================================*/
void TTextLink::MemCleaner(TText &txt) { // сборка мусора
    // пробная версия - в памяти только один текст
    string st;
    // маркировка строк текста - маркер "&&&"
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext()) {
        if (st.find("&&&") != 0)
            txt.SetLine("&&&" + txt.GetLine());
    }
    // маркировка списка свобоных звеньев
    PTTextLink pLink = MemHeader.pFree;
    for ( ; pLink != NULL; pLink = pLink->pNext)
        strcpy(pLink->Str, "&&&");
    // сборка мусора
    pLink = MemHeader.pFirst;
    for ( ; pLink <= MemHeader.pLast; pLink++) {
        if (strstr(pLink->Str, "&&&") != NULL) // строка текста или свободное звено
            strcpy(pLink->Str, pLink->Str + 3);// снятие маркировки
        delete pLink; // "неучтенное" звено в список свободных
    }
}
/*=========================================*/