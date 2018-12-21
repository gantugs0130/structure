# include <limits.h> 
# include <string.h> 
# include <iostream> 
  
# define char_num 256 
using namespace std;
int max (int a, int b) { return (a > b)? a: b; } 
  
void Shift_Hiih( char *str, int size, int S[char_num]) 
{ 
    
    for (int i = 0; i < char_num; i++) 
         S[i] = -1; 
  
    for (int i = 0; i < size; i++) 
         S[(int) str[i]] = i; 
} 
  
void search( char *t,  char *p) 
{ 
    int m = strlen(p); 
    int n = strlen(t); 
  
    int S[char_num]; 
    Shift_Hiih(p, m, S); 
  
    int s = 0;  
    while(s <= (n - m)) 
    { 
        int j = m-1; 
        while(j >= 0 && p[j] == t[s+j]) 
            j--; 
        if (j < 0) 
        { 
            cout<<s<<" deh indexees ehlej bn"<<endl;
            break;
        } 
  
        else
            s += max(1, j - S[t[s+j]]); 
    } 
} 
int main() 
{ 
    char t[] = "ABABADCABABACA"; 
    char p[] = "ABABACA"; 
    search(t, p); 
    return 0; 
} 