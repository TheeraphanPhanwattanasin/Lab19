#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
     ifstream source;
     source.open(filename);
     string info;

     while(getline(source,info)){
        char format[] = "%[^:]: %d %d %d";
        char textname[100];
        int a,b,c;

        sscanf(info.c_str(),format, textname,&a,&b,&c);
        names.push_back(textname);
        int sum = a+b+c;
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
     }
}

void getCommand(string &command,string &key){
cout << "Please input your command: ";
string text;
getline(cin,text);
char format[] = "%s %[^\n]";
char com[100],k[100];
sscanf(text.c_str(),format,com,k);
command = com;
key = k;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
cout << "---------------------------------\n";
int count = 0;
for(unsigned int i=0; i < names.size(); i++){
string name = names[i];
if(key == toUpperStr(name)){
cout << names[i] << "'s score = " << scores[i] << "\n";
cout << names[i] << "'s grade = " << grades[i] << "\n";
count++;
}}
if(count == 0) cout << "Cannot found.\n";
cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
cout << "---------------------------------\n";
int count = 0;
for(unsigned int i=0; i < names.size(); i++){
if(grades[i]== key[0])
cout << names[i] << " (" << scores[i] << ")\n";
count++;
}
if(count == 0) cout << "Cannot found.\n";
cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
