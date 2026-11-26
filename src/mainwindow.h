#pragma once

#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVector>

enum OBAT_KATEGORI
{
    Bebas,
    Terbatas,
    Keras,
    Sirup
};

enum OBAT_STATE
{
    Aman,
    Pertengahan,
    Kedaluarsa
};

struct ObatData
{
    QString kode;
    QString nama;
    OBAT_KATEGORI kategori;
    unsigned int stok;
    unsigned int harga;
    QDate expired_date;
    bool isOut = false;
};

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnItemSave_clicked();

    void on_btnItemUpdate_clicked();

    void on_btnItemOut_clicked();

    void on_btnItemRemove_clicked();

    void on_inputKode_textChanged(const QString &arg1);

    void on_inputNama_textChanged(const QString &arg1);

    void on_inputKategori_currentIndexChanged(int index);

    void on_inputStok_valueChanged(int arg1);

    void on_inputHarga_valueChanged(int arg1);

    void on_inputExpired_dateChanged(const QDate &date);

    void on_tabelObat_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    int selectedRow = -1;
    ObatData getInputData() const;

    void fillObatTable();
    void resetInputData();
    void labelState();
    void validateItemForm();
    void warningModal(QString title, QString msg);
    OBAT_STATE compareTime(const QDate &dateInput) const;
};
