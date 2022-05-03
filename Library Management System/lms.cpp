#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<fstream>
#include <sstream>
#include <cstring>

using namespace std;

class book{
    public:
        string title,author,ISBN,publication,Avaibility,issue_by,issue_dt;
    book(){
        title="No_Book";
        author="na";
        ISBN="na";
        publication="na";
        Avaibility="na";
        issue_by="na";
        issue_dt="na";
    }
    book(vector<string> row){
        title=row[0];
        author=row[1];
        ISBN=row[2];
        publication=row[3];
        Avaibility=row[4];
        issue_by=row[5];
        issue_dt=row[6];
    }
    
    int show_duedate(int); //to show duedate for the book
    int Book_request(string); //to issue the book
};
class book_db{
    public:
    vector<book> bookDB; // vector to store books
    void bookList(int); // to give list of books in library along with its details and avalability
    void Add(); // to add a book in database
    void Update(); // to update a book in database
    void Delete(); // to remove a book from database
    int search(string); // to search a book in database
};
class user{
    public:
        string id,pass,name,role;
    user(){
        id="idOfUser";
        pass="passOfUser";
        name="nameOfUser";
        role="noRole";
    }
    void start(); //to reflect login page to user
};
class user_db{
    public:
    vector<user> userDB;

    void Add(); // to add an user in database
    void Update(); // to update an user details in database
    void Delete(); // to remove an user from database
    int search(string); // to search an user in database
};

book_db books; //the vector of books database
user_db users; //the vector of users database

void getDatabase(){ //function to fetch database from repective csv files of books and users
    int i;
    // getting database
    
    // for books

    ifstream fin;
    fin.open("books.csv", ios::in); //from books.csv file
    vector<string> row;
    string word, temp;

    while (fin >> temp) {  
        row.clear();
        stringstream s(temp);
        while (getline(s, word, ',')){
            row.push_back(word);
        }

        book obj=book(row);

        books.bookDB.push_back(obj); //updating books vector
    }
    
    fin.close();
    
    // for users
    user objt;
    fin.open("users_db.csv", ios::in); //from users_db.csv file 
    while (fin >> temp) {  
        row.clear();
        stringstream s(temp);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        objt.id=row[0];
        objt.pass=row[1];
        objt.name=row[2];
        objt.role=row[3];

        users.userDB.push_back(objt); //updating users vector
    }
    fin.close();
}

class prof:public user{
    public:
        int fine_amount; //to store the fine amount
        vector<book>books_issued; //to store the books issued by professor in vector
    prof(){
        fine_amount=0; //initializing fine amount to zero
    }
    void prof_login(int); //the dashboard like page for professors to have list of functions that can be performed by them
    void calculate_fine(vector<book>,int); //the function to calculate and reflect fine
    void clear_fine_amount(int); //the function to clear fine amount for books
};
class student:public user{
    public:
        int fine_amount; //to store the fine amount
        vector<book>books_issued; //to store the books issued by student in vector
    student(){
        fine_amount=0; //initializing fine amount to zero
    }
    void student_login(int); //the dashboard like page for students to have list of functions that can be performed by them
    void calculate_fine(vector<book>,int); //the function to calculate and reflect fine
    void clear_fine_amount(int); //the function to clear fine amount for books
};
class librarian:public user{
    public:
    void librarian_login(int); //the dashboard like page for librarian to have list of functions that can be performed by them
};

