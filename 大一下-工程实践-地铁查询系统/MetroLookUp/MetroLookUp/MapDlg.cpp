// MapDlg.cpp : ʵ���ļ�
//��һ��-����ʵ��-1-�ɶ�������ѯϵͳ-�û���
//���� 2015051152 �ƿ�154
//mailto://kanchisme@gmail.com
//http://akakanch.com
//

#include "stdafx.h"
#include "MetroLookUp.h"
#include "MetroLookUpDlg.h"
#include "MapDlg.h"
#include "afxdialogex.h"

// CMapDlg �Ի���

IMPLEMENT_DYNAMIC(CMapDlg, CDialogEx)

CMapDlg::CMapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAPS, pParent)
{
	csflog.Open(_T("log.txt"), CFile::modeWrite | CFile::modeCreate);
	csflog.Close();
	xfx.Open(_T("offset.mmld"), CFile::modeCreate | CFile::modeWrite);
	xfx.Close();
	TAG_METRO_LINE_SPILT.id = -1;
}

CMapDlg::~CMapDlg()
{
}

void CMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMapDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMapDlg ��Ϣ�������


void CMapDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	//���öԻ��򱳾���ɫΪ��ɫ
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	//���ص�ͼ
	//����Ҫ�ж�ƽ�ƻ����ļ���С������ܴ�Ļ���ֱ�Ӵ�ƽ�ƻ������
	if (firstrun)
	{
		if (!LoadMaps(PATH_MAP_CACHE, false))
		{
			MessageBox(_T("��ȡ��ͼ����ʧ�ܣ�\t\n\n�����������ӻ�����ͼ�б������ԡ�"), _T("����"), MB_OK | MB_ICONERROR);
		}
	}
	else
	{
		CFile fff;
		fff.Open(PATH_MOVE_MAP_CACHE, CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
		if (fff.GetLength() < 5)
		{
			fff.Close();
			if (!LoadMaps(PATH_MAP_CACHE, false))
			{
				MessageBox(_T("��ȡ��ͼ����ʧ�ܣ�\t\n\n�����������ӻ�����ͼ�б������ԡ�"), _T("����"), MB_OK | MB_ICONERROR);
			}
		}
		else
		{
			fff.Close();
			if (!LoadMaps(PATH_MOVE_MAP_CACHE, false))
			{
				MessageBox(_T("��ȡ��ͼ����ʧ�ܣ�\t\n\n�����������ӻ�����ͼ�б������ԡ�"), _T("����"), MB_OK | MB_ICONERROR);
			}
		}
	}

	CDialog::OnPaint();
}


