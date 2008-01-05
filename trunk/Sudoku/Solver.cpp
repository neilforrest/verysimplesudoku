#include "StdAfx.h"
#include "Solver.h"
#include <math.h>

static const int maxIterate= 100;

static int solverCount= 0;

CSolver::CSolver(void)
{
	solverCount++;
	// Allocate vectors in Solve ()

	// Numbers still to be placed in rows
	rowsToPlace= NULL;

	// Numbers still to be placed in cols
	colsToPlace= NULL;

	// Numbers still to be placed in squares
	squaresToPlace= NULL;

	m_board= NULL;
}

CSolver::~CSolver(void)
{
	solverCount--;
}

// Get grid coords from square coords
void CSolver::GetGridCoords ( CSudokuBoard* board, int square, int index, int* x, int* y )
{
	int size= (int) sqrt ( (double) board->GetSize ( ) );

	// Coords of target square
	int sqX= square % size;
	int sqY= square / size;

	// Coords within square
	int inX= index % size;
	int inY= index / size;

	*x= ( sqX * size ) + inX;
	*y= ( sqY * size ) + inY;
}

// Get square from grid coords
void CSolver::GetSquareCoords ( CSudokuBoard* board, int *square, int x, int y )
{
	int size= (int) sqrt ( (double) board->GetSize ( ) );

	// Coords of target square
	int sqX= x / size;
	int sqY= y / size;

	// Return index of square
	*square= sqX + ( size * sqY );
}

// Is the specified number in the specified row
bool CSolver::IsInRow ( int number, int row )
{
	for ( int i= 0; i < m_board->GetSize (); i++ )
	{
		if ( m_board->GetSquare ( i, row ) == number )
		{
			return true;
		}
	}

	return false;
}

// Is the specified number in the specified col
bool CSolver::IsInCol ( int number, int col )
{
	for ( int i= 0; i < m_board->GetSize (); i++ )
	{
		if ( m_board->GetSquare ( col, i ) == number )
		{
			return true;
		}
	}

	return false;
}

// Is the specified number in the specified square
bool CSolver::IsInSquare ( int number, int squ )
{
	for ( int i= 0; i < m_board->GetSize (); i++ )
	{
		int y, x;
		GetGridCoords ( m_board, squ, i, &x, &y );

		if ( m_board->GetSquare ( x, y ) == number )
		{
			return true;
		}
	}

	return false;
}

// Allocate and initialise to place vectors
void CSolver::InitialiseToPlaceVector ( std::vector<int>*** vectors, int size )
{
	// Allocate
	(*vectors)= new std::vector<int>* [ size ];

	// For each vector
	for ( int i= 0; i < size; i++ )
	{
		(*vectors) [ i ]= new std::vector<int>;

		// For each number 1..size, add to vector
		for ( int j= 0; j < size; j++ )
		{
			(*vectors) [ i ]->push_back ( j+1 );
		}
	}
}

