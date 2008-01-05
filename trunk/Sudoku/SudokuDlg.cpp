// SudokuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sudoku.h"
#include "SudokuDlg.h"
#include "SudokuBoard.h"
#include "Solver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSudokuDlg dialog




CSudokuDlg::CSudokuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSudokuDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for ( int x= 0; x < size; x++ )
	{
		for ( int y= 0; y < size; y++ )
		{
			m_edits [ x ] [ y ]= new CEdit ( );
		}
	}

	m_progress= 0;
}

void CSudokuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, *(m_edits [ 0 ] [ 0 ]) );
	DDX_Control(pDX, IDC_EDIT2, *(m_edits [ 1 ] [ 0 ]) );
	DDX_Control(pDX, IDC_EDIT3, *(m_edits [ 2 ] [ 0 ]) );

	DDX_Control(pDX, IDC_EDIT4, *(m_edits [ 3 ] [ 0 ]) );
	DDX_Control(pDX, IDC_EDIT5, *(m_edits [ 4 ] [ 0 ]) );
	DDX_Control(pDX, IDC_EDIT6, *(m_edits [ 5 ] [ 0 ]) );

	DDX_Control(pDX, IDC_EDIT7, *(m_edits [ 6 ] [ 0 ]) );
	DDX_Control(pDX, IDC_EDIT8, *(m_edits [ 7 ] [ 0 ]) );
	DDX_Control(pDX, IDC_EDIT9, *(m_edits [ 8 ] [ 0 ]) );

	//

	DDX_Control(pDX, IDC_EDIT10, *(m_edits [ 0 ] [ 1 ]) );
	DDX_Control(pDX, IDC_EDIT11, *(m_edits [ 1 ] [ 1 ]) );
	DDX_Control(pDX, IDC_EDIT12, *(m_edits [ 2 ] [ 1 ]) );

	DDX_Control(pDX, IDC_EDIT13, *(m_edits [ 3 ] [ 1 ]) );
	DDX_Control(pDX, IDC_EDIT14, *(m_edits [ 4 ] [ 1 ]) );
	DDX_Control(pDX, IDC_EDIT15, *(m_edits [ 5 ] [ 1 ]) );

	DDX_Control(pDX, IDC_EDIT16, *(m_edits [ 6 ] [ 1 ]) );
	DDX_Control(pDX, IDC_EDIT17, *(m_edits [ 7 ] [ 1 ]) );
	DDX_Control(pDX, IDC_EDIT18, *(m_edits [ 8 ] [ 1 ]) );

	//

	DDX_Control(pDX, IDC_EDIT19, *(m_edits [ 0 ] [ 2 ]) );
	DDX_Control(pDX, IDC_EDIT20, *(m_edits [ 1 ] [ 2 ]) );
	DDX_Control(pDX, IDC_EDIT21, *(m_edits [ 2 ] [ 2 ]) );

	DDX_Control(pDX, IDC_EDIT22, *(m_edits [ 3 ] [ 2 ]) );
	DDX_Control(pDX, IDC_EDIT23, *(m_edits [ 4 ] [ 2 ]) );
	DDX_Control(pDX, IDC_EDIT24, *(m_edits [ 5 ] [ 2 ]) );

	DDX_Control(pDX, IDC_EDIT25, *(m_edits [ 6 ] [ 2 ]) );
	DDX_Control(pDX, IDC_EDIT26, *(m_edits [ 7 ] [ 2 ]) );
	DDX_Control(pDX, IDC_EDIT27, *(m_edits [ 8 ] [ 2 ]) );

	//

	DDX_Control(pDX, IDC_EDIT28, *(m_edits [ 0 ] [ 3 ]) );
	DDX_Control(pDX, IDC_EDIT29, *(m_edits [ 1 ] [ 3 ]) );
	DDX_Control(pDX, IDC_EDIT30, *(m_edits [ 2 ] [ 3 ]) );

	DDX_Control(pDX, IDC_EDIT31, *(m_edits [ 3 ] [ 3 ]) );
	DDX_Control(pDX, IDC_EDIT32, *(m_edits [ 4 ] [ 3 ]) );
	DDX_Control(pDX, IDC_EDIT33, *(m_edits [ 5 ] [ 3 ]) );

	DDX_Control(pDX, IDC_EDIT34, *(m_edits [ 6 ] [ 3 ]) );
	DDX_Control(pDX, IDC_EDIT35, *(m_edits [ 7 ] [ 3 ]) );
	DDX_Control(pDX, IDC_EDIT36, *(m_edits [ 8 ] [ 3 ]) );

	//

	DDX_Control(pDX, IDC_EDIT37, *(m_edits [ 0 ] [ 4 ]) );
	DDX_Control(pDX, IDC_EDIT38, *(m_edits [ 1 ] [ 4 ]) );
	DDX_Control(pDX, IDC_EDIT39, *(m_edits [ 2 ] [ 4 ]) );

	DDX_Control(pDX, IDC_EDIT40, *(m_edits [ 3 ] [ 4 ]) );
	DDX_Control(pDX, IDC_EDIT41, *(m_edits [ 4 ] [ 4 ]) );
	DDX_Control(pDX, IDC_EDIT42, *(m_edits [ 5 ] [ 4 ]) );

	DDX_Control(pDX, IDC_EDIT43, *(m_edits [ 6 ] [ 4 ]) );
	DDX_Control(pDX, IDC_EDIT44, *(m_edits [ 7 ] [ 4 ]) );
	DDX_Control(pDX, IDC_EDIT45, *(m_edits [ 8 ] [ 4 ]) );

	//

	DDX_Control(pDX, IDC_EDIT46, *(m_edits [ 0 ] [ 5 ]) );
	DDX_Control(pDX, IDC_EDIT47, *(m_edits [ 1 ] [ 5 ]) );
	DDX_Control(pDX, IDC_EDIT48, *(m_edits [ 2 ] [ 5 ]) );

	DDX_Control(pDX, IDC_EDIT49, *(m_edits [ 3 ] [ 5 ]) );
	DDX_Control(pDX, IDC_EDIT50, *(m_edits [ 4 ] [ 5 ]) );
	DDX_Control(pDX, IDC_EDIT51, *(m_edits [ 5 ] [ 5 ]) );

	DDX_Control(pDX, IDC_EDIT52, *(m_edits [ 6 ] [ 5 ]) );
	DDX_Control(pDX, IDC_EDIT53, *(m_edits [ 7 ] [ 5 ]) );
	DDX_Control(pDX, IDC_EDIT54, *(m_edits [ 8 ] [ 5 ]) );

	//

	DDX_Control(pDX, IDC_EDIT55, *(m_edits [ 0 ] [ 6 ]) );
	DDX_Control(pDX, IDC_EDIT56, *(m_edits [ 1 ] [ 6 ]) );
	DDX_Control(pDX, IDC_EDIT57, *(m_edits [ 2 ] [ 6 ]) );

	DDX_Control(pDX, IDC_EDIT58, *(m_edits [ 3 ] [ 6 ]) );
	DDX_Control(pDX, IDC_EDIT59, *(m_edits [ 4 ] [ 6 ]) );
	DDX_Control(pDX, IDC_EDIT60, *(m_edits [ 5 ] [ 6 ]) );

	DDX_Control(pDX, IDC_EDIT61, *(m_edits [ 6 ] [ 6 ]) );
	DDX_Control(pDX, IDC_EDIT62, *(m_edits [ 7 ] [ 6 ]) );
	DDX_Control(pDX, IDC_EDIT63, *(m_edits [ 8 ] [ 6 ]) );

	//

	DDX_Control(pDX, IDC_EDIT64, *(m_edits [ 0 ] [ 7 ]) );
	DDX_Control(pDX, IDC_EDIT65, *(m_edits [ 1 ] [ 7 ]) );
	DDX_Control(pDX, IDC_EDIT66, *(m_edits [ 2 ] [ 7 ]) );

	DDX_Control(pDX, IDC_EDIT67, *(m_edits [ 3 ] [ 7 ]) );
	DDX_Control(pDX, IDC_EDIT68, *(m_edits [ 4 ] [ 7 ]) );
	DDX_Control(pDX, IDC_EDIT69, *(m_edits [ 5 ] [ 7 ]) );

	DDX_Control(pDX, IDC_EDIT70, *(m_edits [ 6 ] [ 7 ]) );
	DDX_Control(pDX, IDC_EDIT71, *(m_edits [ 7 ] [ 7 ]) );
	DDX_Control(pDX, IDC_EDIT72, *(m_edits [ 8 ] [ 7 ]) );

	//

	DDX_Control(pDX, IDC_EDIT73, *(m_edits [ 0 ] [ 8 ]) );
	DDX_Control(pDX, IDC_EDIT74, *(m_edits [ 1 ] [ 8 ]) );
	DDX_Control(pDX, IDC_EDIT75, *(m_edits [ 2 ] [ 8 ]) );

	DDX_Control(pDX, IDC_EDIT76, *(m_edits [ 3 ] [ 8 ]) );
	DDX_Control(pDX, IDC_EDIT77, *(m_edits [ 4 ] [ 8 ]) );
	DDX_Control(pDX, IDC_EDIT78, *(m_edits [ 5 ] [ 8 ]) );

	DDX_Control(pDX, IDC_EDIT79, *(m_edits [ 6 ] [ 8 ]) );
	DDX_Control(pDX, IDC_EDIT80, *(m_edits [ 7 ] [ 8 ]) );
	DDX_Control(pDX, IDC_EDIT81, *(m_edits [ 8 ] [ 8 ]) );

	//
	DDX_Control(pDX, IDC_BUTTON1, m_solveButton);
	DDX_Control(pDX, IDC_PROGRESS1, m_progressBar);
}

