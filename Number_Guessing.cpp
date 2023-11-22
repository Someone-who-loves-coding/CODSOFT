#include <iostream>

using namespace std;

int main() {
    int random = rand() % 100 ;
    int in;
    cout<<"Welcome to the Number Guessing Game!!!";
    cout<<"\n\n\n Your Guess? : ";
    cin >> in ;
    while(in!=random){
        if(in<random){
            cout<<"\nToo Low TT Try Again ;) : ";
            cin >> in ;
        }
        if(in>random){
            cout<<"\nToo High TT Try Again ;) : ";
            cin >> in ;
        }
    }
    cout<<"\nYou Guessed it Right! : The Number indeed was "<<in<<".";

    return 0;
}