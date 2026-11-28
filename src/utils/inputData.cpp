#include "mainwindow.h"
#include "../ui_mainwindow.h"

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

// Input Onchange handler
void MainWindow::validateItemForm()
{
    // Validasi Tombol Simpan Hijau
    bool isInvalid = ui->inputKode->text().trimmed().isEmpty() ||
                     ui->inputNama->text().trimmed().isEmpty();

    ui->btnItemSave->setDisabled(isInvalid);

    // Validasi Tombol Update Biru, disabled ketika data tidak berubah atau kolom tidak ditekan
    bool hasChanged = false;
    if (selectedRow >= 0 && selectedRow < listObatData.size())
    {
        ObatData current = getInputData();
        const ObatData &orig = listObatData[selectedRow];
        hasChanged = (current.kode != orig.kode) ||
                     (current.nama != orig.nama) ||
                     (current.kategori != orig.kategori) ||
                     (current.stok != orig.stok) ||
                     (current.harga != orig.harga) ||
                     (current.expired_date != orig.expired_date);
    }
    ui->btnItemUpdate->setDisabled(isInvalid || selectedRow < 0 || !hasChanged);
    ui->btnItemOut->setDisabled(isInvalid || selectedRow < 0);
    ui->btnItemRemove->setDisabled(isInvalid || selectedRow < 0);
}