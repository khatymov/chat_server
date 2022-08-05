#include "server_core.h"

#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>

ServerCore::ServerCore(QObject *parent)
    : QObject{parent}
    , _server_socket(new QTcpSocket(this))
{
    connect(_server_socket, &QTcpSocket::readyRead, this, &ServerCore::receive_json);
}

bool ServerCore::set_socket_desciptor(qintptr socket_desciptor)
{
    _server_socket->setSocketDescriptor(socket_desciptor);
}

void ServerCore::receive_json()
{
    QByteArray json_data;
    QDataStream data_stream(_server_socket);

    while(true)
    {
        //save the current position of the stream
        data_stream.startTransaction();
        //fill by data
        data_stream >> json_data;
        if (data_stream.commitTransaction())
        {
            QJsonParseError json_error;
            const QJsonDocument json_doc = QJsonDocument::fromJson(json_data, &json_error);
            if (json_error.error == QJsonParseError::NoError)
                if (json_doc.isObject())
                    emit json_received(json_doc.object());
        }
    }
}
