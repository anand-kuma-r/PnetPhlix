#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_set>
#include<unordered_map>
#include <algorithm>
#include <utility>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
             const MovieDatabase& movie_database)
    :userdb(user_database), moviedb(movie_database)
{
   
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{



    vector<MovieAndRank> recommendations;
    if (movie_count <= 0) {
        return recommendations;
    }

    // Look up the user by email address
    const User* user = userdb.get_user_from_email(user_email);

    //cout << user->get_full_name() << endl;


    if (!user) {
        return recommendations;
    }


    //try methodically commenting out bits of this code and use print statements to debug where its going wrong
    //unfortunately a stack overflow is preventing me from being able to run this on visual studio :(
    //but it works on g32fast. 
    //start with checking if the watch history got properly copied.
    //then check if the number for compatibity scores gets calculated. not very easy to verify but if it adds something thats good
    //then check if map correctly gets compatibilty score (it should assuming everything is right so far)
    //check the sorts(this will probably be the hardest to verify)
    //check the shortening of the sorted movies to reccomendations
    //if it stil doesnt work idk

    // Get the user's watch history
    vector<string> watched_movies = user->get_watch_history();

    /*for (int i = 0; i < watched_movies.size(); i++)// TESTING THE WATCHEDMOVIED CAN BE ACCESSED SUCCESSFULLY
    {
        cout << watched_movies[i] << endl;
        string copy = watched_movies[i];
        Movie* movie = moviedb.get_movie_from_id(copy);
        cout << movie->get_title();
    }*/


    // Calculate compatibility scores for each movie in the database
    unordered_map<string, int> compatibility_scores;
    for (int i = 0; i < watched_movies.size(); ++i) {

        Movie* movie = moviedb.get_movie_from_id(watched_movies[i]);
        //cout << movie->get_title();

       // Calculate the compatibility score for this movie
        for (const string& director : movie->get_directors()) {//iterate through every director in each movie in watched movie
            for (const Movie* other_movie : moviedb.get_movies_with_director(director)) {//iterates through all movies with that director
                if (watched_movies[i] != other_movie->get_id()) {
                    compatibility_scores[other_movie->get_id()] = +20;
                }
            }
        }
        for (const string& actor : movie->get_actors()) {//iterate through every actor in each movie in watched movie
            for (const Movie* other_movie : moviedb.get_movies_with_actor(actor)) {//iterates through all movies with that actor
                if (watched_movies[i] != other_movie->get_id()) {
                    compatibility_scores[other_movie->get_id()] += 30;
                }
            }
        }
        for (const string& genre : movie->get_genres()) {//iterate through every genre in each movie in watched movie
            for (const Movie* other_movie : moviedb.get_movies_with_genre(genre)) {//iterates through each movie in database that has that genre
                if (watched_movies[i] != other_movie->get_id()) {
                    compatibility_scores[other_movie->get_id()] += 1;
                }
            }
        }
    }
        // Add this movie's compatibility score to the map
       /* if (compatibility_score > 0) {
            compatibility_scores[movie->get_id()] = compatibility_score;
        }
    }*/

    

    /*for (unordered_map<string, int>::iterator it = compatibility_scores.begin(); it != compatibility_scores.end(); ++it)
    {
        Movie* m = moviedb.get_movie_from_id((*it).first);
        cout << m->get_title() << ": " << (*it).second << endl;
    }*/  //THIS FOR LOOP WAS TO TEST IF THE CALUCLUATION OF THE COMPATIBILITY SCORES WORKS AT ALL

    // Sort the movies by compatibility score, rating, and name

    vector<pair<string, int>> sorted_movies(compatibility_scores.begin(), compatibility_scores.end());// create a copy of unordered map that is a vector


    std::sort(sorted_movies.begin(), sorted_movies.end(), comparePairs); // sort the vector that was created using the comparePairs function that is defined in Reccomender.h 

       
        
        for (int i = 0; i < sorted_movies.size() - 1; i++)
        {
            pair<string, int> a = sorted_movies[i];
            pair<string, int> b = sorted_movies[i + 1];
            const Movie* movie_a = moviedb.get_movie_from_id(a.first);
            const Movie* movie_b = moviedb.get_movie_from_id(b.first);
            if (a.second == b.second)//if they have the same compatibility score
            {
                if (movie_a->get_rating() < movie_b->get_rating()) {
                    swap(sorted_movies[i], sorted_movies[i + 1]);
                }
                else if (movie_a->get_rating() == movie_b->get_rating())
                {
                    if (movie_a->get_title() < movie_b->get_title())
                        swap(sorted_movies[i], sorted_movies[i + 1]);
                }
            }
        }

        // Add the top-ranked movies to the recommendations vector
        int count = 0;
        for (const pair<string,int> movie : sorted_movies) {
            if (count >= movie_count) {
                break;
            }
            recommendations.emplace_back(movie.first, movie.second);
            ++count;
        }
        return recommendations;
        
}