// Remove numbers from to be placed vectors that have already been placed on board
void CSolver::RemovePlacedNumbers ( CSudokuBoard* board )
{
	// Look at rows
	for ( int r= 0; r < board->GetSize ( ); r++ )
	{
		// Move along row
		for ( int c= 0; c < board->GetSize ( ); c++ )
		{
			// If square is placed
			if ( board->GetSquare ( c, r ) != -1 )
			{
				// Look for square value in vector
				for ( int i= 0; i < rowsToPlace [ r ]->size(); i ++ )
				{
					// if found
					if ( rowsToPlace [ r ]->at ( i ) == board->GetSquare ( c, r ) )
					{
						// remove entry
						rowsToPlace [ r ]->erase ( rowsToPlace [ r ]->begin () + i );
					}
				}
			}
		}
	}

	// Look at cols
	for ( int c= 0; c < board->GetSize ( ); c++ )
	{
		// Move down col
		for ( int r= 0; r < board->GetSize ( ); r++ )
		{
			// If square is placed
			if ( board->GetSquare ( c, r ) != -1 )
			{
				// Look for square value in vector
				for ( int i= 0; i < colsToPlace [ c ]->size(); i ++ )
				{
					// if found
					if ( colsToPlace [ c ]->at ( i ) == board->GetSquare ( c, r ) )
					{
						// remove entry
						colsToPlace [ c ]->erase ( colsToPlace [ c ]->begin () + i );
					}
				}
			}
		}
	}

	// Size of sub-squares
	int squareSize= (int) sqrt ( (double)board->GetSize ( ) );

	// Look at squares
	for ( int s= 0; s < board->GetSize ( ); s++ )
	{
		// Move through square
		for ( int c= 0; c < board->GetSize ( ); c++ )
		{
			// calculate grid coords
			int x, y;

			GetGridCoords ( board, s, c, &x, &y );

			// If square is placed
			if ( board->GetSquare ( x, y ) != -1 )
			{
				// Look for square value in vector
				for ( int i= 0; i < squaresToPlace [ s ]->size(); i ++ )
				{
					// if found
					if ( squaresToPlace [ s ]->at ( i ) == board->GetSquare ( x, y ) )
					{
						// remove entry
						squaresToPlace [ s ]->erase ( squaresToPlace [ s ]->begin () + i );
					}
				}
			}
		}
	}
}

// Attempt to complete the board, true iff success
bool CSolver::Solve ( CSudokuBoard* board, bool* possible, int* count, int* curDepth, int* maxDepth, int* progress )
{
	m_progress= progress;

	// One deeper in tree
	(*curDepth)++;

	if ( (*curDepth) > (*maxDepth) )
	{
		(*maxDepth)= (*curDepth);
	}

	m_board= board;

	// Allocate/Initialise vectors to store yet to be placed numbers
	InitialiseToPlaceVector ( &rowsToPlace,    board->GetSize ( ) );
	InitialiseToPlaceVector ( &colsToPlace,    board->GetSize ( ) );
	InitialiseToPlaceVector ( &squaresToPlace, board->GetSize ( ) );

	// Remove numbers already placed on board
	RemovePlacedNumbers ( board );

	// While still moves to be made, place (a) number(s)
	while ( Iterate ( possible, count, curDepth, maxDepth ) )
	{
		OutputDebugString ( "." );
		(*progress)++;
	}

	for ( int i= 0; i < m_board->GetSize (); i++ )
	{

		delete rowsToPlace [ i ];
		delete colsToPlace [ i ];
		delete squaresToPlace [ i ];
	}

	delete [] rowsToPlace;
	delete [] colsToPlace;
	delete [] squaresToPlace;

	// Return whether the game is completed
	return IsComplete ();
}

// Can number be placed in (x,y)
bool CSolver::IsPlacable ( int number, int x, int y )
{
	// No number already here
	if ( m_board->GetSquare ( x, y ) != -1 )
	{
		return false;
	}

	if ( IsInCol ( number, x ) )
	{
		return false;
	}

	if ( IsInRow ( number, y ) )
	{
		return false;
	}

	int squ;
	GetSquareCoords ( m_board, &squ, x, y );

	if ( IsInSquare ( number, squ ) )
	{
		return false;
	}

	return true;
}

// Place the number in the specified gird coordinates
void CSolver::PlaceNumber ( int number, int x, int y )
{
	// Place on board
	m_board->SetSquare ( x, y, number );

	// Remove from rows to place
	for ( int i= 0; i < rowsToPlace [ y ]->size (); i++ )
	{
		if ( rowsToPlace [ y ]->at ( i ) == number )
		{
			rowsToPlace [ y ]->erase ( rowsToPlace [ y ]->begin() + i );
		}
	}

	// Remove from cols to place
	for ( int i= 0; i < colsToPlace [ x ]->size (); i++ )
	{
		if ( colsToPlace [ x ]->at ( i ) == number )
		{
			colsToPlace [ x ]->erase ( colsToPlace [ x ]->begin() + i );
		}
	}

	// Remove from squares to place
	int sqIndex;
	GetSquareCoords ( m_board, &sqIndex, x, y );

	for ( int i= 0; i < squaresToPlace [ sqIndex ]->size (); i++ )
	{
		if ( squaresToPlace [ sqIndex ]->at ( i ) == number )
		{
			squaresToPlace [ sqIndex ]->erase ( squaresToPlace [ sqIndex ]->begin() + i );
		}
	}
}

