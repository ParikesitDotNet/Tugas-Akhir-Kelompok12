#include "mainwindow.h"
#include "../ui_mainwindow.h"

void MainWindow::showModal(MODAL_TYPE m, QString msg)
{
    switch (m)
    {
    case Info:
        QMessageBox::information(this, "Informasi", msg);
        break;

    case Warning:
        QMessageBox::warning(this, "Perhatian!", msg);
        break;

    case Error:
        QMessageBox::critical(this, "Error!", msg);
        break;

    default:
        QMessageBox::critical(this, "Error!", "Something went wrong!");
        break;
    }
}