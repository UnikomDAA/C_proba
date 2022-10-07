#include <iostream>
//#include "windows.h"
using namespace std;
int x = 6 , y = 8; 

void out_symbol(){
  cin >> x >> y; x *=2;
char x1 = x/10 + '0'; char x2 = x%10 +'0';
char y1 = y/10 + '0'; char y2 = y%10 +'0';
char w [] = {033, '[', y1, y2, ';', x1, x2, 'H',  0};
cout << w << "*\e[12;1H";   
}
int main(){
       system("cls");
for(int i = 0 ; i < 10; i++){
    cout << " - - - - - - - - - -\n";
}
cout << "primer " << "pr\e[4;12H" << "*\e[11;1H";
cout << "input X and Y (1-10): "; 
out_symbol();
cout << "try once again: ";
out_symbol();
system ("pause ") ;
 
    return 0;
}