#ifndef CURRENTVALUES_H
#define CURRENTVALUES_H

#include <QObject>

class CurrentValues : public QObject
{
    Q_OBJECT
public:
    explicit CurrentValues(QObject *parent = nullptr);

signals:

};

#endif // CURRENTVALUES_H
