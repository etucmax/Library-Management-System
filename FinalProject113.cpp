#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
HANDLE COLOR = GetStdHandle(STD_OUTPUT_HANDLE); // Used To Set Color Of The Text In The Console

/*** Function Prototypes ***/
void headerPage();
void loadingPage();
void errorPage();
void exitPage();
void clearInputStream();
void mainPage();
void logInPage();
void MainMenu();
void addBook();
void deleteBook();
void searchBook();
void updateBook();
void displayAllBooks();
void issueABook();
void returnABook();
void displayBorrowers();
void changePassword();
void addBookAgainOPT();
void deleteBookAgainOPT();
void displayBookBorrowerOPT();

struct BookNode {
	
	string bookName;
	string author;
	string pubDate;
	int bookID;
	bool bookAvailability;
	BookNode *next;
};

struct BorrowerNode {
	string name, studentID, course, year, section, issuedBookName;
	int issuedBookID;
	BorrowerNode *next;
	
	BorrowerNode(string borrowerName, string borrowerID, string borrowerCourse, string borrowerYear, string borrowerSection, string bookName, int bookID) {
		name = borrowerName;
        studentID = borrowerID;
        course = borrowerCourse;
        year = borrowerYear;
        section = borrowerSection;
        issuedBookName = bookName;
        issuedBookID = bookID;
        next = NULL;
	}
};

struct  PasswordNode {
	
	char password[100];
	PasswordNode *next;
};

struct getBookDetails {
	
	int resBookID;
	string resBookName;
	string resAuthor;
	string resPubDate;
};

getBookDetails bookDetails() { // Get the Book Details from The User
	
	getBookDetails details;
	
	while(true) {
        cout << "\t\t\t        Enter Book ID: ";
        if (!(cin >> details.resBookID) || cin.peek() != '\n' || details.resBookID < 0) {
        	SetConsoleTextAttribute(COLOR, 4);
            cout << "\n\t\t\t                  Invalid Book ID! Please Enter A Valid Integer.";
            SetConsoleTextAttribute(COLOR, 15);
            clearInputStream();
            Sleep(500);
            continue;
    	}
    	clearInputStream();
		cout << "\t\t\t        Enter Book Name: ";
		getline(cin, details.resBookName);
		cout << "\t\t\t        Enter Author: ";
		getline(cin, details.resAuthor);
		cout << "\t\t\t        Enter Publication Date: ";
		getline(cin, details.resPubDate);
		break;
	}
	
	return details;
}

/*** Linked List Class***/
class LibraryLinkedList {
	
	BookNode *bookHead = NULL;
	BorrowerNode *borrowerHead = NULL;
	
public:
	
	/*** BOOKS FUNCTION ***/
	void insertBookAtHead(string bookName, string author, string pubDate, int bookID) {
		 // Insert A Book Into The Head Of The Linked List
		BookNode *bookNode = new BookNode;
		bookNode->bookName = bookName;
		bookNode->author = author;
		bookNode->pubDate = pubDate;
		bookNode->bookID = bookID;
		bookNode->bookAvailability = true;
		bookNode->next = bookHead;
		
		bookHead = bookNode;
		SetConsoleTextAttribute(COLOR, 2);
		cout << "\n\t\t\t                             BOOK ADDED SUCESSFULLY" << endl;
		SetConsoleTextAttribute(COLOR, 15);
	}
	
	void insertBookAtMiddle(string bookName, string author, string pubDate, int bookID) {
		 // Insert A Book Into The Middle Of The Linked List
		 
		int count = 0;
		int mid;
		
		BookNode *bookNode = new BookNode;
		bookNode->bookName = bookName;
		bookNode->author = author;
		bookNode->pubDate = pubDate;
		bookNode->bookID = bookID;
		bookNode->bookAvailability = true;
		bookNode->next = NULL;
		
		if(bookHead == NULL) {
			bookHead = bookNode;
			SetConsoleTextAttribute(COLOR, 2);
			cout << "\n\t\t\t                             BOOK ADDED SUCESSFULLY" << endl;
			SetConsoleTextAttribute(COLOR, 15);
			return;
		}
		else {
			BookNode *temp = bookHead;
			while(temp->next != NULL) {
				temp = temp->next;
				count++;
			}
			
			mid = count/2;
			temp = bookHead;
			
			for(int i=0; i<mid; i++){
				temp = temp->next;
			}
			
			bookNode->next = temp->next;
			temp->next = bookNode;
		}
		SetConsoleTextAttribute(COLOR, 2);
		cout << "\n\t\t\t                             BOOK ADDED SUCESSFULLY" << endl;
		SetConsoleTextAttribute(COLOR, 15);
	}
	
