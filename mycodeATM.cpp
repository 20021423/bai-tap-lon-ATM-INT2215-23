// ATM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "mylibATM.h"

void menu(ATM ds[], int& n, TienATM& p)
{
	bool kt = true;
	do
	{
		system("cls");
		cout << "1.Dang ky" << endl;
		cout << "2.Dang nhap" << endl;
		cout << "0. Thoat" << endl;
		int choice;
		cout << "Nhap lua chon: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			DangKy(ds, n);
			system("pause");
			break;
		}
		case 2:
		{
			ATM x;
			DocFile(ds, n);
			if (DangNhap(ds, n, x))
			{
				system("pause");
				DocFileTienTrongATM(p);
				LuaChon(x, p, ds, n);
				break;
			}
			system("pause");
			break;
		}
		case 0:
		{
			cout << "\nYou really want to exit this program? \n";
			cout << "1.Yes 2.No\n";
			int lc;
			cin >> lc;
			if (lc == 1)
			{
				cout << "\nCam on quy khach da su dung dich vu cua chung toi!\n";
				kt = false;
				break;
			}
		}
		}
	} while (kt);
}
bool DangKyMatKhau(string s)
{
	int dem1 = 0, dem2 = 0, dem3 = 0;
	if (s.length() < 8) return false;
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] >= 33 && s[i] <= 47) || (s[i] >= 58 && s[i] <= 64) || (s[i] >= 91 && s[i] <= 96) || (s[i] >= 123 && s[i] <= 126))
		{
			dem1++;
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			dem2++;
		}
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		{
			dem3++;
		}
		if (dem1 >= 1 && dem2 >= 1 && dem3 >= 1)
		{
			return true;
		}
	}
	return false;
}
bool DangKyPin(string s)
{
	int n = s.length();
	if (n < 4 || n>6) return false;
	for (int i = 0; i < n; i++)
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			return false;
		}
	}
	return true;
}
void DangKy(ATM ds[], int& n)
{
	DocFile(ds, n);
	cout << "\n=========Chao mung quy khach den voi chuc nang dang ky===========\n";
	cout << "Moi quy khach nhap ID, pass va ma PIN de xac nhan giao dich";
	ATM x;
	int i = 1;
	do
	{
		if (i > 1) cout << "ID da co nguoi su dung moi ban dang ky ID khac!";
		cout << "\nNhap ID: ";
		cin >> x.ID;
		i++;
	} while (CheckID(ds, n, x.ID));
		cout << "\npass (toi thieu co 8 ki tu trong do co it nhat 1 ki tu so, 1 ki tu chu va 1 ki tu dac biet : ";
		string pass2, PIN2;
		do
		{
			cout << "\n1. Hien thi/ 2.An\n";
			int lc;
			do
			{
				cout << "Nhap lua chon: ";
				cin >> lc;
				switch (lc)
				{
				case 1:
				{
					cout << "\nNhap pass: ";
					cin >> x.pass;
					cout << "\nXac nhan lai pass: ";
					cin >> pass2;
					break;
				}
				case 2:
				{
					cout << "\nNhap pass: ";
					x.pass = CheDoNhapAn();
					cout << "\nXac nhan lai pass: ";
					pass2 = CheDoNhapAn();
					break;
				}
				}
			} while (lc != 1 && lc != 2);
		} while (x.pass != pass2 || !DangKyMatKhau(x.pass));
		cout << "\nNhap ma PIN(toi thieu co 4 chu so va toi da la 6 chu so): ";
		do
		{
			cout << "\nNhap pin: ";
			cin >> x.PIN;
			cout << "\nXac nhan lai ma PIN: ";
			cin >> PIN2;
		} while (x.PIN != PIN2 || !DangKyPin(x.PIN));
	cout << "\nQuy khach da dang ky tai khoan thanh cong\n";
	ds[n] = x;
	n++;
	GhiThongTinKhachHang(x);
}
void GhiThongTinKhachHang(ATM x)
{
	ofstream fileout;
	fileout.open("ThongTinKhachHang.txt", ios_base::app);
	fileout << x.ID << "," << x.pass << "," << x.PIN << "," << x.Money << endl;
	fileout.close();
}
bool CheckID(ATM ds[], int n, string id)
{
	for (int i = 0; i < n; i++)
	{
		if (id == ds[i].ID)
		{
			return true;
		}
	}
	return false;
}
int DocFile(ATM ds[], int& n)
{
	n = 0;
	ifstream filein;
	filein.open("ThongTinKhachHang.txt", ios_base::in);
	if (filein.fail()) return 0;
	while (!filein.eof())
	{
		ATM x;
		getline(filein, x.ID, ',');
		getline(filein, x.pass, ',');
		getline(filein, x.PIN, ',');
		double k;
		filein >> k;
		x.Money = k;
		ds[n] = x;
		string s;
		getline(filein, s);
		n++;
	}
	n--;
	filein.close();
	return n;
}
string CheDoNhapAn()
{
	string pass = "";
	char c = _getch();
	while (c != 13) // 13 la phim enter
	{
		if (c != 8)
		{
			pass += c;
			cout << "*";
		}
		else
		{
			pass.pop_back();
			cout << "\b \b";
		}
		c = _getch();
	}
	return pass;
}
bool DangNhap(ATM ds[], int &n, ATM& x)
{
	int i = 0;
	int j = 0;
	do
	{
		system("cls");
		cout << "\n\n=====================Moi quy khach nhap ID, pass===========================\n\n";
		cout << "Nhap ID: ";
		cin >> x.ID;
		cout << "1. Hien thi mat khau \n2. An mat khau\n";
		int lc;
		do{
		cout << "Nhap lc: ";
		cin >> lc;
		} while (lc != 1 && lc != 2);
		switch (lc)
		{
		case 1:
		{
			cout << "\nNhap pass: ";
			cin >> x.pass;
			break;
		}
		case 2:
		{
			cout << "\nNhap pass: ";
			x.pass = CheDoNhapAn();
			break;
		}
		}	
		i++;
		if (i > 5)
		{
			if (i > 7)
			{
				cout << "\nQua 7 lan chung toi se tam khoa tai khoan\nDe mo tai khoan quy khach can lien he voi admin de lam thu tuc mo\n";
				XoaTaikKhoan(ds, n, x);
				GhiLaiDachSachKhachHang(ds, n);
				return false;
			}
			cout << "\nBan da nhap sai id, pass qua 5 lan, chung toi se tam thoi khoa tai khoan trong 30s!\n";
			Sleep(30000);
		}
	} while (!CheckPass(ds, n, x));
	for (int j = 0; j < n; j++)
	{
		if (x.ID == ds[j].ID)
		{
			x = ds[j];
			break;
		}
	}
	cout << "\nQuy khach da dang nhap thanh cong\n";
	return true;
}
bool CheckPass(ATM ds[], int n, ATM x)
{
	for (int i = 0; i < n; ++i)
	{
		if (ds[i].ID == x.ID)
		{
			if (ds[i].pass == x.pass)
			{
				return true;
			}
		}
	}
	cout << "\nMa ID hoac pass khong dung\n";
	return false;
}
void LuaChon(ATM& x, TienATM& n, ATM ds[], int sl)
{
	bool kt = true;
	do
	{
		system("cls");
		cout << "3. Gui tien" << endl;
		cout << "4. Rut tien" << endl;
		cout << "5. Thoat(Dang xuat)" << endl;
		cout << "6. Xem tien trong tai khoan" << endl;
		cout << "7. Xem lich su giao dich" << endl;
		cout << "8. Doi mat khau" << endl;
		cout << "9. Chuyen tien" << endl;
		cout << "10. Chuc nang cua admin" << endl;
		int lc;
		cout << "Nhap lua chon: ";
		cin >> lc;
		switch (lc)
		{
		case 3:
		{
			DocFileTienTrongATM(n);
			GuiTien(x, n, ds, sl);
			system("pause");
			break;
		}
		case 4:
		{
			DocFileTienTrongATM(n);
			RutTien(x, n,ds,sl);
			system("pause");
			break;
		}
		case 5:
		{
			cout << "\nYou really want to exit this program? \n";
			cout << "1.Yes 2.No\n";
			int c;
			cin >> c;
			if (c == 1)
			{
				kt = false;
				break;
			}
		}
		case 6:
		{
			DocTien(x);
			cout << "\nSo tien trong tai khoan cua quy khach la: \n" << x.Money << endl;
			system("pause");
			break;
		}
		case 7:
		{
			DocLichSuGiaoDich(x);
			system("pause");
			break;
		}
		case 8:
		{
			DoiMatKhau(x, ds, sl);
			system("pause");
			break;
		}
		case 9:
		{
			ChuyenTien(x, ds, sl);
			system("pause");
			break;
		}
		case 10:
		{
			if (TaiKhoanAdmin(ds,sl, x))
			{
				ChucNangAdmin(ds, sl, x, n);
				break;
			}
			else
			{
				cout << "\nChuc nang nay danh rieng cho admin. Xin loi quy khach khong the su dung duoc!\n";
				break;
			}
			
		}
		}

	} while (kt);
}
void DocFileTienTrongATM(TienATM& n)
{
	ifstream filein("TienTrongATM.txt");
	if (filein.fail()) return;
	filein >> n.n500k >> n.n200k >> n.n100k >> n.n50k >> n.n20k >> n.n10k;
	filein.close();
}
bool CheckNhapTien(int x)
{
	if (x == 100000 || x == 200000 || x == 500000 || x == 10000 || x == 20000 || x == 50000)
	{
		return true;
	}
	return false;
}
bool CheckPIN(ATM x, string s)
{
	return (s == x.PIN);
}
void DocTien(ATM& x)
{
	ifstream filein;
	filein.open(x.ID + ".txt");
	if (filein.fail()) {
		return;
	}
	filein >> x.Money;
	filein.close();
}
void GhiTien(ATM& x)
{
	ofstream fileout;
	fileout.open(x.ID + ".txt", ios::out);
	fileout << x.Money;
	fileout.close();
}
void GhiLichSuGiaoDich(ATM x, int tien)
{
	ofstream fileout;
	fileout.open("LSGD " + x.ID + ".txt", ios::app);
	time_t now = time(0);
	tm tg;
	localtime_s(&tg, &now);
	fileout << "Thoi gian GD: " << tg.tm_hour << ":" << 1 + tg.tm_min << ":" << 1 + tg.tm_sec;
	fileout << " " << tg.tm_mday << "/" << 1 + tg.tm_mon << "/" << 1900 + tg.tm_year;
	if (tien > 0)
	{
		fileout << "\nSo tien: +" << tien << " VND\n";
		fileout << "Quy khach nap " << tien << "VND vao tai khoan cua minh" << endl;
	}
	if (tien < 0)
	{
		fileout << "\nSo tien: " << tien << " VND\n";
		fileout << "Quy khach rut " << -tien << "VND khoi tai khoan cua minh" << endl;
	}
	fileout.close();
}
ATM GuiTien(ATM& x, TienATM& n, ATM ds[], int sl)
{
	int menhgia;
	do {
		cout << "\nNhap menh gia tien nap (toi thieu la 10.000VND, toi da la 500.000VND): ";
		cin >> menhgia;
	} while (!CheckNhapTien(menhgia));
	cout << "\nNhap so luong to menh gia vua nap: ";
	int soto;
	cin >> soto;
	cout << "\nNhap ma pin de xac nhan co chac chan muon nap tien: \n";
	string pin;
	do
	{
		cout << "Nhap ma pin: ";
		cin >> pin;
	} while (!CheckPIN(x, pin));
	if (menhgia == 500000) n.n500k += soto;
	else if (menhgia == 200000) n.n200k += soto;
	else if (menhgia == 100000) n.n100k += soto;
	else if (menhgia == 50000) n.n50k += soto;
	else if (menhgia == 20000) n.n20k += soto;
	else if (menhgia == 10000) n.n10k += soto;
	GhiTienTrongATM(n);
	DocTien(x);
	x.Money += (menhgia * soto);
	GhiTien(x);
	GhiLichSuGiaoDich(x, menhgia * soto);
	for (int i = 0; i < sl; i++)
	{
		if (ds[i].ID == x.ID)
		{
			ds[i] = x;
		}
	}
	GhiLaiDachSachKhachHang(ds, sl);
	cout << "\nQuy khach da thanh cong nap " << menhgia * soto << " vao tai khoan cua minh\n";
	return x;
}
void GhiTienTrongATM(TienATM& n)
{
	ofstream fileout;
	fileout.open("TienTrongATM.txt", ios_base::out);
	fileout << n.n500k << " " << n.n200k << " " << n.n100k << " " << n.n50k << " " << n.n20k << " " << n.n10k;
	fileout.close();
}
bool RutTien(ATM& x, TienATM& n, ATM ds[], int sl)
{
	int tien;
	cout << "Nhap so tien muon rut: ";
	cin >> tien;
	int tien2 = tien;
	DocTien(x);
	DocFileTienTrongATM(n);
	if (tien > x.Money)
	{
		cout << "\nTai khoan cua ban khong du tien de rut\n";
		return false;
	}
	cout << "\nNhap ma pin de xac nhan co chac chan muon rut tien: \n";
	string pin;
	do
	{
		cout << "Nhap ma pin: ";
		cin >> pin;
	} while (!CheckPIN(x, pin));
	int t500 = 0, t200 = 0, t100 = 0, t50 = 0, t20 = 0, t10 = 0;
	if (tien >= 500000)
		while (tien >= 500000 && t500 < n.n500k)
		{
			tien -= 500000;
			t500++;
		}
	if (tien >= 200000)
		while (t200 < n.n200k && tien >= 200000)
		{
			tien -= 200000;
			t200++;
		}
	if (tien >= 100000)
		while (t100 < n.n100k && tien >= 100000)
		{
			tien -= 100000;
			t100++;
		}
	if (tien >= 50000)
		while (t50 < n.n50k && tien >= 50000)
		{
			tien -= 50000;
			t50++;
		}
	if (tien >= 20000)
		while (t20 < n.n20k && tien >= 20000)
		{
			tien -= 20000;
			t20++;
		}
	if (tien >= 10000)
		while (t10 < n.n10k && tien >= 10000)
		{
			tien -= 10000;
			t10++;
		}
	if (tien == 0)
	{
		cout << "Ban da rut thanh cong " << tien2 << endl;
		GhiLichSuGiaoDich(x, -tien2);
		x.Money -= tien2;
		n.n500k -= t500;
		n.n200k -= t200;
		n.n100k -= t100;
		n.n50k -= t50;
		n.n20k -= t20;
		n.n10k -= t10;
		cout << "cu the la rut duoc ";
		if (t500 != 0) cout << t500 << " to 500k ";
		if (t200 != 0) cout << t200 << " to 200k ";
		if (t100 != 0) cout << t100 << " to 100k ";
		if (t50 != 0) cout << t50 << " to 50k ";
		if (t20 != 0) cout << t20 << " to 20k ";
		if (t10 != 0) cout << t10 << " to 10k";
		cout << endl;
		GhiTien(x);
		GhiTienTrongATM(n);
		for (int i = 0; i < sl; i++)
		{
			if (ds[i].ID == x.ID)
			{
				ds[i] = x;
				break;
			}
		}
		GhiLaiDachSachKhachHang(ds, sl);
		return true;
	}
	else
	{
		cout << "\nXin loi quy khach, hien tai may ATM khong du luong tien cung cap cho quy khach rut so tien nay\n";
		return false;
	}
}
void DocLichSuGiaoDich(ATM x)
{
	ifstream filein;
	filein.open("LSGD " + x.ID + ".txt", ios::in);
	if (filein.fail())
	{
		cout << "\nChua co lich su giao dich\n";
		return;
	}
	while (!filein.eof())
	{
		string s;
		getline(filein, s);
		cout << s << endl;
	}
	filein.close();
}
void DoiMatKhau(ATM& x, ATM ds[], int n)
{
	DocFile(ds, n);
	cout << "Chao mung den voi chuc nang doi mat khau!\n";
	do {
		cout << "1. Hien thi/ 2.An\n";
		int lc;
		cout << "Nhap lua chon: ";
		cin >> lc;
		cout << "\nNhap mat khau cu: ";
		switch (lc)
		{
		case 1:
		{
			cin >> x.pass;
			break;
		}
		case 2:
		{
			x.pass = CheDoNhapAn();
			break;
		}
		}
	} while (!CheckPass(ds, n, x));
	string pass1, pass2;
	do
	{
		cout << "\nNhap mat khau noi khac voi mat khau cu va tuan thu nguyen tac dat mat khau\n(toi thieu 8 ki tu trong do co it nhat 1 ki tu so, 1 ki tu chu cai va 1 ki tu dac biet)\n";
		cout << "1. Hien thi/ 2.An\n";
		int lc;
		cout << "Nhap lua chon: ";
		cin >> lc;
		switch (lc)
		{
		case 1:
		{
			cout << "\nNhap pass moi: ";
			cin >> pass1;
			cout << "\nXac nhan lai pass: ";
			cin >> pass2;
			break;
		}
		case 2:
		{
			cout << "\nNhap pass moi: ";
			pass1 = CheDoNhapAn();
			cout << "\nXac nhan lai pass: ";
			pass2 = CheDoNhapAn();
			break;
		}
		}
	} while (pass1 != pass2 || pass1==x.pass || !DangKyMatKhau(pass1));
	for (int i = 0; i < n; i++)
	{
		if (ds[i].ID == x.ID)
		{
			ds[i].pass = pass2;
		}
	}
	GhiLaiDachSachKhachHang(ds, n);
	cout << "\nQuy khach da thay doi mat khau thanh cong!\n";
}
void GhiLaiDachSachKhachHang(ATM ds[], int n)
{
	ofstream fileout;
	fileout.open("ThongTinKhachHang.txt", ios_base::out);
	for (int i = 0; i < n; i++)
	{
		fileout << ds[i].ID << "," << ds[i].pass << "," << ds[i].PIN << "," << ds[i].Money << endl;
	}
	fileout.close();
}
void ChuyenTien(ATM& x, ATM ds[], int sl)
{
	DocTien(x);
	ATM y;
	int i = 0;
	do
	{
		if(i==0) cout << "Nhap so ID ban muon chuyen: ";
		if (i > 0) cout << "ID nay khong ton tai hoac ID nay la tai khoan cua chinh ban! Moi quy khach nhap lai: ";
		cin >> y.ID;
		i++;
	} while (!CheckID(ds, sl, y.ID) || y.ID==x.ID);
	for (int i = 0; i < sl; i++)
	{
		if (ds[i].ID == y.ID)
		{
			y = ds[i];
		}
	}
	DocTien(y);
	i = 0;
	double money=0;
	bool kt = true;
	do
	{
		if(i==0)
		cout << "Nhap so tien muon chuyen: ";
		if (i > 0)
		{
			if(money>10000)
			cout << "Tai khoan cua quy khach khong du tien de chuyen so tien nay. Moi quy khach nhap lai so tien!\n";
			cout << "Nhap : ";
		}
		cin >> money;
		cout << "\nChon hinh thuc chuyen phi dich vu\n1.Nguoi gui / 2.Nguoi nhan\n";
		int lc;
		cin >> lc;
		switch (lc )
		{
		case 1:
		{
			money += 10000;
			break;
		}
		case 2:
		{
			kt = false;
			break;
		}
		}
		i++;
	} while (money > x.Money || money <= 10000);
	if (kt)
	{
		x.Money -= money;
		GhiLichSuGiaoDichChoChuyenTien(x, y, -money);
		money -= 10000;
		y.Money += money;
		GhiLichSuGiaoDichChoChuyenTien(x, y, money);
	}
	else
	{
		x.Money -= money;
		GhiLichSuGiaoDichChoChuyenTien(x, y, -money);
		money -= 10000;
		y.Money = y.Money + money;
		GhiLichSuGiaoDichChoChuyenTien(x, y, money);
	}
	for (int i = 0; i < sl; i++)
	{
		if (ds[i].ID == x.ID)
		{
			ds[i] = x;
		}
		if (ds[i].ID == y.ID)
		{
			ds[i] = y;
		}
	}
	GhiLaiDachSachKhachHang(ds, sl);
	GhiTien(x);
	GhiTien(y);
	cout << "\nQuy khach da chuyen tien thanh cong!\n";
}
void GhiLichSuGiaoDichChoChuyenTien(ATM x, ATM y, double money)
{
	if (money < 0)
	{
		ofstream fileout;
		fileout.open("LSGD " + x.ID + ".txt", ios::app);
		time_t now = time(0);
		tm tg;
		localtime_s(&tg, &now);
		fileout << "Thoi gian GD: " << tg.tm_hour << ":" << 1 + tg.tm_min << ":" << 1 + tg.tm_sec;
		fileout << " " << tg.tm_mday << "/" << 1 + tg.tm_mon << "/" << 1900 + tg.tm_year;
		fileout << "\nSo tien: " << money << "VND\n";
		fileout << "Quy khach vua chuyen " << -money << " vao tai khoan co so ID " << y.ID << " phi dich vu 10000" << endl;
		fileout.close();
	}
	if (money > 0)
	{
		ofstream fileout;
		time_t now = time(0);
		tm tg;
		localtime_s(&tg, &now);
		fileout.open("LSGD " + y.ID + ".txt", ios::app);
		fileout << "Thoi gian GD: " << tg.tm_hour << ":" << 1 + tg.tm_min << ":" << 1 + tg.tm_sec;
		fileout << " " << tg.tm_mday << "/" << 1 + tg.tm_mon << "/" << 1900 + tg.tm_year;
		fileout << "\nSo tien: " << "+ " << money << "VND\n";
		fileout << "Quy khach vua nhan duoc " << money << " tu tai khoan co so ID " << x.ID << " phi dich vu 10000" << endl;
		fileout.close();
	}
}
void XoaTaikKhoan(ATM ds[], int& n, ATM x)
{
	int index = -1;
	for (int i = 0; i < n; i++)
	{
		if (ds[i].ID == x.ID)
		{
			ds[i] = x;
			x = ds[i];
			index = i;
		}
	}
	DocTien(x);
	GhiTien(x);
	if (index >= 0)
	{
		for (int i = index; i < n; i++)
		{
			ds[i] = ds[i + 1];
		}
		n--;
	}
}
bool TaiKhoanAdmin(ATM ds[], int n, ATM& ad)
{
	ifstream filein;
	filein.open("TaiKhoanAdmin.txt", ios::in);
	if (filein.fail())
	{
		cout << "Khong mo dc file";
		return false;
	}
	ATM admin[MAX];
	int j = 0;
	while (!filein.eof())
	{
		ATM x;
		getline(filein, x.ID);
		admin[j] = x;
		j++;
	}
	filein.close();
	for (int i = 0; i < j; i++)
	{
		if (ad.ID == admin[i].ID)
		{
			ad = admin[i];
			return true;
		}
	}
	return false;
}
void ChucNangAdmin(ATM ds[], int n, ATM& x, TienATM &p)
{
	bool kt = true;
	do
	{
		system("cls");
		cout << "1. Mo khoa tai khoan" << endl;
		cout << "2. Xem cu the trong may ATM co bao nhieu tien" << endl;
		cout << "3. Xem lich su giao dich cua 1 ID bat ki" << endl;
		cout << "4. Xem danh sach cac tai khoan hien co" << endl;
		cout << "5. Them tien cho ATM" << endl;
		cout << "6. Dang ky tai khoan moi" << endl;
		cout << "0. Thoat" << endl;
		int lc;
		cout << "Nhap lc: ";
		cin >> lc;
		switch (lc)
		{
		case 1:
		{
			MoTaiKhoan(ds, n);
			system("pause");
			break;
		}
		case 0:
		{
			kt = false;
			break;
		}
		case 2:
		{
			DocFileTienTrongATM(p);
			cout << "Trong ATM co: " << endl;
			cout << p.n500k << " to 500k" << endl;
			cout << p.n200k<< " to 200k" << endl;
			cout << p.n100k << " to 100k" << endl;
			cout << p.n50k << " to 50k" << endl;
			cout << p.n20k << " to 20k" << endl;
			cout << p.n10k << " to 10k" << endl;
			system("pause");
			break;
		}
		case 3:
		{
			XemLichSuGiaoDichCuaIDBatKi(ds, n);
			system("pause");
			break;
		}
		case 4:
		{
			XemDanhSachCacTaiKhoan(ds, n);
			system("pause");
			break;
		}
		case 5:
		{
			ThemTienChoATM(p);
			system("pause");
			break;
		}
		case 6:
		{
			DangKy(ds, n);
			system("pause");
			break;
		}
		}
	} while (kt);
}
bool CheckTaiKhoanBiKhoa(ATM x)
{
	ifstream filein;
	filein.open(x.ID + ".txt", ios::in);
	if (filein.fail()) return false;
	filein.close();
	return true;
}
void MoTaiKhoan(ATM ds[], int& n)
{
	DocFile(ds, n);
	ATM x;
	int i = 1;
	do
	{
		if (i > 4)
		{
			cout << "Bam 0 de thoat chuc nang nay!\nBam bat ki de tiep tuc!\n";
			string lc;
			cin >> lc;
			if (lc == "0")
			{
				return;
			}
		}
		if (i > 1) cout << "\nDa nhap sai ID hoac ID chua tung dang ky\n";
		cout << "\nNhap ID: ";
		cin >> x.ID;
		i++;
	} while (CheckID(ds, n, x.ID) || !CheckTaiKhoanBiKhoa(x));
	cout << "\npass (toi thieu co 8 ki tu trong do co it nhat 1 ki tu so, 1 ki tu chu va 1 ki tu dac biet : ";
	string pass2, PIN2;
	do
	{
		cout << "\n1. Hien thi/ 2.An\n";
		int lc;
		do
		{
			cout << "Nhap lua chon: ";
			cin >> lc;
			switch (lc)
			{
			case 1:
			{
				cout << "\nNhap pass: ";
				cin >> x.pass;
				cout << "\nXac nhan lai pass: ";
				cin >> pass2;
				break;
			}
			case 2:
			{
				cout << "\nNhap pass: ";
				x.pass = CheDoNhapAn();
				cout << "\nXac nhan lai pass: ";
				pass2 = CheDoNhapAn();
				break;
			}
			}
		} while(lc!=1 && lc!=2);
	} while (x.pass != pass2 || !DangKyMatKhau(x.pass));
	cout << "\nNhap ma PIN(toi thieu co 4 chu so va toi da la 6 chu so): ";
	do
	{
		cout << "\nNhap pin: ";
		cin >> x.PIN;
		cout << "\nXac nhan lai ma PIN: ";
		cin >> PIN2;
	} while (x.PIN != PIN2 || !DangKyPin(x.PIN));
	cout << "\nda mo khoa thanh cong\n";
	DocTien(x);
	ds[n] = x;
	n++;
	GhiThongTinKhachHang(x);
}
void XemLichSuGiaoDichCuaIDBatKi(ATM ds[], int n)
{
	ATM x;
	int i = 0;
	do
	{
		if (i > 4)
		{
			cout << "\nBam 0 de thoat khoi chuc nang nay!\n";
			cin >> x.ID;
			if (x.ID == "0")
			{
				return;
			}
		}
		cout << "\nNhap ID ban muon xem lich su giao dich: ";
		cin >> x.ID;
		i++;
	} while (!CheckID(ds, n, x.ID));
	cout << endl;
	DocLichSuGiaoDich(x);
}

