#ifndef SERVER_TCP_CHAT_H
#define SERVER_TCP_CHAT_H

#include <QTcpServer>

class QJsonObject;
class ServerCore;

class ServerTcpChat : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerTcpChat(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socket_desciptor) override;

public slots:
    void json_received(ServerCore* server_core, const QJsonObject& qjson_obj);

private:
    QVector<ServerCore*> _clients;
};

#endif // SERVER_TCP_CHAT_H
