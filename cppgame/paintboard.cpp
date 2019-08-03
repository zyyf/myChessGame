#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>
#include "paintboard.h"

PaintBoard::PaintBoard(QWidget *parent) : QWidget(parent)
{
	for(int i = 1; i <= 19; ++i)
	{
		for(int j = 1; j <= 19; ++j)
		{
			flag[i][j] = NONE;
		}
	}
}

void PaintBoard::setBoard(int row, int column)
{
	this->row = row;
	this->column = column;
}

void PaintBoard::paintEvent(QPaintEvent *)
{
    const float wid = (float)this->width();
    const float hei = (float)this->height();
    const float start_row = wid / (row + 1);
    const float end_row = this->width() -start_row;
    const float start_column = hei / (column + 1);
    const float end_column = this->height() -start_column;

    //设置棋盘背景色
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, QColor(211, 185, 153));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QPainter painter(this);
    painter.setPen(Qt::black);
    //painter.setBrush(Qt::black);

    //画横线
    for(size_t i = 0; i < row; ++i)
    {
        painter.drawLine(QPointF(start_row, hei / (column + 1) * (i + 1)), QPointF(end_row, hei / (column + 1) * (i + 1)));
    }

    //画竖线
    for(size_t i = 0; i < column; ++i)
    {
        painter.drawLine(QPointF(wid /(row + 1) * (i + 1), start_column), QPointF(wid /(row + 1) * (i + 1), end_column));
    }

    //画星点
    painter.setBrush(Qt::black);
	painter.drawEllipse(QPointF(wid / 2, hei / 2), wid / (row + 1) / 8, hei / (column + 1) / 8);
	painter.drawEllipse(QPointF(wid / (row+1) * 4, hei / (column+1) * 4), wid / (row+1) / 8, hei / (column+1) / 8);
	painter.drawEllipse(QPointF(wid / (row+1) * 4, hei / (column+1) * (column-3)), wid / (row+1) / 8, hei / (column+1) / 8);
	painter.drawEllipse(QPointF(wid / (row+1) * (row-3), hei / (column+1) * 4), wid / (row+1) / 8, hei / (column+1) / 8);
	painter.drawEllipse(QPointF(wid / (row+1) * (row-3), hei / (column+1) * (column-3)), wid / (row+1) / 8, hei / (column+1) / 8);
	if(row==19)
	{
		painter.drawEllipse(QPointF(wid / (row+1) * 4, hei / 2), wid / (row+1) / 8, hei / (column+1) / 8);
		painter.drawEllipse(QPointF(wid / (row+1) * (row-3), hei / 2), wid / (row+1) / 8, hei / (column+1) / 8);
		painter.drawEllipse(QPointF(wid / 2, hei / (column+1) * 4), wid / (row+1) / 8, hei / (column+1) / 8);
		painter.drawEllipse(QPointF(wid / 2, hei / (column+1) * (column-3)), wid / (row+1) / 8, hei / (column+1) / 8);
	}

	//画旗子
	for(int i = 1; i <= row; ++i)
	{
		for(int j = 1; j <= column; ++j)
		{
			switch (flag[i][j]) {
			case BLACK:
				painter.setPen(Qt::black);
				painter.setBrush(Qt::black);
				break;
			case WHITE:
				painter.setPen(Qt::white);
				painter.setBrush(Qt::white);
				break;
			default:
				continue;
			}
			painter.drawEllipse(QPointF(wid / (row+1) * i, hei / (column+1) * j), wid / (row+1) / 3, hei / (column+1) / 3);
		}
	}
}

void PaintBoard::mouseReleaseEvent(QMouseEvent *event)
{
    const float wid = (float)this->width();
    const float hei = (float)this->height();
    int r = -1;
    int c = -1;

	for(int i = 0; i < row; ++i)
    {
		for(int j = 0; j < column; ++j)
        {
            float temp_x = wid /(row + 1) * (i + 1);
            float temp_y = hei / (column + 1) * (j + 1);
            if((abs(event->x() - temp_x) < (wid / (row + 1) / 2)) && (abs(event->y() - temp_y) < (hei / (column + 1) / 2)))
            {
                r = i + 1;
                c = j + 1;
                emit clicked(r, c);
            }
        }
    }
}

void PaintBoard::putStone(size_t row, size_t column, stoneType stone)
{
	if(flag[row][column] != NONE)
	{
		return;
	}
	flag[row][column] = stone;
	update();
}

void PaintBoard::removeStone(size_t row, size_t column)
{
	flag[row][column] = NONE;
	update();
}

stoneType PaintBoard::checkStone(size_t row, size_t column)
{
	return flag[row][column];
}
