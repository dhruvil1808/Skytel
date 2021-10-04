#include<iostream>
using namespace std;
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
class skytel
{
    private:
		  int user_no;
		  char name[30];
		  char address[50];
		  char phone[10];
          int pack[10];
          int a_la_cart[25];
          double bill;
    public:
		  void main_menu1();
          void main_menu2();
		  void freeChannels();
		  void addChannels(int);
		  void addOnChannels(int);
		  void Packs(int);          
		  void addUser();
		  void userDetails(int);
		  void edit();
		  void delete_rec(int);
		  int check(int);
		  void modify(int);
		  void BillStatus();
		  void displayChannels(int);
		  void report();
};

skytel obj;
void skytel::main_menu1()
{
	        
		int choice;
		while(choice!=4)
		{   cout<<"\n\n\n\t\t\t1.Add user";
			cout<<"\n\t\t\t2.User details";
			cout<<"\n\t\t\t3.Edit user details";
		    cout<<"\n\t\t\t4.Exit";
			cout<<"\n\n\t\t\tEnter Your Choice: ";
			cin>>choice;

			system("clear");
			switch(choice)
			{
				case 1: addUser();
					break;
				case 2: int r;
					cout<<"\n user no: ";
					cin>>r;
			        system("clear");
					userDetails(r);
					break;
				case 3: 
				    edit();
				    break;
				case 4: break;
				default:
					cout<<"\n\n\t\t\tWrong choice. !";
					cout<<"\n\t\t\tPress any key to continue ";
					char cc=getchar();
					system("clear");
			}

		}
}
void skytel::addUser()
{
	int r,flag;char p2[30],f[1];
	ofstream fout("Record.dat",ios::app|ios::binary);

		  cout<<"\n Enter Customer Detalis";
		  cout<<"\n ----------------------";
		  cout<<"\n\n user no.: ";
		  cin>>r;
		  flag=check(r);
		  if(flag)
			cout<<"\n Sorry..!!!user already exists";
		  else
		  {
			user_no=r;
			gets(f);
			cout<<" Name: ";
			gets(name);
			cout<<" Address: ";
			gets(address);
			cout<<" Phone No: ";
			gets(phone);
            addChannels(r);
			fout.write((char*)this,sizeof(skytel));
            cout<<"account created";
          }
	fout.close();
}
void skytel::userDetails(int r)
{
		  ifstream fin("Record.dat",ios::in|ios::binary);
		  int flag=0;
		  while(fin.read((char*)this,sizeof(skytel)))
		  {
		  if(user_no==r)
			{
			cout<<"\n Customer Details";
			cout<<"\n ----------------";
			cout<<"\n\n User no: "<<user_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone no: "<<phone<<"\n\n";
			flag=1;
			break;
			}
		  }

		  if(flag==0)
		  cout<<"\n Sorry User no. not found ";
		  cout<<"\n\n Press any key to continue    \n \n";
		  char cc=getchar();
		  fin.close();
}
void skytel::edit()
{
		  //system("clear");
		  int choice,r;

		  cout<<"\n EDIT MENU";
		  cout<<"\n ---------";
		  cout<<"\n\n 1.Modify Customer Record";
		  cout<<"\n 2.Delete Customer Record";
		  cout<<"\n Enter your choice: ";
		  cin>>choice;
		  system("clear");
		  cout<<"\n Enter user no: " ;
		  cin>>r;

		  switch(choice)
		  {
					 case 1: modify(r);
								break;
					 case 2: delete_rec(r);
								break;
						  default: cout<<"\n Wrong Choice. ";
		  }
		  cout<<"\n Press any key to continue !";
		  char cc=getchar();
}
void skytel::modify(int r)
{
		  long pos,flag=0;char f[1];
		  fstream file("Record.dat",ios::in|ios::out|ios::binary);
		  while(!file.eof())
		  {
					 pos=file.tellg();
					 file.read((char*)this,sizeof(skytel));
					 if(user_no==r)
                     {
                            userDetails(r);
					            gets(f);
								cout<<"\n Enter New Details";
								cout<<"\n -----------------";
								cout<<"\n Name: ";
								gets(name);
								cout<<" Address: ";
								gets(address);
								cout<<" Phone no: ";
								gets(phone);
								file.seekg(pos);
								file.write((char*)this,sizeof(skytel));
								cout<<"\n Record is modified ";
								flag=1;
								break;
						 }
		  }

		  if(flag==0)
					 cout<<"\n Sorry User no. not found or vacant...!!";
		  file.close();
}
void skytel::delete_rec(int r)
{
		  int flag=0;
		  char ch;
		  ifstream fin("Record.dat",ios::in);
		  ofstream fout("temp.dat",ios::out);
		  while(!fin.eof())
		  {
					 fin.read((char*)this,sizeof(skytel));
					 if(user_no==r)
					 {
								cout<<"\n Name: "<<name;
								cout<<"\n Address: "<<address;
								cout<<"\n Pone No: "<<phone;
								cout<<"\n\n Do you want to delete this record(y/n): ";
								cin>>ch;
										  if(ch=='n')
										  fout.write((char*)this,sizeof(skytel));
										  else if(ch=='y')
										  {
								flag=1;
								break;
										  }
					 }
					 else
								fout.write((char*)this,sizeof(skytel));
		  }

		  fin.close();
		  fout.close();
		  if(flag==0)
					 cout<<"\n Sorry user no. not found or vacant...!!";
		  else
		  {
					 remove("Record.dat");
					 rename("temp.dat","Record.dat");
		  }
}
void skytel::main_menu2()
{
	 int i=0,flag,r,a;
	 cout<<"\n Enter user no: " ;
	 cin>>r;
	 flag=check(r);
	if(flag)
	{
        do
          {
             cout<<"\n\n";
             userDetails(r);
             cout<<"  \n  1.Channel details\n  2.Modify channel and pack list \n  0.Return \n";
             cin>>a;
             system("clear");

            if(a==1)
		    {
			 cout<<"your free channels are:"<<"\n";
			 freeChannels();
			 displayChannels(r);
		    }
		    else if(a==2)
		    {
             int z;
			 cout<<"enter 1 to modify paid channels and 2 to modify pack \n";
			 cin>>z;
		     if(z==1)
			 {addOnChannels(r);}
             else if(z==2)
			 {Packs(r);}
             else
			 cout<<"invalid \n";
		    }
		  cout<<"\n\n";
		  }while(a!=0);
    }
    else
	 cout<<"\n Sorry user no. not found or vacant...!!";
}
void skytel::addChannels(int r)
{
int i,flag,pos,x,g=0;;
int c;
ofstream fout("Record.dat",ios::app|ios::binary);
do
{
cout<<"********************a la cart********************** \n";
cout<<"Enter 1 for Khaana Khazana             (5)\n";
cout<<"Enter 2 for 9X Jhakkas                 (6)\n";
cout<<"Enter 3 for Epic TV                    (7)\n";
cout<<"Enter 4 for India TV                   (5)\n";
cout<<"Enter 5 for Homeshop 18                (4)\n";
cout<<"Enter 6 for Satsang                    (6)\n";
cout<<"Enter 7 for SVBC                       (6)\n";
cout<<"Enter 8 for 9XO                        (5)\n";
cout<<"Enter 9 for B4U Movies                 (4)\n";
cout<<"Enter 10 for News Nation               (5)\n";
cout<<"Enter 11 for Manorama TV               (6)\n";
cout<<"Enter 12 for Saam TV                   (5)\n";
cout<<"Enter 13 for MBC TV                    (4)\n";
cout<<"Enter 14 for TV9 Marathi               (6)\n";
cout<<"Enter 15 for Tarang TV                 (7)\n";
cout<<"Enter 16 for Gyandarshan 1             (4)\n";
cout<<"Enter 17 for News 9                    (6)\n";
cout<<"Enter 18 for Public TV                 (5)\n";
cout<<"Enter 19 for B TV                      (5)\n";
cout<<"Enter 20 for Bhakti TV                 (7)\n";
cout<<"Enter 21 for Dharshan 24               (5)\n";
cout<<"Enter 22 for Ali TV                    (7)\n";
cout<<"Enter 23 for ABP Asmita                (5)\n";
cout<<"Enter 24 for Al Jazeera                (6)\n";
cout<<"Enter 25 for Russia Today              (4)\n";
cout<<"enter the channel number and 0 to exit   \n";
cin>>c;
cout<<"........enter any key to continue";
char cc=getchar();
system("clear");
if(c==0)
{
	break;
}
for(x=0;x<g;x++)
{
  if(c==a_la_cart[x])
  {
	 cout<<"you already have this channel"<<"\n";
	 break;
  }
}
if(x==g)
{
a_la_cart[g]=c;
g++;
}
}while(c!=0);
int d=0;g=0;
do
{
cout<<"********************packs********************** \n";
cout<<"Enter 1 for Sports Pack                         (23)"<<endl;
cout<<"Enter 2 for Cartoon Pack                         (24)"<<endl;
cout<<"Enter 3 for News Pack                            (23)"<<endl;
cout<<"Enter 4 for Music                                (26)"<<endl;
cout<<"Enter 5 for Infotainment                         (25)"<<endl;
cout<<"Enter 6 for English Movies                       (27)"<<endl;
cout<<"Enter 7 for Hindi Movies                         (25)"<<endl;
cout<<"Enter 8 for English Entertainment                (23)"<<endl;
cout<<"Enter 9 for Hindi Entertainment                  (24)"<<endl;
cout<<"enter the pack number and 0 to exit \n";
cin>>d;
cout<<"........enter any key to continue";
char cc=getchar();
system("clear");
if(d==0)
{
	break;
}
for(x=0;x<g;x++)
{
  if(d==pack[x])
  {
	 cout<<"you already have this pack"<<"\n";
		 break;
}
}
if(x==g)
{
pack[g]=d;
g++;
}

}while(d!=0);
//fout.write((char*)&obj ,sizeof(skytel));
fout.close();

		  }
