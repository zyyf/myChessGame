#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include "gamejudge.h"
#include "JSONObject.h"
#include "Value.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

private slots:
	void on_connectBtn_clicked();
	void acceptConnect();
	void recv1();
	void recv2();


private:
	Ui::Widget *ui;

	QTcpServer *tcpServer;
	QTcpSocket *clientSocket[2];
	int connectNum;
	gameJudge *game;

	void sendToClient(std::string, QTcpSocket*);
};

#endif // WIDGET_H
