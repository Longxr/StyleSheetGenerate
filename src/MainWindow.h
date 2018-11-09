#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "XmlRW.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_uiLookBtn_clicked();

    void on_generateLookBtn_clicked();

    void on_startBtn_clicked();

private:
    Ui::MainWindow* ui;

    XmlRW*          m_pXmlWorker;
};

#endif // MAINWINDOW_H
