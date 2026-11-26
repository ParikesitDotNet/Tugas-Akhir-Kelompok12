#include "mainwindow.h"
#include "../ui_mainwindow.h"

OBAT_STATE MainWindow::compareTime(const QDate &dateInput) const
{
    const QDate currentDate = QDate::currentDate();
    const QDate period = currentDate.addDays(90);

    if (dateInput <= currentDate)
    {
        return Kedaluarsa;
    }
    else if (dateInput < period)
    {
        return Pertengahan;
    }
    else
    {
        return Aman;
    }
}