#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "Lib.h"
#include <windows.h>
#include "md5.h"
#include <fstream> // lam viec voi file
#include <algorithm> 
#include <vector>
#include <iomanip>
#include <sstream>
#include <exception> //thu vien ngoai le
using namespace std;
// Struct ngay thang
// Su dung esc de thoat ra
struct date
{
	int ngay;
	int thang;
	int nam;
};
// Khai bao sinh vien voi malop, ma sv, ho ten, thoi gian va diem tb
typedef struct sinhvien
{
	char malop[10];
	int masv;
	char hoten[26];
	date tg;
	float diemtb;
} sv;
struct node
{
	sv data;
	struct node *next;
};
typedef struct list
{
	node *dau;
	node *cuoi;
};
// khoi tao danh sach
void initList(list &l)
{
	l.dau = l.cuoi = NULL;
};
// Khai bao nguyen mau ham
node *taoNode();
char filename[20];
// Cho nay la nhap lieu
int nhapmasv(int x,int y);
string nhapTen(int x,int y);
int nhapNgaySinh(int x,int y);
int nhapThangSinh(int x,int y);
int nhapNamSinh(int x,int y);
void xuLyThoiGian(date *p);
string nhapMaLop(int x,int y);
float nhapDiem(int x,int y);
// Doc ghi file
void docfile(list &l);
void luufile(list &l);
// Sap xep
void sapxepchon(list &l,int n);
void sapxepchen(list &l,int n);
void sapxepnoibot(list &l,int n);
void quicksort(list &l,int n);
void Mergersort(list &l, int n);
void hoanvi(sv *p,sv *q);
// Tim kiem
void tktuantu(list l);
void tknhiphan(list l,int n);
// Them sua xoa sv
void themcuoi(list &l,node *p);
void suaSV(list &l,sv *q);
void xoasv(list &l);
// Thong ke
void thongKe(list l,int n);
// Ham phuc vu
int demsv();
char* tachCuoi(char a[]);
const char* tachDau(char a[]);
char* layDau(char a[]);
void xoakitu( char *xau,int vitri , int soluong);
void menu(list &);
void inDS(list l);
bool readFileMD5(string &strmd5)
{
	ifstream fileIn;
	string nameFile = "D:/md5dssv.txt";
	fileIn.open(nameFile.c_str(), ios_base::in);
	if (fileIn.fail() == true)
	{
		cout << "File md5 khong ton tai" << endl;
		return false;
	}
	else
	{
		while (fileIn.eof() == false)
		{
			fileIn >> strmd5;
		}
	}
	fileIn.close();
	return true;
}
int main()
{	
	system("color 37");
	SetConsoleTitle("Quan ly sinh vien - Do Huu Khang - CNTTK60");
	FILE *f;
	do
	{
		cout<<"Nhap ten file: ";
		cin.getline(filename,20);
		if ((f=fopen(filename,"rb")) == NULL)
		cout<<"Khong tim thay file, vui long nhap lai ten"<<endl;
	} while(f == NULL);
	system("cls");
	fclose(f);
	list l;
	initList(l);
	MD5 md5;	
	//doc file md5file dssv
	string md5Data;
	if (readFileMD5(md5Data) == true)
	{
		//tinh toan md5 file du lieu
		char* nameFileOut = filename;
		string md5FileOut = md5.digestFile(nameFileOut);
		if (md5FileOut.compare(md5Data) == 0) // so sanh file md5
		{
			//Doc du lieu tu file vao chuong trinh
			docfile(l);
		}
		else
		{
			SetColor(12);
			cout << "Du lieu co the da bi thay doi hoac khong tin cay, khong doc file du lieu .!!";
			cout << "\nNhan phim bat ki de tiep tuc chuong trinh." << endl;
			system("pause");
		}
	}
	giaodien();	
	menu(l);	
	//tao md5 file
	char* nameFileOut = filename;
	string md5FileOut = md5.digestFile(nameFileOut);
	//ghi md5file to file de luu tru
	ofstream fileOut;
	string nameFile = "D:/md5dssv.txt"; // file so sanh md5
	fileOut.open(nameFile.c_str(), ios_base::out);
	fileOut << md5FileOut;
	fileOut.close();
	cout << "\n\t\t\t\t\tGhi md5 file thanh cong" << endl;
	luufile(l);	
}

