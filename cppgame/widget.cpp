#include <QPainter>
#include <QDebug>
#include "widget.h"
#include "ui_widget.h"
#include "JSONObject.h"
#include "Value.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

	ui->board->setVisible(false);

	isTurn = false;

	//信息传输处理turn
	tcpSocket = new QTcpSocket(this);
	connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recv()));

	connect(ui->board, SIGNAL(clicked(size_t,size_t)), this, SLOT(boardClicked(size_t,size_t)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::boardClicked(size_t row, size_t column)
{
	if(isTurn && ui->board->checkStone(row, column)==NONE)
	{
		ui->board->putStone(row, column, (flagColor==1)?BLACK:WHITE);
		JSONObject sendMessage;
		sendMessage["start"] = false;
		sendMessage["color"] = flagColor;
		sendMessage["gameType"] = ui->fiveBtn->isChecked()?true:false;
		sendMessage["row"] = (int) row;
		sendMessage["column"] = (int) column;
		sendMessage["stopSign"] = false;
		send(sendMessage.toJson());
		ui->turnSign->setText("It isn't your turn");
		isTurn = false;
	}
}



void Widget::recv()
{
	QDataStream in(tcpSocket);
	QString message;
	in >> message;
	JSONObject recvMessage(message.toStdString());
	if(recvMessage["start"].toBool())	//收到开始游戏的信息
	{
		ui->startBtn->setEnabled(false);
		ui->chooseColor->setEnabled(false);
		ui->chooseGame->setEnabled(false);
		ui->fiveBtn->setChecked(recvMessage["gameType"].toBool());
		ui->goBtn->setChecked(!recvMessage["gameType"].toBool());
		ui->blackBtn->setChecked(recvMessage["color"].toInt() == 2);
		ui->whiteBtn->setChecked(recvMessage["color"].toInt() == 1);
		ui->board->setBoard(recvMessage["gameType"].toBool()?15:19, recvMessage["gameType"].toBool()?15:19);
		ui->board->setVisible(true);
		ui->board->update();

		flagColor = 3 - recvMessage["color"].toInt();
		isTurn = flagColor == 1;
		ui->status->append(QString("%1 game begin!").arg(ui->fiveBtn->isChecked()?"Five":"Go"));
		ui->status->append(QString("You are %1").arg(isTurn?"black":"white"));
		ui->turnSign->setText((flagColor==1)?"It's your turn":"It isn't your turn");
		ui->ipText->setVisible(false);
		ui->ipLabel->setVisible(false);
		ui->portText->setVisible(false);
		ui->portLabel->setVisible(false);
	}
	else if(recvMessage["gameType"].toBool() && recvMessage["stopSign"].toBool())	//五子棋游戏结束的消息
	{

		if(recvMessage["winner"].toBool())
		{
			isTurn = false;
			ui->turnSign->setText("You win !!");
			ui->status->append("You win !!");
		}
		else
		{
			ui->board->putStone(recvMessage["row"].toInt(), recvMessage["column"].toInt(), (flagColor==1)?WHITE:BLACK);
			isTurn = false;
			ui->turnSign->setText("You lose.");
			ui->status->append("You lose.");
		}
	}
	else if(!recvMessage["gameType"].toBool() && recvMessage["removeNum"].toInt()>0)
	{
		if(ui->board->checkStone(recvMessage["row"].toInt(), recvMessage["column"].toInt()) == NONE)
		{
			ui->board->putStone(recvMessage["row"].toInt(), recvMessage["column"].toInt(), (flagColor==1)?WHITE:BLACK);
			isTurn = true;
		}
		for(int i=0;i<recvMessage["removeNum"].toInt();++i)
		{
			ui->board->removeStone(recvMessage["removeFlag"][i]["row"].toInt(), recvMessage["removeFlag"][i]["column"].toInt());
		}
	}
	else	//收到旗子变动的消息
	{
		ui->board->putStone(recvMessage["row"].toInt(), recvMessage["column"].toInt(), (flagColor==1)?WHITE:BLACK);
		ui->turnSign->setText("It's your turn");
		isTurn = true;
	}
}

void Widget::on_startBtn_clicked()
{
	ui->startBtn->setEnabled(false);
	JSONObject startMessage;
	startMessage["start"] = true;
	startMessage["color"] = ui->blackBtn->isChecked() ? 1 : 2;
	startMessage["gameType"] = ui->fiveBtn->isChecked() ? true : false;
	send(startMessage.toJson());
	flagColor = ui->blackBtn->isChecked() ? 1 : 2;
	isTurn = flagColor == 1;
	ui->status->append(QString("%1 game begin!").arg(ui->fiveBtn->isChecked()?"Five":"Go"));
	ui->status->append(QString("You are %1").arg((flagColor==1)?"black":"white"));
	ui->turnSign->setText((flagColor==1)?"It's your turn":"It isn't your turn");
	ui->board->setBoard(ui->fiveBtn->isChecked()?15:19, ui->fiveBtn->isChecked()?15:19);
	ui->board->setVisible(true);
	ui->board->update();
	ui->chooseColor->setEnabled(false);
	ui->chooseGame->setEnabled(false);
	ui->ipText->setVisible(false);
	ui->ipLabel->setVisible(false);
	ui->portText->setVisible(false);
	ui->portLabel->setVisible(false);
}

void Widget::on_ConnectBtn_clicked()	//与服务器连接
{
	ui->ConnectBtn->setEnabled(false);
	tcpSocket->connectToHost(ui->ipText->text(), ui->portText->text().toInt());
	if(!tcpSocket->waitForConnected(5000))
	{
		ui->status->append("Over time!");
		ui->ConnectBtn->setEnabled(true);
	}
	else
	{
		ui->startBtn->setEnabled(true);
		ui->chooseColor->setEnabled(true);
		ui->chooseGame->setEnabled(true);
		ui->ipText->setEnabled(false);
		ui->portText->setEnabled(false);
		ui->status->append("Connect Success!");
	}
}

void Widget::send(std::string message)
{
	QByteArray block;
	QDataStream out(&block, QIODevice::ReadWrite);
	out << QString::fromStdString(message);
	tcpSocket->write(block);
}
