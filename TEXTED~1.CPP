#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
void about();
void help();
FILE *fp;
union REGS in,out;
void show()
{
	 in.x.ax=1;
	 int86(0x33,&in,&out);
}
void set(int x,int y)
{
	 in.x.ax=4;
	 in.x.cx=x;
	 in.x.dx=y;
	 int86(0x33,&in,&out);
}
void pos(int *x,int *y,int *b)
{
	 in.x.ax=3;
	 int86(0x33,&in,&out);
	 *b=out.x.bx;
	 *x=out.x.cx;
	 *y=out.x.dx;
}
void create()
{
	 clrscr();
	 int gd=0,gm,i=0,x,y,a[50],j=0;
	 initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	 char s[1000],fn[50],ch;
	 setbkcolor(8);
	 closegraph();
	 printf("Ctrl+s to save and Esc to exit:\n");
	 while(ch!=19)   //Read character until user press ctrl+s or esc
	 {
		ch=getch();
		if(ch==13)
		{
			a[j]=wherex(); //it stores current position for backspace
			printf("\n");
			s[i]='\n';
			i=i+1;
			j=j+1;
		}
		else if(ch==8)
		{
			if(i>0)
			{
				x=wherex();
				y=wherey();
				if(x==1)
				{
					s[i-1]='\0';
					gotoxy(a[j-1],y-1);
					printf(" ");
					gotoxy(a[j-1],y-1);
					i=i-1;
					j=j-1;
				}
				else
				{
					s[i-1]='\0';
					gotoxy(x-1,y);
					printf(" ");
					gotoxy(x-1,y);
					i=i-1;
				}
			}
		}
		else if(ch==27)
		{
			goto end;
		}
		else if(ch==19)
		{
			s[i]='\0';
			break;
		}
		else if(ch==0)
		{
			ch=getch();
		}
		else
		{
		       if(wherex()==80)
		       {
				printf("%c",ch);
				s[i]=ch;
				a[j]=80;
				j=j+1;
				i=i+1;
			}
			else
			{
				printf("%c",ch);
				s[i]=ch;
				i=i+1;
			}
		}
	 }
	 fname:
	 printf("\nEnter file name to save:");
	 i=0;
	 ch='a';
	 while(ch!=13)   //read character for filename until user press enter or esc
	 {
		ch=getch();
		if(ch==8)
		{
			x=wherex();
			y=wherey();
			if(x==25)
			{
				continue;
			}
			else
			{
				fn[i-1]='\0';
				gotoxy(x-1,y);
				printf(" ");
				gotoxy(x-1,y);
				i=i-1;
			}
		}
		else if(ch==13)
		{
			fn[i]='\0';
			break;
		}
		else if(ch==27)
		{
			goto end;
		}
		else if(ch==0)
		{
			ch=getch();
		}
		else
		{
			printf("%c",ch);
			fn[i]=ch;
			i=i+1;
		}
	 }
	 if(fn[0]=='\0')       //check file name is empty or not
	 {
		printf("File name can't be empty");
		goto fname;
	 }
	 fp=fopen(fn,"w");
	 fprintf(fp,"%s",s);
	 fclose(fp);
	 printf("\nFile saved sucessfully");
	 printf("\nPress any key to continue...");
	 if(getch()==27)
	 {
		exit(0);
	 }
	 end:
}
void open()
{
	clrscr();
	int gd=0,gm,i,t,x,y,a[50],j=0,b=0;
	char s[1000],ch,fn[50];
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	closegraph();
	printf("Enter file name to open:");
	i=0;
	while(ch!=13)   //read character of filename until user press enter or esc
	{
		ch=getch();
		if(ch==8)  //When user press backspace
		{       x=wherex();
			y=wherey();
			if(x==25)
			{
				continue;

			}
			else
			{
				fn[i-1]='\0';
				gotoxy(x-1,y);
				printf(" ");
				gotoxy(x-1,y);
				i=i-1;
			}
		}
		else if(ch==13)   //when user press enter
		{
			printf("\n");
			fn[i]='\0';
			break;
		}
		else if(ch==27)    //when user press esc
		{
			goto end;
		}
		else if(ch==0)
		{
			ch=getch();
		}
		else
		{
			printf("%c",ch);
			fn[i]=ch;
			i=i+1;
		}
	}
	fp=fopen(fn,"r");
	if(fp==NULL)
	{
		 printf("File does not exist");
	}
	else
	{
		fp=fopen(fn,"r");
		ch=getc(fp);
		i=0;
		while(!feof(fp)) //read character from file
		{
			 if(ch=='\n')
			 {
				s[i]='\n';
				printf("%c",ch);
				a[j]=b+1;
				i=i+1;
				j=j+1;
				b=0;
			 }
			 else
			 {
				if(b==80)
				{
					a[j]=80;
					j=j+1;
					b=0;
				}
				s[i]=ch;
				printf("%c",ch);
				i=i+1;
				b++;
			 }
			 ch=getc(fp);
		}
		s[i]='\0';
		t=i;
		fclose(fp);
		while(ch!=19)  //add or remove character in opened file
		{
			ch=getch();
			if(ch==13)  //when use press enter
			{
				a[j]=wherex();
				printf("\n");
				s[i]='\n';
				i=i+1;
				j=j+1;
			}
			else if(ch==8)    //when user press backspace
			{
				if(i>0)
				{
					x=wherex();
					y=wherey();
					if(x==1)
					{
						s[i-1]='\0';
						gotoxy(a[j-1],y-1);
						printf(" ");
						gotoxy(a[j-1],y-1);
						i=i-1;
						j=j-1;
					}
					else
					{
						s[i-1]='\0';
						gotoxy(x-1,y);
						printf(" ");
						gotoxy(x-1,y);
						i=i-1;
					}
				}
			}
			else if(ch==27)       //when user press esc
			{
				goto end;
			}
			else if(ch==19)       //when user press ctrl+s
			{
				s[i]='\0';
				break;
			}
			else if(ch==0)
			{
				ch=getch();
			}
			else
			{
				if(wherex()==80)
				{
					printf("%c",ch);
					s[i]=ch;
					a[j]=80;
					j=j+1;
					i=i+1;
				}
				else
				{

					printf("%c",ch);
					s[i]=ch;
					i=i+1;
				}

			}
		}
		fp=fopen(fn,"w");
		fprintf(fp,"%s",s);
		fclose(fp);
		if(s[t]!='\0')           //check file has been edited or not
		{
			printf("\nFile edited sucessfully");
		}
		else
		{
			printf("\nFile saved sucessfully");
		}

	}
	printf("\nPress any key to continue");
	if(getch()==27)
	{
		exit(0);
	}
	end:
}
void del()
{
	clrscr();
	int gd=0,gm,i,x,y;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	closegraph();
	char fn[50],ch;
	printf("Enter file name to delete:");
	i=0;
	while(ch!=13)     //read character for filename until use press enter or esc
	{
		ch=getch();
		if(ch==8)   //when user press backspace
		{
			x=wherex();
			y=wherey();
			if(x==27)
			{
				continue;
			}
			else
			{
				fn[i-1]='\0';
				gotoxy(x-1,y);
				printf(" ");
				gotoxy(x-1,y);
				i=i-1;
			}
		}
		else if(ch==13)      //when user press enter
		{
			printf("\n");
			fn[i]='\0';
			break;
		}
		else if(ch==27)     //when user press esc
		{
			goto end;
		}
		else if(ch==0)
		{
			ch=getch();
		}
		else
		{
			printf("%c",ch);
			fn[i]=ch;
			i=i+1;
		}
	}
	fp=fopen(fn,"r");
	if(fp==NULL)
	{
		printf("File doesn't exist");
	}
		else
	{
		remove(fn);
		printf("File deleted sucessfully");
	}
	printf("\nPress any key to continue...");
	if(getch()==27)
	{
		exit(0);
	}
	end:

}
int main()
{
	start:
	clrscr();
	int gd=DETECT,gm,x,y,b,x1,y1,i;
	char ch;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	show();
	set(1000,1050);
	rectangle(0,60,getmaxx(),getmaxy());
	setfillstyle(SOLID_FILL,3);
	floodfill(250,250,WHITE);
	rectangle(0,30,getmaxx(),60);
	setfillstyle(SOLID_FILL,0);
	floodfill(100,20,WHITE);
	rectangle(0,0,getmaxx(),30);
	setfillstyle(SOLID_FILL,1);
	floodfill(5,5,15);
	line(70,30,70,60);
	line(140,30,140,60);
	line(210,30,210,60);
	line(270,30,270,60);
	line(340,30,340,60);
	outtextxy(250,10,"TEXT EDITOR");
	outtextxy(10,40,"Create");
	outtextxy(90,40,"Open");
	outtextxy(150,40,"Delete");
	outtextxy(220,40,"About");
	outtextxy(290,40,"Help");
	point1:
	while(!kbhit())
	{
		pos(&x,&y,&b);
		if(b==1)
		{
			for(x1=0;x1<70;x1++)
			{
				for(y1=30;y1<60;y1++)
					if(x1==x&&y1==y)
					{
						create();
						goto start;
					}

			}

			for(x1=71;x1<140;x1++)
			{
				for(y1=30;y1<60;y1++)
					if(x1==x&&y1==y)
					{
						open();
						goto start;
					}
			}

			for(x1=141;x1<210;x1++)
			{
				for(y1=30;y1<60;y1++)
					if(x1==x&&y1==y)
					{
						del();
						goto start;
					}
			}
			for(x1=211;x1<270;x1++)
			{
				for(y1=30;y1<60;y1++)
				{
					if(x1==x&&y1==y)
					{
						about();
					}
				}
			}
			for(x1=271;x1<340;x1++)
			{
				for(y1=30;y1<60;y1++)
				{
					if(x1==x&&y1==y)
					{
						help();
					}
				}
			}
		}
	}
	ch=getch();
	if(ch==27)
	{
		exit(1);
		closegraph();
		return 0;
	}
	else if(ch==14)
	{
		create();
		goto start;
	}
	else if(ch==15)
	{
		open();
		goto start;
	}
	else if(ch==4)
	{
		del();
		goto start;
	}
	else
	{
		goto point1;
	}
}
void about()
{
	setfillstyle(SOLID_FILL,0);
	rectangle(5,70,getmaxx()-5,250);
	floodfill(75,90,15);
	gotoxy(3,6);
	printf("About");
}
void help()
{
	setfillstyle(SOLID_FILL,0);
	rectangle(5,70,getmaxx()-5,250);
	floodfill(75,90,15);
	gotoxy(3,6);
	printf("Help\t");
}