void menu(list &l)
{
	keBang(10,15,30,10); // Dinh hinh bang o vi tri 10, 15 va kich thuoc 22 x 10
	char *tenmuc[] = {"Hoc sinh moi","In thong tin","Sap Xep","Tim","Thong ke","Xoa","Chinh sua","Thoat"};
	char *sapxep[] = {"Sap xep chon","Sap xep chen","Sap Xep noi bot","Sap xep nhanh"};
	char *mucsx[] = {"Ma hoc sinh","Ten","Ngay sinh","Diem"};
	char *tKe[] = {"Xep loai","Cung lop","Giong ten","Giong ho"};
	char *tkiem[] = {"Tim","Ma hoc sinh","Ma lop","Ngay sinh","Diem"};
	for (int i = 1; i < 8; i++)
	{
		gotoxy(15,16+i);
		SetColor(4);
		printf(tenmuc[i]);
	}
	gotoxy(13,16);
	SetColor(12);
	printf("%c %s %c",16,tenmuc[0],17);
	int stt = 0;
	char ch;
	while(1)
	{
		ch = getch();
		switch(ch)
    	{
			case 72: // Phim mui ten len
			stt--;
			if(stt<0) // Khi an mui ten len so thu tu chay tu duoi len
			{
				stt = 7;
				gotoxy(13,16);
				SetColor(4);
				printf("  %s  ",tenmuc[0]);
				gotoxy(13, 16+7);
				SetColor(12);
				printf("%c %s %c",16,tenmuc[7],17);
			}
			else 
			{
				gotoxy(13, 16 + stt + 1);
				SetColor(4);
				printf("  %s  ",tenmuc[stt+1]);
				gotoxy(13,16+stt);
				SetColor(12);
				printf("%c %s %c", 16, tenmuc[stt], 17);	
			}
			break;
			case 80: // Mui ten xuong duoi
			stt++;
			if(stt > 7)
			{
				stt = 0;
				gotoxy(13,16 + 7);
				SetColor(4);	
				printf("  %s  ",tenmuc[stt+7]);
				gotoxy(13, 16);
				SetColor(12);
				printf("%c %s %c",16,tenmuc[stt],17);	
			}
			else
			{
				gotoxy(13,16 + stt - 1);
				SetColor(4);
				printf("  %s  ",tenmuc[stt-1]);
				gotoxy(13,16+stt);
				SetColor(12);
				printf("%c %s %c",16,tenmuc[stt],17);					
			}
			break;					
			case 13: // Enter key
				docfile(l); 
				node *p;
				p = taoNode();
			if(stt == 0) // Them moi sinh vien vao danh sach
			{	
				char ten[26];
				int position = 0;
				int masv;
				float diemtb;
				date time;
				string Name;
				string mlop;
				keBang(34,15,50,20);
				gotoxy(36,17);
				SetColor(13);
				cout<<"Ho ten ";
				keBang(49,16,30,2);
				gotoxy(50,17); // con tro len 1 don vi cho vua bang
				SetColor(6);
				Name = nhapTen(50,17);
				gotoxy(36,20);	// quay con tro ve vi tri de in tieu de ma sv
				SetColor(13);	//mau chu ma sinh vien mau hong
				cout<<"Ma sinh vien";
				keBang(49,19,9,2);
				SetColor(15);
				cout<< "(Ma sinh vien gom 8 so)";
				SetColor(6);
				masv = nhapmasv(50,20); // nhap ma sinh vien vao bang,lay gia tri ma ham return vao bien masv
				gotoxy(36,23);
				SetColor(13);
				cout<<"Ma lop";
				keBang(49,22,11,2);
				gotoxy(50,23);
				SetColor(6);
				mlop = nhapMaLop(50,23);
				gotoxy(36,26);
				SetColor(13);
				cout<<"Ngay";
				keBang(49,25,3,2);
				time.ngay = nhapNgaySinh(50,26);
				gotoxy(54,26);
				SetColor(13);
				cout<<"Thang";
				keBang(60,25,3,2);
				time.thang = nhapThangSinh(61,26);
				gotoxy(66,26);
				SetColor(13);
				cout<<"Nam";
				keBang(70,25,5,2);
				time.nam = nhapNamSinh(71,26);
				xuLyThoiGian(&time);
				SetColor(13);
				gotoxy(36,29);
				cout<<"Diem TLTB";
				keBang(49,28,5,2);
				diemtb = nhapDiem(50,29);
				gotoxy(25,37);
				cout<<"\t\tNhap ESC de thoat viec nhap sinh vien";
				gotoxy(50,17);
				while(1)
				{	
					ch = getch();
					switch(ch)
					{
						case 72:
						if(position == 0)
						{
							gotoxy(50,29);
							position = 6;											
						}
						else 
						{
							if(position == 4)
							{
								gotoxy(50,26);
								position = 3;
							}
							else if(position == 5)
							{
								gotoxy(61,26);
								position = 4;
							}
							else if(position == 6)
							{
								gotoxy(71,26);
								position = 5;
							}
							else if(position == 3)
							{		
								gotoxy(50,23);
								position = 2;
							}
							else if(position == 2)
							{
								gotoxy(50,20);
								position = 1;
							}
							else if(position == 1)
							{
								gotoxy(50,17);
								position = 0;
							}
						}	
						break;
						case 80:
						if(position == 6)
						{
							gotoxy(50,17);
							position = 0;
						}
						else if(position == 5)
						{
							gotoxy(50,29);
							position = 6;				
						}
						else if(position == 4)
						{
							gotoxy(71,26);
							position = 5;
						}
						else if(position == 3)
						{
							gotoxy(61,26);
							position = 4;
						}
						else if(position == 2)
						{
							gotoxy(50,26);
							position = 3;
						}
						else if(position == 1)
						{
							gotoxy(50,23);
							position = 2;
						}
						else
						{
							gotoxy(50,20);
							position = 1;
						}
						break;
						case 13:
						if(position == 0)
						{
							Name = nhapTen(50,17);					
						}
						else if(position == 1)
						{
							masv = nhapmasv(50,20);						
						}
						else if(position == 2)
						{
							mlop = nhapMaLop(50,23);				
						}
						else if(position == 3)
						{
							time.ngay = nhapNgaySinh(50,26);
							xuLyThoiGian(&time);				
						}
						else if(position == 4)
						{
							time.thang = nhapThangSinh(61,26);
							xuLyThoiGian(&time);	
						}	
						else if(position == 5)
						{
							time.nam = nhapNamSinh(71,26);
							xuLyThoiGian(&time);	
						}
						else if(position == 6)
						{
							diemtb = nhapDiem(50,29);
						}
						break;		
					}
					if(ch == 27) // esc
					{
						const char* kiki = mlop.c_str();
						const char * kaka = Name.c_str();
						strcpy(p->data.hoten,kaka);
						strcpy(p->data.malop,kiki);
						p->data.masv = masv;
						p->data.tg.ngay = time.ngay;
						p->data.tg.thang = time.thang;
						p->data.tg.nam = time.nam;
						p->data.diemtb = diemtb;
						themcuoi(l,p);
						luufile(l);
						veLaiKhung();
						break;
					}
					}
				}
				else if(stt == 1)
				{
					char ktu;
					inDS(l);
					while(1)
					{
						ktu = getch();
						if(ktu == 27) break;
					}
					veLaiKhung();
					stt = 0;
					break;
				}
				else if(stt == 2)// sap xep
				{					
					int dem = 0,count = 0;
					char ktu,nhap;
				    nhapnhay();
					for(int i = 1; i < 4; ++i)
			 	    { 
						gotoxy(15,16+i);
						SetColor(4);
						printf(sapxep[i]);
			    	} 
			    	gotoxy(13,16);
					SetColor(12);
					printf("%c %s %c",16,sapxep[0],17);
					while(1)
					{
						ktu = getch();
						switch(ktu)
						{
							case 72:
								dem--;
								if(dem<0)
								{
									dem = 3;
									gotoxy(13,16);
									SetColor(4);
									printf("  %s  ",sapxep[0]);
									gotoxy(13,16+3);
									SetColor(12);
									printf("%c %s %c",16,sapxep[3],17);
								}
								else
								{
									gotoxy(13,16+dem+1);
									SetColor(4);
									printf("  %s  ",sapxep[dem+1]);
									gotoxy(13,16+dem);
									SetColor(12);
									printf("%c %s %c",16,sapxep[dem],17);
								}
								break;
							case 80:
								dem++;
								if(dem > 3)
							 	{
									dem = 0;
									gotoxy(13,16+3);
									SetColor(4);
									printf("  %s  ",sapxep[dem+3]);
									gotoxy(13,16);
									SetColor(12);
									printf("%c %s %c",16,sapxep[dem],17);
								}
								else
								{
									gotoxy(13,16+dem-1);
									SetColor(4);
									printf("  %s  ",sapxep[dem-1]);
									gotoxy(13,16+dem);
									SetColor(12);
									printf("%c %s %c",16,sapxep[dem],17);
								}
								break;
							case 13: // an enter vao muc sap xep
									nhapnhay();
									for(int i = 1;i<4;++i)
			 	  					{ 
										gotoxy(15,16+i);
										SetColor(4);
										printf(mucsx[i]);
			    				    } 
			    					 	gotoxy(13,16);
										SetColor(12);
										printf("%c %s %c",16,mucsx[0],17);
									while(1)
									{
										nhap = getch();
										switch(nhap)
										{
											case 72:							
												count--;
												if(count<0)
												{
													count = 3;
													gotoxy(13,16);
													SetColor(4);
													printf("  %s  ",mucsx[0]);
													gotoxy(13,16+3);
													SetColor(12);
													printf("%c %s %c",16,mucsx[3],17);
												}
												else
												{
													gotoxy(13,16+count+1);
													SetColor(4);
													printf("  %s  ",mucsx[count+1]);
													gotoxy(13,16+count);
													SetColor(12);
													printf("%c %s %c",16,mucsx[count],17);
												}
													break;
											case 80:
												count++;
												if(count > 3)
												{
													count = 0;
													gotoxy(13,16+3);
													SetColor(4);
													printf("  %s  ",mucsx[count+3]);
													gotoxy(13,16);
													SetColor(12);
													printf("%c %s %c",16,mucsx[count],17);
												}
												else
												{
													gotoxy(13,16+count-1);
													SetColor(4);
													printf("  %s  ",mucsx[count-1]);
													gotoxy(13,16+count);
													SetColor(12);
													printf("%c %s %c",16,mucsx[count],17);
												}
												break;
											case 13: // an enter 
												switch(dem)
												{
													case 0:
														if(count == 0)
															sapxepchon(l,1);
														else if(count == 1)
															sapxepchon(l,2);
														else if(count == 2)
															sapxepchon(l,3);
														else if(count == 3)
															sapxepchon(l,4);
														break;
													case 1:
														if(count == 0)
														sapxepchen(l,1);
														else if(count == 1)
														sapxepchen(l,2);			
														else if(count == 2)
														sapxepchen(l,3);
														else if(count == 3)
														sapxepchen(l,4);
														break;
													case 2:
														if(count == 0)
														sapxepnoibot(l,1);
														else if(count == 1)
														sapxepnoibot(l,2);
														else if(count == 2)
														sapxepnoibot(l,3);
														else if(count == 3)
														sapxepnoibot(l,4);
														break;
													
													case 3:
														if(count == 0)
														quicksort(l,1);
														else if(count == 1)
														quicksort(l,2);
														else if(count == 2)
														quicksort(l,3);
														else if(count == 3)
														quicksort(l,4);
														inDS(l);
														break;
												}
												break;
										}
										if(nhap == 13)
										{
											while(1)
											{
												nhap = getch();
												if(nhap == 27)
												break;
											}
											break;
										}																						
									}
								break;	
						}
						if(ktu == 13)
						{
							break;
						}
					}
					veLaiKhung();
					stt = 0;
					break;		
				}
				else if(stt == 3) // Tim kiem
				{
					char ktu;
					int dem = 0;
					nhapnhay();		 
					gotoxy(15,16+1);
					SetColor(4);
					printf("Tim kiem nhi phan");
			    	gotoxy(13,16);
					SetColor(12);
					printf("%c %s %c",16,"Tim kiem tuan tu",17);
					while(1)
					{
						ktu = getch();
						switch(ktu)
						{
							case 72:
								dem--;
								if(dem<0)
								{
									dem =1;
									gotoxy(13,16);
									SetColor(4);
									printf("  %s  ","Tim kiem tuan tu");
									gotoxy(13,16+1);
									SetColor(12);
									printf("%c %s %c",16,"Tim kiem nhi phan",17);
								}
								else
								{
									gotoxy(13,16+1);
									SetColor(4);
									printf("  %s  ","Tim kiem nhi phan");
									gotoxy(13,16);
									SetColor(12);
									printf("%c %s %c",16,"Tim kiem tuan tu",17);
								}
								break;
							case 80:
								dem++;
								if(dem>1)
								{
									dem = 0;
									gotoxy(13,16+1);
									SetColor(4);
									printf("  %s  ","Tim kiem nhi phan");
									gotoxy(13,16);
									SetColor(12);
									printf("%c %s %c",16,"Tim kiem tuan tu",17);	
								}
								else
								{
									dem = 1;
									gotoxy(13,16);
									SetColor(4);
									printf("  %s  ","Tim kiem tuan tu");
									gotoxy(13,16+1);
									SetColor(12);
									printf("%c %s %c",16,"Tim kiem nhi phan",17);
								}
								break;
							case 13:
								if(dem == 0)
								{
									tktuantu(l);
									ktu = 27;			
								}
								else if(dem == 1)
								{
									char nhap;
									dem = 0;
									nhapnhay();
									for(int i = 1;i<5;++i)
			 	  					{ 
										gotoxy(15,16+i);
										SetColor(4);
										printf(tkiem[i]);
			    				     } 
			    					 	gotoxy(13,16);
										SetColor(12);
										printf("%c %s %c",16,tkiem[0],17);
									while(1)
									{
										nhap = getch();
										switch(nhap)
										{
											case 72:							
												dem--;
												if(dem<0)
												{
													dem = 4;
													gotoxy(13,16);
													SetColor(4);
													printf("  %s  ",tkiem[0]);
													gotoxy(13,16+4);
													SetColor(12);
													printf("%c %s %c",16,tkiem[4],17);
												}
												else
												{
													gotoxy(13,16+dem+1);
													SetColor(4);
													printf("  %s  ",tkiem[dem+1]);
													gotoxy(13,16+dem);
													SetColor(12);
													printf("%c %s %c",16,tkiem[dem],17);
												}
													break;
											case 80:
												dem++;
												if(dem > 4)
												{
													dem = 0;
													gotoxy(13,16+4);
													SetColor(4);
													printf("  %s  ",tkiem[dem+4]);
													gotoxy(13,16);
													SetColor(12);
													printf("%c %s %c",16,tkiem[dem],17);
												}
												else
												{
													gotoxy(13,16+dem-1);
													SetColor(4);
													printf("  %s  ",tkiem[dem-1]);
													gotoxy(13,16+dem);
													SetColor(12);
													printf("%c %s %c",16,tkiem[dem],17);
												}
												break;
											case 13:
												switch(dem)
												{
													case 0:
														tknhiphan(l,1);
														nhap =27;
														break;
													case 1:
														tknhiphan(l,2);
														nhap = 27;
														break;
													case 2:
														tknhiphan(l,3);
														nhap = 27;
														break;
													case 3:
														tknhiphan(l,4);
														nhap = 27;
														break;
													case 4:
														tknhiphan(l,5);
														nhap = 27;
														break;
												}
												break;
											}
											if (nhap == 27)
											break;
										}
									ktu = 27;
								}
								break;	
						}
							if(ktu == 27)
							break;
					}
					veLaiKhung();
					stt = 0;
					break;				
				}	
				else if(stt == 4) // Thong ke
				{
					int dem = 0;
					char ktu;
					nhapnhay();
					for(int i = 1; i < 5; ++i)
					{ 
	    				gotoxy(15,16+i);	
						SetColor(4);
						printf(tKe[i]);   				 
			   		} 
				 	gotoxy(13,16);
					SetColor(12);
					printf("%c %s %c",16,tKe[0],17);
					while(1)
					{
						ktu = getch();
						switch(ktu)
						{
							case 72:
								dem--;
								if(dem < 0)
								{
									dem = 4;
									gotoxy(13,16);
									SetColor(4);
									printf("  %s  ",tKe[0]);
									gotoxy(13, 16+4);
									SetColor(12);
									printf("%c %s %c",16,tKe[4],17);
								}
								else
								{
									gotoxy(13,16+dem+1);
									SetColor(4);
									printf("  %s  ",tKe[dem+1]);
									gotoxy(13,16+dem);
									SetColor(12);
									printf("%c %s %c",16,tKe[dem],17);
								}
								break;
							case 80:
								dem++;
								if(dem > 4)
							 	{
									dem = 0;
									gotoxy(13,16+4);
									SetColor(4);
									printf("  %s  ",tKe[dem+4]);
									gotoxy(13,16);
									SetColor(12);
									printf("%c %s %c",16,tKe[dem],17);
								}
								else
								{
									gotoxy(13,16+dem-1);
									SetColor(4);
									printf("  %s  ",tKe[dem-1]);
									gotoxy(13,16+dem);
									SetColor(12);
									printf("%c %s %c",16,tKe[dem],17);
								}
								break;
							case 13:
								if(dem == 0)
								{
									thongKe(l,1);
									ktu = 27;
								}
								else if(dem == 1)
								{
									thongKe(l,2);
									ktu = 27;
								}
								else if(dem == 2)
								{
									thongKe(l,3);
									ktu = 27;
								}
								else if( dem == 3)
								{
									thongKe(l,4);
									ktu = 27;
								}
								else if (dem == 4)
								{
									thongKe(l,5);
									ktu = 27;
								}
									break;
								}
							if(ktu == 27)
							break;		
						}
						veLaiKhung();
						stt = 0;
				}
				else if(stt == 5) // Xoa sinh vien
				{
					char ktu;
					xoasv(l);
						while(1)
					{
						ktu = getch();
						if(ktu == 27) break;
					}
					veLaiKhung();
					stt = 0;
				}
				else if(stt == 6) // Sua thong tin sinh vien
				{
					node *p;
					p = taoNode();
					suaSV(l,&p->data);
					veLaiKhung();
					stt = 0;
				}				
				else if(stt == 7) // Thoat chuong trinh
				{
					system("cls");
					gotoxy(35,1);
					SetColor(10);
					cout<<"CAM ON VI DA SU DUNG CHUONG TRINH CUA TOI! ";
					return;
				}	
			break;		
		}
	}
}