void XemDanhSachCacTaiKhoan(ATM ds[], int n)
{
	string s;
	int i = 0;
	cout << "Muon xem het thong tin ID, mat khau, ma pin, so tien du can phai co ma sieu dac biet!\n";
	do
	{
		if (i > 5)
		{
			cout << "Ban da nhap sai qua 5 lan ma dac biet, ban chi co the xem ID duoc thoi!\n";
			cout << "Danh sach ID cac tai khoan la: \n";
			for (int i = 0; i < n; i++)
			{
				cout << ds[i].ID << endl;
			}
			return;
		}
		cout << "Nhap ma sieu dac biet: ";
		cin >> s;
		i++;
	} while (s != "kuetto@110705");
	cout << "ID / pass / ma pin / so tien \n";
	for (int i = 0; i < n; i++)
	{
		cout << ds[i].ID << " " << ds[i].pass << " " << ds[i].PIN << " " << ds[i].Money << endl;
	}
}
void ThemTienChoATM(TienATM& n)
{
	int t500, t200, t100, t50, t20, t10;
	cout << "\nNhap so to 500k: "; cin >> t500;
	cout << "\nNhap so to 200k: "; cin >> t200;
	cout << "\nNhap so to 100k: "; cin >> t100;
	cout << "\nNhap so to 50k: "; cin >> t50;
	cout << "\nNhap so to 20k: "; cin >> t20;
	cout << "\nNhap so to 10k: "; cin >> t10;
	n.n500k += t500;
	n.n200k += t200;
	n.n100k += t100;
	n.n50k += t50;
	n.n20k += t20;
	n.n10k += t10;
	GhiTienTrongATM(n);
	cout << "\nDa them thanh cong!\n";
}