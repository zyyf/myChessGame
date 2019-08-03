#include <QDebug>
#include "gamejudge.h"

gameJudge::gameJudge()
{

}

bool gameJudge::message(QString recvMessage)	//返回T表示需要反馈，F表示不需反馈
{
	JSONObject obj(recvMessage.toStdString());
	if(obj["start"].toBool())	//游戏信息设定
	{
		qDebug()<<"到了信息设定";
		isGameStart = true;
		isFive = obj["gameType"].toBool();
		row = column = isFive ? 15 : 19;
		for(int i = 1; i <= row; ++i)
		{
			for(int j = 1; j <= column; ++j)
			{
				flag[i][j] = NONE;
			}
		}
		return false;
	}
	else
	{
		flag[obj["row"].toInt()][obj["column"].toInt()] = (obj["color"].toInt()==1)?BLACK:WHITE;
		if(judge(obj["row"].toInt(), obj["column"].toInt()))
		{
			qDebug()<<"进入了检查流CHEN....";
			return true;
		}
		return false;
	}
}

bool gameJudge::judge(int row, int column)
{
	if(isFive)				//五子棋判定
	{
		for(int i=row-4;i<=row;++i)			//同列5个
		{
			bool winSign = true;
			if(i<1 || i>11)
			{
				continue;
			}
			for(int j=i;j<i+5;++j)
			{
				if(flag[j][column] != flag[row][column])
				{
					winSign = false;
					break;
				}
			}
			if(winSign)
			{
				return true;
			}
		}
		for(int i=column-4;i<=column;++i)	//同行5个
		{
			bool winSign = true;
			if(i<1 || i>11)
			{
				continue;
			}
			for(int j=i;j<i+5;++j)
			{
				if(flag[row][j] != flag[row][column])
				{
					winSign = false;
					break;
				}
			}
			if(winSign)
			{
				return true;
			}
		}
		for(int i=4;i>=0;--i)	//反斜杠
		{
			bool winSign = true;
			if(((row-i) < 1) || ((column-i) < 1) || ((row-i) > 11) || ((column-i) > 11))
			{
				continue;
			}
			for(int j=0;j<=4;++j)
			{
				if(flag[row-i+j][column-i+j] != flag[row][column])
				{
					winSign = false;
					break;
				}
			}
			if(winSign)
			{
				return true;
			}
		}
		for(int i=4;i>=0;--i)	//斜杠
		{
			bool winSign = true;
			if(((row+i) > 15) || ((column-i) < 1) || ((row+i) < 5) || (column-i) > 11)
			{
				continue;
			}
			for(int j=0;j<=4;++j)
			{
				if(flag[row+i-j][column-i+j] != flag[row][column])
				{
					if(row == 5 && column == 11)
					{
						qDebug()<<"出错";
					}
					winSign = false;
					break;
				}
			}
			if(winSign)
			{
				return true;
			}
		}
		return false;
	}
	else				//围棋判定
	{
		for(int i=1;i<20;++i)
			for(int j=1;j<20;++j)
			{
				isDead[i][j]=false;
				isChecked[i][j]=false;
			}
		for(int i=1;i<=19;++i)
		{
			for(int j=1;j<=19;++j)
			{
				if(flag[i][j]==NONE || isChecked[i][j])		//如果此处无子或棋子已被检查过,则跳过
				{
					continue;
				}
				isChecked[i][j] = true;
				stoneType color = flag[i][j];
				findAlive(i, j, color);
				qDebug()<<"--------------------";
			}
		}
		bool removeSign = false;
		for(int i=1;i<=19;++i)
		{
			for(int j=1;j<=19;++j)
			{
				if(isDead[i][j])
				{
					qDebug()<<"("<<i<<","<<j<<")is dead";
					flag[i][j] = NONE;
					removeSign = true;
				}
			}
		}
		if(removeSign)	return true;
	}
	return false;
}

bool gameJudge::findAlive(int r,int c, stoneType color)
{
	qDebug()<<"findAlive("<<r<<","<<c<<").";
	isChecked[r][c] = true;
	if((r-1)>0 && flag[r-1][c]==NONE)
	{
		setAlive(r, c, color);
		return true;
	}
	else if((c-1)>0 && flag[r][c-1]==NONE)
	{
		setAlive(r, c, color);
		return true;
	}
	else if((r+1)<20 && flag[r+1][c]==NONE)
	{
		setAlive(r, c, color);
		return true;
	}
	else if((c+1)<20 && flag[r][c+1]==NONE)
	{
		setAlive(r, c, color);
		return true;
	}
	else if((r-1)>0 && flag[r-1][c]==color && !isChecked[r-1][c] && findAlive(r-1, c, color))
	{
		setAlive(r, c, color);
		return true;
	}

	else if((c-1)>0 && flag[r][c-1]==color && !isChecked[r][c-1] && findAlive(r, c-1, color))
	{
		setAlive(r, c, color);
		return true;
	}

	else if((r+1)<20 && flag[r+1][c]==color && !isChecked[r+1][c] && findAlive(r+1, c, color))
	{
		setAlive(r, c, color);
		return true;
	}

	else if((c+1)<20 && flag[r][c+1]==color && !isChecked[r][c+1] && findAlive(r, c+1, color))
	{
		setAlive(r, c, color);
		return true;
	}
	else
	{
		isDead[r][c] = true;
		return false;
	}
}

void gameJudge::setAlive(int r, int c, stoneType color)
{
	if((r-1)>0 && flag[r-1][c]==color && !isChecked[r-1][c])
	{
		isChecked[r-1][c] = true;
		setAlive(r-1, c, color);
	}
	else if((c-1)>0 && flag[r][c-1]==color && !isChecked[r][c-1])
	{
		isChecked[r][c-1] = true;
		setAlive(r, c-1, color);
	}
	else if((r+1)<20 && flag[r+1][c]==color && !isChecked[r+1][c])
	{
		isChecked[r+1][c] = true;
		setAlive(r+1, c, color);
	}
	else if((c+1)<20 && flag[r][c+1]==color && !isChecked[r][c+1])
	{
		isChecked[r][c+1] = true;
		setAlive(r, c+1, color);
	}
}

bool gameJudge::checkIsDead(int i, int j)
{
	if(isDead[i][j])
		return true;
	return false;
}
