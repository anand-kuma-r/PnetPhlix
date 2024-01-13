#include "UserDatabase.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

UserDatabase::UserDatabase()
{
    
   
}
UserDatabase::~UserDatabase()
{

}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile) {
        return false;
    }

    string line;
    while (getline(infile, line)) {// while there are lines in 
        string full_name = line;
        //cout << "the full name " << full_name << endl;
        string email;
        vector<string> watch_history;

        getline(infile, email);

        int num_movies;
        infile >> num_movies;
        infile.ignore(10000, '\n');
        //cout << " number of movies for each user " << num_movies << endl;
        for (int i = 0; i < num_movies; i++) {
            string movie_id;
            getline(infile, movie_id);
            watch_history.push_back(movie_id);
        }
        User user(full_name, email, watch_history);// create a user with this info
        m_users.insert(user.get_email(), user);
        

        getline(infile, line); // gotta account for empty line
    }
    return true;
}
User* UserDatabase::get_user_from_email(const string& email) const {
    return &(m_users.find(email).get_value());
}