/*//////////��ѯ�߼���
1.���ȸ���վ�����ֲ�ѯ��վ���Ӧ��ID����������·��
2.�ж�2��վ���Ƿ���ͬһ����·�ϡ�����ǣ���ֱ�Ӽ���ID��ֵ��Ȼ������ɢ����
3.����񣬲�ѯ��ʼվ�㵽Ŀ��վ��ģ�·������Ҫ��þ�������·�ͻ���վ�㣬Ȼ������ɢ
4.�ڵ�ͼ�ϻ��Ƴ��н���·
/*/
bool CMapDlg::LookUpPath(const STATION_DATA SD_BEG, const STATION_DATA SD_END)
{
	CString SQLstr, buf;
	CClientDC dcd(this);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 0, 0));
	dcd.SelectObject(&brush);
	CMLUDlg *mludlg = (CMLUDlg*)GetParent()->GetParent();
	//�����ж�2��վ���Ƿ���ͬһ����·��
	if (SD_BEG.line == SD_END.line) //��ͬһ����·
	{
		int line=SD_BEG.line;
		//�������û�з�������Ļ�������������Ҫ����SD_BEG��SD_END�ĺ�ɢ
		//Ȼ���ڵ�ͼ���ú��߱�ʾ��·��
		//�Ƚ���ͼ��λ
		CMapDlg::ClearMapOnSceen();
		CMapDlg::OnPaint();
		//���ȣ��������ڵ�ͼ�ϻ���·��
		CFile ff;
		MMD_NODE mnb;
		ff.Open(PATH_MOVE_MAP_CACHE, CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
		if (ff.GetLength() < 5)
		{
			ff.Close();
			ff.Open(PATH_MAP_CACHE, CFile::modeRead);
		}
		//����ѭ��Ѱ�����
		int begoft = 0,endoft=0; //��¼ƫ����
		int oftbuf = 0;
		int i = 0;
		while (ff.Read(&mnb, sizeof(MMD_NODE)) > 0)
		{
			if (mnb.id == TAG_METRO_LINE_SPILT.id)
			{
				ff.Seek(sizeof(MMD_HEAD), CFile::SeekPosition::current);//����ͷ��
				oftbuf += sizeof(MMD_NODE);
				oftbuf += sizeof(MMD_HEAD);
				continue;
			}
			if (mnb.id == SD_BEG.id)
			{
				begoft = oftbuf;
			}
			if (mnb.id == SD_END.id)
			{
				endoft = oftbuf;
			}
			oftbuf += sizeof(MMD_NODE);
		}
		//�ж�ƫ������С����Ϊ����Ҫ��С��ƫ������ʼ��ͼ
		int id = SD_END.id;
		if (begoft > endoft)
		{
			int t = begoft;
			begoft = endoft;
			endoft = t;
			id = SD_BEG.id;
		}
		//��ʼ���ƺ���·������ͼ��
		ff.SeekToBegin();
		ff.Seek(begoft, CFile::SeekPosition::current);
		MMD_NODE point;
		CPen pen(PS_SOLID, 6, RGB(255,0,0));  
		dcd.SelectObject(&pen);
		//����Ҫ����ѯ·�����������ļ���
		CFile lkp;
		lkp.Open(PATH_LOOKEDUP_CACHE, CFile::modeCreate | CFile::modeWrite);
		//���濪ʼ����·����ͬʱ�����ɢ
		int price = 0, time = 0;

		ff.Read(&mnb, sizeof(MMD_NODE));
		dcd.MoveTo(mnb.p);
		dcd.Ellipse(mnb.p.x - 10, mnb.p.y - 10, mnb.p.x + 10, mnb.p.y + 10);	
		dcd.TextOutW(mnb.p.x - 111, mnb.p.y -8, _T("���������->"));
		lkp.Write(&mnb, sizeof(MMD_NODE));
		while (ff.Read(&point, sizeof(MMD_NODE)) > 0)
		{
			
			dcd.LineTo(point.p);
			if (point.id == id)
			{
				break;
			}
			dcd.MoveTo(point.p);
			time += point.ltime;
			lkp.Write(&point, sizeof(MMD_NODE));
		}
		lkp.Close();
		mnb = point;
		dcd.Ellipse(mnb.p.x - 10, mnb.p.y - 10, mnb.p.x + 10, mnb.p.y + 10);
		dcd.TextOutW(mnb.p.x - 100, mnb.p.y - 8, _T("��������->"));
		//��Σ������ɢ��Ȼ���������
		price = point.lprice - mnb.lprice;
		mludlg->SetLookupPrice(price);
		mludlg->SetLookupTime(time);

		ff.Close();
	}
	else  //����ͬһ����·��
	{
		//����˼·������ʼ�㿪ʼ����ȡ���ɽڵ㣬Ȼ��һ��һ������չ���ڵ�
		CString lb, le, pdline=_T("");  //pdline���������Ѿ��������վ��
		lb.Format(_T("%d"), SD_BEG.line);
		le.Format(_T("%d"), SD_END.line);
		CString path;
		//Ȼ��ʼ����·��Ѱ��
		path = FindPathXX(SD_BEG.id,SD_END.id);
		//AfxMessageBox(path);
		//�ҵ�·�������濪ʼ����·������ͼ��
		// @1��2��3��4@5��6��7
		//����Ϊ������ַ����ṹ��ÿ������@��ʱ�����ǾͰѻ����ƶ���@����ĵ�һ��IDλ����ʹ��lineto
		//���@����ֻ��һ��id����������@��
		//Ȼ���ڵ�ͼ���ú��߱�ʾ��·��
		//�Ƚ���ͼ��λ
		CMapDlg::ClearMapOnSceen();
		CMapDlg::OnPaint();

		int price = 0, time = 0;
		CString TRSSTR=_T("������ʾ��\n"), bufstr;
		MMD_NODE mnb;
		CFile fff;
		fff.Open(PATH_MOVE_MAP_CACHE, CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
		if (fff.GetLength() < 5)
		{
			fff.Close();
			fff.Open(PATH_MAP_CACHE, CFile::modeRead);
		}
		CPen pen(PS_SOLID, 6, RGB(255, 0, 0));
		bool firststa=true;
		int i = 0;
		bool fsd = true;
		CPoint lp;
		while (true)
		{
			int nextlinebeg = path.Find(_T("@"),1);//������һ��@ֱ��Ѱ����һ��@�����û�У������Ǹ������ַ�������
			int firstcom = path.Find(_T(","));
			bool multiwaydraw = true;
			CString staid = path.Mid(1, firstcom -1);
			mnb = GetStation(_ttoi(staid), fff);
			CPoint linebegpoint = mnb.p;
			dcd.MoveTo(linebegpoint);
			if (fsd)
			{
				fsd = false;
				dcd.Ellipse(mnb.p.x - 10, mnb.p.y - 10, mnb.p.x + 10, mnb.p.y + 10);
				dcd.TextOutW(mnb.p.x - 111, mnb.p.y - 8, _T("���������->"));
			}
			int secondcom = path.Find(_T(","), firstcom+1);  //�ҵ��ڶ���,
			if (secondcom > nextlinebeg && nextlinebeg != -1)//����ڶ�,��λ�ô���������·��@˵��Ϊ����վ�㣬���ǾͲ��������ݽṹ���������� @1,@123,2,
			{
				multiwaydraw = false;
			}
			if (nextlinebeg != -1)
			{
				path = path.Right(path.GetLength() - firstcom - 1);  //ɾ���ոմ�������ַ���������@���͵�һ��վ�㡮id���͵�һ����,����
			}
			else
			{
				path = path.Right(path.GetLength() - 1);
			}
			int firstid = mnb.id;
			CString lastid;
			if (!firststa)
			{
				i++;
				buf.Format(_T("%d:�ڡ�%s�����ˡ�%d������\n"), i,CString(mnb.name), mnb.line);
				TRSSTR += buf;
			}
			while (multiwaydraw)
			{
				staid = _T("");
				firststa = false;
				for (int i = 0; i <= path.GetLength(); i++)
				{
					if (i == path.GetLength())
					{
						MMD_NODE endmnb = GetStation(_ttoi(lastid), fff);
						mnb = GetStation(firstid, fff);
						if (firstid < _ttoi(lastid))
						{
							price += (endmnb.lprice - mnb.lprice);
						}
						else
						{
							price += (endmnb.rprice - mnb.rprice);
						}
						multiwaydraw = false;
						path = _T("");
						break;
					}
					if (CString(path[i]) == CString(_T("@")))
					{
						MMD_NODE endmnb = GetStation(_ttoi(lastid), fff);
						mnb = GetStation(firstid, fff);
						if (firstid < _ttoi(lastid))
						{
							price += (endmnb.lprice - mnb.lprice);
						}
						else
						{
							price += (endmnb.rprice - mnb.rprice);
						}
						multiwaydraw = false;
						path = path.Right(path.GetLength() - i);
						break;
					}
					if (CString(path[i]) != CString(_T(",")))
					{
						staid += path[i];
					}
					else
					{
						mnb = GetStation(_ttoi(staid), fff);
						if (mnb.id > firstid)  //�����ʱ
						{
							time += mnb.ltime;
						}
						else
						{
							time += mnb.rtime;
						}
						dcd.SelectObject(&pen);
						linebegpoint = mnb.p;
						dcd.LineTo(linebegpoint);
						dcd.MoveTo(linebegpoint);
						lastid = staid;
						staid = _T("");
						lp = mnb.p;
					}
				}
			}
			if (path.GetLength()==0)
			{
				break;
			}
		}
		fff.Close();
		dcd.Ellipse(lp.x - 10, lp.y - 10, lp.x + 10, lp.y + 10);
		dcd.TextOutW(lp.x - 100, lp.y - 8, _T("��������->"));
		//���ü۸�
		mludlg->SetLookupPrice(price);
		mludlg->SetLookupTime(time);
		mludlg->SetTrsstrData(TRSSTR);
	}

	return true;
}

//�ú�����������һ����·�����ȵ���OnPaint��Ȼ���ٸ���
const bool CMapDlg::HighlightLine(const int linenum)
{
	ClearMapOnSceen();
	OnPaint();
	CFile ff;
	MMD_NODE mnb;
	ff.Open(PATH_MOVE_MAP_CACHE, CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	if (ff.GetLength() < 5)
	{
		ff.Close();
		ff.Open(PATH_MAP_CACHE, CFile::modeRead);
	}
	bool first = true;
	CClientDC dcd(this);
	CPen pen(PS_SOLID, 7, RGB(60, 255, 32));
	CBrush brush;
	brush.CreateSolidBrush(RGB(60, 255, 32));
	dcd.SelectObject(&pen);
	dcd.SelectObject(&brush);
	while (ff.Read(&mnb, sizeof(MMD_NODE)))
	{
		if (mnb.id == TAG_METRO_LINE_SPILT.id)
		{
			if (!first)
			{
				break;
			}
			ff.Seek(sizeof(MMD_HEAD), CFile::SeekPosition::current);
			continue;
		}
		if (first && mnb.line == linenum)
		{
			first = false;
			dcd.MoveTo(mnb.p);
			dcd.Ellipse(mnb.p.x - 7, mnb.p.y - 7, mnb.p.x + 7, mnb.p.y + 7);
			continue;
		}
		if (mnb.line == linenum)
		{
			dcd.LineTo(mnb.p);
			dcd.MoveTo(mnb.p);
			dcd.Ellipse(mnb.p.x - 7, mnb.p.y - 7, mnb.p.x + 7, mnb.p.y + 7);
		}
	}
	
	return true;
}

//���ص�ͼ�ĺ���
//�����������ͼ�ļ�·�����Ƿ��ǲ�ѯ��ĵ�ͼ����
//���ڶ�������Ϊtrue��ʱ��������Ҫ��PATH_LOOKEDUP_CACHE�ж�ȡ��ѯ��·�Ļ���
//���ڻ���վ��Ļ��Ʒ����������Ƶ�Ϊ����վ���ʱ��������Ҫ�ж��Ƿ�Ϊ��վ����״λ��ƣ�����ǣ����Ǿͻ��ƣ����򲻻���
const bool CMapDlg::LoadMaps(const CString & mapList, const bool not_looked_up)
{

	CPoint point,lbeg;
	CString linePath;
	CClientDC dcd(this);
	CStdioFile mf;   //���������ȡ��ͼ�б�
	CFile f;		//���������ȡÿ����·
	CMLUDlg *mludlg = (CMLUDlg*)GetParent()->GetParent();

	//��ʼ���Ƶ�ͼ
		f.Open(mapList, CFile::modeRead);
		MMD_HEAD mhb;
		MMD_NODE mnb;
		int ii = 0;
		while (f.Read(&mnb, sizeof(MMD_NODE)) > 0)
		{
			CPen pen;
			//�����ָ���
			if (mnb.id == TAG_METRO_LINE_SPILT.id)
			{
				//�����ָ�����˵��������Ӧ�ö�ȡ�ļ�ͷ
				f.Read(&mhb, sizeof(MMD_HEAD));
				//������Ӧ�Ļ���
				pen.CreatePen(PS_SOLID, 2, RGB(mhb.RGB[0], mhb.RGB[1], mhb.RGB[2]));
				dcd.SelectObject(&pen);

				//��������ȡһ������Ϊ���
				f.Read(&mnb, sizeof(MMD_NODE));
				ii = 0;
			}
			point = mnb.p;
			//վ�������������
			if (mnb.id > 0) //����0˵����վ��
			{
				CString transfer(mnb.name);
				//�ж��Ƿ�Ϊ����վ��
					//����ʵ��վ��
					CBrush brush;
					brush.CreateSolidBrush(RGB(mhb.RGB[0], mhb.RGB[1], mhb.RGB[2]));
					dcd.SelectObject(&brush);
					dcd.Ellipse(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
					dcd.TextOutW(point.x - 30, point.y + 10, transfer);
					if (mnb.transfer)
					{
						dcd.SelectObject(&pen);
						dcd.Rectangle(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
					}
			}
			//���Ƶ�ͼ
			//��ͼ����֮ǰ���ж�
			if (!ii)
			{
				lbeg = mnb.p;
				ii = 99999;
				continue;
			}
			dcd.MoveTo(lbeg);
			dcd.LineTo(point);
			lbeg = point;
		}
		f.Close();
		if (not_looked_up)   //������ǵ�ͼ�б��ļ�
		{

		}
	ResetTransferStationDrawedStatus();

	return true;
}



//��ͼƽ�ƺ���
//�����������ͼ�б���������
//���ڷֶε��жϣ�������id=-1��ʱ�򣬾�˵���µĵ�����·��ʼ��
const bool CMapDlg::MoveMap(const CString & mapList,const CPoint &mvet)
{
	CFile mvb;
	MMD_NODE mnb;
	MMD_HEAD mhb;
	mvb.Open(PATH_MOVE_MAP_CACHE, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
	//�ж�ƽ�ƻ����ļ��Ƿ������������Ǹ���PATH_MAP_CACHE�����ݵ�ƽ�ƻ����ļ�
	if (mvb.GetLength() < 5)
	{
		CFile mpb;
		mpb.Open(PATH_MAP_CACHE, CFile::modeRead);
		while (mpb.Read(&mnb, sizeof(MMD_NODE)) > 0)
		{
			//�ж��Ƿ�Ϊ�ָ���
			if (mnb.id == TAG_METRO_LINE_SPILT.id)
			{
				//���Ʒָ���
				mvb.Write(&mnb, sizeof(MMD_NODE));
				//���Ƶ�ͼͷ
				mpb.Read(&mhb, sizeof(MMD_HEAD));
				mvb.Write(&mhb, sizeof(MMD_HEAD));
				continue;
			}
			mvb.Write(&mnb, sizeof(MMD_NODE));
		}
		mpb.Close();
	}
	mvb.SeekToBegin();
	while (mvb.Read(&mnb, sizeof(MMD_NODE)) > 0)
	{
		//�ж��Ƿ�Ϊ�ָ���
		if (mnb.id == TAG_METRO_LINE_SPILT.id)
		{
			mvb.Read(&mhb, sizeof(MMD_HEAD));
			continue;
		}
		mnb.p.x += (mvet.x*-1);
		mnb.p.y += (mvet.y*-1);
		int seekpos = sizeof(MMD_NODE);
		seekpos*=-1;
		mvb.Seek(seekpos, CFile::SeekPosition::current);
		mvb.Write(&mnb, sizeof(MMD_NODE));
	}
	mvb.Close();
	return true;
}
const bool CMapDlg::HaveBeenDrawed(const CString & staname)
{
	for (int i = 0; i < 30; i++)
	{
		if (DrawedTransferStation[i] == staname)
		{
			return true;
		}
	}
	return false;
}
void CMapDlg::ResetTransferStationDrawedStatus()
{
	for (int i = 0; i < 30; i++)
	{
		DrawedTransferStation[i] = _T("");
	}
}
//�ú�������������û���������վ�㣬���û�У�����վ��IDΪ-1��
const MMD_NODE CMapDlg::GetCloseSTA(const CPoint pos,const bool no_zoom)
{
	MMD_NODE mnb;
	CFile ff;
	const int XOFT = 5;
	const int YOFT = 5;
	if (no_zoom)
	{
		ff.Open(PATH_MOVE_MAP_CACHE, CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	}
	if (ff.GetLength() < 5)
	{
		ff.Close();
		ff.Open(PATH_MAP_CACHE, CFile::modeRead);
	}
	while (ff.Read(&mnb, sizeof(MMD_NODE)) > 0)
	{
		if (mnb.id == TAG_METRO_LINE_SPILT.id)
		{
			ff.Seek(sizeof(MMD_HEAD), CFile::SeekPosition::current);
			continue;
		}
		int xoft = mnb.p.x - pos.x;
		int yoft = mnb.p.y - pos.y;
		if (xoft < 0)
		{
			xoft *= -1;
		}
		if (yoft < 0)
		{
			yoft *= -1;
		}
		if (xoft < XOFT && yoft < YOFT)
		{
			ff.Close();
			return mnb;
		}
	}
	ff.Close();
	mnb.id = -1;
	return mnb;
}

void CMapDlg::ShowMsg(const PROCESSqueue pq,const TRS trs, const CString processed,const CString others)
{
	CStdioFile csf;
	csf.Open(_T("open_path_log.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	csf.SeekToEnd();
	CString sstr;
	//sstr.Format(_T("%s:\n------------\n��ջվ��id:%d\nǰ���ȡ��%d\n\n·��ֵ��%s"), others, trs.id, (int)trs.read_ahead, trs.path);
	sstr.Format(_T("\n----------------%s:\npush_id:%d\nread_ahead:%d\npath_value:%s\nqueue size=%d\nprocess list=%s\n"), others, trs.id, (int)trs.read_ahead, trs.path,pq.size(), processed);
	csf.WriteString(sstr);
	//MessageBoxW(sstr, _T("·��չ��������Ϣ"), MB_ICONEXCLAMATION);

	csf.Close();
}

void CMapDlg::ResetMsg()
{
	CStdioFile csf;
	csf.Open(_T("open_path_log.txt"), CFile::modeCreate | CFile::modeReadWrite);
	csf.Close();
}

//�ú����������õ�ĳ��վ�����ļ��е���ʼλ��
//δ�ҵ�����-1
const int CMapDlg::GetSTApos(const int staID,  CFile & fff)
{
	int rawpos = fff.GetPosition();
	fff.SeekToBegin();
	MMD_NODE mnb;
	while (fff.Read(&mnb, sizeof(MMD_NODE)) > 0)
	{
		if (mnb.id == TAG_METRO_LINE_SPILT.id)
		{
			fff.Seek(sizeof(MMD_HEAD), CFile::SeekPosition::current);
			continue;
		}
		if (mnb.id == staID)
		{
			int pos = (fff.GetPosition() - sizeof(MMD_NODE));
			fff.Seek(rawpos, CFile::SeekPosition::begin);
			return pos;
		}
	}
	fff.Seek(rawpos, CFile::SeekPosition::begin);

	return -1;
}
//�ú�����������õ�ͼ�����ļ���ָ��վ��������·�ĵ�һ��վ���λ��
//δ�ҵ�����-1
const int CMapDlg::GetFirstSTApos(const int staid,  CFile & fff)
{
	int rawpos = fff.GetPosition();
	fff.SeekToBegin();
	MMD_NODE mnb;
	mnb = GetStation(staid, fff);
	int line = mnb.line;
	fff.SeekToBegin();
	while (fff.Read(&mnb, sizeof(MMD_NODE)) > 0)
	{
		if (mnb.id == TAG_METRO_LINE_SPILT.id)
		{
			fff.Seek(sizeof(MMD_HEAD), CFile::SeekPosition::current);
			continue;
		}
		if (mnb.line == line)
		{
			int pos = (fff.GetPosition() - sizeof(MMD_NODE));
			fff.Seek(rawpos, CFile::SeekPosition::begin);
			return pos;
		}
	}
	fff.Seek(rawpos, CFile::SeekPosition::begin);

	return -1;
}
//�ú��������õ�IDΪtrsid�Ļ���վ����������·�ϵ�id�������Ҫ��GV_TRSIDS���������ҵ�
//����ֵΪ����trsid֮�������id
const int CMapDlg::GetTRSids(const int trsid,  CFile & fff)
{
	int rawpos = fff.GetPosition();
	fff.SeekToBegin();
	MMD_NODE mnb;
	int i = 0;
	mnb = GetStation(trsid, fff);
	fff.SeekToBegin();
	CString TRSNAME(mnb.name);
	while (fff.Read(&mnb, sizeof(MMD_NODE)) > 0)
	{
		if (mnb.id == TAG_METRO_LINE_SPILT.id)
		{
			fff.Seek(sizeof(MMD_HEAD), CFile::SeekPosition::current);
			continue;
		}
		CString oname(mnb.name);
		if (oname == TRSNAME && mnb.id!=trsid)
		{
			GV_TRSIDS[i] = mnb.id;
			i++;
		}
	}
	fff.Seek(rawpos, CFile::SeekPosition::begin);

	return i;
}

//�ú�����������ָ��id���վ������
const MMD_NODE CMapDlg::GetStation(const int id, CFile &fff)
{
	MMD_NODE mnb;
	fff.SeekToBegin();
	while (fff.Read(&mnb, sizeof(MMD_NODE)) > 0)
	{
		if (mnb.id == TAG_METRO_LINE_SPILT.id)
		{
			fff.Seek(sizeof(MMD_HEAD), CFile::SeekPosition::current);
			continue;
		}
		if (mnb.id == id)
		{
			return mnb;
		}
	}
	return TAG_METRO_LINE_SPILT;
}

//�ú���������beg����read_headָ���ķ����ȡһ��վ�㳤�ȵ�����
//�����������㣬�յ㣬��ȡ����beg��pathֵ��չ�����Ľڵ��б���չ���ڵ���У��ļ�ָ��
//����ֵ��READNODE.findָʾ�Ƿ��ҵ�·�������READNODE.findΪ�棬��·��������READNODE.path��
const READNODE CMapDlg::ReadNode(const int beg, const int target,const bool read_ahead, const CString bpath, CString &processed,PROCESSqueue & po, CFile & fff)
{
	READNODE rnd;
	MMD_NODE BEG,mnb;
	int seekoft = sizeof(MMD_NODE);//���ݳ���
	seekoft *= -1;
	BEG = GetStation(beg, fff);
	CString TRSIDSTR;
	TRS buf;
	if (BEG.transfer)
	{
		int trssum = GetTRSids(beg, fff);  //���ȵõ��û���վ�������id���ϣ�������GV_TRSIDS������
		//����������չ��������ID֮�µ�����վ��
		//����Ҫ���������û���վ����ͬһ����·�ϵ���һ��δչ��վ��
		fff.Seek(GetSTApos(beg, fff), CFile::SeekPosition::begin);
		if (read_ahead)
		{
			fff.Seek(seekoft, CFile::SeekPosition::current);
		}
		else
		{
			fff.Seek(sizeof(MMD_NODE), CFile::SeekPosition::current);
		}
		fff.Read(&mnb, sizeof(MMD_NODE));
		TRSIDSTR.Format(_T("%d"), mnb.id);
		if (processed.Find(_T(",") + TRSIDSTR + _T(",")) < 0)
		{
			buf.id = mnb.id;
			buf.fpos = GetSTApos(mnb.id, fff);
			buf.path = bpath + TRSIDSTR + _T(",");
			buf.read_ahead = read_ahead;
			if (mnb.id == target)
			{
				rnd.find = true;
				rnd.path = buf.path;
				return rnd;
			}
			po.push(buf);
			TRSIDSTR.Format(_T("%d"), mnb.id);
			processed += TRSIDSTR + _T(",");
			ShowMsg(po,buf, processed,_T(">>>TRANSFER - ADD SAME LINE"));
		}
		//������ѭ������û���վ�������IDֵ����
		for (int i = 0; i < trssum; i++)
		{
			int pos = GetSTApos(GV_TRSIDS[i], fff);
			int firstSTApos = GetFirstSTApos(GV_TRSIDS[i], fff);  //�õ���ǰ��·��һ��վ���λ�ã�Ϊ�˱����ȡ����
			fff.Seek(pos, CFile::SeekPosition::begin);
			//�õ��û���վ��ǰ��һ����վ��
			if (firstSTApos != pos)  //�ڲ������ռ����������ǲŽ������뵽�¸�λ��
			{
				fff.Seek(seekoft, CFile::SeekPosition::current);//��λ��ǰһ��վ��λ��
				fff.Read(&mnb, sizeof(MMD_NODE));
				TRSIDSTR.Format(_T("%d"), mnb.id);
				if (processed.Find(_T(",") + TRSIDSTR + _T(",")) < 0)
				{
					buf.id = mnb.id;
					buf.fpos = GetSTApos(mnb.id, fff);
					TRSIDSTR.Format(_T("%d,@%d,%d,"), beg, GV_TRSIDS[i], mnb.id);
					buf.path = bpath + TRSIDSTR;
					buf.read_ahead = true;
					if (mnb.id == target)
					{
						rnd.find = true;
						rnd.path = buf.path;
						return rnd;
					}
					po.push(buf);
					ShowMsg(po,buf, processed,_T(">>>TRANSFER - ADD BEFORE STATION"));
					TRSIDSTR.Format(_T("%d"), mnb.id);
					processed += TRSIDSTR + _T(",");
				}
			}
			//�õ�beg��һ����վ��
			fff.Seek(pos, CFile::SeekPosition::begin);
			fff.Seek(sizeof(MMD_NODE), CFile::SeekPosition::current);//��λ����һ��վ��λ��
			fff.Read(&mnb, sizeof(MMD_NODE));
			TRSIDSTR.Format(_T("%d"), mnb.id);
			if (mnb.id != TAG_METRO_LINE_SPILT.id && processed.Find(_T(",") + TRSIDSTR + _T(",")) < 0)//�ڲ��Ƿָ���������£��Ž������뵽�¸�λ��
			{
				buf.id = mnb.id;
				buf.fpos = GetSTApos(mnb.id, fff);
				TRSIDSTR.Format(_T("%d,@%d,%d,"), beg, GV_TRSIDS[i], mnb.id);
				buf.path = bpath + TRSIDSTR;
				buf.read_ahead = false;
				if (mnb.id == target)
				{
					rnd.find = true;
					rnd.path = buf.path;
					return rnd;
				}
				po.push(buf);
				ShowMsg(po,buf, processed,_T(">>>TRANSFER - ADD BEHIND LINE"));
				TRSIDSTR.Format(_T("%d"), mnb.id);
				processed += TRSIDSTR + _T(",");
			}
		}
	}
	else
	{
		int pos = GetSTApos(beg, fff);
		int firstSTApos = GetFirstSTApos(beg, fff);  //�õ���ǰ��·��һ��վ���λ�ã�Ϊ�˱����ȡ����
		fff.Seek(GetSTApos(beg, fff), CFile::SeekPosition::begin);
		if (read_ahead)
		{
			if (pos == firstSTApos)
			{
				rnd.find = false;
				return rnd;
			}
			fff.Seek(seekoft, CFile::SeekPosition::current);
		}
		else
		{
			fff.Seek(sizeof(MMD_NODE), CFile::SeekPosition::current);
			if (fff.GetLength() == fff.GetPosition())//�����ļ�β��
			{
				rnd.find = false;
				return rnd;
			}
		}
		fff.Read(&mnb, sizeof(MMD_NODE));
		if (mnb.id == TAG_METRO_LINE_SPILT.id)
		{
			rnd.find = false;
			return rnd;
		}
		TRSIDSTR.Format(_T("%d"), mnb.id);
		if (processed.Find(_T(",")+TRSIDSTR+_T(",")) < 0)
		{
			buf.id = mnb.id;
			buf.fpos = GetSTApos(mnb.id, fff);
			buf.path = bpath + TRSIDSTR + _T(",");
			buf.read_ahead = read_ahead;
			if (!mnb.transfer)
			{
				if (mnb.id == target)
				{
					rnd.find = true;
					rnd.path = buf.path;
					return rnd;
				}
			}
			else
			{
				//�ж��Ƿ����յ�վ
				int trssum = GetTRSids(mnb.id, fff);  //���ȵõ��û���վ�������id���ϣ�������GV_TRSIDS������
				for (int r = 0; r < trssum; r++)
				{
					if (GV_TRSIDS[r] == target)
					{
						rnd.path = buf.path;
						rnd.find = true;
						return rnd;
					}
				}
			}
			po.push(buf);
			TRSIDSTR.Format(_T("%d"), mnb.id);
			processed += TRSIDSTR + _T(",");
			ShowMsg(po,buf, processed,_T(">>>NORMAL ADDING"));
		}
	}
	rnd.find = false;
	return rnd;
}

// �øú�����������beg��end֮�侭���������·��
//����ֵ��������վ��ID��@�ָ�ÿ����·�����ָ�ÿ��վ��ID
const CString CMapDlg::FindPathXX(const int beg, const int end)
{
	ResetMsg();
	CFile fff;
	fff.Open(PATH_MAP_CACHE, CFile::modeRead);
	PROCESSqueue poqueue;  //����������һ��Ҫ�����վ��
	CString processed = _T(""),path;
	path.Format(_T("@%d,"), beg);
	//���ȶ�ȡ���վ��ǰһ��վ��
	ReadNode(beg, end, true, path, processed, poqueue, fff);
	//Ȼ���ȡ���վ�ĺ�һ��վ��
	ReadNode(beg, end, false , path, processed, poqueue, fff);
	//��������ʼѭ������ֱ���ҵ��յ�վ�������Ͻ���poqueue����Ϊ�գ�never��
	READNODE rnb;
	while (!poqueue.empty())
	{
		ShowMsg(poqueue, poqueue.front(), processed, _T("-------------------------------->>>queue front "));
		rnb = ReadNode(poqueue.front().id, end, poqueue.front().read_ahead, poqueue.front().path, processed, poqueue, fff);
		if (rnb.find)
		{
			fff.Close();
			return rnb.path;
		}
		poqueue.pop();
	}
	fff.Close();
	return _T("NOT FOUND");
}

void CMapDlg::ClearMapOnSceen()
{
	CClientDC dcd(this);
	CRect rect;
	GetClientRect(rect);
	dcd.FillSolidRect(rect, RGB(255, 255, 255));
}

void CMapDlg::ResetMap()
{
	ClearMapOnSceen();
	OnPaint();
}


void CMapDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMLUDlg *mludlg = (CMLUDlg*)GetParent()->GetParent();
	offset = true;
	lbeg = point;
	CClientDC dcd(this);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,0,0));
	dcd.SelectObject(&brush);
	if (mludlg->IsBegFocused())
	{
		MMD_NODE mnb;
			 mnb = GetCloseSTA(point);
		if (mnb.id != -1)
		{
			mludlg->SetLUbeg(CString(mnb.name));
			dcd.Ellipse(mnb.p.x - 10, mnb.p.y - 10, mnb.p.x + 10, mnb.p.y + 10);
			dcd.TextOutW(mnb.p.x - 30, mnb.p.y + 10, _T("������:")+CString(mnb.name));
		}
	}
	else if (mludlg->IsEndFocused())
	{
		MMD_NODE mnb;
			mnb = GetCloseSTA(point);
		if (mnb.id != -1)
		{
			mludlg->SetLUend(CString(mnb.name));
			dcd.Ellipse(mnb.p.x - 10, mnb.p.y - 10, mnb.p.x + 10, mnb.p.y + 10);
			dcd.TextOutW(mnb.p.x - 30, mnb.p.y + 10, _T("Ŀ�ĵ�:") + CString(mnb.name));
		}
	}
	SetCursor(LoadCursor(NULL, IDC_HAND));
	

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMapDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	offset = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMapDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint mvet, draw, bbeg;
	if (offset)
	{
		//���㷽������
		SetCursor(LoadCursor(NULL, IDC_HAND));
		mvet.x = lbeg.x - point.x;
		mvet.y = lbeg.y - point.y;
		if (!MoveMap(PATH_MAP_CACHE,mvet))
		{
			MessageBox(_T("�޷��϶���ͼ������δ֪����"), _T("����"), MB_ICONERROR | MB_OK);
		}
		ClearMapOnSceen();
		LoadMaps(PATH_MOVE_MAP_CACHE,false);
		lbeg = point;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
