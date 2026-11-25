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

// Input data Handler
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

// Table Handler
void MainWindow::fillObatTable()
{
    ui->tabelObat->setRowCount(listObatData.size());

    for (int i = 0; i < listObatData.size(); i++)
    {
        QString outputObat;
        QString stateObat;

        switch (compareTime(listObatData[i].expired_date))
        {
        case Aman:
            stateObat = "Aman";
            break;
        case Pertengahan:
            stateObat = "Hampir Kedaluarsa";
            break;
        case Kedaluarsa:
            stateObat = "Kedaluarsa";
            break;
        default:
            stateObat = "Unknown";
            break;
        }

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
        ui->tabelObat->setItem(i, 5, new QTableWidgetItem(listObatData[i].expired_date.toString("dd-MM-yyyy")));
        ui->tabelObat->setItem(i, 6, new QTableWidgetItem(stateObat));
    }
}

// Update header label
void MainWindow::updateJenisAmt(int amt)
{
    QString outputText = QString("TOTAL JENIS OBAT: %1").arg(amt);
    ui->lblTotalObat->setText(outputText);
}

// Compare Kedaularsa State
OBAT_STATE MainWindow::compareTime(QDate dateInput)
{
    QDate currentDate = QDate::currentDate();
    QDate period = currentDate.addDays(90);

    if (dateInput < currentDate)
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

// Button Handler
void MainWindow::on_btnItemSave_clicked()
{
    ObatData dataLists = MainWindow::getInputData();
    listObatData.append(dataLists);
    fillObatTable();
    resetInputData();
    updateJenisAmt(listObatData.length());
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
