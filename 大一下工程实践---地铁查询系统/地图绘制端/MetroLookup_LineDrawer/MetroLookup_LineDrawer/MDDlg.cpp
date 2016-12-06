// MDDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MetroLookup_LineDrawer.h"
#include "MDDlg.h"
#include "afxdialogex.h"
#include "MetroLookup_LineDrawerDlg.h"


// CMDDlg �Ի���

IMPLEMENT_DYNAMIC(CMDDlg, CDialogEx)

CMDDlg::CMDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAP_DRAWER, pParent)
{
	TAG_METRO_LINE_SPILT.id = -1;
	csflog.Open(_T("log.txt"), CFile::modeWrite |CFile::modeCreate);
	csflog.Close();
}

CMDDlg::~CMDDlg()
{
}

void CMDDlg::DoDataExchange(CDataExchange* pDX)
{ 
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMDDlg, CDialogEx)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMDDlg ��Ϣ�������


void CMDDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnLButtonUp(nFlags, point);
}

//��д���վ��Ĵ��룬Ϊ�˱���վ����ӵ�̫���ܣ����û��������վ�㣬��׼����ӵ�ʱ�����ǽ��ж�
//����λ���Ƿ�������·�ϣ�Ȼ�󽫵�����λ����Ϊ�µ�����ļ���
//***�߼����ģ�Ŀǰ����ֻ����վ��ĵ����ݣ�������·��Ϊֱ���߶�ʽ
void CMDDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	STA_BEG.p = point;
	CMLLDDlg * mlldlg = (CMLLDDlg*)GetParent()->GetParent();
	if (!mlldlg->IsDrawLock())
	{
		//�жϵ�ǰ��ӵ��Ƿ�Ϊ���վ,����ǵĻ�����������д���ͼ����
		if (mlldlg->IsAddBegStation() && !mlldlg->IsDrawLock())
		{
			//���ȴ�����·�ļ���Ȼ��д����·ͷ����
			CFile f;
			f.Open(STRING_BUFFER_FILENEMA, CFile::modeCreate | CFile::modeWrite);
			MAP_HEAD = mlldlg->GetHead();
			f.Write(&MAP_HEAD, sizeof(MMD_HEAD));
			//�����Ȼ��վ��ID��ŵ�����
			RunOnceFunction();
			//����վ��
			CClientDC dxc(this);
			CPen pen(PS_SOLID, MAP_HEAD.bound, RGB(MAP_HEAD.RGB[0], MAP_HEAD.RGB[1], MAP_HEAD.RGB[2]));
			dxc.SelectObject(&pen);
			dxc.Ellipse(point.x - 10, point.y - 10, point.x + 10, point.y + 10);
			dxc.TextOutW(STA_BEG.p.x - 10, STA_BEG.p.y + 5, mlldlg->GetStaBegName());
			//��վ��ĵ������д�뻺���ļ�
			STA_BEG.id = station_id;
			station_id++;
			STA_BEG.lprice = 0;
			STA_BEG.ltime = 0;
			STA_BEG.rprice = _ttoi(mlldlg->GetTermPrice());
			STA_BEG.line = mlldlg->GetLineConut()+1;
			STA_BEG.rtime = 0;
			STA_BEG.transfer = false;
			USES_CONVERSION;
			strcpy_s(STA_BEG.name, W2A(mlldlg->GetStaBegName()));
			f.Write(&STA_BEG, sizeof(MMD_NODE));
			f.Close();
			//ȡ���������״̬
			mlldlg->SetAddBegStationStatus(FALSE);
			lbeg = point;
			FIRST_TIME_L_BUTTON_DOWN = false;
		}
		//�жϵ�ǰ��ӵ��Ƿ�Ϊ�յ�վ
		if (mlldlg->IsAddEndStation())
		{
			CFile f;
			f.Open(STRING_BUFFER_FILENEMA, CFile::modeCreate | CFile::modeWrite|CFile::modeNoTruncate);
			f.SeekToEnd();
			CClientDC dxc(this);
			//�������ݿ�
			STA_BEG.id = station_id;
			station_id++;
			STA_BEG.p = point;
			////����վ�㣬�޸Ļ���
			CPen pen(PS_SOLID, MAP_HEAD.bound, RGB(MAP_HEAD.RGB[0], MAP_HEAD.RGB[1], MAP_HEAD.RGB[2]));
			dxc.SelectObject(&pen);
			dxc.Ellipse(point.x - 10, point.y - 10, point.x + 10, point.y + 10);
			dxc.TextOutW(STA_BEG.p.x - 10, STA_BEG.p.y + 5, mlldlg->GetStaEndName());
			//��վ��ĵ������д�뻺���ļ�
			STA_BEG.lprice = _ttoi(mlldlg->GetTermPrice());
			STA_BEG.ltime = 0;
			STA_BEG.rprice = 0;
			STA_BEG.rtime = 0;
			STA_BEG.line = mlldlg->GetLineConut() + 1;
			STA_BEG.transfer = false;
			USES_CONVERSION;
			strcpy_s(STA_BEG.name, W2A(mlldlg->GetStaEndName()));
			f.Write(&STA_BEG, sizeof(MMD_NODE));
			f.Close();
			//ȡ������յ��״̬
			mlldlg->SetAddEndStationStatus(FALSE);
			//�յ�վ�Ѿ���Ӻ󣬾Ͳ��������޸�
			mlldlg->SetAddStationStatus(FALSE);
			mlldlg->LockAll();
			dxc.MoveTo(lbeg);
			lbeg = point;
			dxc.LineTo(point);
		}
		if (mlldlg->IsAddStation())
		{
			CStdioFile logf;
			logf.Open(_T("dlog.txt"), CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate);
			logf.SeekToEnd();
			//���վ��
			STATION_DATA SD;
			CClientDC dc(this);
			CFile f;
			int offbytes = 0;
			f.Open(STRING_BUFFER_FILENEMA, CFile::modeWrite);
			f.SeekToEnd();
			//�õ�վ������
			SD = mlldlg->GetStationData();
			MMD_NODE map_node;
			map_node.p = point;
			map_node.id = station_id;
			station_id++;
			//��վ��ĵ������д�뻺���ļ�
			map_node.lprice = _ttoi(SD.L_price);
			map_node.ltime = _ttoi(SD.L_time);
			map_node.rprice = _ttoi(SD.R_price);
			map_node.rtime =_ttoi(SD.R_time);
			map_node.line = mlldlg->GetLineConut() + 1;
			if (mlldlg->IsTransferStation())
			{
				map_node.transfer = true;
				mlldlg->SetTransferStationStatus(false);
				lbeg = point;
				FIRST_TIME_L_BUTTON_DOWN = false;
			}
			else
			{
				map_node.transfer = false;
			}
			USES_CONVERSION;
			strcpy_s(map_node.name, W2A(SD.name));
			f.Write(&map_node, sizeof(MMD_NODE));
			f.Close();
			//���û���
			CPen pen(PS_SOLID, MAP_HEAD.bound, RGB(MAP_HEAD.RGB[0], MAP_HEAD.RGB[1], MAP_HEAD.RGB[2]));
			dc.SelectObject(&pen);
			//�����ڵ�ͼ�ϻ���
			dc.Ellipse(point.x - 10, point.y - 10, point.x + 10, point.y + 10);
			dc.TextOutW(map_node.p.x - 10, map_node.p.y + 5, SD.name);
			//�����ӳɹ���ȡ�����վ���״̬
			mlldlg->SetAddStationStatus(false);
			logf.Close();
			dc.MoveTo(lbeg);
			lbeg = point;
			dc.LineTo(point);
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMDDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMLLDDlg *mlldlg = (CMLLDDlg*)GetParent()->GetParent();
	if (mlldlg->IsAddStation() || mlldlg->IsAddBegStation() || mlldlg->IsAddEndStation())
	{
		SetCursor(LoadCursor(NULL, IDC_CROSS));
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

const bool CMDDlg::OnOpenExistFile(const CString filename, const bool blueprint)
{
	if (!blueprint)
	{
		if (!LoadMaps(filename, false))
		{
			MessageBox(_T("�����ļ�����"), _T("����"), MB_ICONERROR | MB_OK);
			return false;
		}
	}
	else
	{
		if (!LoadMaps(filename, false,true))
		{
			MessageBox(_T("�����ļ�����"), _T("����"), MB_ICONERROR | MB_OK);
			return false;
		}
	}
	return true;
}

const void CMDDlg::Undo()
{
	CFile f;
	int offbytes = sizeof(MMD_NODE);
	offbytes *= -1;
	f.Open(STRING_BUFFER_FILENEMA, CFile::modeReadWrite);
	f.SeekToEnd();
	if(f.GetPosition() <= sizeof(MMD_HEAD))
	{
		MessageBoxW(_T("�޷����г�������"), _T("����"), MB_ICONERROR);
		return;
	}
	f.Seek(offbytes, CFile::SeekPosition::current);
	MMD_NODE mnb,bkb;
	f.Read(&mnb, sizeof(MMD_NODE));
	f.Seek(offbytes*2, CFile::SeekPosition::current);
	f.Read(&bkb, sizeof(MMD_NODE));
	f.SetLength(f.GetPosition());
	f.Close();
	//�����������Ļ�ϸոջ���ȥ�Ǹ�
	CClientDC dc(this);
	COLORREF clo = dc.GetBkColor();

	//���û���
	CPen pen(PS_SOLID, MAP_HEAD.bound, RGB(GetRValue(clo), GetGValue(clo), GetBValue(clo)));
	dc.SelectObject(&pen);
	//�����ڵ�ͼ�ϻ���
	dc.Ellipse(mnb.p.x - 10, mnb.p.y - 10, mnb.p.x + 10, mnb.p.y + 10);
	dc.Rectangle(mnb.p.x - 10, mnb.p.y + 5, mnb.p.x+50 , mnb.p.y + 20);
	//������
	dc.MoveTo(mnb.p);
	dc.LineTo(bkb.p);
}

//�ú����������ѡ���վ��λ���Ƿ�Ϸ�
//�����ļ���߼����ж�������ΪԲ���ڣ��뾶r���Ƿ���ڵ�ͼ�ϵĵ�(��ʵ�Ǹ�����)
//�ڶ�������������ŵ�һ���ҵ�Ŀ����ƫ������Ϊ�˷���GetNearPos�����õ�
bool CMDDlg::CheckStationVaild(const CPoint p, int *offbyte)
{
	CFile f;  //������ȡraw�ļ�
	CMLLDDlg * mlldlg = (CMLLDDlg*)GetParent()->GetParent();
	if (!f.Open(mlldlg->GetFileName(), CFile::modeRead))
	{
		MessageBox(_T("վ�����ʧ�ܣ��޷��򿪻����ļ�\nIn function CheckStationVaild"), _T("����"), MB_ICONERROR | MB_OK);
	}
	MMD_HEAD mhb;
	MMD_NODE mnb;
	int xin=0, yin = 0;
	int bodys = 0;  //�ñ���������¼�ж��ٸ�node����ȡ��
	//ȥ��ͷ��
	f.Read(&mhb, sizeof(MMD_HEAD));
	//����������ѭ���ж��Ƿ���ڵ���ָ����Χ��
	while( f.Read(&mnb, sizeof(MMD_NODE)) > 0)
	{
		xin = mnb.p.x - p.x;
		yin = mnb.p.y - p.y;
		if (xin < 0)
		{
			xin *= -1;
		}
		if (yin < 0)
		{
			yin *= -1;
		}
		if (xin <= RANGE_X  && yin <= RANGE_Y)
		{	
			*offbyte = bodys*sizeof(MMD_NODE);
			f.Close();
			return true;
		}
		bodys++;
	}

	f.Close();
	return false;
}
//��ȷ���û��������վ���λ�úϷ��������������������û�ָ��������ĵ�ͼ�ϵĵ㣬����ԓ����Ϊվ��ʵ������д��
//�����߼�������·�ļ��б�����ֱ���ҵ��������С���Ǹ�����CheckStaitonVaildͨ��������£�һ�������ҵ���
//���£�ͨ�������ȡ�ļ�����ʵ�����ݵĸ�д���������Բ��ÿ������ļ�
//����˵������һ��Ϊ�û�ָ����վ�����꣬�ڶ�����վ��id,��3����Ϊ�˷����ļ����ң����õ���ʼƫ����(��λ���ֽ�)
const bool CMDDlg::SetStationANDWrite(const CPoint p,const int stationid,const int offbyte)
{
	CFile f;  //һ��������ȡraw�ļ���һ������д�뻺���ļ�
	CMLLDDlg * mlldlg = (CMLLDDlg*)GetParent()->GetParent();
	csflog.Open(_T("log.txt"), CFile::modeWrite | CFile::modeNoTruncate);
	csflog.SeekToEnd();
	csflog.WriteString(_T("-----[FUNCTION]----------SetStationANDWrite---------START--------\n"));
	if (!f.Open(mlldlg->GetFileName(), CFile::modeReadWrite))
	{
		MessageBox(_T("վ�����ʧ�ܣ��޷��򿪻����ļ�\nIn function SetStationANDWrite"), _T("����"), MB_ICONERROR | MB_OK);
		return false;
	}
	MMD_HEAD mhb;
	MMD_NODE mnb;
	MMD_NODE nearest[10];   //�������������������������ĵ�
	int xin = 0, yin = 0, sum = 0;
	int min = 200, minpos = 0;
	//��λָ�뵽CheckStationVaild�������ֵĵ�һ�����������ĵط�
	f.Read(&mhb, sizeof(MMD_HEAD));
	f.Seek(offbyte, CFile::SeekPosition::current);
	logstr.Format(_T("%d bytes\nstart find-neareast-point loop:\n"), offbyte);
	csflog.WriteString(_T("file pointer seek to ") + logstr);
	//���濪ʼѭ��������������������㣬Ȼ��д��վ������
	while (f.Read(&mnb, sizeof(MMD_NODE)) > 0 && sum<10)
	{
		xin = mnb.p.x - p.x;
		yin = mnb.p.y - p.y;
		logstr.Format(_T(" #%d : xin=%d,yin=%d\n\t-"), sum, xin, yin);
		csflog.WriteString(_T("pocess") + logstr);
		if (xin < 0)
		{
			xin *= -1;
		}
		if (yin < 0)
		{
			yin *= -1;
		}
		if (xin > RANGE_X  || yin > RANGE_Y)
		{
			csflog.WriteString(_T("DO NOT SATISFY\n"));
			break;
		}
		//Ѱ�������
		if ((xin + yin) / 2 < min)
		{
			csflog.WriteString(_T("SATISFY FOUND\n"));
			min = (xin + yin) / 2;
			minpos = sum;
		}
		//��¼��Χ�ڵ�10����
		nearest[sum] = mnb;
		sum++;
	}
	csflog.WriteString(_T("find-nearest-point loop end\n"));
	//��д�����
	int seekbyte = minpos*sizeof(MMD_NODE);
	logstr.Format(_T("%d\n"), seekbyte);
	csflog.WriteString(_T("VARIBLE seekbyte=")+logstr);
	f.SeekToBegin();
	f.Read(&mhb, sizeof(MMD_HEAD));
	f.Seek(offbyte + seekbyte, CFile::SeekPosition::current);
	logstr.Format(_T("file pointer seeked %d bytes\n"), offbyte + seekbyte);
	csflog.WriteString(logstr);
	nearest[minpos].id = stationid;
	logstr.Format(_T("station id=%d @ minpos=%d\n"), stationid, minpos);
	csflog.WriteString(logstr);
	f.Write(&nearest[minpos], sizeof(MMD_NODE));

	csflog.WriteString(_T("-----[FUNCTION]----------SetStationANDWrite---------END--------\n"));
	f.Close();
	csflog.Close();
	return true;
}


//���ص�ͼ�ĺ���
//�����������ͼ�ļ�·����·������
//��·������Ϊtue��ʱ�򣬱�ʾ������ǵ�ͼ�б��ļ�������Ϊfalse��ʱ�򣬱�ʾ������ǵ�ͼ�����ļ�

const bool CMDDlg::LoadMaps(const CString & path, const bool load_unfinished,const bool load_bule_print)
{
	CPoint point, lbeg;
	CClientDC dcd(this);
	CFile f;		//���������ȡÿ����·
	csflog.Open(_T("log.txt"), CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate);
	csflog.SeekToEnd();
	CMLLDDlg *mlldlg = (CMLLDDlg*)GetParent()->GetParent();
	csflog.WriteString(_T("-[FUNCTION]--------LoadMap function START------\n"));
	csflog.Flush();
	if (!load_bule_print)   //��������Ѿ����ڵĵ�ͼ�ļ�
	{
		csflog.WriteString(_T("load map file\n"));
		csflog.Flush();
		if (!f.Open(path, CFile::modeRead))
		{
			MessageBox(_T("��ͼ�б��ļ���ȡʧ�ܣ�"), _T("����"), MB_OK | MB_ICONERROR);
			return false;
		}
		//����Ĵ����������� MLD �ļ�������
		//������ͼͷ
		MMD_HEAD mmh;
		MMD_NODE mmn;
		mmn.id = 0;
		f.Read(&mmh, sizeof(MMD_HEAD));
		CPen pen(PS_SOLID, mmh.bound, RGB(mmh.RGB[0], mmh.RGB[1], mmh.RGB[2]));  //�����ﶨ��ʵ���ɫ,�ӵ�ͼ�����ļ��ж�ȡ
		dcd.SelectObject(&pen);
		//������ͼ��
		//f.Read(&mmn, sizeof(MMD_NODE));
		int i = 0;
		//lbeg = mmn.p;
		while (f.Read(&mmn, sizeof(MMD_NODE)) > 0)
		{
			point = mmn.p;
			//����load_unfinished���ò����������ж��Ƿ���ص����Ѿ���ɵĵ�ͼ���ǽ����ǵ�ͼ�ı༭״̬�е��ػ�
			//���ò�����F��T����������վ��Ĵ���ʽ�����Ʒ�ʽ��
			//�����վ�㣬�������ݿ��в�����ӦID
			if (mmn.id > 0) //����0˵����վ��
			{
				csflog.WriteString(_T("\n-#station found,start read data from date base\n"));
				csflog.Flush();
				_variant_t VSTADATA;
				CString IDBUF,SQLstr;
				IDBUF.Format(_T("%d"), mmn.id);
				SQLstr = _T("SELECT STANAME FROM STATION_DATA WHERE ID=") + IDBUF;
				m_RecordsetPtr.CreateInstance(_T("ADODB.Recordset"));
				m_RecordsetPtr =  mlldlg->GetConnectionPtr()->Execute(SQLstr.GetBuffer(0),NULL,adCmdText);
				csflog.WriteString(_T("\t#Retrive data from datebase successfully!\n"));
				csflog.Flush();
				VSTADATA = m_RecordsetPtr->GetCollect(_variant_t((long)0));
				m_RecordsetPtr->Close();
				CString STA_NAME = (LPCTSTR)VSTADATA.lVal;
				csflog.WriteString(_T("\t#now draw station: ")+STA_NAME);
				csflog.WriteString( _T("\n"));
				//�������ݿ��л����Ӧ��վ������
				if (load_unfinished)  //������ػ�
				{
					csflog.WriteString(_T("\t#Draw Type: unfinished=true\n"));
					csflog.Flush();
					dcd.Ellipse(point.x - 10, point.y - 10, point.x + 10, point.y + 10);
					dcd.TextOutW(point.x - 30, point.y + 10, STA_NAME);
					logstr.Format(_T("\t#Draw Completed.Station Data: STA_ID:%d----STATION NAME= "), mmn.id);
					logstr = logstr + STA_NAME ;
					csflog.WriteString(_T("\n"));
					csflog.WriteString(logstr);
					csflog.Flush();
				}
				else  //����Ǽ����Ѿ���ɵĵ�ͼ
				{
					csflog.WriteString(_T("\t#Draw Type: unfinished=false\n"));
					csflog.Flush();
					dcd.Ellipse(point.x - 10, point.y - 10, point.x + 10, point.y + 10);
					dcd.TextOutW(point.x - 30, point.y + 10, STA_NAME);
					logstr.Format(_T("\t#Draw Completed.Station Data: STA_ID:%d----STATION NAME= "), mmn.id);
					logstr = logstr + STA_NAME ;
					csflog.WriteString(_T("\n"));
					csflog.WriteString(logstr);
					csflog.Flush();
				}
			}
			//���Ƶ�ͼ
			if (!i)
			{
				lbeg = point;
				i = 99999;
				continue;
			}
			dcd.MoveTo(lbeg);
			dcd.LineTo(point);
			lbeg = point;
		}
		f.Close();
	}
	else  //�������ĵ�ַΪ��ͼ��ͼ����������������������·�ĵ�ͼ���������ǰ��յ�ʱ��MEtroLook�����м��ص�ͼƽ�����ݻ���ķ�ʽ�����ص�ͼ��ͼ
	{
		csflog.WriteString(_T("load blue print map file\n"));
		f.Open(path, CFile::modeRead);
		MMD_HEAD mhb;
		MMD_NODE mnb;
		int i = 0;
		csflog.WriteString(_T("Ready to read MMD_NODE data to draw\n"));
		while (f.Read(&mnb, sizeof(MMD_NODE)) > 0)
		{
			CPen pen;
			csflog.WriteString(_T("D"));
			//�����ָ���
			if (mnb.id == TAG_METRO_LINE_SPILT.id)
			{
				csflog.WriteString(_T("\nSPILT FOUND\n"));
				//�����ָ�����˵��������Ӧ�ö�ȡ�ļ�ͷ
				f.Read(&mhb, sizeof(MMD_HEAD));
				logstr = _T("");
				logstr.Format(_T("HEAD COLOR RGB(%d,%d,%d)\n\n"), mhb.RGB[0], mhb.RGB[1], mhb.RGB[2]);
				csflog.WriteString(_T("\nSPILT FOUND:head---"));
				csflog.WriteString(logstr);
				//������Ӧ�Ļ��ʣ����Ǵ�ϸ����2
				pen.CreatePen(PS_SOLID, mhb.bound-2, RGB(mhb.RGB[0], mhb.RGB[1], mhb.RGB[2]));
				dcd.SelectObject(&pen);
				//��������ȡһ������Ϊ��㣬�ٶ�ȡһ������Ϊ�յ�
				f.Read(&mnb, sizeof(MMD_NODE));
				i = 0;
			}
			point = mnb.p;
			//վ�������������
			if (mnb.id > 0) //����0˵����վ��
			{
				logstr.Format(_T("%s\n"), CString(mnb.name));
				csflog.WriteString(_T("STATION FOUND------") + logstr);
				dcd.Ellipse(point.x - 10, point.y - 10, point.x + 10, point.y + 10);
				dcd.TextOutW(point.x - 30, point.y + 10, logstr);
			}
			if (!i)
			{
				lbeg = point;
				i = 9999;
				continue;
			}
			//���Ƶ�ͼ
			dcd.MoveTo(lbeg);
			dcd.LineTo(point);
			lbeg = point;
		}
		f.Close();
	}
	csflog.WriteString(_T("\n-[FUNCTION]--------LoadMap function END------\n"));
	csflog.Close();

	return true;
}

//�ú�������ִ��SQL��䣬
const bool CMDDlg::KSQL_Excute(const CString cmd, _RecordsetPtr & rp)
{
	CMLLDDlg *cmlldlg = (CMLLDDlg*)GetParent()->GetParent();
	CString CMD = cmd;
	try
	{
		rp = cmlldlg->GetConnectionPtr()->Execute(CMD.GetBuffer(0), NULL, adCmdText);
	}
	catch (_com_error e)
	{
		MessageBoxW(_T("������Ϣ��") + e.Description(), _T("���ݿ��ȡ����"), MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}
const bool CMDDlg::KSQL_Excute(const CString cmd)
{
	CMLLDDlg *cmlldlg = (CMLLDDlg*)GetParent()->GetParent();
	CString CMD = cmd;
	try
	{
		cmlldlg->GetConnectionPtr()->Execute(CMD.GetBuffer(0), NULL, adCmdText);
	}
	catch (_com_error e)
	{
		MessageBoxW(_T("������Ϣ��") + e.Description(), _T("���ݿ��ȡ����"), MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

//�ú�����������¼�����Ƿ��������
//�����������¼������
//����ֵ��������������򷵻�true������false
const bool CMDDlg::KSQL_CheckRecordSetGotValue(const _RecordsetPtr rp)
{
	_variant_t vt;
	try
	{
		vt = rp->GetCollect((long)0);  //ֻ�жϵ�һ��¼��
	}
	catch (_com_error e)
	{
		return false;
	}
	return true;
}

void CMDDlg::RunOnceFunction()
{
	if (RunOnceFuncTimer)
	{
		CMLLDDlg * mlldlg = (CMLLDDlg*)GetParent()->GetParent();
		lineid = mlldlg->GetLineConut();
		lineid++;
		LINEIDBUF.Format(_T("%d"), lineid);
		station_id = mlldlg->GetLineStationCount();
		station_id++;
		RunOnceFuncTimer = false;
	}
}
