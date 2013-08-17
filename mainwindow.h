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
    
    void changeCurMousePos(int newPos);
    void cancelCurChanges();
    void cancelAllChanges();

    void applyChangesFromEdit();
    void applyChangesTemporarilyFromEdit();
    
    
    // Link the edit with the slider:
    void changeConstDecelEdit(double doubleVal);
    void changeConstDecelEdit(int intVal);
    void changeConstDecelSlider(double doubleVal);
    void changeConstDecelSlider(QString stringVal);
    
public slots:
    bool showMouseList(PointersSet &mainSet);
    void showCurDetail(int currentRow);
};

#endif // MAINWINDOW_H
