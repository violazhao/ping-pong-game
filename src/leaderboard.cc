// Copyright (c) 2020 [Your Name]. All rights reserved.
// taken from snake

#include <mylibrary/leaderboard.h>
#include <mylibrary/player.h>
#include <sqlite_modern_cpp.h>

#include <string>
#include <vector>

namespace mylibrary {

using std::string;
using std::vector;

// See examples: https://github.com/SqliteModernCpp/sqlite_modern_cpp/tree/dev

LeaderBoard::LeaderBoard(const string& db_path) : db_{db_path} {
    db_ << "CREATE TABLE if not exists leaderboard (\n"
           "  name  TEXT NOT NULL,\n"
           "  score INTEGER NOT NULL\n"
           ");";
}

void LeaderBoard::AddScoreToLeaderBoard(const Player& player) {
    string player_name = player.name;
    int player_score = static_cast<int>(player.score);
    db_ << "insert into leaderboard (name,score) values (?,?);" << player_name << player_score;
}

vector<Player> GetPlayers(sqlite::database_binder* rows) {
    vector<Player> players;

    for (auto&& row : *rows) {
        string name;
        size_t score;
        row >> name >> score;
        Player player = {name, score};
        players.push_back(player);
    }

    return players;
}

vector<Player> LeaderBoard::RetrieveHighScores(const size_t limit) {
    auto rows = db_ << "select name,score from leaderboard order by score DESC limit (?);" << limit;
    return GetPlayers(&rows);
}

vector<Player> LeaderBoard::RetrieveHighScores(const Player& player,
                                               const size_t limit) {
    auto rows = db_ << "select name,score from leaderboard where name = (?) order by score DESC limit (?);" << player.name << limit;
    return GetPlayers(&rows);
}

}  // namespace mylibrary
