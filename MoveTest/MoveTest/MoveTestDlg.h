
// MoveTestDlg.h : ͷ�ļ�
//

#pragma once
#include "atltypes.h"
#include "QiZi.h"
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

// CMoveTestDlg �Ի���
class CMoveTestDlg : public CDialogEx
{
// ����
public:
	CMoveTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOVETEST_DIALOG };
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
	CPoint m_MousePoint;
	CPoint OldPoint;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	int m_ButtonDownRL;
	afx_msg void OnBnClickedRestart();
	afx_msg void OnBnClickedDoublegame();

	bool m_DoubleGame;
	bool AIPlay(int Location_x, int Location_y);
	int Robot4Qizi();
	int Robot3QiZi();
	void RobotPlayer(int Location_x, int Location_y);

	void SetQiZiLocation(int m_ButtonDownRL, CPoint m_MousePoint);
	afx_msg void OnBnClickedSetting();
	afx_msg void OnBnClickedBkmusic();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
};
