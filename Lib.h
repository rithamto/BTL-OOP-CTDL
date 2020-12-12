#pragma once // tranh trung thu vien khi goi chong file
#include <stdio.h>
#include <conio.h>
#include<ctime> /* thu vien tra ve ho tro thoi gian thuc*/
#include "windows.h" 
#include <iostream>
//======= lay toa do x cua hien tai cua con tro =============
#define KEY_NONE	-1
using namespace std;
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//========= lay toa do y hien tai cua con tro =======
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
//============== di chuyen co tro toi vi tri co toa do (x,y) ==========
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//============= dat ma cho vat the =========
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x0013;
	wAttributes &= 0xfff0;
	wAttributes |= 0x0000;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== lam an con tro chuot ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//======= tra ve ka phim nguoi dung bam tu ban phim =========
int inputKey()
{
	if (kbhit()) // Kiem tra nguoi dung nhap phim bat ky hay khong
	{
		int key = getch();

		if (key == 224)
		{
			key = getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}

	return KEY_NONE;
}
// giao dien
void giaodien()
{
	
//	HANDLE hOut;
//    hOut = GetStdHandle(STD_OUTPUT_HANDLE);	
    char qc[] = "QUAN LY DANH SACH SINH VIEN   QUAN LY DANH SACH SINH VIEN   QUAN LY DANH SACH SINH VIEN";
    int dd = strlen(qc);
    char tam[100];
    strcpy(tam, qc); // Sao chep chuoi nay sang chuoi khac
    system("cls");
    char hien[30];
    int i = 0,m,n;
    while(!kbhit())
    {
    	for(m = 0; m < 10; m++)
    	{
    		SetColor(12);
    		gotoxy (30, m+5);
    		for(n=0;n<60;n++)
    		{
    			if(m==0||m==9||n==0||n==59)
    			{
    				printf("%c",16);
				}
				else
				{
					cout <<" ";		
				}				
			}
		cout<<endl;
	}
	Sleep(5);
	for(m = 0; m < 10; m++)
    {
    	SetColor(9);
    	gotoxy(30, m+5);
    	for(n = 0; n < 60; n++)
    	{
    		if(m==0||m==9||n==0||n==59)
    		{
    			printf("%c",17);
			}
			else
			{
				cout<<" ";	
			}					
		}
		cout<<endl;
	}
	Sleep(2);
    	strncpy (hien, qc+i, 30); // Cung la ham coppy
    	gotoxy(40,9);
    	SetColor(15);
    	cout<<hien;
    	Sleep(100);
    	i++;
    	if(i == dd) i =0;
	}
	getch();
	gotoxy(40,8);	
	SetColor(10);
	cout<<"           BTL OOP/CTDL & GT    ";
	gotoxy(38,9);
	SetColor(4);
	cout << "        QUAN LY DANH SACH SINH VIEN     ";
	gotoxy(38,10);
	SetColor(10);
	cout<<"Designer by KHANG & LAM & LINH & KHOI & KHIEM";
	gotoxy(38,11);
	SetColor(12);
	cout<<"                Lop: CNTT-K60    ";
}
// Ke bang
void keBang(int x, int y, int width, int height)
{
    SetColor(2);
	gotoxy(x,y);
    printf("%c",218); // goc tren trai
    for(int i = 1; i < width; i++)
	{
        gotoxy(x+i,y);
        printf("%c",196);
    }
    gotoxy(x+width, y); // goc tren phai
    printf("%c",191);
    for(int i = 1; i < height; i++)
	{
        gotoxy(x, y+i);
        printf("%c",179);
    }
    gotoxy(x, y+height); // goc duoi trai
    printf("%c",192);
    for(int i = 1; i < width; i++)
	{
        gotoxy(x+i, y+height);
        printf("%c",196);
    }
    gotoxy(x+width, y+height);  // goc duoi phai
    printf("%c",217);
    for(int i =1; i<height; i++)
	{
        gotoxy(x+width, y+i);
        printf("%c",179);
    } 
}
//Hien thi cac de muc
void veLaiKhung()
{
	system("cls");
    int m,n;
    for(m=0;m<10;m++)
    {
    	SetColor(9);
    	gotoxy(30,m+5);
    	for(n=0;n<60;n++)
    	{
    		if(m==0||m==9||n==0||n==59)
    		{
    			printf("%c",17);
			}
			else
			{
				cout<<" ";
			}		
		}
		cout<<endl;
	}
	gotoxy(40,9);
	SetColor(15);
	cout<<"    QUAN LY DANH SACH SINH VIEN    ";
		keBang(10,15,22,10);
	char *tenmuc[] = {"Hoc sinh moi","In thong tin","Sap Xep","Tim","Thong ke","Xoa","Chinh sua","Thoat"};
	for(int i = 1; i < 8; ++i)
	{
		gotoxy(15,16+i);
		SetColor(4);
		printf(tenmuc[i]);
	}
	gotoxy(13,16);
	SetColor(12);
	printf("%c %s %c",16,tenmuc[0],17);
}
//ve nhap nhay
void nhapnhay()
{
	system("cls");
	int m,n;
	keBang(10,15,24,10);
	for(m = 0; m < 10 ; m++)
	{	
   		SetColor(9);  
   		gotoxy(30, m+5);
   		for(n = 0; n < 60; n++)
		{
   			if(m==0||m==9||n==0||n==59)
   			{
   				printf("%c",17);
			}
			else
			{
				cout<<" ";	
			}					
		}
		cout<<endl;
	}
	gotoxy(40,9);
	SetColor(15);
	cout<<"    QUAN LY DANH SACH SINH VIEN    ";			
}
