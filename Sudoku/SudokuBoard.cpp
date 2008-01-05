#include "StdAfx.h"
#include "SudokuBoard.h"

// Create a new sudoku board of given size
CSudokuBoard::CSudokuBoard( int size )
{
	// Remember the size of the board
	boardSize= size;

	board= new int* [ boardSize ];

	for ( int i= 0; i < boardSize; i++ )
	{
		board [ i ]= new int [ boardSize ];

		// Init to -1 (unplaced)
		for ( int j= 0; j < boardSize; j++ )
		{
			board [ i ][ j ]= -1;
		}
	}
}

// Creates a new board based on given board
CSudokuBoard::CSudokuBoard ( CSudokuBoard* b )
{
	// Remember the size of the board
	boardSize= b->GetSize ();

	board= new int* [ boardSize ];

	for ( int i= 0; i < boardSize; i++ )
	{
		board [ i ]= new int [ boardSize ];

		// Copy board numbers
		for ( int j= 0; j < boardSize; j++ )
		{
			board [ i ][ j ]= b->GetSquare ( i, j );
		}
	}
}

// Copy values from board b
void CSudokuBoard::Copy ( CSudokuBoard* b )
{
	for ( int i= 0; i < boardSize; i++ )
	{
		//board [ i ]= new int [ boardSize ];

		// Copy board numbers
		for ( int j= 0; j < boardSize; j++ )
		{
			board [ i ][ j ]= b->GetSquare ( i, j );
		}
	}
}

// Delete the board
CSudokuBoard::~CSudokuBoard(void)
{
	for ( int i= 0; i < boardSize; i++ )
	{
		delete [] board [ i ];
	}

	delete [] board;
}

// Set a square on the board
void CSudokuBoard::SetSquare ( int x, int y, int value )
{
	// Check board boundaries
	if ( x >= 0 && x < boardSize && y >= 0 && y < boardSize )
	{
		board[x][y]= value;
	}
}

// Get a square on the board
int CSudokuBoard::GetSquare ( int x, int y )
{
	// Check boundary condition
	if ( x >= 0 && x < boardSize && y >= 0 && y < boardSize )
	{
		// Get number from rows, -1 if not placed yet
		return board[x][y];
	}
	else
	{
		return -1;	// Error value
	}
}

// Return the size of the board
int CSudokuBoard::GetSize ( )
{	
	return boardSize;
}

// Print the board to std out
void CSudokuBoard::Print ( )
{
	OutputDebugString ( "The board follows:\n" );

	for ( int i= 0; i < boardSize; i++ )
	{
		for ( int j= 0; j < boardSize; j++ )
		{
			CString str;

			str.Format ( " %d ", board[j][i] );
			OutputDebugString ( str );
		}

		OutputDebugString ( "\n" );
	}
}