void skytel::displayChannels(int r)
{
int i;
ifstream fin("Record.dat",ios::in|ios::binary);
cout<<"\n\n";
cout<<"your selected channels are:"<<"\n";
for(int j=0;j<25;j++)
{
if(a_la_cart[j]==1)
cout<<" 1-Khaana Khazana             (5)\n";
if(a_la_cart[j]==2)
cout<<" 2-9X Jhakkas                 (6)\n";
if(a_la_cart[j]==3)
cout<<" 3-Epic TV                    (7)\n";
if(a_la_cart[j]==4)
cout<<" 4-India TV                   (5)\n";
if(a_la_cart[j]==5)
cout<<" 5-Homeshop 18                (4)\n";
if(a_la_cart[j]==6)
cout<<" 6-Satsang                    (6)\n";
if(a_la_cart[j]==7)
cout<<" 7-SVBC                       (6)\n";
if(a_la_cart[j]==8)
cout<<" 8-9XO                        (5)\n";
if(a_la_cart[j]==9)
cout<<" 9-B4U Movies                 (4)\n";
if(a_la_cart[j]==10)
cout<<" 10-News Nation               (5)\n";
if(a_la_cart[j]==11)
cout<<" 11-Manorama TV               (6)\n";
if(a_la_cart[j]==12)
cout<<" 12-Saam TV                   (5)\n";
if(a_la_cart[j]==13)
cout<<" 13-MBC TV                    (4)\n";
if(a_la_cart[j]==14)
cout<<" 14-TV9 Marathi               (6)\n";
if(a_la_cart[j]==15)
cout<<" 15-Tarang TV                 (7)\n";
if(a_la_cart[j]==16)
cout<<" 16-Gyandarshan 1             (4)\n";
if(a_la_cart[j]==17)
cout<<" 17-News 9                    (6)\n";
if(a_la_cart[j]==18)
cout<<" 18-Public TV                 (5)\n";
if(a_la_cart[j]==19)
cout<<" 19-B TV                      (5)\n";
if(a_la_cart[j]==20)
cout<<" 20-Bhakti TV                 (7)\n";
if(a_la_cart[j]==21)
cout<<" 21-Dharshan 24               (5)\n";
if(a_la_cart[j]==22)
cout<<" 22-Ali TV                    (7)\n";
if(a_la_cart[j]==23)
cout<<" 23-ABP Asmita                (5)\n";
if(a_la_cart[j]==24)
cout<<" 24-Al Jazeera                (6)\n";
if(a_la_cart[j]==25)
cout<<" 25-Russia Today              (4)\n";
}

cout<<"\n\n";
cout<<"your selected packs are: \n";
for(int j=0;j<9&&pack[j]!=0;j++)
{
if(pack[j]==1)
cout<<" 1-Sports Pack                (23)"<<endl;
if(pack[j]==2)
cout<<" 2-Cartoon Pack               (24)"<<endl;
if(pack[j]==3)
cout<<" 3-News Pack                  (23)"<<endl;
if(pack[j]==4)
cout<<" 4-Music                      (26)"<<endl;
if(pack[j]==5)
cout<<" 5-Infotainment               (25)"<<endl;
if(pack[j]==6)
cout<<" 6-English Movies             (27)"<<endl;
if(pack[j]==7)
cout<<" 7-Hindi Movies               (25)"<<endl;
if(pack[j]==8)
cout<<" 8-English Entertainment      (23)"<<endl;
if(pack[j]==9)
cout<<" 9-Hindi Entertainment        (24)"<<endl;
}
cout<<"\n\n";

cout<<"........enter any key to continue";
char cc=getchar();
}
void skytel::freeChannels()
{
cout<<"Hindi Channels           Dangal               DD India             DD MP                  DD National \n";
cout<<"DD Rajasthan             DD Bharti            DD Kisan             Divyarashi             Gemporia Direct \n";
cout<<"B4U Movies               Cinema TV            Enter 10             Maha Movies            Skystar Movies  \n";
cout<<"Wow Cinema               9X Jalwa             B4U Music            Mastit                 Music India  \n";

}
void skytel::addOnChannels(int r)
{
	 int i,x;
int c=0,check,new1;

long pos,flag=0;char f[1];
		  fstream file("Record.dat",ios::in|ios::out|ios::binary);
		  while(!file.eof())
		  {
					 pos=file.tellg();
					 file.read((char*)this,sizeof(skytel));
					 if(user_no==r)
					 {
do
{
for(int j=0;j<25&&a_la_cart[j]!=0;j++)
{
if(a_la_cart[j]==1)
cout<<" 1-Khaana Khazana            (5)\n";
if(a_la_cart[j]==2)
cout<<" 2-9X Jhakkas                (6)\n";
if(a_la_cart[j]==3)
cout<<" 3-Epic TV                   (7)\n";
if(a_la_cart[j]==4)
cout<<" 4-India TV                  (5)\n";
if(a_la_cart[j]==5)
cout<<" 5-Homeshop 18               (4)\n";
if(a_la_cart[j]==6)
cout<<" 6-Satsang                   (6)\n";
if(a_la_cart[j]==7)
cout<<" 7-SVBC                      (6)\n";
if(a_la_cart[j]==8)
cout<<" 8-9XO                       (5)\n";
if(a_la_cart[j]==9)
cout<<" 9-B4U Movies                (4)\n";
if(a_la_cart[j]==10)
cout<<" 10-News Nation              (5)\n";
if(a_la_cart[j]==11)
cout<<" 11-Manorama TV              (6)\n";
if(a_la_cart[j]==12)
cout<<" 12-Saam TV                  (5)\n";
if(a_la_cart[j]==13)
cout<<" 13-MBC TV                   (4)\n";
if(a_la_cart[j]==14)
cout<<" 14-TV9 Marathi              (6)\n";
if(a_la_cart[j]==15)
cout<<" 15-Tarang TV                (7)\n";
if(a_la_cart[j]==16)
cout<<" 16-Gyandarshan 1            (4)\n";
if(a_la_cart[j]==17)
cout<<" 17-News 9                   (6)\n";
if(a_la_cart[j]==18)
cout<<" 18-Public TV                (5)\n";
if(a_la_cart[j]==19)
cout<<" 19-B TV                     (5)\n";
if(a_la_cart[j]==20)
cout<<" 20-Bhakti TV                (7)\n";
if(a_la_cart[j]==21)
cout<<" 21-Dharshan 24              (5)\n";
if(a_la_cart[j]==22)
cout<<" 22-Ali TV                   (7)\n";
if(a_la_cart[j]==23)
cout<<" 23-ABP Asmita               (5)\n";
if(a_la_cart[j]==24)
cout<<" 24-Al Jazeera               (6)\n";
if(a_la_cart[j]==25)
cout<<" 25-Russia Today             (4)\n";
}
cout<<"enter the channel number to remove it"<<"\n"<<"enter 0 if you do not want to remove any channel";
cin>>check;
system("clear");
cout<<" Enter 1 for Khaana Khazana             (5)\n";
cout<<"Enter 2 for 9X Jhakkas                 (6)\n";
cout<<"Enter 3 for Epic TV                    (7)\n";
cout<<"Enter 4 for India TV                   (5)\n";
cout<<"Enter 5 for Homeshop 18                (4)\n";
cout<<"Enter 6 for Satsang                    (6)\n";
cout<<"Enter 7 for SVBC                       (6)\n";
cout<<"Enter 8 for 9XO                        (5)\n";
cout<<"Enter 9 for B4U Movies                 (4)\n";
cout<<"Enter 10 for News Nation               (5)\n";
cout<<"Enter 11 for Manorama TV               (6)\n";
cout<<"Enter 12 for Saam TV                   (5)\n";
cout<<"Enter 13 for MBC TV                    (4)\n";
cout<<"Enter 14 for TV9 Marathi               (6)\n";
cout<<"Enter 15 for Tarang TV                 (7)\n";
cout<<"Enter 16 for Gyandarshan 1             (4)\n";
cout<<"Enter 17 for News 9                    (6)\n";
cout<<"Enter 18 for Public TV                 (5)\n";
cout<<"Enter 19 for B TV                      (5)\n";
cout<<"Enter 20 for Bhakti TV                 (7)\n";
cout<<"Enter 21 for Dharshan 24               (5)\n";
cout<<"Enter 22 for Ali TV                    (7)\n";
cout<<"Enter 23 for ABP Asmita                (5)\n";
cout<<"Enter 24 for Al Jazeera                (6)\n";
cout<<"Enter 25 for Russia Today              (4)\n";
cout<<"enter the channel number and 0 to exit   \n";
cout<<"enter new channel number"<<"\n"<<"enter 0 if you do not want to add new channel";
cin>>new1;
for(x=0;x<25;x++)
{
  if(a_la_cart[x]==check&&new1==0)
 {a_la_cart[x]=0;break;}
 if(a_la_cart[x]==check)
 {a_la_cart[x]=new1;break;}
}
if(x==25)
{
	 cout<<"you do not have channel number"<<check<<"adding the new channel to your previous list";
	 for(int y=0;y<25;y++)
	 {
		  if(a_la_cart[y]==0)
		  {a_la_cart[y]=new1;
		  break;}
		  }
break;
}
}while(new1!=0&&check!=0||new1==0&&check!=0);
file.seekg(pos);
								file.write((char*)this,sizeof(skytel));
								cout<<"\n Record is modified \n";
								break;
								flag=1;
					 }
		  if(flag==0)
					 cout<<"\n Sorry User no. not found or vacant...!!";
		  file.close();

}
}
void skytel::Packs(int r)
{
int i,x;
int check2,new2;
long pos,flag=0;char f[1];
		  fstream file("Record.dat",ios::in|ios::out|ios::binary);
		  while(!file.eof())
		  {
					 pos=file.tellg();
					 file.read((char*)this,sizeof(skytel));
					 if(user_no==r)
					 {

do
{for(int j=0;j<9&&pack[j]!=0;j++)
{
if(pack[j]==1)
cout<<" 1-Sports Pack                (23)"<<endl;
if(pack[j]==2)
cout<<" 2-Cartoon Pack               (24)"<<endl;
if(pack[j]==3)
cout<<" 3-News Pack                  (23)"<<endl;
if(pack[j]==4)
cout<<" 4-Music                      (26)"<<endl;
if(pack[j]==5)
cout<<" 5-Infotainment               (25)"<<endl;
if(pack[j]==6)
cout<<" 6-English Movies             (27)"<<endl;
if(pack[j]==7)
cout<<" 7-Hindi Movies               (25)"<<endl;
if(pack[j]==8)
cout<<" 8-English Entertainment      (23)"<<endl;
if(pack[j]==9)
cout<<" 9-Hindi Entertainment        (24)"<<endl;
}
cout<<"enter the pack number to remove it"<<"\n"<<"enter 0 if you do not want to remove any pack";
cin>>check2;
system("clear");
cout<<"Enter 1 for Sports Pack                         (23)"<<endl;
cout<<"Enter 2 for Cartoon Pack                         (24)"<<endl;
cout<<"Enter 3 for News Pack                            (23)"<<endl;
cout<<"Enter 4 for Music                                (26)"<<endl;
cout<<"Enter 5 for Infotainment                         (25)"<<endl;
cout<<"Enter 6 for English Movies                       (27)"<<endl;
cout<<"Enter 7 for Hindi Movies                         (25)"<<endl;
cout<<"Enter 8 for English Entertainment                (23)"<<endl;
cout<<"Enter 9 for Hindi Entertainment                  (24)"<<endl;
cout<<"enter the pack number and 0 to exit \n";
cout<<"enter new pack number"<<"\n"<<"enter 0 if you do not want to add new pack";
cin>>new2;
cout<<"........enter any key to continue";
char cc=getchar();
system("clear");
for(x=0;x<25;x++)
{
  if(pack[x]==check2&&new2==0)
 {pack[x]=0;break;}
 if(pack[x]==check2)
 {pack[x]=new2;break;}
}
if(x==25)
{
	 cout<<"you do not have pack number"<<check2<<"adding the new pack to your previous list";
	 for(int y=0;y<25;y++)
	 {
		  if(pack[y]==0)
		  {pack[y]=new2;
		  break;}
		  }
break;
}
}while(new2!=0&&check2!=0||new2==0&&check2!=0);
}
file.seekg(pos);
								file.write((char*)this,sizeof(skytel));
								cout<<"\n Record is modified ";
								break;
								flag=1;
					 }
		  if(flag==0)
					 cout<<"\n Sorry User no. not found or vacant...!!";
		  file.close();
		  }
