
// PuzzleDlg.cpp : ���� ����
// test test
// test test
#include "stdafx.h"
#include "Puzzle.h"
#include "PuzzleDlg.h"
#include "afxdialogex.h"
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int i = 0; // �� ���� ����
int cnt[9] = { 0 }; // �� �迭 ����
char szText[100]; // ��� �ð� ���ڿ� ����
static int nCho = 1, nBun = 0; // ��, �� ����
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPuzzleDlg ��ȭ ����



CPuzzleDlg::CPuzzleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PUZZLE_DIALOG, pParent)
	, m_x(0)
	, m_y(0)
	, m_check_x(0)
	, m_check_y(0)
	, m_EditA(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TIME, m_EditA);
}

BEGIN_MESSAGE_MAP(CPuzzleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTT_LEFT, &CPuzzleDlg::OnBnClickedButtLeft)
	ON_BN_CLICKED(IDC_BUTT_CHOOSE, &CPuzzleDlg::OnBnClickedButtChoose)
	ON_BN_CLICKED(IDC_BUTT_RIGHT, &CPuzzleDlg::OnBnClickedButtRight)
	//	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPuzzleDlg �޽��� ó����

BOOL CPuzzleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CPuzzleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CPuzzleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CPuzzleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// �� ���� �Լ�(<<)
void CPuzzleDlg::OnBnClickedButtLeft()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (i == 0) i = 1;
	else if (i > 1) i--;
	else if (i == 1) i = 2;
	CClientDC dc(this); // ��Ʈ���� ��µ� DC ����

						// ��Ʈ��
	if (i == 1) {
		HDC hOneRealDC; // ���ȭ���� ���� �޸� ���� DC ����
		HBITMAP hOneReal; // ��Ʈ�� �ν��Ͻ� ����

		hOneReal = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_1Real")); // ��Ʈ�� 1 �ε�
		hOneRealDC = CreateCompatibleDC(dc); // �޸� DC�� ����
		SelectObject(hOneRealDC, hOneReal); // �޸� DC�� ��Ʈ�� ����

		BitBlt(dc, 350, 000, 300, 300, hOneRealDC, 0, 0, SRCCOPY);

		DeleteDC(hOneRealDC);
		DeleteObject(hOneReal);
	}


	else if (i == 2) {
		HDC hTwoRealDC; // ���ȭ���� ���� �޸� ���� DC ����
		HBITMAP hTwoReal; // ��Ʈ�� �ν��Ͻ� ����

		hTwoReal = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_2Real")); // ��Ʈ�� 2 �ε�
		hTwoRealDC = CreateCompatibleDC(dc); // �޸� DC�� ����
		SelectObject(hTwoRealDC, hTwoReal); // �޸� DC�� ��Ʈ�� ����

		BitBlt(dc, 350, 000, 300, 300, hTwoRealDC, 0, 0, SRCCOPY);
		DeleteDC(hTwoRealDC);
		DeleteObject(hTwoReal);

	}
}

