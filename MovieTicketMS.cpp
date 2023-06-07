#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <string.h>

using namespace std;
vector<string> movie_name(25);
vector<string> showtimeDate(25);
vector<string> showtime1(25);
vector<string> showtime2(25);
vector<string> showtime3(25);
vector<string> seat_(5);
const int WIDTH = 77, MAXMOVIES = 15;
int counter;
char name[50], icno[25], email[40], phone_number[25], acc_num[25], password[25], month[25], year[25];
int seat_price = 1000;

bool isTimeValid(const std::string &timeStr)
{
    std::istringstream timeStream(timeStr);
    int hour, minute;
    char delimiter;

    // Extract hour, minute, and delimiter from the time string
    timeStream >> hour >> delimiter >> minute;

    // Check if the extraction was successful and the delimiter is ':'
    if (!timeStream.fail() && delimiter == ':')
    {
        // Check the validity of the hour and minute values
        if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59)
        {
            return true;
        }
    }

    return false;
}

bool isDateValid(const string &dateStr)
{
    istringstream dateStream(dateStr);
    int day, month, year;
    char delimiter;

    // Extract day, month, year and delimiter from the date string
    dateStream >> day >> delimiter >> month >> delimiter >> year;

    // Check if the extraction was successful and the delimiter is '/'
    if (!dateStream.fail() && delimiter == '/')
    {
        // Check the validity of the day, month, and year values
        if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 0 && year <= 9999)
        {
            return true;
        }
    }

    return false;
}

class Movie
{
    string name, showtime_date, release_date, time1, time2, time3;

public:
    void addMovie()
    {
        ofstream out("Movies.txt", ios::app);

        cout << "Enter name of the movie: ";
        cin.ignore();
        getline(cin, name);
    r_date:
        cout << "Enter the released date (DD/MM/YYYY): ";
        cin.ignore();
        cin >> release_date;
        if (!isDateValid(release_date))
        {
            cout << "Invalid date format or value." << endl;
            goto r_date;
        }
    s_date:
        cout << "Enter the showtime date (DD/MM/YYYY): ";
        cin.ignore();
        cin >> showtime_date;
        if (!isDateValid(showtime_date))
        {
            cout << "Invalid date format or value." << endl;
            goto s_date;
        }
    t1:
        cout << "Enter time of first show: ";
        cin.ignore();
        cin >> time1;
        if (isTimeValid(time1))
        {
            cout << "Invalid time format or value." << endl;
            goto t1;
        }
    t2:
        cout << "Enter time of second show: ";
        cin.ignore();
        cin >> time2;
        if (isTimeValid(time1))
        {
            cout << "Invalid time format or value." << endl;
            goto t2;
        }
    t3:
        cout << "Enter time of third show: ";
        cin.ignore();
        cin >> time3;
        if (isTimeValid(time1))
        {
            cout << "Invalid time format or value." << endl;
            goto t3;
        }
        cout << "Adding movie. Please wait";
        Sleep(700);
        cout << ".";
        Sleep(700);
        cout << ".";
        Sleep(700);
        cout << ".";
        out << name << "|" << release_date << "|" << showtime_date << "|" << time1 << "|" << time2 << "|" << time3 << '\n';
    }

