#include<iostream>
#include<string>
using namespace std;
int ecount=0;
string ner[100];
int ncount=0;
class node{
    public:
    string name;
    node *next;
    node(string a){
        this->name=a;
        this->next=NULL;
    }
};
class element{
    public:
    node *root;
};
element e[100];
void insert_e(string a){
    int count=0;
    for(int i=0; i<ecount; i++){
        if(e[i].root->name==a){
            count++;
        }
    }
    if(count==0){
        node *temp = new node(a);
        e[ecount].root=temp;
        ecount++;
    }
    
}
void insert_l(string a1, string a2){
    int ss=0;
    for(int i=0; i<ncount; i++){
        if(e[i].root->name==a1){
            ss++;
        }
        if(e[i].root->name==a2){
            ss++;
        }
    }
    if(ss==2){
    int i = 0;
    while(e[i].root->name!=a1){
        if(i>=ecount){
            return;
        }
        i++;
    }
    node *temp = e[i].root;
    while(temp->next!=NULL){
        if(temp->name==a2){
            return;
        }
        temp = temp->next;
    }
    temp->next = new node(a2);
    i = 0;
    while(e[i].root->name!=a2){
        if(i>=ecount){
            return;
        }
        i++;
    }
    node *temp1 = e[i].root;
    while(temp1->next!=NULL){
        if(temp1->name==a1){
            return;
        }
        temp1 = temp1 -> next;
    }
    temp1->next = new node(a1);
    }
}
void delete_l(string a1, string a2){
    int i = 0;
    while(e[i].root->name!=a1){
        if(i>=ecount){
            return;
        }
        i++;
    }
        node *temp1 = e[i].root;
    while(temp1!=NULL){
        if(temp1->next->name==a2){
            node *x1 =temp1->next->next;
            delete temp1->next;
            temp1->next = x1;
            break;
        }
        temp1 = temp1->next;
    }
    i = 0;
    while(e[i].root->name!=a2){
        if(i>=ecount){
            return;
        }
        i++;
    }
        node *temp = e[i].root;
    while(temp!=NULL){
        if(temp->next->name==a1){
            node *x2 =temp->next->next;
            delete temp->next;
            temp->next = x2;
            return;
        }
        temp = temp->next;
    }
}
void delete_e(string a){
    int i = 0;
    while(e[i].root->name!=a){
        if(i>=ecount){
            return;
        }
        i++;
    }
    node *temp = e[i].root->next;
    while(temp != NULL){
        delete_l(temp->name, a);
        temp = temp ->next;
    }
    for(int j = i; j<ecount-1; j++){
        e[j].root->name = e[j+1].root->name;
        e[j].root->next = e[j+1].root->next;
    }
    e[ecount-1].root->name=" ";
    e[ecount-1].root->next=NULL;
    ecount--;
}

bool search(string a1, string a2){
    
    ner[ncount]=a1;
    ncount++;
    if(a1==a2){
        return true;
    }
    else{
    int i = -1;
    for(int j=0; j<ecount; j++){
        if(e[j].root->name==a1){
            i = j;
        }
    }
    if(i==-1){
        return false;
    }
    else{
        node *temp = e[i].root->next;
        while(temp!=NULL){
            if(temp->name == a2){
                return true;
            }
            temp  = temp -> next;
        }
        temp = e[i].root->next;
        while(temp != NULL){     
            int cor=0;
            for(int j=0; j<ncount; j++){
                if(ner[j]==temp->name){
                    cor++;
                }
            }
            if(cor == 0){
                if(search(temp->name, a2)){
                    cout<<temp->name<<"..."<<endl;
                    for(int l=0; l<ncount; l++){
                        ner[l]=" ";
                    }
                    ncount = 0;
                return true;
            }
            }           
            else{
               temp = temp->next;
           }    
          }
         return false; 
    }
    }
}
int main(){
    insert_e("a");
    insert_e("aa");
    insert_e("aaa");
    insert_e("aaaa");
    insert_l("a", "aa");
    insert_l("aaa", "aa");
    insert_l("a", "aaaa");
    insert_e("bbb");
    insert_e("bbbb");
    insert_e("b");
    insert_e("bb");
    insert_l("aaa", "bbb");
    insert_l("bb", "b");
    insert_l("aaa", "bb");
    insert_l("aa", "bbbb");
    delete_e("a");
    for(int i=0; i<ecount; i++){
        node *temp = e[i].root;
        while(temp!=NULL){
            cout<<temp->name<<"  ";
            temp = temp->next;
        }
        cout<<endl;
    }
    if(search("aa", "b")){
        cout<< "zam baina"<<endl;
    }
    else{
        cout<<"zam baihgui bn"<<endl;
    }
    if(search("aa", "aaaa")){
        cout<< "zam baina"<<endl;
    }
    else{
        cout<<"zam baihgui bn"<<endl;
    }
}