#pragma once

#include <vector>

class CSudokuBoard
{
public:
	// Create a new sudoku board of given size
	CSudokuBoard( int size );

	// Creates a new board based on given board
	CSudokuBoard ( CSudokuBoard* b );

	// Delete the board
	virtual ~CSudokuBoard(void);

	// Set a square on the board
	void SetSquare ( int x, int y, int value );

	// Get a square on the board
	int GetSquare ( int x, int y );

	// Return the size of the board
	int GetSize ( );

	// Copy values from board b
	void Copy ( CSudokuBoard* b );

	// Print the board to std out
	void Print ( );

protected:

	// The size of the board
	int boardSize;

	// Array of integers representing the board
	int **board;
};
