#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;
class EMP_CLASS
{
 typedef struct EMPLOYEE
 {
 char name[10];
 int emp_id;
 int salary;
 }Rec;
 typedef struct INDEX
 {
 int emp_id;
 int position;
 }Ind_Rec;
 Rec Records;
 Ind_Rec Ind_Records;
 public: 
  EMP_CLASS()
  {
   strcpy(Records.name,"");
  }
  void Create();
  void Display();
  void Delete();
  void Add();
  void Search();
};
void EMP_CLASS::Create()
{
 int i,j;
 char ch='y';
 fstream seqfile;
 fstream indexfile;
 i=0;
 indexfile.open("IND.DAT",ios::out);
 seqfile.open("EMP.DAT",ios::out);
 do
 {
  cout<<"\n Enter Name: ";
  cin>>Records.name;
  cout<<"\n Enter Emp_ID: ";
  cin>>Records.emp_id;
  cout<<"\n Enter Salary: ";
  cin>>Records.salary;
  seqfile.write((char*)&Records,sizeof(Records))<<flush;
  Ind_Records.emp_id=Records.emp_id;
  Ind_Records.position=i;
  indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
  i++;
  cout<<"\nDo you want to add more records?";
  cin>>ch;
  }while(ch=='y');
  seqfile.close();
  indexfile.close();
}
void EMP_CLASS::Display()
{
 fstream seqfile;
 fstream indexfile;
 int n,i,j;
 seqfile.open("EMP.DAT",ios::in);
 indexfile.open("IND.DAT",ios::in);
 indexfile.seekg(0,ios::beg);
 seqfile.seekg(0,ios::beg);
 cout<<"\n The Contents of file are ..."<<endl;
 i=0;
 while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
 {
   i=Ind_Records.position*sizeof(Rec);
   seqfile.seekg(i,ios::beg);
   seqfile.read((char *)&Records,sizeof(Records));
   if(Records.emp_id!=-1)
   {   
   cout<<"\nName: "<<Records.name<<flush;
   cout<<"\nEmp_ID: "<<Records.emp_id;
   cout<<"\nSalary: "<<Records.salary;
   cout<<"\n";
    }
 }
 seqfile.close();
 indexfile.close();
}
void EMP_CLASS::Delete()
{
 int id,pos;
 cout<<"\n For deletion,";
 cout<<"\n Enter the Emp_ID for searching ";
 cin>>id;
 fstream seqfile;
 fstream indexfile;
 seqfile.open("EMP.DAT",ios::in|ios::out);
 indexfile.open("IND.DAT",ios::in|ios::out);
 seqfile.seekg(0,ios::beg);
 indexfile.seekg(0,ios::beg);
 pos=-1;
 while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
 {
  if(id==Ind_Records.emp_id)
  {
   pos=Ind_Records.position;
   Ind_Records.emp_id=-1;
   break;
  }
 }
 if(pos==-1)
 {
  cout<<"\n The record is not present in the file";
  return;
 }
 int offset=pos*sizeof(Rec);
 seqfile.seekp(offset);
 strcpy(Records.name,"");
 Records.emp_id=-1;
 Records.salary=-1; 
 seqfile.write((char*)&Records,sizeof(Records))<<flush;
 offset=pos*sizeof(Ind_Rec);
 indexfile.seekp(offset); 
 Ind_Records.emp_id=-1; 
 Ind_Records.position=pos;
 indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
 seqfile.seekg(0);
 indexfile.close();
 seqfile.close();
 cout<<"\n The record is Deleted!!!";
}
void EMP_CLASS::Add()
{
 fstream seqfile;
 fstream indexfile;
 int pos;
 indexfile.open("IND.DAT",ios::in);
 indexfile.seekg(0,ios::end);
 pos=indexfile.tellg()/sizeof(Ind_Records);
 indexfile.close();
 indexfile.open("IND.DAT",ios::app);
 seqfile.open("EMP.DAT",ios::app);
 cout<<"\n Enter the record for appending";
 cout<<"\nName: ";cin>>Records.name;
 cout<<"\nEmp_ID: ";cin>>Records.emp_id;
 cout<<"\nSalary: ";cin>>Records.salary;
 seqfile.write((char*)&Records,sizeof(Records));
 Ind_Records.emp_id=Records.emp_id;        
 Ind_Records.position=pos;                          
 indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
 seqfile.close();
 indexfile.close();
 cout<<"\n The record is Appended!!!";
}
void EMP_CLASS::Search()
{
 fstream seqfile;
 fstream indexfile;
 int id,pos,offset;
 cout<<"\n Enter the Emp_ID for searching the record ";
 cin>>id;
 indexfile.open("IND.DAT",ios::in);
 pos=-1;
 while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
 {
  if(id==Ind_Records.emp_id)
  {
   pos=Ind_Records.position;
   break;
  }
 }
  if(pos==-1)
  {
  cout<<"\n Record is not present in the file";
  return;
  }
  offset=pos*sizeof(Records);
  seqfile.open("EMP.DAT",ios::in);
  seqfile.seekg(offset,ios::beg);
  seqfile.read((char *)&Records,sizeof(Records));
  if(Records.emp_id==-1)
  {
  cout<<"\n Record is not present in the file";
  return;
  }
  else 
  {
  cout<<"\n The Record is present in the file and it is...";
  cout<<"\n Name: "<<Records.name;
  cout<<"\n Emp_ID: "<<Records.emp_id;
  cout<<"\n Salary: "<<Records.salary;
  }
  seqfile.close();
  indexfile.close();
}
int main()
{
 EMP_CLASS List;
 char ans='y';
 int choice,key;
 do
 {
  cout<<"\nMain Menu"<<endl;
  cout<<"\n 1.Create";
  cout<<"\n 2.Display";
  cout<<"\n 3.Delete";
  cout<<"\n 4.Add";
  cout<<"\n 5.Search";
  cout<<"\n 6.Exit";
  cout<<"\n Enter your choice: ";
  cin>>choice;
  switch(choice)
  {
  case 1:List.Create();
      break;
  case 2:List.Display();
      break;
  case 3:List.Delete();
      break;
  case 4:List.Add();
      break;
  case 5:List.Search();
      break;
  case 6:exit(0);
  }
 cout<<"\n\t Do you want to go back to Main Menu?";
 cin>>ans;
 }while(ans=='y');
 return 0;
}

