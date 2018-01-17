// MainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GPA-Calculator.h"
#include "MainDialog.h"
#include "afxdialogex.h"



// CMainDialog dialog

IMPLEMENT_DYNAMIC(CMainDialog, CDialogEx)

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, SCORE(0)
{

}

CMainDialog::~CMainDialog()
{
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, SCORE);
}


BEGIN_MESSAGE_MAP(CMainDialog, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMainDialog::OnLvnItemchangedList1)
	ON_NOTIFY(LVN_INSERTITEM, IDC_LIST1, &CMainDialog::OnLvnInsertitemList1)
	ON_BN_CLICKED(IDC_RADIO3, &CMainDialog::OnBnClickedRadio3)
	ON_BN_CLICKED(IDOK, &CMainDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CMainDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMainDialog::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMainDialog message handlers


void CMainDialog::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


BOOL CMainDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_list.SetExtendedStyle(dwStyle);
	m_list.InsertColumn(0, _T("Course"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(1, _T("Semester"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T("Credits"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T("Score(100)"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, _T("GPA(4.0)"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T("Compulsory"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(6, _T("Major"), LVCFMT_LEFT, 100);
	vector<Courses> vec = readFile(filename);
	vec_courses = vec;
	int size = vec.size();
	for (int i = 0; i < size; i++) {
		items++;
		if (!vec[i].selected)
			continue;
		m_list.InsertItem(i, _T(" "));
		//set name
		string sname = vec[i].name;
		CString cname(sname.c_str());
		m_list.SetItemText(i, 0, cname);
		//set credits
		string scre = vec[i].credit;
		CString ccre(scre.c_str());
		m_list.SetItemText(i, 2, ccre);
		//set semester
		string ssem = vec[i].semester;
		CString csem(ssem.c_str());
		m_list.SetItemText(i, 1, csem);
		//set score
		string sscr = vec[i].score;
		CString cscr(sscr.c_str());
		m_list.SetItemText(i, 3, cscr);
		//set gpa
		string sgpa = vec[i].gpa;
		CString cgpa(sgpa.c_str());
		m_list.SetItemText(i, 4, cgpa);
		//set compulsory
		string scmp = vec[i].compulsory;
		CString ccmp(scmp.c_str());
		m_list.SetItemText(i, 5, ccmp);
		//set major
		string smj = vec[i].major;
		CString cmj(smj.c_str());
		m_list.SetItemText(i, 6, cmj);

	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CMainDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

void CMainDialog::OnLvnInsertitemList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CMainDialog::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	// Calculate compulsory score and gpa.
	UpdateData(TRUE);
	double scr = 0;
	double cre = 0;
	double gpa = 0;
	int size = vec_courses.size();
	for (int i = 0; i < size; i++) {
		double t_credit = atof(vec_courses[i].credit.c_str()) * atof(vec_courses[i].compulsory.c_str()) * vec_courses[i].selected;
		scr += atof(vec_courses[i].score.c_str()) * t_credit;
		gpa += atof(vec_courses[i].gpa.c_str()) * t_credit;
		cre += t_credit;
	}
	scr /= cre;
	gpa /= cre;
	SCORE = scr;
	UpdateData(FALSE);
}

void CMainDialog::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	// Calculate overall score and gpa.
	UpdateData(TRUE);
	double scr = 0;
	double cre = 0;
	double gpa = 0;
	int size = vec_courses.size();
	for (int i = 0; i < size; i++) {
		double t_credit = atof(vec_courses[i].credit.c_str()) * vec_courses[i].selected;
		scr += atof(vec_courses[i].score.c_str()) * t_credit;
		gpa += atof(vec_courses[i].gpa.c_str()) * t_credit;
		cre += t_credit;
	}
	scr /= cre;
	gpa /= cre;
	SCORE = scr;
	UpdateData(FALSE);

}


void CMainDialog::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	// Calculate major score and gpa.
	UpdateData(TRUE);
	double scr = 0;
	double cre = 0;
	double gpa = 0;
	int size = vec_courses.size();
	for (int i = 0; i < size; i++) {
		double t_credit = atof(vec_courses[i].credit.c_str()) * atof(vec_courses[i].major.c_str()) * vec_courses[i].selected;
		scr += atof(vec_courses[i].score.c_str()) * t_credit;
		gpa += atof(vec_courses[i].gpa.c_str()) * t_credit;
		cre += t_credit;
	}
	scr /= cre;
	gpa /= cre;
	SCORE = scr;
	UpdateData(FALSE);
}


void CMainDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int count = 0;
	vector<int> pos;
	for (int i = 0; i < items; i++) {
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_list.GetCheck(i) == 1) {
			CString nameToDel = m_list.GetItemText(i, 0);
			for (int j = 0; j < vec_courses.size(); j++) {
				string strname = vec_courses[j].name;
				if (strname.c_str() == nameToDel) {
					vec_courses[j].selected = 0;
				}
			}
			pos.push_back(i);
			count++;
		}
	}
	items -= count;
	for (int i = 0; i < pos.size(); i++) {
		m_list.DeleteItem(pos[i]);

	}
}
