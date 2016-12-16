
// PuzzleDlg.cpp : 구현 파일
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

int i = 0; // 맵 선택 변수
int cnt[9] = { 0 }; // 맵 배열 변수
char szText[100]; // 경과 시간 문자열 변수
static int nCho = 1, nBun = 0; // 분, 초 변수
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CPuzzleDlg 대화 상자



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


// CPuzzleDlg 메시지 처리기

BOOL CPuzzleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPuzzleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPuzzleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// 맵 변경 함수(<<)
void CPuzzleDlg::OnBnClickedButtLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (i == 0) i = 1;
	else if (i > 1) i--;
	else if (i == 1) i = 2;
	CClientDC dc(this); // 비트맵이 출력될 DC 생성

						// 비트맵
	if (i == 1) {
		HDC hOneRealDC; // 배경화면을 위한 메모리 내의 DC 생성
		HBITMAP hOneReal; // 비트맵 인스턴스 생성

		hOneReal = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_1Real")); // 비트맵 1 로드
		hOneRealDC = CreateCompatibleDC(dc); // 메모리 DC와 정합
		SelectObject(hOneRealDC, hOneReal); // 메모리 DC에 비트맵 정합

		BitBlt(dc, 350, 000, 300, 300, hOneRealDC, 0, 0, SRCCOPY);

		DeleteDC(hOneRealDC);
		DeleteObject(hOneReal);
	}


	else if (i == 2) {
		HDC hTwoRealDC; // 배경화면을 위한 메모리 내의 DC 생성
		HBITMAP hTwoReal; // 비트맵 인스턴스 생성

		hTwoReal = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_2Real")); // 비트맵 2 로드
		hTwoRealDC = CreateCompatibleDC(dc); // 메모리 DC와 정합
		SelectObject(hTwoRealDC, hTwoReal); // 메모리 DC에 비트맵 정합

		BitBlt(dc, 350, 000, 300, 300, hTwoRealDC, 0, 0, SRCCOPY);
		DeleteDC(hTwoRealDC);
		DeleteObject(hTwoReal);

	}
}

// 맵 선택 함수
void CPuzzleDlg::OnBnClickedButtChoose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CClientDC dc(this); // 비트맵이 출력될 DC 생성


	if (i == 1) { // 맵이 태양일시
		HDC hOneDC; // 배경화면을 위한 메모리 내의 DC 생성
		HBITMAP hOne; // 비트맵 인스턴스 생성

		hOne = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_1")); // 비트맵 1 로드
		hOneDC = CreateCompatibleDC(dc); // 메모리 DC와 정합
		SelectObject(hOneDC, hOne); // 메모리 DC에 비트맵 정합

	// 랜덤 값 설정
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


	else if (i == 2) { // 맵이 달일시
		HDC hTwoDC; // 배경화면을 위한 메모리 내의 DC 생성
		HBITMAP hTwo; // 비트맵 인스턴스 생성

		hTwo = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_2")); // 비트맵 2 로드
		hTwoDC = CreateCompatibleDC(dc); // 메모리 DC와 정합
		SelectObject(hTwoDC, hTwo); // 메모리 DC에 비트맵 정합

	// 랜덤 값 설정
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

	nCho = 1, nBun = 0; // 타이머 초기화
	SetTimer(1, 1000, NULL); // 타이머 가동
}

// 맵 변경 함수(>>)
void CPuzzleDlg::OnBnClickedButtRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (i < 2) i++;
	else if (i == 2) i = 1;
	CClientDC dc(this); // 비트맵이 출력될 DC 생성


	if (i == 1) {
		HDC hOneRealDC; // 배경화면을 위한 메모리 내의 DC 생성
		HBITMAP hOneReal; // 비트맵 인스턴스 생성

		hOneReal = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_1Real")); // 비트맵 1 로드
		hOneRealDC = CreateCompatibleDC(dc); // 메모리 DC와 정합
		SelectObject(hOneRealDC, hOneReal); // 메모리 DC에 비트맵 정합

		BitBlt(dc, 350, 000, 300, 300, hOneRealDC, 0, 0, SRCCOPY);

		DeleteDC(hOneRealDC);
		DeleteObject(hOneReal);
	}


	else if (i == 2) {
		HDC hTwoRealDC; // 배경화면을 위한 메모리 내의 DC 생성
		HBITMAP hTwoReal; // 비트맵 인스턴스 생성

		hTwoReal = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_2Real")); // 비트맵 2 로드
		hTwoRealDC = CreateCompatibleDC(dc); // 메모리 DC와 정합
		SelectObject(hTwoRealDC, hTwoReal); // 메모리 DC에 비트맵 정합

		BitBlt(dc, 350, 000, 300, 300, hTwoRealDC, 0, 0, SRCCOPY);
		DeleteDC(hTwoRealDC);
		DeleteObject(hTwoReal);

	}

}



//void CPuzzleDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	if(nChar == VK_LEFT)
//	MessageBox(_T("하이"));
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}

