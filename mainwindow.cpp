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

    // Link slider with edit:
    connect( ui->constDecelSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeConstDecelEdit(int)) );
    connect( ui->constDecelEdit, SIGNAL(textEdited(QString)), this, SLOT(changeConstDecelSlider(QString)) );
    connect( ui->constDecelSlider, SIGNAL(sliderReleased()), this, SLOT(applyChangesTemporarilyFromEdit()) );
    connect( ui->constDecelEdit, SIGNAL(textEdited(QString)), this, SLOT(applyChangesTemporarilyFromEdit()) );

    
    connect( ui->mouseList, SIGNAL(currentRowChanged(int)), this, SLOT(changeCurMouse(int)) );
    
    // Apply, Cancel, Refresh and Quit buttons:
    connect( ui->applyButton, SIGNAL(clicked()), this, SLOT(applyChangesFromEdit()) );
    connect( ui->refreshButton, SIGNAL(clicked()), this, SLOT(clearAllAndInitialize()) );
    connect( ui->discardButton, SIGNAL(clicked()), this, SLOT(restoreCurMouseAttrs()) );


    // Initialize:
    this->refreshMouseList(mainSet);
    
    // Testing:
    // disableConfigs();
}

MainWindow::~MainWindow()
{
    restoreAllMouseAttrs();
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

bool MainWindow::changeCurMouse(int newPos)
{
    // Note: All of the -1 issue should be treated at here.
    if (newPos == -1) {
        qDebug() << "changeCurMouse: pos is -1. Are you using the refresh button?";
        ui->nameLabel->setText("");
        disableConfigs();
        return false;
    }
    if (mainSet.getCurMousePos() == -1) {
        // That means user just selected a mouse for first time.
        enableConfigs();
    } else {
        restoreCurMouseAttrs();
    }
    mainSet.setCurMousePos(newPos);
    showCurDetail(newPos);
    return true;
}

void MainWindow::restoreCurMouseAttrs()
{
    int pos = mainSet.getCurMousePos();
    double constDecelVal = mainSet[pos].getConstDecel();
    applyChangesTemporarily(pos, constDecelVal);
    changeConstDecelEdit(constDecelVal);
    changeConstDecelSlider(constDecelVal);
}

void MainWindow::applyChangesFromEdit()
{
    int curMousePos = mainSet.getCurMousePos();
    qDebug() << "curMousePos: " << mainSet.getCurMousePos();
    double constDecelVal = (ui->constDecelEdit->text()).toDouble();
    qDebug() << "constDecelVal: " << constDecelVal;
    applyChanges(curMousePos, constDecelVal);
    return;
}
void MainWindow::applyChangesTemporarilyFromEdit()
{
    int curMousePos = mainSet.getCurMousePos();
    qDebug() << "curMousePos: " << curMousePos;
    double constDecelVal = (ui->constDecelEdit->text()).toDouble();
    qDebug() << "constDecelVal: " << constDecelVal;
    applyChangesTemporarily(curMousePos, constDecelVal);
    return;
}

void MainWindow::restoreAllMouseAttrs()
{
    for (int i=0; i<mainSet.size(); i++)
        restoreMouseAttrs(i);
    qDebug() << "Restored all temporary changes.";
    return;
}

bool MainWindow::refreshMouseList(PointersSet &mainSet)
{
    ui->mouseList->clear(); // note: this will emit currentRowChanged(-1).
    if (mainSet.size() == 0) {
        qDebug() << "Warning: There is no element in mainSet.";
        return false;
    }

    // else: print them all.
    for (int i=0; i<mainSet.size(); i++) {
        new QListWidgetItem(mainSet[i].getName(), ui->mouseList);
    }
    return true;
}

void MainWindow::showCurDetail(int currentRow)
{
    PointerElement *curElement = &(mainSet[currentRow]);
    ui->nameLabel->setText( curElement->getName() );
    changeConstDecelEdit(curElement->getConstDecel());
    changeConstDecelSlider(curElement->getConstDecel());
}



void MainWindow::clearAllAndInitialize()
{
    
    this->restoreCurMouseAttrs();
    ui->nameLabel->setText("");
    //this->disableConfigs();
    mainSet.clear();
    initialize();
    this->refreshMouseList(mainSet); // Note: this will emit currentRowChanged(-1).
    
    return;
}


void MainWindow::disableConfigs()
{
    ui->constDecelEdit->setEnabled(false);
    ui->constDecelSlider->setEnabled(false);
    return;
}
void MainWindow::enableConfigs()
{
    ui->constDecelEdit->setEnabled(true);
    ui->constDecelSlider->setEnabled(true);
    return;
}