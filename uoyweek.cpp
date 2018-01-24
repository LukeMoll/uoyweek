#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <cstring>

using namespace std;

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
        //Store actual value instead of reference to gmtime so as to avoid issues
        start = *gmtime(&s);
        end = *gmtime(&e);
    }

    bool isIn(time_t ts) {
        return startTS <= ts && ts <= endTS;
    }

    string toString() {
        char yearStr[128];
        //Assign result of asctime to string due to  weird memory management of asctime
        char start_string[128];
        strncpy(start_string, asctime(&start), 128);
        char end_string[128];
        strncpy(end_string, asctime(&end), 128);
        //sprintf is fine for actual values but results of asctime, etc. should be put in string in memory first
        sprintf(yearStr, "%s (%d-%d) %s %s", code.c_str(), ((&start)->tm_year+1900), ((&end)->tm_year+1900), start_string, end_string);
        return yearStr;
    }
};

Term * aut  = new Term("Aut", (time_t) 1506297600l, (time_t) 1512086400l);
Term * spr  = new Term("Spr", (time_t) 1515369600l, (time_t) 1521158400l);
string days[] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

time_t normaliseToMonday(time_t toNormalise) {
    struct tm *tN = gmtime(&toNormalise);
    time_t result = toNormalise;
    result -= tN->tm_sec;
    result -= tN->tm_min * 60;
    result -= tN->tm_hour * 3600;
    result -= (tN->tm_wday - 1) * 24 * 3600;
    return result;
}

int getWeek(time_t now, Term * currentTerm) {
    time_t startNormalised = normaliseToMonday(currentTerm->startTS);
    time_t interval = now - startNormalised;
    int weeks = interval/604800;
    return weeks + 1;
}

Term * getTerm(time_t now) {
    if(aut->isIn(now)) {
        return aut;
    }
    if(spr->isIn(now)) {
        return spr;
    }
    exit(5);
}

string getString() {
    time_t now = time(0);
    Term *term = getTerm(now);
    int week = getWeek(now, term);
    string day = days[gmtime(&now)->tm_wday].substr(0,3);
    int length = strlen(term->code.c_str()) + 2 + 3 + (week>=10?2:1) + 1;
    char* str = (char*) malloc(sizeof(char) * length);
    snprintf(str, length, "%s/%d/%s", term->code.c_str(), week, day.c_str());
    return str;
}

int main(void) {
    cout << getString() <<endl;
}
