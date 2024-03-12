
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Pjt.h"
#include "ChildView.h"
#define CBSIZE 15	//CheckerBoard size
#ifdef _DEBUG
#define new DEBUG_NEW
#endif	
bool giveUp = false; //giveUp flag of Black
bool EOG = false; //End of Game
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);
	//2중 for문을 활용한 오목판 구현
	for (int i = 1; i < CBSIZE ; i++)
	{
		for (int n = 1; n < CBSIZE; n++)
		{
			dc.Rectangle(n * 30, i * 30, n * 30 + 30, i * 30 + 30);	
		}
	}
	CBrush newBrush(RGB(0, 0, 0));
	CBrush* oldBrush = dc.SelectObject(&newBrush);
	int x, y;
	if (EOG)
	{	
		EOG = false;
		return;
	}// 현재 실행하는 OnPaint()가 새 게임일 경우 EOG을 이용해 바둑돌 다시 그리기는 skip
		

	for (x = 1; x <= CBSIZE; x++)
	{
		for (y = 1; y <= CBSIZE; y++)
		{
			if (instanceCheckArr[x - 1][y - 1])	//LbuttonDown()에서 착수했던 바둑돌 인스턴스 배열
			{	//흑백 구분 출력
				if (instanceCheckArr[x - 1][y - 1] != 1)
				{
					dc.SelectObject(oldBrush);
				}
				dc.Ellipse(x * 30 - 15, y * 30 - 15, x * 30 + 15, y * 30 + 15);	//착수
				dc.SelectObject(newBrush);
			}
			else	//바둑돌이 없다면 빈공간이므로 출력 X
				continue;
		}
	}
	
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);
	CClientDC dc(this);
	CBrush newBrush(RGB(0, 0, 0));
	CBrush* oldBrush = dc.SelectObject(&newBrush);
	int x = (point.x + 15) / 30;	//바둑알이 꼭지점쪽에 위치할 수 있도록 클릭좌표 구체화
	int y = (point.y + 15) / 30;
	if (x > 0 && y > 0 && x <= CBSIZE && y <= CBSIZE)
	{//바둑판 내부에 착수(클릭)할 경우

		if (EOG)
		{	//진행중인 게임이 종료된 상황인데 착수를 시도한 경우
			if (MessageBox(_T("게임이 종료되었습니다. \n착수할 수 없습니다.\n새 게임을 시작하시겠습니까?"), 
				_T("End of Game"), MB_YESNO) == IDYES)
			{
				clearGameMemory();	//바둑돌 인스턴스 배열을 비워주는 method
				instanceCnt = 0;
				giveUp = false;
				Invalidate(true);			//윈도우 clear
			}
			return;
		}
		if (instanceCheckArr[x - 1][y - 1] == 0)
		{	//착수할 곳에 바둑알이 없는 경우(=바둑알 인스턴스 배열 인덱스가 0)
			instanceCheckArr[x - 1][y - 1] = 1;
			
			if (instanceCnt == 0)
				colorOfInstance = 0;
			if (colorOfInstance)
			{
				dc.SelectObject(oldBrush);
				instanceCheckArr[x - 1][y - 1] = 2;
			}
			x *= 30;
			y *= 30;
			dc.Ellipse(x - 15, y - 15, x + 15, y + 15);
			instanceCnt++;

			colorOfInstance = (colorOfInstance + 1) % 2;

			int whoWins = WLCheck();	//승리 알고리즘
			CString winner;
			switch (whoWins)
			{//승자 판별
			case -1:
				winner = _T("백(Player2) 승리!!");
				break;
			case 1:
				winner = _T("흑(Player1) 승리!!");
				break;
			case 0:
				if (instanceCnt == 255)	//바둑판이 Full
					winner = _T("무승부!!");
				else
					return;
			}
			CString message = winner + _T("\n새 게임을 하시겠습니까 ?");
			if (MessageBox(message, _T("결과"), MB_YESNO) == IDYES)	//승자 발표 및 새 게임 창
			{	//수락할 경우
				clearGameMemory();	//메모리 삭제
				Invalidate(true);			//화면 갱신
				whoWins = 0;			//승자 초기화
				instanceCnt = 0;		//누적 바둑알 수 초기화
			}
			EOG = true;		//해당 변수를 이용해 게임이 끝났음을 알림 => 새 게임 시작 전까지 착수 더이상 불가능
		}
		else
		{	//중복 바둑알 배치 시
			MessageBox(_T("다른 곳에 착수하세요. "), _T("Warning"));	
		}
	}
}

