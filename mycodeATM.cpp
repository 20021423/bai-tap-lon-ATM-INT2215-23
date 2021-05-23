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
void DangKy(ATM ds[], int& n)
{
	DocFile(ds, n);
	cout << "\n=========Chao mung quy khach den voi chuc nang dang ky===========\n";
	cout << "Moi quy khach nhap ID, pass va ma PIN de xac nhan giao dich";
	ATM x;
	int i = 1;
	cout << endl << n << endl;
	do
	{
		if (i > 1) cout << "ID da co nguoi su dung moi ban dang ky ID khac!";
		cout << "\nNhap ID: ";
		cin >> x.ID;
		cout << "\nNhap pass: ";
		cin >> x.pass;
		cout << "\nNhap ma PIN: ";
		cin >> x.PIN;
		cout << "\nXac nhan lai pass va ma PIN";
		string pass2, PIN2;
		do
		{
			cout << "\nXac nhan lai pass: ";
			cin >> pass2;
		} while (x.pass != pass2);
		do
		{
			cout << "\nXac nhan lai ma PIN: ";
			cin >> PIN2;
		} while (x.PIN != PIN2);
		i++;
	} while (CheckID(ds, n, x.ID));
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
bool DangNhap(ATM ds[], int n, ATM& x)
{
	cout << "\nMoi quy khach nhap ID, pass: \n";
	int i = 0;
	do
	{
		cout << "Nhap ID: ";
		cin >> x.ID;
		cout << "\nNhap pass: ";
		cin >> x.pass;
		i++;
		if (i > 5)
		{
			cout << "\nBan da nhap sai id, pass qua 5 lan, chung toi se tam thoi khoa tai khoan trong 30s!\n";
			Sleep(30000);
			return false;
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
		int lc;
		cout << "Nhap lua chon: ";
		cin >> lc;
		switch (lc)
		{
		case 3:
		{
			DocFileTienTrongATM(n);
			GuiTien(x, n);
			system("pause");
			break;
		}
		case 4:
		{
			DocFileTienTrongATM(n);
			RutTien(x, n);
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
		fileout << "\nSo tien: +" << tien << " VND\n";
	if (tien < 0)
		fileout << "\nSo tien: " << tien << " VND\n";
	fileout.close();
}
ATM GuiTien(ATM& x, TienATM& n)
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
bool RutTien(ATM& x, TienATM& n)
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
		cout << "Chua co lich su giao dich";
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
		cout << "Nhap mat khau cu: ";
		cin >> x.pass;
	} while (!CheckPass(ds, n, x));
	string pass1, pass2;
	do
	{
		cout << "Nhap pass moi: ";
		cin >> pass1;
		cout << "Xac nhan lai pass: ";
		cin >> pass2;
	} while (pass1 != pass2);
	for (int i = 0; i < n; i++)
	{
		if (ds[i].ID == x.ID)
		{
			ds[i].pass = pass2;
		}
	}
	GhiLaiDachSachKhachHang(ds, n);
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