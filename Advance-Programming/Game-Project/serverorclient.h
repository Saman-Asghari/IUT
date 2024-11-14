#ifndef SERVERORCLIENT_H
#define SERVERORCLIENT_H

#include <QWidget>

namespace Ui {
class ServerOrClient;
}

class ServerOrClient : public QWidget
{
    Q_OBJECT

public:
    explicit ServerOrClient(QWidget *parent = nullptr);
    ~ServerOrClient();

private slots:
    void on_server_clicked();

    void on_client_clicked();

private:
    Ui::ServerOrClient *ui;
};

#endif // SERVERORCLIENT_H
