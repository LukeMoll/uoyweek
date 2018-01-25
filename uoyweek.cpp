#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <cstring>

using std::string;

const int SECS_PER_MIN = 60;
const int SECS_PER_HOUR = 60 * SECS_PER_MIN;
const int SECS_PER_DAY = 24 * SECS_PER_HOUR;
const int SECS_PER_WEEK = 7 * SECS_PER_DAY;

const string DAYS[] = {
    "sunday",
    "monday",
    "tuesday",
    "wednesday",
    "thursday",
    "friday",
    "saturday"
};

class Term {
    public:
    time_t startTS;
    time_t endTS;
    struct tm start;
    struct tm end;
    string code;

    Term(string c, time_t s, time_t e) {
        code = c;
        startTS = s;
        endTS = e;
        /* Store actual value instead of reference to gmtime so as to avoid
         * issues */
        start = *gmtime(&s);
        end = *gmtime(&e);
    }

    bool isIn(time_t ts) {
        return startTS <= ts && ts <= endTS;
    }

    string toString() {
        char yearStr[128];
        /* Assign result of asctime to string due to  weird memory management of
         * asctime */
        char start_string[128];
        strncpy(start_string, asctime(&start), 128);
        char end_string[128];
        strncpy(end_string, asctime(&end), 128);
        /* sprintf is fine for actual values but results of asctime, etc. should
         * be put in string in memory first */
        sprintf(yearStr, "%s (%d-%d) %s %s",
                code.c_str(),
                (&start)->tm_year + 1900,
                (&end)->tm_year + 1900,
                start_string,
                end_string);
        return yearStr;
    }
};

const int AUT_START = 1506297600l;
const int AUT_END = 1512086400l;
const int SPR_START = 1515369600l;
const int SPR_END   = 1521158400l;

Term *aut = new Term("aut", (time_t)AUT_START, (time_t)AUT_END);
Term *spr = new Term("spr", (time_t)SPR_START, (time_t)SPR_END);

time_t normaliseToMonday(time_t toNormalise) {
    struct tm *tN = gmtime(&toNormalise);
    time_t result = toNormalise;
    result -= tN->tm_sec;
    result -= tN->tm_min * SECS_PER_MIN;
    result -= tN->tm_hour * SECS_PER_HOUR;
    result -= (tN->tm_wday - 1) * SECS_PER_DAY;
    return result;
}

int getWeek(time_t now, Term *currentTerm) {
    time_t startNormalised = normaliseToMonday(currentTerm->startTS);
    time_t interval = now - startNormalised;
    return interval/SECS_PER_WEEK + 1;
}

Term *getTerm(time_t now) {
    if(aut->isIn(now)) {
        return aut;
    }
    if(spr->isIn(now)) {
        return spr;
    }
    exit(5);
}

string getString(bool capitalize) {
    time_t now = time(0);
    Term *term = getTerm(now);
    string code = term->code;
    int week = getWeek(now, term);
    string day = DAYS[gmtime(&now)->tm_wday].substr(0,3);
    if (capitalize) {
        code[0] = std::toupper(code[0]);
        day[0] = std::toupper(day[0]);
    }
    int length = strlen(term->code.c_str()) + 2 + 3 + (week/10 + 1) + 1;
    char *str = (char *)malloc(sizeof(char) * length);
    snprintf(str, length, "%s/%d/%s", code.c_str(), week, day.c_str());
    return str;
}

int main(void) {
    std::cout << getString(false) << std::endl;
}
