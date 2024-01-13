#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
    :m_userName(full_name), m_userEmail(email), m_userHistory(watch_history)
{

}

string User::get_full_name() const
{
    return m_userName;  
}

string User::get_email() const
{
    return m_userEmail;  
}

vector<string> User::get_watch_history() const
{
    return m_userHistory; 
}
