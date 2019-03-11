
// Kolokvijum2016View.h : interface of the CKolokvijum2016View class
//

#pragma once
#include "DImage.h"

class CKolokvijum2016View : public CView
{
protected: // create from serialization only
	CKolokvijum2016View() noexcept;
	DECLARE_DYNCREATE(CKolokvijum2016View)

// Attributes
public:
	CKolokvijum2016Doc* GetDocument() const;
	DImage* imgFelt2;
	DImage* imgWood;
	float pomerajUgao;
	int pomeraj;
	bool kraj;

// Operations
public:
	void Translate(CDC* pDC, float x, float y, bool right);
	void Rotate(CDC* pDC, float angle, bool right);
	void Scale(CDC* pDC, float x, float y, bool right);
	void DrawEverything(CDC* pDC, CRect rect);
	void DrawBorder(CDC* pDC, CRect rect, int w);
	void DrawTable(CDC* pDC, CRect rect, int w);
	void DrawHoles(CDC* pDC, CRect rect, int size);
	void DrawStick(CDC* pDC, int w);
	void DrawBall(CDC* pDC, int w);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CKolokvijum2016View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Kolokvijum2016View.cpp
inline CKolokvijum2016Doc* CKolokvijum2016View::GetDocument() const
   { return reinterpret_cast<CKolokvijum2016Doc*>(m_pDocument); }
#endif

