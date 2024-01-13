#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include"UserDatabase.h"
#include"MovieDatabase.h"

#include <string>
#include <vector>
#include <utility>

class UserDatabase;
class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
      UserDatabase userdb;
      MovieDatabase moviedb;
};

bool inline comparePairs(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second; // Sort in descending order of compatibility score (returns true if a's compatibilty rating is less than b's)
}
#endif // RECOMMENDER_INCLUDED
