
// DNA_ShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DNA_Show.h"
#include "DNA_ShowDlg.h"
#include "afxdialogex.h"
#include <stdlib.h>


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


// CDNA_ShowDlg �Ի���



CDNA_ShowDlg::CDNA_ShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDNA_ShowDlg::IDD, pParent),
	fileParms(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDNA_ShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_type);
	DDX_Control(pDX, IDC_COMBO2, m_prob);
}

BEGIN_MESSAGE_MAP(CDNA_ShowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDNA_ShowDlg::OnBnClickedButton1)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CDNA_ShowDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CDNA_ShowDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDNA_ShowDlg ��Ϣ�������

BOOL CDNA_ShowDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	GetClientRect(&m_rect); //��Ӵ���
	m_type.SetCurSel(0);
	m_prob.SetCurSel(0);
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.4, 0.6, 0, 2, 1);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDNA_ShowDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CDNA_ShowDlg::DrawPicToHDC(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img); // ����ͼƬ
	cimg.DrawToHDC(hDC, &rect); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC(pDC);
}
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDNA_ShowDlg::OnPaint()
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
// 		DrawPicToHDC(&m_image, IDC_STATIC);
// 		DrawBox(fileParms->m_listBoxsInfo);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDNA_ShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDNA_ShowDlg::DrawBox(list<BOXinfo> box)
{
	CDC *pDC = GetDlgItem(IDC_STATIC)->GetDC();
	HDC hdc = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);

	CPen pen(PS_DASH, 2, RGB(0, 0, 255)); //���� ��2 ��ɫ
	pDC->SelectObject(&pen);
// 	CBrush bush;
// 	bush.CreateSolidBrush(RGB(255, 0, 0));
// 	pDC->SelectObject(bush);


	list<BOXinfo>::iterator iter = box.begin();
	while (iter != box.end())
	{

		CPen pen(PS_DASH, 2, RGB(iter->classtype * 5, 0, iter->classtype * 10)); //���� ��2 ��ɫ
		pDC->SelectObject(&pen);

		CPoint point1(iter->box[0] * rect.Width(), iter->box[1] * rect.Height());
		CPoint point2(iter->box[0] * rect.Width() + iter->box[2] * rect.Width(), iter->box[1] * rect.Height());
		CPoint point3(iter->box[0] * rect.Width() + iter->box[2] * rect.Width(), iter->box[1] * rect.Height() + rect.Height()*iter->box[3]);
		CPoint point4(iter->box[0] * rect.Width(), iter->box[1] * rect.Height() + rect.Height()*iter->box[3]);

		MoveToEx(hdc, point1.x, point1.y, NULL);
		LineTo(hdc, point2.x, point2.y);

		MoveToEx(hdc, point2.x, point2.y, NULL);
		LineTo(hdc, point3.x, point3.y);

		MoveToEx(hdc, point3.x, point3.y, NULL);
		LineTo(hdc, point4.x, point4.y);

		MoveToEx(hdc, point4.x, point4.y, NULL);
		LineTo(hdc, point1.x, point1.y);

		
// 		//���������
// 		CPoint point1(100, 150);
// 		CPoint point2(400, 300);
// 
// 		//���ƾ���
// 		pDC->Rectangle(point1.x, point1.y, point2.x, point2.y);
		iter++;

	}
	ReleaseDC(pDC);
}

void CDNA_ShowDlg::OnBnClickedButton1()
{

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Invalidate();
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY,
		TEXT("Supported Types (*.jpg;)|*.jpg;|All Files(*.*)|*.*||"), NULL);
	dlg.m_ofn.nFilterIndex = 1;
	dlg.m_ofn.hwndOwner = m_hWnd;
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	dlg.m_ofn.lpstrTitle = TEXT("Opening Image...\0");
	dlg.m_ofn.nMaxFile = MAX_PATH;
	if (dlg.DoModal() == IDOK)
	{
		m_path = dlg.GetPathName();
		m_capacity = TRUE;
		UpdateData(FALSE);
	}
	else
		return;
	//���ͼƬ�ؼ���ʾͼƬ
	//string s_path(m_path.GetBuffer());  //������Ҫ#include <string.h>
	char *s_path;
	s_path = m_path.GetBuffer(m_path.GetLength());   //��CStringת��ΪChar * ��ʽ
	//m_StaticPath.SetWindowTextA(m_path);  //��ͼƬ·����ʾ����̬�ı��ؼ�
	Mat_image = cv::imread(s_path, 1);



	
	m_image = Mat_image;

	//string parms = " detector test D:\\tensorflow_code\\darknet_windows\\build\\darknet\\x64\\cfg\\voc.data D:\\tensorflow_code\\darknet_windows\\build\\darknet\\x64\\cfg\\yolov3.cfg D:\\tensorflow_code\\darknet_windows\\build\\darknet\\x64\\yolov3_3030000.weights -thresh 0.1 -save_labels -dont_show " + m_path;
	string parms = m_path;
	

	CallDarknet(parms);

