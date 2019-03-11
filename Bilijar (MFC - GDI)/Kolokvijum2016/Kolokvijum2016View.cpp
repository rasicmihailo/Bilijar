
// Kolokvijum2016View.cpp : implementation of the CKolokvijum2016View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kolokvijum2016.h"
#endif

#include "Kolokvijum2016Doc.h"
#include "Kolokvijum2016View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKolokvijum2016View

IMPLEMENT_DYNCREATE(CKolokvijum2016View, CView)

BEGIN_MESSAGE_MAP(CKolokvijum2016View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKolokvijum2016View construction/destruction

CKolokvijum2016View::CKolokvijum2016View() noexcept
{
	// TODO: add construction code here
	imgFelt2 = new DImage();
	imgFelt2->Load(CString("felt2.jpg"));

	imgWood = new DImage();
	imgWood->Load(CString("wood.jpg"));

	pomerajUgao = 0.0;

	pomeraj = 0;

	kraj = false;
}

CKolokvijum2016View::~CKolokvijum2016View()
{
	delete imgFelt2;
	delete imgWood;
}

BOOL CKolokvijum2016View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKolokvijum2016View drawing



void CKolokvijum2016View::OnDraw(CDC* pDC)
{
	CKolokvijum2016Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CRect rect;
	GetClientRect(&rect);

	CDC* pMemDC = new CDC();
	pMemDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
	pMemDC->SelectObject(&bmp);
	
	DrawEverything(pMemDC, &rect);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), pMemDC, 0, 0, SRCCOPY);
	pMemDC->DeleteDC();
	delete pMemDC;


}

