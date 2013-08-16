#ifndef FUNC_H
#define FUNC_H

#include <QProcess>
#include <QVector>
#include <QDebug>
#include <QRegExp>

#include "datastructure.h"

extern PointersSet mainSet;

//void initialize(PointersSet &mainSet);
void initialize();
void getAllMouseInfo(PointersSet &toReturn);

bool applyCurChanges(PointerElement &element, double newConstDecel);
bool applyCurChangesTemporarily(double newConstDecel);
bool restoreCurMouseAttrs();



#endif // FUNC_H
