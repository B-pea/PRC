
// PCRDlg.cpp : ʵ���ļ�
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
int enablePort;								//�õ��Ŀ��ö˿ں���ֵ
#include "enumser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPCRDlg �Ի���




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


// CPCRDlg ��Ϣ�������

BOOL CPCRDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CUIntArray ports;
	EnumerateSerialPorts(ports);
	for (int i=0; i<ports.GetSize(); i++)
	{
		enablePort = ports.ElementAt(i);
	}
	CString str;str.Format("%d",enablePort);
	SetDlgItemText(IDC_COMBO_CHOOSE,str); 

	OnBnClickedButtonPortChoose();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPCRDlg::OnPaint()
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
HCURSOR CPCRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPCRDlg::OnBnClickedButtonPortChoose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Text;
	GetDlgItem(IDC_BUTTON_PORT_CHOOSE)->GetWindowText(Text);

	if (Text=="�رմ���")
	{
		if( !m_ctrlComm.GetPortOpen()) 
		{
			AfxMessageBox("����δ�򿪣��޷��رգ�");
		}
		else
		{
			m_ctrlComm.SetPortOpen(FALSE);

			if(!m_ctrlComm.GetPortOpen())
			{
				AfxMessageBox("���ڹرճɹ���"); 
				GetDlgItem(IDC_BUTTON_PORT_CHOOSE)->SetWindowText("�򿪴���");
				CString a1="0";

			}
			else
			{
				AfxMessageBox("���ڹر�ʧ�ܣ�"); 
			}
		}
	}	
	else
	{		
		m_ctrlComm.SetCommPort(enablePort); //ѡ��com1  ����381��û�й�������DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
		if( !m_ctrlComm.GetPortOpen()) 
			m_ctrlComm.SetPortOpen(TRUE);//�򿪴��� 
		else 
			AfxMessageBox("cannot open serial port"); 

		m_ctrlComm.SetSettings("115200,n,8,1"); //������9600����У�飬8������λ��1��ֹͣλ 

		m_ctrlComm.SetInputMode(1); //1����ʾ�Զ����Ʒ�ʽ��ȡ���� 
		m_ctrlComm.SetRThreshold(1); //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼� 
		m_ctrlComm.SetInputLen(0); //���õ�ǰ���������ݳ���Ϊ0 
		m_ctrlComm.GetInput();//��Ԥ��������������������� 

		if(m_ctrlComm.GetPortOpen())
			AfxMessageBox("�򿪴��ڳɹ���");

		GetDlgItem(IDC_BUTTON_PORT_CHOOSE)->SetWindowText("�رմ���");
	}
}

BEGIN_EVENTSINK_MAP(CPCRDlg, CDialog)
	//{{AFX_EVENTSINK_MAP(CSCommTestDlg)
	ON_EVENT(CPCRDlg, IDC_MSCOMM1, 1 /* OnComm */, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPCRDlg::OnComm()	//�򿪺͹رն˿�
{
	UpdateData(TRUE);
	VARIANT variant_inp; 
	COleSafeArray safearray_inp; 
	LONG len,k; 
	BYTE rxdata[2048]; //����BYTE���� An 8-bit integerthat is not signed. 
	CString strtemp; 

	if(m_ctrlComm.GetCommEvent()==2) //�¼�ֵΪ2��ʾ���ջ����������ַ� 
	{ ////////��������Ը����Լ���ͨ��Э����봦����� 
		//Sleep(100);
		variant_inp=m_ctrlComm.GetInput(); //��������
		safearray_inp=variant_inp; //VARIANT�ͱ���ת��ΪColeSafeArray�ͱ��� 
		len=safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ��� 
		for(k=0;k<len;k++) 
			safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������ 
		for(k=0;k<len;k++) //������ת��ΪCstring�ͱ��� 
		{ 
			BYTE bt=*(BYTE*)(rxdata+k); //ԭ�����ַ���
			strtemp.Format(" %d",bt); //���ַ�������ʱ����strtemp��� 
			back_str+=strtemp; //������ձ༭���Ӧ�ַ��� 
			
		} 
		//SetDlgItemText(IDC_EDIT_TO_HOST,back_str); //���±༭������ 
	}

}

void CPCRDlg::OnBnClickedButLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("�ı��ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||");   
	// ��ʾ���ļ��Ի��� 
	CFileDialog fileDlg(TRUE, _T("bmp"), NULL, 0, szFilter, this);   
	CString strFilePath;   
	if (IDOK == fileDlg.DoModal())   
	{      
		strFilePath = fileDlg.GetPathName();      
	}  
	IplImage *image,*hsv;//ͼ��ռ�
	char * name = strFilePath.GetBuffer(0);//���ֽ��ַ���
	image = cvLoadImage(name);//��ͼ��Դͼ��

	//��ʾ�򿪵�ͼƬ�����������ŵ���Դ���С��
	CDC* pDC = GetDlgItem(IDC_STATIC)->GetDC();  
	HDC hDC = pDC->GetSafeHdc();    
	CvvImage cimg;  
	cimg.CopyOf( image,1 );  
	CRect rect;  
	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);  
	cimg.DrawToHDC(hDC, &rect);  
	ReleaseDC( pDC );  

	//BGRת��HSV�������H��S��V���ڱ���
	hsv=cvCreateImage(cvGetSize(image),8,3);//��hsvɫϵ��ͼ������ռ�
	cvCvtColor(image,hsv,CV_BGR2HSV);//��RGBɫϵתΪHSVɫϵ
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
	
	////�����㷨ʶ����ɨ��ͼ�񣬲�����Ӧ����
	//if ()//�ǲ���Ǯ��
	//{
	//	Money_hundred();
	//}
	//if ()//�ǲ���100Ԫ
	//{
	//}
	//if ()//�ǲ���50Ԫ
	//{
	//}
	//if ()//�ǲ���20Ԫ
	//{
	//}
	//if ()//�ǲ���10Ԫ
	//{
	//}

	cvReleaseImage( &image ); //�ͷ�ͼ��
	cvReleaseImage( &hsv );
}


void CPCRDlg::Money_hundred(void)
{

	CString commandSTART;
	commandSTART.Format("HOME X X 1 1 1\n");
	m_ctrlComm.SetOutput(COleVariant(commandSTART));//��������	
}
