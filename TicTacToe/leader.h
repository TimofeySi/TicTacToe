#pragma once

#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Leader
{
public:
    Leader(std::string name, std::string user_score, std::string computer_score);

private:
    std::string Name;
    std::string userScore;
    std::string computerScore;

public:
    std::string getName() const;
    std::string getUserScore() const;
    std::string getComputerScore() const;

    friend void to_json(json& j, const Leader& leader);
    friend void from_json(const json& j, Leader& leader);

    friend bool operator==(const Leader &leader1, const Leader &leader2);
};

