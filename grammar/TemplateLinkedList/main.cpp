
#include "LinkedList.h"

using namespace std;

int main() {

    CLinkedList<int> listInt;
    CLinkedList<float> listFloat;


    for(int i=0; i<100; i++) {
        listInt.push_back(i+1);
    }

    cout << listInt.size() << endl;

    // inner class 선언은 아래와 같이 한다.
    CLinkedList<int>::iterator iter;
//    CListIterator<int> iter1; // 위는 이와 같다.

    for(iter = listInt.begin(); iter != listInt.end(); ++iter) {
        cout << *iter << endl;
    }


    cout << "===== reverse Iterator =====" << endl;
    CLinkedList<int>::reverseIterator rIter;
    for(rIter = listInt.rBegin(); rIter != listInt.rEnd(); ++rIter) {
        cout << *rIter << endl;
    }


    return 0;
}