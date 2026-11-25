#pragma once

#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    ObatData getInputData() const;

    void fillObatTable();
    void resetInputData();
    void labelState();
    void validateItemForm();
    OBAT_STATE compareTime(const QDate &dateInput) const;
};
