//CINEMATE: A NEW GEN MOVIE TICKET BOOKING EXPERIENCE::::
//Made by : ABHIJEET(24BDE0015)...... PRATYUSH(24BIT0596) ...... VAAMAN(24BDE0067)...... RIDHI(24BDE0171)

#include <iostream> 
#include <fstream> // to work with files (read/write) basically we had to learn this for  text file operations...
#include <string> 
using namespace std;

class User {
protected:
    int id; 
    string name; 
    string role; 
public:

    User(int userId, string userName, string userRole) {
        id = userId;
        name = userName;
        role = userRole;
    }
    // Displays user details
    void displayInfo() {
        cout << "User ID: " << id << ", Name: " << name << ", Role: " << role << endl;
    }
};

// Admin inherits from User
class Admin : public User {
public:

    Admin(int userId, string userName) : User(userId, userName, "Admin") {}

    // Adds movie details to a file
    void addMovie(string title, string timing, double price, string genre) {
        ofstream file("Movies.txt", ios::app); // opens Movies.txt to add data
        if (file) {
            file << title << " | Genre: " << genre << " | Timing: " << timing << " | Price: " << price << endl;
            cout << "Movie added successfully and saved to Movies.txt\n";
        }
    }
};

// Checks if a seat is free by reading booked seat numbers from file
bool isSeatAvailable(int seatNum) {
    ifstream file("Seats.txt");
    int seat;
    while (file >> seat) {
        if (seat == seatNum) return false; // found booked seat
    }
    return true; // seat is free
}

// This will add seat number to booked list so that we have a record of booked seats and the same seat wouldnt be booked ....
void bookSeat(int seatNum) {
    ofstream file("Seats.txt", ios::app);
    file << seatNum << endl;
}

// Now this is our USP...  which no other site has...suggesting you movies based on your mood to watch isnt it great?
string mapMoodToGenre(string mood) {
    if (mood == "happy") return "comedy";
    if (mood == "sad") return "drama";
    if (mood == "excited") return "action";
    if (mood == "thoughtful") return "documentary";
    if (mood == "romantic") return "romance";
    if (mood == "scared") return "horror";
    if (mood == "curious") return "sci-fi";
    return "any"; //if  mood is unknown by the user .....(we have to work on this but these are the limited moods we added )
}


class Customer : public User {
public:
    Customer(int userId, string userName) : User(userId, userName, "Customer") {}

    // This function will display all the movies available to watch for a user... (Added by the admin obviously)..
    void viewMovies() {
        ifstream file("Movies.txt");
        string movie;
        cout << "Available Movies:\n";
        while (getline(file, movie)) {
            cout << "- " << movie << endl;
        }
    }

    // So we made an improvement of not asking the user to give the ticket price also as input as 
    // its set by admin so we had to make this function to search up for the price saved in movies text file for 
    // the particular movie the user has searched so that he can just pay the movie ticket price directly....
    double getMoviePrice(const string& movieTitle, const string& timing) {    //we use const and & to pass the specific string by reference instead of copying it to make it more efficient..
        ifstream file("Movies.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(movieTitle) != string::npos && line.find(timing) != string::npos) {
                size_t pricePos = line.find("Price: ");
                if (pricePos != string::npos) {
                    return stod(line.substr(pricePos + 7));
                }
            }
        }
        return -1; //  means not found..
    }

    // This is the core of our project that is the booking itself....we have added the seat availability checker , movie price getter
    // using the above function , a function to marka seat as booked if booking done succesfully , popcorn!! who can watch a movie without it..
    void bookTicket(string movie, int seatNum, string timing, bool popcorn) {
        if (!isSeatAvailable(seatNum)) {
            cout << "Seat " << seatNum << " is already booked! Returning to main menu.\n";
            return;
        }

        double price = getMoviePrice(movie, timing); // get ticket price of the movie as given by the admin
        if (price < 0) {
            cout << "Could not retrieve price for selected movie and timing.\n";
            return;
        }

        bookSeat(seatNum); //  this will mark seat as booked ....very important to not upset people by bad service of same seat number
        double totalPrice = price + (popcorn ? 89 : 0); // we made the popcorn cost Rs.89 extra...we have cheap popcorn comparitively (Hehe)
        cout << "Total price: Rs." << totalPrice << endl;
        //payment is to ensure we are profitable ....cant sell tickets for free...
        double payment;
        while (true) {
            cout << "Enter payment amount: ";
            cin >> payment;
            if (payment < totalPrice) {
                cout << "Insufficient payment! Please try again.\n";
            } else {
                break;
            }
        }

        // Now we also have to save the booking details to provide our customer a proof of booking....
        ofstream file("Bookings.txt", ios::app);
        file << name << " booked: " << movie << " | Seat: " << seatNum << " | Timing: " << timing << " | Popcorn: " << (popcorn ? "Yes" : "No") << " | Total Price: " << totalPrice << endl;
        cout << "Booking successful! Change: Rs." << payment - totalPrice << endl;
        cout << "Booking saved in Bookings.txt\n";
    }

    // Our customer will be able to see their bookings and get an entry into the hall showing these details right...
    void viewBookings() {
        ifstream file("Bookings.txt");
        string line;
        cout << " Your Bookings:\n";
        while (getline(file, line)) {
            if (line.find(name) != string::npos) {
                cout << line << endl;
            }
        }
    }

    // This is where the movies will be suggested based on the customer's mood ....hence the functioning of our unique feature
    void suggestMovieByMood(string mood) {
        string genre = mapMoodToGenre(mood);
        ifstream file("Movies.txt");
        string movie;
        cout << "Suggested Movies for mood: " << mood << " (Genre: " << genre << ")\n";
        bool found = false;
        while (getline(file, movie)) {
            if (movie.find(genre) != string::npos || genre == "any") {
                cout << "- " << movie << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No suggestions available for your mood right now.\n";
        }
    }
};