void CKolokvijum2016View::Translate(CDC * pDC, float x, float y, bool right)
{
	XFORM form;
	form.eM11 = 1.0;
	form.eM12 = 0.0;
	form.eM21 = 0.0;
	form.eM22 = 1.0;
	form.eDx = x;
	form.eDy = y;

	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

void CKolokvijum2016View::Rotate(CDC * pDC, float angle, bool right)
{
	float angle2 = 3.14159 * angle / 180.0;

	XFORM form;
	form.eM11 = cos(angle2);
	form.eM12 = sin(angle2);
	form.eM21 = -sin(angle2);
	form.eM22 = cos(angle2);
	form.eDx = 0.0;
	form.eDy = 0.0;

	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

void CKolokvijum2016View::Scale(CDC * pDC, float x, float y, bool right)
{
	XFORM form;
	form.eM11 = x;
	form.eM12 = 0.0;
	form.eM21 = 0.0;
	form.eM22 = y;
	form.eDx = 0.0;
	form.eDy = 0.0;

	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

void CKolokvijum2016View::DrawEverything(CDC * pDC, CRect rect)
{
	XFORM formOld;
	int gm = pDC->SetGraphicsMode(GM_ADVANCED);
	pDC->GetWorldTransform(&formOld);

	DrawBorder(pDC, &rect, 40);
	DrawTable(pDC, &rect, 40);
	DrawHoles(pDC, &rect, 40);


	float angle = 90.0 + pomerajUgao;
	float angleRad = 3.14159 * angle / 180.0;

	int xBall = 600 - pomeraj * sin(angleRad);
	int yBall = 400 + pomeraj * cos(angleRad);

	if (pomeraj <= 0)
		Translate(pDC, xBall, yBall, true);
	else
		Translate(pDC, 600, 400, true);
	DrawBall(pDC, 30);

	pDC->SetWorldTransform(&formOld);

	if (pomeraj <= 0)
		Translate(pDC, 600, 400, true);
	else
		Translate(pDC, 600, 400, true);

	Rotate(pDC, angle, false);
	int pomerajPom = pomeraj + 15;
	if (pomerajPom >= 15)
		Translate(pDC, 0, pomerajPom, false);
	else
		Translate(pDC, 0, 15, false);
	DrawStick(pDC, 600);


	pDC->SetWorldTransform(&formOld);
	pDC->SetGraphicsMode(gm);

	if ((xBall <= 45 && yBall <= 45)
			|| (xBall >= rect.Width() / 2 - 5 && xBall <= rect.Width() / 2 + 5 && yBall <= 45)
			|| (xBall >= rect.Width() - 45 && yBall <= 45)
			|| (xBall <= 45 && yBall >= rect.Height() - 45)
			|| (xBall >= rect.Width() / 2 - 5 && xBall <= rect.Width() / 2 + 5 && yBall >= rect.Height() - 45)
			|| (xBall >= rect.Width() - 45 && yBall >= rect.Height() - 45))
	{

		CFont font;
		font.CreateFontW(70, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
		CFont* oldFont = pDC->SelectObject(&font);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(153, 102, 51));

		pDC->TextOutW(200, 400, CString("WINNER WINNER CHICKEN DINNER"));

		kraj = true;
	}
}
	
void CKolokvijum2016View::DrawBorder(CDC * pDC, CRect rect, int w)
{
	imgWood->Draw(pDC, CRect(0, 0, w, rect.Height()), CRect(0, 0, w, rect.Height()));
	imgWood->Draw(pDC, CRect(w, 0, rect.Width() - w, w), CRect(w, 0, rect.Width() - w, w));
	imgWood->Draw(pDC, CRect(rect.Width() - w, 0, rect.Width(), rect.Height()), CRect(rect.Width() - w, 0, rect.Width(), rect.Height()));
	imgWood->Draw(pDC, CRect(w, rect.Height() - w, rect.Width() - w, rect.Height()), CRect(w, rect.Height() - w, rect.Width() - w, rect.Height()));
}

void CKolokvijum2016View::DrawTable(CDC * pDC, CRect rect, int w)
{
	bool prolazPoVrstama = true;
	bool prolaKrozVrstu = true;
	int x1 = 0;
	int y1 = 0;
	while (prolazPoVrstama) {
		if (y1 + imgFelt2->Height() < rect.Height() - 2 * w) {
			while (prolaKrozVrstu) {
				if (x1 + imgFelt2->Width() < rect.Width() - 2 * w) {
					imgFelt2->Draw(pDC, CRect(0, 0, imgFelt2->Width(), imgFelt2->Height()), CRect(x1 + w, y1 + w, imgFelt2->Width() + w + x1, imgFelt2->Height() + w + y1));
					x1 += imgFelt2->Width();
				}
				else
					prolaKrozVrstu = false;
			}
			imgFelt2->Draw(pDC, CRect(0, 0, rect.Width() - 2 * w - x1, imgFelt2->Height()), CRect(x1 + w, y1 + w, (rect.Width() - 2 * w - x1) + w + x1, imgFelt2->Height() + w + y1));
			
			prolaKrozVrstu = true;
			x1 = 0;
			y1 += imgFelt2->Height();
		}
		else
			prolazPoVrstama = false;
		

		prolaKrozVrstu = true;
		while (prolaKrozVrstu) {
			if (x1 + imgFelt2->Width() < rect.Width() - 2 * w) {
				imgFelt2->Draw(pDC, CRect(0, 0, rect.Width() - 2 * w - x1, rect.Height() - 2 * w - y1), CRect(x1 + w, y1 + w, (rect.Width() - 2 * w - x1) + w + x1, (rect.Height() - 2 * w - y1) + w + y1));
				x1 += imgFelt2->Width();
			}
			else
				prolaKrozVrstu = false;
		}
		imgFelt2->Draw(pDC, CRect(0, 0, rect.Width() - 2 * w - x1, rect.Height() - 2 * w - y1), CRect(x1 + w, y1 + w, (rect.Width() - 2 * w - x1) + w + x1, (rect.Height() - 2 * w - y1) + w + y1));

	}
}

void CKolokvijum2016View::DrawHoles(CDC* pDC, CRect rect, int size)
{
	CBrush* brushBlack = new CBrush(RGB(0, 0, 0));
	CBrush* oldBrush = pDC->SelectObject(brushBlack);

	pDC->Ellipse(size / 2, size / 2, size / 2 + size, size / 2 + size);
	pDC->Ellipse(rect.Width() / 2 - size / 2, size / 2, rect.Width() / 2 + size / 2, size / 2 + size);
	pDC->Ellipse(rect.Width() - 3 * size / 2, size / 2, rect.Width() - size / 2, size / 2 + size);

	pDC->Ellipse(size / 2, rect.Height() - 3 * size / 2, size / 2 + size, rect.Height() - size / 2);
	pDC->Ellipse(rect.Width() / 2 - size / 2, rect.Height() - 3 * size / 2, rect.Width() / 2 + size / 2, rect.Height() - size / 2);
	pDC->Ellipse(rect.Width() - 3 * size / 2, rect.Height() - 3 * size / 2, rect.Width() - size / 2, rect.Height() - size / 2);

	pDC->SelectObject(oldBrush);
}

void CKolokvijum2016View::DrawStick(CDC * pDC, int w)
{
	CPen* newPen = new CPen(PS_SOLID, 1, RGB(77, 51, 0));
	CPen* oldPen = pDC->SelectObject(newPen);
	CBrush* brushBlack = new CBrush(RGB(255, 204, 102));
	CBrush* oldBrush = pDC->SelectObject(brushBlack);

	pDC->BeginPath();
		pDC->MoveTo(-w / 200, 0);
		pDC->LineTo(w / 200, 0);
		pDC->LineTo(w / 100 / 3 * 2, w / 3 * 2);
		pDC->LineTo(-w / 100 / 3 * 2, w / 3 * 2);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	CBrush* brushBrown = new CBrush(RGB(77, 51, 0));
	pDC->SelectObject(brushBrown);

	pDC->BeginPath();
		pDC->MoveTo(-w / 100 / 3 * 2, w / 3 * 2);
		pDC->LineTo(w / 100 / 3 * 2, w / 3 * 2);
		pDC->LineTo(w / 100, w);
		pDC->LineTo(-w / 100, w);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

void CKolokvijum2016View::DrawBall(CDC * pDC, int w)
{
	CPen* newPen = new CPen(PS_SOLID, 1, RGB(102, 26, 0));
	CPen* oldPen = pDC->SelectObject(newPen);
	CBrush* brushBlack = new CBrush(RGB(204, 51, 0));
	CBrush* oldBrush = pDC->SelectObject(brushBlack);

	
	pDC->Ellipse(-w / 2, -w / 2, w / 2, w / 2);


	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}


// CKolokvijum2016View printing

BOOL CKolokvijum2016View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolokvijum2016View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolokvijum2016View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKolokvijum2016View diagnostics

#ifdef _DEBUG
void CKolokvijum2016View::AssertValid() const
{
	CView::AssertValid();
}

void CKolokvijum2016View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolokvijum2016Doc* CKolokvijum2016View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolokvijum2016Doc)));
	return (CKolokvijum2016Doc*)m_pDocument;
}
#endif //_DEBUG


// CKolokvijum2016View message handlers


BOOL CKolokvijum2016View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CView::OnEraseBkgnd(pDC);
	return true;
}


void CKolokvijum2016View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == VK_LEFT) {
		if (!kraj) {
			pomerajUgao += 1;
			Invalidate(false);
		}
	}
	if (nChar == VK_RIGHT) {
		if (!kraj) {
			pomerajUgao -= 1;
			Invalidate(false);
		}
	}

	if (nChar == VK_UP) {
		if (!kraj) {
			pomeraj += 10;
			Invalidate(false);
		}
	}

	if (nChar == VK_DOWN) {
		if (!kraj) {
			pomeraj -= 10;
			Invalidate(false);
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
