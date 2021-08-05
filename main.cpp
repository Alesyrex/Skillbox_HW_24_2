#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>

struct BIRTHDAY{
    std::tm date;
    std::string name = "unknown";
};

int year_days (std::tm &tm) {
    std::time_t time = std::mktime(&tm);
    std::tm x = *std::localtime(&time);
    if ((x.tm_year % 400 == 0 || (x.tm_year % 100 != 0 && x.tm_year % 4 == 0))
        && x.tm_yday > 59)
        return x.tm_yday - 1;
    else return x.tm_yday;
}

int main() {

    BIRTHDAY friends;
    std::vector<BIRTHDAY> birthdayList;
    std::vector<BIRTHDAY> nearestBirthday;
    std::time_t date = std::time(nullptr);
    friends.date = *std::localtime(&date);
    std::tm today = *std::localtime(&date);


    std::cout << "Enter your friend's name and date of birth in the format 'YYYY/MM/DD'.\n";
    std::cout << "To end input enter 'end'.\n";

    do {
        std::cin >> friends.name;
        if (friends.name == "end") break;
        std::cin >> std::get_time (&friends.date, "%Y/%m/%d");
        birthdayList.push_back(friends);
    } while (friends.name != "end");

    int minDifference = 365;
    int tmp;
    bool todayBirthday = false;

    for (int i=0;i < birthdayList.size();++i) {
        if (year_days(birthdayList[i].date) >= year_days(today)) {
            tmp = year_days(birthdayList[i].date) - year_days(today);
            if (tmp == 0) todayBirthday = true;
            if (tmp == minDifference) {
                nearestBirthday.push_back(birthdayList[i]);
            } else if (tmp < minDifference) {
                minDifference = tmp;
                nearestBirthday.resize(0);
                nearestBirthday.push_back(birthdayList[i]);
            }
        }
    }

    for (int i=0;i < nearestBirthday.size();++i) {
        std::cout << nearestBirthday[i].name << " " << std::put_time (&nearestBirthday[i].date,"%m/%d") << std::endl;
        if (todayBirthday) std::cout << "Happy Birthday " << nearestBirthday[i].name << "!" << std::endl;
    }

    return 0;
}
