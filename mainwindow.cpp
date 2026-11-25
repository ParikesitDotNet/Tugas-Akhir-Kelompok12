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
            stateObat = "Tidak diketahui";
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
        ui->tabelObat->setItem(i, 5, new QTableWidgetItem(listObatData[i].expired_date.toString("dd-MM-yyyy")));
        ui->tabelObat->setItem(i, 6, new QTableWidgetItem(stateObat));
    }
}

// Update labels
void MainWindow::labelState()
{
    int midExpired = 0, expired = 0;

    for (int i = 0; i < listObatData.length(); i++)
    {
        OBAT_STATE statusObat = compareTime(listObatData[i].expired_date);
        if (statusObat == Pertengahan)
        {
            midExpired++;
        }
        else if (statusObat == Kedaluarsa)
        {
            expired++;
        }
    }

    // Total obat
    ui->lblTotalObat->setText(QString("TOTAL JENIS OBAT: %1").arg(listObatData.length()));

    // Total mid-expired
    ui->lblHampirExpired->setText(QString("HAMPIR KEDALUARSA (90 HARI): %1").arg(midExpired));

    // Total expired
    ui->lblSudahExpired->setText(QString("SUDAH KEDALUARSA: %1").arg(expired));
}

// Button Handler
void MainWindow::on_btnItemSave_clicked()
{
    ObatData dataLists = MainWindow::getInputData();

    listObatData.append(dataLists);
    fillObatTable();
    resetInputData();
    labelState();
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

// Input Onchange handler
void MainWindow::validateItemForm()
{
    bool isInvalid = ui->inputKode->text().trimmed().isEmpty() ||
                     ui->inputNama->text().trimmed().isEmpty();

    ui->btnItemSave->setDisabled(isInvalid);
}

void MainWindow::on_inputKode_textChanged(const QString &arg1)
{
    validateItemForm();
}

void MainWindow::on_inputNama_textChanged(const QString &arg1)
{
    validateItemForm();
}