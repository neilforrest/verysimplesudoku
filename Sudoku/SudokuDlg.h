// SudokuDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// Size of the board
static const int size= 9;

// CSudokuDlg dialog
class CSudokuDlg : public CDialog
{
// Construction
public:
	CSudokuDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CSudokuDlg ( );

// Dialog Data
	enum { IDD = IDD_SUDOKU_DIALOG };

	// CEdit board
	CEdit* m_edits [ 9 ] [ 9 ];
	int m_progress;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedClear();
public:
	afx_msg void OnBnClickedSolve();
public:
	CButton m_solveButton;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	CProgressCtrl m_progressBar;
};

// Controlling function for solver thread
UINT SolveBoardThread ( LPVOID pParam );