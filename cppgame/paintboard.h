#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include <QWidget>

enum stoneType
{
	BLACK, WHITE, NONE
};

/*
 * This is a class for draw the chess board and the stone.
 * The object of this class is the chess board.
 */
class PaintBoard : public QWidget
{
    Q_OBJECT



public:
    explicit PaintBoard(QWidget *parent = nullptr);
	/*
	 * Function: setBoard
	 * Usage: Set the size of chess board
	 * Input:
	 *	int row: the row number
	 *	int column: the column number
	 * Demo:
	 *	setBoard(15, 15);	Set the chess board to FIVE GAME board.
	 */
	void setBoard(int, int);
	/*
	 * Function: paintEvent
	 * Usage: To complete the draw action.
	 *		  This function will be automatically called when the widget redraw.
	 */
    void paintEvent(QPaintEvent *event);
	/*
	 * Function: putStone
	 * Usage:
	 *	Put stone in the board
	 * Input:
	 *	size_t row: the row position of stone
	 *	size_t column: the column position of stone
	 *	stoneType stone: the color of the stone
	 * Demo:
	 *	putStone(10, 10, BLACK);	put a black stone in the position (10,10)
	 */
	void putStone(size_t row, size_t column, stoneType stone);
	/*
	 * Function: removeStone
	 * Usage: Remove the stone in the board
	 * Input:
	 *	size_t row: the row position of stone
	 *	size_t column: the column position of stone
	 * Demo:
	 *	removeStone(10, 10);	remove the stone in the position (10,10) of board
	 */
	void removeStone(size_t row, size_t column);
	/*
	 * Function: checkStone
	 * Usage: Check the color of a stone
	 * Input:
	 *	size_t row: the row position of stone
	 *	size_t column: the column position of stone
	 * Output:
	 *	stoneType: the color of the stone, return stoneType::BLACK or stoneType::WHITE or stoneType::NONE if there is not stone
	 * Demo:
	 *	checkStone(10, 10);		return BLACK
	 */
	stoneType checkStone(size_t row, size_t column);


signals:
    void clicked(size_t row, size_t column);

protected:
	/*
	 * Function: mouseReleaseEvent
	 * Usage: Detect the mouse click event in the board.
	 *		  This function will be automatically called when the event occurs.
	 */
    void mouseReleaseEvent(QMouseEvent *event);

private:
    size_t row;
    size_t column;
	stoneType flag[20][20];

};

#endif // PAINTBOARD_H