// 마우스 클릭함수
void CPuzzleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// X: 0~100, Y : 0~100
	if (point.x > 0 && point.y > 0 && point.x <= 100 && point.y <= 100) {
		check(); // 빈 공간의 x, y를 찾는 함수		
		if (m_x == 1 && m_y == 0) { // 빈 공간이 우측에 있을 때
			int k = original_check(0, 0); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 3; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 0; // 포인터 위치에 빈 공간으로 만듬

		}
		else if (m_x == 0 && m_y == 1) { // 빈공간이 아래에 있을 떼
			int k = original_check(0, 0); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 1; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 0; // 포인터 위치에 빈 공간으로 만듬
		}
		print(); // 결과값 출력
	}
	// X: 100~200, Y : 0~100
	else if (point.x > 100 && point.y > 0 && point.x <= 200 && point.y <= 100) {
		check(); // 빈 공간의 x, y를 찾는 함수
		if (m_x == 2 && m_y == 0) { // 빈 공간이 우측에 있을 때
			int k = original_check(1, 0); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 6; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 3; // 포인터 위치에 빈 공간으로 만듬

		}
		else if (m_x == 1 && m_y == 1) { // 빈공간이 아래에 있을 떼
			int k = original_check(1, 0); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 4; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 3; // 포인터 위치에 빈 공간으로 만듬
		}
		else if (m_x == 0 && m_y == 0) { // 빈공간이 좌측에 있을 떼
			int k = original_check(1, 0); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 0; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 3; // 포인터 위치에 빈 공간으로 만듬
		}
		print(); // 결과값 출력
	}
	// X: 200~300, Y : 0~100
	else if (point.x > 200 && point.y > 0 && point.x <= 300 && point.y <= 100) {
		check(); // 빈 공간의 x, y를 찾는 함수		
		if (m_x == 1 && m_y == 0) { // 빈 공간이 좌측에 있을 때
			int k = original_check(2, 0); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 3; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 6; // 포인터 위치에 빈 공간으로 만듬

		}
		else if (m_x == 2 && m_y == 1) { // 빈공간이 아래에 있을 떼
			int k = original_check(2, 0); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 7; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 6; // 포인터 위치에 빈 공간으로 만듬
		}
		print(); // 결과값 출력
	}
	// X: 0~100, Y : 100~200
	else if (point.x > 000 && point.y > 100 && point.x <= 100 && point.y <= 200) {
		check(); // 빈 공간의 x, y를 찾는 함수		
		if (m_x == 0 && m_y == 0) { // 빈 공간이 위에 있을 때
			int k = original_check(0, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 0; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 1; // 포인터 위치에 빈 공간으로 만듬

		}
		else if (m_x == 0 && m_y == 2) { // 빈공간이 아래에 있을 떼
			int k = original_check(0, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 2; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 1; // 포인터 위치에 빈 공간으로 만듬
		}
		else if (m_x == 1 && m_y == 1) { // 빈공간이 우측에 있을 떼
			int k = original_check(0, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 4; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 1; // 포인터 위치에 빈 공간으로 만듬
		}
		print(); // 결과값 출력
	}
	// X: 100~200, Y : 100~200
	else if (point.x > 100 && point.y > 100 && point.x <= 200 && point.y <= 200) {
		check(); // 빈 공간의 x, y를 찾는 함수		
		if (m_x == 1 && m_y == 0) { // 빈 공간이 위에 있을 때
			int k = original_check(1, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 3; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 4; // 포인터 위치에 빈 공간으로 만듬
		}
		else if (m_x == 1 && m_y == 2) { // 빈공간이 아래에 있을 떼
			int k = original_check(1, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 5; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 4; // 포인터 위치에 빈 공간으로 만듬
		}
		else if (m_x == 0 && m_y == 1) { // 빈공간이 좌측에 있을 떼
			int k = original_check(1, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 1; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 4; // 포인터 위치에 빈 공간으로 만듬
		}
		else if (m_x == 2 && m_y == 1) { // 빈공간이 우측에 있을 떼
			int k = original_check(1, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 7; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 4; // 포인터 위치에 빈 공간으로 만듬
		}
		print(); // 결과값 출력
	}
	// X: 200~300, Y : 100~200
	else if (point.x > 200 && point.y > 100 && point.x <= 300 && point.y <= 200) {
		check(); // 빈 공간의 x, y를 찾는 함수		
		if (m_x == 2 && m_y == 0) { // 빈 공간이 위에 있을 때
			int k = original_check(2, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 6; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 7; // 포인터 위치에 빈 공간으로 만듬

		}
		else if (m_x == 2 && m_y == 2) { // 빈공간이 아래에 있을 떼
			int k = original_check(2, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 8; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 7; // 포인터 위치에 빈 공간으로 만듬
		}
		else if (m_x == 1 && m_y == 1) { // 빈공간이 좌측에 있을 떼
			int k = original_check(2, 1); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 4; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 7; // 포인터 위치에 빈 공간으로 만듬
		}
		print(); // 결과값 출력
	}
	// X: 000~100, Y : 200~300
	else if (point.x > 000 && point.y > 200 && point.x <= 100 && point.y <= 300) {
		check(); // 빈 공간의 x, y를 찾는 함수		
		if (m_x == 0 && m_y == 1) { // 빈 공간이 위에 있을 때
			int k = original_check(0, 2); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 1; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 2; // 포인터 위치에 빈 공간으로 만듬

		}
		else if (m_x == 1 && m_y == 2) { // 빈공간이 우측에 있을 떼
			int k = original_check(0, 2); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 5; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 2; // 포인터 위치에 빈 공간으로 만듬
		}
		print(); // 결과값 출력
	}
	// X: 100~200, Y : 200~300
	else if (point.x > 100 && point.y > 200 && point.x <= 200 && point.y <= 300) {
		check(); // 빈 공간의 x, y를 찾는 함수		
		if (m_x == 1 && m_y == 1) { // 빈 공간이 위에 있을 때
			int k = original_check(1, 2); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 4; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 5; // 포인터 위치에 빈 공간으로 만듬
		}
		else if (m_x == 2 && m_y == 2) { // 빈공간이 우측에 있을 떼
			int k = original_check(1, 2); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 8; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 5; // 포인터 위치에 빈 공간으로 만듬
		}
		else if (m_x == 0 && m_y == 2) { // 빈공간이 좌측에 있을 떼
			int k = original_check(1, 2); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 2; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 5; // 포인터 위치에 빈 공간으로 만듬
		}
		print(); // 결과값 출력
	}
	// X: 200~300, Y : 200~300
	else if (point.x > 200 && point.y > 200 && point.x <= 300 && point.y <= 300) {
		check(); // 빈 공간의 x, y를 찾는 함수		
		if (m_x == 2 && m_y == 1) { // 빈 공간이 위에 있을 때
			int k = original_check(2, 2); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 7; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 8; // 포인터 위치에 빈 공간으로 만듬
		}
		else if (m_x == 1 && m_y == 2) { // 빈공간이 좌측에 있을 떼
			int k = original_check(2, 2); // 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
			cnt[k] = 5; // 포인터의 그림을 빈 공간을 세겨놓음
			cnt[8] = 8; // 포인터 위치에 빈 공간으로 만듬
		}

		print(); // 결과값 출력
	}


	CDialogEx::OnLButtonDown(nFlags, point);
}


// 결과값 출력 함수
void CPuzzleDlg::print() {
	CClientDC dc(this); // 비트맵이 출력될 DC 생성

	if (i == 1) {
		HDC hOneDC; // 배경화면을 위한 메모리 내의 DC 생성
		HBITMAP hOne; // 비트맵 인스턴스 생성

		hOne = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_1")); // 비트맵 1 로드
		hOneDC = CreateCompatibleDC(dc); // 메모리 DC와 정합
		SelectObject(hOneDC, hOne); // 메모리 DC에 비트맵 정합

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
		HDC hTwoDC; // 배경화면을 위한 메모리 내의 DC 생성
		HBITMAP hTwo; // 비트맵 인스턴스 생성

		hTwo = LoadBitmap(AfxGetInstanceHandle(), _T("IDB_BIT_2")); // 비트맵 2 로드
		hTwoDC = CreateCompatibleDC(dc); // 메모리 DC와 정합
		SelectObject(hTwoDC, hTwo); // 메모리 DC에 비트맵 정합

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

// 포인터의 x, y가 저장된 배열의 번호를 찾는 함수
int CPuzzleDlg::original_check(int x, int y) {
	// 포인터의 x,y좌표가 같은 배열값이 있으면, 그 배열의 위치를 반환 하는 함수
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

// 빈 공간의 x, y를 찾는 함수
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



// 마우스 클릭하고 위치 변경후 원본 상태랑 비교
void CPuzzleDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (cnt[0] == 0 && cnt[1] == 3 && cnt[2] == 6 && cnt[3] == 1 && cnt[4] == 4 && cnt[5] == 7 && cnt[6] == 2 && cnt[7] == 5 && cnt[8] == 8) {
		KillTimer(1); // 타이머 해제
		WCHAR str[100];
		wsprintf(str, _T("완성하였습니다, 걸린시간은 %s 입니다."), m_EditA);
		AfxMessageBox(str);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

// 타이머
void CPuzzleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	sprintf_s(szText, "%d분 %d초", nBun, nCho);
	m_EditA = szText; // 경과시간 삽입
	UpdateData(FALSE); // 에디트에 경과 시간 출력

	nCho = nCho + 1; // 시간 경과에 따라 분,초 값 변화
	if (nCho == 60) {
		nCho = 1;
		nBun = nBun + 1;
	}

	CDialogEx::OnTimer(nIDEvent);
}
