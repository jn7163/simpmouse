#include <QDoubleValidator>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QValidator *editValidator = new QDoubleValidator(0, 1023, 3);
    ui->constDecelEdit->setValidator(editValidator);

    // Connect:
    connect( ui->constDecelSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeConstDecelEdit(int)) );
    connect( ui->constDecelEdit, SIGNAL(textEdited(QString)), this, SLOT(changeConstDecelSlider(QString)) );
    connect( ui->constDecelSlider, SIGNAL(sliderReleased()), this, SLOT(setValueFromEdit()) );
    connect( ui->constDecelEdit, SIGNAL(textEdited(QString)), this, SLOT(setValueFromEdit()) );

    connect( ui->mouseList, SIGNAL(currentRowChanged(int)), this, SLOT(changeCurMousePos(int)) );
    connect( ui->mouseList, SIGNAL(currentRowChanged(int)), this, SLOT(showCurrentDetail(int)) );


    // Initialize:
    this->showMouseList(mainSet);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Calculate method:
 * doubleVal = 256/intVal
 * intVal belongs to [16, 256]
 * doubleVal belongs to [1, 16]
 */

void MainWindow::changeConstDecelEdit(double doubleVal)
{
    ui->constDecelEdit->setText( QString::number(doubleVal, 'f', 3) );
}
void MainWindow::changeConstDecelEdit(int intVal)
{
    double doubleVal = 256/(double)intVal;
    this->changeConstDecelEdit(doubleVal);
}

void MainWindow::changeConstDecelSlider(double doubleVal)
{
    // the value of the slider should be between 16 and 256.
    int intValue = 256/doubleVal + 0.5;
    ui->constDecelSlider->setValue(intValue);
}
void MainWindow::changeConstDecelSlider(QString stringVal)
{
    double doubleVal = stringVal.toDouble();
    this->changeConstDecelSlider(doubleVal);
}

void MainWindow::changeCurMousePos(int newPos)
{
    mainSet.setCurMousePos(newPos);
}

void MainWindow::cancelCurChanges()
{
    
}

void MainWindow::setValueFromEdit()
{
    int curMousePos = mainSet.getCurMousePos();
    if (curMousePos == -1) {
        throw "curMousePos error!";
    }
    qDebug() << "curMousePos: " << mainSet.getCurMousePos();
    double constDecelVal = (ui->constDecelEdit->text()).toDouble();
    qDebug() << "constDecelVal: " << constDecelVal;
    applyCurChanges(mainSet[curMousePos], constDecelVal);
    return;
}

bool MainWindow::showMouseList(PointersSet &mainSet)
{
    if (mainSet.size() == 0) {
        qDebug() << "There is no element in mainSet.";
        return false;
    }

    // else: print them all.
    for (int i=0; i<mainSet.size(); i++) {
        new QListWidgetItem(mainSet[i].getName(), ui->mouseList);
    }
    return true;
}

void MainWindow::showCurrentDetail(int currentRow)
{
    if (currentRow < 0 || currentRow > mainSet.size()-1 ) {
        throw "currentRow error!";
    }
    PointerElement *curElement = &(mainSet[currentRow]);
    ui->nameLabel->setText( curElement->getName() );
    changeConstDecelEdit(curElement->getConstDecel());
    changeConstDecelSlider(curElement->getConstDecel());
}
