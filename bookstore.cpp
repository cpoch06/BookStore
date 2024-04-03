#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Book
{
private:
    string title;
    string author;
    string genre;
    double price;
    int quantity;

public:
    Book *next;
    Book(){}

    Book(const string &title, const string &author, const string &genre, double price, int quantity)
    {
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->price = price;
        this->quantity = quantity;
        this->next = nullptr;
    }
    
    string getTitle() const
    {
        return title;
    }

    string getAuthor() const
    {
        return author;
    }

    string getGenre() const
    {
        return genre;
    }

    double getPrice() const
    {
        return price;
    }

    int getQuantity() const
    {
        return quantity;
    }

    void setTitle(const string &title)
    {
        this->title = title;
    }

    void setAuthor(const string &author)
    {
        this->author = author;
    }

    void setGenre(const string &genre)
    {
        this->genre = genre;
    }

    void setPrice(double price)
    {
        this->price = price;
    }

    void setQuantity(int quantity)
    {
        this->quantity = quantity;
    }

    void print() const
    {   
        cout << left << setw(30) << title << setw(30) << author 
            << setw(30) << genre
            << setw(30) << quantity 
            << setw(0) << price << endl;
    }   

    void searchByTitle(const string &searchTitle) const
    {
        if (title == searchTitle)
        {
            print();
            cout << endl;
        }
    }

    void searchByAuthor(const string &searchAuthor) const
    {
        if (author == searchAuthor)
        {
            print();
            cout << endl;
        }
    }

    // void searchByGenre(const string &searchGenre) const
    // {
    //     if (genre == searchGenre)
    //     {
    //         print();
    //         cout << endl;
    //     }
    // }
};

class BookNode
{
public:
    Book *book;
    BookNode *left;
    BookNode *right;

