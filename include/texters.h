#ifndef __TEXTERS_H
#define __TEXTERS_H

#define TextOK          0 /* ошибок нет */
    /* коды ситуаций */
#define TextNoDown    101 /* нет подуровня для текущей позиции */
#define TextNoText    102 /* нет след. раздела текущего уровня */
#define TextNoPrev    103 /* текущая позиция в начале текста   */
    /* коды ошибок */
#define TextError    -102 /* ошибка в тексте */
#define TextNoMem    -101 /* нет памяти      */

#endif