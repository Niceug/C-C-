
// cFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "cFile.h"
#include "cFileDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
SOCKET sock;
UINT recv_thd(LPVOID p);
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


// CcFileDlg �Ի���



CcFileDlg::CcFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CFILE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, send_edit);
	DDX_Control(pDX, IDC_EDIT3, ip_edit);
	DDX_Control(pDX, IDC_btnConnect, btnconn);
}

BEGIN_MESSAGE_MAP(CcFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CcFileDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_btnConnect, &CcFileDlg::OnBnClickedbtnconnect)
END_MESSAGE_MAP()


// CcFileDlg ��Ϣ�������

BOOL CcFileDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ip_edit.SetWindowText("192.168.1.108");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CcFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CcFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcFileDlg::update(CString s)
{
	edit1.ReplaceSel(s + "\r\n");
}

UINT recv_thd(LPVOID p)
{
	int res;
	char msg[1024];
	CString s;
	CcFileDlg * dlg = (CcFileDlg *)AfxGetApp()->GetMainWnd();
	dlg->update("���ӳɹ�");

	while (1)
	{
		if ((res = recv(sock, msg, 1024, 0)) == -1)
		{
			dlg->update("ʧȥ����");
			break;
		}
		else
		{
			msg[res] = '\0';
			dlg->update("server:" + CString(msg));
		}
	}

	//closesocket(sock);
	return 0;
}

void CcFileDlg::OnBnClickedSend()
{
	CString s;
	char * msg;
	send_edit.GetWindowText(s);
	msg = s.GetBuffer(s.GetLength());
	if (send(sock, msg, strlen(msg), 0) == SOCKET_ERROR)
	{
		update("����ʧ��");
	}
	else if (s == "")
	{
		MessageBox("��������Ϣ");
	}
	else
	{
		update("client:" + s);//��Ϣ������������룬���ػ񽹵�
		send_edit.SetWindowText("");
		send_edit.SetFocus();
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CcFileDlg::OnBnClickedbtnconnect()
{
	WSADATA wsaData;
	SOCKADDR_IN server_addr;
	WORD wVersion;
	wVersion = MAKEWORD(2, 2);
	WSAStartup(wVersion, &wsaData);
	// WSAStartup(0x0202, &wsaData);
	CString ip;
	ip_edit.GetWindowText(ip);//ȡ�÷�������IP��ַ
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5150);
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		edit1.ReplaceSel("create socket error\r\n");
	}
	if (connect(sock, (struct sockaddr *) &server_addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		edit1.ReplaceSel("����ʧ��\r\n");
	}
	else
	{
		edit1.ReplaceSel("���ӳɹ�\r\n");
		AfxBeginThread(&recv_thd, 0);
		btnconn.EnableWindow(FALSE);//��ť���
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
