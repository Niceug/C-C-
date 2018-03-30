
// sFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "sFile.h"
#include "sFileDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SOCKET listen_sock;
SOCKET sock;
UINT server_thd(LPVOID p);
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CsFileDlg �Ի���



CsFileDlg::CsFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SFILE_DIALOG, pParent)
	, show_edit()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, show_edit);
	DDX_Control(pDX, IDC_EDIT2, send_edit);
}

BEGIN_MESSAGE_MAP(CsFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnSend, &CsFileDlg::OnBnClickedBtnsend)
END_MESSAGE_MAP()


// CsFileDlg ��Ϣ�������

BOOL CsFileDlg::OnInitDialog()
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

	send_edit.SetFocus();
	char name[80];
	CString IP;
	hostent* pHost;
	gethostname(name, 128);//��������� 
	pHost = gethostbyname(name);//��������ṹ 
	IP = inet_ntoa(*(in_addr *)pHost->h_addr);
	update("����IP��ַ��" + IP);
	AfxBeginThread(&server_thd, 0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CsFileDlg::update(CString s)
{
	show_edit.ReplaceSel(s + "\r\n");
}

UINT server_thd(LPVOID p)
{
	WSADATA wsaData;
	WORD wVersion;
	wVersion = MAKEWORD(2, 2);
	WSAStartup(wVersion, &wsaData);
	// WSAStartup(0x0202, &wsaData);
	SOCKADDR_IN local_addr;
	SOCKADDR_IN client_addr;
	int iaddrSize = sizeof(SOCKADDR_IN);
	int res;
	char msg[1024];
	CsFileDlg * dlg = (CsFileDlg *)AfxGetApp()->GetMainWnd();
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(5150);
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		dlg->update("��������ʧ��");
	}
	if (bind(listen_sock, (struct sockaddr*) &local_addr, sizeof(SOCKADDR_IN)))
	{
		dlg->update("�󶨴���");
	}
	listen(listen_sock, 5);//����û���
	if ((sock = accept(listen_sock, (struct sockaddr *)&client_addr, &iaddrSize)) == INVALID_SOCKET)
	{
		dlg->update("����ʧ��!");
	}
	else
	{
		CString port;
		port.Format("%d", int(ntohs(client_addr.sin_port)));
		dlg->update("���������ԣ�" + CString(inet_ntoa(client_addr.sin_addr)) + "\n  �˿ڣ�" +
			port);
	}

	////////////��������
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
			dlg->update("client:" + CString(msg));
		}
	}
	return 0;
}


void CsFileDlg::OnBnClickedBtnsend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString s;
	char * msg;
	send_edit.GetWindowText(s);
	msg = s.GetBuffer(s.GetLength());
	if (send(sock, msg, strlen(msg), 0) == SOCKET_ERROR)
	{
		show_edit.ReplaceSel("����ʧ��\r\n");
	}
	else if (s == "")
	{
		MessageBox("��������Ϣ");
	}
	else
	{
		show_edit.ReplaceSel("server:" + s + "\r\n");//��Ϣ������������룬���ػ񽹵�
		send_edit.SetWindowText("");
		send_edit.SetFocus();
	}
}

void CsFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CsFileDlg::OnPaint()
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
HCURSOR CsFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


