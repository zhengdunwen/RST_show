
// DNA_ShowDlg.h : 头文件
//

#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CvvImage.h"
#include "ReadPosFile.h"
#include "afxwin.h"
using namespace cv;
// CDNA_ShowDlg 对话框
class CDNA_ShowDlg : public CDialogEx
{
// 构造
public:
	CDNA_ShowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = ID_SHOWLEFT };

	protected:

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	IplImage m_image;
	cv::Mat Mat_image;
	IplImage *iplImageSave;
	CReadPosFile *fileParms;
	CvFont font;
	void DrawBox(list<BOXinfo> box);
public:
	afx_msg void OnBnClickedButton1();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void DrawPicToHDC(IplImage *img, UINT ID);
	CString m_path;
	BOOL m_capacity;
    CRect m_rect;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ReSize(int nID, int cx, int cy);
	afx_msg void OnBnClickedOk();
	CComboBox m_type;
	CComboBox m_prob;
	bool CallDarknet(string parms);
	afx_msg void OnBnClickedButton2();
};
