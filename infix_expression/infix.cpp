#include <cstdio>
#include <cstring>
#include <vector>
#include "stack.h"

#define LEVEL 6

using namespace std;

int pn[LEVEL][LEVEL] = {{}};
int getOperatorIndex(const char symbol);

class OperatorStrategy{

public:
    virtual ~OperatorStrategy(){};

    virtual void run(Stack<float> *num)=0;
};

class AddStrategy
    :public OperatorStrategy{

public:
    void run(Stack<float> *num){
        float n2 = num->pop();
        float n1 = num->pop();
        num->push(n1 + n2);
    }

};

class SubtractStrategy
    :public OperatorStrategy{

public:
    void run(Stack<float> *num){

        float n2 = num->pop();
        float n1 = num->pop();
        num->push(n1 - n2);
    }

};

class MultiStrategy
    :public OperatorStrategy{

public:
    void run(Stack<float> *num){
        float n2 = num->pop();
        float n1 = num->pop();
        num->push(n1 * n2);
    }
};

class DivideStrategy
    :public OperatorStrategy{

public:
    void run(Stack<float> *num){
        float n2 = num->pop();
        float n1 = num->pop();
        num->push(n1 / n2);
    }

};

class OperatorStrategyFactory{

private:
    vector<OperatorStrategy*> operatorArray;
public:

    OperatorStrategyFactory(){
        operatorArray.push_back(new AddStrategy());
        operatorArray.push_back(new SubtractStrategy());
        operatorArray.push_back(new MultiStrategy());
        operatorArray.push_back(new DivideStrategy());
    }

    OperatorStrategy* getStrategy(char symbol){
        int index = getOperatorIndex(symbol);
        return operatorArray[index];
    }

};


inline
char* _readFormatter(int level){

    int len = 3 * level;

    char* s = new char [ len ];

    for(int i=0; i<len-3 ; i+=3){
        s[i] = '%';
        s[i+1] = 'd';
        s[i+2] = ',';
    }
    s[len-3] = '%';
    s[len-2] = 'd';
    s[len-1] = '\0';
    return s;

}

inline
int initializeOperatorPriority(int pnArray[LEVEL][LEVEL], const char* fileName){

    FILE *fp = NULL;

    fp = fopen(fileName, "r");

    if( !fp ){
        return 1;
    }

    for(int i=0; i<LEVEL; ++i){
        for(int j=0; j<LEVEL; ++j){
            if( j != LEVEL-1 ){
                fscanf(fp, "%d,", &pnArray[i][j]);
            }else{
                fscanf(fp, "%d", &pnArray[i][j]);
            }
        }
    }
    fclose(fp);

}

inline
int getOperatorIndex( const char symbol ){
    int flag = -1;

    switch( symbol ){
        case '+': flag = 0; break;
        case '-': flag = 1; break;
        case '*': flag = 2; break;
        case '/': flag = 3; break;
        case '(': flag = 4; break;
        case ')': flag = 5; break;
        default: break;
    }

    return flag;
}

inline
int readNumber( char* expression, int index, Stack<float>* number ){

    int n = expression[index] - '0';
    int s = index;
    index++;
    while( expression[index] >= '0' && expression[index] <= '9' ){

        n += (n * 10 + expression[index] - '0');
        index++;
    }
    number->push(n);
    return index - s;
}

inline
int getAction(int t, int n){
    return pn[t][n];
}

inline
bool isOperator(char symbol){

    bool ret = true;
    switch( symbol ){

    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        break;
    default:
        ret = false;
        break;
    }
    return ret;

}

int main(int argc, char* argv[]){

    char *exp = "2+3*2/2+1";
    int len = strlen(exp);
    int i = 0;

    initializeOperatorPriority(pn, "op.txt");
    Stack<char> *OPERATOR = new Stack<char>();
    Stack<float> *NUMBER = new Stack<float>();

    //add a endpoint for our expression
    char *expression = new char [ len + 2 ];
    strcpy(expression, exp);
    expression[ len ] = ')';
    expression[ len + 1] = '\0';

    char symbol;
    OperatorStrategyFactory *factory = new OperatorStrategyFactory();
    // push a guard symbol into the stack
    OPERATOR->push('(');

    while( (symbol = expression[i]) ){

        if( symbol >= '0' && symbol <= '9' ){
            i += readNumber(expression, i,NUMBER);
            continue;
        }else if ( isOperator(symbol) ){
            char stackTopSymbol = OPERATOR->getTopValue();
            // get those symbol's index that at priority table
            int t = getOperatorIndex(stackTopSymbol);
            int n = getOperatorIndex(symbol);

            int action = getAction(t, n);
            if( action == 0 ){
                char st = OPERATOR->pop();
                OperatorStrategy* op = factory->getStrategy(st);
                if( op ){
                    op->run(NUMBER);
                    continue;
                }else{
                    printf("invalid expression\n");
                    break;
                }
            }else if( action == 1 ){
                OPERATOR->push(symbol);
                i++;
                continue;
            }else if( action == 2 ){
                OPERATOR->pop();
                i++;
                continue;
            }else if( action == -1 ){
                printf("invalid expression\n");
                break;
            }

        }else{
            i++;
        }
    }

    printf("result = %f\n", NUMBER->pop());
    printf("isEmpty = %d\n", NUMBER->isEmpty());
    return 0;
}



