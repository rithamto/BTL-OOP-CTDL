#include <iostream>
#include <string.h>
//#include <conio.h>
//#include <graphics.h> 
#include<winbgim.h>
#include<fstream>
#include <cstdio>
using namespace std;
void menu();


void press(int &x1,int &x2, int &y1, int &y2, int &v, int &z, FILE *file){	
	int i;	
	char *x;
	x =(char*)calloc(9999,sizeof(char));						//43
	setcolor(10);
	rectangle(x1,y1,x2,y2);
	*(x+i) = getch();
	if (*(x+i) == 0){
		*(x+i) = getch();
			if(*(x+i) == KEY_DOWN){
				fprintf(file,"\n" );
				setcolor(8);
				rectangle(x1,y1,x2,y2);
				y1+=30;
				y2+=30;	
				z+=30;
				v=270;			
				if(y1>475&&y2>502){
					y1-=30;
					y2-=30;
					z-=30;
				}
				setcolor(10);
				rectangle(x1,y1,x2,y2);			
			}
			else if(*(x+i) == KEY_UP){
				setcolor(8);
				rectangle(x1,y1,x2,y2);
				y1-=30;
				y2-=30;
				z-=30;
				v=270;
				if(y1<295&&y2<322){
					y1+=30;
					y2+=30;
					z+=30;
				}
				setcolor(10);
				rectangle(x1,y1,x2,y2);		
			}
			else if(*(x+i) == KEY_LEFT){
				v-=12;
				if(v<270){
					v+=12;
				}
			}
			else if(*(x+i) == KEY_RIGHT){
				fprintf(file," ");
				v+=12;
				if(v>790){
					v-=12;
				}	
			}	
	}
	else{
		
		setcolor(7);
		settextstyle(10, 0, 1);
	    outtextxy(v,z,x+i);
	    fprintf(file,"%s" ,(x+i));                      //(x+i)
	    v+=12;  
	}
		
		i++;
//		fclose(file);
}
void button_menu1(int a, int b){
	if(a>570&&a<710&&b>520&&b<580){
		setcolor(3);                               //	rectangle(570,520,710,580);						//	rectangle(140,520,280,580);
		settextstyle (10, 0, 1);
		outtextxy(190,540,"LUU");
		ellipse(210,550,70,70,70,30);
		setcolor(15);
		outtextxy(600,540,"QUAY LAI");
		ellipse(642,550,70,70,70,30);
		}
	else if(a>140&&a<280&&b>520&&b<580){
		setcolor(15);
		settextstyle (10, 0, 1);
		outtextxy(190,540,"LUU");
		ellipse(210,550,70,70,70,30);	
		setcolor(3);
		outtextxy(600,540,"QUAY LAI");
		ellipse(642,550,70,70,70,30);
		}	
	else{
		setcolor(3);
		settextstyle (10, 0, 1);
		outtextxy(600,540,"QUAY LAI");
		outtextxy(190,540,"LUU");
		ellipse(642,550,70,70,70,30);
		ellipse(210,550,70,70,70,30);
	}
}	

int check(){	
	
		if(ismouseclick(WM_LBUTTONDOWN)){
		int x, y;
		getmouseclick(WM_LBUTTONDOWN, x, y);
			if (x>480&&x<830&&y>140&&y<=170){
					return 1;			
			}
			else if(x>480&&x<830&&y>190&&y<230){
				return 2;
			}
			else if(x>480&&x<830&&y>240&&y<280){
				return 3;
			}
			else if(x>570&&x<710&&y>520&&y<580){
				return 4;
			}
			else if(x>140&&x<280&&y>520&&y<580){
				return 5;
			}	
			else if(x>480&&x<790&&y>290&&y<330){
				return 6;
			}
		}
		
}
int button_menu(int a, int b){	
				if (a>480&&a<790&&b>140&&b<170){
					setcolor(10);	
					rectangle(480,140,790,180);	
					setcolor(15);
					rectangle(480,190,790,230);
					rectangle(480,240,790,280);	
					rectangle(480,290,790,330);
				}
				else if(a>480&&a<790&&b>190&&b<230){
					setcolor(10);	
					rectangle(480,190,790,230);
					setcolor(15);
					rectangle(480,140,790,180);	
					rectangle(480,240,790,280);
					rectangle(480,290,790,330);
				}
				else if(a>480&&a<790&&b>240&&b<280){
					setcolor(10);
					rectangle(480,240,790,280);	
					setcolor(15);
					rectangle(480,140,790,180);
					rectangle(480,190,790,230);
					rectangle(480,290,790,330);
				}
				else if(a>480&&a<790&&b>290&&b<330){
					setcolor(10);
					rectangle(480,290,790,330);
					setcolor(15);
					rectangle(480,140,790,180);
					rectangle(480,190,790,230);
					rectangle(480,240,790,280);
				}
				else{
					setcolor(15);
					rectangle(480,140,790,180);
					rectangle(480,190,790,230);
					rectangle(480,240,790,280);
					rectangle(480,290,790,330);
				}
				
		}
