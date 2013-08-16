#include "func.h"

//void initialize(PointersSet &mainSet)
void initialize()
{
    getAllMouseInfo(mainSet);
}


void getAllMouseInfo(PointersSet &toReturn)
{
    /**
      Get all mouse info from the output of command: "xinput --list --short".
      Please check the output by yourself and notice the table("\t").
      */


    // Run the script and get the list of mouses:
    QProcess *process = new QProcess;
    process->start("xinput --list --short");
    //process.waitForStarted();
    process->waitForFinished();
    QByteArray result = process->readAllStandardOutput();
    QString tmpAll(QString::fromLocal8Bit(result));
    delete process;
    process = NULL;

    QStringList lineList = tmpAll.split("\n");


    // Find out useful lines and throw out unuseful lines:
    lineList = lineList.filter(QRegExp("slave( {1,})pointer"));
    //qDebug() << lineList;

    // Ready for write:
    toReturn.clear();

    // Read the useful lines and generate PointersSet.
    QStringList tmpList;
    for (int i=0; i<lineList.size(); ++i) {
        tmpList = lineList[i].split("\t", QString::SkipEmptyParts);
        /* After splitting, the list contains three parts:
          ("NAME_WITH_SOME_USELESS_CHARACTERS", "id=X", "[slave pointer....]")
          */

        // Get id:
        int newId = (tmpList[1].mid(3)).toInt();

        // Get name (find and pickup useful characters):
        int startPos = tmpList[0].indexOf(QRegExp("[a-zA-Z]"));
        Q_ASSERT (startPos!=-1);
        int endPos = tmpList[0].lastIndexOf(QRegExp("[a-zA-Z]"));
        QString newName = tmpList[0].mid(startPos, endPos-startPos+1);
        qDebug() << newName << newId;
        toReturn.append(newName, newId);
    }

}

bool applyCurChanges(PointerElement &element, double newConstDecel)
{
    applyCurChangesTemporarily(newConstDecel);
    element.setConstDecel(newConstDecel);
    return true;
}

bool applyCurChangesTemporarily(double newConstDecel)
{
    //qDebug() << "content element: " << element.getId();
    int pos = mainSet.getCurMousePos();
    QString str = QString("xinput set-prop %1 %2 %3").arg(mainSet[pos].getId()).arg(mainSet[pos].getConstDecelProperty()).arg(newConstDecel);
    QProcess *process = new QProcess;
    process->start(str);
    process->waitForFinished();
    delete process;
    return true;
}

bool restoreCurMouseAttrs()
{
    int pos = mainSet.getCurMousePos();
    applyCurChangesTemporarily(mainSet[pos].getConstDecel());
    return true;
}