#include "UGrabCursorMouse.h"

UGrabCursorMouse::UGrabCursorMouse()
{
}

QPixmap UGrabCursorMouse::topPart(QPixmap pixmap)
{
    QSize size(pixmap.width(), pixmap.height()/2);
    return pixmap.copy(QRect(QPoint(), size));
}

QPixmap UGrabCursorMouse::bottomPart(QPixmap pixmap)
{
    QSize size(pixmap.width(), pixmap.height()/2);
    return pixmap.copy(QRect(QPoint(0, size.height()), size));
}

void UGrabCursorMouse::drawTop(QPixmap& dest, const QPixmap& src)
{
    QPainter p(&dest);
    p.drawPixmap(QPoint(0,0), src);
}

QPixmap UGrabCursorMouse::compileIcon(QPixmap p1Top, QPixmap p2Top, QPixmap p2Bottom)
{
    QPixmap result = p1Top;
    const QBitmap bitmap = p2Top;
    result.setMask(bitmap);
    drawTop(result, p2Bottom);
    return result;
}

QPixmap UGrabCursorMouse::grabCurrentCursor()
{
    CURSORINFO cinfo;
    cinfo.cbSize = sizeof(CURSORINFO);
    bool result = ::GetCursorInfo(&cinfo);
    if(!result)
        return QPixmap();

    QPixmap pixmap;
    ICONINFO iconinfo = {0};
    GetIconInfo(cinfo.hCursor, &iconinfo);

//    DIBSECTION dsBitmap;
//    DIBSECTION dsMask;

//    if(!GetObjectA(iconinfo.hbmColor, sizeof(DIBSECTION), &dsBitmap))
//    {
//        if(GetObjectA(iconinfo.hbmMask, sizeof(DIBSECTION), &dsMask))
//        {
//            QPixmap p1 = QPixmap::fromWinHBITMAP(iconinfo.hbmMask);
//            QPixmap p2 = QPixmap::fromWinHBITMAP(iconinfo.hbmMask, QPixmap::Alpha);

//            QPixmap p1Top = topPart(p1);
//            QPixmap p2Top = topPart(p2);

//            QPixmap p2Bottom = bottomPart(p2);

//            pixmap = compileIcon(p1Top, p2Top, p2Bottom);
//        }

//        return pixmap;
//    }

    pixmap = QPixmap::fromWinHBITMAP(iconinfo.hbmColor, QPixmap::PremultipliedAlpha);
    return pixmap;
}
