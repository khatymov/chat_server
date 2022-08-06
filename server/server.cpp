#include "server.h"

#include <QDataStream>
#include <QIODevice>
#include <QDebug>

Server::Server()
    :_next_block_size(0)
{
    if (this->listen(QHostAddress::Any, 8080))
        qDebug() << "server is running";
    else
        qDebug() << "liston error";
}

void Server::incomingConnection(qintptr socket_descriptor)
{
    _socket = new QTcpSocket;
    _socket->setSocketDescriptor(socket_descriptor);

    connect(_socket, &QTcpSocket::readyRead, this, &Server::slot_ready_read);
    connect(_socket, &QTcpSocket::disconnected, _socket, &QTcpSocket::deleteLater);

    _sockets.push_back(_socket);

    qDebug() << "Client desciptor: " << socket_descriptor;
}

void Server::slot_ready_read()
{
    _socket = (QTcpSocket*)sender();

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
            in_stream >> str;
            qDebug() << str;

            sent_data_to_client(str);
            _next_block_size = 0;
            break;
        }

    } else
        qDebug() << "stream error";
}

void Server::sent_data_to_client(const QString& str)
{
    _data.clear();

    QDataStream out_stream(&_data, QIODevice::WriteOnly);
    out_stream.setVersion(QDataStream::Qt_5_15);
    out_stream << str;
    for (int i = 0; i < _sockets.size(); i++)
        _sockets[i]->write(_data);
}