// �� ���� �Լ�
void CPuzzleDlg::OnBnClickedButtChoose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CClientDC dc(this); // ��Ʈ���� ��µ� DC ����


	if (i == 1) { // ���� �¾��Ͻ�
		HDC hOneDC; // ���ȭ���� ���� �޸� ���� DC ����
		HBITMAP hOne; // ��Ʈ�� �ν��Ͻ� ����

		hOne = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_1")); // ��Ʈ�� 1 �ε�
		hOneDC = CreateCompatibleDC(dc); // �޸� DC�� ����
		SelectObject(hOneDC, hOne); // �޸� DC�� ��Ʈ�� ����

	// ���� �� ����
		srand((unsigned int)time(NULL));
		int ran = 0;
		for (int k = 0; k < 9; k++) {
			ran = rand() % 9;
			cnt[k] = ran;
			for (int j = 0; j < k; j++) {
				if (cnt[j] == cnt[k]) {
					k--;
					break;
				}
			}
		}

		for (int k = 0, m_check_y = 0; m_check_y < 3; m_check_y++) {
			for (m_check_x = 0; m_check_x < 3; m_check_x++, k++) {
				if (cnt[k] == 0) {
					m_x = 0;
					m_y = 0;
				}

				else if (cnt[k] == 1) {
					m_x = 0;
					m_y = 1;
				}
				else if (cnt[k] == 2) {
					m_x = 0;
					m_y = 2;
				}
				else if (cnt[k] == 3) {
					m_x = 1;
					m_y = 0;
				}
				else if (cnt[k] == 4) {
					m_x = 1;
					m_y = 1;
				}
				else if (cnt[k] == 5) {
					m_x = 1;
					m_y = 2;
				}
				else if (cnt[k] == 6) {
					m_x = 2;
					m_y = 0;
				}
				else if (cnt[k] == 7) {
					m_x = 2;
					m_y = 1;
				}
				else if (cnt[k] == 8) {
					m_x = 2;
					m_y = 2;
				}
				BitBlt(dc, m_x * 100, m_y * 100, 100, 100, hOneDC, m_check_x * 100, m_check_y * 100, SRCCOPY);
			}
		}

		DeleteDC(hOneDC);
		DeleteObject(hOne);
	}


	else if (i == 2) { // ���� ���Ͻ�
		HDC hTwoDC; // ���ȭ���� ���� �޸� ���� DC ����
		HBITMAP hTwo; // ��Ʈ�� �ν��Ͻ� ����

		hTwo = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_2")); // ��Ʈ�� 2 �ε�
		hTwoDC = CreateCompatibleDC(dc); // �޸� DC�� ����
		SelectObject(hTwoDC, hTwo); // �޸� DC�� ��Ʈ�� ����

	// ���� �� ����
		srand((unsigned int)time(NULL));
		int ran = 0;
		for (int k = 0; k < 9; k++) {
			ran = rand() % 9;
			cnt[k] = ran;
			for (int j = 0; j < k; j++) {
				if (cnt[j] == cnt[k]) {
					k--;
					break;
				}
			}
		}

		for (int k = 0, m_check_y = 0; m_check_y < 3; m_check_y++) {
			for (m_check_x = 0; m_check_x < 3; m_check_x++, k++) {
				if (cnt[k] == 0) {
					m_x = 0;
					m_y = 0;
				}

				else if (cnt[k] == 1) {
					m_x = 0;
					m_y = 1;
				}
				else if (cnt[k] == 2) {
					m_x = 0;
					m_y = 2;
				}
				else if (cnt[k] == 3) {
					m_x = 1;
					m_y = 0;
				}
				else if (cnt[k] == 4) {
					m_x = 1;
					m_y = 1;
				}
				else if (cnt[k] == 5) {
					m_x = 1;
					m_y = 2;
				}
				else if (cnt[k] == 6) {
					m_x = 2;
					m_y = 0;
				}
				else if (cnt[k] == 7) {
					m_x = 2;
					m_y = 1;
				}
				else if (cnt[k] == 8) {
					m_x = 2;
					m_y = 2;
				}
				BitBlt(dc, m_x * 100, m_y * 100, 100, 100, hTwoDC, m_check_x * 100, m_check_y * 100, SRCCOPY);
			}
		}
		DeleteDC(hTwoDC);
		DeleteObject(hTwo);
	}

	nCho = 1, nBun = 0; // Ÿ�̸� �ʱ�ȭ
	SetTimer(1, 1000, NULL); // Ÿ�̸� ����
}

