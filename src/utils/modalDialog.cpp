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

    case Danger:
        QMessageBox::critical(this, "Error!", msg);
        break;

    default:
        QMessageBox::critical(this, "Error!", "Something went wrong!");
        break;
    }
}

bool MainWindow::confimModal(QString title, QString msg)
{
    bool state = false;

    QMessageBox::StandardButton reply = QMessageBox::warning(
        this,
        title,
        msg,
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        state = true;
    }

    return state;
}