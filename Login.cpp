#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

string user_name;

void write()
{
	
		cout<<"Enter the user name"<<endl;
		getline(cin,user_name);
	
}

void store_username()
{
	fstream nfile;
	nfile.open("login.txt",ios::app);
	
		nfile<<user_name<<endl;
	
	nfile.close();
}
void read() {
    string word;
    fstream file;
    file.open("login.txt", ios::in);
   
    while (getline(file, word) ){  
        name[idx] = parse(word, 1);
        gender[idx] = parse(word, 2);
        password[idx] = parse(word, 3);
        
        idx++;
    }
    file.close();
}

string name[100];
string gender[100];
string password[100];
int idx = 0;


string parse(string record, int field) {
    int count = 1;
    string items = "";
    for (int i = 0; i < record.length(); i++) {
        if (record[i] == ',') {
            count++;
        } else if (count == field) {
            items += record[i];
        }
    }
    return items;
}
int main()
{
	write();
store_username();	
	read();
	int op;
	cout<<"WELCOME TO THE GAME "<<endl;
	cout<<"1. sign in "<<endl;
	cout<<"2. sign up"<<endl;
	cout<<"enter any option "<<endl;
	cin>>op;
	if (op==1)
	
}


string num, pass;
    cout << "Enter your name: ";
    cin >> num;
    cout << "Enter your password: ";
    cin >> pass;

    bool found = false;
    for (int i = 0; i < idx; i++) {
        if (num == name[i] && pass == password[i]) {
           system("cls");
		    display(i);
            found = true;
            break;