    friend class ShowMovie;
    friend void delete_movie(Movie m1);
};
class ShowMovie
{
public:
    void showMovies(Movie m1)
    {
        string name, release_date, showtime_date, time1, time2, time3;
        const int MAX_LENGTH = 19;
        const char SEPARATOR = '=';

        system("CLS");

        ifstream in("Movies.txt");
        if (!in.is_open())
        {
            cout << "Error opening file 'Movies.txt'" << endl;
            return;
        }

        for (int i = 0; i < MAX_LENGTH * 4; i++)
        {
            cout << SEPARATOR;
        }
        cout << endl;

        cout << "S.no\tMOVIE" << setw(MAX_LENGTH + 1) << "RELEASE DATE" << setw(MAX_LENGTH + 1) << "SHOWTIME DATE" << setw(MAX_LENGTH + 1) << "SHOWTIMES" << endl;

        for (int i = 0; i < MAX_LENGTH * 4; i++)
        {
            cout << SEPARATOR;
        }
        cout << endl;

        int serialNo = 1;
        int j = 0;
        while (getline(in, name, '|') && getline(in, release_date, '|') &&
               getline(in, showtime_date, '|') && getline(in, time1, '|') &&
               getline(in, time2, '|') && getline(in, time3))
        {
            movie_name[j] = name;
            showtimeDate[j] = showtime_date;
            showtime1[j] = time1;
            showtime2[j] = time2;
            showtime3[j] = time3;

            j++;
            cout << left << setw(5) << serialNo << setw(MAX_LENGTH + 1) << name << setw(MAX_LENGTH + 1) << release_date << setw(MAX_LENGTH + 1) << showtime_date << setw(MAX_LENGTH + 1) << time1 << endl
                 << setw(65) << "" << setw(MAX_LENGTH + 1) << time2 << endl
                 << setw(65) << "" << setw(MAX_LENGTH + 1) << time3 << endl;

            serialNo++;
        }

        in.close();
    }
};
class deletee
{
public:
    void delete_movie()
    {
        Movie m;
        ShowMovie s;
        s.showMovies(m);
        string nameToDelete;
        cout << "Enter the name of the movie to delete: ";
        cin >> nameToDelete;

        ifstream in("Movies.txt");
        ofstream out("temp.txt");

        if (!in.is_open())
        {
            cout << "Error opening file 'Movies.txt'" << endl;
            return;
        }

        if (!out.is_open())
        {
            cout << "Error creating temporary file" << endl;
            return;
        }

        string name, release_date, showtime_date, time1, time2, time3;
        while (getline(in, name, '|') && getline(in, release_date, '|') &&
               getline(in, showtime_date, '|') && getline(in, time1, '|') &&
               getline(in, time2, '|') && getline(in, time3))
        {
            if (name != nameToDelete)
            {
                out << name << "|" << release_date << "|" << showtime_date << "|" << time1 << "|" << time2 << "|" << time3 << '\n';
            }
        }

        in.close();
        out.close();

        remove("Movies.txt");
        rename("temp.txt", "Movies.txt");

        cout << "Successfully deleted movie: " << nameToDelete << endl;
        cout << "Press any button to return to admin menu\n";
        getch();
    }
};
class update
{
public:
    void update_movie()
    {
        Movie M;
        ShowMovie s;
        s.showMovies(M);
        string nameToUpdate;
        cout << "Enter the name of the movie to update: ";
        cin >> nameToUpdate;

        ifstream in("Movies.txt");
        ofstream out("temp.txt");

        if (!in.is_open())
        {
            cout << "Error opening file" << endl;
            return;
        }

        if (!out.is_open())
        {
            cout << "Error" << endl;
            return;
        }

        string name, release_date, showtime_date, time1, time2, time3;
        bool movieFound = false;
        while (getline(in, name, '|') && getline(in, release_date, '|') &&
               getline(in, showtime_date, '|') && getline(in, time1, '|') &&
               getline(in, time2, '|') && getline(in, time3))
        {
            if (name == nameToUpdate)
            {
                movieFound = true;
                cout << "Enter name of the movie: ";
                cin.ignore();
                getline(cin, name);
            r1_date:
                cout << "Enter the released date (DD/MM/YYYY): ";
                cin.ignore();
                cin >> release_date;
                if (!isDateValid(release_date))
                {
                    cout << "Invalid date format or value." << endl;
                    goto r1_date;
                }
            s1_date:
                cout << "Enter the showtime date (DD/MM/YYYY): ";
                cin.ignore();
                cin >> showtime_date;
                if (!isDateValid(showtime_date))
                {
                    cout << "Invalid date format or value." << endl;
                    goto s1_date;
                }
            t1_:
                cout << "Enter time of first show: ";
                cin.ignore();
                cin >> time1;
                if (isTimeValid(time1))
                {
                    cout << "Invalid time format or value." << endl;
                    goto t1_;
                }
            t2_:
                cout << "Enter time of second show: ";
                cin.ignore();
                cin >> time2;
                if (isTimeValid(time1))
                {
                    cout << "Invalid time format or value." << endl;
                    goto t2_;
                }
            t3_:
                cout << "Enter time of third show: ";
                cin.ignore();
                cin >> time3;
                if (isTimeValid(time1))
                {
                    cout << "Invalid time format or value." << endl;
                    goto t3_;
                }
            }

            out << name << "|" << release_date << "|" << showtime_date << "|" << time1 << "|" << time2 << "|" << time3 << '\n';
        }

        in.close();
        out.close();

        if (movieFound)
        {
            remove("Movies.txt");
            rename("temp.txt", "Movies.txt");

            cout << "Successfully updated movie: " << nameToUpdate << endl;
        }
        else
        {
            remove("temp.txt");
            cout << "Could not find movie: " << nameToUpdate << endl;
            cout << "Press any button to continue\n";
            getch();
            update_movie();
        }
    }
};

