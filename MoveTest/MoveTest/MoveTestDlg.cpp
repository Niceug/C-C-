
// MoveTestDlg.cpp : ʵ���ļ�
//m_

#include "stdafx.h"
#include "MoveTest.h"
#include "MoveTestDlg.h"
#include "afxdialogex.h"
#include "Setting.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define BKLocation_xy 0
#define WidthAndHigh 15
#define SizeOfQiZi  25

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
int g_Brick[WidthAndHigh][WidthAndHigh];
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMoveTestDlg �Ի���



CMoveTestDlg::CMoveTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MOVETEST_DIALOG, pParent)
	, m_MousePoint(1000)
	, OldPoint(0)
	, m_ButtonDownRL(0)
	, m_DoubleGame(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMoveTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMoveTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_RESTART, &CMoveTestDlg::OnBnClickedRestart)
	ON_BN_CLICKED(IDC_DOUBLEGAME, &CMoveTestDlg::OnBnClickedDoublegame)
	ON_BN_CLICKED(IDC_SETTING, &CMoveTestDlg::OnBnClickedSetting)
	ON_BN_CLICKED(IDC_BKMUSIC, &CMoveTestDlg::OnBnClickedBkmusic)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMoveTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMoveTestDlg ��Ϣ�������

BOOL CMoveTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	MoveWindow(0, 0, (WidthAndHigh + 1) *60, (WidthAndHigh) *60 - 20);		//���ô��ڴ�С
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMoveTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMoveTestDlg::OnPaint()
{
		CPaintDC dc(this);
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITMAP2);
		CBrush m_brush;
		m_brush.CreatePatternBrush(&bmp);
		CBrush* pOldBrush = dc.SelectObject(&m_brush);
		CRect rect;
		GetClientRect(&rect);
		dc.Rectangle(0, 0, rect.Width(),rect.Height()); // ��Щ�������Ե���ͼƬ���λ�úʹ�С
		dc.SelectObject(pOldBrush);
		//������
		CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
		CPen pen1(PS_SOLID, 1, RGB(0, 0, 0));
		dc.SelectObject(pen);
		dc.MoveTo(BKLocation_xy, BKLocation_xy);
		for (int i = 0; i < WidthAndHigh; i++)
		{
			for (int j = 0; j < WidthAndHigh + 1; j++)
			{
				if (j >= WidthAndHigh)
				{
					dc.MoveTo(BKLocation_xy, BKLocation_xy + j * 60);
					dc.LineTo(BKLocation_xy, BKLocation_xy + j * 60);
				}
				else
				dc.LineTo(BKLocation_xy +j * 60, BKLocation_xy +i * 60);
			}
		}

		dc.MoveTo(BKLocation_xy, BKLocation_xy);
		for (int i = 0; i < WidthAndHigh; i++)
		{
			for (int j = 0; j < WidthAndHigh + 1; j++)
			{
				if (j >= WidthAndHigh)
				{
					dc.MoveTo(BKLocation_xy + i * 60, BKLocation_xy);
					dc.LineTo(BKLocation_xy + i * 60, BKLocation_xy);
				}
				else
				dc.LineTo(BKLocation_xy +i * 60, BKLocation_xy +j * 60);
			}
		}
		dc.SelectObject(pen1);
		//��������
		CBrush brush(RGB(50, 50, 50));
		CBrush brush1(RGB(255, 255, 255));
		for (int i = 0; i < WidthAndHigh + 1; i++)
		{
			for (int j = 0; j < WidthAndHigh + 1; j++)
			{
				if (g_Brick[i][j] == 1)
				{
					dc.SelectObject(&brush);
					dc.Ellipse(i * 60 - SizeOfQiZi, j * 60 - SizeOfQiZi, i * 60 + SizeOfQiZi, j * 60 + SizeOfQiZi);
				}

				if (g_Brick[i][j] == 2)
				{
					dc.SelectObject(&brush1);
					dc.Ellipse(i * 60 - SizeOfQiZi, j * 60 - SizeOfQiZi, i * 60 + SizeOfQiZi, j * 60 + SizeOfQiZi);
				}

				if (g_Brick[i][j] == 3)
				{
					dc.SelectObject(&brush1);
					dc.Ellipse(i * 60 - SizeOfQiZi, j * 60 - SizeOfQiZi, i * 60 + SizeOfQiZi, j * 60 + SizeOfQiZi);
				}
			}
		}
	CDialogEx::OnPaint();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMoveTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���1����������,Ĭ��Ϊ�˻���ս
void CMoveTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime time = CTime::GetCurrentTime();
	int q = int(time.GetSecond());
	int p = int(time.GetSecond()) + 1;
	int Location_x = ((q + 1) % 4) + 4;
	int Location_y = ((p + 1) % 4) + 4;
	m_ButtonDownRL = 0;
	m_MousePoint = point;
	PlaySound(_T("C:\\Users\\hasee\\Documents\\Visual Studio 2015\\Projects\\MoveTest\\MoveTest\\res\\�����.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//��������λ��
	SetQiZiLocation(m_ButtonDownRL, m_MousePoint);
	//SetTimer(0, 1000, NULL);
	if (m_DoubleGame == false)
	{
		RobotPlayer(Location_x, Location_y);
	}
	Invalidate(false);
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i][j + 2] == 1 && g_Brick[i][j + 3] == 1 && g_Brick[i][j + 4] == 1)
			{
				MessageBox(_T("���1----Win!"));   return;   return;
			}
			if (g_Brick[i][j] == 1 && g_Brick[i+ 1][j ] == 1 && g_Brick[i + 2][j] == 1 && g_Brick[i + 3][j] == 1 && g_Brick[i+ 4][j] == 1)
			{
				MessageBox(_T("���1----Win!"));   return;
			}
			if (g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 2] == 1 && g_Brick[i + 3][j + 3] == 1 && g_Brick[i + 4][j + 4] == 1)
			{
				MessageBox(_T("���1----Win!"));   return;
			}
			if (g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i - 2][j + 2] == 1 && g_Brick[i - 3][j + 3] == 1 && g_Brick[i - 4][j + 4] == 1)
			{
				MessageBox(_T("���1----Win!"));   return;
			}

//�жϵ���ʤ��
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 3 && g_Brick[i][j + 3] == 3 && g_Brick[i][j + 4] == 3)
			{
				MessageBox(_T("����----Win!"));   return;
			}
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 3 && g_Brick[i + 3][j] == 3 && g_Brick[i + 4][j] == 3)
			{
				MessageBox(_T("����----Win!"));   return;
			}
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 3 && g_Brick[i + 3][j + 3] == 3 && g_Brick[i + 4][j + 4] == 3)
			{
				MessageBox(_T("����----Win!"));   return;
			}
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 3 && g_Brick[i - 3][j + 3] == 3 && g_Brick[i - 4][j + 4] == 3)
			{
				MessageBox(_T("����----Win!"));   return;
			}
		}
		CDialogEx::OnLButtonDown(nFlags, point);
}


//��Ҷ�ս���2��������Ҽ�
void CMoveTestDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_DoubleGame == true)
	{
		m_ButtonDownRL = 1;
		m_MousePoint = point;
		SetQiZiLocation(m_ButtonDownRL, m_MousePoint);
		Invalidate(false);
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 2 && g_Brick[i][j + 1] == 2 && g_Brick[i][j + 2] == 2 && g_Brick[i][j + 3] == 2 && g_Brick[i][j + 4] == 2)
				{
					MessageBox(_T("���2--Win!"));   return;
				}
				if (g_Brick[i][j] == 2 && g_Brick[i + 1][j] == 2 && g_Brick[i + 2][j] == 2 && g_Brick[i + 3][j] == 2 && g_Brick[i + 4][j] == 2)
				{
					MessageBox(_T("���2--Win!"));   return;
				}
				if (g_Brick[i][j] == 2 && g_Brick[i + 1][j + 1] == 2 && g_Brick[i + 2][j + 2] == 2 && g_Brick[i + 3][j + 3] == 2 && g_Brick[i + 4][j + 4] == 2)
				{
					MessageBox(_T("���2--Win!"));   return;
				}
				if (g_Brick[i][j] == 2 && g_Brick[i - 1][j + 1] == 2 && g_Brick[i - 2][j + 2] == 2 && g_Brick[i - 3][j + 3] == 2 && g_Brick[i - 4][j + 4] == 2)
				{
					MessageBox(_T("���2--Win!"));   return;
				}
			}
		
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}

