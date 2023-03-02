#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QCloseEvent>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//close event
public:
    void closeEvent(QCloseEvent *event)override;
private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket * m_socket;
    QLabel *lable;
};
#endif // MAINWINDOW_H