//nhap ma lop va chuan hoa (gom ky tu va so duoc viet hoa va ko co ky tu dac biet va dau cach o dau)
string nhapMaLop(int x,int y)
{
	SetColor(6);
	gotoxy(x,y);
	char ch,tam[2];
	string name = "";
	int i=0;
	while(1)
	{
		const char* chuoi = name.c_str(); // Ktra chuoi
		if(i == 0)
		{
			do
			{
				tam[0] = getch();
			} while(isalpha(tam[0]) == 0 && isdigit(tam[0]) == 0); // Ktra ky tu la kieu so
		}
		else
		{
			tam[0] = getch();
		}
		if(isalpha(tam[0]) != 0) // Ktra ky tu truyen vao co phai la chu cai hay ko
		{
			if( tam[0]>='a'&& tam[0]<='z')
			{
				tam[0] = tam[0]-32;
			}
		}	
		if(isalpha(tam[0]) != 0 || isdigit(tam[0]) != 0  || chuoi[i-1] !=' ' && tam[0] ==' ' && i != 0)
		{
			name += tam[0];
			gotoxy (x,y);
			for(int j = 0;j < 10; j++) cout<<" ";
			gotoxy(x,y);
			cout << name;
			i++;
		}		
		if(tam[0] == 8)
		{
day:		const char *chuoiName = name.c_str();
			char *tam1 = new char();
			strcpy(tam1, chuoiName);
			xoakitu(tam1, strlen(tam1)-1,1);
			name = tam1;
			gotoxy(x,y);
			for(int j = 0; j< 10; j++) cout<<" ";
			gotoxy(x,y);
			cout<<name;
			i--;
		}
		if(i==10 || tam[0] == 13)
		{
			if( i == 10)
			{
				do
				{
					ch = getch();
				} while(ch != 8 && ch != 13);		
			if(ch == 13)
				break;
			else
				goto day;
			}
			else
			{
				break;
			}
		}
	}
	return name;
}
// nhap ma sinh vien (Nhap du 8 ky tu la so)
int nhapmasv(int x,int y)
{
	char ch;
	gotoxy(x,y);
	int i = 0, kq = 0;	
	string tam = "";
	char masv[2];
	char *xoa = new char();
	while(1)
	{
		masv[0] = getch();	
		if(isdigit(masv[0]) != 0 && i <=8)
		{	
			tam += masv[0];
			gotoxy(x,y);		
			for(int j = 0; j < 8; j++) cout<<" ";
			gotoxy(x,y);
			cout << tam;
			i++;	
		}
		else if(masv[0] == 8) // Phim backspace
		{
day:		if(i>0)
			{
				const char *h = tam.c_str();
				strcpy(xoa,h);
				xoakitu(xoa, strlen(xoa)-1,1);
				tam = xoa;
				gotoxy(x,y);
				for(int j = 0; j < 8; j++) cout<< " ";
				gotoxy(x,y);
				cout << tam;
				i--;
			}
		}
		if(i == 8)
		{
			while(1)
			{
				masv[0] = getch();
				if(masv[0] == 8)
				goto day;
				else if(masv[0] == 13)
				break;
			}
			break;	
		 } 
	}
	const char* h = tam.c_str();
	kq = atoi(h);
	return kq;
}
// Nhap ngay sinh
int nhapNgaySinh(int x,int y)
{
	SetColor(6);
	gotoxy(x,y);
	char ngay[2];
	string day ="";
	int kq = 0,i=0;
	const char* chuoiNgay;
	while(1)
	{
		chuoiNgay = day.c_str();
		if(i == 0)
		{
			do
			{
				ngay[0] = getch(); 
			}while(isdigit(ngay[0]) == 0);
			i++;
			day += ngay[0];
			gotoxy(x,y);
			for(int j=0;j<2;j++)
			cout<<" ";
			gotoxy(x,y);
			cout<<day; 
		}
		else
		{
			ngay[0] = getch();
			if(ngay[0] == 8)
			{
				char *chuoi1 = new char();
				strcpy(chuoi1,chuoiNgay);
				xoakitu(chuoi1,strlen(chuoi1)-1,1);
				day = chuoi1;
				gotoxy(x,y);
				for(int j=0;j<2;j++)
				cout<<" ";
				gotoxy(x,y);
				cout<<day;
				i--;
			}
			else if(isdigit(ngay[0]) != 0)
			{
				day += ngay[0];
				gotoxy(x,y);
				for(int j=0;j<2;j++) cout<<" ";
				gotoxy(x,y);
				cout<<day;
				i++;
			}
		}
		if(i==2) 
		{
			do
			{
				ngay[0] = getch();		
			} while(ngay[0] != 8 && ngay[0] != 13);			
			if(ngay[0] == 8)
			{
				chuoiNgay = day.c_str();
				char * chuoi1 = new char();
				strcpy(chuoi1,chuoiNgay);
				xoakitu(chuoi1,strlen(chuoi1)-1,1);
				day = chuoi1;
				gotoxy(x,y);
				for(int j = 0; j < 2; j++) cout<<" ";
				gotoxy(x,y);
				cout<<day;
				i--;
			}
			else if(ngay[0] == 13)
			break;
		}
	}
	chuoiNgay = day.c_str();
	kq = atoi(chuoiNgay); // Chuyen chuoi sang so nguyen
	return kq;
}
//nhap thang sinh
int nhapThangSinh(int x,int y)
{
	SetColor(6);
	gotoxy(x,y);
	char thang[2];
	string month ="";
	int kq = 0,i=0;
	const char* chuoiThang;
	while(1)
	{
		chuoiThang = month.c_str();
		if(i == 0)
		{
			do
			{
				thang[0] = getch(); 
			} while(isdigit(thang[0]) == 0);
			i++;
			month += thang[0];
			gotoxy(x,y);
			for(int j=0;j<2;j++)
			cout<<" ";
			gotoxy(x,y);
			cout<<month; 
		}
		else
		{
			thang[0] = getch();
			if(thang[0] == 8)
			{
				char *chuoi1 = new char();
				strcpy(chuoi1,chuoiThang);
				xoakitu(chuoi1,strlen(chuoi1)-1,1);
				month = chuoi1;
				gotoxy(x,y);
				for(int j=0;j<2;j++)
				cout<<" ";
				gotoxy(x,y);
				cout<<month;
				i--;
			}
			else if(isdigit(thang[0]) != 0)
			{
				month += thang[0];
				gotoxy(x,y);
				for(int j=0;j<2;j++) cout<<" ";
				gotoxy(x,y);
				cout<<month;
				i++;
			}
		}
		if(i == 2) 
		{
			do
			{
				thang[0] = getch();	
			}while(thang[0] != 8 && thang[0] != 13);						
			if(thang[0] == 8)
			{
				chuoiThang = month.c_str();
				char * chuoi1 = new char();
				strcpy(chuoi1,chuoiThang);
				xoakitu(chuoi1,strlen(chuoi1)-1,1);
				month = chuoi1;
				gotoxy(x,y);
				for(int j=0;j<2;j++) cout<<" ";
				gotoxy(x,y);
				cout<<month;
				i--;
			}
			else if(thang[0] == 13)
			break;
		}
	}
	chuoiThang = month.c_str();
	kq = atoi(chuoiThang);
	return kq;
}
//nhap nam sinh
int nhapNamSinh(int x,int y)
{
	SetColor(6);
	gotoxy(x,y);
	char nam[2];
	string year="";
	int kq = 0,i=0;
	const char* chuoiNam;
	while(1)
	{
		chuoiNam = year.c_str();
		if(i == 0)
		{
			do
			{
				nam[0] = getch(); 
			} while(isdigit(nam[0]) == 0);
			i++;
			year += nam[0];
			gotoxy(x,y);
			for(int j = 0; j < 4; j++)
			cout << " ";
			gotoxy(x,y);
			cout<<year; 
		}
		else
		{
			nam[0] = getch();		
			if(nam[0] == 8)
			{
				char *chuoi1 = new char();
				strcpy(chuoi1,chuoiNam);
				xoakitu(chuoi1,strlen(chuoi1)-1,1);
				year = chuoi1;
				gotoxy(x,y);
				for(int j=0;j<4;j++)
				cout<<" ";
				gotoxy(x,y);
				cout<<year;
				i--;
			}
			else if(isdigit(nam[0]) != 0)
			{
				year += nam[0];
				gotoxy(x,y);
				for(int j = 0; j < 4; j++) cout<<" ";
				gotoxy (x,y);
				cout<<year;
				i++;
			}
		}
		if(i==4) 
		{
			do
			{
				nam[0] = getch();				
			} while(nam[0] != 8 && nam[0] != 13);						
			if(nam[0] == 8)
			{
				chuoiNam = year.c_str();
				char * chuoi1 = new char();
				strcpy(chuoi1,chuoiNam);
				xoakitu(chuoi1,strlen(chuoi1)-1,1);
				year = chuoi1;
				gotoxy(x,y);
				for(int j = 0; j < 4; j++) cout<<" ";
				gotoxy(x,y);
				cout << year;
				i--;
			}
			else if(nam[0] == 13)
			break;
		}
	}
	chuoiNam = year.c_str();
	kq = atoi(chuoiNam);
	return kq;	
}
// Xu ly loi nhap thoi gian
void xuLyThoiGian(date *p)
{
	int i;
	int day = p->ngay;
	int year = p->nam;
	int month = p->thang;						
		if(day > 31 || day <= 0)
		{
			p->ngay = nhapNgaySinh(50,26);
			xuLyThoiGian(p);
		}
		else if (year < 1970 || year > 2015)
		{
			p->nam = nhapNamSinh(71,26);
			xuLyThoiGian(p);
		}
		else
		{
			if(month == 1||month == 3||month == 5||month == 7||month ==8||month ==10||month == 12)
			{
				return;
			}		
			else if( month == 2) //tuc month =2
			{
				if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) 
				{
					if(day >29)
					{
						p->ngay = nhapNgaySinh(50,26);
						xuLyThoiGian(p);
					}	
				}
				else
				{
					if(day>28)
					{
						p->ngay = nhapNgaySinh(50,26);
						xuLyThoiGian(p);
					}
				}	
			}
			else if(month == 4 || month == 6 || month == 9|| month == 11) //tuc thang bang 4,6,9,11
			{
				if(day>30)
				{
					p->ngay = nhapNgaySinh(50,26);
					xuLyThoiGian(p);			
				}
			}
			else if(month >12) //thang lon hon 12
			{
				p->thang = nhapThangSinh(61,26);
				xuLyThoiGian(p);
			}
		}		
	return;
}
// nhap diem trung binh
float nhapDiem(int x,int y)
{
	SetColor(6);
	gotoxy(x,y);
	float kq;
	string mark ="";
	char diem[2],ch;
	int ktra =0;
	const char *diemtb ;
	int i=0;
	while(1)
	{
		if(i == 0)
		{
			do
	    	{
				diem[0] = getch();
			}while(isdigit(diem[0]) == 0);
			i++;
			mark += diem[0];
			gotoxy(x,y);
			for(int j=0;j<4;j++) cout<<" ";
			gotoxy(x,y);
			cout<<mark;
		}
		else
		{
			diem[0] = getch();
			ktra  = 0;
			if(diem[0] == 13)
			{
				diemtb = mark.c_str();
				kq = atof(diemtb);
				if(kq < 0 || kq > 10)
				{
					mark = "";
					i = 0;
					gotoxy(x,y);
					for(int j=0;j<4;j++)
					cout<<" ";
					gotoxy(x,y);
				}
				else
					break;	
			}
dayne:		diemtb = mark.c_str();
			for(int j = 0;j < i; j++)
			{
				if(diemtb[j] == '.')
				ktra++;
			}
			if(diem[0] == 8)
			{
				
				char *tam = new char();
				strcpy(tam,diemtb);
				xoakitu(tam,strlen(tam)-1,1);
				mark = tam;
				gotoxy(x,y);
				for(int j=0;j<4;j++) cout<<" ";
				gotoxy(x,y);
				cout<<mark;
				i--;
			}
			else if( ktra == 0 && diem[0] == '.' || isdigit(diem[0]) == 1)
			{
				mark += diem[0];
				i++;
				gotoxy(x,y);
				for(int j=0;j<4;j++)
				cout<<" "; 
				gotoxy(x,y);
				cout<<mark;
			}
		}
		if(i == 4)
		{
			while(1)
			{
				diem[0] = getch();
				if(diem[0] == 8)
				goto dayne;
				else if(diem[0] == 13)
				break;			
			}
			diemtb = mark.c_str();
			kq = atof(diemtb);
			if(kq < 0 || kq >10.0)
			{
				gotoxy(x,y);
				for(int j=0;j<4;j++) 
				cout<<" ";
				i =0;
				mark ="";
				gotoxy(x,y);
			}
			else
			break;
		}		
	}
	return kq;
}
//nhap ten
string nhapTen(int x, int y) // de la chi so lan nhap,dung trong ham menu()
{
	
	SetColor(6);
	gotoxy(x,y);
	char ch,tam[2];
	string name = "";
	int i=0;
	while(1)
	{
		const char* chuoi = name.c_str();
		if(i == 0)
		{
			do
			{
				tam[0] = getch();
			} while(isalpha(tam[0]) == 0);
		}
		else
		{
			tam[0] = getch();
		}
		if(isalpha(tam[0]) != 0 && i == 0 )	
		{
			if( tam[0]>='a'&& tam[0]<='z')
			{
				tam[0] = tam[0]-32;
			}
		}		
		if(chuoi[i-1] == ' ' && isalpha(tam[0]) != 0)
		{
			if( tam[0] >= 'a' && tam[0] <= 'z')
			{
				tam[0] = tam[0] -32;
			}
		}		
		if(isalpha(tam[0]) != 0 || chuoi[i-1] !=' ' && tam[0] ==' ' && i != 0)
		{
			name += tam[0];
			gotoxy(x,y);
			for(int j=0;j<24;j++) cout<<" ";
			gotoxy(x,y);
			cout<<name;
			i++;
		}
		if(tam[0] == 8)
		{
day:		const char *chuoiName = name.c_str();
			char *tam1 = new char();
			strcpy(tam1,chuoiName);
			xoakitu(tam1,strlen(tam1)-1,1);
			name = tam1;
			gotoxy(x,y);
			for(int j=0;j<24;j++) cout<<" ";
			gotoxy(x,y);
			cout<<name;
			i--;
		}	
		if(i==24 || tam[0] == 13)
		{
			if( i == 24)
			{
				do
				{
					ch = getch();
				}while(ch != 8 && ch != 13);			
			if(ch == 13)
				break;
			else
			goto day;
			}
			else
			{
				break;
			}
		}
	}
	return name;
}
// in danh sach sinh vien
void inDS(list l)
{
    	char ch;
		system("cls");
		node *p;
		p = taoNode();
		int i = 0;
		p = l.dau;
		SetColor(6);
		printf("\n\t\t\t\tDANH SACH SINH VIEN\n");
		SetColor(3);
		printf("%c",201); // goc tren trai
		for(int j =0;j<74;j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i=0;i<74;i++)
		{
			printf("%c",205);
		}
		printf("%c",185);

		while(p!=NULL)
		{			
			printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++i,179,p->data.hoten,179,p->data.malop,179,p->data.masv,179,p->data.tg.ngay,p->data.tg.thang,p->data.tg.nam,179,p->data.diemtb,186);
			if(p->next!=NULL)
		{
		printf("%c",204);	
		for(int j=0;j<74;j++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		}
		else
		{
			printf("%c",200);
			for(int j=0;j<74;j++)
			{
				printf("%c",205);
			}
			printf("%c",188);
		}
		p = p->next;
		
		}
		SetColor(13);
		cout<<endl<<"Nhan ESC de thoat viec in danh sach";
}		
// tao node
node *taoNode()
{
	node *p;
	p = new node();
	if(p==NULL)
	{
		cout<<"Khong du bo nho";
		exit(1);
	}
	else
	p->next = NULL;
	return p;
}
//them Cuoi
void themcuoi(list &l,node *p)
{
	if(l.dau == NULL)
	{
		l.cuoi = l.dau = p;
	}
	else
	{
		l.cuoi->next = p;
		l.cuoi = p;
	}
}