void user::start(){

    string id,pass;
    int input;
    while (1)
    {
       system("clear");
        cout<<"\n\n Welcome to IITK Library\n";
        
        cout<<"\n1. Login with credentials\n2. Exit\n\n";
        int i; cin>>i;
        if(i==1){
            system("clear");
            cout<<"\n\nPlease credentials to login";
            cout<<"\nenter your id: "; //to take id from user
            cin>>id;
            cout<<"enter you pass: "; //to take password from user
            cin>>pass;
        
            input= users.search(id); // to crosscheck the id with the database

            if(input!=-1 && pass.compare(users.userDB[input].pass)==0){ //the user is present and password matches
                //the user is sent to respective dashbord pages according to their role in database
                if(users.userDB[input].role.compare("professor")==0){ 
                    system("clear");
                    prof professor; //creating a professor object
                    professor.prof_login(input); 
                }
                else if(users.userDB[input].role.compare("student")==0){
                    system("clear");
                    student stud; //creating a student object
                    stud.student_login(input);
                }
                else if(users.userDB[input].role.compare("librarian")==0){
                    system("clear");
                    librarian employee; //creating a librarian object
                    employee.librarian_login(input);
                }
                
            }
            else{
                cout<<"\n\nPlease choose correct option and try again with correct credentials";
                cout<<"\n";
                cout << "\nPress any char to Continue: ";
                char c;
                cin>>c;
                system("clear");
            }
        }
        else{
            system("clear");
            exit(0);
        } 
    }
}
int user_db::search(string id){
    int i,f=0;
    for(i=0;i<users.userDB.size();i++){
            if(users.userDB[i].id.compare(id)==0){ //matching id with the one present in database
                f++;
                break;
            }
    }

    if (f == 0){
        cout << "Record not found\n";
        return -1;
    }
    return i; //returning the the index where the user details are present in vector
}
void user_db::Add(){
    user newUser;
    string j;
    int i;
    cout<<"Fill details to add a user:\n";

    cout<<"id: ";
    cin>>j;
    user obj;

    if(users.search(j)!=-1) {
        cout<<"user with this id already present.";
        return;//returning as no new user can be added with same id
    }
    else{
        cout<<"You can continue\n\n";
    }

    newUser.id=j;

    newUser.pass="iitk"; //by default the password is set as "iitk" which can be furtur changed after login by users

    cout<<"Name: ";
    cin>>j;
    newUser.name=j; //name for user

    cout<<"\nselect role:\n1. professor\n2.student\n3. librarian\n";
    cin>>i;

    if(i==1) newUser.role="professor";
    else if(i==2) newUser.role="student";
    else if(i==3) newUser.role="librarian";

    // adding the new user so created in database as well as vector with users
    users.userDB.push_back(newUser); 

    fstream fout;
    
    fout.open("users_db.csv", ios::out);
    
    for(int i=0;i<users.userDB.size();i++){
        fout<<users.userDB[i].id<<",";
        fout<<users.userDB[i].pass<<",";
        fout<<users.userDB[i].name<<",";
        fout<<users.userDB[i].role<<"\n";
    }
    fout.close();  

    cout<<"\n------------User Added-------------";
}
void user_db::Update(){
    string id,newname,role;
    int i;
    cout<< "enter credentials to update:\n";
    cout<<"id: ";
    cin>>id;

    i=users.search(id);
    if(i==-1){
        cout<<"can't find the user with such credentials\n"; //no user to update thus returning
        return;
    }

    cout<<"updating details of: "<<users.userDB[i].name;
    cout<<"new Name: "; //updating name of user
    cin>>newname;
    cout<<"\nselect role:\n1. professor\n2.student\n3. librarian\n";
    cin>>i; // updating role of user

    if(i==1) role="professor";
    else if(i==2) role="student";
    else if(i==3) role="librarian";

    users.userDB[i].name=newname;
    users.userDB[i].role=role;

    fstream fout; //updating the csv database file
    
    fout.open("users_db.csv", ios::out);
    
    for(int i=0;i<users.userDB.size();i++){
        fout<<users.userDB[i].id<<",";
        fout<<users.userDB[i].pass<<",";
        fout<<users.userDB[i].name<<",";
        fout<<users.userDB[i].role<<"\n";
    }
    fout.close(); 
    
    cout<<"---------- Updated----------";
}
void user_db::Delete(){
    string id;
    int i,k;
    cout<< "enter credentials to delete:\n";
    cout<<"id: ";
    cin>>id;
    // if(id==person[0]){
    //     cout<<"you can't delete yourself from the database";
    //     return;
    // } 

    k=users.search(id);
    if(i==-1){
        cout<<"can't find the user with such credentials\n"; // no user to be deleted
        return;
    }

    fstream fout;
    
    fout.open("users.csv", ios::out); //updating csv database by deleting the user
    
    int f=0;
    for(i=0;i<users.userDB.size();i++){
        if(i!=k){
            fout<<users.userDB[i].id<<",";
            fout<<users.userDB[i].pass<<",";
            fout<<users.userDB[i].name<<",";
            fout<<users.userDB[i].role<<"\n";
        }
    }
    fout.close(); 
    users.userDB.clear();
    getDatabase();
    
    cout<<"---------- Deleted----------";

}

