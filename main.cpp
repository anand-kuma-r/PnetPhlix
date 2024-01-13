#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include "MovieDatabase.h"
#include "Recommender.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";


int main()
{


	/*TreeMultimap<int, string> myMap1;
	myMap1.insert(1, "value1");
	myMap1.insert(2, "value2");
	myMap1.insert(3, "value3");

	TreeMultimap<int, string>::Iterator it1 = myMap1.find(1);
	//cout << it.nodes.empty();
	//cout << it.get_value() << endl;
	assert(it1.is_valid());
	assert(it1.get_value() == "value1");
	it1.advance();
	assert(!it1.is_valid());

	

	TreeMultimap<int, string>::Iterator it3 = myMap1.find(3);
	assert(it3.is_valid());
	assert(it3.get_value() == "value3");
	it3.advance();
	assert(!it3.is_valid());

	TreeMultimap<int, std::string> myMap;

	// Insert some values
	myMap.insert(1, "value1");
	myMap.insert(2, "value2");
	myMap.insert(3, "value3");
	myMap.insert(2, "value4"); // multiple values can be inserted with the same key

	// Find all values with key 2 and print them
	TreeMultimap<int, std::string>::Iterator it = myMap.find(2);
	while (it.is_valid()) {
		std::cout << it.get_value() << std::endl;
		it.advance();
	}

	// Find all values with key 4 (which doesn't exist) and print them
	TreeMultimap<int, std::string>::Iterator it2 = myMap.find(4);
	while (it2.is_valid()) {
		std::cout << it2.get_value() << std::endl;
		it2.advance();
	}

	cout << "all tests passed!!" << endl;
	getchar(); // wait for user input before closing the window
	*/

	UserDatabase udb;
	if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
	else
	{
		cout << "Loaded user data file " << endl;
	}
	/*for (;;)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email); //using the stl map says this must be a const
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
		{
			cout << "Found " << u->get_full_name() << endl;

			vector<string> v = u->get_watch_history();
			for (int i = 0; i < v.size(); i++)
			{
				cout << v[i]<< endl;
			}
		}

	}*/

	//return 0; ///THE LAST THING I DID DURING LAST SESSION WAS: revert code back to the state where treemm works for Userdatabase but Moviedatabase causes stack overflow. likely cuz of way too many insert calls in MvieDatabase load function.
		MovieDatabase mdb;
		if (!mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
		{
			cout << "Failed to load movie data file " << MOVIE_DATAFILE << "!" << endl;
			return 1;
		}
		else
		{
			cout << "Loaded movie data file " << endl;
		}
		/*for (;;)
		{
			cout << "Enter movie actor name (or quit): "; //Try Will Ferrell
			string id;
			getline(cin, id);
			if (id == "quit")
				return 0;
			//Movie* u = mdb.get_movie_from_id(id); //using the stl map says this must be a const
			vector<Movie*> m = mdb.get_movies_with_actor(id);
			for(int i=0 ;i<m.size();i++)
			{
			Movie* u = m[i];
			if (u == nullptr)
				cout << "No user in the database has that email address." << endl;
			else
				cout << "Found " << u->get_title() << endl;
			}
		}
	*/
	Recommender r(udb, mdb);
	for (;;)
	{
		cout << "Enter user email address (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;

		vector<MovieAndRank> recommendations = r.recommend_movies(email, 5);

		
		User* u = udb.get_user_from_email(email);


			vector<string> his = u->get_watch_history();
		for (int i = 0; i < his.size(); ++i)
		{
			Movie* m = mdb.get_movie_from_id(his[i]);
			cout << m->get_title()<< endl;
			}
			if (recommendations.empty())
				cout << "We found no movies to recommend :(.\n";
			else {
				for (int i = 0; i < recommendations.size(); i++) {
					const MovieAndRank& mr = recommendations[i];
					Movie* m = mdb.get_movie_from_id(mr.movie_id);
					cout << i << ". " << m->get_title() << " ("
						<< m->get_release_year() << ")\n Rating: "
						<< m->get_rating() << "\n Compatibility Score: "
						<< mr.compatibility_score << "\n";
				}
			}
	}/**/
		return 0;
}
