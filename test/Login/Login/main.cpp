#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	char username[10], password[10];
	char f_user[10], f_pass[10], f_file[10];
	cout << "username: ";
//	cin.getline(username,10);
	cout << "password: ";
//	cin.getline(password,10);
	ifstream fin("database\\users.txt");
	while (fin.getline(fin, f_user, ',')) {
		cout << "User: " << f_user << " " ; 
		
		fin.getline(fin, f_pass, ',') ;
		cout << "Passd: " << f_pass << " " ;
		
		fin.getline(fin, f_file, ',') ;
		cout << "File: " << f_file << " "  ; 
}

	return 0;
}