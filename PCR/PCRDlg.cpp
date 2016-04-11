
// PCRDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PCR.h"
#include "PCRDlg.h"
#include "afxdialogex.h"


#include <math.h>
#include "cv.h"
#include <string>
#include <iostream>  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp" 

#include "CvvImage.h"
#include "mscomm.h"
CMSComm	m_ctrlComm;
int enablePort;								//得到的可用端口号码值
#include "enumser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPCRDlg 对话框




CPCRDlg::CPCRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPCRDlg::IDD, pParent)
	, back_str(_T(""))
	, choose_port(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPCRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_CHOOSE, choose_port);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
}

BEGIN_MESSAGE_MAP(CPCRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_LOAD, &CPCRDlg::OnBnClickedButLoad)
END_MESSAGE_MAP()


// CPCRDlg 消息处理程序

BOOL CPCRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CUIntArray ports;
	EnumerateSerialPorts(ports);
	for (int i=0; i<ports.GetSize(); i++)
	{
		enablePort = ports.ElementAt(i);
	}
	CString str;str.Format("%d",enablePort);
	SetDlgItemText(IDC_COMBO_CHOOSE,str); 

	OnBnClickedButtonPortChoose();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPCRDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPCRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPCRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPCRDlg::OnBnClickedButtonPortChoose()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Text;
	GetDlgItem(IDC_BUTTON_PORT_CHOOSE)->GetWindowText(Text);

	if (Text=="关闭串口")
	{
		if( !m_ctrlComm.GetPortOpen()) 
		{
			AfxMessageBox("串口未打开，无法关闭！");
		}
		else
		{
			m_ctrlComm.SetPortOpen(FALSE);

			if(!m_ctrlComm.GetPortOpen())
			{
				AfxMessageBox("串口关闭成功！"); 
				GetDlgItem(IDC_BUTTON_PORT_CHOOSE)->SetWindowText("打开串口");
				CString a1="0";

			}
			else
			{
				AfxMessageBox("串口关闭失败！"); 
			}
		}
	}	
	else
	{		
		m_ctrlComm.SetCommPort(enablePort); //选择com1  错误381，没有关联变量DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
		if( !m_ctrlComm.GetPortOpen()) 
			m_ctrlComm.SetPortOpen(TRUE);//打开串口 
		else 
			AfxMessageBox("cannot open serial port"); 

		m_ctrlComm.SetSettings("115200,n,8,1"); //波特率9600，无校验，8个数据位，1个停止位 

		m_ctrlComm.SetInputMode(1); //1：表示以二进制方式检取数据 
		m_ctrlComm.SetRThreshold(1); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件 
		m_ctrlComm.SetInputLen(0); //设置当前接收区数据长度为0 
		m_ctrlComm.GetInput();//先预读缓冲区以清除残留数据 

		if(m_ctrlComm.GetPortOpen())
			AfxMessageBox("打开串口成功！");

		GetDlgItem(IDC_BUTTON_PORT_CHOOSE)->SetWindowText("关闭串口");
	}
}

BEGIN_EVENTSINK_MAP(CPCRDlg, CDialog)
	//{{AFX_EVENTSINK_MAP(CSCommTestDlg)
	ON_EVENT(CPCRDlg, IDC_MSCOMM1, 1 /* OnComm */, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPCRDlg::OnComm()	//打开和关闭端口
{
	UpdateData(TRUE);
	VARIANT variant_inp; 
	COleSafeArray safearray_inp; 
	LONG len,k; 
	BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed. 
	CString strtemp; 

	if(m_ctrlComm.GetCommEvent()==2) //事件值为2表示接收缓冲区内有字符 
	{ ////////以下你可以根据自己的通信协议加入处理代码 
		//Sleep(100);
		variant_inp=m_ctrlComm.GetInput(); //读缓冲区
		safearray_inp=variant_inp; //VARIANT型变量转换为ColeSafeArray型变量 
		len=safearray_inp.GetOneDimSize(); //得到有效数据长度 
		for(k=0;k<len;k++) 
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组 
		for(k=0;k<len;k++) //将数组转换为Cstring型变量 
		{ 
			BYTE bt=*(BYTE*)(rxdata+k); //原来是字符型
			strtemp.Format(" %d",bt); //将字符送入临时变量strtemp存放 
			back_str+=strtemp; //加入接收编辑框对应字符串 
			
		} 
		//SetDlgItemText(IDC_EDIT_TO_HOST,back_str); //更新编辑框内容 
	}

}

void CPCRDlg::OnBnClickedButLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("文本文件(*.bmp)|*.bmp|所有文件(*.*)|*.*||");   
	// 显示打开文件对话框 
	CFileDialog fileDlg(TRUE, _T("bmp"), NULL, 0, szFilter, this);   
	CString strFilePath;   
	if (IDOK == fileDlg.DoModal())   
	{      
		strFilePath = fileDlg.GetPathName();      
	}  
	IplImage *image,*hsv;//图像空间
	char * name = strFilePath.GetBuffer(0);//多字节字符集
	image = cvLoadImage(name);//打开图像源图像

	//显示打开的图片（按比例缩放到资源框大小）
	CDC* pDC = GetDlgItem(IDC_STATIC)->GetDC();  
	HDC hDC = pDC->GetSafeHdc();    
	CvvImage cimg;  
	cimg.CopyOf( image,1 );  
	CRect rect;  
	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);  
	cimg.DrawToHDC(hDC, &rect);  
	ReleaseDC( pDC );  

	//BGR转换HSV，并求出H、S、V所在比例
	hsv=cvCreateImage(cvGetSize(image),8,3);//给hsv色系的图像申请空间
	cvCvtColor(image,hsv,CV_BGR2HSV);//将RGB色系转为HSV色系
	CvScalar value_HSV = {0.0};
	double H = 0.0,S = 0.0,V = 0.0,
		H_proportion = 0.0,S_proportion = 0.0,V_proportion = 0.0,
		sum_total = 0.0;

	for(int i=0;i<hsv->height;i++)  
		for(int j=0;j<hsv->width;j++)
		{
			value_HSV = cvGet2D(hsv,i,j);
			H += value_HSV.val[0];
			S += value_HSV.val[1];
			V += value_HSV.val[2];
		}
	sum_total = H + S + V;
	H_proportion = H/sum_total;
	S_proportion = S/sum_total;
	V_proportion = V/sum_total;
	
	////根据算法识别所扫描图像，并做相应处理
	//if ()//是不是钱币
	//{
	//	Money_hundred();
	//}
	//if ()//是不是100元
	//{
	//}
	//if ()//是不是50元
	//{
	//}
	//if ()//是不是20元
	//{
	//}
	//if ()//是不是10元
	//{
	//}

	cvReleaseImage( &image ); //释放图像
	cvReleaseImage( &hsv );
}


void CPCRDlg::Money_hundred(void)
{

	CString commandSTART;
	commandSTART.Format("HOME X X 1 1 1\n");
	m_ctrlComm.SetOutput(COleVariant(commandSTART));//发送数据	
}