static int depth= 0;

// Returns true when complete
bool CSolver::Iterate ( bool* possible, int* count, int* curDepth, int* maxDepth )
{
	// One more iteration
	(*count)++;

	// Did we manage to make a move?
	bool moved= false;
	*possible= true;

	std::vector<GridPos> possiblePositions;
	std::vector<GridPos> smallestPossiblePositions;
	int numberToPlace= -1;
	int minPlaceCount= INT_MAX;

	// Rows
	for ( int i= 0; i < m_board->GetSize (); i++ )
	{
		for ( int j= 0; j < rowsToPlace [ i ]->size (); j++ )
		{
			int x;
			if ( PlaceInRow ( rowsToPlace [ i ]->at ( j ), i, &x, possible, &possiblePositions ) )
			{
				// Record that we managed to move
				moved= true;

				PlaceNumber ( rowsToPlace [ i ]->at ( j ), x, i );
			}
			else
			{
				// if no posible positions exist then in is imposible to complete
				if ( !(*possible) )
				{
					// board is imposible, return false now
					return false;
				}

				// Otherwise placement is possible, but we have choices

				// if the number of choices in position is the smallest yet
				if ( possiblePositions.size() < minPlaceCount )
				{
					smallestPossiblePositions= possiblePositions;
					minPlaceCount= possiblePositions.size();
					numberToPlace= rowsToPlace [ i ]->at ( j );
				}

				// Otherwise this is not the smallest list, so discard it
			}
		}
	}

	// Cols
	for ( int i= 0; i < m_board->GetSize (); i++ )
	{
		for ( int j= 0; j < colsToPlace [ i ]->size (); j++ )
		{
			int y;
			if ( PlaceInCol ( colsToPlace [ i ]->at ( j ), i, &y, possible, &possiblePositions ) )
			{
				// Record that we managed to move
				moved= true;

				PlaceNumber ( colsToPlace [ i ]->at ( j ), i, y );
			}
			else
			{
				// if no posible positions exist then in is imposible to complete
				if ( !(*possible) )
				{
					// board is imposible, return false now
					return false;
				}

				// Otherwise placement is possible, but we have choices

				// if the number of choices in position is the smallest yet
				if ( possiblePositions.size() < minPlaceCount )
				{
					smallestPossiblePositions= possiblePositions;
					minPlaceCount= possiblePositions.size();
					numberToPlace= colsToPlace [ i ]->at ( j );
				}

				// Otherwise this is not the smallest list, so discard it
			}
		}
	}

	// Squares
	for ( int i= 0; i < m_board->GetSize (); i++ )
	{
		for ( int j= 0; j < squaresToPlace [ i ]->size (); j++ )
		{
			int sqIndex;
			if ( PlaceInSquare ( squaresToPlace [ i ]->at ( j ), i, &sqIndex, possible, &possiblePositions ) )
			{
				// Record that we managed to move
				moved= true;

				int x, y;
				GetGridCoords ( m_board, i, sqIndex, &x, &y );

				PlaceNumber ( squaresToPlace [ i ]->at ( j ), x, y );
			}
			else
			{
				// if no posible positions exist then in is imposible to complete
				if ( !(*possible) )
				{
					// board is imposible, return false now
					return false;
				}

				// Otherwise placement is possible, but we have choices

				// if the number of choices in position is the smallest yet
				if ( possiblePositions.size() < minPlaceCount )
				{
					smallestPossiblePositions= possiblePositions;
					minPlaceCount= possiblePositions.size();
					numberToPlace= squaresToPlace [ i ]->at ( j );
				}

				// Otherwise this is not the smallest list, so discard it
			}
		}
	}

	// If ctrl is here, board is not impossible

	// If board is possible and we have not moved
	if ( !moved && numberToPlace != -1 )
	{
		for ( int i= 0; i < smallestPossiblePositions.size (); i++ )
		{
			// Create a new board, from current board
			CSudokuBoard* board= new CSudokuBoard ( m_board );

			// Create a new solver
			CSolver* solver= new CSolver ( );

			// Try placing the number in this position
			board->SetSquare ( smallestPossiblePositions.at ( i ).x,
							   smallestPossiblePositions.at ( i ).y, numberToPlace );

			// Try to solve
			if ( solver->Solve ( board, possible, count, curDepth, maxDepth, m_progress ) )
			{
				// Solved, return solved board
				m_board->Copy ( board );

				delete solver;
				delete board;

				return true;
			}
			else
			{
				// That didn't work
				delete solver;
				delete board;
			}
		}
	}

	return moved;
}