//���¿�ʼ��Ϸ
void CMoveTestDlg::OnBnClickedRestart()
{
	for (int i = 0; i < WidthAndHigh; i++)
	{
		for (int j = 0; j < WidthAndHigh; j++)
		{
			g_Brick[i][j] = 0;
		}
	}
	
	Invalidate();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//////////////////////////////////////////////////////
/////////////////////////////�����ж�/////////////////
//////////////////////////////////////////////////////

//�ж�����������������Բ�
void CMoveTestDlg::RobotPlayer(int Location_x, int Location_y)
{

//�ж����������
	if (Robot4Qizi() == 0)//AIû��4����
	{
		//���б��4����1
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 2] == 1 && g_Brick[i + 3][j + 3] == 1)
				{
					if (g_Brick[i + 4][j + 4] == 0 && g_Brick[i - 1][j - 1] == 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
					if (g_Brick[i + 4][j + 4] == 0 && g_Brick[i - 1][j - 1] != 0)
					{
						if (i + 4 < WidthAndHigh && j + 4 < WidthAndHigh)
						{
							g_Brick[i + 4][j + 4] = 3;
							return;
						}
							
					}
					if (g_Brick[i + 4][j + 4] != 0 && g_Brick[i - 1][j - 1] == 0)
					{
						if (i - 1 >= 0 && j - 1 >= 0)
						{
							g_Brick[i - 1][j - 1] = 3;
							return;
						}
					}
					if (g_Brick[i + 4][j + 4] != 0 && g_Brick[i - 1][j - 1] != 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
				}
			}

		//���б��4����2
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i - 2][j + 2] == 1 && g_Brick[i - 3][j + 3] == 1)
				{
					//MessageBox(_T("���б��4����"));
					if (g_Brick[i - 4][j + 4] == 0 && g_Brick[i + 1][j - 1] == 0)
					{

						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
					if (g_Brick[i + 1][j - 1] != 0 && g_Brick[i - 4][j + 4] == 0)
					{
						if (i - 4 >=0 && j + 4 < WidthAndHigh)
						{
							g_Brick[i - 4][j + 4] = 3;
							return;
						}
					}
					if (g_Brick[i + 1][j - 1] == 0 && g_Brick[i - 4][j + 4] != 0)
					{
						if (i + 1 < WidthAndHigh && j - 1>=0)
						{
							g_Brick[i + 1][j - 1] = 3;
							return;
						}
					}
					if (g_Brick[i - 4][j + 4] != 0 && g_Brick[i + 1][j - 1] != 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
				}
			}
		//�������4����
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i][j + 2] == 1 && g_Brick[i][j + 3] == 1)
				{
					if (g_Brick[i][j + 4] == 0 && g_Brick[i][j - 1] == 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
					else if (g_Brick[i][j - 1] != 0 && g_Brick[i][j + 4] == 0)
					{
						if (j + 4 < WidthAndHigh)
						{
							g_Brick[i][j + 4] = 3;
							return;
						}
					}
					else if (g_Brick[i][j - 1] == 0 && g_Brick[i][j + 4] != 0)
					{
						if (j - 1 >= 0)
						{
							g_Brick[i][j - 1] = 3;
							return;
						}
					}
					else if (g_Brick[i][j - 1] != 0 && g_Brick[i][j + 4] != 0)
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
				}
			}

		//��Һ���4����
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 1 && g_Brick[i + 2][j] == 1 && g_Brick[i + 3][j] == 1)
				{
					if (g_Brick[i + 4][j] == 0 && g_Brick[i - 1][j] == 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
					if (g_Brick[i - 1][j] != 0 && g_Brick[i + 4][j] == 0)
					{
						if (i + 4 < WidthAndHigh)
						{
							g_Brick[i + 4][j] = 3;
							return;
						}
					}
					if (g_Brick[i - 1][j] == 0 && g_Brick[i + 4][j] != 0)
					{
						if (i - 1 >=0)
						{
							g_Brick[i - 1][j] = 3;
							return;
						}
					}
					if (g_Brick[i - 1][j] != 0 && g_Brick[i + 4][j] != 0)
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
				}
			}

		if (0 == Robot3QiZi())//AIû��3����
		{
//�ж�����Ƿ���3����
			//����������
			//1101��
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 0 && g_Brick[i + 2][j + 2] == 1 && g_Brick[i + 3][j + 3] == 1 && g_Brick[i + 4][j + 4] != 3)
					{
						if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
						{
							g_Brick[i + 1][j + 1] = 3;
							return;
						}
					}
				}
			//1011��
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 2] == 0 && g_Brick[i + 3][j + 3] == 1 && g_Brick[i + 4][j + 4] != 3)
					{
						if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
						{
							g_Brick[i + 2][j + 2] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 0 && g_Brick[i - 2][j + 2] == 1 && g_Brick[i - 3][j + 3] == 1 && g_Brick[i - 4][j + 4] != 3)
					{
						if (i - 1 >= 0 && j + 1 < WidthAndHigh)
						{
							g_Brick[i - 1][j + 1] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i - 2][j + 2] == 0 && g_Brick[i - 3][j + 3] == 1 && g_Brick[i - 4][j + 4] != 3)
					{
						if (i - 2 >= 0 && j + 2 < WidthAndHigh)
						{
							g_Brick[i - 2][j + 2] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 0 && g_Brick[i][j + 2] == 1 && g_Brick[i][j + 3] == 1 && g_Brick[i][j + 4] != 3)
					{
						if (j + 1 < WidthAndHigh)
						{
							g_Brick[i][j + 1] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i][j + 2] == 0 && g_Brick[i][j + 3] == 1 && g_Brick[i][j + 4] != 3)
					{
						if (j + 2 < WidthAndHigh)
						{
							g_Brick[i][j + 2] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] != 3 && g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 0 && g_Brick[i + 2][j] == 1 && g_Brick[i + 3][j] == 1 && g_Brick[i + 4][j] != 3)
					{
						if (i + 1 < WidthAndHigh)
						{
							g_Brick[i + 1][j] = 3;
							return;
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] != 3 && g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 1 && g_Brick[i + 2][j] == 0 && g_Brick[i + 3][j] == 1 && g_Brick[i + 4][j] != 3)
					{
						if (i + 2 < WidthAndHigh)
						{
							g_Brick[i + 2][j] = 3;
							return;
						}
					}
				}
			//�������3����
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{

					if (g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i][j + 2] == 1)
					{
						//MessageBox(_T("�������3����"));
						if (g_Brick[i][j + 3] == 0 && g_Brick[i][j - 1] == 0)
						{
							if (j + 3 < WidthAndHigh)
							{
								g_Brick[i][j + 3] = 3;
								return;
							}
						}
					}
				}
			//��Һ���3����
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 1 && g_Brick[i + 2][j] == 1)
					{
						//MessageBox(_T("��Һ���3����"));
						if (g_Brick[i - 1][j] == 0 && g_Brick[i + 3][j] == 0)
						{
							if (i + 3 < WidthAndHigh)
							{
								g_Brick[i + 3][j] = 3;
								return;
							}
						}
					}
				}

			//���б��3����
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 2] == 1)
					{
						//MessageBox(_T("���б��3����"));
						if (g_Brick[i - 1][j - 1] == 0 && g_Brick[i + 3][j + 3] == 0)
						{
							if (i + 3 < WidthAndHigh && j + 3 < WidthAndHigh)
							{
								g_Brick[i + 3][j + 3] = 3;
								return;
							}
						}
					}
				}
			//���б��3����
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j] == 1 && g_Brick[i + 1][j - 1] == 1 && g_Brick[i + 2][j - 2] == 1)
					{
						//MessageBox(_T("���б��3����"));
						if (g_Brick[i - 1][j + 1] == 0 && g_Brick[i + 3][j - 3] == 0)
						{
							if (i + 3 < WidthAndHigh && j - 3 >= 0)
							{
								g_Brick[i + 3][j - 3] = 3;
								return;
							}
						}
					}
				}

			//���б��3����
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i - 2][j + 2] == 1)
					{
						//MessageBox(_T("���б��3����"));
						if (g_Brick[i + 1][j - 1] == 0 && g_Brick[i - 3][j + 3] == 0)
						{
							if (i -3 >= 0 && j + 3 < WidthAndHigh)
							{
								g_Brick[i - 3][j + 3] = 3;
								return;
							}
						}
					}
				}

			//���б��2����
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 4][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 3][j + 1] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							//MessageBox(_T("1"));
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 2][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i + 3][j + 1] == 1)
					{
						if (g_Brick[i + 1][j - 1] == 0)
						{
							if (i + 1 < WidthAndHigh && j - 1 >= 0)
							{
								//MessageBox(_T("2"));
								g_Brick[i + 1][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 2][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 1] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								//MessageBox(_T("3"));
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i - 1][j + 1] == 1)
					{
						if (g_Brick[i - 1][j - 1] == 0)
						{
							if (i - 1 >= 0 && j - 1 >= 0)
							{
								//MessageBox(_T("4"));
								g_Brick[i - 1][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j + 4] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 1][j + 3] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								//MessageBox(_T("5"));
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 2] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 1][j - 3] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i - 1 >= 0 && j - 1 >= 0)
							{
								//MessageBox(_T("6"));
								g_Brick[i - 1][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i - 2][j + 1] == 1)
					{
						if (g_Brick[i][j - 1] == 0)
						{
							if (j -1 >= 0)
							{
								//MessageBox(_T("7"));
								g_Brick[i][j - 1] = 3;
								return;
							}
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 1 && g_Brick[i + 2][j - 1] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("8"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i - 1][j + 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("9"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i + 1][j + 2] == 1)
					{
						if (g_Brick[i - 1][j] == 0)
						{
							if (i - 1 >= 0)
							{
								//MessageBox(_T("10"));
								g_Brick[i - 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j + 2] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i][j + 2] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								//MessageBox(_T("11"));
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i + 1][j + 1] == 1)
					{
						if (g_Brick[i - 1][j + 1] == 0)
						{
							if (i - 1>= 0 && j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("12"));
								g_Brick[i - 1][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i - 1][j + 2] == 1 && g_Brick[i - 2][j + 3] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("13"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 2] == 1 && g_Brick[i + 2][j + 3] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("14"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j + 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 2][j - 1] == 1 && g_Brick[i + 3][j - 1] == 1)
					{
						if (g_Brick[i + 1][j - 1] == 0)
						{
							if (i + 1 < WidthAndHigh && j - 1 >= 0)
							{
								//MessageBox(_T("15"));
								g_Brick[i + 1][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 2][j + 1] == 1 && g_Brick[i + 3][j + 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("16"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j + 3] == 1 && g_Brick[i][j] == 1 && g_Brick[i - 1][j - 1] == 1 && g_Brick[i + 1][j + 2] == 1)
					{
						if (g_Brick[i + 1][j + 1] == 0)
						{
							if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("17"));
								g_Brick[i + 1][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j + 3] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j - 1] == 1 && g_Brick[i - 1][j + 2] == 1)
					{
						if (g_Brick[i - 1][j + 1] == 0)
						{
							if (i - 1>=0 && j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("18"));
								g_Brick[i - 1][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 2][j + 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 3][j + 1] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								//MessageBox(_T("19"));
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 2][j - 1] == 1 && g_Brick[i + 3][j - 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("20"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j - 1] == 1 && g_Brick[i + 1][j - 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("21"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 1] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("22"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 1][j + 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("23"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j - 1] == 1 && g_Brick[i + 2][j - 1] == 1)
					{
						if (g_Brick[i][j - 1] == 0)
						{
							if (j - 1 >= 0)
							{
								//MessageBox(_T("24"));
								g_Brick[i][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 2][j] == 1 && g_Brick[i + 3][j] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("25"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 2] == 1 && g_Brick[i][j + 3] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("26"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}
			//��������������ϣ����û��3����,AI�Լ���
			AIPlay(Location_x, Location_y);
			return;
		}
		else
			return;
	}
	else
		return;
}

void CMoveTestDlg::OnBnClickedDoublegame()
{
	m_DoubleGame = true;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


//AI4�����
int CMoveTestDlg::Robot4Qizi()
{
	//AIб��4����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{

			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 3 && g_Brick[i + 3][j + 3] == 3)
			{
				if (g_Brick[i + 4][j + 4] == 0)
				{
					if (i + 4 < WidthAndHigh && j + 4 < WidthAndHigh)
					{
						g_Brick[i + 4][j + 4] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 1][j - 1] == 0)
				{
					if (i - 1 >= 0 && j - 1 >= 0)
					{
						g_Brick[i - 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 4][j + 4] != 0 && g_Brick[i - 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//AIб��4����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 3 && g_Brick[i - 3][j + 3] == 3)
			{
				if (g_Brick[i - 4][j + 4] == 0)
				{
					if (i - 4 >= 0 && j + 4 < WidthAndHigh)
					{
						g_Brick[i - 4][j + 4] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 1][j - 1] == 0)
				{
					if (i + 1 < WidthAndHigh && j - 1 >= 0)
					{
						g_Brick[i + 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 4][j + 4] != 0 && g_Brick[i + 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//������4����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 3 && g_Brick[i][j + 3] == 3)
			{
				if (g_Brick[i][j + 4] == 0)
				{
					if (j + 4 < WidthAndHigh)
					{
						g_Brick[i][j + 4] = 3;
						return 1;
					}
				}
				else if (g_Brick[i][j - 1] == 0)
				{
					if (j - 1 >= 0)
					{
						g_Brick[i][j - 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] != 0 && g_Brick[i][j - 1] != 0)
				{
					break;
				}
			}
		}

	//������4����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 3 && g_Brick[i + 3][j] == 3)
			{
				if (g_Brick[i + 4][j] == 0)
				{
					if (i + 4 < WidthAndHigh)
					{
						g_Brick[i + 4][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j] == 0)
				{
					if (i - 1 >= 0)
					{
						g_Brick[i - 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] != 0 && g_Brick[i - 1][j] != 0)
				{
					break;
				}
			}
		}
	return 0;
}


//AI�������
int CMoveTestDlg::Robot3QiZi()
{
	//б��WidthAndHigh01
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 0 && g_Brick[i + 2][j + 2] == 3 && g_Brick[i + 3][j + 3] == 3)
			{
				if (g_Brick[i - 1][j - 1] != 1)
				{
					if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j + 4] != 1)
				{
					if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j + 4] == 1 && g_Brick[i - 1][j - 1] == 1)
					break;
			}
		}

	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 0 && g_Brick[i + 3][j + 3] == 3)
			{
				if (g_Brick[i - 1][j - 1] != 1)
				{
					if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j + 4] != 1)
				{
					if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j + 4] == 1 && g_Brick[i - 1][j - 1] == 1)
					break;
			}
		}
	//б��WidthAndHigh01
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 0 && g_Brick[i - 2][j + 2] == 3 && g_Brick[i - 3][j + 3] == 3)
			{
				if (g_Brick[i + 1][j - 1] != 1)
				{
					if (i - 1 >= 0 && j + 1 < WidthAndHigh)
					{
						g_Brick[i - 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 4][j + 4] != 1)
				{
					if (i - 1 >= 0 && j + 1 < WidthAndHigh)
					{
						g_Brick[i - 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 4][j + 4] == 1 && g_Brick[i + 1][j - 1] == 1)
					break;
			}
		}

	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 0 && g_Brick[i - 3][j + 3] == 3)
			{
				if (g_Brick[i + 1][j - 1] != 1)
				{
					if (i - 2 >= 0 && j + 2 < WidthAndHigh)
					{
						g_Brick[i - 2][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 4][j + 4] != 1)
				{
					if (i - 2 >= 0 && j + 2 < WidthAndHigh)
					{
						g_Brick[i - 2][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 4][j + 4] == 1 && g_Brick[i + 1][j - 1] == 1)
					break;
			}
		}
	//����1101
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 0 && g_Brick[i][j + 2] == 3 && g_Brick[i][j + 3] == 3)
			{
				if (g_Brick[i][j - 1] != 1)
				{
					if (j + 1 < WidthAndHigh)
					{
						g_Brick[i][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] != 1)
				{
					if (j + 1 < WidthAndHigh)
					{
						g_Brick[i][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] == 1 && g_Brick[i][j - 1] == 1)
					break;
			}
		}

	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 0 && g_Brick[i][j + 3] == 3)
			{
				if (g_Brick[i][j - 1] != 1)
				{
					if (j + 2 < WidthAndHigh)
					{
						g_Brick[i][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] != 1)
				{
					if (j + 2 < WidthAndHigh)
					{
						g_Brick[i][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] == 1 && g_Brick[i][j - 1] == 1)
					break;
			}
		}
	//����WidthAndHigh01
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 0 && g_Brick[i + 2][j] == 3 && g_Brick[i + 3][j] == 3)
			{
				if (g_Brick[i - 1][j] != 1)
				{
					if (j + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] != 1)
				{
					if (i + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] == 1 && g_Brick[i - 1][j] == 1)
					break;
			}
		}
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 0 && g_Brick[i + 3][j] == 3)
			{
				if (g_Brick[i - 1][j] != 1)
				{
					if (i + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] != 1)
				{
					if (i + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] == 1 && g_Brick[i - 1][j] == 1)
					break;
			}
		}
	//���������ӵ����
	//AIб��������
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 3)
			{
				if (g_Brick[i + 3][j + 3] == 0)
				{
					if (j + 3 < WidthAndHigh && i + 3 < WidthAndHigh)
					{
						g_Brick[i + 3][j + 3] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 1][j - 1] == 0)
				{
					if (i- 1 >= 0 && j- 1>=0)
					{
						g_Brick[i - 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 3][j + 3] == 1 && g_Brick[i - 1][j - 1] == 1)
				{
					break;
				}
			}
		}

	//AIб��������
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 3)
			{
				if (g_Brick[i - 3][j + 3] == 0)
				{
					if (j + 3 < WidthAndHigh && i - 3 >= 0)
					{
						g_Brick[i - 3][j + 3] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 1][j - 1] == 0)
				{
					if (j + 1 < WidthAndHigh && i - 1 >= 0)
					{
						g_Brick[i + 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 3][j + 3] == 1 && g_Brick[i + 1][j - 1] == 1)
				{
					break;
				}
			}
		}


	//������3����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 3)
			{
				if (g_Brick[i][j + 3] == 0)
				{
					if (j + 3 < WidthAndHigh)
					{
						g_Brick[i][j + 3] = 3;
						return 1;
					}
				}
				else if (g_Brick[i][j - 1] == 0)
				{
					if (j - 1 >= 0)
					{
						g_Brick[i][j - 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 3] == 1 && g_Brick[i][j - 1] == 1)
				{
					break;
				}
			}
		}
	//������3����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 3)
			{
				if (g_Brick[i + 3][j] == 0)
				{
					if (i + 3 < WidthAndHigh)
					{
						g_Brick[i + 3][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j] == 0)
				{
					if (i - 1 >= 0)
					{
						g_Brick[i - 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 3][j] == 1 && g_Brick[i - 1][j] == 1)
				{
					break;
				}
			}
		}
	return 0;
}


//AI2�����
bool CMoveTestDlg::AIPlay(int Location_x, int Location_y)
{
//AIб��2����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{

			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3)
			{
				if (g_Brick[i + 2][j + 2] == 0)
				{
					if (j + 2 < WidthAndHigh && i + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j + 2] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 1][j - 1] == 0)
				{
					if (i - 1 >= 0 && j - 1 >= 0)
					{
						g_Brick[i - 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 3][j + 3] != 0 && g_Brick[i - 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//AIб��2����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3)
			{
				if (g_Brick[i - 2][j + 2] == 0)
				{
					if (j + 2 < WidthAndHigh && i  - 2 >= 0)
					{
						g_Brick[i - 2][j + 2] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 1][j - 1] == 0)
				{
					if (i + 1 < WidthAndHigh && j - 1 >= 0)
					{
						g_Brick[i + 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 2][j + 2] != 0 && g_Brick[i + 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//������2����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3)
			{
				if (g_Brick[i][j + 2] == 0)
				{
					if (j + 2 < WidthAndHigh)
					{
						g_Brick[i][j + 2] = 3;
						return 1;
					}
				}
				else if (g_Brick[i][j - 1] == 0)
				{
					if (j - 1 >= 0)
					{
						g_Brick[i][j - 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 2] != 0 && g_Brick[i][j - 1] != 0)
				{
					break;
				}
			}
		}

	//������2����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3)
			{
				if (g_Brick[i + 2][j] == 0)
				{
					if (i + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j] == 0)
				{
					if (i - 1 >= 0)
					{
						g_Brick[i - 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 2][j] != 0 && g_Brick[i - 1][j] != 0)
				{
					break;
				}
			}
		}

	//AI1�����
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3)
			{
				if (g_Brick[i + 1][j] == 0)
				{
					if (i + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j] == 0)
				{
					if (i - 1 >= 0)
					{
						g_Brick[i - 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j - 1] == 0)
				{
					if (i - 1 >= 0 && j - 1 >= 0)
					{
						g_Brick[i - 1][j - 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 1][j + 1] == 0)
				{
					if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 1] == 0)
				{
					if (j + 1 < WidthAndHigh)
					{
						g_Brick[i][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j - 1] == 0)
				{
					if (j - 1 >= 0)
					{
						g_Brick[i][j - 1] = 3;
						return 1;
					}
				}
			}
		}


	//���������������AI�����

	while (1)
	{
		int robotRandom_x = rand() % (WidthAndHigh - 5);
		int robotRandom_y = rand() % (WidthAndHigh - 5);
		robotRandom_x+=3;
		robotRandom_y+=3;
		if (g_Brick[robotRandom_x][robotRandom_y] == 0)
		{
			g_Brick[robotRandom_x][robotRandom_y] = 3;
			break;
		}
	}
}


//�������λ��
void CMoveTestDlg::SetQiZiLocation(int m_ButtonDownRL, CPoint m_MousePoint)
{
	if ((m_MousePoint.x - BKLocation_xy) % 60 > 30)
	{
		if ((m_MousePoint.y - BKLocation_xy) % 60 > 30)
		{
			int i = (int)m_MousePoint.x / 60 + 1;
			int j = (int)m_MousePoint.y / 60 + 1;
			if (g_Brick[i][j] == 0)
			{
				if (m_ButtonDownRL == 0)
				{
					g_Brick[i][j] = 1;
				}
				else
					g_Brick[i][j] = 2;
			}
		}
		if ((m_MousePoint.y - BKLocation_xy) % 60 < 30)
		{
			int i = (int)m_MousePoint.x / 60 + 1;
			int j = (int)m_MousePoint.y / 60;
			if (g_Brick[i][j] == 0)
			{
				if (m_ButtonDownRL == 0)
				{
					g_Brick[i][j] = 1;
				}
				else
					g_Brick[i][j] = 2;
			}
		}
	}

	if ((m_MousePoint.x - BKLocation_xy) % 60 < 30)
	{
		if ((m_MousePoint.y - BKLocation_xy) % 60 > 30)
		{
			int i = (int)m_MousePoint.x / 60;
			int j = (int)m_MousePoint.y / 60 + 1;
			if (g_Brick[i][j] == 0)
			{
				if (m_ButtonDownRL == 0)
				{
					g_Brick[i][j] = 1;
				}
				else
					g_Brick[i][j] = 2;
			}
		}
		if ((m_MousePoint.y - BKLocation_xy) % 60 < 30)
		{
			int i = (int)m_MousePoint.x / 60;
			int j = (int)m_MousePoint.y / 60;
			if (g_Brick[i][j] == 0)
			{
				if (m_ButtonDownRL == 0)
				{
					g_Brick[i][j] = 1;
				}
				else
					g_Brick[i][j] = 2;
			}
		}
	}

}


void CMoveTestDlg::OnBnClickedSetting()
{
	CSetting SetDlg;
	//WidthAndHigh = m_nSizeOfQiPan;
	//SizeOfQiZi = m_nSizeOfQiZi;
	if (IDOK == SetDlg.DoModal())
	{
	//	m_nSizeOfQiPan = SetDlg.m_SizeOfQiPan;
	//	m_nSizeOfQiZi = SetDlg.m_SizeOfQiZi;
	}
}


void CMoveTestDlg::OnBnClickedBkmusic()
{
	PlaySound(_T("C:\\Users\\hasee\\Documents\\Visual Studio 2015\\Projects\\MoveTest\\MoveTest\\res\\Night.wav"), NULL, SND_FILENAME | SND_ASYNC);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMoveTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PlaySound(_T("C:\\Users\\hasee\\Documents\\Visual Studio 2015\\Projects\\MoveTest\\MoveTest\\res\\�����.wav"), NULL, SND_FILENAME | SND_ASYNC);
	CDialogEx::OnTimer(nIDEvent);
}


void CMoveTestDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
