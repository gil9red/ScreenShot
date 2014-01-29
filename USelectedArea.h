#ifndef SELECTEDAREA_H
#define SELECTEDAREA_H

#include <QtGui>
#include <QtCore>

#include <windows.h>

#include "UGrabCursorMouse.h"

/*
 Этот класс наследуется от QWidget
 создает окно без рамки
 окно на весь экран и прозрачно на половину
 на этом окне можно выделять область
 при нажатии пробела, виджет подает сигнал и закрывается

 связываю этот класс с классом ScreenShot
 когда поступает сигнал, класс ScreenShot его получает и
 получает координаты выделенной области, после чего делает по
 ним скриншот области экрана
 */
class USelectedArea: public QWidget
{
    Q_OBJECT

public:
    int x0, y0, x1, y1;
    QRect rectSelectedArea;
    bool mousePress;

public:
    USelectedArea(QWidget *parent = 0);

signals:
    void areaIsSelected(QRect);
    void windowClose(void);

protected:
    void paintEvent(QPaintEvent *);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);
};

#endif // SELECTEDAREA_H