// 	ShellExecute(this->m_hWnd, "open", "D:\\tensorflow_code\\darknet_windows\\build\\darknet\\x64\\darknet_no_gpu.exe",
// 						parms.c_str(),
// 					   "",
// 					   SW_SHOW);

	string pathBox = s_path;
	pathBox = pathBox.substr(0, pathBox.length() - 3) + "txt";
	fileParms = new CReadPosFile(pathBox);
	fileParms->readfileInfo();

// 	DrawPicToHDC(&m_image, IDC_STATIC);
// 	DrawBox(fileParms->m_listBoxsInfo);
}


void CDNA_ShowDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	if (nType != SIZE_MINIMIZED) //�ж��Ƿ�Ϊ��С��
	{
// 		ReSize(IDC_STATIC, cx, cy);
// 		ReSize(IDC_BUTTON1, cx, cy);
// 		ReSize(IDOK, cx, cy);
// 		ReSize(IDC_STATIC1, cx, cy);
// 		ReSize(IDC_STATIC2, cx, cy);
// 		ReSize(IDC_COMBO1, cx, cy);
// 		ReSize(IDC_COMBO2, cx, cy);
	}
	// TODO:  �ڴ˴������Ϣ����������
}
void CDNA_ShowDlg::ReSize(int nID, int cx, int cy)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(nID);     //��ȡ�ؼ����
	GetClientRect(&m_rect);
// 	if (pWnd && nID == IDC_STATIC)
// 	{
// 		
// 		CRect rect;   //��ȡ�ؼ��仯ǰ��С
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
// 		rect.left = (int)(m_rect.left);//�����ؼ���С
// 		rect.right = (int)(m_rect.right -80 );
// 		rect.top = (int)(m_rect.top);
// 		rect.bottom = (int)(m_rect.bottom);
// 		pWnd->MoveWindow(rect);//���ÿؼ�λ��
// 	}
// 	else if (pWnd && nID == IDC_BUTTON1)
// 	{
// 		CRect rect;   //��ȡ�ؼ��仯ǰ��С
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
// 		rect.left = (int)(m_rect.right - 70);//�����ؼ���С
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.bottom-40);
// 		rect.bottom = (int)(m_rect.bottom-10);
// 		pWnd->MoveWindow(rect);//���ÿؼ�λ��
// 	}
// 	else if (pWnd && nID == IDOK)
// 	{
// 		CRect rect;   //��ȡ�ؼ��仯ǰ��С
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
// 		rect.left = (int)(m_rect.right - 70);//�����ؼ���С
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.bottom - 80);
// 		rect.bottom = (int)(m_rect.bottom - 50);
// 		pWnd->MoveWindow(rect);//���ÿؼ�λ��
// 	}
// 	else if (pWnd && nID == IDC_STATIC1)
// 	{
// 		CRect rect;   //��ȡ�ؼ��仯ǰ��С
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
// 		rect.left = (int)(m_rect.right - 70);//�����ؼ���С
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.top + 50);
// 		rect.bottom = (int)(m_rect.top + 70);
// 		pWnd->MoveWindow(rect);//���ÿؼ�λ��
// 	}
// 	else if (pWnd && nID == IDC_COMBO1)
// 	{
// 		CRect rect;   //��ȡ�ؼ��仯ǰ��С
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
// 		rect.left = (int)(m_rect.right - 70);//�����ؼ���С
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.top + 80);
// 		rect.bottom = (int)(m_rect.top + 300);
// 		pWnd->MoveWindow(rect);//���ÿؼ�λ��
// 	}
// 	else if (pWnd && nID == IDC_STATIC2)
// 	{
// 		CRect rect;   //��ȡ�ؼ��仯ǰ��С
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
// 		rect.left = (int)(m_rect.right - 70);//�����ؼ���С
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.top + 130);
// 		rect.bottom = (int)(m_rect.top + 150);
// 		pWnd->MoveWindow(rect);//���ÿؼ�λ��
// 	}
// 
// 	else if (pWnd && nID == IDC_COMBO2)
// 	{
// 		CRect rect;   //��ȡ�ؼ��仯ǰ��С
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
// 		rect.left = (int)(m_rect.right - 70);//�����ؼ���С
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.top + 160);
// 		rect.bottom = (int)(m_rect.top + 300);
// 		pWnd->MoveWindow(rect);//���ÿؼ�λ��
// 	}

}