void book_db::bookList(int j){ // getting book list 
    cout<<"********************** Book List *****************************\n";
    cout<<"total books= "<<books.bookDB.size()<<endl; //for number of books in library
    int i;
    for(i=0;i<books.bookDB.size();i++){
        //printing details for each book
        cout<<"\nTitle: "<<books.bookDB[i].title<<endl;
        cout<<"Author: "<<books.bookDB[i].author<<endl;
        cout<<"ISBN: "<<books.bookDB[i].ISBN<<endl;
        cout<<"Publication: "<<books.bookDB[i].publication<<endl;
        cout<<"Availability: "<<books.bookDB[i].Avaibility<<endl;
        if(j && books.bookDB[i].Avaibility.compare("no")==0){ // if book is issued to someone and librarian in fetching the book details
            j=users.search(books.bookDB[i].issue_by);
            cout << "Issued by user with id: "<<users.userDB[j].id<<"; name: "<<users.userDB[j].name<<"; role: "<<users.userDB[j].role<<endl; //the details of user who issued
            books.bookDB[i].show_duedate(j); //the issue and due date
        }
    }
}
int book_db::search(string isbn){ //searching a book in database using its isbn
    int i,f=0;
    for(i=0;i<books.bookDB.size();i++){
            if(books.bookDB[i].ISBN.compare(isbn)==0){
                f++;
                break;
            }
    }

    if (f == 0){
        cout << "Record not found\n";
        return -1;
    }
    return i;
}
void book_db::Add(){ //adding a book to database
    cout<<"Please provide the details of the book to be added\n";
    book newBook;

    cout<<"\nISBN: ";
    cin>>newBook.ISBN;

    if(books.search(newBook.ISBN)!=-1) {
        cout<<"book with this isbn is already present"; //thus book can't be added
        return;
    }
    //getting details of book from user
    cout<<"So you can proceed to add one\n";
    cout<<"Title: ";
    cin>>newBook.title;
    cout<<"\nAuthor: ";
    cin>>newBook.author;
    cout<<"\nPublication: ";
    cin>>newBook.publication;

    newBook.Avaibility="yes";
    newBook.issue_by="na";
    newBook.issue_dt="na";

    books.bookDB.push_back(newBook); //appending the book in database vector

    fstream fout; //adding book in csv file
    
    fout.open("books.csv", ios::out);
    
    int f=0;
    for(int i=0;i<books.bookDB.size();i++){
        fout<<books.bookDB[i].title<<",";
        fout<<books.bookDB[i].author<<",";
        fout<<books.bookDB[i].ISBN<<",";
        fout<<books.bookDB[i].publication<<",";
        fout<<books.bookDB[i].Avaibility<<",";
        fout<<books.bookDB[i].issue_by<<",";
        fout<<books.bookDB[i].issue_dt<<"\n";
    }
    fout.close();  

    cout<<"\n------------Book Added-------------";
}
void book_db::Update(){ //updating a book details
    string isbn,avaibility;
    int i,j;
    cout<< "enter details to update:\n";
    cout<<"isbn: ";
    cin>>isbn;

    i=books.search(isbn);
    if(i==-1){
        cout<<"can't find the book with such ISBN\n"; //thus can't be updated
        return;
    }

    cout<<"want to update:\n1. details\n2. avaibility as yes/no\n";
    cin>>j;

    if(j==1){
        //for updating details
        cout<<"updating details of ISBN: "<<books.bookDB[i].ISBN;
        cout<<"\nnew Title: ";
        cin>>books.bookDB[i].title;
        cout<<"new Author: ";
        cin>>books.bookDB[i].author;
        cout<<"new Publication: ";
        cin>>books.bookDB[i].publication;
    }
    else if(j==2){
        //the issued updation
        cout<<"change avaibility to yes/no";
        cout<<"\n1. to yes\n2. to no\n";
        int k; cin>>k;
        if(k==1){
            books.bookDB[i].Avaibility="yes";
            books.bookDB[i].issue_by="na";
            books.bookDB[i].issue_dt="na";
        }
        else if(k==2){
            books.bookDB[i].Avaibility="no";
            string s;
            cout<<"issued to (id of person): "; cin>>s;
            if(users.search(s)==-1){
                cout<<"No user with this id is in database."<<endl;//thus book can't be issued
                return;
            }
            books.bookDB[i].issue_by=s;
            cout<<"\nissued on (date in ddmmyyyy): "; cin>>s;
            books.bookDB[i].issue_dt=s;
        }
    }
    fstream fout; // updating the book database with the details
    
    fout.open("books.csv", ios::out);
    
    int f=0;
    for(int i=0;i<books.bookDB.size();i++){
        fout<<books.bookDB[i].title<<",";
        fout<<books.bookDB[i].author<<",";
        fout<<books.bookDB[i].ISBN<<",";
        fout<<books.bookDB[i].publication<<",";
        fout<<books.bookDB[i].Avaibility<<",";
        fout<<books.bookDB[i].issue_by<<",";
        fout<<books.bookDB[i].issue_dt<<"\n";
    }
    fout.close(); 
    
    cout<<"---------- Updated----------";
}
void book_db::Delete(){ //deleting a book
    string isbn;
    int i,k;
    cout<< "enter credentials to delete:\n";
    cout<<"isbn: ";
    cin>>isbn;

    k=books.search(isbn);
    if(k==-1){
        cout<<"can't find the book with such ISBN\n"; // thus returning
        return;
    }

    fstream fout; // deleting the book from the database
    
    fout.open("books.csv", ios::out);
    
    int f=0;
    for(i=0;i<books.bookDB.size();i++){
        if(i!=k){
            fout<<books.bookDB[i].title<<",";
            fout<<books.bookDB[i].author<<",";
            fout<<books.bookDB[i].ISBN<<",";
            fout<<books.bookDB[i].publication<<",";
            fout<<books.bookDB[i].Avaibility<<",";
            fout<<books.bookDB[i].issue_by<<",";
            fout<<books.bookDB[i].issue_dt<<"\n";
        }  
    }
    fout.close();
    books.bookDB.clear();
    getDatabase();
    
    cout<<"---------- Deleted----------";
}

