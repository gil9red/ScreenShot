#ifndef GRABCURSORMOUSE_H
#define GRABCURSORMOUSE_H

// класс метод которого возвращает pixmap текущего курсора
// реализованно используя winapi функции

#include <QtGui>
#include <QtCore>

#include <windows.h>

class UGrabCursorMouse
{
public:
    UGrabCursorMouse();
    QPixmap grabCurrentCursor();

private:
    QPixmap topPart(QPixmap pixmap);
    QPixmap bottomPart(QPixmap pixmap);
    void drawTop(QPixmap& dest, const QPixmap& src);
    QPixmap compileIcon(QPixmap p1Top, QPixmap p2Top, QPixmap p2Bottom);
};

#endif // GRABCURSORMOUSE_H
