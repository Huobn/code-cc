#ifndef __QUEUE__
#define __QUEUE__
#define EMPTY_EXCEPTION 211


template<class T> class DualTrackNode{

private:
    DualTrackNode<T> *precursor; //precursor node's reference
    DualTrackNode<T> *next; // next node's reference
    T data; // data field
public:
    DualTrackNode(){
        // initialize the reference
        precursor = NULL;
        next = NULL;
    }

    DualTrackNode(const T& val){
        // initialize the reference
        precursor = NULL;
        next = NULL;
        data = val;
    }

    virtual ~DualTrackNode(){}

    void setData(const T& val){
        data = val;
    }

    T& getData(){
        return data;
    }

    void setNext(DualTrackNode<T> *nxt){
        next = nxt;
    }

    DualTrackNode<T> *getNext(){
        return next;
    }

    void setPrecursor(DualTrackNode<T> *pre){
        precursor = pre;
    }

    DualTrackNode<T> *getPrecursor(){
        return precursor;
    }


};

template<class T> class Queue{

private:

    DualTrackNode<T> *pointer;
    int size;

public:

    Queue(){
        pointer = NULL;
        size = 0;
    }

    ~Queue(){
        DualTrackNode<T> *p;
        for(int i=0; i<size; ++i){
            p = pointer->getNext();
            delete pointer;
            pointer = p;
        }
    }
    T& dequeue(){
       if( pointer && size ){
            T ret = pointer->getData();
            DualTrackNode<T> *p = pointer->getNext();

            pointer->getPrecursor()->setNext(p);
            p->setPrecursor(pointer->getPrecursor());

            delete pointer;

            pointer = p;
            size--;
            return ret;
       }else{
            throw EMPTY_EXCEPTION;
       }
    }

    void enqueue(const T& val){
        DualTrackNode<T> *node = new DualTrackNode<T>(val);
        if( pointer && size ){
            node->setNext(pointer);
            node->setPrecursor(pointer->getPrecursor());

            pointer->getPrecursor()->setNext(node);
            pointer->setPrecursor(node);

        }else{
            pointer = node;
            pointer->setNext(pointer);
            pointer->setPrecursor(pointer);
        }

        size++;
    }

    int getSize(){
        return size;
    }

    bool isEmpty(){
        return size == 0;
    }



};


#endif // __QUEUE__