void intro(){
	setbkcolor(8);
	cleardevice();
	setcolor(2);
	settextstyle (10, 0, 1);
	outtextxy(360,50,"QUAN LY SINH VIEN");
	setcolor(14);
	settextstyle (5, 0, 2);
	outtextxy(100,100,"Danh sach nhom: ");
	settextstyle (5, 0, 1);
	outtextxy(110,125,"- Do Huu Khang ");
	outtextxy(110,150,"- Huynh Xuan Lam ");
	outtextxy(110,175,"- Tran Cong Linh ");
	outtextxy(110,200,"- Nguyen Tuan Khoi ");
	outtextxy(110,225,"- Phan Gia Khiem ");
	setcolor(13);
	ellipse(450,60,70,70,110,40);
	setcolor(14);
	rectangle(90,90,320,250);	
}
void menu(){
	intro();
	int a,b,c = 0;
	settextstyle (3, 0, 1);
	setcolor(9);
	outtextxy(605,100,"Menu");
	outtextxy(490,150,"1.Nhap Sinh Vien vao dau tien");
	outtextxy(490,200,"2.Nhap Sinh Vien vao cuoi cung");
	outtextxy(490,250,"3.Nhap Sinh Vien vao bat ki");
	outtextxy(490,300,"4.Danh sach Sinh Vien");
	setcolor(15);
	rectangle(595,95,662,130);
	rectangle(480,140,790,180);
	rectangle(480,190,790,230);
	rectangle(480,240,790,280);
	rectangle(480,290,790,330);
	do{
			a=mousex();
			b=mousey();
			button_menu(a,b);
			delay(100);	
		}while( ismouseclick(WM_LBUTTONDOWN) == false);
}
void menu1(int &x1, int &x2, int &y1, int &y2, int &v, int &z, FILE *file){
	cleardevice();
	intro();
	setcolor(7);
	settextstyle (10, 0, 1);
	outtextxy(100,300," Ten sinh vien: ");
	outtextxy(80,360," Ma so sinh vien: ");
	outtextxy(36,330," Ngay thang nam sinh: ");
	outtextxy(190,390," Email: ");
	outtextxy(103,420," So dien thoai: ");
	outtextxy(170,450," Dia chi: ");
	outtextxy(182,480," Ma lop: ");		
	
	do{	
			int a,b;
			a=mousex();
			b=mousey();
			if(a>40&&a<790&&b>295&&b<502){
				press(x1,x2,y1,y2,z,v,file);
			}
			else{
				button_menu1(a,b);
			}	
			delay(100);
		}while(ismouseclick(WM_LBUTTONDOWN) == false);
}
int count=0;
typedef class Student{
	public:
		string Name;
		string STID;
		string Born;
		string Email;
		string PhoneNum;
		string Address;
		string Grade;
		friend class Node;	
} ST;
class Node{
	private:
		ST data;
		Node *n;
		Node *p;
	public:
		friend class List;	
};
class List{
	private:
		Node *first, *last;
	public:
		Node* create_node(char[], char[], char[] , char[] , char[] , char[] , char[]);
		void insert_begin(char[], char[], char[] , char[] , char[] , char[] , char[]);
		void insert_end(char[], char[], char[] , char[] , char[] , char[] , char[]);
		void insert_pos(char[], char[], char[] , char[] , char[] , char[] , char[], int);
		string fileName;		
		void readfile(List &l);
		void writefile(List &l);
		void sortbyName(List &l, int n);
		void sortbyID(List &l, int n);
		void searchST(List &l, int n);
		void fixST(List &l, int *q);
		void delST(List &l);	
		int cout();
		void memu(List &);
		void inList(List l);
};
Node *List::create_node(char Name[],char STID[],char  Born[],char  Email[],char  PhoneNum[],char  Address[],char  Grade[]){
	Node *t;
	count++;
	t = new Node;
	t->data.Name = Name;
	t->data.STID = STID;
	t->data.Born = Born;
	t->data.Email = Email;
	t->data.PhoneNum = PhoneNum;
	t->data.Address = Address;
	t->data.Grade = Grade;
	t->n=NULL;
	t->p=NULL;
	return t;
}
void List::insert_begin(char Name[],char STID[],char  Born[],char  Email[],char  PhoneNum[],char  Address[],char  Grade[]){
	Node *t = create_node(Name,STID,Born,Email,PhoneNum,Address,Grade);	
	if(first == last && first == NULL){
		first=last=t;
		first->n = last->n=NULL;
		first->p = last->p= NULL;
	}
	else{
		last->n= t;
        t->p= last;
        last = t;
        first->p = last;
        last->n= first;
	}
}
void List::insert_pos(char Name[],char STID[],char  Born[],char  Email[],char  PhoneNum[],char  Address[],char  Grade[], int pos){
	Node *t, *s, *ptr;
	t = create_node(Name,STID,Born,Email,PhoneNum,Address,Grade);
	if (first == last && first == NULL) {
      if (pos == 1) {
         first = last = t;
         first->n = last->n = NULL;
         first->p = last->p = NULL;
      } else {
         count--;
         return;
      }
   } else {
      if (count < pos) {
         count--;
         return;
      }
      s = first;
      for (int i = 1; i <= count; i++) {
         ptr = s;
         s = s->n;
         if (i == pos - 1) {
            ptr->n = t;
            t->p= ptr;
            t->n= s;
            s->p = t;
            break;
         }
      }
  }
}
void List::insert_end(char Name[],char STID[],char Born[],char  Email[],char  PhoneNum[],char  Address[],char  Grade[]){
	Node *t = create_node(Name,STID,Born,Email,PhoneNum,Address,Grade);
	if (first == last && first == NULL) {
      first = last = t;
      first->n= last->n = NULL;
      first->p = last->p= NULL;
   } 
    else {
      last->n= t;
      t->p= last;
      last = t;
      first->p = last;
      last->n= first;
}
}
void out(){
	char *x;
	x =(char*)calloc(9999,sizeof(char));
	
}
void first(FILE *file, List Ls){
	char Name[100];
	char STID[100];
	char Born[100];
	char Email[100];
	char PhoneNum[100];
	char Address[100];
	char Grade[100];
	fgets(Name,100,file);
	fgets(STID,100,file);
	fgets(Born,100,file);
	fgets(Email,100,file);
	fgets(PhoneNum,100,file);
	fgets(Address,100,file);
	fgets(Grade,100,file);
	Ls.insert_begin(Name, STID,  Born,  Email, PhoneNum,  Address,  Grade);
}
void end(FILE *file, List Ls){
	char Name[100];
	char STID[100];
	char Born[100];
	char Email[100];
	char PhoneNum[100];
	char Address[100];
	char Grade[100];
	fgets(Name,100,file);
	fgets(STID,100,file);
	fgets(Born,100,file);
	fgets(Email,100,file);
	fgets(PhoneNum,100,file);
	fgets(Address,100,file);
	fgets(Grade,100,file);
	Ls.insert_end(Name, STID,  Born,  Email, PhoneNum,  Address,  Grade);
}
void pos(FILE *file, List Ls, int pos){
	char Name[100];
	char STID[100];
	char Born[100];
	char Email[100];
	char PhoneNum[100];
	char Address[100];
	char Grade[100];
	fgets(Name,100,file);
	fgets(STID,100,file);
	fgets(Born,100,file);
	fgets(Email,100,file);
	fgets(PhoneNum,100,file);
	fgets(Address,100,file);
	fgets(Grade,100,file);
	Ls.insert_pos(Name, STID,  Born,  Email, PhoneNum,  Address,  Grade, pos);
}
int main(){
	List Ls;
	int p;
	const char *filePath = 	"D:\danhsach.txt";
	FILE *file;
	file = fopen(filePath, "w+");	
	initwindow(900, 600);	
	menu();	
	while(true){
	int v=300, z=270;
	int x1 =40, y1 =295, x2 =790, y2=322, i=0;	
		
		switch(check()){
			case 1:
				menu1(x1, x2, y1, y2,v,z, file);
				first(file,Ls);
	        break;
			case 2:
				menu1(x1, x2, y1, y2,v,z, file);
				end(file,Ls);
			break;
			case 3:
				menu1(x1, x2, y1, y2,v,z, file);
				pos(file,Ls,p);
			break;					
			case 4:
				menu();	
			case 5:
				menu();	
			case 6:
				out();			
		}
	
	delay(100);
	}
	fclose(file);
}

