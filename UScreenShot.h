#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QtGui>
#include <QtCore>

#include <windows.h>

#include "USelectedArea.h"

const short PUSH_BUTTON_PRINT_SCREEN = 0x0000;

class UScreenShot : public QWidget
{
    Q_OBJECT
    
public:
    UScreenShot(QWidget *parent = 0);
    ~UScreenShot();

private:
    QLabel *labelScreenShot;
    QLabel *delaySpinBoxLabel;

    QPixmap originalPixmap;

    USelectedArea selectedArea;
    UGrabCursorMouse grabCursorMouse;

    QSpinBox *delaySpinBox;

    QCheckBox *cbHideThisWindow;
    QCheckBox *cbShowCursorMouse;

    QGroupBox *optionsGroupBox;
    QGridLayout *optionsGroupBoxLayout;

    QPushButton *pushButtonNewScreenshotSelectedArea;
    QPushButton *pushButtonNewScreenshotFullScreen;
    QPushButton *pushButtonSaveScreenshot;
    QPushButton *pushButtonQuitScreenshot;

    QHBoxLayout *buttonsLayout;
    QVBoxLayout *mainLayout;

    QSystemTrayIcon systemTrayIcon;

private:
    void createOption();
    void createButtons();
    void createIconTray();

    void registerHotKey(bool bValue);
    void clearLabelScreenShot();
    void updateLabelScreenShot();

public slots:
    void showSelectedArea();
    void takeScreenShotSelectedArea(QRect);
    void takeScreenShotFullScreen();
    void saveScreenshot();
    void shootScreen(int x = 0, int y = 0, int width = -1, int height = -1);

private slots:    
    void updateCheckBox();   
    void showHide(QSystemTrayIcon::ActivationReason reason);

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void closeEvent(QCloseEvent *);
    virtual void changeEvent(QEvent *event);
    virtual bool winEvent(MSG *message, long *result);
};

#endif // SCREENSHOT_H
