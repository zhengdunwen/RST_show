
// DNA_ShowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DNA_Show.h"
#include "DNA_ShowDlg.h"
#include "afxdialogex.h"
#include <stdlib.h>


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


// CDNA_ShowDlg 对话框



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


// CDNA_ShowDlg 消息处理程序

BOOL CDNA_ShowDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	GetClientRect(&m_rect); //添加代码
	m_type.SetCurSel(0);
	m_prob.SetCurSel(0);
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.4, 0.6, 0, 2, 1);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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
	cimg.CopyOf(img); // 复制图片
	cimg.DrawToHDC(hDC, &rect); // 将图片绘制到显示控件的指定区域内
	ReleaseDC(pDC);
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDNA_ShowDlg::OnPaint()
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
// 		DrawPicToHDC(&m_image, IDC_STATIC);
// 		DrawBox(fileParms->m_listBoxsInfo);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	CPen pen(PS_DASH, 2, RGB(0, 0, 255)); //虚线 粗2 蓝色
	pDC->SelectObject(&pen);
// 	CBrush bush;
// 	bush.CreateSolidBrush(RGB(255, 0, 0));
// 	pDC->SelectObject(bush);


	list<BOXinfo>::iterator iter = box.begin();
	while (iter != box.end())
	{

		CPen pen(PS_DASH, 2, RGB(iter->classtype * 5, 0, iter->classtype * 10)); //虚线 粗2 蓝色
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

		
// 		//定义坐标点
// 		CPoint point1(100, 150);
// 		CPoint point2(400, 300);
// 
// 		//绘制矩形
// 		pDC->Rectangle(point1.x, point1.y, point2.x, point2.y);
		iter++;

	}
	ReleaseDC(pDC);
}

void CDNA_ShowDlg::OnBnClickedButton1()
{

	// TODO:  在此添加控件通知处理程序代码
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
	//左边图片控件显示图片
	//string s_path(m_path.GetBuffer());  //这样就要#include <string.h>
	char *s_path;
	s_path = m_path.GetBuffer(m_path.GetLength());   //将CString转化为Char * 格式
	//m_StaticPath.SetWindowTextA(m_path);  //将图片路径显示到静态文本控件
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
	if (nType != SIZE_MINIMIZED) //判断是否为最小化
	{
// 		ReSize(IDC_STATIC, cx, cy);
// 		ReSize(IDC_BUTTON1, cx, cy);
// 		ReSize(IDOK, cx, cy);
// 		ReSize(IDC_STATIC1, cx, cy);
// 		ReSize(IDC_STATIC2, cx, cy);
// 		ReSize(IDC_COMBO1, cx, cy);
// 		ReSize(IDC_COMBO2, cx, cy);
	}
	// TODO:  在此处添加消息处理程序代码
}
void CDNA_ShowDlg::ReSize(int nID, int cx, int cy)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(nID);     //获取控件句柄
	GetClientRect(&m_rect);
