#include "mainwindow.h"
#include "../ui_mainwindow.h"

void MainWindow::warningModal(QString title, QString msg)
{
    QMessageBox::warning(this, title, msg);
}