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

bool applyChanges(int mousePos, double newConstDecel);
bool applyChangesTemporarily(int mousePos, double newConstDecel);
bool restoreMouseAttrs(int mousePos);



#endif // FUNC_H
