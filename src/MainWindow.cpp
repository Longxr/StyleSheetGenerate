#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pXmlWorker = new XmlRW(this);

    ui->uiPathEdit->setText("Z:/GithubCode/StyleSheetGenerate/Test/bllistwidget.ui");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_uiLookBtn_clicked()
{
    const QString documentLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择ui文件"), documentLocation, "Files (*.ui)");

    if(fileName.isEmpty()){
        return;
    }
    else{
        QFileInfo info(fileName);
        if("ui" != info.suffix()){
            qDebug() << "File type is not supported";
            return;
        }
    }

    ui->uiPathEdit->setText(fileName);
}

void MainWindow::on_generateLookBtn_clicked()
{
    //generate qss file
    if(ui->generatePathEdit->text().isEmpty()) {
        const QString documentLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        QString saveName = documentLocation + "/untitled.qss";
        QString fileName = QFileDialog::getSaveFileName(this, "qss file path", saveName, "Files (*.qss)");

        if (fileName.isEmpty())
        {
            return;
        }
        else{
            ui->generatePathEdit->setText(fileName);
        }
    }
}

void MainWindow::on_startBtn_clicked()
{
    //import ui file
    if(ui->uiPathEdit->text().isEmpty()) {
        on_uiLookBtn_clicked();
    }

    bool ret;

    ret = m_pXmlWorker->ImportFromUI(ui->uiPathEdit->text());
    if(ret) {
        qDebug() << "ImportFromUI success";
    }
    else {
        qDebug() << "ImportFromUI failed";
        return;
    }

    ret = m_pXmlWorker->ExportToQSS(ui->generatePathEdit->text());
    if(ret) {
        qDebug() << "ExportToQSS success";
    }
    else {
        qDebug() << "ExportToQSS failed";
    }
}
