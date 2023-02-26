
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
private:
	char colorOfInstance = 0;
	int instanceCheckArr[15][15] = { {0,}, };	//바둑알 인스턴스 기억 배열
	int instanceCnt = 0;	//누적 바둑알 수
	
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	int CChildView::WLCheck();	//승리 알고리즘
	int CChildView::Length();
	int CChildView::Width();
	int CChildView::Diagonal1();
	int CChildView::Diagonal2();
	void CChildView::clearGameMemory();	//바둑판 초기화
};

