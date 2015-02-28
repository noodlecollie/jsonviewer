#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QFileInfo>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_szLastFilePath = qApp->applicationDirPath();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file", m_szLastFilePath,
                                                    "JSON files (*.json);;JSON binaries (*.jbin);;All files (*.*)");
    
    if ( filename.isNull() ) return;
    
    QFile file(filename);
    
    if ( !file.open(QIODevice::ReadOnly) )
    {
        QMessageBox::critical(this, "Error", "Unable to open file for reading.");
        return;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QFileInfo info(file);
    m_szLastFilePath = info.canonicalFilePath();
    
    QJsonDocument document;
    if ( info.suffix() == "jbin" )
    {
        document = QJsonDocument::fromBinaryData(data);
    }
    else
    {
        QJsonParseError er;
        document = QJsonDocument::fromJson(data, &er);
        if ( er.error != QJsonParseError::NoError )
        {
            QMessageBox::critical(this, "Error", QString("An error occurred while parsing the JSON document: \"%0\" at position %1.").arg(er.errorString()).arg(er.offset));
            return;
        }
    }
    
    if ( document.isNull() )
    {
        QMessageBox::critical(this, "Error", QString("An error occurred while parsing the JSON document."));
        return;
    }
    
    ui->jsWidget->readFrom(document);
}
