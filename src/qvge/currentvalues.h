#ifndef CURRENTVALUES_H
#define CURRENTVALUES_H

#include <qstring.h>

class CurrentValues
{
public:
    CurrentValues();
    QString shape;
    static CurrentValues & instance() {
        static CurrentValues * _instance = 0;
        if ( _instance == 0 ) {
            _instance = new CurrentValues();
        }
        return *_instance;
    }
};
#endif // CURRENTVALUES_H