void skytel::BillStatus()
{
	 int i,r,pos,flag;
int defAddOn[]={5,6,7,5,4,8,6,5,4,5,6,5,4,6,7,4,6,5,5,7,5,7,5,6,4};
int defPack[]={23,24,23,26,25,27,25,23,24};
int bill2=0,bill3=0;
cout<<"\n Enter user no: " ;
	 cin>>r;
flag=check(r);
	 fstream file("Record.dat",ios::in|ios::out|ios::binary);
		  while(!file.eof())
		  {
					 pos=file.tellg();
					 file.read((char*)this,sizeof(skytel));
					 if(user_no==r)
					 {
						  userDetails(r);
						  cout<<"your free channels are:"<<"\n";
						  freeChannels();
displayChannels(r);
ifstream fin("Record.dat",ios::in);
cout<<"\n\n";
cout<<"your bill";
bill=350;
cout<<"basic amount :  "<<bill<<"\n";
for(int i=1;i<25;i++)
{
for(int j=0;j<25;j++)
if(a_la_cart[j]==i)
 bill2=bill2+defAddOn[i-1];
}
 cout<<"add on channels:  "<<bill2<<"\n";
for(int i=1;i<10;i++)
{
for(int j=0;j<10;j++)
if(pack[j]==i)
 bill3=bill3+defPack[i-1];
}
cout<<"packs :  "<<bill3<<"\n";
bill+=(bill2+bill3);
 cout<<"total amount :  "<<bill<<"\n";
 cout<<"........enter any key to continue";
char cc=getchar();
//system("clear");
break;
}
 }
		  if(flag==0)
					 cout<<"\n Sorry User no. not found or vacant...!!";
		  file.close();
}
int skytel::check(int r)
{
		  int flag=0;
		  ifstream fin("Record.dat",ios::in);
		  while(!fin.eof())
		  {
					 fin.read((char*)this,sizeof(skytel));
					 if(user_no==r)
					 {
								flag=1;
								break;
					 }
		  }

		  fin.close();
		  return(flag);
}
void skytel::report()
{
	 int c=0;
	 ifstream fin("Record.dat",ios::in);
	cout<<"\n Customer Details";
                   cout<<"\n----------------------------------------------------------------------------------------- \n";
			       cout<<"\tUser no: ";
			       cout<<"\t\t    Name: ";
			       cout<<"\t\t   Address: ";
			       cout<<"\t\t Phone no: \n\n";	 while( fin.read((char*)this,sizeof(skytel)))
		  {

				cout<<setw(10)<<user_no;
			cout<<"\t\t\t"<<setw(10)<<name;
			cout<<"\t\t"<<setw(10)<<address;
			cout<<"\t\t"<<setw(10)<<phone<<"\n";
                                      c++;
	  }
	  if(c==0)
		  {
		 cout<<"\n Sorry User no. not found or vacant...!!";
	  }
		  char cc=getchar();
		  cout<<"........enter any key to continue";
cc=getchar();
	  //system("clear");
	  fin.close();
}
int main()
{

		 int ch=0;
		  system("clear");
		  cout<<"\n\t\t\t****************************";
		  cout<<"\n\t\t\t*\t  SKYTEL           *";
          cout<<"\n\t\t\t*\t   DTH             *";
		  cout<<"\n\t\t\t****************************\n";
          cout<<"\n \t\t\t __________________________";
          cout<<"\n \t\t\t |Made by :Dhruvil Patel  | \n \t\t\t |\t   Ayush Kaura    | \n \t\t\t |\t   Rohith Nair    | \n \t\t\t |\t   Siddhesh Darak |";
		  cout<<"\n \t\t\t __________________________";
		  cout<<"\n\n\n\n\t\t\t Press any key to continue ";
		  char cc=getchar();
		  system("clear");
		  do
			 {
				  cout<<"\n\t\t\t\t*************";
				  cout<<"\n\t\t\t\t* MAIN MENU *";
				  cout<<"\n\t\t\t\t*************";
				  cout<<"\n\t\t\t\t1.User ";
				  cout<<"\n\t\t\t\t2.Channels ";
				  cout<<"\n\t\t\t\t3.Billing ";
				  cout<<"\n\t\t\t\t4.Report ";
				  cout<<"\n\t\t\t\t5.Exit \n";
cin>>ch;
system("clear");
switch(ch)
{
case 1:
		     obj.main_menu1();system("clear");
             break;
case 2:
			 obj.main_menu2();system("clear");
			 break;
case 3:
			 obj.BillStatus();system("clear");
			 break;
case 4:
			 obj.report();system("clear");
			 break;
case 5:
    cout<<" \n \n \t \t thankyou \t \t \n \n ";
    break;
default:
    cout<<"invalid";
}
}while(ch!=5);
}