    BookNode(Book *book)
    {
        this->book = book;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class TitleBST
{
private:
    BookNode *root;

public:
    TitleBST() : root(nullptr) {}

    ~TitleBST()
    {
        clearTree(root);
    }

    void insert(Book *book)
    {
        root = insertRecursive(root, book);
    }

    void searchByTitle(const string &searchTitle) const
    {
        searchByTitleRecursive(root, searchTitle);
    }

private:
    BookNode *insertRecursive(BookNode *node, Book *book)
    {
        if (node == nullptr)
        {
            return new BookNode(book);
        }

        if (book->getTitle() < node->book->getTitle())
        {
            node->left = insertRecursive(node->left, book);
        }
        else if (book->getTitle() > node->book->getTitle())
        {
            node->right = insertRecursive(node->right, book);
        }
        else
        {
            
        }

        return node;
    }

    bool searchByTitleRecursive(BookNode *node, const string &searchTitle) const
    {
        if (node != nullptr)
        {
            searchByTitleRecursive(node->left, searchTitle);

            if (searchTitle == node->book->getTitle())
            {   
                cout << "\n\t\t\t\t\t\t\tBooks Details: \n" << endl;
        
                cout << left  << setw(30) << "Title" 
                    << setw(30) << "Author"
                    << setw(30) << "Genre" 
                    << setw(30) << "Quantity" 
                    << setw(30) << "Price\n" << endl;

                node->book->print();
                cout << endl;
                return true;
            } 
            

            searchByTitleRecursive(node->right, searchTitle);
        }
        return false;
    }

    void clearTree(BookNode *node)
    {
        if (node != nullptr)
        {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }
};


class BookList
{
public:
    Book *head;
    TitleBST titleBST;

    BookList() : head(nullptr) {}

    ~BookList()
    {
        while (head != nullptr)
        {
            Book *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addBook(const string &title, const string &author, const string &genre, double price, int quantity)
    {
        Book *newBook = new Book(title, author, genre, price, quantity);
        newBook->next = head;
        head = newBook;

        titleBST.insert(newBook);
    }

    void displayBooks() const
    {
        Book* current = head;
        cout << "\t\t\t\t\t\t\tBooks Details: \n" << endl;

        cout << left  << setw(30) << "Title" 
            << setw(30) << "Author"
            << setw(30) << "Genre" 
            << setw(30) << "Quantity" 
            << setw(30) << "Price\n" << endl;

        while (current != nullptr)
        {
            current->print();
            current = current->next;
        }
    }
};

bool isValidCardNumber(const string &cardNumber)
{
    // Check if the card number has exactly 16 digits
    return (cardNumber.length() == 16 && all_of(cardNumber.begin(), cardNumber.end(), ::isdigit));
}

bool isValidCVV(const string &cvv)
{
    // Check if the CVV has exactly 3 digits
    return (cvv.length() == 3 && all_of(cvv.begin(), cvv.end(), ::isdigit));
}

void merge_title(vector<Book>& books, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Book> leftArr(books.begin() + left, books.begin() + left + n1);
    vector<Book> rightArr(books.begin() + mid + 1, books.begin() + mid + 1 + n2);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].getTitle() <= rightArr[j].getTitle()) {
            books[k++] = leftArr[i++];
        } else {
            books[k++] = rightArr[j++];
        }
    }

    while (i < n1) {
        books[k++] = leftArr[i++];
    }

    while (j < n2) {
        books[k++] = rightArr[j++];
    }
}

void mergeSort_title(vector<Book>& books, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort_title(books, left, mid);
        mergeSort_title(books, mid + 1, right);

        merge_title(books, left, mid, right);
    }
}

void sortBooksByTitle(vector<Book>& books) {
    int n = books.size();
    mergeSort_title(books, 0, n - 1);
}

void bubble_sort(vector<Book>& books) {
    int n = books.size();
    bool swapped;

    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            if (books[i].getPrice() > books[i + 1].getPrice()) {
                swap(books[i], books[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);

    cout << "\n\nBooks sorted!" << endl;
}

void merge(vector<Book>& books, vector<Book>& left, vector<Book>& right, int leftCount, int rightCount) {
    int i = 0, j = 0, k = 0;

    while (i < leftCount && j < rightCount) {
        if (left[i].getPrice() < right[j].getPrice()) {
            books[k++] = left[i++];
        } else {
            books[k++] = right[j++];
        }
    }

    while (i < leftCount) {
        books[k++] = left[i++];
    }

    while (j < rightCount) {
        books[k++] = right[j++];
    }

    for (int i = 0; i < books.size(); i++) {
        books[i].print();
    }
}

void merge_sort(vector<Book>& books) {
    int n = books.size();
    if (n < 2) {
        return;
    }

    int mid = n / 2;
    vector<Book> left(books.begin(), books.begin() + mid);
    vector<Book> right(books.begin() + mid, books.end());

    merge_sort(left);
    merge_sort(right);

    merge(books, left, right, left.size(), right.size());

   cout << "\n\nBooks sorted!" << endl;
}


void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<Book>& books, int low, int high) {
    double pivot = books[high].getPrice();
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (books[j].getPrice() < pivot) {
            i++;
            swap(books[i], books[j]);
        }
    }

    swap(books[i + 1], books[high]);
    return i + 1;
}

void quick_sort(vector<Book>& books, int low, int high) {
    if (low < high) {
        int pi = partition(books, low, high);

        quick_sort(books, low, pi - 1);
        quick_sort(books, pi + 1, high);
    }
}

void insertion_sort(vector<Book>& books) {
    int n = books.size();
    for (int i = 1; i < n; i++) {
        Book temp = books[i];
        int j = i - 1;
        while (j >= 0 && books[j].getPrice() > temp.getPrice()) {
            books[j + 1] = books[j];
            j = j - 1;
        }
        books[j + 1] = temp;
    }

    cout << "\n\nBooks sorted!" << endl;
}

void selection_sort(vector<Book>& books) {
    int n = books.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (books[j].getPrice() < books[minIndex].getPrice()) {
                minIndex = j;
            }
        }
        swap(books[i], books[minIndex]);
    }

    cout << "\n\nBooks sorted!" << endl;
}

void heapify(vector<Book>& books, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && books[left].getPrice() > books[largest].getPrice()) {
        largest = left;
    }

    if (right < n && books[right].getPrice() > books[largest].getPrice()) {
        largest = right;
    }

    if (largest != i) {
        swap(books[i], books[largest]);
        heapify(books, n, largest);
    }
}

void heap_sort(vector<Book>& books) {
    int n = books.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(books, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(books[0], books[i]);
        heapify(books, i, 0);
    }

   cout << "\n\nBooks sorted!" << endl;
}

