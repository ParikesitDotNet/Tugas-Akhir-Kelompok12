#include "mainwindow.h"
#include "ui_mainwindow.h"

ObatData MainWindow::getInputData() const
{
    return ObatData{
        ui->inputKode->text(),
        ui->inputNama->text(),
        static_cast<OBAT_KATEGORI>(ui->inputKategori->currentIndex()),
        static_cast<unsigned int>(ui->inputStok->value()),
        static_cast<unsigned int>(ui->inputHarga->value()),
        ui->inputExpired->date()};
}

void MainWindow::resetInputData()
{
    ui->inputKode->clear();
    ui->inputNama->clear();
    ui->inputStok->setValue(0);
    ui->inputHarga->setValue(0);
    ui->inputKategori->setCurrentIndex(0);
}

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