// Makes sure files are created if they don’t exist...( a bug fix ...we were having trouble running the code without this..)
void ensureFilesExist() {
    ofstream("Movies.txt", ios::app).close();
    ofstream("Seats.txt", ios::app).close();
    ofstream("Bookings.txt", ios::app).close();
}

// Main program..(We made it as a loop so that we dont have to run the program for each and every function and and again (fixed by Vaaman))
int main() {
    ensureFilesExist(); // this is to create needed files if not already present as we dont want ppl to create three separate text files all the time

    Admin admin(1, "AdminUser"); // hardcoded admin
    Customer customer(2, "CustomerUser"); // hardcoded customer

    while (true) {
        int choice;
        cout <<endl<<"Movie Ticket Booking Menu"<<endl;
        cout << "1. Add Movie (Admin)"<<endl;
        cout << "2. View Movies"<<endl;
        cout << "3. Book Ticket"<<endl;
        cout << "4. View Bookings"<<endl;
        cout << "5. Suggest Movie by Mood"<<endl;
        cout << "0. Exit"<<endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            string title, timing, genre;
            double price;
            cout << "Enter movie title: ";
            cin >> title;
            cout << "Enter genre (e.g. action, comedy, drama): ";
            cin >> genre;
            cout << "Enter show timing: ";
            cin >> timing;
            cout << "Enter ticket price: Rs.";
            cin >> price;
            admin.addMovie(title, timing, price, genre);

        } else if (choice == 2) {
            customer.viewMovies();

        } else if (choice == 3) {
            string movie, timing;
            int seatNum;
            char popcornChoice;
            bool popcorn;
            cout << "Enter movie title to book: ";
            cin >> movie;
            cout << "Enter seat number: ";
            cin >> seatNum;
            if (!isSeatAvailable(seatNum)) {
                cout << "Seat " << seatNum << " is already booked! Returning to main menu."<<endl;//to come out if seat already booked why ask further details..
                continue;
            }
            cout << "Enter show timing (no spaces): ";
            cin >> timing;
            cout << "Do you want popcorn? (y/n): ";
            cin >> popcornChoice;
            popcorn = (popcornChoice == 'y' || popcornChoice == 'Y');
            customer.bookTicket(movie, seatNum, timing, popcorn);

        } else if (choice == 4) {
            customer.viewBookings();

        } else if (choice == 5) {
            string mood;
            cout << "Enter your current mood (happy, sad, excited, romantic, etc.): ";
            cin >> mood;
            customer.suggestMovieByMood(mood);

        } else if (choice == 0) {
            cout << "Exiting... Goodbye!\n";
            break;

        } else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
//Hope you liked our small project....
//Made by Abhijeet , Vaaman , Pratyush , Ridhi
/*We made a static website based on this for the frontend part using html,css,javascript..(We cannot run this code as a website directly as its a cpp code
so we had to make the website with same functioning as this using html,css,javascript....its basically mimicing our cpp project instead of directly
using the same as its not possible for websites to run cpp backend as browsers dont understand cpp as they dont have built in compilers,
cpp itself is a compiled programming language used for games , software tools, etc whereas web programming understands completely 
different languages like html , css , javascript , etc. ).............abort*/

                                  //                   ~THANK YOU~              / /
