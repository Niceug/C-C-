
// sFileDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

// CsFileDlg �Ի���
class CsFileDlg : public CDialogEx
{
// ����
public:
	CsFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SFILE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit show_edit;
	CEdit send_edit;
public:
	void update(CString s);
	afx_msg void OnBnClickedBtnsend();
};
