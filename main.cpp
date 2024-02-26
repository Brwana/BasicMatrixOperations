#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <math.h>

using namespace std;

vector<char *> split(char *s, char *delim)
{
  vector<char *> result;
  char *section;
  section = strtok(s, delim);
  while (section != NULL)
  {
    result.push_back(section);
    section = strtok(0, delim);
  }
  return result;
}

vector<vector<float>> createMatrix(char *s)
{
  vector<char *> withoutOpeningBracket = split(s, "[");
  vector<char *> withoutClosingBracket = split(withoutOpeningBracket[0], "]");
  char *withoutBrackets = withoutClosingBracket[0];

  vector<char *> rows = split(withoutBrackets, ",");
  vector<vector<float>> Error;

  vector<vector<float>> Matrix;

  for (int i = 0; i < rows.size(); ++i)
  {
    vector<char *> cols = split(rows[i], " ");
    vector<float> colsAsNums;
    for (int j = 0; j < cols.size(); ++j)
    {
      float colsAsF = stof(cols[j]);
      colsAsNums.push_back(colsAsF);
    }

    Matrix.push_back(colsAsNums);
  }
  int num = Matrix[0].size();
  for (int i = 1; i < Matrix.size(); i++)
  {
    if (Matrix[i].size() != num)
    {
      return Error;
    }
  }
  return Matrix;
}

void printMatrix(vector<vector<float>> matrix)
{
  cout << "[";
  for (int i = 0; i < matrix.size(); i++)
  {
    if (i != 0)
    {
      cout << ", ";
    }
    for (int j = 0; j < matrix[i].size(); j++)
    {
      if (j != 0)
      {
        cout << " ";
      }
     
      
      cout << matrix[i][j];
    }
  }
  cout << "]";
}

vector<vector<float>> Addition(vector<vector<float>> Matrix1, vector<vector<float>> Matrix2)
{
  vector<vector<float>> ResultofAddition;

  for (int i = 0; i < Matrix1.size(); i++)
  {
    vector<float> Rows;
    for (int j = 0; j < Matrix1[i].size(); j++)
    {
      Rows.push_back(Matrix1[i][j] + Matrix2[i][j]);
    }
    ResultofAddition.push_back(Rows);
  }
  return ResultofAddition;
}

vector<vector<float>> Subtraction(vector<vector<float>> Matrix1, vector<vector<float>> Matrix2)
{
  vector<vector<float>> ResultofSubtraction;

  for (int i = 0; i < Matrix1.size(); i++)
  {
    vector<float> Rows;

    for (int j = 0; j < Matrix1[i].size(); j++)
    {
      Rows.push_back(Matrix1[i][j] - Matrix2[i][j]);
    }
    ResultofSubtraction.push_back(Rows);
  }
  return ResultofSubtraction;
}

vector<vector<float>> Multiplication(vector<vector<float>> Matrix1, vector<vector<float>> Matrix2)
{
  float sum;
  vector<vector<float>> result;

  for (int i = 0; i < Matrix1.size(); i++)
  {
    vector<float> row;
    for (int x = 0; x < Matrix2[0].size(); x++)
    {
      sum = 0;
      for (int j = 0; j < Matrix1[0].size(); j++)
      {
        sum += Matrix1[i][j] * Matrix2[j][x];
      }
      row.push_back(sum);
    }
    result.push_back(row);
  }

  return result;
}

vector<vector<float>> MultiplicationByScalar(vector<vector<float>> Matrix1, float n)
{

  vector<vector<float>> ResultofMult;

  for (int i = 0; i < Matrix1.size(); i++)
  {
    vector<float> rows;
    for (int j = 0; j < Matrix1.size(); j++)
    {
      rows.push_back(n * Matrix1[i][j]);
    }
    ResultofMult.push_back(rows);
  }
  return ResultofMult;
}
vector<vector<float>>Transpose(vector<vector<float>>matrix)
{
  vector<vector<float>>Newmatrix;
  for(int i=0;i<matrix.size();i++)
  {
    for(int j=0;j<matrix[i].size();j++)
    {
       Newmatrix[j][i]=matrix[i][j];
    }
  }
  return Newmatrix;

}
int main()
{
//  char s1[]="[1 2 3, 4 5 6]";
//  printMatrix(Transpose(createMatrix(s1)));
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */

  char s1[1000];
  cin.getline(s1, 1000);

  char operation[2];
  cin.getline(operation, 2);
  char op = operation[0];

  char s2[1000];
  cin.getline(s2, 1000);

  float n;

  vector<vector<float>> matrix1 = createMatrix(s1);
  
  vector<vector<float>> matrix2 = createMatrix(s2);
 
  if(matrix1.size()==0||matrix2.size()==0)
{
  cout<<"ERROR!";
  return 0;
}


  switch (op)
  {
  case '+':

 if(matrix1.size()!=matrix2.size()||matrix1[0].size()!=matrix2[0].size())
 {
    cout<<"ERROR!";
    return 0;
 }
    printMatrix(Addition(matrix1, matrix2));

    break;

  case '-':

 if(matrix1.size()!=matrix2.size()||matrix1[0].size()!=matrix2[0].size())
 {
    cout<<"ERROR!";
    return 0;
 }
    printMatrix(Subtraction(matrix1, matrix2));

    break;
  case '*':
    if (s1[0] == '[' && s2[0] == '[')

    {
      if(matrix1[0].size()==matrix2.size())
      {
        printMatrix(Multiplication(matrix1, matrix2));
      }
      else{
            cout<<"ERROR!";
      return 0;
      }
      
    }
    if (s1[0] == '[' && s2[0] != '[')
    {
      n=stof(s2);
      printMatrix(MultiplicationByScalar(matrix1, n));
    }
    if (s1[0] != '[' && s2[0] == '[')
    {  n=stof(s1);
      printMatrix(MultiplicationByScalar(matrix2, n));
    }

    break;
  }

  return 0;
}


