#include "UScreenShot.h"

/// PUBLIC
UScreenShot::UScreenShot(QWidget *parent)
    : QWidget(parent)
{    
    originalPixmap = 0;

    createOption();
    createButtons();
    createIconTray();

    labelScreenShot = new QLabel();
    labelScreenShot->setSizePolicy(QSizePolicy::Expanding,
                                   QSizePolicy::Expanding);
    labelScreenShot->setAlignment(Qt::AlignCenter);
    labelScreenShot->setMinimumSize(240, 160);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(labelScreenShot);
    mainLayout->addWidget(optionsGroupBox);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);


    connect(&selectedArea, SIGNAL(areaIsSelected(QRect)),
            this, SLOT(takeScreenShotSelectedArea(QRect)));

//    // при закрытии окна выбора области, показываем основное окно
//    connect(&selectedArea, SIGNAL(windowClose()),
//            this, SLOT(show()));
}

UScreenShot::~UScreenShot()
{
    
}

/// PRIVATE
void UScreenShot::createOption()
{
    optionsGroupBox = new QGroupBox(tr("Опции"));

    delaySpinBox = new QSpinBox;
    delaySpinBox->setValue(5);
    delaySpinBox->setSuffix(tr(" с"));
    delaySpinBox->setMaximum(60);

    connect(delaySpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(updateCheckBox()));

    delaySpinBoxLabel = new QLabel(tr("Задержка снимка:"));

    cbHideThisWindow = new QCheckBox(tr("Скрыть это окно"));
    cbHideThisWindow->setCheckable(true);

    cbShowCursorMouse = new QCheckBox(tr("Показывать курсор мыши на снимке"));
    cbShowCursorMouse->setCheckable(true);

    optionsGroupBoxLayout = new QGridLayout;
    optionsGroupBoxLayout->addWidget(delaySpinBoxLabel, 0, 0);
    optionsGroupBoxLayout->addWidget(delaySpinBox, 0, 1);
    optionsGroupBoxLayout->addWidget(cbHideThisWindow, 1, 0);
    optionsGroupBoxLayout->addWidget(cbShowCursorMouse, 2, 0);

    optionsGroupBox->setLayout(optionsGroupBoxLayout);
}

void UScreenShot::createButtons()
{
    pushButtonNewScreenshotSelectedArea  = new QPushButton;
    pushButtonNewScreenshotFullScreen    = new QPushButton;
    pushButtonSaveScreenshot             = new QPushButton;
    pushButtonQuitScreenshot             = new QPushButton;

    pushButtonNewScreenshotSelectedArea->setText(tr("Снимок выбранной области"));
    pushButtonNewScreenshotFullScreen->setText(tr("Снимок всего экрана"));
    pushButtonSaveScreenshot->setText(tr("Сохранить снимок"));
    pushButtonQuitScreenshot->setText(tr("Выйти"));

    connect(pushButtonNewScreenshotSelectedArea, SIGNAL(clicked()),
            this, SLOT(showSelectedArea()));
    connect(pushButtonNewScreenshotFullScreen, SIGNAL(clicked()),
            this, SLOT(takeScreenShotFullScreen()));
    connect(pushButtonSaveScreenshot, SIGNAL(clicked()),
            this, SLOT(saveScreenshot()));
    connect(pushButtonQuitScreenshot, SIGNAL(clicked()),
            this, SLOT(close()));

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(pushButtonNewScreenshotSelectedArea);
    buttonsLayout->addWidget(pushButtonNewScreenshotFullScreen);
    buttonsLayout->addWidget(pushButtonSaveScreenshot);
    buttonsLayout->addWidget(pushButtonQuitScreenshot);
}

void UScreenShot::createIconTray()
{
    systemTrayIcon.setParent(this);
    systemTrayIcon.setIcon(QIcon(":/IconProgram"));
    connect(&systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(showHide(QSystemTrayIcon::ActivationReason)));
    systemTrayIcon.hide();
}

void UScreenShot::registerHotKey(bool bValue)
{
    if(bValue)
    {
        // регистрируем в винде что событие нажатия
        // кнопку скрина будет отлавливать наша программа
        RegisterHotKey(winId(), PUSH_BUTTON_PRINT_SCREEN,
                       0, VK_SNAPSHOT);
    }else    
        UnregisterHotKey(winId(), PUSH_BUTTON_PRINT_SCREEN);   
}

void UScreenShot::clearLabelScreenShot()
{
    originalPixmap = QPixmap();
    labelScreenShot->setPixmap(originalPixmap);
}

void UScreenShot::updateLabelScreenShot()
{
    if(!originalPixmap.isNull())
        labelScreenShot->setPixmap(originalPixmap.scaled(labelScreenShot->size(),
                                                         Qt::KeepAspectRatio,
                                                         Qt::SmoothTransformation));
}

