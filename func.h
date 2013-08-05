#ifndef FUNC_H
#define FUNC_H

#include <QProcess>
#include <QVector>
#include <QDebug>
#include <QRegExp>

#include "datastructure.h"

void initialize(PointersSet &mainSet);
void getAllMouseInfo(PointersSet &toReturn);

bool applyConstDecel(PointerElement &element, double newConstDecel);

#endif // FUNC_H
