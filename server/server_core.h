#ifndef SERVER_CORE_H
#define SERVER_CORE_H

#include <QObject>
#include <QTcpSocket>

class QJsonObject;

class ServerCore : public QObject
{
    Q_OBJECT
public:
    explicit ServerCore(QObject *parent = nullptr);

    virtual bool set_socket_desciptor(qintptr socket_desciptor);

signals:
    void json_received(const QJsonObject& qjson_obj);

private slots:
    void receive_json();

private:
    QTcpSocket *_server_socket;
};

#endif // SERVER_CORE_H
