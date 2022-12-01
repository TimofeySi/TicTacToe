#include "leader.h"

Leader::Leader(std::string name, std::string user_score, std::string computer_score)
    : Name(name), userScore(user_score), computerScore(computer_score)
{

}

std::string Leader::getName() const
{
    return Name;
}

std::string Leader::getUserScore() const
{
    return userScore;
}

std::string Leader::getComputerScore() const
{
    return computerScore;
}

void to_json(json& j, const Leader& leader) {
    j = json {
    {"Name", leader.Name},
    {"User score", leader.userScore},
    {"Computer score", leader.computerScore},
    };
}

void from_json(const json& j, Leader& leader) {
    leader.Name = j.at("Name").get<std::string>();
    leader.userScore = j.at("User score").get<std::string>();
    leader.computerScore = j.at("Computer score").get<std::string>();
}


bool operator==(const Leader &leader1, const Leader &leader2)
{
    if (leader1.Name == leader2.Name)
    {
        if (leader1.userScore == leader2.userScore)
        {
            if (leader1.computerScore == leader2.computerScore)
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}
