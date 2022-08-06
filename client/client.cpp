#include "client.h"
#include "ui_client.h"

#include <QDataStream>
#include <QTime>

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
    , _next_block_size(0)
{
    ui->setupUi(this);

    _socket = new QTcpSocket(this);

    connect(_socket, &QTcpSocket::readyRead, this, &Client::slot_ready_read);
    connect(_socket, &QTcpSocket::disconnected, _socket, &QTcpSocket::deleteLater);
    //TODO fix crash after client reconnect
}

Client::~Client()
{
    delete ui;
}

void Client::slot_ready_read()
{
    QDataStream in_stream(_socket);
    in_stream.setVersion(QDataStream::Qt_5_15);
    if (in_stream.status() == QDataStream::Ok)
    {
        for (;;)
        {
            if (_next_block_size == 0)
            {
                if (_socket->bytesAvailable() < 2)
                    break;

                in_stream >> _next_block_size;
            }

            if (_socket->bytesAvailable() < _next_block_size)
                break;

            QString str;
            QTime time;
            in_stream >> time >> str;
            qDebug() << time << str;
            ui->textBrowser->append(time.toString() + ": "+ str);

            _next_block_size = 0;
            break;
        }
    } else
        ui->textBrowser->append("error");
}

void Client::on_pushButton_clicked()
{
    _socket->connectToHost("127.0.0.1", 8080);
}

void Client::sent_2_server(const QString &str)
{
    _data.clear();
    QDataStream out_stream(&_data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_5_15);

//    out_stream << quint16(0) <<  str;
    out_stream << quint16(0) << QTime::currentTime() << str;
    out_stream.device()->seek(0);
    out_stream << quint16(_data.size() - sizeof(quint16));

    _socket->write(_data);
    ui->lineEdit->clear();
}

void Client::on_pushButton_2_clicked()
{
    sent_2_server(ui->lineEdit->text());
}

void Client::on_lineEdit_returnPressed()
{
    sent_2_server(ui->lineEdit->text());
}

