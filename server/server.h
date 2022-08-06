#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QByteArray>

class Server: public QTcpServer
{
    Q_OBJECT

public:
    Server();

    void sent_data_to_client(const QString& data);

private:
    quint16 _next_block_size;

    QByteArray _data;

    QTcpSocket* _socket;
    QVector<QTcpSocket*> _sockets;

public slots:
    void incomingConnection(qintptr socket_descriptor) override;
    void slot_ready_read();
};

#endif // SERVER_H