int book::show_duedate(int id){ //to show issue as well as due date of the book

    if(this->issue_by.compare(users.userDB[id].id)==0){
        int date = stoi(this->issue_dt);
        int day,mon,yr;

        yr=date/10000;date=date%10000;
        mon=date/100;day=date%100;
        cout<<"issued date (in yyyy/mm/dd) was "<<yr<<"/"<<mon<<"/"<<day<<endl;

        if(users.userDB[id].role.compare("professor")==0){
            day+=60; //as book can be issued for 60 days to professor
        }
        else if(users.userDB[id].role.compare("student")==0){
            day+=30; //as book can be issued for 30 days to professor
        }
        while(1){
            if(mon==1||mon==3||mon==5||mon==7||mon==8||mon==10){
                if(day>31){
                    day=day-31;
                    mon++;
                }
                else break;
            }
            else if(mon==4||mon==6||mon==9||mon==11){
                if(day>30){
                    day=day-30;
                    mon++;
                }
                else break;
            }
            else if(mon==2){
                if(yr%400==0 && day>29){
                    day=day-30;
                    mon++;
                }
                else if(yr%100==0 && day>28){
                    day=day-28;
                    mon++;
                }
                else if(yr%4==0 && day>29){
                    day-=29;
                    mon++;
                }
                else if(day>28){
                    day-=28;
                    mon++;
                }
                else{
                    break;
                }
            }
            else if(mon==12){
                if(day>31){
                    day-=31;
                    mon=1;
                    yr++;
                }
                else break;
            }
        }
        date=(yr*10000)+(mon*100)+day;
        cout<<"due date (in yyyy/mm/dd): "<<yr<<"/"<<mon<<"/"<<day<<"\n";
        
        return date;
    }
    else{
        cout<<"either book not issued or wrong credentials";
        return -1;
    }
}
int book::Book_request(string person){//to issue a book
    string isbn=this->ISBN;
    int id= users.search(person);
    int bn,i,j;
    bn=books.search(isbn);
    if(bn!=-1 && books.bookDB[bn].Avaibility.compare("yes")==0){
        books.bookDB[bn].Avaibility="no";
        books.bookDB[bn].issue_by=users.userDB[id].id;

        cout<<"\ntoday's date in yyyymmdd: ";
            string s;cin>>s;
        books.bookDB[bn].issue_dt=s;

    }
    else{
        cout<<"\nThe book with such ISBN is not available to issue.";
        return 0;
    }
    
    fstream fout; //updating the csv book databse with the issued details 
    
    fout.open("books.csv", ios::out);
    
    int f=0;
    for(int i=0;i<books.bookDB.size();i++){
        fout<<books.bookDB[i].title<<",";
        fout<<books.bookDB[i].author<<",";
        fout<<books.bookDB[i].ISBN<<",";
        fout<<books.bookDB[i].publication<<",";
        fout<<books.bookDB[i].Avaibility<<",";
        fout<<books.bookDB[i].issue_by<<",";
        fout<<books.bookDB[i].issue_dt<<"\n";
    }

    fout.close();
    cout<<"--------book issued-----------";
    return 1;
}

void prof::calculate_fine(vector<book>books_issued,int dt){ //calculating fine for any book for professor
    system("clear");
    int i,date,x,fine; this->fine_amount=0;

    for(i=0;i<books_issued.size();i++){
        cout<<"\nBOOK ISBN: "<<books_issued[i].ISBN<<endl;
        date= books_issued[i].show_duedate(users.search(this->id));
        if(dt>date){
            int yr=dt/10000,year=date/10000;
            int mon=(dt%10000)/100,month=(date%10000)/100;
            dt=dt%100;date=date%100;

            while(mon!=month || yr!=year){
                if(mon-1==1||mon-1==3||mon-1==5||mon-1==7||mon-1==8||mon-1==10){
                    dt+=31;
                    mon--;
                }
                else if(mon-1==4||mon-1==6||mon-1==9||mon-1==11){
                    dt+=30;
                    mon--;
                }
                else if(mon-1==2){
                    if(yr%400==0){
                        dt+=29;
                        mon--;
                    }
                    else if(yr%100==0){
                        dt+=28;
                        mon--;
                    }
                    else if(yr%4==0){
                        dt+=29;
                        mon--;
                    }
                    else{
                        dt+=28;
                        mon--;
                    }
                } 
                else if(mon-1==0){
                    dt+=31;
                    mon=12;
                    yr--;
                }
            }
            x=dt-date;
            this->fine_amount+=x*5;
            cout<<"\nfine is: "<<x*5<<endl;
        }
        else{
            cout<<"\nno dues\n";
        }
    }
    cout<<"\n Total fine (in Rupees): "<<this->fine_amount;
}
void prof::clear_fine_amount(int isbn){//clearing fine for a book
    system("clear");
    if(isbn==-1){
        cout<<"\nno book present";
        return;
    }
    string s;vector<book>bk;
    if(books.bookDB[isbn].issue_by.compare(this->id)==0){
        cout<<"\ntoday's date in yyyymmdd: ";
            cin>>s;
            int dt = stoi(s);
            int duedate=books.bookDB[isbn].show_duedate(users.search(this->id));
        if(duedate>dt){
            cout<<"\nNo dues for this book."<<endl;
            return;
        }
        bk.push_back(books.bookDB[isbn]);
        calculate_fine(bk,dt);
        books.bookDB[isbn].issue_dt=s;
        cout<<"\nfine cleared for this book with this date";
    }
    else{
        cout<<"\nBook with this ISBN is not present or not issued by you.";
    }
}

