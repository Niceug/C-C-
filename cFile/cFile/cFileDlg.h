
// cFileDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CcFileDlg �Ի���
class CcFileDlg : public CDialogEx
{
// ����
public:
	CcFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CFILE_DIALOG };
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
	void update(CString s);
private:
	CEdit edit1;
	CEdit send_edit;
	CEdit ip_edit;
	CButton btnconn;
public:
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedbtnconnect();
};
