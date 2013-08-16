#include "datastructure.h"

#include <QRegExp>


PointerElement::PointerElement()
{
    /**
      This initialize function shouldn't be used in normal case.
      */
    name = "";
    id = -1;
    constantDeceleration = -1;
    constDecelProperty = -1;
    qDebug() << "Warning: the default (shouldn\'t use) initialize function has been called.";
}
PointerElement::PointerElement(QString newName, int newId, double newConstDecel, int newConstDecelProperty)
{
    /**
      precondition:
          newConstDecel >= 1.0
      */
    name = newName;
    id = newId;
    constantDeceleration = newConstDecel;
    constDecelProperty = newConstDecelProperty;
}

QString PointerElement::getName()
{
    return this->name;
}
int PointerElement::getId()
{
    return this->id;
}
double PointerElement::getConstDecel()
{
    return this->constantDeceleration;
}
int PointerElement::getConstDecelProperty()
{
    return this->constDecelProperty;
}

void PointerElement::setConstDecel(double newConstDecel)
{
    this->constantDeceleration = newConstDecel;
}


PointersSet::PointersSet()
{
    Q_ASSERT(PointersVector.size() == 0);
    this->curMousePos = -1;
}

bool PointersSet::append(PointerElement newElement)
{
    PointersVector.append(newElement);
    return true;
}
/*
bool PointersSet::append(QVector<PointerElement> &newElementList)
{
    for (int i=0; i<newElementList.size(); ++i) {
        PointersVector.append(newElementList[i]);
    }
    return true;
}
*/
bool PointersSet::append(QString newName, int newId)
{
    // Check if there is a value called "Constant Deceleration:
    // The number of Constant Deceleration is 255 on my device, but different devices may be different.

    QString commandToRun = QString("xinput list-props %1").arg(newId);
    QProcess *process = new QProcess;
    process->start(commandToRun);
    process->waitForFinished();
    QByteArray result = process->readAll();
    QStringList lineList = QString(result).split("\n", QString::SkipEmptyParts);

    qDebug() << "The whole lineList:\n";
    for (int i=1; i<lineList.size(); ++i) {
        qDebug() << lineList[i];
    }


    int findLine = -1;
    for (int i=1; i<lineList.length(); ++i) { // i starts at 1 for skipping the device name.
        if (lineList[i].indexOf("Device Accel Constant Deceleration") >= 0) {
            qDebug() << "Find:\n" << lineList[i];
            findLine = i;
        }
    }
    if (findLine == -1) { // Not a property device.
        return false;
    }
    // else:
    QStringList decelList( lineList[findLine].split("\t", QString::SkipEmptyParts) );
    Q_ASSERT(decelList.size()==2);
    double newConstDecel = decelList[1].toDouble();
    qDebug() << "Constant Deceleration: " << newConstDecel;
    int startPos = decelList[0].indexOf("(") +1;
    int endPos = decelList[0].indexOf(")", startPos) -1;
    //qDebug()<< decelList[0].mid(startPos, endPos-startPos+1);
    int newConstDecelProperty = ( decelList[0].mid(startPos, endPos-startPos+1) ).toInt();
    qDebug() << "newConstDecelProperty: " << newConstDecelProperty;
    return this->append( PointerElement(newName, newId, newConstDecel, newConstDecelProperty) );
}

bool PointersSet::clear()
{
    PointersVector.clear();
    return true;
}

PointerElement &PointersSet::operator[] (int index)
{
    if (index > this->size()) {
        throw "Overflow!";
    }
    //return PointersVector.at(index);
    return PointersVector[index];
}


int PointersSet::getCurMousePos()
{
    return curMousePos;
}
bool PointersSet::setCurMousePos(int newPos)
{
    if (newPos < 0 || newPos >= this->size() ) {
        qDebug() << "Wrong number in setCurMousePos!";
        return false;
    }
    // else:
    this->curMousePos = newPos;
    qDebug() << "New curMousePos: " << newPos;
    return true;
}


int PointersSet::size()
{
    return PointersVector.size();
}



PointersSet mainSet;