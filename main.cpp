#include <QtGui>
#include <QtCore>

#include "UScreenShot.h"

class UTextCodec
{
public:
    static void initTextCodecs(const char *codecName)
    {
        QTextCodec *codec = QTextCodec::codecForName(codecName);
        QTextCodec::setCodecForCStrings(codec);
//        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForTr(codec);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false); // TODO

    UTextCodec::initTextCodecs("utf8");

    UScreenShot w;
    w.shootScreen();
    w.show();    

    return app.exec();
}

//#include <QtGui>


//class Frame: public QWidget
//{
//public:
//    Frame(QWidget *parent = 0)
//        : QWidget(parent),
//          mouseDown(false)
//    {
//        setMinimumSize(50, 50);

//        Qt::WindowFlags flags = Qt::FramelessWindowHint;

//        if(!parentWidget())
//            flags |= Qt::Tool;

//        setWindowFlags(flags);
//        setAttribute(Qt::WA_TranslucentBackground);

//        setMouseTracking(true);
//    }

//    void mousePressEvent(QMouseEvent *e)
//    {
//        QPoint pos = e->pos();

//        if(parentWidget())
//            pos = mapToParent(pos);

//        oldPos = pos;
//        mouseDown = e->button() == Qt::LeftButton;
//    }

//    void mouseMoveEvent(QMouseEvent *e)
//    {
//        int x = e->x();
//        int y = e->y();

//        if(mouseDown)
//        {
//            if(!top && !left && !right && !bottom)
//            {
//                QPoint pos = e->globalPos();

//                if(parentWidget())
//                    pos = e->pos();

//                move(pos - oldPos);
//                return;
//            }

//            int dx = x - oldPos.x();
//            int dy = y - oldPos.y();

//            QRect g = geometry();

//            if(top)
//                g.setTop(g.top() + dy);
//            if(left)
//                g.setLeft(g.left() + dx);
//            if(right)
//                g.setRight(g.right() + dx);
//            if(bottom)
//                g.setBottom(g.bottom() + dy);

//            setGeometry(g);

//            QPoint newOldPos;
//            newOldPos.setY(e->y());

//            if(!left)
//                newOldPos.setX(e->x());
//            else
//                newOldPos.setX(oldPos.x());

//            oldPos = newOldPos;

//        }else
//        {
//            QRect r = rect();
//            top = qAbs(y - r.top()) <= 5;
//            left = qAbs(x - r.left()) <= 5;
//            right = qAbs(x - r.right()) <= 5;
//            bottom = qAbs(y - r.bottom()) <= 5;
//            bool hor = left | right;
//            bool ver = top | bottom;

//            if(hor && bottom)
//            {
//                if(left)
//                    setCursor(Qt::SizeBDiagCursor);
//                else
//                    setCursor(Qt::SizeFDiagCursor);

//            }else if(ver && left)
//            {
//                if(bottom)
//                    setCursor(Qt::SizeBDiagCursor);
//                else
//                    setCursor(Qt::SizeFDiagCursor);

//            }else if(ver && right)
//            {
//                if(top)
//                    setCursor(Qt::SizeBDiagCursor);
//                else
//                    setCursor(Qt::SizeFDiagCursor);

//            }else if(hor)
//                setCursor(Qt::SizeHorCursor);

//            else if(ver)
//                setCursor(Qt::SizeVerCursor);

//            else
//                setCursor(Qt::ArrowCursor);
//        }
//    }

//    void mouseReleaseEvent(QMouseEvent *e)
//    {
//        mouseDown = false;
//    }

//    void paintEvent(QPaintEvent *)
//    {
//        QPainter painter(this);

//        QRect r = rect();

//        painter.save();
//        painter.setOpacity(0.2);
//        painter.setPen(Qt::NoPen);
//        painter.setBrush(Qt::black);
//        painter.drawRect(r);
//        painter.restore();

//        painter.setPen(QPen(Qt::black, 5));
//        painter.setBrush(Qt::transparent);
//        painter.drawRect(r.x() + 5, r.y() + 5, r.width() - 5*2, r.height() - 5*2);
//    }

//private:
//    QPoint oldPos;
//    bool mouseDown;
//    bool top, left, right, bottom;
//};


//int main(int argc, char **argv)
//{
//    QApplication app(argc, argv);

//    QWidget w;
//    w.setStyleSheet("QWidget{background: red}");
//    w.show();

//    Frame box(&w);
//    box.move(100, 100);
//    box.show();

//    return app.exec();
//}
