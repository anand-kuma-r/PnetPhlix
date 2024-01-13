#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile) {
        return false;
    }
    string line;
    while (getline(infile, line)) {


        string id = line;
        for (int i = 0; i < id.size(); i++)
        {
            if (isalpha(id[i]))
                id[i] = tolower(id[i]);
        }

        //cout << "the movie ID: " << id << endl;
        string title;
        
        string releaseYear;
        vector<string> directors;
        vector<string> actors;
        vector<string> genres;
        float rating = 0;

        getline(infile, title);
        //cout << "the movie Title: " << title << endl;
        getline(infile, releaseYear);

        string director;
        string directorLine;
        getline(infile, directorLine);
        for (int i = 0; i < directorLine.size(); i++)
        {
            char c = directorLine[i];
            if (isalpha(c))
            {
                c = tolower(c);
            }
            if (c == ',')
            {
                directors.push_back(director);
                director.clear();
            }
            else
                director += c;
        }
        if (!director.empty())// add last entry since the above code only pushes the string when it sees a comma. if the line doesnt end in a comma there is a missed entry.
            directors.push_back(director);


        
        
        string actor;
        string actorLine;
        getline(infile, actorLine);
        for (int i = 0; i < actorLine.size(); i++)
        {
            char c = actorLine[i];
            if (isalpha(c))
            {
                c = tolower(c);
            }
            if (c == ',')
            {
                actors.push_back(actor);
                actor.clear();
            }
            else
                actor += c;
        }
        if (!actor.empty())// add last entry since the above code only pushes the string when it sees a comma. if the line doesnt end in a comma there is a missed entry.
            actors.push_back(actor);

        /*cout << "Actors: " << endl;
        for (int i = 0; i < actors.size(); i++) {
            cout <<"\t" << actors[i] << endl;
        }*/
        string genre;
        string genreLine;
        getline(infile, genreLine);
        for (int i = 0; i < genreLine.size(); i++)
        {
            char c = genreLine[i];
            if (isalpha(c))
            {
                c = tolower(c);
            }
            if (c == ',')
            {
                genres.push_back(genre);
                genre.clear();
            }
            else
                genre += c;
        }
        if (!genre.empty())// add last entry since the above code only pushes the string when it sees a comma. if the line doesnt end in a comma there is a missed entry.
            genres.push_back(genre);

        infile >> rating;
        infile.ignore(10000, '\n');

        Movie movie(id, title, releaseYear, directors, actors, genres, rating);
        m_movies.insert(movie.get_id(), movie); // has O(LogM) time complexity

        for (int i = 0; i < directors.size(); i++) {
            m_directors.insert(directors[i],movie);
        }
        for (int i = 0; i < actors.size(); i++) {
            m_actors.insert(actors[i], movie);
        }
        for (int i = 0; i < genres.size(); i++) {
            m_genres.insert(genres[i], movie);  //these loops are for adding movies to these things
        }

        getline(infile, line); // gotta account for empty line
    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string copy = id;
    for (int i = 0; i < copy.size(); ++i)
    {
        if (isalpha(copy[i]))
        {
            copy[i] = tolower(copy[i]);
        }
    }
    return &(m_movies.find(copy).get_value());
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string copy = director;
    for (int i = 0; i < copy.size(); ++i)
    {
        if (isalpha(copy[i]))
        {
            copy[i] = tolower(copy[i]);
        }
    }
    vector<Movie*> result;
    TreeMultimap<string, Movie>::Iterator it = m_directors.find(copy);

    while (it.is_valid())
    {
        result.push_back(&(it.get_value()));
        it.advance();
    }
    return result;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string copy = actor;
    for (int i = 0; i < copy.size(); ++i)
    {
        if (isalpha(copy[i]))
        {
            copy[i] = tolower(copy[i]);
        }
    }
    vector<Movie*> result;
    TreeMultimap<string, Movie>::Iterator it = m_actors.find(copy);

    while (it.is_valid())
    {
        result.push_back(&(it.get_value()));
        it.advance();
    }
    return result;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string copy = genre;
    for (int i = 0; i < copy.size(); ++i)
    {
        if (isalpha(copy[i]))
        {
            copy[i]=tolower(copy[i]);
        }
    }
    vector<Movie*> result;
    TreeMultimap<string, Movie>::Iterator it = m_genres.find(copy);

    while (it.is_valid())
    {
        result.push_back(&(it.get_value()));
        it.advance();
    }
    return result;
}