//doc file
void docfile(list &l)
{
	list lt;
	initList(lt);
	node *p;
	FILE *f;
	f = fopen(filename,"rb");
	if(f == NULL)
	{
		cout<<"Khong ton tai file";
		exit(1);
	}
	fseek(f,0,SEEK_END);
	int n = ftell(f);
	n = n/sizeof(sv);
	rewind(f);
	for (int i=0;i<n;i++)
	{
		p =taoNode();
		fread(&p->data,sizeof(sv),1,f);
		themcuoi(lt,p);
	}
	l = lt;
	fclose(f);
}
 // ghi file
void luufile(list &l)
{
	node *p;
	FILE *f;
	p = l.dau;
	f = fopen(filename,"wb");
	while(p!=NULL)
	{
		fwrite(&p->data,sizeof(sv),1,f);
		p = p->next;
	}
	fclose(f);
}
//dem so sinh vien trong danh sach
int demsv()
{
	FILE *f;
	int dem;
	f= fopen(filename,"rb");
	fseek(f,0,SEEK_END);
	dem = ftell(f);
	dem = dem/sizeof(sv);
	fclose(f);
	return dem;	
}
//xoa sinh vien
void xoasv(list &l)
{
	system("cls");
	char x;
	node *p;
	node *q;
	p = taoNode();
	int stt;
nhan:
	string tam = "";
	inDS(l);
	cout<<endl<<"Ban can xoa sinh vien thu may: ";
	while(1)
	{
		x = getch();
		if(isdigit(x) == 1)
		{
			tam += x;
			cout << x;
		}
		else if(x == 13)
		break;
	}
	stt = atoi(tam.c_str());
	cout<<endl<<"Ban co chac chan xoa: "<<endl<<"(Nhap y de tiep tuc xoa, n de thoat ):";
	x = getch();
	system("cls");
	p = l.dau;
	int dem;
	if(x == 'y')
	do
	{
		dem = 1;
		if(demsv() == 0)
		{
			cout<<"Khong con gi de xoa";
			getch();
			break;
		}
		if(stt == 1)
			{
			if(demsv() == 1)
				{
					initList(l);
					break;
				}
			else
			{
				q = p;
				l.dau = p->next;
				p = p->next;
				free(q);
				break;
			}
		}
		else if(stt > 1 && stt <= demsv())
		{
			while(p!=NULL)
			{
				++dem;
				if(dem == stt)
				{
					q = p->next;
					p->next = q->next;
					free(q);
				}
				p=p->next;
			}
		}
		else if( stt > demsv() || stt < 1)
		{
    		//cout<< "Ban nhap ";
    		goto nhan;
		}
	} while(stt > demsv());
	else if(x == 'n');
	else goto nhan;  //ky tu ko phai y hoac n thi se quay lai
	luufile(l);
	docfile(l);
	inDS(l);
}
//tach chuoi cuoi cua xau (Lay ho)
char* tachCuoi(char a[])
{
	int dem1;
	int j=0;
	char *tam1= new char();
	dem1 =strlen(a);
	while(a[dem1-1]!=' '&& dem1!=0)dem1--;
	for(int i=dem1;i<strlen(a);i++)
	{
		*(tam1+j) = a[i];
		j++;
	}
	*(tam1+j) = '\0';
	return tam1;
}
// Lay ten
char* layDau(char a[])
{
	int dem=0;
	int i=0;
	char *tam = new char();
	while(a[i]!=' '&& i <=strlen(a)-1)
	{
		*(tam+i) = a[i];	
		i++;
	}
	*(tam+i) = '\0';
	return tam;
}	
const char* tachDau(char a[])
{
	string s = a;
	return s.c_str();
}

// Khu vuc cac ham sap xep
// 1. Chon
// 2. Chen
// 3. Noi bot
// 4. Nhanh
// sap xep chon
void sapxepchon(list &l,int n)
{
	node *p,*q,*min;
	for(p = l.dau;p->next!=NULL;p=p->next)
	{
		min = p;
		for(q = p->next;q!=NULL;q=q->next)
		{
			if(n == 1) // Ma Sinh Vien
			{
				if(q->data.masv < min->data.masv)
				min = q;
			}
			else if(n == 2) // Ho Ten
			{
				string tam1,tam2,tam3,tam4;
				tam1 = tachCuoi(q->data.hoten);
				tam2 = tachCuoi(min->data.hoten);
				tam3 = tachDau(q->data.hoten);
				tam4 = tachDau(min->data.hoten);
				if(tam1 < tam2 ||(tam1 == tam2) && (tam3 <= tam4))
					min = q;	
			}
			else if(n == 3) // Ngay sinh
			{
				if(q->data.tg.nam < min->data.tg.nam)
				min = q;
				else if(q->data.tg.nam == min->data.tg.nam)
				{
					if(q->data.tg.thang < min->data.tg.thang)
					{
						min = q;
					}
					else if(q->data.tg.thang == min->data.tg.thang)
					{
						if(q->data.tg.ngay < min->data.tg.ngay)
						min = q;
					}		
				}	
			}	
			else if(n==4) // Diem TB
			{
				if(q->data.diemtb < min->data.diemtb)
				min = q;
			}
		}
		hoanvi(&min->data,&p->data);
	}
	inDS(l);	
}

// sap xep chen
void sapxepchen(list &l, int n)
{
	node *first_unsorted,*last_sorted,*current,*trailing,*p;	
	if(l.dau!=NULL)
	{
		last_sorted = l.dau;
		while(last_sorted->next != NULL)
		{
			first_unsorted = last_sorted->next;
			if(n == 1) //ma sv
			{
				if(first_unsorted->data.masv <= l.dau->data.masv)
			 	{
					last_sorted->next= first_unsorted->next;
					first_unsorted->next = l.dau;
					l.dau = first_unsorted;
			 	}	 
				else
			    {
			 		trailing = l.dau; 
					current = trailing->next;
					while(first_unsorted->data.masv > current->data.masv)
					{
						trailing = current;
						current  = current->next;
						if(current == first_unsorted)
						break;
					}
					// first_unsorted duoc chen vao giua trailing va current
					if(current == first_unsorted)
					{
						last_sorted = first_unsorted;
					}
					else
					{
						last_sorted->next = first_unsorted->next;
						first_unsorted->next = current;
						trailing->next = first_unsorted;
					}
				}		
			}
			else if( n==2) // Ho ten
			{
				// truong hop xet last Name
				string tam1,tam2,tam3,tam4;
				tam1 = tachCuoi(first_unsorted->data.hoten); 
				tam2 = tachCuoi(l.dau->data.hoten);
				tam3 = tachDau(first_unsorted->data.hoten);
				tam4 = tachDau(l.dau->data.hoten);
				if(tam1<tam2 || (tam1 == tam2)&&(tam3 <= tam4)) //neu chuoi cuoi cua tam1 nho hon chuoi cuoi tam2
				{
					last_sorted->next= first_unsorted->next;
					first_unsorted->next = l.dau;
					l.dau = first_unsorted;	
			 	}	 
				 //truong hop chuoi 2 lon hon chuoi 1
			 	else //truong hop cuoi chuoi first_unsorted lon hon chuoi cuoi cua l.dau
			    {
					string tamCur,tamFirst,tamF,tamC;
			 		trailing = l.dau; 
					current = trailing->next;
					tamFirst = tachCuoi(first_unsorted->data.hoten);
					tamCur = tachCuoi(current->data.hoten);
					tamF = tachDau(first_unsorted->data.hoten);
					tamC = tachDau(current->data.hoten);
					while(tamFirst > tamCur||( (tamFirst == tamCur )&& tamF > tamC))
					{
						trailing = current;
						current  = current->next;
						if(current == first_unsorted)
						break;
						tamCur = tachCuoi(current->data.hoten);
						tamC = tachDau(current->data.hoten);		
					}
					// first_unsorted duoc chen vao giua trailing va current
					if(current == first_unsorted)
					{
						last_sorted = first_unsorted;
					}
					else
					{
						last_sorted->next = first_unsorted->next;
						first_unsorted->next = current;
						trailing->next = first_unsorted;
					}
				}		
			}
			else if(n == 3) // Ngay sinh
			{
				if(first_unsorted->data.tg.nam < l.dau->data.tg.nam || first_unsorted->data.tg.nam == l.dau->data.tg.nam && (first_unsorted->data.tg.thang*100+first_unsorted->data.tg.ngay <= l.dau->data.tg.thang*100+l.dau->data.tg.ngay))
				{
					last_sorted->next = first_unsorted->next;
					first_unsorted->next = l.dau;
					l.dau = first_unsorted;
				}
				else
				{
					trailing = l.dau;
					current = trailing->next;
					while(first_unsorted->data.tg.nam > current->data.tg.nam || first_unsorted->data.tg.nam == current->data.tg.nam && (first_unsorted->data.tg.thang*100+first_unsorted->data.tg.ngay > current->data.tg.thang*100+l.dau->data.tg.ngay))
					{
						trailing = current;
						current = current->next;
						if(current == first_unsorted)
						break;
					}
					if(current == first_unsorted)
					{
						last_sorted = first_unsorted;
					}
					else
					{
						last_sorted->next = first_unsorted->next;
						trailing->next = first_unsorted;
						first_unsorted->next = current;
					}		
				}
			}
			else if(n == 4) // Diem TB
			{
				if(first_unsorted->data.diemtb <= l.dau->data.diemtb )
				{
					last_sorted->next = first_unsorted->next;
					first_unsorted->next = l.dau;
					l.dau = first_unsorted;			
				}
				else
				{
					trailing = l.dau;
					current = trailing->next;
					while(first_unsorted->data.diemtb > current->data.diemtb)
					{
						trailing = current;
						current = current->next;
						if(current == first_unsorted)
						break;		
					}
					if(current == first_unsorted)
					{
						last_sorted = first_unsorted;
					}
					else
					{
						last_sorted->next = first_unsorted->next;
						trailing->next = first_unsorted;
						first_unsorted->next = current;
					}
				}
			}
		}
		inDS(l);
	} 
}