void student::calculate_fine(vector<book>books_issued,int dt){//calculating fine for any book for student
    system("clear");
    int i,date,x,fine; this->fine_amount=0;

    for(i=0;i<books_issued.size();i++){
        cout<<"\nBOOK ISBN: "<<books_issued[i].ISBN<<endl;
        date= books_issued[i].show_duedate(users.search(this->id));
        if(dt>date){
            int yr=dt/10000,year=date/10000;
            int mon=(dt%10000)/100,month=(date%10000)/100;
            dt=dt%100;date=date%100;

            while(mon!=month || yr!=year){
                if(mon-1==1||mon-1==3||mon-1==5||mon-1==7||mon-1==8||mon-1==10){
                    dt+=31;
                    mon--;
                }
                else if(mon-1==4||mon-1==6||mon-1==9||mon-1==11){
                    dt+=30;
                    mon--;
                }
                else if(mon-1==2){
                    if(yr%400==0){
                        dt+=29;
                        mon--;
                    }
                    else if(yr%100==0){
                        dt+=28;
                        mon--;
                    }
                    else if(yr%4==0){
                        dt+=29;
                        mon--;
                    }
                    else{
                        dt+=28;
                        mon--;
                    }
                } 
                else if(mon-1==0){
                    dt+=31;
                    mon=12;
                    yr--;
                }
            }
            x=dt-date;
            this->fine_amount+=x*2;
            cout<<"\nfine is: "<<x*2<<endl;
        }
        else{
            cout<<"\nno dues\n";
        }
    }
    cout<<"\n Total fine (in Rupees): "<<this->fine_amount;
}
void student::clear_fine_amount(int isbn){//clearing fine for a book
    system("clear");
    if(isbn==-1){
        cout<<"\nno book present";
        return;
    }
    string s;vector<book>bk;
    if(books.bookDB[isbn].issue_by.compare(this->id)==0){
        cout<<"\ntoday's date in yyyymmdd: ";
            cin>>s;
            int dt = stoi(s);
            int duedate=books.bookDB[isbn].show_duedate(users.search(this->id));
        if(duedate>dt){
            cout<<"\nNo dues for this book."<<endl;
            return;
        }
        bk.push_back(books.bookDB[isbn]);
        calculate_fine(bk,dt);
        books.bookDB[isbn].issue_dt=s;
        cout<<"\nfine cleared for this book with this date";
    }
    else{
        cout<<"\nBook with this ISBN is not present or not issued by you.";
    }
}

