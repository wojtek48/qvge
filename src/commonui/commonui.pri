# config
include($$PWD/../config.pri)

# app sources
SOURCES += $$files($$PWD/*.cpp)
SOURCES += $$files($$PWD/Źródła/*.cpp)
HEADERS += $$files($$PWD/*.h) \
    $$PWD/Const.h
FORMS += $$files($$PWD/*.ui)
RESOURCES += $$files($$PWD/*.qrc)

# base sources
include($$PWD/../appbase/appbase.pri)
#include($$PWD/../qvge/qvge.pri)

# includes 
INCLUDEPATH += $$PWD $$PWD/.. 
INCLUDEPATH += $$PWD/../3rdParty/qsint-widgets 
INCLUDEPATH += $$PWD/../3rdParty/qtpropertybrowser 

USE_OGDF{
    INCLUDEPATH += $$PWD/../3rdParty/ogdf/include

    SOURCES += $$files($$PWD/ogdf/*.cpp)
    HEADERS += $$files($$PWD/ogdf/*.h)
    FORMS += $$files($$PWD/ogdf/*.ui)
}

DISTFILES += \
    $$PWD/Icons/komponenty/bankDanych.PNG \
    $$PWD/Icons/komponenty/celZasobu.PNG \
    $$PWD/Icons/komponenty/generatorZdarzen.PNG \
    $$PWD/Icons/komponenty/kompPrzeplywu.PNG \
    $$PWD/Icons/komponenty/kompPrzetwarzania.PNG \
    $$PWD/Icons/komponenty/kompUniwersalny.PNG \
    $$PWD/Icons/komponenty/kompWymuszPrzeplyw.PNG \
    $$PWD/Icons/komponenty/procedury.PNG \
    $$PWD/Icons/komponenty/zasobStatyczny.PNG \
    $$PWD/Icons/komponenty/zrodloZasobu.PNG
