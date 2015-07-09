#ifndef CODECLEAR_H
#define CODECLEAR_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class CodeClear
{
private:
    vector<char> sumbol;

private:
    void SomeExtraSpace(string &str);
    void Trim(string &str);

public:
    CodeClear();
    ~CodeClear();

    void ClearText(string &str);
};

#endif // CODECLEAR_H
