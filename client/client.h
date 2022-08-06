#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

public slots:
    void slot_ready_read();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

private:
    void sent_2_server(const QString& str);

    Ui::Client *ui;

    QTcpSocket* _socket;

    QByteArray _data;

    quint16 _next_block_size;
};
#endif // CLIENT_H
