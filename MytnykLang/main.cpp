#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Any
{
public:
  int Int;
  string String;
  double Double;
  char Char;
};

enum Type
{
  Int,
  String,
  Double,
  Char
};

class Variable
{
public:
  Type type;
  string name;
  Any value;
  bool operator==(Variable var)
  {
    if (this->name == var.name &&
      this->type == var.type &&
      this->value.String == var.value.String &&
      this->value.Char == var.value.Char &&
      this->value.Double == var.value.Double &&
      this->value.Int == var.value.Int)
      return true;
    else
      return false;
  }
};

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
    if (all != "")
      all += "/";
    all += t;
  }
  in.close();
  return all;
}

string Next(string all, char symbol, int &line)
{
  string a;
  if (symbol == '\"')
    line++;
  while (line < all.size() && all[line] != symbol && all[line] != '/')
  {
    a += all[line];

    line++;
  }
  return a;
}

Variable GetByName(vector<Variable> variables, string name)
{
  for (Variable var : variables)
    if (var.name == name)
      return var;
}

int GetIndexByVariable(vector<Variable> variables, Variable var)
{
  for (size_t i = 0; i < variables.size(); i++)
    if (variables[i] == var)
      return i;
}

string ListenQuotes(string all, int &line)
{
  return Next(all, '\"', line);
}

void Compile(string code)
{
  vector<Variable> variables;
  for (int i = 0; i < code.size();i++)
  {
    int line_copy = i;
    if (Next(code, ' ', i) == "print")
    {
      i++;
      string next;
      if (code[i] == '\"')
      {
        next = ListenQuotes(code, i);
        cout << next << endl;
        i++;
      }
      else
      {
        next = Next(code, ' ', i);
        cout << GetByName(variables, next).value.String << endl;
      }
      continue;
    }
    else
      i = line_copy;
    if (Next(code, ' ', i) == "println")
    {
      i++;
      string next;
      if (code[i] == '\"')
      {
        next = ListenQuotes(code, i);
        cout << next << endl;
        i++;
      }
      else
      {
        next = Next(code, ' ', i);
        cout << GetByName(variables, next).value.String << endl;
      }
      continue;
    }
    else
      i = line_copy;
    if (Next(code, ' ', i) == "var")
    {
      i++;
      string next = Next(code, ' ', i);
      Variable var;
      var.name = next;
      variables.push_back(var);
      cout << "Variable added";
      continue;
    }
    else
      i = line_copy;
    string next = Next(code, ' ', i);
    i++;
    string next2 = Next(code, ' ', i);
    if (next2 == "=")
    {
      i++;
      string next3 = ListenQuotes(code, i);
      Variable Var = GetByName(variables, next);
      variables[GetIndexByVariable(variables, Var)].value.String = next3;
      i++;
    }
  }
}

int main(int args, char *file_ptr[]) 
{
  int d;
  string k(file_ptr[args - 1]);
  //string k = "d.m";
  if (GetLastEl(k, '.') != "m")
  {
    cout << "Error file .m" << endl;
  }
  else
  {
    string code = GetAllFromFile(k);
    if (code == "")
    {
      cout << "File is empty" << endl;
      cin >> d;
    }
    Compile(code);
  }
  cin >> d;
}