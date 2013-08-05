#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datastructure.h"
#include "func.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    
private:
    Ui::MainWindow *ui;

signals:
private slots:
    void changeConstDecelEdit(double doubleVal);
    void changeConstDecelEdit(int intVal);
    //void changeConstDecelEdit(QString stringVal);
    void changeConstDecelSlider(double doubleVal);
    void changeConstDecelSlider(QString stringVal);
    
    void changeCurrentMousePos(int newPos);

    void setValueFromEdit();

    //void clearAll();
public slots:
    bool showMouseList(PointersSet &mainSet);
    void showCurrentDetail(int currentRow);
};

#endif // MAINWINDOW_H
