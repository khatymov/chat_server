#include "server_tcp_chat.h"

#include "server_core.h"

#include <QJsonDocument>
#include <QJsonObject>
//TODO del
#include <QDebug>

ServerTcpChat::ServerTcpChat(QObject *parent)
    : QTcpServer{parent}
{}

void ServerTcpChat::incomingConnection(qintptr socket_desciptor)
{
   ServerCore* server_handler = new ServerCore(this);

   connect(server_handler, &ServerCore::json_received, this, std::bind(&ServerTcpChat::json_received, this, server_handler, std::placeholders::_1));

   _clients.append(server_handler);
}

void ServerTcpChat::json_received(ServerCore* sender, const QJsonObject& qjson_obj)
{
    QJsonDocument doc(qjson_obj);
    QString str(doc.toJson(QJsonDocument::Compact));

    qDebug() << str;
}
