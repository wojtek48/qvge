#ifndef CURRENTVALUES_H
#define CURRENTVALUES_H

#include <qstring.h>
#include <commonui/Const.h>

class CurrentValues
{
public:
    CurrentValues();
    QString shape;
    QString connection;
    static CurrentValues & instance() {
        static CurrentValues * _instance = 0;
        if ( _instance == 0 ) {
            _instance = new CurrentValues();
            _instance->shape = cKompUniwersalny;   //wpawl - domyślny komponent
            _instance->connection = cKanalZdarzen; //wpawl - domyślne połączenie
        }
        return *_instance;
    }
};
#endif // CURRENTVALUES_H
