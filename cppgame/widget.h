#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>


namespace Ui {
class Widget;
}
/*
 * This class is the main widget of the client
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();



private slots:
    /*
     * Function: boardClicked
     * Usage: When the signal click() of class paintBoard is emited, this slot function will be called.
     * Input:
     *  size_t row: the row position of clicked
     *  size_t column: the column position of clicked
     */
	void boardClicked(size_t row, size_t column);
    /*
     * Function: recv
     * Usage: Process the infomation from server, including the sign of game start, and the information of put stone.
     *      This function will be called when there are some message are ready to read.
     */
	void recv();


	void on_ConnectBtn_clicked();
	void on_startBtn_clicked();

private:
    Ui::Widget *ui;

	QTcpSocket *tcpSocket;
	bool isTurn;
	int flagColor;			//1为黑，2为白

    /*
     * Function: send
     * Usage: send message to server
     * Input:
     *  std::string message: the message to send
     * Demo:
     *  send(JObject.tojson());
     */
	void send(std::string);
};

#endif // WIDGET_H