// �� ���� �Լ�(>>)
void CPuzzleDlg::OnBnClickedButtRight()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (i < 2) i++;
	else if (i == 2) i = 1;
	CClientDC dc(this); // ��Ʈ���� ��µ� DC ����


	if (i == 1) {
		HDC hOneRealDC; // ���ȭ���� ���� �޸� ���� DC ����
		HBITMAP hOneReal; // ��Ʈ�� �ν��Ͻ� ����

		hOneReal = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_1Real")); // ��Ʈ�� 1 �ε�
		hOneRealDC = CreateCompatibleDC(dc); // �޸� DC�� ����
		SelectObject(hOneRealDC, hOneReal); // �޸� DC�� ��Ʈ�� ����

		BitBlt(dc, 350, 000, 300, 300, hOneRealDC, 0, 0, SRCCOPY);

		DeleteDC(hOneRealDC);
		DeleteObject(hOneReal);
	}


	else if (i == 2) {
		HDC hTwoRealDC; // ���ȭ���� ���� �޸� ���� DC ����
		HBITMAP hTwoReal; // ��Ʈ�� �ν��Ͻ� ����

		hTwoReal = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_2Real")); // ��Ʈ�� 2 �ε�
		hTwoRealDC = CreateCompatibleDC(dc); // �޸� DC�� ����
		SelectObject(hTwoRealDC, hTwoReal); // �޸� DC�� ��Ʈ�� ����

		BitBlt(dc, 350, 000, 300, 300, hTwoRealDC, 0, 0, SRCCOPY);
		DeleteDC(hTwoRealDC);
		DeleteObject(hTwoReal);

	}

}



//void CPuzzleDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//	if(nChar == VK_LEFT)
//	MessageBox(_T("����"));
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}

