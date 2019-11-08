#include <iostream>
#include "queue.h"

using namespace std;

int main(int argc, char* argv[]){

    Queue<int> *q = new Queue<int>();

    for(int i=0; i<10; ++i){

        q->enqueue(i);
    }
    delete q;
    return 0;
}
