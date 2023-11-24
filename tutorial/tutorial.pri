FORMS += \
    $$PWD/Window.ui

HEADERS += \
    $$PWD/Window.h

SOURCES += \
    $$PWD/Window.cpp \
#    $$PWD/main.cpp

TARGET="ONLINE UPDATE"

include($$PWD/../QSimpleUpdater/QSimpleUpdater.pri)

RESOURCES += \
    $$PWD/image.qrc