// 	if (pWnd && nID == IDC_STATIC)
// 	{
// 		
// 		CRect rect;   //获取控件变化前大小
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标
// 		rect.left = (int)(m_rect.left);//调整控件大小
// 		rect.right = (int)(m_rect.right -80 );
// 		rect.top = (int)(m_rect.top);
// 		rect.bottom = (int)(m_rect.bottom);
// 		pWnd->MoveWindow(rect);//设置控件位置
// 	}
// 	else if (pWnd && nID == IDC_BUTTON1)
// 	{
// 		CRect rect;   //获取控件变化前大小
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标
// 		rect.left = (int)(m_rect.right - 70);//调整控件大小
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.bottom-40);
// 		rect.bottom = (int)(m_rect.bottom-10);
// 		pWnd->MoveWindow(rect);//设置控件位置
// 	}
// 	else if (pWnd && nID == IDOK)
// 	{
// 		CRect rect;   //获取控件变化前大小
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标
// 		rect.left = (int)(m_rect.right - 70);//调整控件大小
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.bottom - 80);
// 		rect.bottom = (int)(m_rect.bottom - 50);
// 		pWnd->MoveWindow(rect);//设置控件位置
// 	}
// 	else if (pWnd && nID == IDC_STATIC1)
// 	{
// 		CRect rect;   //获取控件变化前大小
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标
// 		rect.left = (int)(m_rect.right - 70);//调整控件大小
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.top + 50);
// 		rect.bottom = (int)(m_rect.top + 70);
// 		pWnd->MoveWindow(rect);//设置控件位置
// 	}
// 	else if (pWnd && nID == IDC_COMBO1)
// 	{
// 		CRect rect;   //获取控件变化前大小
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标
// 		rect.left = (int)(m_rect.right - 70);//调整控件大小
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.top + 80);
// 		rect.bottom = (int)(m_rect.top + 300);
// 		pWnd->MoveWindow(rect);//设置控件位置
// 	}
// 	else if (pWnd && nID == IDC_STATIC2)
// 	{
// 		CRect rect;   //获取控件变化前大小
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标
// 		rect.left = (int)(m_rect.right - 70);//调整控件大小
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.top + 130);
// 		rect.bottom = (int)(m_rect.top + 150);
// 		pWnd->MoveWindow(rect);//设置控件位置
// 	}
// 
// 	else if (pWnd && nID == IDC_COMBO2)
// 	{
// 		CRect rect;   //获取控件变化前大小
// 		pWnd->GetWindowRect(&rect);
// 		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标
// 		rect.left = (int)(m_rect.right - 70);//调整控件大小
// 		rect.right = (int)(m_rect.right - 10);
// 		rect.top = (int)(m_rect.top + 160);
// 		rect.bottom = (int)(m_rect.top + 300);
// 		pWnd->MoveWindow(rect);//设置控件位置
// 	}

}

void CDNA_ShowDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	IplImage *iplImage = cvLoadImage(m_path.GetBuffer(), -1);
	iplImageSave = iplImage;
	if (iplImage->imageData == 0)
	{
		::AfxMessageBox("图片加载失败。");
		return;
	}

	if (fileParms == nullptr)
	{
		::AfxMessageBox("请先打开图像，分析后才能查看。");
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
				//在图像中显示文本字符串
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

	//------------------exe文件在当前路径下（可忽略）--------------
	//获取当前程序路径
	TCHAR exeFullPath[200];
	GetModuleFileName(NULL, exeFullPath, 100);
	//获取程序运行当前路径
	TCHAR drive[100], dir[100], fname[100], ext[20];
	_splitpath(exeFullPath, drive, dir, fname, ext);
	CString dirPath;
	dirPath.Format(("%s%s"), drive, dir);
	//------------------------------------------------------------

	//打开指定exe程序，并传递命令行参数SHELLEXECUTEINFO ShExecInfo;
	SHELLEXECUTEINFO ShExecInfo = { 0 };        // ShellExecuteEx调用例程及定义
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = this->m_hWnd;
	ShExecInfo.lpVerb = ("open");
	//输入要调用的exe文件路径
	CString exePath = dirPath + "x64\\darknet_no_gpu.exe";
	ShExecInfo.lpFile = (exePath);
	//传入命令行参数数据

	CString pram;
	pram.Format("  detector test %sx64\\cfg\\voc.data %sx64\\cfg\\yolov3.cfg  %sx64\\yolov3.weights -thresh 0.1 -save_labels -dont_show  %s", 
		dirPath, dirPath, dirPath, parms.c_str());

	ShExecInfo.lpParameters = (pram.GetBuffer()); //若没有命令行参数，可为NULL



	ShExecInfo.lpDirectory = dirPath;//这里exe的目录可忽略，写为NULL
	ShExecInfo.nShow = SW_SHOW;//这里设置为不显示exe界面，若设置为SW_SHOW，则可以显示exe界面
	ShExecInfo.hInstApp = NULL;
	//调用exe程序
	ShellExecuteEx(&ShExecInfo);
	//关闭该exe程序
	if (ShExecInfo.hProcess != NULL)
	{
		//等待程序运行完毕
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		//关闭程序
		TerminateProcess(ShExecInfo.hProcess, 0);
		ShExecInfo.hProcess = NULL;
	}

	return false;
}


void CDNA_ShowDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH]; //存放选择的目录路径 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));
	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择需要输出的目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		string str = szPath;
		str = str +"\\Temp.jpg";
		cvSaveImage(str.c_str(), iplImageSave);
	}
	else
		AfxMessageBox("无效的目录，请重新选择");
}