CSudokuDlg::~CSudokuDlg ( )
{
	for ( int x= 0; x < size; x++ )
	{
		for ( int y= 0; y < size; y++ )
		{
			delete m_edits [ x ] [ y ];
		}
	}
}

BEGIN_MESSAGE_MAP(CSudokuDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CSudokuDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BUTTON1, &CSudokuDlg::OnBnClickedSolve)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSudokuDlg message handlers

BOOL CSudokuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSudokuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSudokuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSudokuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSudokuDlg::OnBnClickedClear()
{
	// TODO: Add your control notification handler code here
	for ( int x= 0; x < size; x++ )
	{
		for ( int y= 0; y < size; y++ )
		{
			m_edits [ x ] [ y ]->SetWindowText ( "" );
		}
	}
}

void CSudokuDlg::OnBnClickedSolve()
{
	AfxBeginThread ( &SolveBoardThread, this );
}

// Controlling function for solver thread
UINT SolveBoardThread ( LPVOID pParam )
{
	CSudokuDlg* pObject = (CSudokuDlg*)pParam;

    if (pObject == NULL ||
        !pObject->IsKindOf(RUNTIME_CLASS(CSudokuDlg)))
    return 1;   // if pObject is not valid

	// TODO: Add your control notification handler code here
	pObject->m_solveButton.EnableWindow ( false );
	pObject->m_solveButton.SetWindowText ( "Working..." );

	pObject->m_progress= 0;
	UINT_PTR timer= pObject->SetTimer ( 0, 25, 0 );

	// Create a board
	CSudokuBoard* board= new CSudokuBoard ( 9 );

	// Create a solver
	CSolver* solver= new CSolver ( );

	// Initialise the board
	for ( int x= 0; x < size; x++ )
	{
		for ( int y= 0; y < size; y++ )
		{
			char buf[256];
			int number;

			pObject->m_edits [ x ] [ y ]->GetWindowText ( buf, 256 );

			if ( strlen ( buf ) > 0 )
			{
				sscanf ( buf, "%d", &number );

				if ( number >= 0 && number <= 9 )
				{
					board->SetSquare ( x, y, number );
				}
				else
				{
					MessageBox ( 0, "Numbers must be in range 0..9", "Error", MB_OK );
					//OnBnClickedClear ( );
					return 1;
				}
			}

		}
	}

	// Is it possible to solve the board
	bool possible;
	
	// Total number of iterations
	int iterations= 0;

	// Max depth of search
	int maxDepth= 0;
	int curDepth= 0;

	// Attempt to solve the board
	if ( solver->Solve ( board, &possible, &iterations, &curDepth, &maxDepth, &(pObject->m_progress) ) )
	{
		CString str;
		str.AppendFormat ( "Completed board.\n\n" );
		str.AppendFormat ( "Total number of iterations: %d\n", iterations );
		str.AppendFormat ( "Max search tree depth: %d\n", maxDepth );

		MessageBox ( 0, str, "Message", MB_OK );
	}
	else
	{
		if ( possible )
		{
			MessageBox ( 0, "Cannot complete board, although it may be possible.", "Message", MB_OK );
		}
		else
		{
			MessageBox ( 0, "Cannot complete board, it is not possible.", "Message", MB_OK );
		}
	}

	// Display the board
	for ( int x= 0; x < size; x++ )
	{
		for ( int y= 0; y < size; y++ )
		{
			CString str;

			if ( board->GetSquare ( x, y ) != -1 )
			{
				str.Format ( "%d", board->GetSquare ( x, y ) );
			}
			else
			{
				str= "";
			}


			pObject->m_edits [ x ] [ y ]->SetWindowText ( str );
		}
	}

	delete board;
	delete solver;

	pObject->m_progress= 0;
	pObject->m_progressBar.SetPos ( 0 );
	pObject->m_solveButton.EnableWindow ( true );
	pObject->m_solveButton.SetWindowText ( "Solve Board" );
	pObject->KillTimer ( timer );;

    return 0;   // thread completed successfully
}
void CSudokuDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	m_progressBar.SetPos ( m_progress );

	CDialog::OnTimer(nIDEvent);
}
