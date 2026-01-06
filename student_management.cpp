#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

struct student{
    int roll;
    char name[20];
    char course[20];
    int m1,m2,m3;
    int attendance;
};

char getGrade(float p){
    if(p>=75) return 'A';
    else if(p>=60) return 'B';
    else if(p>=40) return 'C';
    else return 'F';
}

bool sortByRoll(student a,student b){
    return a.roll<b.roll;
}

int main(){
    char user[10],pass[10];
    int choice;
    student s;

    cout<<"\nEnter Username: ";
    cin>>user;
    cout<<"Enter Password: ";
    cin>>pass;

    if(!((strcmp(user,"admin")==0 && strcmp(pass,"123")==0) || (strcmp(user,"teacher")==0 && strcmp(pass,"456")==0))){
        cout<<"Invalid Login!";
        return 0;
    }

    cout<<"\nLogin Successful!\n";

    do{
        cout<<"\n1.ADD\n2.VIEW\n3.UPDATE\n4.DELETE\n5.SEARCH\n6.SORT\n7.EXIT\n\nEnter your choice: ";
        cin>>choice;

        if(choice==1){
            ofstream f("data.dat", ios::app | ios::binary);  
            cout<<"\nRoll no: ";
            cin>>s.roll;
            cout<<"Name: ";
            cin>>s.name;
            cout<<"Course: ";
            cin>>s.course;
            cout<<"M1: ";
            cin>>s.m1;
            cout<<"M2: ";
            cin>>s.m2;
            cout<<"M3: ";
            cin>>s.m3;
            cout<<"Attendance: ";
            cin>>s.attendance;
            cout<<"\n";
            f.write((char*)&s,sizeof(s));
            f.close();
        
            cout<<"\nStudent Added Successfully!\n";
        }
        else if(choice==2){
            ifstream f("data.dat", ios::binary);
            while(f.read((char*)&s,sizeof(s))){
                int total=s.m1+s.m2+s.m3;
                float per=total/3.0;
                cout<<"\n";
                cout<<s.roll<<" "<<s.name<<" "<<s.course<<endl;
                cout<<"Total: "<<total<<endl;
                cout<<"%age: "<<per<<endl;
                cout<<"Grade: "<<getGrade(per)<<endl;
                cout<<" "<<(per>=40 ? "pass" : "fail")<<endl;
                cout<<"Attendance: "<<s.attendance;
                cout<<"\n";
            }
            f.close();
        }
        else if(choice==3){
        fstream f("data.dat", ios::in | ios::out | ios::binary);
        int r;
        cout<<"Enter Roll no. to Update: ";
        cin>>r;

         while(f.read((char*)&s, sizeof(s))){
            if(s.roll==r){
                cout<<"Enter NEW Values: \n";
                 cout<<"M1: ";
                 cin>>s.m1;
                 cout<<"M2: ";
                 cin>>s.m2;
                 cout<<"M3: ";
                 cin>>s.m3;
                 cout<<"Attendance: ";
                 cin>>s.attendance;
                 cout<<"\n";
                 std::streampos pos = f.tellg();
                 pos -= static_cast<std::streamoff>(sizeof(s));

                 f.seekg(pos);
                 f.seekp(pos);

                 f.write((char*)&s, sizeof(s));
                 f.flush();

                 cout << "Updated successfully\n";
                 break;

            }
        }
        f.close();
        }
        else if(choice==4){
            ifstream f("data.dat", ios::binary);
            ofstream t("temp.dat", ios::binary);
            int r;
            cout<<"\nEnter Roll no. to Delete: ";
            cin>>r;

            while(f.read((char*)&s,sizeof(s))){
                if(s.roll!=r) t.write((char*)&s,sizeof(s));
            }
            f.close();
            t.close();
            remove("data.dat");
            rename("temp.dat", "data.dat");
            cout <<"Deleted successfully\n";
        }
        else if(choice==5){
            ifstream f("data.dat", ios::binary);
            int r;
            cout<<"\nEnter Roll no. to Search: ";
            cin>>r;

            while(f.read((char*)&s, sizeof (s))){
                if(s.roll==r){
                    cout<<"Found: "<<s.name<<" "<<s.course<<endl;
                }
            }
            f.close();
        }
        else if(choice==6){
            student arr[50];
            int n=0;
            ifstream f("data.dat", ios::binary);
            while(f.read((char*)&arr[n], sizeof(student))){
                n++;
            }
                f.close();

                sort(arr,arr+n,sortByRoll);

                ofstream o("data.dat", ios::binary);
                for(int i=0;i<n;i++)
                o.write((char*)&arr[i], sizeof(student));
                o.close();
            
            cout<<"\nSorted by Roll no.!";
        }
    }
    while(choice!=7);

    ifstream f("data.dat", ios::binary);
    ofstream txt("report.txt");  
    ofstream pdf("report.pdf");   
    while(f.read((char*)&s, sizeof(s))){
        int total=s.m1+s.m2+s.m3;
        float per=total/3.0;
        txt<<s.name<<" "<<total<<" "<<per<<" "<<getGrade(per)<<endl;
        pdf<<s.name<<" "<<total<<" "<<per<<" "<<getGrade(per)<<endl;
    }
    f.close();
    txt.close();
    pdf.close();

    cout<<"Report Generated!";
    return 0;
}