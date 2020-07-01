#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <tuple>

using namespace std;
typedef long long lld;

tuple<lld**, int, int> readMatrix(string filename)
{
    int n = 0,m = 0;
    
    lld** matrix;
    string line, text;
    ifstream file;

    file.open("matrixes/"+filename,ios::in);
    if(!file)
    {
            cout<<"Error al abrir archivo!"<<endl;
            return make_tuple(matrix,-1,-1);
    }

    
    while (!file.eof())
    {
            getline(file,line);
            text += line + " ";
            
            n ++;
    }

    file.close();
    
    istringstream iss(text);
    vector<string> results((istream_iterator<string>(iss)),
                                istream_iterator<string>());
    vector<int> aux;
    m = results.size()/n;
    
    matrix = new lld*[n];
    for (int i=0;i<n;i++)
        matrix[i] = new lld[m];
    
    for (int i=0;i<results.size();i++)
        matrix[i / m][i % m] = stoi(results[i]);
    
    return make_tuple(matrix,n,m);
}