// Student-Record-Management-System (Mini Project)

#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

// the class that stores data
class Student 
{
    int rollno;
    char name[50];
    int eng_marks, math_marks, sci_marks, lang2_marks, cs_marks;
    double average;
    char grade;
    
    public:
    void getdata();
    void showdata() const;
    void calculate();
    int retrollno() const;
}; 
//class ends here

void Student::calculate()
{
    average=(eng_marks+math_marks+sci_marks+lang2_marks+cs_marks)/5.0;
    if(average>=90)
    grade ='O'; // Ordinary grade
    else if(average>=70)
    grade='A';
    else if(average>=60)
    grade='B';
    else if(average>=50)
    grade='C';
    else
    grade='F';
}

void Student::getdata()
{
    cout<<"Enter Student's Roll Number : ";
    cin>>rollno;
    
    cout<<"Enter Student's Name: ";
    cin.ignore();
    cin.getline(name,50);

    cout<<"\n\nEnter Student's Marks"<<endl;
    cout<<"All Marks should be out of 100";

    cout<<"\n\nEnter Marks in English: ";
    cin>>eng_marks;
    
    cout<<"Enter Marks in Math: ";
    cin>>math_marks;

    cout<<"Enter Marks in Science: ";
    cin>>sci_marks;
    
    cout<<"Enter Marks in Second Language: ";
    cin>>lang2_marks;
    
    cout<<"Enter Marks in Computer Science: ";
    cin>>cs_marks;
    calculate();
}

//display
void Student::showdata() const
{
    cout<<"\nRoll Number of Student : "<<rollno;
    cout<<"\nName of Student        : "<<name;
    cout<<"\n.......................................";
    cout<<"\nEnglish          : "<<eng_marks;
    cout<<"\nMaths            : "<<math_marks;
    cout<<"\nScience          : "<<sci_marks;
    cout<<"\nSecond Language  : "<<lang2_marks;
    cout<<"\nComputer Science : "<<cs_marks;
    cout<<"\n.............................";
    cout<<"\nAverage Marks (%)   : "<<average<<" %";
    cout<<"\nGrade of Student is : "<<grade;
}

int Student::retrollno() const
{
return rollno;
}

//function declaration

void create_student();
void display_sp(int);//display particular record
void display_all(); // display all records
void delete_student(int);//delete particular record
void change_student(int);//edit particular record

//Main Function

int main()
{
    char ch;
    cout<<setprecision(2);
    
    do
    {
        char ch;
        int num;
        system("cls");
        cout<<"Welcome to Student Registration Management System"<<endl;
        cout<<"\n\t*** MENU ***"<<endl;
        cout<<"\n1. Create a New Student Record "<<endl;
        cout<<"2. Search Students Record"<<endl;
        cout<<"3. Display all Students Records"<<endl;
        cout<<"4. Delete Student Record"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"\nEnter your Choice : ";
        cin>>ch;
        
        system("cls");
        
        switch(ch)
        {
            case '1': create_student(); 
                    break;
            case '2': cout<<"\n\n\tEnter The Roll Number: "; 
                    cin>>num;
                    display_sp(num); 
                    break;
            case '3': display_all(); 
                    break;
            case '4': cout<<"\n\n\tEnter The Roll Number: ";
                    cin>>num;
                    delete_student(num);
                    break;
            case '5': cout<<"Exiting, Thank you!";
                    exit(0);
        }
    
    }
    while(ch!='5');
    return 0;
}

//Write Student Details to File 
void create_student()
{
    Student stud;
    ofstream oFile;
    oFile.open("student.dat",ios::binary|ios::app); 
    stud.getdata();
    oFile.write(reinterpret_cast<char *> (&stud), sizeof(Student));
    oFile.close();
    cout<<"\nStudent's Record has been Created.. ";
    cin.ignore();
    cin.get();
}

// Read File Records and display
void display_all()
{
    Student stud;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be Opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }

    cout<<"\n\n\t*** DISPLAYING ALL RECORDS ***\n\n";
    while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(Student)))
    {
        stud.showdata();
        cout<<"\n\n====================================\n";
    }

    inFile.close();
    cin.ignore();
    cin.get();
}

//Read Specific Record Based on Roll Number

void display_sp(int n)
{
    Student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile)
    {
        cout<<"File could not be Opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    
    bool flag=false;
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(Student)))
    {
        if(stud.retrollno()==n)
        {
            stud.showdata();
            flag=true;
        }
    }
    
    iFile.close();
    if(flag==false)
    cout<<"\n\nRecord does not exist";
    cin.ignore();
    cin.get();
}

//Delete Record with Particular Roll Number

void delete_student(int n)
{
    Student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile)
    {
        cout<<"File could not be Opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat",ios::out);
    iFile.seekg(0,ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(Student)))
    {
        if(stud.retrollno()!=n)
        {
            oFile.write(reinterpret_cast<char *> (&stud), sizeof(Student));
        }
    }
    oFile.close();
    iFile.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout<<"\n\n\tRecord Deleted ..";
    cin.ignore();
    cin.get();
}