#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iomanip>
using namespace std;
string temp;
vector<string> lines;
string buffer;
bool founded=false;
class Bbp
{
    int     d;    
    double  pi;                         
    char    pi_hex[14];                 
    clock_t t0, t1;                     
    double  S(int);                     
    long    compModExp(int, int, int);  
    void    convHex(double, char[]);    

public:
    Bbp(int);            
    void compPi();       
};

Bbp::Bbp(int d)
{
    this->d = d - 1;
}

void Bbp::compPi()
{
    pi = 4.0 * S(1) - 2.0 * S(4) - S(5) - S(6);
    pi = pi - (int)pi + 1.0;
    convHex(pi, pi_hex);
    buffer="";
    for (int i = 0; i < 10; i++)
    {
        buffer = buffer + pi_hex[i];
    }
}

double Bbp::S(int j)
{
    double s = 0.0;       
    double t;              
    int    r;              
    int    k;              
    double EPS = 1.0e-17;  

    for (k = 0; k <= d; k++) {
        r = 8 * k + j;
        t = (double)compModExp(16, d - k, r);
        t /= r;
        s += t - (int)t;
        s -= (int)s;
    }

    while (1) {
        r = 8 * k + j;
        t = pow(16.0, (double)(d - k));
        t /= (double)r;
        if (t < EPS) break;
        s += t;
        s -= (int)s;
        k ++;
    }

    return s;
}

long Bbp::compModExp(int b, int e, int m)
{
    long ans;

    if (e == 0) return 1;

    ans = compModExp(b, e / 2, m);
    ans = (ans * ans) % m;
    if ((e % 2) == 1) ans = (ans * b) % m;

    return ans;
}

void Bbp::convHex(double x, char chx[]) {
    double y;
    int i;
    const char hx[] = "0123456789abcdef";
    y = fabs(x);
    for (i = 0; i < 16; i++) {
        y = 16.0 * (y - floor(y));
        chx[i] = hx[(int)(y)];
    }
}
void split(const std::string& str, int splitLength)
{
    int NumSubstrings = str.length() / splitLength;
    for (auto i = 0; i < NumSubstrings; i++)
    {
        lines.push_back(str.substr(i * splitLength, splitLength));
    }
    if (str.length() % splitLength != 0)
    {
        lines.push_back(str.substr(splitLength * NumSubstrings));
    }
}
void readfile(string file)
{
    unsigned char x;
    ifstream input(file, ios::binary);
    input >> noskipws;
    ostringstream tohex;
    while (input >> x) 
    {
    tohex << hex << setw(2) << setfill('0') << (int)x;
    }
    temp=tohex.str();
    split(temp, 5);
}
void checkfound(vector<bool> found)
{
    for(int i=0; i < lines.size(); i++)
    {
        if(found[i]==false)
        {
            founded=false;
        }
    }
}
int main(int argc, char** argv)
{
        readfile(argv[1]);
        int j=1;
        vector<bool> found(lines.size()-1);
        ofstream bruh("bruh.txt");
        string search;
        while(founded == false)
        {
        Bbp objMain(j);
        objMain.compPi();
        for(int i=0; i<lines.size()-1; i++)
        {
            if(found[i] == false)
            {
                search="";
                int d=4;
                for(int f=0; d < 10; f++)
                {
                    search="";
                    search.append(1, buffer[f]);
                    search.append(1, buffer[f+1]);
                    search.append(1, buffer[f+2]);
                    search.append(1, buffer[f+3]);
                    search.append(1, buffer[d]);
                    if(lines[i]==search)
                    {
                    cout << lines[i] << " found at position "<< search << " " << j+f << " " << buffer << endl;
                    bruh << lines[i] << " found at position "<< search << " " << j+f << " " << buffer << endl;
                    found[i]=true;
                    founded=true;
                    checkfound(found);
                    }
                    d++;
                }
                cout << j << " " << buffer << " " << lines[i] << " " << search << endl;
            }

        }
        j++;
        }
        return 0;
}