// Is the board complete?
bool CSolver::IsComplete ( )
{
	// Check if complete
	bool comp= true;

	for ( int x= 0; x < m_board->GetSize ( ); x++ )
	{
		for ( int y= 0; y < m_board->GetSize ( ); y++ )
		{
			if ( m_board->GetSquare ( x, y ) == -1 )
			{
				comp= false;
			}
		}
	}

	return comp;
}

// Try and put the number in the specified col
bool CSolver::PlaceInCol ( int number, int col, int *y, bool* possible,
						   std::vector<GridPos>* possiblePositions )
{
	int positions= 0;
	int row;

	for ( int i= 0; i < m_board->GetSize (); i++ )
	{
		if ( IsPlacable ( number, col, i ) )
		{
			positions++;
			row= i;

			GridPos pos;
			pos.x= col;
			pos.y= i;
			possiblePositions->push_back ( pos );
		}
	}

	// If there are no possible positions for this number then 
	// completion is not possible
	*possible= ( positions > 0 );

	// One unique position, ready to place
	if ( positions == 1 )
	{
		*y= row;

		return true;
	}

	return false;
}

// Try and put the number in the specified square
bool CSolver::PlaceInSquare ( int number, int square, int *index, bool* possible,
							  std::vector<GridPos>* possiblePositions  )
{
	int positions= 0;
	int ind;

	for ( int i= 0; i < m_board->GetSize (); i++ )
	{
		int x, y;
		GetGridCoords ( m_board, square, i, &x, &y );

		if ( IsPlacable ( number, x, y ) )
		{
			positions++;
			ind= i;

			GridPos pos;
			pos.x= x;
			pos.y= y;
			possiblePositions->push_back ( pos );
		}
	}

	// If there are no possible positions for this number then 
	// completion is not possible
	*possible= ( positions > 0 );

	if ( positions == 1 )
	{
		*index= ind;

		return true;
	}

	return false;
}

// Try and put the number in the specified row
bool CSolver::PlaceInRow ( int number, int row, int *x, bool* possible,
						   std::vector<GridPos>* possiblePositions )
{
	int positions= 0;
	int col;

	for ( int i= 0; i < m_board->GetSize (); i++ )
	{
		if ( IsPlacable ( number, i, row ) )
		{
			positions++;
			col= i;

			GridPos pos;
			pos.x= i;
			pos.y= row;
			possiblePositions->push_back ( pos );
		}
	}

	// If there are no possible positions for this number then 
	// completion is not possible
	*possible= ( positions > 0 );

	if ( positions == 1 )
	{
		*x= col;

		return true;
	}

	return false;
}

// Print remaining numbers
void CSolver::PrintRemaining ( )
{
	OutputDebugString ( "Rows to place:\n" );
	for ( int i= 0; i < 9; i++ )
	{
		CString str;
		str.Format ( "Row %d: ", i+1 );
		OutputDebugString ( str );

		for ( int j= 0; j < rowsToPlace [ i ]->size (); j++ )
		{
			str.Format ( " %d  ", rowsToPlace [ i ]->at ( j ) );
			OutputDebugString ( str );
		}

		OutputDebugString ( "\n" );
	}

	OutputDebugString ( "Cols to place:\n" );

	OutputDebugString ( "Squares to place:\n" );
}