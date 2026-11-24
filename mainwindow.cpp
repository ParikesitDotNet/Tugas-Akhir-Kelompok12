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

enum OBAT_KATEGORI
{
    BEBAS,
    TERBATAS,
    KERAS,
    SIRUP
};

enum OBAT_STATE
{
    SAFE,
    MID_EXPIRED,
    EXPIRED
};

struct ObatData
{
    char Kode[10];
    QString Nama;
    OBAT_KATEGORI Kategori;
    unsigned int stok;
    unsigned int harga;
    // ??? expired_date;
};

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
