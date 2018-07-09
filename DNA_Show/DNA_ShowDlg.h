
// DNA_ShowDlg.h : ͷ�ļ�
//

#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CvvImage.h"
#include "ReadPosFile.h"
#include "afxwin.h"
using namespace cv;
// CDNA_ShowDlg �Ի���
class CDNA_ShowDlg : public CDialogEx
{
// ����
public:
	CDNA_ShowDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = ID_SHOWLEFT };

	protected:

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
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