int CChildView::Length()
{
	for (int x = 0; x < CBSIZE; x++)	//세로 승리조건
	{
		int colorCheck;	//현재 연속인 바둑알의 흑/백 판단 (빈 공간일 경우 0)
		bool flag = true;	//연속조건의 첫 바둑알일 때 판단 flag
		int cnt = 0;	//연속된 바둑알의 수

		for (int y = 0; y < CBSIZE; y++)
		{
			if (flag)
			{
				colorCheck = instanceCheckArr[x][y];
				flag = false;
			}

			if (colorCheck == instanceCheckArr[x][y] && colorCheck != 0)
			{//현재 연속인 바둑알 색과 현재 검사하는 바둑알의 색이 같은지 && 
			 //빈공간이 연속으로 나올 경우를 위해 0이 아니여야 하는 조건 추가
				cnt++;

			}
			else
			{
				if (cnt >= 5 && colorCheck == 1)	//흑돌이 5알 이상인 경우 중
				{
					if (cnt == 5)	return 1;	//정확히 5목인 경우 승리
					else
					{
						giveUp = true;//기권 flag 키고
						return 1;		   //흑 승리로 넘기기
					}
				}
				else if (cnt >= 5 && colorCheck == 2)
				{	//백은 장목도 승리조건에 포함됨
					return -1;
				}
				flag = true;
				if (colorCheck == 0 || instanceCheckArr[x][y] == 0)
				{	//인덱스가 0인 지점(즉, 빈공간)이 연속인 경우와 연속적으로 가다가
					//인덱스가 0인 지점(즉, 빈 공간)을 만났을 경우
					cnt = 0;//연속 횟수 초기화 및 continue
					continue;
				}
				cnt = 1;
				// 흑/백돌이 연속으로 나오다가 다른 색의 돌(0제외)이 나왔을 경우
				//그 돌부터 새로 연속이므로 cnt = 1;
			}
		}
	}
}

int CChildView::Width()
{
	int colorCheck;
	for (int y = 0; y < CBSIZE; y++)	//가로 승리조건
	{
		bool flag = true;
		int cnt = 0;
		for (int x = 0; x < CBSIZE; x++)
		{
			if (flag)
			{
				colorCheck = instanceCheckArr[x][y];
				flag = false;
			}

			if (colorCheck == instanceCheckArr[x][y] && instanceCheckArr[x][y] != 0)
			{//현재 연속인 바둑알 색과 현재 검사하는 바둑알의 색이 같은지 && 빈공간이 연속으로 나올 경우를 위해 0이 아니여야하는 조건 추가
				cnt++;
			}
			else
			{
				if (cnt >= 5 && colorCheck == 1)//흑돌이 5알 이상인 경우 중
				{
					if (cnt == 5)	return 1;//정확히 5목인 경우 승리
					else
					{
						giveUp = true;
						return 1;
					}
				}
				else if (cnt >= 5 && colorCheck == 2)
				{	//백은 장목도 승리조건에 포함됨
					return -1;
				}
				flag = true;
				if (colorCheck == 0 || instanceCheckArr[x][y] == 0)
				{	//인덱스가 0인 지점(즉, 빈공간)이 연속인 경우와 연속적으로 가다가 인덱스가 0인 지점(즉, 빈 공간)을 만났을 경우
					cnt = 0;	//연속 횟수 초기화 및 continue
					continue;
				}
				cnt = 1;	// 흑/백돌이 연속으로 나오다가 다른 색의 돌(0제외)이 나왔을 경우 그 돌부터 새로 연속이므로 cnt = 1;
			}
		}
	}
}

