#ifndef GAMEJUDGE_H
#define GAMEJUDGE_H

#include <QObject>
#include "JSONObject.h"
#include "Value.h"

enum stoneType
{
	BLACK, WHITE, NONE
};
/*
 * This is the class to process the game status.
 */
class gameJudge
{
public:
	gameJudge();
	bool message(QString);
	bool checkIsDead(int, int);

private:
	bool isGameStart;
	bool isFive;
	int row, column;
	stoneType flag[20][20];
	bool isChecked[20][20];
	bool isDead[20][20];

	bool judge(int, int);
	bool findAlive(int, int, stoneType);
	void setAlive(int, int, stoneType);
};

#endif // GAMEJUDGE_H
