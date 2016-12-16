
// PuzzleDlg.h : 헤더 파일
//

#pragma once


// CPuzzleDlg 대화 상자
class CPuzzleDlg : public CDialogEx
{
// 생성입니다.
public:
	CPuzzleDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUZZLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtLeft();
	afx_msg void OnBnClickedButtChoose();
	afx_msg void OnBnClickedButtRight();
	int m_x;
	int m_y;
	int m_check_x;
	int m_check_y;
	void check();
	void print();
	int original_check(int x, int y);
//	void Mapping(HDC x);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CString m_EditA;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
