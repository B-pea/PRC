
// PCRDlg.h : ͷ�ļ�
//

#pragma once


// CPCRDlg �Ի���
class CPCRDlg : public CDialogEx
{
// ����
public:
	CPCRDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_PCR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void OnBnClickedButtonPortChoose();
	void OnComm();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	afx_msg void OnBnClickedButLoad();
	CString back_str;
	CString choose_port;
	void Money_hundred(void);
};
