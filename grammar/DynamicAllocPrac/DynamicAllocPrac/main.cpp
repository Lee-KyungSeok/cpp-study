//
//  main.cpp
//  DynamicAllocPrac
//
//  Created by Cory on 2018. 8. 28..
//  Copyright © 2018년 Cory. All rights reserved.
//

#include <iostream>

using namespace std;

// int main(int argc, const char * argv[]) {
    /*
     동적할당: 메모리 생성을 원하는 시점에 할 수 있는 기능
     - 메모리 영역중 힙영역에 공간이 할당된다. 힙의 특성상 메모리를 해제하기 전까지는 계속 남아있다.
     - 동적할당을 하고 메모리를 해제하지 않으면 사용하지는 않지만 공간은 계속 잡혀있게 된다.
     - 해당 공간은 다른곳에 사용이 불가능하다.
     - 메모리 릭 현상에 주의해야 한다.
     
     동적할당은 new 키워드를 이용해서 할 수 있다.
     C 언어에서는 malloc() 함수를 이용해서 할 수 있다.
     
     new 할당할타입; 으로 처리한다.
     
     new나 malloc 둘 다 마찬가지로 힙영역에 메모리 공간을 할당하고 해당 메모리의 주소를 반환해준다.
     
     delete 키워드를 이용해서 동적할당한 메모리를 해제할 수 있다. (delete 뒤에 메모리 주소를 넣어준다.)
     */

/*
    // 아래는 new 뒤에 들어오는 타입인 int 의 크기만큼 공간을 할당한다.(4바이트)
    // 그 뒤 할당한 공간의 메모리 주소를 pNumber 에 넣어준다.
    int* pNumber = new int;
    // 값을 대입
    *pNumber = 100;
    // 메모리 해제
    delete pNumber;
  */
    /*
     동적배열 할당방법: new 타입[갯수]; 의 형태로 사용 가능
     */
    /*
    // 아래처럼 동적 배열로 할당하면 메모리 공간에 400 바이트 만큼 공간을 할당하고 해당 메모리의 시작 주소를 반환한다.
    int* pArray = new int[100];
    // 배열에 값을 넣을 수 있다.
    pArray[1] = 300;
    // 동적배열을 지울 때는 배열을 지움을 표시해주어야 한다.
    delete[] pArray;
    */
    
//    return 0;
// }
