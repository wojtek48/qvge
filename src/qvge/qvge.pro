include(../lib.pri)

CONFIG(debug, debug|release){
        DESTDIR = $$OUT_PWD/../lib.debug
}
else{
        DESTDIR = $$OUT_PWD/../lib
}

TARGET = qvge
QT += core gui widgets printsupport xml

SOURCES += $$files($$PWD/*.cpp) \
    currentvalues.cpp
HEADERS += $$files($$PWD/*.h) \
    currentvalues.h
FORMS += $$files($$PWD/*.ui)
RESOURCES += $$files($$PWD/*.qrc)

INCLUDEPATH += $$PWD $$PWD/..

