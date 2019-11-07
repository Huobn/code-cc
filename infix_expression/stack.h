#ifndef __STACK__
#define __STACK__

#define POP_EXCEPTION 211

/**
*Stack data node template class
*@author : Bingnan Huo
*@version : 1.0.0
*/

template<class T> class Node{

private:
    T data; // data field
    Node<T> *next; // next node's reference
public:
    Node(){
        // initialize node reference to NULL
        next = NULL;
    }

    Node(const T& val, const Node<T> *refe){
        data = val;
        next = refe;
    }

    Node(const T& val){
        data = val;
        next = NULL;
    }
    ~Node(){}

    void setData(const T& val){
        data = val;
    }

    T& getData(){
        return data;
    }

    void setNext(Node<T> *refe){
        next = refe;
    }

    Node<T>* getNext(){
        return next;
    }

};
/**
* Linked stack defined
* @author : Bingnan Huo
* @version : 1.0.0
*/
template<class T> class Stack{

private:
    Node<T> *top;
    int length;

    // finalize function
    void destory(){
        Node<T> *p;
        while( top ){
            p = top->getNext();
            delete top;
            top = p;
        }
    }

public:
    Stack():top(NULL), length(0){}

    ~Stack(){
        destory();
    }

    void push(const T& val){
        // create a new node to storage data
        Node<T> *node = new Node<T>(val);

        if( !top ) top = node;
        else{
            node->setNext(top);
            top = node;
        }
        length++;
    }

    T& pop(){
        // validity check
        if( top && length ){
            T ret = top->getData();
            Node<T> *garbage = top;
            top = top->getNext();
            delete garbage;
            return ret;
        }else{
            throw POP_EXCEPTION;
        }
    }

    T& getTopValue(){
        if( top &&  length ){
            return top->getData();
        }else{
            throw POP_EXCEPTION;
        }
    }

    bool isEmpty(){
        return length == 0;
    }

    int getSize(){
        return length;
    }

    void clean(){
        destory();
    }

};

#endif // __STACK__
