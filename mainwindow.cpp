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

QVector<ObatData> listObatData;

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
    ui->inputKode->setText("");
    ui->inputNama->setText("");
    ui->inputStok->setValue(0);
    ui->inputHarga->setValue(0);
    ui->inputKategori->setCurrentIndex(0);
}

void MainWindow::fillObatTable()
{
    ui->tabelObat->setRowCount(listObatData.size());

    for (int i = 0; i < listObatData.size(); i++)
    {
        QString outputObat;
        switch (listObatData[i].kategori)
        {
        case Bebas:
            outputObat = "Bebas";
            break;
        case Terbatas:
            outputObat = "Terbatas";
            break;
        case Keras:
            outputObat = "Keras";
            break;
        case Sirup:
            outputObat = "Sirup";
            break;
        default:
            outputObat = "Tidak diketahui";
            break;
        }

        ui->tabelObat->setItem(i, 0, new QTableWidgetItem(listObatData[i].kode));
        ui->tabelObat->setItem(i, 1, new QTableWidgetItem(listObatData[i].nama));
        ui->tabelObat->setItem(i, 2, new QTableWidgetItem(outputObat));
        ui->tabelObat->setItem(i, 3, new QTableWidgetItem(QString::number(listObatData[i].stok)));
        ui->tabelObat->setItem(i, 4, new QTableWidgetItem(QString::number(listObatData[i].harga)));
        // Untuk saat ini diisi tanggal expired dulu, akan diubah setelah diformat
        ui->tabelObat->setItem(i, 5, new QTableWidgetItem(listObatData[i].expired_date.toString("yyyy-MM-dd")));
    }
}

void MainWindow::on_btnItemSave_clicked()
{
    ObatData dataLists = MainWindow::getInputData();
    listObatData.append(dataLists);

    // for (int i = 0; i < listObatData.length(); i++)
    // {
    //     OBAT_KATEGORI tipeObat = listObatData[i].kategori;
    //     QString outputObat;

    //     switch (tipeObat)
    //     {
    //     case Bebas:
    //         outputObat = "Bebas";
    //         break;
    //     case Terbatas:
    //         outputObat = "Terbatas";
    //         break;
    //     case Keras:
    //         outputObat = "Keras";
    //         break;
    //     case Sirup:
    //         outputObat = "Sirup";
    //         break;
    //     default:
    //         outputObat = "Tidak diketahui";
    //         break;
    //     }

    //     qDebug() << "Obat ke-" << i << ": "
    //              << listObatData[i].kode << ", "
    //              << listObatData[i].nama << ", "
    //              << outputObat << ", "
    //              << listObatData[i].stok << ", "
    //              << listObatData[i].harga << ", "
    //              << listObatData[i].expired_date << ";";
    // }
    fillObatTable();
    resetInputData();
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