class Customer
{
protected:
    string name, email, phone_number;

public:
    void setName()
    {
        cin.ignore();
        cout << "Enter your name : ";
        getline(cin, name);
        cout << endl;
    }

    void setEmail()
    {
        int valid_email = 0;
        char temp;
        cout << "Enter your email address: ";
        cin >> email;
        cout << endl;

        int email_length = email.length();

        for (int i = 0; i < email.length(); ++i)
        {
            temp = email.at(i);
            if (temp == '@')
            {
                valid_email = 1;
            }
        }

        while (valid_email != 1)
        {
            cout << "Enter a valid email address: ";
            cin.ignore();
            cin >> email;
            cout << endl;

            for (int i = 0; i < email.length(); ++i)
            {
                temp = email.at(i);
                if (temp == '@')
                {
                    valid_email = 1;
                }
            }
        }
    }

    void setPhonenumber()
    {
        cout << "Enter your phone number : ";
        cin.ignore();
        cin >> phone_number;

        int phone_length = phone_number.length();

        while (phone_length != 10)
        {
            cout << endl;
            cout << "Enter a valid phone number: ";
            cin >> phone_number;
            phone_length = phone_number.length();
        }

        cout << endl;
    }

    string getName()
    {
        return name;
    }

    string getPhonenumber()
    {
        return phone_number;
    }

    string getEmail()
    {
        return email;
    }

    ~Customer(){};
};
class Ticket
{
public:
    virtual void purchase() = 0;
};
// Function to display the seating map
void displaySeatingMap(const vector<vector<char>> &seatingMap)
{
    cout << "Seating Map:" << endl;
    for (const auto &row : seatingMap)
    {
        for (char seat : row)
        {
            cout << seat << " ";
        }
        cout << endl;
    }
}
class TicketingService : public Ticket
{
    string namee;
    string ph;
    string name;
    char number[11];

public:
    void purchase() override
    {
        Customer c1;
        Movie m1;
        ShowMovie s;

        int movie_select;
        int numOfSeats = 0;
        system("cls");

        c1.setName();
        c1.setPhonenumber();
        string namee = c1.getName();
        string ph = c1.getPhonenumber();
        s.showMovies(m1);
        int showtime_select, seatNumber[5];
        string showtime, showtime_, movie_, ticket_, customer_, number_, date_;

        cout << "Enter serial number of the movie you want to reserve seat for: ";
        cin >> movie_select; // movie_=movie_name[movie_select];
        cout << "Enter showtime you want to reserve seat for: ";
        cin >> showtime_select;

        if (showtime_select == 1)
        {
            cout << "============== You have selected " << showtime1[movie_select - 1] << ".=====================" << endl;
            showtime = showtime1[movie_select - 1];
        }
        else if (showtime_select == 2)
        {
            cout << "============== You have selected " << showtime2[movie_select - 1] << ".=====================" << endl;
            showtime = showtime2[movie_select - 1];
        }
        else
        {
            cout << "============== You have selected " << showtime3[movie_select - 1] << ".=====================" << endl;
            showtime = showtime3[movie_select - 1];
        }
        ofstream out("Bookings.txt", ios::app);
        const int numRows = 5;
        const int numCols = 5;

        // Create initial seating map
        vector<vector<char>> seatingMap(numRows, vector<char>(numCols, 'O'));
        int ticketNumber;
        // Display initial seating map

        displaySeatingMap(seatingMap);

        // Get user input for occupied seat numbers
        int row[5], col[5];
    numSeats:
        cout << "Enter Number of seats you want to reserve: ";
        cin >> numOfSeats;
        if (numOfSeats < 0 || numOfSeats > 5)
        {
            cout << "Invalid Choice!!!" << endl;
            goto numSeats;
        }

        for (int i = 0; i < numOfSeats; i++)
        {
            cout << "Enter Row and column to reserve a seat: ";
            cin >> row[i] >> col[i];

            // Check if the seat number is valid
            if (row[i] >= 1 && row[i] <= numRows && col[i] >= 1 && col[i] <= numCols)
            {
                // Check if the seat is already occupied
                if (seatingMap[row[i] - 1][col[i] - 1] == 'O')
                {
                    seatingMap[row[i] - 1][col[i] - 1] = 'X';
                    cout << "Seat (" << row[i] << ", " << col[i] << ") has been reserved." << endl;
                    srand(time(0));
                    ticketNumber = rand() % 1000000;
                    cout << "Ticket Number: " << ticketNumber << endl;
                }
                else
                {
                    cout << "Seat (" << row[i] << ", " << col[i] << ") is already occupied." << endl;
                }
            }
            else
            {
                cout << "Invalid seat number. Please try again." << endl;
            }

            // Display updated seating map
            displaySeatingMap(seatingMap);
        }
        system("CLS");
        cout << "=========================================================\n"
             << "=                         RECEIPT                       =\n"
             << "---------------------------------------------------------\n"
             << "=                       MOVIE TICKET                    =\n"
             << "=========================================================\n\n"
             << "\nTicket No. : " << ticketNumber << endl
             << "\nTo Mr/Ms " << c1.getName() << ",\n"
             << "\nYou have booked " << movie_name[movie_select - 1] << " at " << showtime << endl;

        cout << "\nYour selection of seat(s) is : ";
        for (int i = 0; i < numOfSeats; i++)
        {
            cout << "(" << row[i] << "," << col[i] << ")";
            // The comma will not be print out after last seat
            if (i < (numOfSeats - 1))
            {
                cout << ", ";
            }
        }

        cout << "\nPrice of seat(s) : "
             << "Total Seats: " << numOfSeats << endl
             << "Rs " << seat_price * numOfSeats << endl
             << endl;
        cout << "---------------------------------------------------------" << endl
             << left << setw(15) << "\nAmount to PAY : Rs " << seat_price << endl;

        out << namee << "|" << ph << "|" << movie_name[movie_select - 1] << "|" << ticketNumber << "|" << showtime << '|';
        for (int i = 0; i < numOfSeats; i++)
        {
            out << row[i] << ',' << col[i] << '|';
        }
        out << endl;
        out.close();
    }
};

