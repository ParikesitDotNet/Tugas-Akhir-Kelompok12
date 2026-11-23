#pragma once

#include <QMainWindow>

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
};
