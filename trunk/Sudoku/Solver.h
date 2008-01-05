#pragma once

#include <vector>
#include "SudokuBoard.h"

// Position on the board
struct GridPos
{
	int x;
	int y;
};

class CSolver
{
public:
	CSolver(void);
	virtual ~CSolver(void);

	// Attempt to complete the board, true iff success
	bool Solve ( CSudokuBoard* board, bool* possible, int* count, int* curDepth, int* maxDepth, int* progress );

	// Print remaining numbers
	void PrintRemaining ( );

	int* m_progress;

protected:

	// Allocate and initialise to place vectors
	void InitialiseToPlaceVector ( std::vector<int>*** vectors, int size );

	// Remove numbers from to be placed vectors that have already been placed on board
	void RemovePlacedNumbers ( CSudokuBoard* board );

	// Get grid coords from square coords
	void GetGridCoords ( CSudokuBoard* board, int square, int index, int* x, int* y );

	// Is the specified number in the specified row
	bool IsInRow ( int number, int row );

	// Is the specified number in the specified col
	bool IsInCol ( int number, int col );

	// Is the specified number in the specified square
	bool IsInSquare ( int number, int squ );

	// Can number be placed in (x,y)
	bool IsPlacable ( int number, int x, int y );

	// Get square from grid coords
	void GetSquareCoords ( CSudokuBoard* board, int *square, int x, int y );

	// Returns true when complete
	bool Iterate ( bool* possible, int* count, int* curDepth, int* maxDepth );

	// Try and put the number in the specified row
	bool PlaceInRow ( int number, int row, int *x, bool* possible, 
		              std::vector<GridPos>* possiblePositions  );

	// Try and put the number in the specified col
	bool PlaceInCol ( int number, int col, int *y, bool* possible,
					  std::vector<GridPos>* possiblePositions  );

	// Try and put the number in the specified square
	bool PlaceInSquare ( int number, int square, int *index, bool* possible,
					  std::vector<GridPos>* possiblePositions  );

	// Place the number in the specified gird coordinates
	void PlaceNumber ( int number, int x, int y );

	// Is the board complete?
	bool IsComplete ( );

	// Numbers still to be placed in rows
	std::vector<int>** rowsToPlace;

	// Numbers still to be placed in cols
	std::vector<int>** colsToPlace;

	// Numbers still to be placed in squares
	std::vector<int>** squaresToPlace;
	
	// Current board
	CSudokuBoard* m_board;
};
