/*tac gia: Trần Đăng Khoa
phân công:Phiếu mượn
*/
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <sstream>
#include <iomanip>
using namespace std;
// nguyen mau ham
int PhieuMuon::nTongPM = 0;
void inputData_PhieuMuon(list <PhieuMuon> &L4);
void them_PhieuMuon(list <PhieuMuon> &L4, list <BanDoc*> L2, list <Sach> &L3);
void outputData_PhieuMuon_ToScreen(list <PhieuMuon> L4);
void outputData_PhieuMuon_File(list <PhieuMuon> L4, list <BanDoc*> L2, list <Sach> L3);
int demTongPhieuMuon(list <PhieuMuon> L4);
void traSach_PhieuMuon(list <PhieuMuon> &L4, list <BanDoc*> L2, list <Sach> &L3);
void lietKeSach1BanDocDangMuon(list <PhieuMuon> L4, list <Sach> L3);
bool ktrHetHanMuon(int nNgayTra, int nThangTra, int nNamTra, int nNgayHienTai, int nThangHienTai, int nNamHienTai);
void xuat_DS_PM_HetHanMuonSach(list <PhieuMuon> L4);

//dinh nghia ham con
void xuat_DS_PM_HetHanMuonSach(list <PhieuMuon> L4)
{
	int nNgayTra = 0;
	int nThangTra = 0;
	int nNamTra = 0;
	time_t t = time(0); 
	struct tm *Now = localtime(&t);
	int nNgayHienTai = Now->tm_mday;
	int nThangHienTai = Now->tm_mon+1;
	int nNamHienTai = Now->tm_year+1900;
	list <PhieuMuon> ::iterator p = L4.begin();
	while(p != L4.end())
	{
		nNgayTra = p->getNgayTra().getNgay();
		nThangTra = p->getNgayTra().getThang();
		nNamTra = p->getNgayTra().getNam();
		if (ktrHetHanMuon(nNgayTra, nThangTra, nNamTra, nNgayHienTai, nThangHienTai, nNamHienTai) == true && p->getTrangThai() != 0)
		{
			p->xuat();
		}
		p++;
	}	
}
bool ktrHetHanMuon(int nNgayTra, int nThangTra, int nNamTra, int nNgayHienTai, int nThangHienTai, int nNamHienTai)
{	//true la den han tra
	//false la van con han muon
	if(nNamHienTai > nNamTra) 
	{
		return true;
	}
	else if (nThangHienTai > nThangTra) 
	{
		return true;
	}
	else if (nThangHienTai < nThangTra) // trường hợp: ngày hiện tại 29/5/2018 - ngày trả 5/6/2018
	{
		return false;
	}
	else if (nNgayHienTai > nNgayTra)
	{
		return true;
	}
	return false;
}
void lietKeSach1BanDocDangMuon(list <PhieuMuon> L4, list <Sach> L3)
{
	int flag = 0;
	string sMBD = "";
dd:
	textColor(4);
	cout << "\t\tNhap N de thoat!\n";
	textColor(7);
	cout << "\t\tNhap ma ban doc: ";
	fflush(stdin);
	getline(cin, sMBD);
	if (sTK == "N")
	{
		textColor(10);
		cout << "\t\tBan da con thoat!\n";
		textColor(7);
		return;
	}
	list <PhieuMuon>::iterator p = L4.begin();
	cout << "\tDanh Sach Sach Ban Doc Dang Muon\n";
	while(p != L4.end())
	{
		if (sMBD == p->getBanDoc().getMBD() && p->getTrangThai() != 0)
		{
			
			list <Sach>::iterator q = L3.begin();
			while(q != L3.end())
			{
				if (q->getMS() == p->getSach().getMS())
				{
					flag = 1;
					q->outputSach();
				}
				q++;
			}
		}
		else 
		{
			flag = 0;
		}
		p++;
	}
	if (flag == 0)
	{
		textColor(4);
		cout << "\t\tMa ban doc nay chua muon sach!\n";
		textColor(7);
		system("pause");
		goto dd;
	}

}
void traSach_PhieuMuon(list <PhieuMuon> &L4, list <BanDoc*> L2, list <Sach> &L3)
{
	int flag = 0;
	int nMPM = 0;
	while(true)
	{
		dd:
		system("cls");
		cout << "\t\tNhap ma phieu muon can tra sach: "; cin >> nMPM;
		list <PhieuMuon> ::iterator p = L4.begin();
		while(p != L4.end())
		{
			if (nMPM == p->getMaPM())
			{
				if (p->getTrangThai() != 0)
				{
					flag = 1;
					p->setTrangThai(0); // gán trạng thái 0 cho phiếu mượn đang muốn trả
					string sMaSach = p->getSach().getMS();
					list <Sach> ::iterator q = L3.begin();
					while(q != L3.end())
					{
						if (q->getMS() == sMaSach)
						{
							q->setTT(0); // gán tình trạng 0 cho sách đã được trả
							break;
						}
						q++;
					}
					outputData_Sach_File(L3);
					outputData_PhieuMuon_File(L4, L2, L3);
					textColor(10);
					cout << "\t\tTra sach thanh cong!\n";
					textColor(7);
					break;
				}
				textColor(4);
				cout << "\t\tMa phieu muon da duoc tra!\n";
				textColor(7);
				system("pause");
				goto dd;
			}
			p++;
		}
		if (flag == 0)
		{
			textColor(4);
			cout << "\t\tMa phieu muon khong ton tai!\n";
			textColor(7);
			system("pause");
		}
		else if(flag == 1)
		{
			break;
		}
	}
}