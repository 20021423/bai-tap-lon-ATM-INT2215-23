#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#define MAX 100

using namespace std;

struct ATM
{
	string ID;
	string pass;
	string PIN;
	double Money = 0;
};
struct TienATM
{
	int n10k = 0;
	int n20k = 0;
	int n50k = 0;
	int n100k = 0;
	int n200k = 0;
	int n500k = 0;
};
void menu(ATM ds[], int& n, TienATM& p);
bool DangKyMatKhau(string s);
bool DangKyPin(string s);
void DangKy(ATM ds[], int& n);
bool CheckID(ATM ds[], int n, string id);
int DocFile(ATM ds[], int& n);
void GhiThongTinKhachHang(ATM x);
bool DangNhap(ATM ds[], int n, ATM& x);
bool CheckPass(ATM ds[], int n, ATM x);
void LuaChon(ATM& x, TienATM& n, ATM ds[], int sl);
void DocFileTienTrongATM(TienATM& n);
ATM GuiTien(ATM& x, TienATM& n, ATM ds[], int sl);
bool CheckNhapTien(int x);
bool CheckPIN(ATM x, string s);
void DocTien(ATM& x);
void GhiTien(ATM& x);
void GhiLichSuGiaoDich(ATM x, int tien);
void GhiTienTrongATM(TienATM& n);
bool RutTien(ATM& x, TienATM& n, ATM ds[], int sl);
void DocLichSuGiaoDich(ATM x);
void DoiMatKhau(ATM& x, ATM ds[], int n);
void GhiLaiDachSachKhachHang(ATM ds[], int n);
void ChuyenTien(ATM& X, ATM ds[], int sl);
void GhiLichSuGiaoDichChoChuyenTien(ATM x, ATM y, double money);
string CheDoNhapAn();