// ���콺 Ŭ���Լ�
void CPuzzleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// X: 0~100, Y : 0~100
	if (point.x > 0 && point.y > 0 && point.x <= 100 && point.y <= 100) {
		check(); // �� ������ x, y�� ã�� �Լ�		
		if (m_x == 1 && m_y == 0) { // �� ������ ������ ���� ��
			int k = original_check(0, 0); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 3; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 0; // ������ ��ġ�� �� �������� ����

		}
		else if (m_x == 0 && m_y == 1) { // ������� �Ʒ��� ���� ��
			int k = original_check(0, 0); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 1; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 0; // ������ ��ġ�� �� �������� ����
		}
		print(); // ����� ���
	}
	// X: 100~200, Y : 0~100
	else if (point.x > 100 && point.y > 0 && point.x <= 200 && point.y <= 100) {
		check(); // �� ������ x, y�� ã�� �Լ�
		if (m_x == 2 && m_y == 0) { // �� ������ ������ ���� ��
			int k = original_check(1, 0); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 6; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 3; // ������ ��ġ�� �� �������� ����

		}
		else if (m_x == 1 && m_y == 1) { // ������� �Ʒ��� ���� ��
			int k = original_check(1, 0); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 4; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 3; // ������ ��ġ�� �� �������� ����
		}
		else if (m_x == 0 && m_y == 0) { // ������� ������ ���� ��
			int k = original_check(1, 0); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 0; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 3; // ������ ��ġ�� �� �������� ����
		}
		print(); // ����� ���
	}
	// X: 200~300, Y : 0~100
	else if (point.x > 200 && point.y > 0 && point.x <= 300 && point.y <= 100) {
		check(); // �� ������ x, y�� ã�� �Լ�		
		if (m_x == 1 && m_y == 0) { // �� ������ ������ ���� ��
			int k = original_check(2, 0); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 3; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 6; // ������ ��ġ�� �� �������� ����

		}
		else if (m_x == 2 && m_y == 1) { // ������� �Ʒ��� ���� ��
			int k = original_check(2, 0); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 7; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 6; // ������ ��ġ�� �� �������� ����
		}
		print(); // ����� ���
	}
	// X: 0~100, Y : 100~200
	else if (point.x > 000 && point.y > 100 && point.x <= 100 && point.y <= 200) {
		check(); // �� ������ x, y�� ã�� �Լ�		
		if (m_x == 0 && m_y == 0) { // �� ������ ���� ���� ��
			int k = original_check(0, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 0; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 1; // ������ ��ġ�� �� �������� ����

		}
		else if (m_x == 0 && m_y == 2) { // ������� �Ʒ��� ���� ��
			int k = original_check(0, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 2; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 1; // ������ ��ġ�� �� �������� ����
		}
		else if (m_x == 1 && m_y == 1) { // ������� ������ ���� ��
			int k = original_check(0, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 4; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 1; // ������ ��ġ�� �� �������� ����
		}
		print(); // ����� ���
	}
	// X: 100~200, Y : 100~200
	else if (point.x > 100 && point.y > 100 && point.x <= 200 && point.y <= 200) {
		check(); // �� ������ x, y�� ã�� �Լ�		
		if (m_x == 1 && m_y == 0) { // �� ������ ���� ���� ��
			int k = original_check(1, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 3; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 4; // ������ ��ġ�� �� �������� ����
		}
		else if (m_x == 1 && m_y == 2) { // ������� �Ʒ��� ���� ��
			int k = original_check(1, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 5; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 4; // ������ ��ġ�� �� �������� ����
		}
		else if (m_x == 0 && m_y == 1) { // ������� ������ ���� ��
			int k = original_check(1, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 1; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 4; // ������ ��ġ�� �� �������� ����
		}
		else if (m_x == 2 && m_y == 1) { // ������� ������ ���� ��
			int k = original_check(1, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 7; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 4; // ������ ��ġ�� �� �������� ����
		}
		print(); // ����� ���
	}
	// X: 200~300, Y : 100~200
	else if (point.x > 200 && point.y > 100 && point.x <= 300 && point.y <= 200) {
		check(); // �� ������ x, y�� ã�� �Լ�		
		if (m_x == 2 && m_y == 0) { // �� ������ ���� ���� ��
			int k = original_check(2, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 6; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 7; // ������ ��ġ�� �� �������� ����

		}
		else if (m_x == 2 && m_y == 2) { // ������� �Ʒ��� ���� ��
			int k = original_check(2, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 8; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 7; // ������ ��ġ�� �� �������� ����
		}
		else if (m_x == 1 && m_y == 1) { // ������� ������ ���� ��
			int k = original_check(2, 1); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 4; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 7; // ������ ��ġ�� �� �������� ����
		}
		print(); // ����� ���
	}
	// X: 000~100, Y : 200~300
	else if (point.x > 000 && point.y > 200 && point.x <= 100 && point.y <= 300) {
		check(); // �� ������ x, y�� ã�� �Լ�		
		if (m_x == 0 && m_y == 1) { // �� ������ ���� ���� ��
			int k = original_check(0, 2); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 1; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 2; // ������ ��ġ�� �� �������� ����

		}
		else if (m_x == 1 && m_y == 2) { // ������� ������ ���� ��
			int k = original_check(0, 2); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 5; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 2; // ������ ��ġ�� �� �������� ����
		}
		print(); // ����� ���
	}
	// X: 100~200, Y : 200~300
	else if (point.x > 100 && point.y > 200 && point.x <= 200 && point.y <= 300) {
		check(); // �� ������ x, y�� ã�� �Լ�		
		if (m_x == 1 && m_y == 1) { // �� ������ ���� ���� ��
			int k = original_check(1, 2); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 4; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 5; // ������ ��ġ�� �� �������� ����
		}
		else if (m_x == 2 && m_y == 2) { // ������� ������ ���� ��
			int k = original_check(1, 2); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 8; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 5; // ������ ��ġ�� �� �������� ����
		}
		else if (m_x == 0 && m_y == 2) { // ������� ������ ���� ��
			int k = original_check(1, 2); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 2; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 5; // ������ ��ġ�� �� �������� ����
		}
		print(); // ����� ���
	}
	// X: 200~300, Y : 200~300
	else if (point.x > 200 && point.y > 200 && point.x <= 300 && point.y <= 300) {
		check(); // �� ������ x, y�� ã�� �Լ�		
		if (m_x == 2 && m_y == 1) { // �� ������ ���� ���� ��
			int k = original_check(2, 2); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 7; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 8; // ������ ��ġ�� �� �������� ����
		}
		else if (m_x == 1 && m_y == 2) { // ������� ������ ���� ��
			int k = original_check(2, 2); // �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
			cnt[k] = 5; // �������� �׸��� �� ������ ���ܳ���
			cnt[8] = 8; // ������ ��ġ�� �� �������� ����
		}

		print(); // ����� ���
	}


	CDialogEx::OnLButtonDown(nFlags, point);
}


// ����� ��� �Լ�
void CPuzzleDlg::print() {
	CClientDC dc(this); // ��Ʈ���� ��µ� DC ����

	if (i == 1) {
		HDC hOneDC; // ���ȭ���� ���� �޸� ���� DC ����
		HBITMAP hOne; // ��Ʈ�� �ν��Ͻ� ����

		hOne = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_1")); // ��Ʈ�� 1 �ε�
		hOneDC = CreateCompatibleDC(dc); // �޸� DC�� ����
		SelectObject(hOneDC, hOne); // �޸� DC�� ��Ʈ�� ����

		for (int k = 0, m_check_y = 0; m_check_y < 3; m_check_y++) {
			for (m_check_x = 0; m_check_x < 3; m_check_x++, k++) {
				if (cnt[k] == 0) {
					m_x = 0;
					m_y = 0;
				}

				else if (cnt[k] == 1) {
					m_x = 0;
					m_y = 1;
				}
				else if (cnt[k] == 2) {
					m_x = 0;
					m_y = 2;
				}
				else if (cnt[k] == 3) {
					m_x = 1;
					m_y = 0;
				}
				else if (cnt[k] == 4) {
					m_x = 1;
					m_y = 1;
				}
				else if (cnt[k] == 5) {
					m_x = 1;
					m_y = 2;
				}
				else if (cnt[k] == 6) {
					m_x = 2;
					m_y = 0;
				}
				else if (cnt[k] == 7) {
					m_x = 2;
					m_y = 1;
				}
				else if (cnt[k] == 8) {
					m_x = 2;
					m_y = 2;
				}
				BitBlt(dc, m_x * 100, m_y * 100, 100, 100, hOneDC, m_check_x * 100, m_check_y * 100, SRCCOPY);
			}
		}


		DeleteDC(hOneDC);
		DeleteObject(hOne);
	}

	else if (i == 2) {
		HDC hTwoDC; // ���ȭ���� ���� �޸� ���� DC ����
		HBITMAP hTwo; // ��Ʈ�� �ν��Ͻ� ����

		hTwo = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_2")); // ��Ʈ�� 2 �ε�
		hTwoDC = CreateCompatibleDC(dc); // �޸� DC�� ����
		SelectObject(hTwoDC, hTwo); // �޸� DC�� ��Ʈ�� ����

		for (int k = 0, m_check_y = 0; m_check_y < 3; m_check_y++) {
			for (m_check_x = 0; m_check_x < 3; m_check_x++, k++) {
				if (cnt[k] == 0) {
					m_x = 0;
					m_y = 0;
				}

				else if (cnt[k] == 1) {
					m_x = 0;
					m_y = 1;
				}
				else if (cnt[k] == 2) {
					m_x = 0;
					m_y = 2;
				}
				else if (cnt[k] == 3) {
					m_x = 1;
					m_y = 0;
				}
				else if (cnt[k] == 4) {
					m_x = 1;
					m_y = 1;
				}
				else if (cnt[k] == 5) {
					m_x = 1;
					m_y = 2;
				}
				else if (cnt[k] == 6) {
					m_x = 2;
					m_y = 0;
				}
				else if (cnt[k] == 7) {
					m_x = 2;
					m_y = 1;
				}
				else if (cnt[k] == 8) {
					m_x = 2;
					m_y = 2;
				}
				BitBlt(dc, m_x * 100, m_y * 100, 100, 100, hTwoDC, m_check_x * 100, m_check_y * 100, SRCCOPY);
			}
		}


		DeleteDC(hTwoDC);
		DeleteObject(hTwo);
	}
}

// �������� x, y�� ����� �迭�� ��ȣ�� ã�� �Լ�
int CPuzzleDlg::original_check(int x, int y) {
	// �������� x,y��ǥ�� ���� �迭���� ������, �� �迭�� ��ġ�� ��ȯ �ϴ� �Լ�
	for (int k = 0, m_check_y = 0; m_check_y < 3; m_check_y++) {
		for (m_check_x = 0; m_check_x < 3; m_check_x++, k++) {
			if (cnt[k] == 0) {
				m_x = 0;
				m_y = 0;
			}

			else if (cnt[k] == 1) {
				m_x = 0;
				m_y = 1;
			}
			else if (cnt[k] == 2) {
				m_x = 0;
				m_y = 2;
			}
			else if (cnt[k] == 3) {
				m_x = 1;
				m_y = 0;
			}
			else if (cnt[k] == 4) {
				m_x = 1;
				m_y = 1;
			}
			else if (cnt[k] == 5) {
				m_x = 1;
				m_y = 2;
			}
			else if (cnt[k] == 6) {
				m_x = 2;
				m_y = 0;
			}
			else if (cnt[k] == 7) {
				m_x = 2;
				m_y = 1;
			}
			else if (cnt[k] == 8) {
				m_x = 2;
				m_y = 2;
			}

			if (x == m_x && y == m_y)
				return k;
		}
	}
}

// �� ������ x, y�� ã�� �Լ�
void CPuzzleDlg::check() {
	if (cnt[8] == 0) {
		m_x = 0;
		m_y = 0;
	}

	else if (cnt[8] == 1) {
		m_x = 0;
		m_y = 1;
	}
	else if (cnt[8] == 2) {
		m_x = 0;
		m_y = 2;
	}
	else if (cnt[8] == 3) {
		m_x = 1;
		m_y = 0;
	}
	else if (cnt[8] == 4) {
		m_x = 1;
		m_y = 1;
	}
	else if (cnt[8] == 5) {
		m_x = 1;
		m_y = 2;
	}
	else if (cnt[8] == 6) {
		m_x = 2;
		m_y = 0;
	}
	else if (cnt[8] == 7) {
		m_x = 2;
		m_y = 1;
	}
	else if (cnt[8] == 8) {
		m_x = 2;
		m_y = 2;
	}
}



// ���콺 Ŭ���ϰ� ��ġ ������ ���� ���¶� ��
void CPuzzleDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (cnt[0] == 0 && cnt[1] == 3 && cnt[2] == 6 && cnt[3] == 1 && cnt[4] == 4 && cnt[5] == 7 && cnt[6] == 2 && cnt[7] == 5 && cnt[8] == 8) {
		KillTimer(1); // Ÿ�̸� ����
		WCHAR str[100];
		wsprintf(str, _T("�ϼ��Ͽ����ϴ�, �ɸ��ð��� %s �Դϴ�."), m_EditA);
		AfxMessageBox(str);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

// Ÿ�̸�
void CPuzzleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	sprintf_s(szText, "%d�� %d��", nBun, nCho);
	m_EditA = szText; // ����ð� ����
	UpdateData(FALSE); // ����Ʈ�� ��� �ð� ���

	nCho = nCho + 1; // �ð� ����� ���� ��,�� �� ��ȭ
	if (nCho == 60) {
		nCho = 1;
		nBun = nBun + 1;
	}

	CDialogEx::OnTimer(nIDEvent);
}
