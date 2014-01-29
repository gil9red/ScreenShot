TARGET = UScreenShot
TEMPLATE = app

DESTDIR = ../bin

SOURCES += main.cpp\
        UScreenShot.cpp \
    USelectedArea.cpp \
    UGrabCursorMouse.cpp

HEADERS  += UScreenShot.h \
    USelectedArea.h \
    UGrabCursorMouse.h

RC_FILE = icon.rc

OTHER_FILES += \
    icon.rc

RESOURCES += \
    resource.qrc