// sap xep noi bot
void sapxepnoibot(list &l,int n)
{
	node *p,*q;
	for(p = l.dau;p->next!=NULL;p=p->next )
	{
		for(q = p->next;q!=NULL;q=q->next)
		{
			if(n == 1) // Ma SV
			{
				if(q->data.masv < p->data.masv)
				hoanvi(&q->data,&p->data);
			}
			else if(n == 2) // Ten
			{
				string tam1,tam2,tam3,tam4;
				tam1 = tachCuoi(q->data.hoten);
				tam2 = tachCuoi(p->data.hoten);
				tam3 = tachDau(q->data.hoten);
				tam4 = tachDau(p->data.hoten);
				if(tam1 < tam2 || tam1 == tam2 && tam3 <= tam4)
				hoanvi(&q->data,&p->data);			
			}
			else if(n == 3) // Ngay Sinh
			{
				if(q->data.tg.nam < p->data.tg.nam || (q->data.tg.nam == p->data.tg.nam)&& q->data.tg.thang*100+q->data.tg.ngay < p->data.tg.thang*100+p->data.tg.ngay )
				hoanvi(&q->data,&p->data);
			}
			else if(n == 4) // Diem TB
			{
				if(q->data.diemtb < p->data.diemtb)
				hoanvi(&q->data,&p->data);
			}		
		}
	}
	inDS(l);
}
// sap xep quicksort
void quicksort(list &l,int n)
{
	list l1,l2;
	initList(l1);
	initList(l2);
	node *pivot,*p;
	if(l.dau == NULL) return;
	else
	{ 
		if(l.dau == l.cuoi) return;
		pivot = l.dau;
		l.dau = pivot->next;
		while(l.dau!=NULL)
		{
			p = l.dau;
			l.dau = p->next;
			p->next = NULL;
			if(n == 1)
			{
				if(p->data.masv < pivot->data.masv)
					themcuoi(l1,p);
				else 
					themcuoi(l2,p);
			}
			else if(n == 2)
			{
				string tam1,tam2,tam3,tam4;
				tam1 = tachCuoi(p->data.hoten);
				tam2 = tachCuoi(pivot->data.hoten);
				tam3 = tachDau(p->data.hoten);
				tam4 = tachDau(pivot->data.hoten);
				if((tam1 < tam2)||((tam1 == tam2)&& tam3 <= tam4))
				{
					themcuoi(l1,p);
				}
				else
				{
					themcuoi(l2,p);
				}
			}
			else if(n == 3)
			{
				if(p->data.tg.nam < pivot->data.tg.nam ||( p->data.tg.nam == pivot->data.tg.nam ) && p->data.tg.thang*100+p->data.tg.ngay <= pivot->data.tg.thang*100+pivot->data.tg.ngay)
				{
					themcuoi(l1,p);
				}
				else
				{
					themcuoi(l2,p);	
				}
			}
			else if( n==4)
			{
				if(p->data.diemtb <= pivot->data.diemtb)
				themcuoi(l1,p);
				else 
				themcuoi(l2,p);
			}
		}
		quicksort(l1,n);
		quicksort(l2,n);
		if( l1.dau != NULL)
		{
			l.dau = l1.dau;
			l1.cuoi->next = pivot;
		}
		else
			l.dau = pivot;
			pivot->next = l2.dau;
		if(l2.dau != NULL)
		{
			l.cuoi = l2.cuoi;
		}
		else
			l.cuoi = pivot;	
	}	
}
void Mergersort(list &l, int n)
{
	
}
// ham hoan vi
void hoanvi(sv *p,sv *q)
{
	sv tam;
	tam.diemtb = p->diemtb;
	strcpy(tam.hoten,p->hoten);
	strcpy(tam.malop,p->malop);
	tam.masv = p->masv;
	tam.tg.ngay = p->tg.ngay;
	tam.tg.thang = p->tg.thang;
	tam.tg.nam = p->tg.nam;
	p->diemtb = q->diemtb;
	strcpy(p->hoten,q->hoten);
	strcpy(p->malop,q->malop);
	p->masv =q->masv;
	p->tg.ngay = q->tg.ngay;
	p->tg.thang = q->tg.thang;
	p->tg.nam = q->tg.nam;
	q->diemtb = tam.diemtb;
	strcpy(q->hoten,tam.hoten);
	strcpy(q->malop,tam.malop);
	q->masv = tam.masv;
	q->tg.ngay = tam.tg.ngay;
	q->tg.thang = tam.tg.thang;
	q->tg.nam = tam.tg.nam;
}
// Khu vuc Ham tim kiem
// 1. TK Tuan tu
// 2. TK nhi phan
// tim kiem tuan tu
void tktuantu(list l)
{
 	node *p = taoNode();
 	string tam="";
 	char ktu;
 	inDS(l);
 	keBang(80,1,30,2);
 	char *xoa = new char();
 	while(1)
 	{
 		p = l.dau;
 		gotoxy(81,2);
 		ktu = getch();
 		if(ktu == 27)
 		break;
 		else if(ktu == 8)
 		{
 			const char* h = tam.c_str();
 			strcpy(xoa,h);
 			xoakitu(xoa,strlen(xoa)-1,1);
 			tam = xoa;
 			goto there;
		}
		else if(isalpha(ktu)!=0 || isdigit(ktu)!=0 || ktu == '/' || ktu == '.' || ktu == ' ' )
 		{
there:	system("cls");
		SetColor(6);
		printf("\n\t\t\t\tDANH SACH SINH VIEN\n");
		SetColor(3);
		printf("%c",201); // goc tren trai
		for(int j = 0; j < 74; j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i = 0;i < 74; i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		keBang(80,1,30,2);
	 	if(ktu != 8) // Phim backspace
 		tam += ktu;
 		gotoxy(81,2);
 		cout<< tam;
 		const char* b = tam.c_str();
 		char *c = new char();
 		strcpy(c,b);
 		gotoxy(0,4);
 		int dem = 0;
 		for(p ; p != NULL; p = p->next)
 		{
 			int demP = strlen(p->data.hoten);
 			int demT = strlen(b);
 			int i = 0,j = 0;
 			do
 			{
 				char tamP[2];
 				char tamB[2];
 				tamP[0] = p->data.hoten[i];
 				tamP[1] ='\0';
 				tamB[0] =b[j];
 				tamB[1]='\0';
 				if(stricmp(tamP,tamB) == 0)
 				{
 					i++;
 					j++;
				}
				else
				{			 
					i = i-j+1;
					j = 0;
				}	 			 
			} while(j < demT && i< demP);
 			if( j < demT)			// neu truong hop ho ten ma quet het ko tim thay thi se chuyen sang tim tren ma lop
			{
	 			i = 0;j = 0;
	 			do
	 			{		 		
	 				char tamB[strlen(b)+1];
	 				for(int t=0;t<strlen(b);t++ )
	 				{
	 					if(b[t] >= 'a' && b[t] <= 'z' )
						{
				 			tamB[t] = b[t] -32;
						}
						else
						{
				 			tamB[t] = b[t];
						}	
					}
					tamB[strlen(b)] ='\0';
	 				if(p->data.malop[i] == tamB[j])
	 				{
	 					i++;
	 					j++;
					}
					else
					{
						i = i-j+1;
						j = 0;
					}
				} while(j<demT && i < strlen(p->data.malop));
				if(j >= demT)
					goto here;
				else		// ko tim thay tren ma lop thi chuyen sang tim tren ma sinh vien
				{
					char mangMSV[9];
					itoa(p->data.masv,mangMSV,10);
					int i=0,j=0;
					do
					{
						if(mangMSV[i] == b[j])
						{
			 				i++;
			 				j++;
						}
						else
						{
			 				i= i-j+1;
			 				j = 0;
						} 	
		   			} while(j < demT && i < strlen(mangMSV));
		   			if(j >= demT)
		   				goto here;
		  	 		else	// tuong tu,se tim tren ngay thang nam sinh
		   			{
		   				i=0,j=0;
						string ngaysinh="";
						char tamngay[4],tamthang[4],tamnam[6];
						itoa(p->data.tg.ngay,tamngay,10);
						ngaysinh+=tamngay;
						ngaysinh+="/";
						itoa(p->data.tg.thang,tamthang,10);
						ngaysinh+=tamthang;
						ngaysinh+="/";
						itoa(p->data.tg.nam,tamnam,10);
						ngaysinh+=tamnam;
						const char* day = ngaysinh.c_str();
						do
						{
							if(day[i] == b[j])
							{
								i++;
								j++;
							}
							else
							{
								i = i-j+1;
								j = 0;
							}
		   				} while(j<demT && i< strlen(day));
		   				if(j >= demT)
		   					goto here;
		   				else
		   				{
		   					i = 0, j = 0;
		   					string chuoitb ="";
		   					int a = p->data.diemtb*100;
		   					char tamNguyen[5],tamThapPhan[5];  
							int so;
							so = a/100; 		
		   					itoa(so,tamNguyen,10);
		   					chuoitb += tamNguyen;
		   					chuoitb += ".";
		   					itoa(a%(so*100),tamThapPhan,10);
		   					chuoitb+=tamThapPhan;
		   					const char* tamtb = chuoitb.c_str();
		   					do
		   					{
		   						if(tamtb[i] == b[j])
		   						{
		   							i++;
		   							j++;
								}
								else
								{
									i = i-j+1;
									j = 0;
								}
							} while(j < demT && i < strlen(tamtb));
							if( j >= demT)
								goto here;
		   				}
					}
		 		}
			}
			else 
			{
				here: dem++;	
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,dem,179,p->data.hoten,179,p->data.malop,179,p->data.masv,179,p->data.tg.ngay,p->data.tg.thang,p->data.tg.nam,179,p->data.diemtb,186);
				printf("%c",204);	
				for(int j=0;j<74;j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
			}
		}
		if(dem == 0)
		{
			SetColor(3);
			gotoxy(0,4);
			printf("%c",200);
			for(int j=0;j<73;j++)
			{
				printf("%c",205);
			}
			printf("%c",188);
			SetColor(13);
			cout<<endl<<"nhap ESC de thoat viec in danh sach";
		}
		else
		{
			gotoxy(0,whereY());
			printf("%c",200);
			for(int j=0;j<74;j++)
			{
				printf("%c",205);
			}
			printf("%c",188);
			SetColor(13);
			cout<<endl<<"nhap ESC de thoat viec in danh sach";		
		}
		}
	}
}
//tim kiem nhi phan
void tknhiphan(list l,int n)
{
	if(n == 1) // ho ten
	{
		sapxepchon(l,2);
		getch();
		system("cls");
		list ltam,ldubi;
		initList(ltam),initList(ldubi);
		ltam = l;
		string tenTK;
		node *bottom,*top,*position;
		bottom = ltam.dau, top = ltam.cuoi;
		position = bottom;	
 		char ktu;
		 //	inDS(l);
 		keBang(80,1,30,2);
 	 	SetColor(6);
		printf("\n\t\t\t\tDANH SACH SINH VIEN\n");
		SetColor(3);
		printf("%c",201); // goc tren trai
		for(int j =0;j<74;j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i=0;i<74;i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int y = whereY();
		int stt =0;
		tenTK = nhapTen(81,2);
		gotoxy(0,y);
 		while(bottom != top)
 		{
 			node *p;
		 	int vtri = 1;
		 	p = ltam.dau;
		 	while(p != ltam.cuoi) // gia tri cua bien vtri la so phan tu cua danh sach
		 	{
		 		vtri++;
		 		p = p->next;
		 	}
		 	position  = bottom;
			int dem = 1;
			
			while(dem++ < (1 + vtri)/2) 
				position = position->next;
			const char * ten = tenTK.c_str();
			char *chuoiTen = new char();
			strcpy(chuoiTen,ten);
			if(stricmp(position->data.hoten,ten) == 0)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,position->data.hoten,179,position->data.malop,179,position->data.masv,179,position->data.tg.ngay,position->data.tg.thang,position->data.tg.nam,179,position->data.diemtb,186);
				printf("%c",204);
				for(int j=0;j<74;j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
				node *q;
				q = position;
				for(q;q != top;q=q->next)   //neu tim duoc cai can tim thi phai bo node do ra va tiep tuc tim tiep xem co them cai nao nua khong
				{
					hoanvi(&q->data,&q->next->data);
					if(q->next == top)
					{
						top = q;
						break;
					}
				}	
			}
			else if(stricmp(tachCuoi(position->data.hoten),tachCuoi(chuoiTen)) < 0 || stricmp(tachCuoi(position->data.hoten),tachCuoi(chuoiTen)) == 0 && stricmp(position->data.hoten,ten) < 0)
			{
				bottom = position->next;
			}
			else
			{
				node *q;
				q = bottom;
				while(q->next != top) q=q->next;
				top = q;
			}
			p = bottom;
			initList(ldubi);
			while(p != top)
			{
				themcuoi(ldubi,p);
				p = p->next;
			}
			themcuoi(ldubi,p);  // danh sach du bi luu vi tri bottom va top moi
			initList(ltam);
			ltam = ldubi; // gan list tam = list du bi de chuan bi cho viec tim kiem tiep theo	
		}
		if(bottom == top)
		{
			const char * ten = tenTK.c_str();
			if(stricmp(bottom->data.hoten,ten) == 0)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,bottom->data.hoten,179,bottom->data.malop,179,bottom->data.masv,179,bottom->data.tg.ngay,bottom->data.tg.thang,bottom->data.tg.nam,179,bottom->data.diemtb,186);
				printf("%c",204);
				for(int j=0;j<74;j++)
				{
					printf("%c",205);
				}
					printf("%c",185);
			}
		}	
		gotoxy(0,whereY());
		SetColor(3);
		printf("%c",200);
		for(int j=0;j<74;j++)
		{
			printf("%c",205);		
		}
		printf("%c",188);
		SetColor(13);
		cout<<endl<<"nhap ESC de thoat viec in danh sach";
		while(1)
		{
			ktu = getch();
			if(ktu == 27)
			break;
		}
	}
	else if(n == 2) // ma sinh vien
	{
		sapxepchon(l,1);
		getch();
		system("cls");
		list ltam,ldubi;
		int findMSV;
		initList(ltam),initList(ldubi);
		ltam = l;
		node *bottom,*top,*position;
		bottom = ltam.dau, top = ltam.cuoi;
		position = bottom;
		char ktu;
		keBang(80,1,30,2);
		SetColor(6);
		printf("\n\t\t\t\tDANH SACH SINH VIENn\n");
		SetColor(3);
		printf("%c",201); // goc tren trai
		for(int j =0;j<74;j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i=0;i<74;i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int y = whereY();
		int stt =0;
		SetColor(6);
		findMSV = nhapmasv(81,2);
		gotoxy(0,y);
 		while(bottom != top)
 		{
 			node *p;
			int vtri = 1;
			p = ltam.dau;
			while(p != ltam.cuoi) // gia tri cua bien vtri la so phan tu cua danh sach
		 	{
		 		vtri++;
		 		p = p->next;
		 	}
		 	position  = bottom;
		 	int dem = 1;
		 	while(dem++ <(1 +vtri)/2) position = position->next;
			if(position->data.masv == findMSV)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,position->data.hoten,179,position->data.malop,179,position->data.masv,179,position->data.tg.ngay,position->data.tg.thang,position->data.tg.nam,179,position->data.diemtb,186);
				printf("%c",204);
				for(int j=0;j<74;j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
				node *q;
				q = position;
				for(q;q != top;q=q->next)   //neu tim duoc cai can tim thi phai bo node do ra va tiep tuc tim tiep xem co them cai nao nua khong
				{
					hoanvi(&q->data,&q->next->data);
					if(q->next == top)
					{
						top = q;
						break;
					}
				}	
			}
			else if(position->data.masv < findMSV)
			{
				bottom = position->next;
			}
			else
			{
				node *q;
				q = bottom;
				while(q->next != top) q=q->next;
				top = q;
			}
			p = bottom;
			initList(ldubi);
			while(p != top)
			{
				themcuoi(ldubi,p);
				p = p->next;
				
			}
			themcuoi(ldubi,p);  // danh sach du bi luu vi tri bottom va top moi
			initList(ltam);
			ltam = ldubi; // gan list tam = list du bi de chuan bi cho viec tim kiem tiep theo	
		}
		if(bottom == top)
		{
			if(bottom->data.masv == findMSV)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,bottom->data.hoten,179,bottom->data.malop,179,bottom->data.masv,179,bottom->data.tg.ngay,bottom->data.tg.thang,bottom->data.tg.nam,179,bottom->data.diemtb,186);
				printf("%c",204);
				for(int j=0;j<74;j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
			}
		}
		gotoxy(0,whereY());
		SetColor(3);
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{
			printf("%c",205);			
		}
		printf("%c",188);
		SetColor(13);
		cout<<endl<<"nhap ESC de thoat viec in danh sach";
		while(1)
		{
			ktu = getch();
			if(ktu == 27)
			break;
		}	
	}
	else if( n == 3) // Ma Lop
	{
	 	node *min,*p,*q;
	 	for(p=l.dau;p->next != NULL;p=p->next)
	 	{
	 		min = p;
	 		for(q = p->next;q!=NULL;q=q->next)
	 		{
	 			if(stricmp(q->data.malop,min->data.malop) < 0)
	 			min = q;
			}
			 hoanvi(&p->data,&min->data);
		} 
		system("cls");
		list ltam,ldubi;
		initList(ltam),initList(ldubi);
		ltam = l;
		string tenLop;
		node *bottom,*top,*position;
		bottom = ltam.dau, top = ltam.cuoi;
		position = bottom;
 		char ktu;
 		keBang(80,1,30,2);
 		SetColor(6);
		printf("\n\t\t\t\tDANH SACH SINH VIEN\n");
		SetColor(3);
		printf("%c",201); // goc tren trai
		for(int j =0;j<74;j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i=0;i<74;i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int y = whereY();
		int stt =0;
		tenLop = nhapMaLop(81,2);
		gotoxy(0,y);
 		while(bottom != top)
 		{		
 			node *p;
			int vtri = 1;
			p = ltam.dau;
			while(p != ltam.cuoi) // gia tri cua bien vtri la so phan tu cua danh sach
			{
		 		vtri++;
		 		p = p->next;
		 	}
		 	position  = bottom;
		 	int dem = 1;
		 	while(dem++ <(1 +vtri)/2) position = position->next;
			const char * ten = tenLop.c_str();
			char *chuoiTen = new char();
			strcpy(chuoiTen,ten);
			if(stricmp(position->data.malop,ten) == 0)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,position->data.hoten,179,position->data.malop,179,position->data.masv,179,position->data.tg.ngay,position->data.tg.thang,position->data.tg.nam,179,position->data.diemtb,186);
				printf("%c",204);
				for(int j=0;j<74;j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
				node *q;
				q = position;
				for(q; q != top;q = q->next)   //neu tim duoc cai can tim thi phai bo node do ra va tiep tuc tim tiep xem co them cai nao nua khong
				{
					hoanvi(&q->data,&q->next->data);
					if(q->next == top)
					{
						top = q;
						break;
					}
				}
			}
			else if(stricmp(position->data.malop,ten) < 0)
			{
				bottom = position->next;
			}
			else
			{
				node *q;
				q = bottom;
				while(q->next != top) q=q->next;	
				top = q;
			}
			p = bottom;
			initList(ldubi);
			while(p != top)
			{
				themcuoi(ldubi,p);
				p = p->next;	
			}
			themcuoi(ldubi,p);  // danh sach du bi luu vi tri bottom va top moi
			initList(ltam);
			ltam = ldubi; // gan list tam = list du bi de chuan bi cho viec tim kiem tiep theo	
		}
		if(bottom == top)
		{
			const char * ten = tenLop.c_str();
			if(stricmp(bottom->data.malop,ten) == 0)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,bottom->data.hoten,179,bottom->data.malop,179,bottom->data.masv,179,bottom->data.tg.ngay,bottom->data.tg.thang,bottom->data.tg.nam,179,bottom->data.diemtb,186);
				printf("%c",204);
				for(int j=0;j<74;j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
			}
		}
		gotoxy(0,whereY());
		SetColor(3);
		printf("%c",200);
		for(int j=0;j<74;j++)
		{
			printf("%c",205);		
		}
		printf("%c",188);
		SetColor(13);
		cout<<endl<<"nhap ESC de thoat viec in danh sach";
		while(1)
		{
			ktu = getch();
			if(ktu == 27)
			break;
		}
	}
	else if(n == 4) // nGAY SINH
	{
		sapxepchon(l,3);
		getch();
		system("cls");
		date findTime;
		list ltam,ldubi;
		initList(ltam),initList(ldubi);
		ltam = l;
		node *bottom,*top,*position;
		bottom = ltam.dau, top = ltam.cuoi;
		position = bottom;
		char ktu;
		keBang(80,1,3,2);
		keBang(85,1,3,2);
		keBang(90,1,5,2);
		SetColor(6);
		printf("\n\t\t\t\tDANH SACH SINH VIEN\n");
		SetColor(3);
		printf("%c",201); // goc tren trai
		for(int j =0;j<74;j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i = 0; i < 74; i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int y = whereY();
		int stt =0;
		findTime.ngay = nhapNgaySinh(81,2);
		findTime.thang = nhapThangSinh(86,2);
		findTime.nam = nhapNamSinh(91,2);
		gotoxy(0,y);
 		while(bottom != top)
 		{
	 		node *p;
			int vtri = 1;
			p = ltam.dau;
			while(p != ltam.cuoi) // gia tri cua bien vtri la so phan tu cua danh sach
		 	{
		 		vtri++;
		 		p = p->next;
		 	}
		 	position  = bottom;
		 	int dem = 1;
		 	while(dem++ <(1 +vtri)/2) position = position->next;
			if(position->data.tg.nam == findTime.nam && position->data.tg.thang == findTime.thang && position->data.tg.ngay == findTime.ngay)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,position->data.hoten,179,position->data.malop,179,position->data.masv,179,position->data.tg.ngay,position->data.tg.thang,position->data.tg.nam,179,position->data.diemtb,186);
				printf("%c",204);
				for(int j = 0;j < 74;j ++)
				{
					printf("%c",205);
				}
				printf("%c",185);
				node *q;
				q = position;
				for(q; q != top;q = q->next)   //neu tim duoc cai can tim thi phai bo node do ra va tiep tuc tim tiep xem co them cai nao nua khong
				{
					hoanvi(&q->data,&q->next->data);
					if(q->next == top)
					{
						top = q;
						break;
					}
				}
			}
			else if(position->data.tg.nam < findTime.nam  || position->data.tg.nam == findTime.nam && position->data.tg.thang < findTime.thang||position->data.tg.nam == findTime.nam && position->data.tg.thang == findTime.thang && position->data.tg.ngay < findTime.ngay)
			{
				bottom = position->next;
			}
			else
			{
				node *q;
				q = bottom;
				while(q->next != top) q=q->next;
				top = q;
			}
			p = bottom;
			initList(ldubi);
			while(p != top)
			{
				themcuoi(ldubi,p);
				p = p->next;
			}
			themcuoi(ldubi,p);  // danh sach du bi luu vi tri bottom va top moi
			initList(ltam);
			ltam = ldubi; // gan list tam = list du bi de chuan bi cho viec tim kiem tiep theo	
		}
		if(bottom == top)
		{
			
			if(bottom->data.tg.nam == findTime.nam && bottom->data.tg.thang == findTime.thang && bottom->data.tg.ngay == findTime.ngay)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,bottom->data.hoten,179,bottom->data.malop,179,bottom->data.masv,179,bottom->data.tg.ngay,bottom->data.tg.thang,bottom->data.tg.nam,179,bottom->data.diemtb,186);
				printf("%c",204);
				for(int j = 0;j < 74; j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
			}
		}
		gotoxy(0,whereY());
		SetColor(3);
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{
			printf("%c",205);	
		}
		printf("%c",188);
		SetColor(13);
		cout<<endl<<"Nhap ESC de thoat viec in danh sach";
		while(1)
		{
			ktu = getch();
			if(ktu == 27)
			break;
		}
	}
	else if( n == 5) // Theo Diem TB
	{
	 	sapxepchon(l,4);
		getch();
		system("cls");
		list ltam,ldubi;
		float findDiem;
		initList(ltam),initList(ldubi);
		ltam = l;
		node *bottom,*top,*position;
		bottom = ltam.dau, top = ltam.cuoi;
		position = bottom;
		char ktu;
		keBang(80,1,30,2);
		SetColor(6);
		printf("\n\t\t\t\tDANH SACH SINH VIEN\n");
		SetColor(3);
		printf("%c",201); // goc tren trai
		for(int j =0;j<74;j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i=0;i<74;i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int y = whereY();
		int stt =0;
		SetColor(6);
		findDiem = nhapDiem(81,2);
		gotoxy(0,y);
 		while(bottom != top)
 		{	
 			node *p;
			int vtri = 1;
			p = ltam.dau;
		 	while(p != ltam.cuoi) // gia tri cua bien vtri la so phan tu cua danh sach
		 	{
		 		vtri++;
		 		p = p->next;
		 	}
		 	position  = bottom;
			int dem = 1;
		 	while(dem++ <(1 +vtri)/2) position = position->next;
			if(position->data.diemtb == findDiem)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,position->data.hoten,179,position->data.malop,179,position->data.masv,179,position->data.tg.ngay,position->data.tg.thang,position->data.tg.nam,179,position->data.diemtb,186);
				printf("%c",204);
				for(int j = 0; j < 74; j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
				node *q;
				q = position;
				for(q;q != top;q=q->next)   //neu tim duoc cai can tim thi phai bo node do ra va tiep tuc tim tiep xem co them cai nao nua khong
				{
					hoanvi(&q->data,&q->next->data);
					if(q->next == top)
					{
						top = q;
						break;
					}
				}
			}
			else if(position->data.diemtb < findDiem)
			{
				bottom = position->next;
			}
			else
			{
				node *q;
				q = bottom;
				while(q->next != top) q=q->next;
				top = q;
			}
			p = bottom;
			initList(ldubi);
			while(p != top)
			{
				themcuoi(ldubi,p);
				p = p->next;	
			}
			themcuoi(ldubi,p);  // danh sach du bi luu vi tri bottom va top moi
			initList(ltam);
			ltam = ldubi; // gan list tam = list du bi de chuan bi cho viec tim kiem tiep theo	
		}
		if(bottom == top)
		{
			if(bottom->data.diemtb == findDiem)
			{
				SetColor(3);			
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,++stt,179,bottom->data.hoten,179,bottom->data.malop,179,bottom->data.masv,179,bottom->data.tg.ngay,bottom->data.tg.thang,bottom->data.tg.nam,179,bottom->data.diemtb,186);
				printf("%c",204);
				for(int j = 0; j < 74; j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
			}
		}
		gotoxy(0,whereY());
		SetColor(3);
		printf("%c",200);
		for(int j=0;j<74;j++)
		{
			printf("%c",205);
		}
		printf("%c",188);
		SetColor(13);
		cout<<endl<<"Nhap ESC de thoat viec in danh sach";
		while(1)
		{
			ktu = getch();
			if(ktu == 27)
			break;
		}	
	}
}