int CChildView::Diagonal1()
{
	int colorCheck;
	for (int y = 2; y < CBSIZE - 2; y++)	//오른쪽 아래방향 대각선 승리조건
	{	//대각선 승리판단 알고리즘 기준을 가운데 돌로 삼았음.
		//그러므로 0행,1행,13행,14행, 0열,1열,13열,14열은 바둑판을 넘어서게 됨 => 바둑판 점검하는 인덱스를 2~(CBSIZE-2)로 지정
		for (int x = 2; x < CBSIZE - 2; x++)
		{
			int  n = 361;
			colorCheck = instanceCheckArr[x][y];	//기준 돌
			while (n--)
			{
				if (colorCheck > 0)	//기준 돌이 빈 공간이 아니고
				{	//가운데 돌을 기준으로 오른쪽아래 방향으로 4개 돌을 2쌍씩 점검
					if (colorCheck == instanceCheckArr[x - 1][y - 1] && colorCheck == instanceCheckArr[x - 2][y - 2] && //가운데 돌과 좌측 상단 2개 돌이 같고
						instanceCheckArr[x - 1][y - 1] == instanceCheckArr[x + 1][y + 1] &&	//그 각각의
						instanceCheckArr[x - 2][y - 2] == instanceCheckArr[x + 2][y + 2])		//쌍들이 같으면 5목
					{
						if (colorCheck == 1)	//흑돌 금수처리
						{
							if (instanceCheckArr[x - 3][y - 3] == colorCheck || instanceCheckArr[x + 3][y + 3] == colorCheck)
							{
								giveUp = true;
							}
							return 1;		//흑 승
						}
						else if (colorCheck == 2)
						{
							return -1;	//백 승
						}
					}
				}
			}
		}
	}
}

int CChildView::Diagonal2()
{
	int colorCheck;
	for (int y = 2; y < CBSIZE - 2; y++)	//왼쪽 아래방향 대각선 승리조건
	{	//오른쪽 아래방향 대각선과 동일하게 0행,1행,13행,14행, 0열,1열,13열,14열은 바둑판을 넘어서게 됨
		//그에 맞게 for문 구현
		for (int x = CBSIZE - 3; x >= 2; x--)
		{
			int  n = 255;
			colorCheck = instanceCheckArr[x][y];//기준 돌
			while (n--)
			{
				if (colorCheck > 0)	//기준 돌이 빈 공간이 아니고
				{	//가운데 돌을 기준으로 왼쪽 아래 방향으로 4개 돌을 2쌍씩 점검
					if (colorCheck == instanceCheckArr[x + 1][y - 1] && colorCheck == instanceCheckArr[x + 2][y - 2] &&	//가운데 돌과 우측 상단 2개 돌이 같고
						instanceCheckArr[x + 1][y - 1] == instanceCheckArr[x - 1][y + 1] &&	//그 각각의
						instanceCheckArr[x - 2][y + 2] == instanceCheckArr[x + 2][y - 2])		//쌍들이 같으면 5목
					{
						if (colorCheck == 1)
						{
							if (instanceCheckArr[x + 3][y - 3] == colorCheck || instanceCheckArr[x - 3][y + 3] == colorCheck)
							{
								giveUp = true;
							}
							return 1;		//흑
						}
						else if (colorCheck == 2)
						{
							return -1;	//백
						}
					}
				}
			}
		}
	}
}

int CChildView::WLCheck()
{
	int x,y;
	int colorCheck;	//현재 연속인 바둑알의 흑/백 판단 (빈 공간일 경우 0)
	if (Length() == 1 || Width() == 1 || Diagonal1() == 1 || Diagonal2() == 1)
	{
		if (giveUp)
		{
			MessageBox(_T("흑(Player1)은 장목(6목이상)이 불가합니다.\n기권으로 처리됩니다."));
			return -1;
		}
		else
			return 1;
	}		
	else if (Length() == -1 || Width() == -1 || Diagonal1() == -1 || Diagonal2() == -1)
		return -1;
	else
		return 0;	//승리조건 못 찾을시 0 리턴
}

void CChildView::clearGameMemory()
{	//바둑판 메모리 초기화
	for (int i = 0; i < CBSIZE; i++)
	{
		for (int j = 0; j < CBSIZE; j++)
		{
			instanceCheckArr[i][j] = 0;
		}
	}
}

