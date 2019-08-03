#include <QDebug>
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	game = new gameJudge();
	connectNum = 0;
}

Widget::~Widget()
{
	delete ui;
}

void Widget::on_connectBtn_clicked()
{
	tcpServer = new QTcpServer(this);
	tcpServer->listen(QHostAddress::Any, ui->portText->text().toInt());
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnect()));
	ui->connectBtn->setEnabled(false);
}

void Widget::acceptConnect()
{
	//QTcpSocket qts = tcpServer->nextPendingConnection();
	//connect(qts, SIGNAL(readyRead()), this, SLOT(recv(int))
	clientSocket[connectNum] = tcpServer->nextPendingConnection();
	++connectNum;
	ui->status->append(QStringLiteral("Connection num: %1").arg(connectNum));
	qDebug()<<connectNum;
	if(connectNum == 2)
	{
		connect(clientSocket[0], SIGNAL(readyRead()), this, SLOT(recv1()));
		connect(clientSocket[1], SIGNAL(readyRead()), this, SLOT(recv2()));
	}
}

void Widget::recv1()
{
	QDataStream in(clientSocket[0]);
	QString recvMessage;
	in >> recvMessage;
	if(game->message(recvMessage))	//需要反馈
	{
		qDebug()<<"return true success";
		JSONObject obj(recvMessage.toStdString());
		if(obj["gameType"].toBool())	//五子棋胜负处理
		{
			obj["stopSign"] = true;
			obj["winner"] = true;
			sendToClient(obj.toJson(), clientSocket[0]);
			obj["winner"] = false;
			sendToClient(obj.toJson(), clientSocket[1]);
		}
		else				//围棋吃子处理
		{
			qDebug()<<"进入了围棋吃子处理chuli";
			obj["removeNum"] = 0;
			obj["removeFlag"] = Array();
			for(int i=1;i<=19;++i)
			{
				for(int j=1;j<=19;++j)
				{
					if(game->checkIsDead(i, j))
					{
						qDebug()<<"("<<i<<","<<j<<")check is dead";
						JSONObject removeFlag;
						removeFlag["row"] = i;
						removeFlag["column"] = j;
						obj["removeFlag"].pushBack(removeFlag);
						obj["removeNum"] = obj["removeNum"].toInt()+1;
					}
				}
			}
			sendToClient(obj.toJson(), clientSocket[0]);
			sendToClient(obj.toJson(), clientSocket[1]);
		}
	}
	else		//无需反馈，直接传递消息
	{
		sendToClient(recvMessage.toStdString(), clientSocket[1]);
	}
}

void Widget::recv2()
{
	QDataStream in(clientSocket[1]);
	QString recvMessage;
	in >> recvMessage;
	if(game->message(recvMessage))	//需要反馈
	{
		qDebug()<<"return true success";
		JSONObject obj(recvMessage.toStdString());
		if(obj["gameType"].toBool())
		{
			obj["stopSign"] = true;
			obj["winner"] = true;
			sendToClient(obj.toJson(), clientSocket[1]);
			obj["winner"] = false;
			sendToClient(obj.toJson(), clientSocket[0]);
		}
		else				//围棋吃子处理
		{
			obj["removeNum"] = 0;
			obj["removeFlag"] = Array();
			for(int i=1;i<=19;++i)
			{
				for(int j=1;j<=19;++j)
				{
					if(game->checkIsDead(i, j))
					{
						JSONObject removeFlag;
						removeFlag["row"] = i;
						removeFlag["column"] = j;
						obj["removeFlag"].pushBack(removeFlag);
						obj["removeNum"] = obj["removeNum"].toInt()+1;
					}
				}
			}
			sendToClient(obj.toJson(), clientSocket[0]);
			sendToClient(obj.toJson(), clientSocket[1]);
		}
	}
	else			//无需反馈，直接传递消息
	{
		sendToClient(recvMessage.toStdString(), clientSocket[0]);
	}
}

void Widget::sendToClient(std::string message, QTcpSocket *client)
{
	QString qMessage;
	qMessage = QString::fromStdString(message);
	QByteArray block;
	QDataStream out(&block, QIODevice::ReadWrite);
	out << qMessage;
	client->write(block);
}
