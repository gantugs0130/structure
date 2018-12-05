#include <string>
using namespace std;
class Node{
    public:
    int val;
    string vali;
    Node *next;
    Node(int val, string a){
        this->val=val;
        this->vali=a;
        this->next=NULL;
    }
};
class Table{
    public:
    Node *root;
};
