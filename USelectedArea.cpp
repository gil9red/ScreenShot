#include "USelectedArea.h"

USelectedArea::USelectedArea(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.5);

    setGeometry(QApplication::desktop()->geometry());
    mousePress = false;
    x0 = -1;
    y0 = -1;
    x1 = -1;
    y1 = -1;
}

void USelectedArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(Qt::black);
    painter.setPen(Qt::black);
    painter.drawRect(rect());

    QPen pen;
    pen.setColor(Qt::white);
    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.setBrush(QColor(100, 100, 100));
    painter.drawRect(x0, y0, x1-x0, y1-y0);

    QString textHint;
    textHint = tr("Для снимка нажмите SPACE, ENTER или среднюю кнопку мыши");
    textHint+= tr("\n");
    textHint+= tr("Для закрытия нажмите ESCAPE, Alt+F4, или правую кнопку мыши");

    QFont font;
    font.setPixelSize(30);

    painter.setFont(font);
    painter.setPen(Qt::white);

    painter.drawText(rect(), Qt::AlignCenter, textHint);
}
void USelectedArea::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        close();
    }
    if(event->key() == Qt::Key_Space || event->key() == Qt::Key_Return)
    {
        if(x0 > x1)
        {
            int temp = x0;
            x0 = x1;
            x1 = temp;
        }

        if(y0 > y1)
        {
            int temp = y0;
            y0 = y1;
            y1 = temp;
        }


        close();
        emit areaIsSelected(QRect(x0, y0, x1-x0, y1-y0).normalized());
    }
}
void USelectedArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mousePress = true;
        x0 = event->x();
        y0 = event->y();

        setCursor(QCursor(Qt::CrossCursor));
    }
    if(event->button() == Qt::RightButton)
    {
        close();
    }
}
void USelectedArea::mouseReleaseEvent(QMouseEvent *event)
{
    mousePress = false;
    setCursor(QCursor(Qt::ArrowCursor));

    if(event->button() == Qt::MiddleButton)
    {
        close();
        emit areaIsSelected(QRect(x0, y0, x1-x0, y1-y0).normalized());
    }
}
void USelectedArea::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePress)
    {
        x1 = event->x();
        y1 = event->y();
        update();
    }
}

void USelectedArea::closeEvent(QCloseEvent *)
{
    emit windowClose();
}