class TicketingAdmin
{
public:
    void showBookings()
    {
        ifstream in("Bookings.txt");
        if (!in.is_open())
        {
            cout << "Unable to open booking file." << endl;
            return;
        }
        cout << "Name            | Phone        | Movie     | Show time     | Ticket   | Seat" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        string name, phone, movie, ticket, showtime, row[5], col[5];
        int i;
        while (getline(in, name, '|') && getline(in, phone, '|') &&
               getline(in, movie, '|') && getline(in, ticket, '|') && getline(in, showtime, '|'))
        {
            for (i = 0; i < 1; i++)
            {
                getline(in, row[i], ',');
                getline(in, col[i]);
                cout << left << setw(12) << name << " | "
                     << setw(15) << phone << " | "
                     << setw(10) << movie << " | "
                     << setw(13) << showtime << " | "
                     << setw(8) << ticket << " | "
                     << setw(4) << row[i] << ',' << col[i] << endl;
            }
        }

        in.close();
        cout << "\n\nPress any button to go to Admin Menu.";
        getch();
    }
};

void menu()
{
    int entry;
    Movie m;
    TicketingService t;
    ShowMovie s;
    deletee d;
    update u;
    char userentry;
    TicketingAdmin ta;
    int ch, ch1, ch2, ch3;
    system("CLS");
home:
    cout << "|--------------------------------------------------------------------|\n";
    cout << "|                WELCOME TO  FAST MOVIE MANAGEMENT SYSTEM             |\n";
    cout << "|--------------------------------------------------------------------|\n";
    cout << "|          Press [1] To Login As Admin                               |\n";
    cout << "|--------------------------------------------------------------------|\n";
    cout << "|          Press [2] To Enter As Customer                            |\n";
    cout << "|--------------------------------------------------------------------|\n";
    cout << "|          Press [3] To Exit                                         |\n";
    cout << "|--------------------------------------------------------------------|\n";
    cout << "\n\nChoose Your Desired Selection : ";
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
    login:
        int password;
        password = 1234;
        string username;
        string admin;
        username = "admin";
        cout << "Enter username:";
        cin >> username;
        if (username == "admin")
        {
            cout << "Enter password:";
            cin >> password;
            cout << "\n";
            if (password == 1234)
            {
                cout << "Logging You In";
                Sleep(750);
                cout << ".";
                Sleep(750);
                cout << ".";
                Sleep(750);
                cout << ".";
                Sleep(750);
                cout << ".";
                Sleep(750);
                system("CLS");
                cout << "Login Successful!\n";
                Sleep(1500);
            adminmenu:
                system("CLS");
                cout << "|--------------------------------------------------------------------|\n";
                cout << "|               ADMIN MENU                                           |\n";
                cout << "|--------------------------------------------------------------------|\n";
                cout << "|          Press [1] To Add New Movies                               |\n";
                cout << "|--------------------------------------------------------------------|\n";
                cout << "|          Press [2] To Update Existing Movies                       |\n";
                cout << "|--------------------------------------------------------------------|\n";
                cout << "|          Press [3] To Delete Movies                                |\n";
                cout << "|--------------------------------------------------------------------|\n";
                cout << "|          Press [4] To View Bookings                                |\n";
                cout << "|--------------------------------------------------------------------|\n";
                cout << "|          Press [5] To Go Back                                      |\n";
                cout << "|--------------------------------------------------------------------|\n";
                cout << "\n\nChoose Your Desired Selection : ";
                cin >> ch1;
                switch (ch1)
                {
                case 1:
                {
                    system("CLS");
                    m.addMovie();
                    goto adminmenu;
                }
                case 2:
                {
                    u.update_movie();
                    goto adminmenu;
                }
                case 3:
                {
                    d.delete_movie();
                    goto adminmenu;
                    break;
                }
                case 4:
                {
                    system("CLS");
                    cout << "---------------- TICKET BOOKING'S --------------" << endl
                         << endl;
                    ta.showBookings();
                    goto adminmenu;
                    break;
                }
                case 5:
                {
                    cout << "Redirecting to Home Screen\nPlease Wait";
                    cout << ".";
                    Sleep(750);
                    cout << ".";
                    Sleep(750);
                    cout << ".";
                    Sleep(750);
                    cout << ".";
                    Sleep(750);
                    system("CLS");
                    goto home;
                }
                default:
                {
                    cout << "Invalid Choice.\n";
                    goto adminmenu;
                }
                }
            }
            else if (password != 1234)
            {
                cout << "Invalid Username/Password\n";
                goto login;
            }
        }
        else if (username != "admin")
        {
            cout << "Invalid Username!\n";
            goto login;
        }
        break;
    }
    case 2:
    {
        cout << "It will take few seconds";
        Sleep(750);
        cout << ".";
        Sleep(750);
        cout << ".";
        Sleep(750);
        cout << ".";
        Sleep(750);
        cout << ".";
        Sleep(750);
        system("CLS");
        cout << "Dear User, Welcome!!\n";
        Sleep(1500);
    custmenu: // Customer Menu
        system("CLS");
        cout << "|--------------------------------------------------------------------|\n";
        cout << "|               CUSTOMER MENU                                        |\n";
        cout << "|--------------------------------------------------------------------|\n";
        cout << "|          Press [1] To Book Movie Ticket                            |\n";
        cout << "|--------------------------------------------------------------------|\n";
        cout << "|          Press [2] To Show Movies                                  |\n";
        cout << "|--------------------------------------------------------------------|\n";
        cout << "|          Press [3] To Go Back                                      |\n";
        cout << "|--------------------------------------------------------------------|\n";

        cout << "\n\nChoose Your Desired Selection : ";
        cin >> ch2;
        switch (ch2)
        {
        case 1:
        {
            system("CLS");
        purchase:
            t.purchase();
            cout << "Do you wish to Continue? Yes[Y]/No[N]\n";
            cin >> userentry;
            if (userentry == 'N' || userentry == 'n')
            {
                goto custmenu;
            }
            else
            {
                goto purchase;
            }
        }
        case 2:
        {
            system("CLS");
            s.showMovies(m);
            cout << "\n\n\n\nPress '1' to go back to the previous menu!\n";
            cin >> entry;
            if (entry == 1)
            {
                goto custmenu;
            }
        }
        case 3:
        {
            cout << "Redirecting to Home Screen\nPlease Wait";
            cout << ".";
            Sleep(750);
            cout << ".";
            Sleep(750);
            cout << ".";
            Sleep(750);
            cout << ".";
            Sleep(750);
            system("CLS");
            goto home;
        }
        }
    }
    case 3:
    {
        system("CLS");
        cout << "Thank You for Using our Movie Management System!\nWe Hope Our Services did not disappoint you!";
        cout << "To Contact Us, You can Email us at the Email listed below!\n";
        cout << "k224266@nu.edu.pk\nk224306@nu.edu.pk\nk224456@nu.edu.pk\n";
        break;
    }
    default:
    {
        cout << "Invalid Choice\n";
    }
    }
}

int main()
{
    menu();
    return 0;
}
