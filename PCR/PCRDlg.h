
// PCRDlg.h : 头文件
//

#pragma once


// CPCRDlg 对话框
class CPCRDlg : public CDialogEx
{
// 构造
public:
	CPCRDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_PCR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void OnBnClickedButtonPortChoose();
	void OnComm();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
