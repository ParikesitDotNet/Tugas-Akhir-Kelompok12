#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(1280, 720);
    ui->inputExpired->setDate(QDate::currentDate());
    ui->btnItemUpdate->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Table Handler
void MainWindow::fillObatTable()
{
    ui->tabelObat->setRowCount(listObatData.size());

    for (int i = 0; i < listObatData.size(); i++)
    {
        QString outputObat;
        QString stateObat;
        OBAT_STATE currState = compareTime(listObatData[i].expired_date);

        switch (currState)
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

        QTableWidgetItem *item = ui->tabelObat->item(i, 6);
        if (item)
        {
            QFont font = item->font();
            font.setBold(true);
            item->setFont(font);

            switch (currState)
            {
            case Kedaluarsa:
                item->setForeground(QColor("#ef4444"));
                break;
            case Pertengahan:
                item->setForeground(QColor("#facc15"));
                break;
            default:
                item->setForeground(QColor("#4ade80"));
                break;
            }
        }
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

    for (int i = 0; i < listObatData.length(); i++)
    {
        QString kodeObat = listObatData[i].kode;
        if (kodeObat.toLower() == dataLists.kode.toLower())
        {
            showModal(Warning, QString("Kode Obat '%1' Telah Tersimpan di Tabel!").arg(dataLists.kode));
            return;
        }
    }

    listObatData.append(dataLists);
    fillObatTable();
    resetInputData();
    labelState();
}

void MainWindow::on_btnItemUpdate_clicked()
{
    ObatData updated = getInputData();

    for (int i = 0; i < listObatData.size(); i++)
    {
        if (listObatData[i].kode.toLower() == updated.kode.toLower())
        {
            listObatData[i] = updated;
            fillObatTable();
            resetInputData();
            labelState();
            selectedRow = -1;
            ui->inputKode->setReadOnly(false);
            validateItemForm();
            return;
        }
    }

    showModal(Warning, QString("Kode Obat '%1' tidak ditemukan!").arg(updated.kode));
}

void MainWindow::on_btnItemOut_clicked()
{
    if (selectedRow < 0)
    {
        return;
    }

    listObatData[selectedRow].stok--;
    ObatData currData = listObatData[selectedRow];

    if (currData.stok < 1)
    {
        listObatData.removeAt(selectedRow);
        showModal(Info, QString("Stok obat '%1' dengan kode '%2' telah habis!").arg(currData.nama, currData.kode));
    }

    fillObatTable();
    validateItemForm();
    labelState();
}

void MainWindow::on_btnItemRemove_clicked()
{
    if (selectedRow < 0)
    {
        return;
    }

    ObatData currData = listObatData[selectedRow];

    if (!confimModal("Hapus obat?", "Apakah anda ingin menghapus obat ini secara permanen?"))
    {
        return;
    }

    listObatData.removeAt(selectedRow);

    fillObatTable();
    validateItemForm();
    labelState();
}

void MainWindow::on_tabelObat_cellClicked(int row, int column)
{
    Q_UNUSED(column);
    if (row < 0 || row >= listObatData.size())
    {
        return;
    }

    selectedRow = row;
    const ObatData &data = listObatData[row];
    ui->inputKode->setText(data.kode);
    ui->inputKode->setReadOnly(true);
    ui->inputNama->setText(data.nama);
    ui->inputKategori->setCurrentIndex(static_cast<int>(data.kategori));
    ui->inputStok->setValue(static_cast<int>(data.stok));
    ui->inputHarga->setValue(static_cast<int>(data.harga));
    ui->inputExpired->setDate(data.expired_date);

    validateItemForm();
}

// Input Forms
void MainWindow::on_inputKode_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    validateItemForm();
}

void MainWindow::on_inputNama_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    validateItemForm();
}

void MainWindow::on_inputKategori_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    validateItemForm();
}

void MainWindow::on_inputStok_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    validateItemForm();
}

void MainWindow::on_inputHarga_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    validateItemForm();
}

void MainWindow::on_inputExpired_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    validateItemForm();
}

void MainWindow::on_tabelObat_itemSelectionChanged()
{
    if (!ui->tabelObat->selectedItems().isEmpty())
    {
        return;
    }

    ui->inputKode->setReadOnly(false);
    selectedRow = -1;
    resetInputData();
    validateItemForm();
}
