#pragma once

#include <QDate>
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>
#include <QDate>
#include <QDateTime>

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

private:
    Ui::MainWindow *ui;
    ObatData getInputData() const;

    void fillObatTable();
    void resetInputData();
    void updateJenisAmt(int amt);
    OBAT_STATE compareTime(QDate dateInput);
};
