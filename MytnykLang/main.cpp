#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

string GetLastEl(string path, char symbol)
{
  string str;
  for (int i = path.size() - 1; i > -1; i--)
  {
    if (path[i] == symbol)
    {
      reverse(str.begin(), str.end());
      return str;
    }
    else 
      str += path[i];
  }
}

string GetAllFromFile(string filename)
{
  ifstream in;
  in.open(filename);
  string t, all;
  int age;
  while (!in.eof())
  {
     getline(in, t);
     all += "/";
    all += t;
  }
  in.close();
  return all;
}

string Next(string all, char symbol, int &line)
{
  string a;
  while (line < all.size() && all[line] != symbol && all[line] != '/')
  {
    a += all[line];

    line++;
  }
  return a;
}

void Compile(string code)
{
  for (int i = 0; i < code.size();i++)
  {
    int line_copy = i;
    if (Next(code, ' ', i) == "print")
    {
      i++;
      string next = Next(code, ' ', i);
      cout << next;
      continue;
    }
    else
      i = line_copy;
    if (Next(code, ' ', i) == "println")
    {
      i++;
      string next = Next(code, ' ', i);
      cout << next << endl;
    }
    else
      i = line_copy;
  }
}

int main(int args, char *file_ptr[]) 
{
  int d;
  string k(file_ptr[args - 1]);
  //string k = "d.txt";
  string code = GetAllFromFile(k);
  Compile(code);
  cin >> d;
}