#define BufLength 80
#include "../include/ttext.h"

static char StrBuf[BufLength + 1]; // буфер для ввода строк
static int  TextLevel;             // номер текущего уровня текста

TText::TText(PTTextLink pl) {
    if (pl == NULL)
        pl = new TTextLink();
    pFirst = pl;
}
// навигация
int TText::GoFirstLink() { // переход к первой строке
    while (!path.empty())
        path.pop(); // очистка стека
    pCurrent = pFirst;
    if (pCurrent == NULL)
        SetRetCode(TextError);
    SetRetCode(TextOK);
    return RetCode;
}
/*=========================================*/
int TText::GoDownLink() { // переход к след. строке по Down
    SetRetCode(TextNoDown);
    if (pCurrent != NULL) {
        if (pCurrent->pDown != NULL) {
            path.push(pCurrent);
            pCurrent = pCurrent->pDown;
            SetRetCode(TextOK);
        }
    }
    return RetCode;
}
/*=========================================*/
int TText::GoNextLink() { // переход к след. строке по Next
    SetRetCode(TextNoText);
    if (pCurrent != NULL) {
        if (pCurrent->pNext != NULL) {
            path.push(pCurrent);
            pCurrent = pCurrent->pNext;
            SetRetCode(TextOK);
        }
    }
    return RetCode;
}
/*=========================================*/
int TText::GoPrevLink() { // переход к пред. позиции в тексте
    if (path.empty())
        SetRetCode(TextNoPrev);
    else {
        pCurrent = path.top();
        path.pop();
        SetRetCode(TextOK);
    }
    return RetCode;
}
// доступ
/*=========================================*/
string TText::GetLine() { // чтение текущей строки
    if (pCurrent == NULL)
        return string("");
    else 
        return string(pCurrent->Str);
}
/*=========================================*/
void TText::SetLine(string s) { // замена текущей строки
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else
        strncpy(pCurrent->Str, s.c_str(), TextLineLenght);
    pCurrent->Str[TextLineLenght - 1] = '\0';
}
// модификация
/*=========================================*/
void TText::InsDownLine(string s) { // вставка строки в подуровень
    if (pCurrent = NULL)
        SetRetCode(TextError);
    else {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink("", pd, NULL);
        strncpy(pl->Str, s.c_str(), TextLineLenght);
        pl->Str[TextLineLenght - 1] = '\0'; // установка, если s длинее Str;
        pCurrent->pDown = pl;               // установка указателя на новую строку
        SetRetCode(TextOK);
    }
}
/*=========================================*/
void TText::InsDownSection(string s) { // вставка раздела в подуровень
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else {
        PTTextLink pd = pCurrent->pDown;
        PTTextLink pl = new TTextLink("", NULL, pd);
        strncpy(pl->Str, s.c_str(), TextLineLenght);
        pl->Str[TextLineLenght - 1] = '\0'; // установка, если s длинее Str
        pCurrent->pDown = pl;               // установка указателя на новую строку
        SetRetCode(TextOK);
    }
}
/*=========================================*/
void TText::InsNextLine(string s) { // вставка строки в том же уровне
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else {
        PTTextLink pn = pCurrent->pNext;
        PTTextLink pl = new TTextLink("", pn, NULL);
        strncpy(pl->Str, s.c_str(), TextLineLenght);
        pl->Str[TextLineLenght - 1] = '\0'; // установка, если s длинее Str;
        pCurrent->pDown = pl;               // установка указателя на новую строку
        SetRetCode(TextOK);
    }
}
/*=========================================*/
void TText::InsNextSection(string s) { // вставка раздела в тот же уровень
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else {
        PTTextLink pn = pCurrent->pNext;
        PTTextLink pl = new TTextLink("", NULL, pn);
        strncpy(pl->Str, s.c_str(), TextLineLenght);
        pl->Str[TextLineLenght - 1] = '\0'; // установка, если s длинее Str;
        pCurrent->pDown = pl;               // установка указателя на новую строку
        SetRetCode(TextOK);
    }
}
/*=========================================*/
void TText::DelDownLine() { // удаление строки в подуровне
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pDown != NULL) {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pDown == NULL)
            pCurrent->pDown = pl2; // только для атома
        SetRetCode(TextOK);
    }
}
/*=========================================*/
void TText::DelDownSection() { // удаление раздела в подуровне
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pDown != NULL) {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pDown = pl2;
    }
}
/*=========================================*/
void TText::DelNextLine() { // удаление строки в том же уровне
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pNext != NULL) {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pNext == NULL)
            pCurrent->pDown = pl2;
        SetRetCode(TextOK);
    }
}
/*=========================================*/
void TText::DelNextSection() { // удаление раздела в том же уровне
    if (pCurrent == NULL)
        SetRetCode(TextError);
    else if (pCurrent->pNext != NULL) {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pNext = pl2;
        SetRetCode(TextOK);
    }
}
/*=========================================*/
int TText::Reset() { // установить на первую запись
    while (!st.empty())
        st.pop(); // очистка стека
    // текущая строка в стеке не харнится
    // исключение - первая строка текста, которая на дне стека
    pCurrent = pFirst;

    if (pCurrent != NULL) {
        st.push(pCurrent);
        if (pCurrent->pNext != NULL)
            st.push(pCurrent->pNext);
        if (pCurrent->pDown != NULL)
            st.push(pCurrent->pDown);
    }

    return IsTextEnded();
}
/*=========================================*/
int TText::IsTextEnded() const { // таблица завершена
    return !st.size();
}
/*=========================================*/
int TText::GoNext() { // переход к следующей записи
    if (!IsTextEnded()) {
        pCurrent = st.top();
        st.pop(); // если после выборки стек пуст, значит
        if (pCurrent != pFirst) { // первая строка текста уже была обработана
            if (pCurrent->pNext != NULL)
                st.push(pCurrent->pNext);
            if (pCurrent->pDown != NULL)
                st.push(pCurrent->pDown);
        }
    }

    return IsTextEnded();
}
/*=========================================*/
PTTextLink TText::GetFirstAtom(PTTextLink pl) { // поиск первого атома
    PTTextLink tmp = pl;
    while (!tmp->IsAtom()) { 
        st.push(tmp);
        tmp = tmp->GetDown();
    }
    return tmp;
}
/*=========================================*/
PTText TText::GetCopy() { // копирование текста
    PTTextLink pl1, pl2, p1 = pFirst, cpl = NULL;
    if (pFirst != NULL) {
        while (!st.empty())
            st.pop(); // очистка стека
        while (1) {
            if (p1 != NULL) { // переход к первому атому
                p1 = GetFirstAtom(p1);
                st.push(p1);
                p1 = p1->GetDown();
            }
            else if (st.empty())
                break;
            else {
                pl1 = st.top();
                st.pop();
                if (strstr(pl1->Str, "Copy") == NULL) { // первый этам создания копии
                    // создание копии - pDown на уже скопированный подуровень
                    pl2 = new TTextLink("Copy", pl1, cpl); // pNext на оригинал
                    st.push(pl2);
                    p1 = pl1->GetNext();
                    cpl = NULL;
                }
                else { // второй этап создания копии
                    pl2 = pl1->GetNext();
                    strncpy(pl1->Str, pl2->Str, TextLineLenght);
                    pl1->pNext = cpl;
                    cpl = pl1;
                }
            }
        }
    }
    return new TText(cpl);
}
/*=========================================*/
void TText::Print() {
    TextLevel = 0;
    PrintText(pFirst);
    Reset();
}
/*=========================================*/
void TText::PrintText(PTTextLink ptl) {
    if (ptl != NULL) {
        for (int i = 0; i < TextLevel; i++) {
            cout << " ";
            cout << " " << ptl->Str << endl;
            TextLevel++;
            PrintText(ptl->GetDown());
            TextLevel--;
            PrintText(ptl->GetNext());
        }
    }
}
/*=========================================*/
void TText::Read(char *pFileName) {
    ifstream TxtFile(pFileName);
    TextLevel = 0;
    if (&TxtFile != nullptr)
        pFirst = ReadText(TxtFile);
}
/*=========================================*/
PTTextLink TText::ReadText(ifstream &TxtFile) {
    PTTextLink pHead, ptl;
    pHead = ptl = new TTextLink();
    while (TxtFile.eof() == 0) {
        TxtFile.getline(StrBuf, BufLength, '\n');
        if (StrBuf[0] == ')') {
            TextLevel--;
            break;
        }
        else if (StrBuf[0] == '(') { // рекурсия
            TextLevel++;
            ptl->pDown = ReadText(TxtFile);
        }
        else { // присоединение следующей строки
            ptl->pNext = new TTextLink(StrBuf, NULL, NULL);
            ptl = ptl->pNext;
        }
    }
    ptl = pHead;
    if (pHead->pDown == NULL) { // удаление первой строки, если нет подуровня
        pHead = pHead->pNext;
        delete ptl;
    }
    return pHead;
}
/*=========================================*/
void TText::Write(char *pFileName) {
    ofstream TxtFile(pFileName);
    TextLevel = 0;
    PrintTextF(TxtFile, pFirst);
    Reset();
}

void TText::PrintTextF(ofstream& TxtFile, PTTextLink pl) {
    if (pl != NULL) {
        for (int i = 0; i < TextLevel; i++) {
            TxtFile << " ";
            TxtFile << pl->Str << endl;
            TextLevel++;
            PrintTextF(TxtFile, pl->GetDown());
            TextLevel--;
            PrintTextF(TxtFile, pl->GetNext());
        }
    }
}