void CDNA_ShowDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	IplImage *iplImage = cvLoadImage(m_path.GetBuffer(), -1);
	iplImageSave = iplImage;
	if (iplImage->imageData == 0)
	{
		::AfxMessageBox("ͼƬ����ʧ�ܡ�");
		return;
	}

	if (fileParms == nullptr)
	{
		::AfxMessageBox("���ȴ�ͼ�񣬷�������ܲ鿴��");
	}

	
	list<BOXinfo>::iterator iter = fileParms->m_listBoxsInfo.begin();
	int typeClass = m_type.GetCurSel() ;
	float probInfo = ((float)m_prob.GetCurSel() + 1.00)*0.1;

	float width = (float)iplImage->width;
	float height = (float)iplImage->height;










	while (iter != fileParms->m_listBoxsInfo.end())
	{
		if (typeClass == 0 || iter->classtype+1 == typeClass)
		{
			if (iter->xiangshidu >= probInfo)
			{
				int R = (rand() % (250 + 1));
				int G = (rand() % (250 + 1));
				int B = (rand() % (250 + 1));
				
		
				CPoint point1(iter->box[0] * width - iter->box[2] * width / 2, iter->box[1] * height - height*iter->box[3] / 2);
				CPoint point3(iter->box[0] * width + iter->box[2] * width / 2, iter->box[1] * height + height*iter->box[3] / 2);

				cvRectangle(iplImage, cvPoint(point1.x, point1.y), cvPoint(point3.x, point3.y), Scalar(R,G,B), 2, 2, 0);
				//��ͼ������ʾ�ı��ַ���
				CString info;
				info.Format("%d : %d%%", iter->classtype + 1, (int)(iter->xiangshidu * 100));
				cvPutText(iplImage, info.GetBuffer(), cvPoint(point1.x, point1.y - 5), &font, CV_RGB(R, G, B));
			}
		}


		iter++;
	}

	cvShowImage("Image", iplImage);

}




bool CDNA_ShowDlg::CallDarknet(string parms)
{
// 	ShellExecute(this->m_hWnd, "open", "D:\\tensorflow_code\\darknet_windows\\build\\darknet\\x64\\darknet_no_gpu.exe",
// 		parms.c_str(),
// 		"",
// 		SW_SHOW);

	//------------------exe�ļ��ڵ�ǰ·���£��ɺ��ԣ�--------------
	//��ȡ��ǰ����·��
	TCHAR exeFullPath[200];
	GetModuleFileName(NULL, exeFullPath, 100);
	//��ȡ�������е�ǰ·��
	TCHAR drive[100], dir[100], fname[100], ext[20];
	_splitpath(exeFullPath, drive, dir, fname, ext);
	CString dirPath;
	dirPath.Format(("%s%s"), drive, dir);
	//------------------------------------------------------------

	//��ָ��exe���򣬲����������в���SHELLEXECUTEINFO ShExecInfo;
	SHELLEXECUTEINFO ShExecInfo = { 0 };        // ShellExecuteEx�������̼�����
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = this->m_hWnd;
	ShExecInfo.lpVerb = ("open");
	//����Ҫ���õ�exe�ļ�·��
	CString exePath = dirPath + "x64\\darknet_no_gpu.exe";
	ShExecInfo.lpFile = (exePath);
	//���������в�������

	CString pram;
	pram.Format("  detector test %sx64\\cfg\\voc.data %sx64\\cfg\\yolov3.cfg  %sx64\\yolov3.weights -thresh 0.1 -save_labels -dont_show  %s", 
		dirPath, dirPath, dirPath, parms.c_str());

	ShExecInfo.lpParameters = (pram.GetBuffer()); //��û�������в�������ΪNULL



	ShExecInfo.lpDirectory = dirPath;//����exe��Ŀ¼�ɺ��ԣ�дΪNULL
	ShExecInfo.nShow = SW_SHOW;//��������Ϊ����ʾexe���棬������ΪSW_SHOW���������ʾexe����
	ShExecInfo.hInstApp = NULL;
	//����exe����
	ShellExecuteEx(&ShExecInfo);
	//�رո�exe����
	if (ShExecInfo.hProcess != NULL)
	{
		//�ȴ������������
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		//�رճ���
		TerminateProcess(ShExecInfo.hProcess, 0);
		ShExecInfo.hProcess = NULL;
	}

	return false;
}


void CDNA_ShowDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH]; //���ѡ���Ŀ¼·�� 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "��ѡ����Ҫ�����Ŀ¼��";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		string str = szPath;
		str = str +"\\Temp.jpg";
		cvSaveImage(str.c_str(), iplImageSave);
	}
	else
		AfxMessageBox("��Ч��Ŀ¼��������ѡ��");
}
