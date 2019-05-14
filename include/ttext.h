#ifndef __TTEXT_H
#define __TTEXT_H

#include <stack>
#include <fstream>
#include "tdatacom.h"
#include "textlink.h"

class TText;
typedef TText * PTText;

class TText : public TDataCom {
    protected:
        PTTextLink pFirst;      // указатель корня дерева
        PTTextLink pCurrent;      // указатель текущей строки
        stack< PTTextLink > path; // стек траектории движения по тексту
        stack< PTTextLink > st;   // стек для итератора
        PTTextLink GetFirstAtom (PTTextLink pl); // поиск первого атома
        void PrintText (PTTextLink ptl);         // печать текста со звена ptl
        void PrintTextF(ofstream& TxtFile, PTTextLink pl); // печать текста со звена pl в файл
        PTTextLink ReadText (ifstream &TxtFile); //чтение текста из файла
    public:
        TText (PTTextLink pl = NULL);
        ~TText () {pFirst = NULL;}
        PTText GetCopy();
        // навигация
        int GoFirstLink (); // переход к первой строке
        int GoDownLink ();  // переход к следующей строке по Down
        int GoNextLink ();  // переход к следующей строке по Next
        int GoPrevLink ();  // переход к предыдущей позиции в тексте
        // доступ
        string GetLine();   // чтение текущей строки
        void SetLine ( string s); // замена текущей строки 
        // модификация
        void InsDownLine (string s);    // вставка строки в подуровень
        void InsDownSection (string s); // вставка раздела в подуровень
        void InsNextLine (string s);    // вставка строки в том же уровне
        void InsNextSection (string s); // вставка раздела в том же уровне
        void DelDownLine ();        // удаление строки в подуровне
        void DelDownSection ();     // удаление раздела в подуровне
        void DelNextLine ();        // удаление строки в том же уровне
        void DelNextSection ();     // удаление раздела в том же уровне
        // итератор
        int Reset ();              // установить на первую звапись
        int IsTextEnded () const;  // текст завершен?
        int GoNext ();             // переход к следующей записи
        //работа с файлами
        void Read (char * pFileName);  // ввод текста из файла
        void Write (char * pFileName); // вывод текста в файл
        //печать
        void Print ();             // печать текста
};

#endif 