/// PUBLIC SLOTS
void UScreenShot::showSelectedArea()
{
    if(cbHideThisWindow->isChecked())
        hide();

    selectedArea.show();
}
void UScreenShot::takeScreenShotSelectedArea(QRect r)
{
    // вообще все 4 параметра передаются с -1, если
    // произошла ошибка, но смысл их всех проверять...
    if(r.x() == -1)
        return;

    shootScreen(r.x(), r.y(), r.width(), r.height());
}
void UScreenShot::takeScreenShotFullScreen()
{
    if(cbHideThisWindow->isChecked())
        hide();

    pushButtonNewScreenshotFullScreen->setDisabled(true);
    QTimer::singleShot(1000 * delaySpinBox->value(), this, SLOT(shootScreen()));
}
void UScreenShot::saveScreenshot()
{
    QString filters;

    foreach(QByteArray byteArray, QImageWriter::supportedImageFormats())
    {
        QString filter = byteArray;
        filters += QString("%1 (*.%2)\n")
                .arg(filter.toUpper())
                .arg(filter);
    }

    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,
                                            "Сохранить как...",
                                            QDir::currentPath() + "/" + "untitled",
                                            filters);

    if(!fileName.isEmpty())
        originalPixmap.save(fileName);
}
void UScreenShot::shootScreen(int x, int y, int width, int height)
{
    if(delaySpinBox->value() != 0)
        qApp->beep();

    originalPixmap = QPixmap();
    // получаем скриншот выбранной области
    originalPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());

    if(cbShowCursorMouse->isChecked())
    {
        QPainter painter(&originalPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawPixmap(QCursor::pos(), grabCursorMouse.grabCurrentCursor());
    }

    originalPixmap = originalPixmap.copy(x, y, width, height);

    labelScreenShot->setPixmap(originalPixmap);

    updateLabelScreenShot();

    pushButtonNewScreenshotFullScreen->setDisabled(false);

    if(cbHideThisWindow->isChecked())
        QTimer::singleShot(1, this, SLOT(show()));

    // TODO AUTOSAVE SCREENSHOT

//    QString path = tr("D:\\Documents and Settings\\Admin\\Рабочий стол\\");
//    QString name = QDateTime::currentDateTime().toString("hh_mm_ss_zzzz");
//    originalPixmap.save(path + name + ".jpg");
}

/// PRIVATE SLOTS
void UScreenShot::updateCheckBox()
{
    if (delaySpinBox->value() == 0)
    {
        cbHideThisWindow->setDisabled(true);
        cbHideThisWindow->setChecked(false);
    }else    
        cbHideThisWindow->setDisabled(false);
}
void UScreenShot::showHide(QSystemTrayIcon::ActivationReason reason)
{
    //если нажато левой кнопкой продолжаем
    if(reason == QSystemTrayIcon::Trigger)
    {
        //если окно было не видимо - отображаем его
        if(!isVisible())
        {
            // показываем окно в нормальном состоянии
            showNormal();
            // переводим фокус на окно
            activateWindow();
            // иконку в трее скрываем
            systemTrayIcon.hide();

            // если окно "развернули" из трея
            // то и убираем регистрацию горячей кнопки
            registerHotKey(false);
        }
    }
}

/// PROTECTED
void UScreenShot::resizeEvent(QResizeEvent *)
{
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(labelScreenShot->size(), Qt::KeepAspectRatio);

    if (!labelScreenShot->pixmap()
            || scaledSize != labelScreenShot->pixmap()->size())    
        updateLabelScreenShot();    
}

void UScreenShot::closeEvent(QCloseEvent *)
{
//    systemTrayIcon.hide();
    qApp->quit();
}

void UScreenShot::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::WindowStateChange)
    {
        // если окно свернули
        if(isMinimized() == true)
        {
            // прячем окно с панели задач
            QTimer::singleShot(0, this, SLOT(hide()));

            // если окно свернули в трей, то регистрируем кнопку
            // Print Screen для своих нужд
            registerHotKey(true);

            // показываем значок программы в трее
            systemTrayIcon.show();
            // показываем подсказку
            systemTrayIcon.showMessage(tr("Подсказка"),
                                       tr("Для снимка нажмите Print Screen"),
                                       QSystemTrayIcon::Information);
        }
    }
}

bool UScreenShot::winEvent(MSG *message, long *result)
{
    // отловили событие нажатия
    if(message->message == WM_HOTKEY)
    {
        // если нажата кнопка скрин
        if(message->wParam == (unsigned)PUSH_BUTTON_PRINT_SCREEN)        
            shootScreen();

        return true;
    }
    return false;
}
