/* 
 * File:   main.cpp
 * Author: c4lichua
 *
 * Created on March 20, 2015, 4:54 PM
 */



#include <cstdlib>
#include <iostream>     // std::cout, std::end
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <set>
#include <limits>
using namespace std;


/*
 * 
 */
//This is container for the each sub vector
vector<vector<string> > subvector;
 int current_max = numeric_limits<int>::max();;
void checker(vector<string> &myvector,  int even){
  //outer iterator is i from 0 to end
  //odd
  int step = 0;
  if(even == 1){
      step = 1;
  }
  for(int i = 0; i < myvector.size(); i++){
      //odd cases
      int upper = i+step; 
      int lower = i;
      //j is upper bound, i is lower bound
      while(lower >= 0 && upper<myvector.size()){
          if(myvector[lower] == myvector[upper] && upper-lower+1<=current_max){
              vector<string> v1(myvector.begin()+lower, myvector.begin()+upper+1);
              subvector.push_back(v1);
              lower--;
              upper++;
          }
          else{
              break;
          }
      }
  }
}


int main(int argc, char* argv[]) {
 string line;
 ifstream myfile (argv[1]);


 vector<vector<string> > common;
 vector<string> final;

 int max_words;
 if (myfile.is_open()){
    while (! myfile.eof()){
      getline (myfile,line);

      int end  = 0;
      int start = 0;
      vector<string> myvector;

          while (line.size()+1 > end){

            char c=line[end];
            //detect the space
            if (isspace(c)){
                myvector.push_back(line.substr(start, end-start));
                start = end+1;
            };
            end++;
          }
          //append the last element into the vector
          myvector.push_back(line.substr(start, end-start));

          //odd
          int first = 0;
          checker(myvector, first);

          //even
          int second = 1;
          checker(myvector, second);
          if(common.empty()){
                //first round
                set<vector<string> >  s(subvector.begin(), subvector.end());
                common.assign(s.begin(), s.end());
          }
          else{
                //merge
                vector<vector<string> > merged;
                set<vector<string> > s(subvector.begin(), subvector.end());
                subvector.assign(s.begin(), s.end());
                sort(subvector.begin(), subvector.end());
                sort(common.begin(), common.end());
                set_intersection(subvector.begin(), subvector.end(), common.begin(), common.end(), back_inserter(merged));
                common = merged;
                merged.clear();
          }   
          subvector.clear();
          myvector.clear();
          //updating the max
          for ( int i = 0; i < common.size(); i++) {
              if(i == 0){
                  final = common[i];
                  current_max = common[i].size();
              }
              else{
                  if(current_max < common[i].size()){
                        current_max = common[i].size();
                        final = common[i];
                  }
              }
         }
    }
    myfile.close();
  }
 
  
 for(int i = 0; i < final.size(); i++){
     cout << final[i] << " ";
 }
    cout<<endl;
 return 0;
}