void prof::prof_login(int in){
    system("clear");
    cout<<"Welcome ";
    //updating the variables of the class with user details
    this->id=users.userDB[in].id;
    this->name=users.userDB[in].name;
    this->pass=users.userDB[in].pass;
    this->role=users.userDB[in].role;
    cout<<this->name;

    //updating the vector of issued books
    for(int i=0;i<books.bookDB.size();i++){
       if(books.bookDB[i].issue_by.compare(users.userDB[in].id)==0)this->books_issued.push_back(books.bookDB[i]);
    }

    int input;
    while(1){
        cout<<"\nSelect an option -\n"; //providing user the list of function they can perform
        cout<<"1. See all books\n2. list of the books issued by you\n3. check availability of any book\n4. calculate fine for any issued book\n5. clear fine amount\n6. Issue a book\n7. Return a book\n8. Reset your password\n9. Logout\n";
        cin>> input;
        if(input==1){ // to get list of books in library
            system("clear");
            books.bookList(0);
        }
        else if(input==2){ // the list of books issued by the user
            system("clear");
            cout<<"********************** List of books issued by you*****************************\n";
            cout<<"\nTotal number of books issued: "<<books_issued.size()<<"\n";
            if(books_issued.size()!=0){
                for(int i=0;i<this->books_issued.size();i++){
                    cout<<"\nTitle: "<<books_issued[i].title<<endl;
                    cout<<"Author: "<<books_issued[i].author<<endl;
                    cout<<"ISBN: "<<books_issued[i].ISBN<<endl;
                    cout<<"Publication: "<<books_issued[i].publication<<endl;
                    books_issued[i].show_duedate(in);
                    cout<<"\n";
                }
            }
            else{
                cout<<"no books issued till now";
            }
            
        }
        else if(input==3){//checking availability of any book
            system("clear");
            int i; string j;

            cout<<"Search by ISBN: ";
            cin>>j;
            i=books.search(j);

            
            if(i!=-1 && books.bookDB[i].Avaibility.compare("yes")==0){
                cout<<"\nYes, the books with given ISBN is available.\n\n The details of the same can be found below-\n";
                cout<<"\nTitle: "<<books.bookDB[i].title<<endl;
                cout<<"Author: "<<books.bookDB[i].author<<endl;
                cout<<"ISBN: "<<books.bookDB[i].ISBN<<endl;
                cout<<"Publication: "<<books.bookDB[i].publication<<endl;
            }
            else{
                cout<<"Sorry, the book with this ISBN is not available.\n";
            }
        }
        else if(input==4){//calculating fine for every book he/she has issued
            system("clear");
            cout<<"\ntoday's date in yyyymmdd: "; int dt;
            cin>>dt;
            this->calculate_fine(this->books_issued,dt);
        }
        else if(input==5){ // to clear the fine amount of any book issued by him/her and reissuing it
            system("clear");
            
            cout<<"isbn of book for which you want to clear the fine amount: ";
            string s; cin>>s;
            this->clear_fine_amount(books.search(s));
        }
        else if(input==6){//to issue a book
            system("clear");
            cout<<"Type ISBN of book you want to issue: ";
            string isbn;
            cin>>isbn;
            int k = books.bookDB[books.search(isbn)].Book_request(this->id);
            if(k) this->books_issued.push_back(books.bookDB[books.search(isbn)]);
        }
        else if(input==7){
            system("clear");
            //Return a book

            cout<<"ISBN of books you have\n"; //getting the list books' ISBN issued by the user
            for(int i=0;i<this->books_issued.size();i++){
                cout<<this->books_issued[i].ISBN;
                if(i!=this->books_issued.size()-1)cout<<", ";
                else cout<<"\n";
            }

            cout<<"\nreturn a book with isbn: ";
            string s; cin>>s; 
            int dt; cout<<"\ntoday's date in yyyymmdd: "; cin>>dt;
            vector<book>bk;

            int i = books.search(s);
            if(i!=-1 && books.bookDB[i].issue_by.compare(this->id)==0){

                bk.push_back(books.bookDB[i]);
                calculate_fine(bk,dt);

                if(this->fine_amount==0){//returning only when there is no dues for the book

                    books.bookDB[i].Avaibility="yes";
                    books.bookDB[i].issue_by="na";
                    books.bookDB[i].issue_dt="na";

                    this->books_issued.clear();
                    for(int i=0;i<books.bookDB.size();i++){//updating the issued books vector
                        if(books.bookDB[i].issue_by.compare(users.userDB[in].id)==0)this->books_issued.push_back(books.bookDB[i]);
                    }

                    fstream fout;//updating the book database
            
                    fout.open("books.csv", ios::out);
                    
                    int f=0;
                    for(int i=0;i<books.bookDB.size();i++){
                        fout<<books.bookDB[i].title<<",";
                        fout<<books.bookDB[i].author<<",";
                        fout<<books.bookDB[i].ISBN<<",";
                        fout<<books.bookDB[i].publication<<",";
                        fout<<books.bookDB[i].Avaibility<<",";
                        fout<<books.bookDB[i].issue_by<<",";
                        fout<<books.bookDB[i].issue_dt<<"\n";
                    }
                    fout.close(); 
                    
                    cout<<"\n----------Returned----------";
                }
                else{
                    cout<<"\nclear fine amount first";
                }

            }
            else{
                cout<<"The book with this ISBN is not issued by you.";
            }

            
        }
        else if(input==8){ // to reset the password
            system("clear");
            cout<<"Enter your old password: ";
            string oldPass,newPass1,newPass2; cin>>oldPass;
            if(this->pass.compare(oldPass)==0){
                cout<<"\nEnter your new password: "; cin>>newPass1;
                cout<<"\nRenter your new password: "; cin>>newPass2;
                if(newPass1.compare(newPass2)==0){
                    this->pass=newPass1;
                    users.userDB[in].pass=this->pass;

                    fstream fout;
    
                    fout.open("users_db.csv", ios::out); //updating the user database with same new password
                     
                    for(int i=0;i<users.userDB.size();i++){
                        fout<<users.userDB[i].id<<",";
                        fout<<users.userDB[i].pass<<",";
                        fout<<users.userDB[i].name<<",";
                        fout<<users.userDB[i].role<<"\n";
                    }
                    fout.close(); 
                    
                    cout<<"---------- Updated----------";
                }
                else{
                    cout<<"passwords didn't match";
                }
            }
            else{
                cout<<"Wrong password entered";
            }

        }
        else if(input==9){
            system("clear");
            break;
        }  

        cout << "\nPress any char to Continue: ";
        char c;
        cin>>c;
        system("clear");
    }
    return;
}
void student::student_login(int in){
    system("clear");
    cout<<"Welcome ";
    //updating the variables of the class with user details
    this->id=users.userDB[in].id;
    this->name=users.userDB[in].name;
    this->pass=users.userDB[in].pass;
    this->role=users.userDB[in].role;
    cout<<this->name;

    for(int i=0;i<books.bookDB.size();i++){//updating the vector of issued books
       if(books.bookDB[i].issue_by.compare(users.userDB[in].id)==0)this->books_issued.push_back(books.bookDB[i]);
    }

    int input;
    while(1){
        cout<<"\nSelect an option -\n";//providing user the list of function they can perform
        cout<<"1. See all books\n2. list of the books issued by you\n3. check availability of any book\n4. calculate fine for any issued book\n5. clear fine amount\n6. Issue a book\n7. Return a book\n8. Reset your password\n9. Logout\n";
        cin>> input;
        if(input==1){//to get list of books in library
            system("clear");
            books.bookList(0);
        }
        else if(input==2){// the list of books issued by the user
            system("clear");
            cout<<"********************** List of books issued by you*****************************\n";
            cout<<"\nTotal number of books issued: "<<books_issued.size()<<"\n";
            if(books_issued.size()!=0){
                for(int i=0;i<this->books_issued.size();i++){
                    cout<<"\nTitle: "<<books_issued[i].title<<endl;
                    cout<<"Author: "<<books_issued[i].author<<endl;
                    cout<<"ISBN: "<<books_issued[i].ISBN<<endl;
                    cout<<"Publication: "<<books_issued[i].publication<<endl;
                    books_issued[i].show_duedate(in);
                    cout<<"\n";
                }
            }
            else{
                cout<<"no books issued till now";
            }
            
        }
        else if(input==3){//checking availability of any book
            system("clear");
            int i; string j;

            cout<<"Search by ISBN: ";
            cin>>j;
            i=books.search(j);

            
            if(i!=-1 && books.bookDB[i].Avaibility.compare("yes")==0){
                cout<<"\nYes, the books with given ISBN is available.\n\n The details of the same can be found below-\n";
                cout<<"\nTitle: "<<books.bookDB[i].title<<endl;
                cout<<"Author: "<<books.bookDB[i].author<<endl;
                cout<<"ISBN: "<<books.bookDB[i].ISBN<<endl;
                cout<<"Publication: "<<books.bookDB[i].publication<<endl;
            }
            else{
                cout<<"Sorry, the book with this ISBN is not available.\n";
            }
        }
        else if(input==4){//calculating fine for every book he/she has issued
            system("clear");
            cout<<"\ntoday's date in yyyymmdd: "; int dt;
            cin>>dt;
            this->calculate_fine(this->books_issued,dt);
        }
        else if(input==5){// to clear the fine amount of any book issued by him/her and reissuing it
            system("clear");
            cout<<"isbn of book for which you want to clear the fine amount: ";
            string s; cin>>s;
            this->clear_fine_amount(books.search(s));
        }
        else if(input==6){//to issue a book
            system("clear");
            if(this->books_issued.size()==5){//student has already issued 5 books thus can't issue more
                cout<<"You can't issue more books.";
            }
            else{
                cout<<"Type ISBN of book you want to issue: ";
                string isbn;
                cin>>isbn;
                int k = books.bookDB[books.search(isbn)].Book_request(this->id);
                if(k) this->books_issued.push_back(books.bookDB[books.search(isbn)]);//updating the issued book vector of student
            }
        }
        else if(input==7){
            system("clear");
            //Return a book

            cout<<"ISBN of books you have\n";//getting the list books' ISBN issued by the user
            for(int i=0;i<this->books_issued.size();i++){
                cout<<this->books_issued[i].ISBN;
                if(i!=this->books_issued.size()-1)cout<<", ";
                else cout<<"\n";
            }

            cout<<"\nreturn a book with isbn: ";
            string s; cin>>s; 
            int dt; cout<<"\ntoday's date in yyyymmdd: "; cin>>dt;
            vector<book>bk;

            int i = books.search(s);
            if(i!=-1 && books.bookDB[i].issue_by.compare(this->id)==0){

                bk.push_back(books.bookDB[i]);
                calculate_fine(bk,dt);
                if(this->fine_amount==0){//returning only when there is no dues for the book

                    books.bookDB[i].Avaibility="yes";
                    books.bookDB[i].issue_by="na";
                    books.bookDB[i].issue_dt="na";

                    this->books_issued.clear();
                    for(int i=0;i<books.bookDB.size();i++){//updating the issued books vector
                        if(books.bookDB[i].issue_by.compare(users.userDB[in].id)==0)this->books_issued.push_back(books.bookDB[i]);
                    }

                    fstream fout;//updating the book database
            
                    fout.open("books.csv", ios::out);
                    
                    int f=0;
                    for(int i=0;i<books.bookDB.size();i++){
                        fout<<books.bookDB[i].title<<",";
                        fout<<books.bookDB[i].author<<",";
                        fout<<books.bookDB[i].ISBN<<",";
                        fout<<books.bookDB[i].publication<<",";
                        fout<<books.bookDB[i].Avaibility<<",";
                        fout<<books.bookDB[i].issue_by<<",";
                        fout<<books.bookDB[i].issue_dt<<"\n";
                    }
                    fout.close(); 
                    
                    cout<<"\n----------Returned----------";
                }
                else{
                    cout<<"\nclear fine amount first";
                }

            }
            else{
                cout<<"The book with this ISBN is not issued by you.";
            }

            
        }
        else if(input==8){ // to reset the password
            system("clear");
            cout<<"Enter your old password: ";
            string oldPass,newPass1,newPass2; cin>>oldPass;
            if(this->pass.compare(oldPass)==0){
                cout<<"\nEnter your new password: "; cin>>newPass1;
                cout<<"\nRenter your new password: "; cin>>newPass2;
                if(newPass1.compare(newPass2)==0){
                    this->pass=newPass1;
                    users.userDB[in].pass=this->pass;

                    fstream fout;
    
                    fout.open("users_db.csv", ios::out);
                    
                    for(int i=0;i<users.userDB.size();i++){
                        fout<<users.userDB[i].id<<",";
                        fout<<users.userDB[i].pass<<",";
                        fout<<users.userDB[i].name<<",";
                        fout<<users.userDB[i].role<<"\n";
                    }
                    fout.close(); 
                    
                    cout<<"---------- Updated----------";
                }
                else{
                    cout<<"passwords didn't match";
                }
            }
            else{
                cout<<"Wrong password entered";
            }

        }
        else if(input==9){
            system("clear");
            break;
        }

        cout << "\nPress any char to Continue: ";
        char c;
        cin>>c;
        system("clear");
    }
    return;
}
void librarian::librarian_login(int in){
    cout<<"Welcome ";
    //updating the class variables
    this->id=users.userDB[in].id;
    this->name=users.userDB[in].name;
    this->pass=users.userDB[in].pass;
    this->role=users.userDB[in].role;
    cout<<this->name;

    int input;
    while(1){

        cout<<"\nSelect an option -\n";
        cout<<"1. See all books\n2. list of users\n3. modify book database\n4. modify user database\n5. get issued book list by any user\n6. Details of any book\n7. Reset your Password\n8. Logout\n";
        cin>> input;
        
        if(input==1){ //getting book list along with issued details
            system("clear");
            books.bookList(1);
        }
        else if(input==2){//getting user list
            cout<<"********************** Users List *****************************\n";
            cout<<"No of users: "<<users.userDB.size()<<endl;
            int i;
            for(i=0;i<users.userDB.size();i++){
                cout<<"\nName: "<<users.userDB[i].name<<endl;
                cout<<"id: "<<users.userDB[i].id<<"; Role: "<<users.userDB[i].role<<endl;
            }
        }
        else if(input==3){//the options to make changes in book database
            system("clear");
            cout<<"type of operation want to perform-\n1. Add a book\n2. Update a Book\n3. Delete a Book\n";
            int i;
            cin>>i;
            if(i==1){
                system("clear");
                books.Add();
            }
            else if(i==2){
                system("clear");
                books.Update();
            }
            else if(i==3){
                system("clear");
                books.Delete();
            }
        }
        else if(input==4){//the options to make changes in user database
            system("clear");
            cout<<"type of operation want to perform-\n1. Add a user\n2. Update a user\n3. Delete a user\n";
            int i;
            cin>>i;
            if(i==1){
                system("clear");
                users.Add();
            }
            else if(i==2){
                system("clear");
                users.Update();
            }
            else if(i==3){
                system("clear");
                users.Delete();
            }
        }
        else if(input==5){ // the details of issued any specific users
            system("clear");
            string j;
            cout<<"id of user whose list of issued books you want to view: ";
            cin>>j;
            int in=users.search(j);

            cout<<"**********************Issued Books List*****************************\n";
            
            int i,k,t=0;

            for(int i=0;i<books.bookDB.size();i++){
                if(books.bookDB[i].Avaibility.compare("no")==0){
                    if(books.bookDB[i].issue_by.compare(j)==0){
                        t++;
                        cout<<"\nTitle: "<<books.bookDB[i].title<<endl;
                        cout<<"Author: "<<books.bookDB[i].author<<endl;
                        cout<<"ISBN: "<<books.bookDB[i].ISBN<<endl;
                        cout<<"Publication: "<<books.bookDB[i].publication<<endl;
                        books.bookDB[i].show_duedate(in);
                        cout<<"\n";
                    }
                } 
            }
            if(t==0) cout<<"No books issued";
        }
        else if(input==6){ //getting any one book detail
            system("clear");
            string j;
            cout<<"isbn of book whose details you want to view: ";
            cin>>j;

            cout<<"**********************Book Details*****************************\n";
            
            int i,k;

            i=books.search(j);

            if(i==-1) cout<<"No such book in record";
            else{
                cout<<"\nTitle: "<<books.bookDB[i].title<<endl;
                cout<<"Author: "<<books.bookDB[i].author<<endl;
                cout<<"ISBN: "<<books.bookDB[i].ISBN<<endl;
                cout<<"Publication: "<<books.bookDB[i].publication<<endl;
                cout<<"Availability: "<<books.bookDB[i].Avaibility<<endl;
                if(books.bookDB[i].Avaibility.compare("no")==0){
                    k=users.search(books.bookDB[i].issue_by);
                    cout << "Issued by user with id: "<<users.userDB[k].id<<" name: "<<users.userDB[k].name<<endl;
                    books.bookDB[i].show_duedate(k);
                    cout<<"\n";
                }
            }
        }
        else if(input==7){ //reseting the password
            system("clear");
            cout<<"Enter your old password: ";
            string oldPass,newPass1,newPass2;
            cin>>oldPass;
            if(this->pass.compare(oldPass)==0){
                cout<<"\nEnter your new password: "; cin>>newPass1;
                cout<<"\nRenter your new password: "; cin>>newPass2;
                if(newPass1.compare(newPass2)==0){
                    this->pass=newPass1;
                    users.userDB[in].pass=this->pass;

                    fstream fout;
    
                    fout.open("users_db.csv", ios::out);
                    
                    for(int i=0;i<users.userDB.size();i++){
                        fout<<users.userDB[i].id<<",";
                        fout<<users.userDB[i].pass<<",";
                        fout<<users.userDB[i].name<<",";
                        fout<<users.userDB[i].role<<"\n";
                    }
                    fout.close(); 
                    
                    cout<<"---------- Updated----------";
                }
                else{
                    cout<<"passwords didn't match";
                }
            }
            else{
                cout<<"Wrong password entered";
            }
        }
        else if(input==8){
            break;
        }
        cout << "\nPress any char to Continue: ";
        char c;
        cin>>c;
        system("clear");
    }
}

int main(){
    user person;
    getDatabase();
    person.start();
    return 0;
}