	void insertBookAtEnd(string bookName, string author, string pubDate, int bookID) {
		 // Insert A Book Into The End Of The Linked List
		BookNode *bookNode = new BookNode;
		bookNode->bookName = bookName;
		bookNode->author = author;
		bookNode->pubDate = pubDate;
		bookNode->bookID = bookID;
		bookNode->bookAvailability = true;
		bookNode->next = NULL;
		
		if(bookHead == NULL) {
			bookHead = bookNode;
			SetConsoleTextAttribute(COLOR, 2);
			cout << "\n\t\t\t                             BOOK ADDED SUCESSFULLY" << endl;
			SetConsoleTextAttribute(COLOR, 15);
			return;
		}
		else {
			BookNode *temp = bookHead;
			while(temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = bookNode;
		}
		
		SetConsoleTextAttribute(COLOR, 2);
		cout << "\n\t\t\t                             BOOK ADDED SUCESSFULLY" << endl;
		SetConsoleTextAttribute(COLOR, 15);
	}
	
	void insertBookAtEndFromFile(string bookName, string author, string pubDate, int bookID, bool bookAvailability) {
		 // Inserting A Book From The File txt Into The End Of The Linked List
		BookNode *bookNode = new BookNode;
		bookNode->bookName = bookName;
		bookNode->author = author;
		bookNode->pubDate = pubDate;
		bookNode->bookID = bookID;
		bookNode->bookAvailability = bookAvailability;
		bookNode->next = NULL;
		
		if(bookHead == NULL) {
			bookHead = bookNode;
			return;
		}
		else {
			BookNode *temp = bookHead;
			while(temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = bookNode;
		}
	}
	
	void deleteBookHead() {
		// Deleting The Head Of the LinkedList
		char opt;
		
		if(bookHead == NULL) {
			SetConsoleTextAttribute(COLOR, 4);
        	cout << "\n\t\t\t                    NO BOOKS IS FOUND. THE LIBRARY IS EMPTY" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
        	return;
		}
		
		if(!bookHead->bookAvailability) {
    			SetConsoleTextAttribute(COLOR, 12);
        		cout << "\n\t\t\t           YOU CANNOT DELETE THE BOOK BECAUSE IT IS CURRENTLY BORROWED" << endl;
        		SetConsoleTextAttribute(COLOR, 15);
        		return;
		}
		
		cout << "\n\t\t\t        Here's The Book In The Head:" << endl;
		displayBookDetails(bookHead);
		cout << "\n\t\t\t        Do You Want To Delete The Book? (Y/N): ";
		cin >> opt;
		
		if(opt == 'y' || opt == 'Y') {
			
			BookNode *temp = bookHead;
			bookHead = bookHead->next;
			delete temp;
			SetConsoleTextAttribute(COLOR, 2);
			cout << "\n\t\t\t                            BOOK DELETED SUCESSFULLY" << endl;	
			SetConsoleTextAttribute(COLOR, 15);
			return;
		}
		else {
			
			SetConsoleTextAttribute(COLOR, 4);
			cout << "\n\t\t\t                               DELETION CANCELLED" << endl;
			SetConsoleTextAttribute(COLOR, 15);
			return;
		}
	}
	
	void deleteMiddleBook() {
		// Deleting The Middle Of the LinkedList
		int mid, count = 0;
		char opt;
		
		if(bookHead == NULL) {
			SetConsoleTextAttribute(COLOR, 4);
        	cout << "\n\t\t\t                    NO BOOKS IS FOUND. THE LIBRARY IS EMPTY" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
        	return;
		}
		
		BookNode *temp = bookHead;
		while(temp != NULL) {
			temp = temp->next;
			count++;
		}
		
		mid = count/2;
		temp = bookHead;
		BookNode *prev = NULL;
		
		for(int i=0; i<mid; i++) {
			prev = temp;
			temp = temp->next;
		}
		if(!temp->bookAvailability){
    			SetConsoleTextAttribute(COLOR, 12);
        		cout << "\n\t\t\t           YOU CANNOT DELETE THE BOOK BECAUSE IT IS CURRENTLY BORROWED" << endl;
        		SetConsoleTextAttribute(COLOR, 15);
        		return;
		}
		cout << "\n\t\t\t        Here's The Book In The Middle:" << endl;
		displayBookDetails(temp);
		cout << "\n\t\t\t        Do You Want To Delete The Book? (Y/N): ";
		cin >> opt;
		
		if(opt == 'y' || opt == 'Y') {
			prev->next = temp->next;
			delete temp;
			SetConsoleTextAttribute(COLOR, 2);
			cout << "\n\t\t\t                            BOOK DELETED SUCESSFULLY" << endl;	
			SetConsoleTextAttribute(COLOR, 15);
			return;
		}
		else {
			SetConsoleTextAttribute(COLOR, 4);
			cout << "\n\t\t\t                               DELETION CANCELLED" << endl;
			SetConsoleTextAttribute(COLOR, 15);
			return;
		}
	}
	
	void deleteEndBook() {
		// Deleting The End Of the LinkedList
		char opt;
		
		if(bookHead == NULL) {
			SetConsoleTextAttribute(COLOR, 4);
        	cout << "\n\t\t\t                    NO BOOKS IS FOUND. THE LIBRARY IS EMPTY" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
        	return;
		}
		
		BookNode *temp = bookHead;
		BookNode *prev = NULL;
		
		while(temp->next != NULL) {
			prev = temp;
			temp = temp->next;
		}
		if(!temp->bookAvailability){
    			SetConsoleTextAttribute(COLOR, 12);
        		cout << "\n\t\t\t           YOU CANNOT DELETE THE BOOK BECAUSE IT IS CURRENTLY BORROWED" << endl;
        		SetConsoleTextAttribute(COLOR, 15);
        		return;
		}
		
		cout << "\n\t\t\t        Here's The Book In The End:" << endl;
		displayBookDetails(temp);
		cout << "\n\t\t\t        Do You Want To Delete The Book? (Y/N): ";
		cin >> opt;
		
		if(opt == 'y' || opt == 'Y') {
			prev->next = NULL;
			delete temp;
			SetConsoleTextAttribute(COLOR, 2);
			cout << "\n\t\t\t                            BOOK DELETED SUCESSFULLY" << endl;	
			SetConsoleTextAttribute(COLOR, 15);
			return;
		}
		else {
			SetConsoleTextAttribute(COLOR, 4);
			cout << "\n\t\t\t                               DELETION CANCELLED" << endl;
			SetConsoleTextAttribute(COLOR, 15);
			return;
		}
	}
	
	void deleteBySearchingABook(string bookName) {
		// Deleting The Book By searchig A Specific Book
		BookNode *temp = bookHead;
    	BookNode *prev = NULL;
    	char opt;
		
		while(temp != NULL && temp->bookName != bookName) {
			
        	prev = temp;
       	 	temp = temp->next;
   		}
	
    	if(temp == NULL) {
    		
        	SetConsoleTextAttribute(COLOR, 4);
        	cout << "\n\t\t\t                                 BOOK NOT FOUND" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
        	return;
    	}
    	if(!temp->bookAvailability){
    			SetConsoleTextAttribute(COLOR, 12);
        		cout << "\n\t\t\t           YOU CANNOT DELETE THE BOOK BECAUSE IT IS CURRENTLY BORROWED" << endl;
        		SetConsoleTextAttribute(COLOR, 15);
        		return;
		}

    	cout << "\n\t\t\t        Here's The Book You Searched:" << endl;
    	displayBookDetails(temp);
    	cout << "\n\t\t\t        Do You Want To Delete The Book? (Y/N): ";
    	cin >> opt;

    	if(opt == 'y' || opt == 'Y') {
        	if (prev == NULL) {
          	  bookHead = temp->next;
        	} else {
         	   prev->next = temp->next;
        	}

        	delete temp;
        	SetConsoleTextAttribute(COLOR, 2);
        	cout << "\n\t\t\t                            BOOK DELETED SUCCESSFULLY" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
        return;
    	} 
		else{
        	SetConsoleTextAttribute(COLOR, 4);
        	cout << "\n\t\t\t                               DELETION CANCELLED" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
        	return;
    	}
	}

	void searchABook(string bookName) {
		// Searching A Book Function
    	BookNode *temp = bookHead;
    	bool found = false;

    	while(temp != NULL) {
        	if(temp->bookName == bookName) {
        		
            	system("cls");
            	headerPage();
            	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>>> SEARCH A BOOK <<<<<<<<<<<<<<<<<<<<<<<<" << endl;
            	SetConsoleTextAttribute(COLOR, 10);
            	cout << "\n\t\t\t                                 BOOK IS FOUND!" << endl;
            	SetConsoleTextAttribute(COLOR, 15);
            	displayBookDetails(temp);
            	found = true;
            	break;
        	}
        	temp = temp->next;
    	}

    	if(!found) {
    		
        	system("cls");
        	headerPage();
        	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>>> SEARCH A BOOK <<<<<<<<<<<<<<<<<<<<<<<<" << endl;
        	SetConsoleTextAttribute(COLOR, 12);
        	cout << "\n\t\t\t                               BOOK IS NOT FOUND!" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
    	}
	}

	void updateABook(string bookName) {
		// A Function To Update The Value Of The LinkedLIst
		BookNode* temp = bookHead;
		getBookDetails newDetails;
		
    	while(temp != NULL) {
    		if(!temp->bookAvailability){
    			SetConsoleTextAttribute(COLOR, 12);
        		cout << "\n\t\t\t            YOU CANNOT UPDATE THE BOOK BECAUSE IT IS CURRENTLY BORROWED" << endl;
        		SetConsoleTextAttribute(COLOR, 15);
        		return;
			}
        	else if(temp->bookName == bookName) {
        		
        		cout << "\n\n\t\t\t        Heres The Book You Want To Update:" << endl;
            	displayBookDetails(temp);
            	cout << "\n\t\t\t        Enter The New Details Of The Book:" << endl;
            	newDetails = bookDetails();	
            	// Update book details
            	temp->bookName = newDetails.resBookName;
            	temp->author = newDetails.resAuthor;
            	temp->pubDate = newDetails.resPubDate;
            	temp->bookID = newDetails.resBookID;

            	SetConsoleTextAttribute(COLOR, 2);
				cout << "\n\t\t\t                        BOOK DETAILS UPDATED SUCCESSFULLY!" << endl;
				SetConsoleTextAttribute(COLOR, 15);
            	return;
        	}
        	temp = temp->next;
    	}
    	SetConsoleTextAttribute(COLOR, 12);
        cout << "\n\t\t\t                               BOOK IS NOT FOUND!" << endl;
        SetConsoleTextAttribute(COLOR, 15);
	}
	
	void displayAllBooks() {
		// Funtion To Display All The Content Of The LinkedList
		BookNode *temp = bookHead;

    	if(temp == NULL) {
    		
    		SetConsoleTextAttribute(COLOR, 12);
        	cout << "\n\t\t\t                    NO BOOKS IS FOUND. THE LIBRARY IS EMPTY" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
        	return;
    	}
		else {
        	while (temp != NULL) {
            	displayBookDetails(temp);
            	temp = temp->next;
        	}
    	}
    cout << endl;
	}
	
	/*** Function For The Borrower ***/
	
	void insertBorrowerAtEnd(string borrowerName, string borrowerID, string course, string year, string section, string bookName, int bookID) {
		// Insert The Borrower Details To The Borrower Node
        BorrowerNode* borrowerNode = new BorrowerNode(borrowerName, borrowerID, course, year, section, bookName, bookID);
        borrowerNode->next = NULL;

        if (borrowerHead == NULL) {
            borrowerHead = borrowerNode;
        } else {
            BorrowerNode* temp = borrowerHead;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = borrowerNode;
        }
    }

	void issueABooks(const string& bookName) {
		// A Function To Issue A Book To The Borrower
        BookNode* temp = bookHead;
        string borrowerName, studentID, course, year, section;
        int bookID;

        while (temp != NULL) {
            if (temp->bookName == bookName && temp->bookAvailability) {
            	
                displayBookDetails(temp);
                bookID =temp->bookID;

                cout << "\t\t\t        Enter Borrower Name: ";
                getline(cin, borrowerName);
                cout << "\t\t\t        Enter Student ID: ";
                getline(cin, studentID);
                cout << "\t\t\t        Enter Borrower Course: ";
                getline(cin, course);
                cout << "\t\t\t        Enter Borrower Year: ";
                getline(cin, year);
                cout << "\t\t\t        Enter Borrower Section: ";
                getline(cin, section);

                insertBorrowerAtEnd(borrowerName, studentID, course, year, section, bookName, bookID);
                temp->bookAvailability = false;

                SetConsoleTextAttribute(COLOR, 2);
                cout << "\n\t\t\t                            BOOK ISSUED SUCCESSFULLY!" << endl;
                SetConsoleTextAttribute(COLOR, 15);
                return;
            }
            temp = temp->next;
        }
        SetConsoleTextAttribute(COLOR, 12);
        cout << "\n\t\t\t                   BOOK NOT FOUND OR UNAVAILABLE FOR BORROWING" << endl;
        SetConsoleTextAttribute(COLOR, 15);
    }
	
	void returnABooks(const string &bookName, const string &borrowerName) {
		// Function To Return The Book
    	BorrowerNode *tempBorrower = borrowerHead;
    	BookNode *tempBook = bookHead;

    	while (tempBook != NULL) {
        	if (tempBook->bookName == bookName && !(tempBook->bookAvailability)) {
            	displayBookDetails(tempBook);

            	// Check if borrower name matches
            	while (tempBorrower != NULL) {
                	if (tempBorrower->name == borrowerName && tempBorrower->issuedBookName == bookName) {
                		
                    	deleteBorrower(borrowerName);
                    	tempBook->bookAvailability = true;

                    	SetConsoleTextAttribute(COLOR, 2);
                    	cout << "\n\t\t\t                           BOOK SUCCESSFULLY RETURNED!" << endl;
                    	SetConsoleTextAttribute(COLOR, 15);
                    	return;
                	}
                	tempBorrower = tempBorrower->next;
            	}

            	SetConsoleTextAttribute(COLOR, 12);
            	cout << "\n\t\t\t                       WRONG BORROWER NAME OR BOOK NOT BORROWED!" << endl;
            	SetConsoleTextAttribute(COLOR, 15);
            	return;
        	}
        	tempBook = tempBook->next;
    	}
    	SetConsoleTextAttribute(COLOR, 12);
    	cout << "\n\t\t\t                       BOOK NOT FOUND OR ALREADY AVAILABLE" << endl;
    	SetConsoleTextAttribute(COLOR, 15);
	}
	
	void deleteBorrower(const string& borrowerName) {
		// Function To Delte The Borrower After Returning The Book
    	BorrowerNode* temp = borrowerHead;
		BorrowerNode* prev = NULL;

    	while (temp != NULL && temp->name != borrowerName) {
        	prev = temp;
        	temp = temp->next;
    	}
    	if (temp != NULL) {
        	if (prev == NULL) {
            	borrowerHead = borrowerHead->next;
        	} else {
            	prev->next = temp->next;
        	}
        	delete temp;
    	} else {
        	SetConsoleTextAttribute(COLOR, 12);
        	cout << "\n\t\t\t                               BORROWER NOT FOUND!" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
    	}
	}
	
	void displayBorrowers() {
		// Fucntion To Display The Borrowers And Their Books That They Borrowed
    	BorrowerNode* borrower = borrowerHead;
    	
    	if(borrower == NULL) {
    		
    		SetConsoleTextAttribute(COLOR, 12);
        	cout << "\n\t\t\t                              NO LIST OF BORROWERS!" << endl;
        	SetConsoleTextAttribute(COLOR, 15);
        	return;
		}

    	while (borrower != NULL) {
    		
        	cout << "\t\t\t        --------------------------------------------" << endl;
        	cout << "\t\t\t        BORROWER NAME         -> " << borrower->name << endl;
        	cout << "\t\t\t        BORROWED BOOK NAME    -> " << borrower->issuedBookName << endl;
        	cout << "\t\t\t        BORROWED BOOK ID      -> " << borrower->issuedBookID << endl;
        	cout << "\t\t\t        --------------------------------------------" << endl;

        	borrower = borrower->next;
    	}
	}
	
	/*** Functions To Save And Load The Borrowers and Book Data From/To The File ***/
	
	void saveBooksToFile(const string &fileName) {
		// Save The Books Data Into The File After you Exit The Program
		ofstream outFile(fileName.c_str());
		
		if(!outFile) {
			return;
		}
		
		BookNode *temp = bookHead;
		while(temp != NULL) {
			outFile << temp->bookID << "§"
					<< temp->bookName << "§"
					<< temp->author << "§"
					<< temp->pubDate << "§"
					<< temp->bookAvailability << endl;
					
			temp = temp->next;
		}
		
		outFile.close();
	}
	
	void saveBorrowersToFile(const string &fileName) {
		
		ofstream outFile(fileName.c_str());
		
		if(!outFile) {
			return;
		}
		
		BorrowerNode *temp = borrowerHead;
		while(temp != NULL) {
			outFile << temp->name << "§" // This § Symbol Is Used A Delimeter
					<< temp->studentID << "§"
					<< temp->course << "§"
					<< temp->year << "§"
					<< temp->section << "§"
					<< temp->issuedBookName << "§"
					<< temp->issuedBookID << endl;
					
			temp = temp->next;
		}
		outFile.close();
	}
	
	void loadBooksFromFile(const string &fileName) {
		
		ifstream inFile(fileName.c_str());
		string line;
		
		if(!inFile) {
			return;
		}
		
		while(bookHead != NULL) { // Clear existing data in the linkedlist
			
			BookNode *temp = bookHead;
			bookHead = bookHead->next;
			delete temp;
		}
		
		while(getline(inFile, line)) {
			
			stringstream get(line); // Use stringstream to parse each line
			string bookIDStr;  // Temporary string to read book ID
        	getline(get, bookIDStr, '§');

        	int bookID = stoi(bookIDStr); // Convert book ID from string to integer
			
			string bookName, author, pubDate;
			bool bookAvailability;
			
			getline(get, bookName, '§');
			getline(get, author, '§');
			getline(get, pubDate, '§');
			get >> bookAvailability;
			insertBookAtEndFromFile(bookName, author, pubDate, bookID, bookAvailability);	
		}
		
		inFile.close();
	}
	
	void loadBorrowersFromFile(const string &fileName) {
		
		ifstream inFile(fileName.c_str());
		string line;
		
		if(!inFile) {
			return;
		}
		
		while(borrowerHead != NULL) { // Clear exixting data
			
			BorrowerNode *temp = borrowerHead;
			borrowerHead = borrowerHead->next;
			delete temp;
		}
		
		while(getline(inFile, line)) {
			
			stringstream get(line); // Use stringstream to parse each line
			string name, studentID, course, year, section, issuedBookName; 
			int issuedBookID;
		
			getline(get, name, '§');
			getline(get, studentID, '§');
			getline(get, course, '§');
			getline(get, year, '§');
			getline(get, section, '§');
			getline(get, issuedBookName, '§');
			get >> issuedBookID;
			
			insertBorrowerAtEnd(name, studentID, course, year, section, issuedBookName, issuedBookID);
		}
		
		inFile.close();
	}
	
private:
 
    void displayBookDetails(BookNode* bookNode) {
    	
        cout << "\t\t\t        --------------------------------------------" << endl;
        cout << "\t\t\t        BOOK ID               -> " << bookNode->bookID << endl;
        cout << "\t\t\t        BOOK NAME             -> " << bookNode->bookName << endl;
        cout << "\t\t\t        BOOK AUTHOR           -> " << bookNode->author << endl;
        cout << "\t\t\t        BOOK PUBLICATION DATE -> " << bookNode->pubDate << endl;
        cout << "\t\t\t        BOOK AVAILABILITY     -> " << (bookNode->bookAvailability ? "Available" : "Not Available") << endl;
        cout << "\t\t\t        --------------------------------------------" << endl;
    }	
};

/*** Stack Class For the Password***/
class PasswordStack {
	
public:
	
	PasswordNode *PassTop = NULL;
	
	void pushPassword(const char *pass) {
		
		PasswordNode *passnode = new PasswordNode;
		strcpy(passnode->password, pass);
		passnode->next = PassTop;
		PassTop = passnode;
	}
	
	void pop() {
		
		if(PassTop == NULL) {
			return;
		}
		
		PasswordNode *temp = PassTop;
		PassTop = PassTop->next;
		delete temp;
	}
	
	string displayPass() {
		
		if(PassTop == NULL) {
			return "";
		}
		
		return PassTop->password;
	}
	
	bool comparePassword(const string& enteredPassword) const {
		
    	if (PassTop == NULL) {
        	return false;
    	}
    	// Compares The Entered Pass The PassTop->Password using the strcmp if the two strings equal strcmp return 0 which is true
    	return strcmp(enteredPassword.c_str(), PassTop->password) == 0; 
	}
    
    void updatePassword(const char* newPassword) {
    	
        if(PassTop != NULL) {
        	
            strcpy(PassTop->password, newPassword); // copies the string pointed to by newpassword to PassTop->password
            SetConsoleTextAttribute(COLOR, 2);
            cout << "\n\t\t\t                     PASSWORD HAS BEEN SUCCESSFULLY CHANGED" << endl;
            SetConsoleTextAttribute(COLOR, 15);
            return;
        }
    }
	
	void savePassToFile(const string &fileName) {
		
		ofstream outFile(fileName.c_str());
		
		if(!outFile) {
			return;
		}
		
		PasswordNode *temp = PassTop;
		
		while(temp != NULL) {
			outFile << temp->password << endl;
			
			temp = temp->next;
		}
		
		outFile.close();	
	}
	
	void loadPassFromFile(const string &fileName) {
		
		ifstream inFile(fileName.c_str());
		string line;
		
		if(!inFile) {
			return;
		}
		
		while(PassTop != NULL) {
			
			PasswordNode *temp = PassTop;
			PassTop = PassTop->next;
			delete temp;
		}
		
		while(getline(inFile, line)) {
			
			pushPassword(line.c_str());
		}
		
		inFile.close();
	}
};

/*** Global Declaration	***/
LibraryLinkedList libraryLL; // LibraryLinkedList
PasswordStack passSTACK; // PasswordStack

/*-- MAIN FUNCTION --*/
int main() {
	
	libraryLL.loadBooksFromFile("BooksData.txt");
	libraryLL.loadBorrowersFromFile("BorrowersData.txt");
	passSTACK.loadPassFromFile("PasswordData.txt");
	
	system("cls");
	mainPage();

	return 0;
}

void MainMenu() {
	
	int menuOPT;
	
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>>>> MAIN MENU <<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "\n\n\t\t\t                               >>SELECT AN OPTION<<" << endl;
	cout << "\t\t\t        [1] -> ADD A BOOK" << endl;
	cout << "\t\t\t        [2] -> DELETE A BOOK" << endl;
	cout << "\t\t\t        [3] -> SEARCH A BOOK" << endl;
	cout << "\t\t\t        [4] -> UPDATE A BOOK" << endl;
	cout << "\t\t\t        [5] -> DISPLAY ALL BOOKS" << endl;
	cout << "\t\t\t        [6] -> ISSUE A BOOK" << endl;
	cout << "\t\t\t        [7] -> RETURN A BOOK" << endl;
	cout << "\t\t\t        [8] -> DISPLAY LIST OF BORROWERS" << endl;
	cout << "\t\t\t        [9] -> CHANGE PASSWORD" << endl;
	cout << "\t\t\t        [10] -> EXIT" << endl;
	cout << "\n\t\t\t        ENTER OPTION: ";
	
	while(!(cin >> menuOPT) || cin.peek() == ' ' || cin.peek() == '.' || menuOPT < 1 || menuOPT > 10 || getchar() != 10) {
		
		system("cls");
		errorPage();
		clearInputStream();
		Sleep(500);
		MainMenu();
	}
	
	switch(menuOPT) {
		case 1:
			
			system("cls");
			addBook();
			MainMenu();
			break;
		case 2:
			
			system("cls");
			deleteBook();
			break;
		case 3:
			
			system("cls");
			searchBook();
			break;
		case 4:
			
			system("cls");
			updateBook();
			break;
		case 5:
			
			displayAllBooks();
			system("cls");
			
			break;
		case 6:
			
			system("cls");
			issueABook();
			break;
		case 7:
			
			system("cls");
			returnABook();
			break;
		case 8:
			
			system("cls");
			displayBorrowers();
			break;
		case 9:
			
			system("cls");
			changePassword();
			break;
		case 10:
			
			system("cls");
			exitPage();
			break;
	}
}

void addBook() {
	
    int addBookOPT;
    getBookDetails detailsHead;
    getBookDetails detailsMid;
    getBookDetails detailsEnd;
    
    headerPage();
    cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>>>>> ADD BOOK <<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "\n\n\t\t\t        Where Do You Want To Insert The Book?" << endl;
    cout << "\t\t\t        [1] -> IN THE HEAD" << endl;
    cout << "\t\t\t        [2] -> IN THE MIDDLE" << endl;
    cout << "\t\t\t        [3] -> IN THE END" << endl;
    cout << "\t\t\t        [4] -> GO BACK TO MAIN MENU" << endl;
    cout << "\t\t\t        [5] -> EXIT" << endl;
    cout << "\n\t\t\t        ENTER OPTION: ";

    while (!(cin >> addBookOPT) || cin.peek() == ' ' || cin.peek() == '.' || addBookOPT < 1 || addBookOPT > 5 || getchar() != 10) {
    	
        system("cls");
        errorPage(); 
        clearInputStream();
        Sleep(500);
        addBook();
    }

    switch (addBookOPT) {
        case 1:
        	
            system("cls");
            headerPage();
            cout << "\t\t\t        >>>>>>>>>>>>>>>>>>> ADDING A BOOK AT THE HEAD <<<<<<<<<<<<<<<<<<<\n\n" << endl;
            detailsHead = bookDetails(); // CAll THE FUNCTION BOOKDETAILS
            libraryLL.insertBookAtHead(detailsHead.resBookName, detailsHead.resAuthor, detailsHead.resPubDate, detailsHead.resBookID);
            addBookAgainOPT();
            break;
        case 2:
        	
            system("cls");
            headerPage();
            cout << "\t\t\t        >>>>>>>>>>>>>>>>>> ADDING A BOOK AT THE MIDDLE <<<<<<<<<<<<<<<<<<\n\n" << endl;
            detailsMid = bookDetails();  // CAll THE FUNCTION BOOKDETAILS
            libraryLL.insertBookAtMiddle(detailsMid.resBookName, detailsMid.resAuthor, detailsMid.resPubDate, detailsMid.resBookID);
            addBookAgainOPT();
            break;
        case 3:
        	
            system("cls");
            headerPage();
            cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>> ADDING A BOOK AT THE END <<<<<<<<<<<<<<<<<<<\n\n" << endl;
            detailsEnd = bookDetails();  // CAll THE FUNCTION BOOKDETAILS
            libraryLL.insertBookAtEnd(detailsEnd.resBookName, detailsEnd.resAuthor, detailsEnd.resPubDate, detailsEnd.resBookID);
            addBookAgainOPT();
            break;
        case 4:
        	
            system("cls");
            MainMenu();
            break;
        case 5:
        	
            system("cls");
            exitPage();
            break;
    }
}

void deleteBook() {
	
	string bookName;
	int deleteBookOPT;
	
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>>> DELETE A BOOK <<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "\n\n\t\t\t        Where Do You Want To Delete A Book?" << endl;
	cout << "\t\t\t        [1] -> IN THE HEAD" << endl;
	cout << "\t\t\t        [2] -> IN THE MIDDLE" << endl;
	cout << "\t\t\t        [3] -> IN THE END" << endl;
	cout << "\t\t\t        [4] -> SEARCH A BOOK TO DELETE" << endl;
	cout << "\t\t\t        [5] -> GO BACK TO MAIN MENU" << endl;
	cout << "\t\t\t        [6] -> EXIT" << endl;
	cout << "\n\t\t\t        ENTER OPTION: ";
	
	while(!(cin >> deleteBookOPT) || cin.peek() == ' ' || cin.peek() == '.' || deleteBookOPT < 1 || deleteBookOPT > 6 || getchar() != 10) {
		
		system("cls");
		errorPage();
		clearInputStream();
		Sleep(500);
		deleteBook();
	}
	
	switch(deleteBookOPT) {
		case 1:
			
			system("cls");
			headerPage();
			cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>> DELETE THE HEAD BOOK <<<<<<<<<<<<<<<<<<<<<" << endl;
			libraryLL.deleteBookHead();
			deleteBookAgainOPT();
			break;
		case 2:
			
			system("cls");
			headerPage();
			cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>> DELETE THE MIDDLE BOOK <<<<<<<<<<<<<<<<<<<<" << endl;
			libraryLL.deleteMiddleBook();
			deleteBookAgainOPT();
			break;
		case 3:
			
			system("cls");
			headerPage();
			cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>> DELETE THE END BOOK <<<<<<<<<<<<<<<<<<<<<<" << endl;
			libraryLL.deleteEndBook();
			deleteBookAgainOPT();
			break;
		case 4:
			
			system("cls");
			headerPage();
			cout << "\t\t\t        >>>>>>>>>>>>>>>> SEARCH A BOOK YOU WANT TO DELETE <<<<<<<<<<<<<<<" << endl;
			cout << "\n\n\t\t\t        ENTER THE BOOK NAME YOU WANT TO DELETE: ";
			getline(cin, bookName);
			
			libraryLL.deleteBySearchingABook(bookName);
			deleteBookAgainOPT();
			break;
		case 5:
			
			system("cls");
			MainMenu();
			break;
		case 6:
			
			system("cls");
			exitPage();
			break;
	}
}

void searchBook() {
	
	string bookName;
	int OPT;
	
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>>> SEARCH A BOOK <<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "\n\n\t\t\t        ENTER THE BOOK NAME YOU WANT TO SEARCH: ";
	getline(cin, bookName);
	
	libraryLL.searchABook(bookName);
	
	cout << "\n\n\t\t\t        >>SELECT AN OPTION<<" << endl;
	cout << "\t\t\t        [1] -> SEARCH A BOOK AGAIN" << endl;
	cout << "\t\t\t        [2] -> BACK TO MAIN MENU" << endl;
	cout << "\t\t\t        [3] -> EXIT" << endl;
	cout << "\n\t\t\t        ENTER OPTION: ";
	cin >> OPT;
	
	while(cin.fail() || cin.peek() == ' ' || cin.peek() == '.' || OPT < 1 || OPT > 3 || getchar() != 10) {
		
		errorPage();
		clearInputStream();
		Sleep(500);
		cout << "\n\t\t\t        ENTER OPTION: ";
		cin >> OPT;
	}
	
	switch(OPT) {
		case 1:
			
			system("cls");
			searchBook();
			clearInputStream();
			break;
			
		case 2:
			system("cls");
			MainMenu();
			break;
			
		case 3:
			system("cls");
			exitPage();
			break;
	}
}

void updateBook() {
	
	string bookName;
	int OPT;
	
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>>> UPDATE A BOOK <<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "\n\n\t\t\t        ENTER THE BOOK NAME YOU WANT TO UDATE: ";
	getline(cin, bookName);

	libraryLL.updateABook(bookName);
	
	cout << "\n\n\t\t\t        >>SELECT AN OPTION<<" << endl;
	cout << "\t\t\t        [1] -> UPDATE A BOOK AGAIN" << endl;
	cout << "\t\t\t        [2] -> BACK TO MAIN MENU" << endl;
	cout << "\t\t\t        [3] -> EXIT" << endl;
	cout << "\n\t\t\t        ENTER OPTION: ";
	cin >> OPT;
	
	while(cin.fail() || cin.peek() == ' ' || cin.peek() == '.' || OPT < 1 || OPT > 3 || getchar() != 10) {
		
		errorPage();
		clearInputStream();
		Sleep(500);
		cout << "\n\t\t\t        ENTER OPTION: ";
		cin >> OPT;
	}
	
	switch(OPT) {
		case 1:
			
			system("cls");
			updateBook();
			clearInputStream();
			break;
			
		case 2:
			system("cls");
			MainMenu();
			break;
			
		case 3:
			system("cls");
			exitPage();
			break;
	}
}

void displayAllBooks() {
	
	int OPT;
	
	system("cls");
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>> DISPLAY ALL BOOKS <<<<<<<<<<<<<<<<<<<<<<\n\n" << endl;
	libraryLL.displayAllBooks();
	displayBookBorrowerOPT();
}

void issueABook() {
	
	string bookName;
	int OPT;
	
	system("cls");
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>>> ISSUE A BOOK <<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "\n\n\t\t\t        Enter The Book Name You want To Issue: ";
	getline(cin, bookName);
	
	libraryLL.issueABooks(bookName);
	
	cout << "\n\n\t\t\t        >>SELECT AN OPTION<<" << endl;
	cout << "\t\t\t        [1] -> ISSUE A BOOK AGAIN" << endl;
	cout << "\t\t\t        [2] -> BACK TO MAIN MENU" << endl;
	cout << "\t\t\t        [3] -> EXIT" << endl;
	cout << "\n\t\t\t        ENTER OPTION: ";
	cin >> OPT;
	
	while(cin.fail() || cin.peek() == ' ' || cin.peek() == '.' || OPT < 1 || OPT > 3 || getchar() != 10) {
		
		errorPage();
		clearInputStream();
		Sleep(500);
		cout << "\n\t\t\t        ENTER OPTION: ";
		cin >> OPT;
	}
	
	switch(OPT) {
		case 1:
			system("cls");
			issueABook(); 
			clearInputStream();
			break;
		case 2:
			system("cls");
			MainMenu();
			break;
		case 3:
			system("cls");
			exitPage();
			break;
	}
}

void returnABook() {
	
	string bookName, borrowerName;
	int OPT;
	
	system("cls");
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>> RETURN A BOOK <<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "\n\n\t\t\t        Enter The Book Name You want To Return: ";
	getline(cin, bookName);
	cout << "\n\n\t\t\t        Enter The Name of The Borrower: ";
	getline(cin, borrowerName);
	
	libraryLL.returnABooks(bookName, borrowerName);
	
	cout << "\n\n\t\t\t        >>SELECT AN OPTION<<" << endl;
	cout << "\t\t\t        [1] -> RETURN A BOOK AGAIN" << endl;
	cout << "\t\t\t        [2] -> BACK TO MAIN MENU" << endl;
	cout << "\t\t\t        [3] -> EXIT" << endl;
	cout << "\n\t\t\t        ENTER OPTION: ";
	cin >> OPT;
	
	while(cin.fail() || cin.peek() == ' ' || cin.peek() == '.' || OPT < 1 || OPT > 3 || getchar() != 10) {
		
		errorPage();
		clearInputStream();
		Sleep(500);
		cout << "\n\t\t\t        ENTER OPTION: ";
		cin >> OPT;
	}
	
	switch(OPT) {
		case 1:
			system("cls");
			returnABook();
			break;
		case 2:
			system("cls");
			MainMenu();
			break;
		case 3:
			system("cls");
			exitPage();
			break;
	}
}

void displayBorrowers() {
	
	int OPT;
	
	system("cls");
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>> DISPLAY BORROWERS <<<<<<<<<<<<<<<<<<<<<<<" << endl;
	libraryLL.displayBorrowers();
	displayBookBorrowerOPT();
}

/*** OPTIONS ***/
void addBookAgainOPT() {
	
	int OPT;
	
	cout << "\n\t\t\t        >>SELECT AN OPTION<<" << endl;
	cout << "\t\t\t        [1] -> ADD BOOK AGAIN" << endl;
	cout << "\t\t\t        [2] -> BACK TO MAIN MENU" << endl;
	cout << "\t\t\t        [3] -> EXIT" << endl;
	while(true) {
		cout << "\n\t\t\t        ENTER OPTION: ";
		if(!(cin >> OPT) || cin.peek() != '\n' || OPT < 1 || OPT > 3) {
			errorPage();
			clearInputStream();
			Sleep(500);
			continue;
		}
		break;		
	}
	
	switch(OPT) {
		case 1:
			system("cls");
			addBook();
			clearInputStream();
			break;
			
		case 2:
			system("cls");
			MainMenu();
			break;
			
		case 3:
			system("cls");
			exitPage();
			break;
	}
	
}

void deleteBookAgainOPT() {
	
	int OPT;
	
	cout << "\n\t\t\t        >>SELECT AN OPTION<<" << endl;
	cout << "\t\t\t        [1] -> DELETE A BOOK AGAIN" << endl;
	cout << "\t\t\t        [2] -> BACK TO MAIN MENU" << endl;
	cout << "\t\t\t        [3] -> EXIT" << endl;
	
	while(true) {
		cout << "\n\t\t\t        ENTER OPTION: ";
		if(!(cin >> OPT) || cin.peek() != '\n' || OPT < 1 || OPT > 3) {
			errorPage();
			clearInputStream();
			Sleep(500);
			continue;
		}
		break;	
	}
	
	switch(OPT) {
		case 1:
			system("cls");
			deleteBook();
			clearInputStream();
			break;
		case 2:
			system("cls");
			MainMenu();
			break;
		case 3:
			system("cls");
			exitPage();
			break;
	}
}

void displayBookBorrowerOPT() {
	
	int OPT;
	
	cout << "\n\t\t\t        >>SELECT AN OPTION<<" << endl;
	cout << "\t\t\t        [1] -> BACK TO MAIN MENU" << endl;
	cout << "\t\t\t        [2] -> EXIT" << endl;
	
	while(true) {
		
		cout << "\n\t\t\t        ENTER OPTION: ";
		if(!(cin >> OPT) || cin.peek() != '\n' || OPT < 1 || OPT > 2) {
			errorPage();
			clearInputStream();
			Sleep(500);
			continue;
		}
		break;	
	}
	
	switch(OPT) {
		case 1:
			system("cls");
			MainMenu();
			break;
		case 2:
			system("cls");
			exitPage();
			break;
	}
}

void changePassword() {
	
	char newpass[100];
	
	system("cls");
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>> CHANGE PASSWORD <<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	
	cout << "\n\n\n\t\t\t        YOUR OLD PASSWORD IS -> " << passSTACK.displayPass() << endl;
	cout << "\n\t\t\t        ENTER YOUR NEW PASSWORD: ";
	cin >> newpass;
	
	passSTACK.updatePassword(newpass);
	displayBookBorrowerOPT();
}

void mainPage() {
	
	headerPage();
	cout << "\t\t\t                         Press Any Key To Continue...";
	getch();
	system("cls");
	logInPage();
}

void logInPage() {
	
	string inputPass;
	char ch;
	
	headerPage();
	cout << "\t\t\t        >>>>>>>>>>>>>>>>>>>>>>>>>> LOG IN PAGE <<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << "\n\n\t\t\t        Enter EXIT to Exit The Program." << endl;
	cout << "\n\t\t\t        ENTER PASSWORD: ";
	
	while(1) { // This Loop Will Execute Indefinitely Until The User Presses The Enter Key
		
		ch = _getch(); // Get The Character That The User Type
		if(ch == 13) { // Checks if The "ENTER KEY" is Pressed Because The Key Code Of "ENTER" is "13"
			break;
		}
		else if(ch == 8) { // Checks If The "BACKSPACE KEY" is Pressed
			if(!inputPass.empty()) {
				inputPass.pop_back();
				cout << "\b \b"; // Deletes The Last Character From The Console
			}
		}
		else {
			inputPass.push_back(ch);
			cout << '*'; // This Will Print An asterisk in A place of the actual password chracter
		}
	}
	
	// Check If the Entered Pass is Correct By Comparaing To The Correct Password That Is stored In The passStack
	if(passSTACK.comparePassword(inputPass)) { 
		loadingPage();
		return;
	}
	else if(inputPass == "EXIT" || inputPass == "exit") { // If the User Enter Exit It Will Exit the Program
		exitPage();
	} else { // This Will be Executed If The Password Is Incorrect
		system("cls");
		SetConsoleTextAttribute(COLOR, 4);
		cout << "\n\t\t\t                                INVALID PASSWORD" << endl;
		cout << "\t\t\t                                PLEASE TRY AGAIN" << endl;
		SetConsoleTextAttribute(COLOR, 15);
		logInPage();
		return;
	}
	
	cout << endl;
}

void clearInputStream() { // This Used To Clear The Input Stream
	
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void headerPage() {
	
	SetConsoleTextAttribute(COLOR, 1);
	cout << "\n\n\t\t\t        *****************************************************************" << endl;
	cout << "\t\t\t        *****************************************************************" << endl;
	cout << "\t\t\t        ***                                                           ***" << endl;
	cout << "\t\t\t        ***      -----------------------------------------------      ***" << endl;
	cout << "\t\t\t        ***            WELCOME TO LIBRARY MANGEMENT SYSTEM            ***" << endl;
	cout << "\t\t\t        ***      -----------------------------------------------      ***" << endl;
	cout << "\t\t\t        ***                                                           ***" << endl;
	cout << "\t\t\t        *****************************************************************" << endl;
	cout << "\t\t\t        *****************************************************************" << endl;
	SetConsoleTextAttribute(COLOR, 15);
}

void loadingPage() {
	
	system("cls");
	for(int i=1; i<=100; ++i) {
		Sleep(2);
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\t\t\t                               LOADING " << i << "%";
		if(i == 100) {
			Sleep(1000);
		}
	}
	
	system("cls");
	MainMenu();
}

void errorPage() {
	
	SetConsoleTextAttribute(COLOR, 4);
	cout << "\n\t\t\t                                 INVALID OPTION!" << endl;
	cout << "\t\t\t                                PLEASE TRY AGAIN" << endl;
	SetConsoleTextAttribute(COLOR, 15);
}

void exitPage() {
	
	libraryLL.saveBooksToFile("BooksData.txt");
	libraryLL.saveBorrowersToFile("BorrowersData.txt");
	passSTACK.savePassToFile("PasswordData.txt");
	
	system("cls");
	cout << "\n\n\n\n\n\t\t\t        *****************************************************************" << endl;
	cout << "\t\t\t        *****************************************************************" << endl;
	cout << "\t\t\t        ***                                                           ***" << endl;
	cout << "\t\t\t        ***      -----------------------------------------------      ***" << endl;
	cout << "\t\t\t        ***              THANK YOU FOR USING THIS SYSTEM              ***" << endl;
	cout << "\t\t\t        ***                  DEVELOPED BY BOKANEERS                   ***" << endl;
	cout << "\t\t\t        ***      -----------------------------------------------      ***" << endl;
	cout << "\t\t\t        ***                                                           ***" << endl;
	cout << "\t\t\t        *****************************************************************" << endl;
	cout << "\t\t\t        *****************************************************************\n\n\n\n\n\n" << endl;
	exit(0);
	
	
	
	
}
