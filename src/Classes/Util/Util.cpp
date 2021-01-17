#include "./Util.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

Util::Util(){

}

bool Util::findElement(int element, vector<int> vector){
   
    auto it = std::find(vector.begin(), vector.end(), element);
    if (it != vector.end())
    {
       return true;
    }
    else
    {
        return false;
    }
  
}