// xoa ky tu
void xoakitu(char *xau,int vitri , int soluong)
{
    if (vitri + soluong > strlen(xau)+1) xau[0] = NULL;
    else
    {
        while (xau[vitri+soluong] != NULL)
        {
            xau[vitri] = xau[vitri+soluong];
            vitri++;
        }
        xau[vitri]=NULL;
    }
}
// Ham thong ke
// 1. Hoc luc
// 2. Lop
// 3. Ten
// 4. Ho
void thongKe(list l, int n)
{
	node *p,*q;
	//HANDLE hOut;
	system("cls");
	//hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(n == 1) // Theo hoc luc
	{	
		SetColor(14);
		gotoxy(30,1);
		cout<< "HOC SINH GIOI";
		gotoxy(0,whereY()+1);
		SetColor(3);
		printf("%c",201); // goc tren trai
		for(int j =0;j<74;j++)
		{
			printf("%c",205); // ong ngang
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i=0;i<74;i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		//sap xep truoc khi thong ke
		for(p = l.dau; p->next != NULL; p = p->next)
		{
			for(q = p->next; q != NULL; q = q->next)
			{
				if(q->data.diemtb > p->data.diemtb)
				{
					hoanvi(&p->data,&q->data);
				}
			}
		}
		int demSVGioi = 0;
		for(p = l.dau; p != NULL; p = p->next)
		{
			if(p->data.diemtb >= 8.0)
			{
				++demSVGioi;
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,demSVGioi,179,p->data.hoten,179,p->data.malop,179,p->data.masv,179,p->data.tg.ngay,p->data.tg.thang,p->data.tg.nam,179,p->data.diemtb,186);
				printf("%c",204);	
				for(int j = 0; j < 74; j++)
				{
					printf("%c", 205);
				}
				printf("%c", 185);
			}
		}
		gotoxy(0,whereY());
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{	
			printf("%c",205);		
		}
		printf("%c",188);
		SetColor(14);
		gotoxy(30,whereY()+2);
		cout<<"HOC SINH KHA";
		SetColor(3);
		gotoxy(0,whereY()+1);
		printf("%c",201); // goc tren trai
		for(int j = 0; j < 74; j++)
		{
			printf("%c", 205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i = 0; i < 74; i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int demSVKha = 0;
		for(p = l.dau; p != NULL; p = p->next)
		{
			if(p->data.diemtb < 8 && p->data.diemtb >= 6.5)
			{
				++demSVKha;
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,demSVKha,179,p->data.hoten,179,p->data.malop,179,p->data.masv,179,p->data.tg.ngay,p->data.tg.thang,p->data.tg.nam,179,p->data.diemtb,186);
				printf("%c",204);	
				for(int j = 0; j < 74; j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
			}				
		}
		gotoxy(0,whereY());
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{	
			printf("%c", 205);				
		}
		printf("%c", 188);
		//hoc sinh trung binh
		SetColor(14);
		gotoxy(30,whereY()+2);
		cout<<"HOC SINH TRUNG BINH";
		SetColor(3);
		gotoxy(0,whereY()+1);
		printf("%c",201); // goc tren trai
		for(int j = 0; j < 74; j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i = 0; i < 74; i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int demSVTrungBinh = 0;
		for(p = l.dau; p != NULL; p = p->next)
		{
			if(p->data.diemtb < 6.5 && p->data.diemtb >= 5)
			{
				++demSVTrungBinh;
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,demSVTrungBinh,179,p->data.hoten,179,p->data.malop,179,p->data.masv,179,p->data.tg.ngay,p->data.tg.thang,p->data.tg.nam,179,p->data.diemtb,186);
				printf("%c",204);	
				for(int j = 0; j < 74; j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
			}				
		}
		gotoxy(0,whereY());
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{	
			printf("%c",205);		
		}
		printf("%c",188);
		// hoc sinh yeu
		SetColor(14);
		gotoxy(30,whereY()+2);
		cout<<"HOC SINH YEU";
		SetColor(3);
		gotoxy(0,whereY()+1);
		printf("%c",201); // goc tren trai
		for(int j = 0; j < 74; j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i = 0; i < 74; i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int demSVYeu = 0;
		for(p = l.dau; p != NULL; p = p->next)
		{
			if(p->data.diemtb <5)
			{
				++demSVYeu;
				printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,demSVYeu,179,p->data.hoten,179,p->data.malop,179,p->data.masv,179,p->data.tg.ngay,p->data.tg.thang,p->data.tg.nam,179,p->data.diemtb,186);
				printf("%c",204);	
				for(int j = 0;j < 74;j++)
				{
					printf("%c",205);
				}
				printf("%c",185);
			}				
		}
		gotoxy(0,whereY());
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{	
			printf("%c",205);				
		}
		printf("%c",188);	
	// Bang tong hop
		// Tinh ty le
		int tongSV = demSVGioi + demSVKha + demSVTrungBinh + demSVYeu;		
		float tyleGioi = (1.0*demSVGioi/tongSV) * 100;
		float tyleKha = (1.0*demSVKha/tongSV) * 100;
		float tyleTB = (1.0*demSVTrungBinh/tongSV) * 100;
		float tyleYeu = (1.0*demSVYeu/tongSV) * 100;		
		SetColor(14);
		gotoxy(30,whereY()+2);
		cout<<"BANG TONG HOP";
		SetColor(3);
		gotoxy(0,whereY()+1);
		printf("%c",201); // goc tren trai
		for(int j = 0; j < 74; j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%c      GIOI       %c       KHA       %c      TRUNG BINH     %c       YEU      %c\n",186,179,179,179,186);
		printf("%c",204);
		for(int i = 0; i < 74; i++)
		{
			printf("%c",196);
		}
		printf("%c",185);
		gotoxy(0,whereY()+1);
		printf("%c   SL   %c   TL   %c   SL   %c   TL   %c    SL    %c   TL     %c   SL   %c  TL   %c\n",186,179,179,179,179,179,179,179,186);
		printf("%c",204);
		for(int i = 0; i < 74; i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		gotoxy(0,whereY()+1);
		printf("%c%-8d%c%-8.2f%c%-8d%c%-8.2f%c%-10d%c%-10.2f%c%-8d%c%-7.2f%c\n",186,demSVGioi,
		179,tyleGioi,179,demSVKha,179, tyleKha,179,demSVTrungBinh,179, tyleTB, 179,demSVYeu,179, tyleYeu, 186);
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{	
			printf("%c",205);				
		}
		printf("%c",188);
		printf("Nhan ESC de quay lai menu chinh");	
	}
	// Thong ke hoc sinh cung lop
	else if(n == 2)
	{
		int dem;
		SetColor(14);
		gotoxy(30,1);
		cout<<"HOC SINH CUNG LOP";
		SetColor(3);
		gotoxy(0,whereY()+1);
		printf("%c",201); // goc tren trai
		for(int j = 0; j < 74; j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i = 0; i < 74; i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		dem = 0;
		int color = 3;		
		for(p = l.dau; p != NULL; p = p->next)
		{
			string tamP;
			tamP = p->data.malop;
			for(q = p->next; q != NULL; q = q->next)
			{
				string tamQ;
				tamQ = q->data.malop;
				if( tamP == tamQ)
				{
					p = p->next;
					hoanvi(&p->data,&q->data);
				}
			}		
		}	
		node *current;
		current = l.dau->next;
		p = l.dau;
		while(p!=NULL)
		{	
			SetColor(color);
			++dem;
			printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,dem,179,p->data.hoten,179,p->data.malop,179,p->data.masv,179,p->data.tg.ngay,p->data.tg.thang,p->data.tg.nam,179,p->data.diemtb,186);
			printf("%c",204);	
			for(int j = 0; j < 74; j++)
			{
				printf("%c",205);
			}
			printf("%c",185);					
			if(current->next == NULL)
				break;
			current = p->next;
			if(strcmp(p->data.malop,current->data.malop) != 0)
			{
				color++;
			}
			p = p->next;						
		}	
		gotoxy(0,whereY());
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{	
			printf("%c",205);				
		}
		printf("%c",188);
		printf("Nhan ESC de quay lai menu chinh");
	}
	else if(n == 3) // Cung ten
	{
		SetColor(14);
		gotoxy(30,whereY()+2);
		cout<<"HOC SINH CUNG TEN";
		SetColor(3);
		gotoxy(0,whereY()+1);
		printf("%c",201); // goc tren trai
		for(int j = 0; j < 74; j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i = 0; i < 74;i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int dem;
		dem = 0;
		int color =3;
		for(p=l.dau; p!=NULL;p=p->next)
		{			
			for(q =p->next;q!=NULL;q=q->next)
			{			
				if(stricmp(tachCuoi(q->data.hoten),tachCuoi(p->data.hoten)) == 0)
				{
					p = p->next;
					hoanvi(&p->data,&q->data);
				}
			}
		}
		p = l.dau;
		node *current = l.dau;
		while(p!=NULL)
		{	
			SetColor(color);
			++dem;
			printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,dem,179,p->data.hoten,179,p->data.malop,179,p->data.masv,179,p->data.tg.ngay,p->data.tg.thang,p->data.tg.nam,179,p->data.diemtb,186);
			printf("%c",204);	
			for(int j = 0; j < 74; j++)
			{
				printf("%c",205);
			}
			printf("%c",185);
			if(current->next == NULL)
				break;
			current = p->next;
			if(stricmp(tachCuoi(p->data.hoten),tachCuoi(current->data.hoten))!= 0)
			{
				color++;
			}
			p = p->next;				
		}
		gotoxy(0,whereY());
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{	
			printf("%c",205);			
		}
		printf("%c",188);
		printf("Nhan ESC de quay lai menu chinh");	
	}
	else if(n == 4) // Sinh vien cung ho
	{
		SetColor(14);
		gotoxy(30,whereY()+2);
		cout<<"HOC SINH CUNG HO";
		SetColor(3);
		gotoxy(0,whereY()+1);
		printf("%c",201); // goc tren trai
		for(int j = 0; j < 74; j++)
		{
			printf("%c",205);
		}
		printf("%c\n",187);
		printf("%cSTT%c        HO VA TEN       %c   MA LOP   %c   Ma SV  %c NGAY SINH  %c DIEM TB%c\n",186,179,179,179,179,179,186);
		printf("%c",204);
		for(int i = 0; i < 74; i++)
		{
			printf("%c",205);
		}
		printf("%c",185);
		int dem = 0;
		int color =3;
		for(p = l.dau; p != NULL; p = p->next)
		{	
			for(q = p->next; q!= NULL; q = q->next)
			{			
				if(stricmp(layDau(q->data.hoten),layDau(p->data.hoten)) == 0)
				{
					p = p->next;
					hoanvi(&p->data,&q->data);
				}
			}
		}
		dem = 0;
		p = l.dau;
		node *current = l.dau;
		while(p!=NULL)
		{	
			SetColor(color);
			++dem;
			printf("\n%c %-2d%c%24s%c % -10s %c% 8d %c %-2d\/%2d\/%-4d %c%7.2f %c\n",186,dem,179,p->data.hoten,179,p->data.malop,179,p->data.masv,179,p->data.tg.ngay,p->data.tg.thang,p->data.tg.nam,179,p->data.diemtb,186);
			printf("%c",204);	
			for(int j = 0; j < 74;j++)
			{
				printf("%c",205);
			}
			printf("%c",185);					
			if(current->next == NULL)
				break;
			current = p->next;
			if(stricmp(layDau(p->data.hoten),layDau(current->data.hoten)) != 0)
			{
				color++;
			}
			p = p->next;				
		}
		gotoxy(0,whereY());
		printf("%c",200);
		for(int j = 0; j < 74; j++)
		{	
			printf("%c",205);			
		}
		printf("%c",188);	
	}
//	else if (n == 5)// Ve bieu do
//	{
//		// Phan nay la ve cai khung
//		gotoxy(20, 4);printf("^");
//		gotoxy(17, 3);printf("(%%)");
//		gotoxy(20, 25);printf("%c", 192);
//		for (int i = 21; i < 80; i++)
//		{
//			gotoxy(i, 25);printf("%c", 196);
//		}
//		for (int i = 5; i < 25; i++)
//		{
//			gotoxy(20, i);printf("%c", 179);
//		}
//		gotoxy(80, 26);printf("(Hoc luc)");
//		gotoxy(80, 25);printf(">");
//		for (int i = 30; i < 70; i = i + 12)
//		{
//			gotoxy(i, 25);
//			printf("%c", 193);
//			if (i == 30)
//			{
//				gotoxy(i - 1, 26);printf("Gioi");
//			}
//			if (i == 42)
//			{
//				gotoxy(i-1, 26);printf("Kha");
//			}
//			if (i == 54)
//			{
//				gotoxy(i - 1, 26);printf("TB");
//			}
//			if (i == 66)
//			{
//				gotoxy(i - 1, 26);printf("Yeu");
//			}
//		}
//		int PhanTram = 100;
//		for (int i = 5; i < 25; i = i + 4)
//		{
//			gotoxy(20, i);printf("%c", 197);
//			gotoxy(16, i);printf("%d%%", PhanTram);
//			PhanTram -= 20;
//		}
//		gotoxy(17, 25); printf("0%%");
//		gotoxy(35, 28); printf("BIEU DO THONG KE HOC LUC SINH VIEN");
//		gotoxy(35, 29); printf("Nhan ESC de quay lai menu chinh");
//		// Ket thuc ve khung
//		//sap xep truoc khi thong ke
//		for(p = l.dau; p->next != NULL; p = p->next)
//		{
//			for(q = p->next; q != NULL; q = q->next)
//			{
//				if(q->data.diemtb > p->data.diemtb)
//				{
//					hoanvi(&p->data,&q->data);
//				}
//			}
//		}
//		int demSVGioi = 0;
//		for(p = l.dau; p != NULL; p = p->next)
//		{
//			if(p->data.diemtb >= 8.0)
//			{
//				++demSVGioi;				
//			}
//		}
//		int demSVKha = 0;
//		for(p = l.dau; p != NULL; p = p->next)
//		{
//			if(p->data.diemtb < 8 && p->data.diemtb >= 6.5)
//			{
//				++demSVKha;	
//			}				
//		}
//		//hoc sinh trung binh
//		int demSVTrungBinh = 0;
//		for(p = l.dau; p != NULL; p = p->next)
//		{
//			if(p->data.diemtb < 6.5 && p->data.diemtb >= 5)
//			{
//				++demSVTrungBinh;
//			}				
//		}
//		// hoc sinh yeu
//		int demSVYeu = 0;
//		for(p = l.dau; p != NULL; p = p->next)
//		{
//			if(p->data.diemtb <5)
//			{
//				++demSVYeu;
//			}				
//		}
//	// Bang tong hop
//		// Phan nay la tinh ty le % va ve
//		int tongSV = demSVGioi + demSVKha + demSVTrungBinh + demSVYeu;
//		float pt_gioi, pt_kha, pt_tb, pt_yeu;	
//		pt_gioi = (1.0*demSVGioi/tongSV)*100;
//		pt_kha = (1.0*demSVKha/tongSV)*100;
//		pt_tb = (1.0*demSVTrungBinh/tongSV)*100;
//		pt_yeu = (1.0*demSVYeu/tongSV)*100;		
//		SetColor(14);
//		int Tang = 24;
//		//Yeu
//		SetColor(12);
//		for (float j = 0; j < pt_gioi; (float)(j += 6))
//		{
//			gotoxy(29, Tang);printf("%c%c%c", 178, 178, 178);
//			Tang -= 1;
//		}
//		SetColor(7);
//		gotoxy(28, Tang); printf("%0.2f%%", pt_gioi);
//		///Tb
//		Tang = 24;
//		SetColor(8);
//		for (float j = 0; j < pt_kha; (float)(j += 5.5))
//		{
//			gotoxy(41, Tang);printf("%c%c%c", 178, 178, 178);
//			Tang -= 1;
//		} SetColor(7);
//		gotoxy(40, Tang);printf("%0.2f%%", pt_kha);
//		///Kha
//		Tang = 24;
//		SetColor(14);
//		for (float j = 0; j < pt_tb; (float)(j += 5.5))
//		{
//			gotoxy(53, Tang);printf("%c%c%c", 178, 178, 178);
//			Tang -= 1;
//		} SetColor(7);
//		gotoxy(52, Tang);printf("%0.2f%%", pt_tb);
//		///Gioi
//		Tang = 24;
//		SetColor(9);
//		for (float j = 0; j < pt_yeu; (float)(j += 5.5))
//		{
//			gotoxy(65, Tang);printf("%c%c%c", 178, 178, 178);
//			Tang -= 1;
//		} SetColor(7);
//		gotoxy(64, Tang);printf("%0.2f%%", pt_yeu);		
//	}
	// dieu chinh con tro
	char ktu;
	int vtriX,vtriY;
	int count = 0;
	int dosau = whereY();
	keBang(100,0,2,whereY()+20);
	gotoxy(101,1);
	SetColor(14);
	printf("%c",219);
	while(1)
	{
		ktu = getch();
		if(ktu == 27)
		break;
		switch(ktu)
		{
			case 80:
			if(count == dosau/20+1)
			{
				gotoxy(whereX()-1,whereY());
				cout<<" ";
				gotoxy(whereX()-1,1);
				printf("%c",219);
				count = 0;					
			}
			else
			{
				gotoxy(whereX()-1,whereY());
				cout<<" ";
				count++;
				gotoxy(whereX()-1,whereY()+20);
				printf("%c",219);
			}
			break;
			case 72:
			if(count == 0)
			{
				gotoxy(whereX()-1,whereY());
				cout<<" ";
				gotoxy(whereX()-1,20*(dosau/20+1));
				printf("%c",219);
				count = dosau/20+1;
			}
			else
			{
				count--;
				gotoxy(whereX()-1,whereY());
				cout<<" ";
				gotoxy(whereX()-1,whereY()-20);
				printf("%c",219);		
			}
			break;	
		}
	}
}
//sua sinh vien
void suaSV(list &l,sv *q)
{
	char ktu;
//	HANDLE hOut;
//	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int stt,dem =1;
	node *p;
	p = l.dau;
	do
	{
		inDS(l);
		printf("\nBan muon sua sinh vien thu may:");
		cin>>stt;
	}while(stt>demsv() || stt<=0);
	while(p!=NULL && ++dem <=stt) p = p->next;
	veLaiKhung();
	char ten[26];
	int masv;
	float diemtb;
	date time;
	string Name;
	string mlop;
	keBang(34,15,50,20);
	gotoxy(36,17);
	SetColor(13);
	cout<< "Ho ten ";
	keBang(49,16,30,2);
	gotoxy(50,17); // con tro len 1 don vi cho vua cai bang
	SetColor(6);
	cout<< p->data.hoten;		
	gotoxy(36,20);	// quay con tro ve vi tri de in tieu de ma sv
	SetColor(13);	//mau chu ma sinh vien mau hong
	cout<< "Ma sinh vien";
	keBang(49,19,9,2);
	SetColor(6);
	gotoxy(50,20);
	cout<< p->data.masv;
	gotoxy(36,23);
	SetColor(13);
	cout<< "Ma lop";
	keBang(49,22,11,2);
	gotoxy(50,23);
	SetColor(6);
	cout<< p->data.malop;
	gotoxy(36,26);
	SetColor(13);
	cout<< "Ngay";
	keBang(49,25,3,2);
	gotoxy(50,26);
	SetColor(6);
	cout<<p->data.tg.ngay;
	gotoxy(54,26);
	SetColor(13);
	cout<< "Thang";
	keBang(60,25,3,2);
	gotoxy(61,26);
	SetColor(6);
	cout<< p->data.tg.thang;
	gotoxy(66,26);
	SetColor(13);
	cout<< "Nam";
	keBang(70,25,5,2);
	gotoxy(71,26);
	SetColor(6);
	cout<< p->data.tg.nam;
	SetColor(13);
	gotoxy(36,29);
	cout<< "Diem TB";
	keBang(49,28,5,2);
	gotoxy(50,29);
	SetColor(6);
	cout<< p->data.diemtb;
	gotoxy(25,37);
	cout<< "Nhap ESC de thoat viec nhap sinh vien,ENTER de sua thong tin";		
	gotoxy(50,17);
	int position = 0;
	int ktra0 = 0,ktra1 = 0,ktra2 = 0,ktra3 = 0,ktra4 = 0,ktra5 = 0,ktra6 =0;
	while(1)		
	{
		ktu = getch();
		switch(ktu)
		{		
			case 72:
				if(position == 0)
				{
					gotoxy(50,29);
					position = 6;												
				}
				else 
				{
					if(position == 4)
					{
						gotoxy(50,26);
						position = 3;
					}
					else if(position == 5)
					{
						gotoxy(61,26);
						position = 4;
					}
					else if(position == 6)
					{
						gotoxy(71,26);
						position = 5;
					}
					else if(position == 3)
					{
						gotoxy(50,23);
						position = 2;
					}
					else if(position == 2)
					{
						gotoxy(50,20);
						position = 1;
					}
					else if(position == 1)
					{
						gotoxy(50,17);
						position = 0;
					}
				}								
				break;
			case 80:
				if(position == 6)
				{
					gotoxy(50,17);
					position = 0;
				}
				else if(position == 5)
				{
					gotoxy(50,29);
					position = 6;													
				}
				else if(position == 4)
				{
					gotoxy(71,26);
					position = 5;
				}
				else if(position == 3)
				{
					gotoxy(61,26);
					position = 4;
				}
				else if(position == 2)
				{
					gotoxy(50,26);
					position = 3;
				}
				else if(position == 1)
				{
					gotoxy(50,23);
					position = 2;
				}
				else
				{
					gotoxy(50,20);
					position = 1;
				}
				break;
				case 13:
				if(position == 0)
				{
					Name = nhapTen(50,17);
					const char* mangName = Name.c_str();
					strcpy(q->hoten,mangName);
					ktra0 = 1;		
				}
				else if(position == 1)
				{
					q->masv = nhapmasv(50,20);
					ktra1 =1;	
				}
				else if(position == 2)
				{
					mlop = nhapMaLop(50,23);
					const char* MALOP = mlop.c_str();
					strcpy(q->malop,MALOP);
					ktra2 = 1;									
				}
				else if(position == 3)
				{
					if(ktra3 == 0)
					{
						q->tg.nam = p->data.tg.nam;	
						q->tg.thang = p->data.tg.thang;
						q->tg.ngay = nhapNgaySinh(50,26);
						xuLyThoiGian(&q->tg);
						ktra3 = 1;
					}
					else if(ktra3 == 1)
					{
						q->tg.ngay = nhapNgaySinh(50,26);
						xuLyThoiGian(&q->tg);
					}			
				}
				else if(position == 4)
				{
					if(ktra4 == 0)
					{
						q->tg.nam = p->data.tg.nam;
						q->tg.ngay = p->data.tg.ngay;
						q->tg.thang = nhapThangSinh(61,26);
						xuLyThoiGian(&q->tg);
						ktra4 =1;
					}
					else if(ktra4 == 1)
					{
						q->tg.thang = nhapThangSinh(61,26);
						xuLyThoiGian(&q->tg);
					}
				}					
				else if(position == 5)
				{
					if(ktra5 == 0)
					{
						q->tg.ngay = p->data.tg.ngay;
						q->tg.thang = p->data.tg.thang;
						q->tg.nam = nhapNamSinh(71,26);
						xuLyThoiGian(&q->tg);
						ktra5 =1;
					}
					else if(ktra5 == 1)
					{
						q->tg.nam = nhapNamSinh(71,26);
						xuLyThoiGian(&q->tg);
					}
				}
				else if(position == 6)
				{
					q->diemtb = nhapDiem(50,29);
					ktra6 = 1;
				}
				break;
		}
		if(ktu == 27)
		break;
	}
	if(ktra0 == 0)
	{
		strcpy(q->hoten,p->data.hoten);
	}
	if(ktra1 == 0)
	{
		q->masv = p->data.masv;
	}
	if(ktra2 == 0)
	{
		strcpy(q->malop,p->data.malop);
	}
	if(ktra3 == 0 && ktra4 == 0 && ktra5 == 0 )
	{
		q->tg.ngay = p->data.tg.ngay;
		q->tg.thang = p->data.tg.thang;
		q->tg.nam = p->data.tg.nam;
	}
	if(ktra6 == 0)
	{
		q->diemtb = p->data.diemtb;
	}
	hoanvi(&p->data,q);
	luufile(l);				
}

