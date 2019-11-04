#include <iostream>
#include <cstring>
#define EMPTY_EXCEPTION 211

using namespace std;

// define linked stack's node
template<class T> class Node{

private:
    T data;
    Node<T> *next;

public:

    Node(){
        next = NULL;
    }

    void setData(const T& d){
        data = d;
    }

    T& getData(){
        return data;
    }

    void setNext(Node<T> *n){
        next = n;
    }

    Node<T>* getNext(){
        return next;
    }

};
// define linked stack
template<class T> class Stack{

private:

    Node<T> *dataFiled;
    int length;

public:

    Stack(){
        dataFiled = NULL;
        length = 0;
    }

    ~Stack(){delete dataFiled;}

    void push(const T& value){
        Node<T> *node = new Node<T>();
        node->setData(value);

        if( !dataFiled ){
            dataFiled = node;
        }
        else{
            node->setNext(dataFiled);
            dataFiled = node;
        }
        length++;
    }

    T& pop(){
        T data;
        if( dataFiled && length ){
            data = dataFiled->getData();
            Node<T> *tmp = dataFiled->getNext();
            delete dataFiled;
            dataFiled = tmp;
            length--;
        }else{
            throw EMPTY_EXCEPTION;
        }
        return data;
    }

    int getSize(){
        return length;
    }

    bool isEmpty(){
        return length == 0;
    }

};

// bracket match function implemented
bool bracketMatch(char* str, int l, int h){
    bool flag = true;
    int len = strlen(str);
    Stack<char> *c = new Stack<char>();

    if(h >= len || l < 0){
        flag = false;
    }else{
        for(int i=l; i<=h; ++i){
            char k = str[i];
            if( k == '(' ){
                c->push(k);
            }else if( k == '[' ){
                c->push(k);
            }else if( k == '{' ){
                c->push(k);
            }else if( k == ')'){
                if( c->isEmpty() || c->pop() !=  '('){
                    flag = false;
                    break;
                }
            }else if( k == ']'){
                if( c->isEmpty() || c->pop() != '['){
                    flag = false;
                    break;
                }
            }else if( k == '}' ){
                if( c->isEmpty() || c->pop() != '{'){
                    flag = false;
                    break;
                }
            }
        }
    }

    if(!c->isEmpty()){
        flag = false;
    }

    return flag;

}

bool bracketMatch(char *str){
    bool flag = true;
    int len = strlen(str);
    Stack<char> *c = new Stack<char>();

    for(int i=0; i<len; ++i){
        char k = str[i];
        if( k == '(' ){
            c->push(k);
        }else if( k == '[' ){
            c->push(k);
        }else if( k == '{' ){
            c->push(k);
        }else if( k == ')'){
            if( c->isEmpty() || c->pop() !=  '('){
                flag = false;
                break;
            }
        }else if( k == ']'){
            if( c->isEmpty() || c->pop() != '['){
                flag = false;
                break;
            }
        }else if( k == '}' ){
            if( c->isEmpty() || c->pop() != '{'){
                flag = false;
                break;
            }
        }
    }

    if(!c->isEmpty()){
        flag = false;
    }

    return flag;
}

int main(int argc, char* argv[]){

    char* cstr = "{{[()]}}";

    bool ret = bracketMatch(cstr);

    if( ret ){
        cout << "success" << endl;
    }else{
        cout << "failure" << endl;
    }

    return 0;
}
