// Setting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MoveTest.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting �Ի���

IMPLEMENT_DYNAMIC(CSetting, CDialogEx)

CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_SizeOfQiPan(0)
	, m_SizeOfQiZi(0)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_QIPANSIZE, m_SizeOfQiPan);
	DDV_MinMaxInt(pDX, m_SizeOfQiPan, 5, 20);
	DDX_Text(pDX, IDC_QIZISIZE, m_SizeOfQiZi);
	DDV_MinMaxInt(pDX, m_SizeOfQiZi, 10, 30);
}


BEGIN_MESSAGE_MAP(CSetting, CDialogEx)
END_MESSAGE_MAP()


// CSetting ��Ϣ�������
