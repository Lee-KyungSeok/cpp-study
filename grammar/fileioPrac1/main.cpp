#include <iostream>

using namespace std;

//pp 는 main 함수 안에 있는 int* 타입의 p변수의 주소를 가지게 된다.
void Test(int** pp) {
    *pp = new int; // 4바이트 메모리 할당
}

int main(int argc, const char * argv[]) {

//    int* p = NULL;
//    Test(&p); // 결국 이는 p=new int 와 동일

    FILE* pFile = NULL;

#if 0
    //========== 파일 쓰기 ==========
    // fopen_s 의 경우
    // 1번인자: 파일의 이중포인터이다.
    // 2번인자: 파일 경로, 파일 생성 기준 경로는 현재 프로젝트가 있는 폴더 기준 (but> exe 파일인 경우 이 파일이 있는 경로를 기준으로 생성)
    // 3번인자: 읽기(r), 쓰기(w), 접근(a) / 파일형태(텍스트파일(t), 바이너리파일(b)) 로 2가지 모드가 있어서 합쳐서 사용한다.

    // 하지만... visual studio 가 아니므로 fopen 을 사용함
    pFile = fopen("sample.txt", "wt");
    if(pFile != NULL) {

        //fwrite, fread, fputs, fgets 함수 제공
        char* pText = (char*)"abcd";
        // 1번인자: 저장하고자 하는 값의 메모리 주소를 넣어준다.
        // 2번인자: 저장하고자 하는 값의 변수타입의 메모리 크기를 넣어준다.
        // 3번인자: 배열의 갯수를 넣어준다.
        // 4번인자: 저장할 파일의 스트림을 넣어준다.
        fwrite(pText, 1, 4, pFile);

        fclose(pFile); // 반드시 닫아주어야 한다.

        cout << "파일 저장 완료" << endl;
    }
#elif 1
    // ========== 파일 읽기 ==========
    pFile = fopen("sample.txt", "rt");
    if(pFile != NULL) {

        char strText[5] = {};

        fread(strText, 1, 4, pFile);
        cout << strText << endl;

        fclose(pFile);
    }

#endif

    return 0;
}