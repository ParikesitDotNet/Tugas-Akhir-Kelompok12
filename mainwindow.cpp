#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(1280, 720);
}

MainWindow::~MainWindow()
{
    delete ui;
}

ObatData MainWindow::getInputData() const
{
    return ObatData{
        ui->inputKode->text(),
        ui->inputNama->text(),
        static_cast<OBAT_KATEGORI>(ui->inputKategori->currentIndex()),
        static_cast<unsigned int>(ui->inputStok->value()),
        static_cast<unsigned int>(ui->inputHarga->value()),
        ui->inputExpired->date()
    };
}

void MainWindow::on_btnItemSave_clicked()
{
}

void MainWindow::on_btnItemUpdate_clicked()
{
}

void MainWindow::on_btnItemOut_clicked()
{
}

void MainWindow::on_btnItemRemove_clicked()
{
}
