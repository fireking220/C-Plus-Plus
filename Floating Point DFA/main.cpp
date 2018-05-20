#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

static int SZ = 50;

int main(){
  //row indicies are states
  //col indicies are possible symbols
  //col index 0-9 are symbols 0-9
  //col index 10 is +
  //col index 11 is -
  //col index 12 is .
  //col index 13 is e
  //col index 14 is E
  bool match = false;
  bool Accepted = false;
  int curState = 0;
  int numOfAcceptStates = 3;
  int acceptStates[numOfAcceptStates] = {4,5,7};
  int symbolNum = 15;
  //this is our DFA for detecting floating point numbers in our alphabet
  int fpDFA[9][symbolNum] = {{1,1,1,1,1,1,1,1,1,1,2,2,3,8,8},
                             {1,1,1,1,1,1,1,1,1,1,8,8,4,8,8},
                             {1,1,1,1,1,1,1,1,1,1,8,8,3,8,8},
                             {4,4,4,4,4,4,4,4,4,4,8,8,8,8,8},
                             {4,4,4,4,4,4,4,4,4,4,8,8,8,5,5},
                             {7,7,7,7,7,7,7,7,7,7,6,6,8,8,8},
                             {7,7,7,7,7,7,7,7,7,7,8,8,8,8,8},
                             {7,7,7,7,7,7,7,7,7,7,8,8,8,8,8},
                             {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}};
  //this is our alphabet
  char symbols[symbolNum] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '.', 'e', 'E'};
  char * line = new char[SZ];
  ifstream in;

  //open our file
  in.open("Points.txt");
  //check if our file is opened
  if(!in.is_open()){
    cout << "Failed to open file\n";
  }
  //if our file is opened do this
  else{
    cout << "Opened file\n";
    //read the file to the end, getting each line and storing it inside the variable line
    while(in.getline(line, SZ)){
      int length = strlen(line);
      //displays the state path throughout of DFA
      cout << line << " State order: ";
      //grabs the ith character in line
      for(int i = 0; i < length; ++i){
        //compare the ith character in line with every symbol in our aplhabet
        for(int j = 0; j < symbolNum; ++j){
          //if we found a match, set the cur state to the state in the jth index, set
          //match to true, and break out of the loop since we don't have to search anymore
          if(line[i] == symbols[j]){
            curState = fpDFA[curState][j];
            cout << curState << " ";
            match = true;
            break;
          }
        }
        //if we didn't find a match, then the ith character is not in our alphabet so
        //we immediately go dead
        if(match == false){
          //this is the dead state
          curState = 8;
          cout << curState << " ";
        }
        //set match to false so we can compare the next ith element
        match = false;
      }
      //check to see if the curState is in an accept state
      for(int i = 0; i < numOfAcceptStates; ++i){
        //if curState is equal to at least one of our acceptStates, set accepted to true and
        //accept the string
        if(curState == acceptStates[i]){
          cout << "Accepted\n";
          Accepted = true;
        }
      }
      //if we were not in an acept state, reject the string
      if(!Accepted){
        cout << "Rejected\n";
      }
      //reset curState, match, and accepted to prepare for the next line
      curState = 0;
      match = false;
      Accepted = false;
    }
  }
  return 0;
}
