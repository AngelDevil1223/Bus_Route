#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <string.h>
#include<fstream>
#include<vector>
#include<time.h>
#include<ctype.h>

using namespace std;

int remove(string s)
{
    if (s.size() == 4)
        s.replace(1, 1, "");
    if (s.size() == 5)
        s.replace(2, 1, "");
    return std::stoi(s);
}

string difference(string s1, string s2)
{

    int time1 = remove(s1);
    int time2 = remove(s2);
    int hourDiff = time2 / 100 - time1 / 100 -1;
    int minDiff = time2 % 100 + (60 - time1 % 100);
    if (minDiff >= 60) {
        hourDiff++;
        minDiff = minDiff - 60;
    }
    string res = to_string(hourDiff) + ':' + to_string(minDiff);
    return res;
}