int main()
{
    BookList bookList;
    ifstream inputFile("books.txt");

    if (inputFile.is_open())
    {
        string line;

        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string title, author, genre;
            double price;
            int quantity;

            getline(ss, title, ',');
            ss.seekg(1, ios::cur);
            getline(ss, author, ',');

            string temp;
            while (ss >> temp)
            {
                if (isdigit(temp[0]) || (temp[0] == '-' && isdigit(temp[1])))
                {
                    ss.seekg(-temp.length(), ios::cur);
                    break;
                }
                genre += (temp + " ");
            }

            genre.pop_back();
            ss >> price >> quantity;

            bookList.addBook(title, author, genre, price, quantity);

        }
    
        inputFile.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
        return 1;
    }

    cout << "\n\t\tWelcome to our Book Store!\n" << endl;

    int choice;
    double total = 0.0;
    Book *current = nullptr;
    int n = 0;
    vector<Book> vec_books;

    do
    {
        cout << "--------------------------Menu---------------------------\n"<< endl;
        cout << "1. Search Options" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Buy a Book" << endl;
        cout << "4. Sort Options" << endl;
        cout << "5. Confirm" << endl;
        cout << "6. Exit" << endl;
        cout << "\n---------------------------------------------------------" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        int searchChoice;
        string title;
        string author;
        string genre;
        bool found = false;
        int low, high, mid;

        switch (choice)
        {
        case 1:
            cout << "\nSearch by Title: " << endl;
            cout << "1. Serial Search" << endl;
            cout << "2. Binary Search" << endl;
            cout << "3. Binary Search Tree" << endl;
            cout << "Enter your choice: ";
            cin >> searchChoice;

            switch (searchChoice)
            {
                case 1:
                    cout << "\nEnter the title: ";
                    cin.ignore();
                    getline(cin, title);
                    found = false;

                    current = bookList.head;
                    while (current != nullptr)
                    {
                        if (current->getTitle() == title)
                        {
                            cout << "\n\t\t\t\t\t\t\tBooks Details: \n" << endl;
                            cout << left  << setw(30) << "Title" 
                                << setw(30) << "Author"
                                << setw(30) << "Genre" 
                                << setw(30) << "Quantity" 
                                << setw(30) << "Price\n" << endl;
                            current->print();
                            found = true;
                        }
                        current = current->next;
                    }

                    if (!found)
                    {
                        cout << "\nBook not found" << endl;
                    }
                    break;
                case 2:
                    cout << "\nEnter the title: ";
                    cin.ignore();
                    getline(cin, title);
                    found = false;

                    current = bookList.head;
                    while (current != nullptr)
                    {
                        vec_books.push_back(*current);
                        current = current->next;
                    }

                    sortBooksByTitle(vec_books);

                    n = vec_books.size();

                    low = 0;
                    high = n - 1;

                    while(low <= high) {
                        mid = (low + high) / 2;

                        if (vec_books[mid].getTitle() == title) {
                            // Search for more matching books to the left
                            for (int i = mid; i >= 0 && vec_books[i].getTitle() == title; --i) {
                                cout << "\n\t\t\t\t\t\t\tBooks Details: \n" << endl;
                                cout << left  << setw(30) << "Title" 
                                    << setw(30) << "Author"
                                    << setw(30) << "Genre" 
                                    << setw(30) << "Quantity" 
                                    << setw(30) << "Price" << endl << endl;
                                vec_books[i].print();
                                found = true;
                            }

                            // Search for more matching books to the right
                            for (int i = mid + 1; i < n && vec_books[i].getTitle() == title; ++i) {
                              cout << "\n\t\t\t\t\t\t\tBooks Details: \n" << endl;     
                                cout << left  << setw(30) << "Title" 
                                    << setw(30) << "Author"
                                    << setw(30) << "Genre" 
                                    << setw(30) << "Quantity" 
                                    << setw(30) << "Price" << endl;
                                vec_books[i].print();
                                found = true;
                            }
                            break;
                        } else if (vec_books[mid].getTitle() < title) {
                            low = mid + 1;
                        } else {
                            high = mid - 1;
                        }
                    }

                    break;
                case 3:
                    cout << "\nEnter the title: ";
                    cin.ignore();
                    getline(cin, title);
                    found = false;

                    bookList.titleBST.searchByTitle(title);
                    break;

                default:
                    cout << "Invalid choice" << endl;
                    break;
            }
            break;
        case 2: 
            bookList.displayBooks();
            break;
        case 3:
            cout << "\nEnter the title: ";
            cin.ignore();
            getline(cin, title);
            found = false;

            current = bookList.head;
            while (current != nullptr)
            {
                if (current->getTitle() == title)
                {
                    cout << "\nEnter the quantity: ";
                    int quantity;
                    cin >> quantity;

                    if (quantity <= current->getQuantity())
                    {
                        total += quantity * current->getPrice();
                        current->setQuantity(current->getQuantity() - quantity);
                        cout << "\nBook added to cart\n"
                             << endl;
                        cout << "Price: $" << total << endl;
                    }
                    else
                    {
                        cout << "Insufficient quantity\n"
                             << endl;
                    }
                    found = true;
                }
                current = current->next;
            }

            if (!found)
            {
                cout << "\nBook not found\n"
                     << endl;
            }

            break;

        case 4:
            cout << "\nSort by: " << endl;
            cout << "1. Bubble Sort" << endl;
            cout << "2. Merge Sort" << endl;
            cout << "3. Quick Sort" << endl;
            cout << "4. Insertion Sort" << endl;
            cout << "5. Selectin Sort" << endl;
            cout << "6. Heap Sort" << endl;

            cout << "\nEnter your choice: ";
            int sortChoice; 
            cin >> sortChoice;

            vec_books.clear();
            current = bookList.head;
            while (current != nullptr)
            {
                vec_books.push_back(*current);
                current = current->next;
            }

            n = vec_books.size();

            switch (sortChoice)
            {
            case 1:            
                bubble_sort(vec_books);
                break;
            case 2:                
                merge_sort(vec_books);
                break;
            case 3:
                quick_sort(vec_books, 0, vec_books.size() - 1);
                break;
            case 4:
                insertion_sort(vec_books);
                break;
            case 5:
                selection_sort(vec_books);
                break;
            case 6:
                heap_sort(vec_books);
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
            }

            cout << "\nBooks sorted by price: " << endl;
            cout << "\n\t\t\t\t\t\t\tBooks Details: \n" << endl;
        
                cout << left  << setw(30) << "Title" 
                    << setw(30) << "Author"
                    << setw(30) << "Genre" 
                    << setw(30) << "Quantity" 
                    << setw(30) << "Price\n" << endl;

            for (int i = 0; i < n; i++)
            {   
                vec_books[i].print();
            }
            break;

        case 5:
            if (total > 0)
            {
                cout << "\nTotal Price: $" << total << endl;
                cout << "\nConfirm purchase? (Y/N): ";
                char confirm;
                cin >> confirm;

                if (confirm == 'Y' || confirm == 'y')
                {
                    cout << "\nThank you for shopping with us!" << endl;
                }
                else if (confirm == 'N' || confirm == 'n')
                {
                    cout << "\nPurchase cancelled" << endl;
                }
                else
                {
                    cout << "\nInvalid choice" << endl;
                }
            }
            else
            {
                cout << "\nNo books in cart" << endl;
            }
            break;
        case 6:
            cout << "\nThank you for shopping with us!" << endl;
            return 0;

        }

    } while (choice != 5 && choice != 6);

    int paymentChoice;

    if (total > 0 && choice == 5)
    {
        cout << "\n\nTotal Price: $" << total << endl;
        cout << "\nHow would you like to pay?" << endl;
        cout << "1. Cash" << endl;
        cout << "2. Card" << endl;
        cout << "Enter your choice: ";
        cin >> paymentChoice;

        do
        {
            double amount;
            string cardNumber;
            string expiryDate;
            string cvv;

            switch (paymentChoice)
            {
            case 1:
                cout << "\nTotal Price: $" << total << endl;
                cout << "\nEnter the amount: ";
                cin >> amount;

                while (amount < total)
                {
                    cout << "\nInsufficient amount" << endl;
                    cout << "Enter the amount: ";
                    cin >> amount;
                }

                if (amount > total)
                {
                    cout << "\nChange: $" << amount - total << endl;
                    cout << "Thank you for shopping with us!" << endl;
                    break;
                }
                else if (amount == total)
                {
                    cout << "\nThank you for shopping with us!" << endl;
                    break;
                }
                break;
            case 2:
                cout << "\nEnter the card number: ";
                cin >> cardNumber;

                // Validate card number
                if (!isValidCardNumber(cardNumber))
                {
                    cout << "Invalid card number" << endl;
                    break;
                }

                cout << "Enter the CVV: ";
                cin >> cvv;

                // Validate CVV
                if (!isValidCVV(cvv))
                {
                    cout << "Invalid CVV" << endl;
                    break;
                }

                cout << "\nThank you for shopping with us!" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
            }

        } while (paymentChoice != 1 && paymentChoice != 2);
    }
    else
    {
        cout << "\nThank you for shopping with us!" << endl; // Sarcasm
    }

    // ofstream outputFile("books.txt");

    return 0;
}

