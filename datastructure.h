#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QProcess>
#include <QVector>
#include <QDebug>

class PointerElement
{
    QString name;
    int id;
    double constantDeceleration;
    int constDecelProperty;

public:
    friend class PointersSet;

    PointerElement();
    PointerElement(QString newName, int newId, double newConstDecel, int newConstDecelProperty);

    QString getName();
    int getId();
    double getConstDecel();
    int getConstDecelProperty();

    void setConstDecel(double newConstDecel);



};

class PointersSet
{
private:
    QVector<PointerElement> PointersVector;
public:
    PointersSet();

    bool append(PointerElement newElement);
    bool append(QString newName, int newId);
    bool clear();
    PointerElement &operator[] (int index);

    int size();
};



/* mainSet contains all the attributes of moused and is the central data structure of the whole programme. */
extern PointersSet mainSet;
/* currentMousePos is the number of currently selected PointerElement in mainSet. */
extern int currentMousePos;

#endif // DATASTRUCTURE_H
