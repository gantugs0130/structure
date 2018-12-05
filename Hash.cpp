#include <math.h>
#include <iostream>
#include "header.h"
#include<string.h>
using namespace std;
Table a[11]; 
int conv(char ch){
    return int(ch);
}
void hashs(string aa, int location){
    int count=aa.length();
    char x[count];
    strcpy(x, aa.c_str());
    int sum=0;
    for(int i=0; i<count; i++){
        sum = sum + conv(x[i]);
    }
    int loc = sum % 11;
    if(a[loc].root==NULL){
        a[loc].root=new Node(location,aa);
    }
    else{
        Node *temp = a[loc].root;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = new Node(location,aa);
    }
}
Node * search(string aa){
    int count=aa.length();
    char x[count];
    strcpy(x, aa.c_str());
    int sum=0;
    for(int i=0; i<count; i++){
        sum = sum + conv(x[i]);
    }
    int loc = sum % 11;
    Node * temp = a[loc].root;
    while(temp!=NULL){
        if(temp->vali == aa){
            return temp;
        }
        else{
            temp = temp->next;
        }
        
    }
    return NULL;
}
int main(){
    string str[]={"abab","baba", "cccc", "ddd","abbc"};
    for(int i=0; i<5; i++){
        hashs(str[i], i);
    }
    for(int i=0; i<11; i++){
        Node *temp=a[i].root;
        cout<<"List "<< i <<" is: ";
        while(temp!=NULL){
            cout<<str[temp->val]<<"  ";
            temp = temp->next;
        }
        cout<<endl;
    }
    if(search("baba")==NULL){
        cout<<"baihgui bn";
    }
    else{
        cout <<"This address is your word address : "<<search("baba")<<endl;
        cout <<"Your array index is : " << search("baba")->val<<endl;
        cout <<"Your word is : " << search("baba")->vali<<endl;
    }
}