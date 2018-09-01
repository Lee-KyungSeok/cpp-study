#include <iostream>

using namespace std;

#define NAME_SIZE 32
#define STUDENT_MAX 3

typedef struct _tagStudent {
    char strName[NAME_SIZE];
    int iNumber;
    int iKor;
    int iEng;
    int iMath;
    int iTotal;
    float fAvg;
}STUDENT, *PSTUDENT;

int main() {

#if 0 // 학생 저장
    STUDENT tStudent[STUDENT_MAX] = {};

    for(int i=0; i< STUDENT_MAX; i++) {
        cout << "이름: ";
        cin >> tStudent[i].strName; // 일단 그냥 띄어쓰기 없이 받음
        tStudent[i].iNumber = i + 1;

        cout << "국어: ";
        cin >> tStudent[i].iKor;

        cout << "영어: ";
        cin >> tStudent[i].iEng;

        cout << "수학: ";
        cin >> tStudent[i].iMath;

        tStudent[i].iTotal = tStudent[i].iKor + tStudent[i].iEng + tStudent[i].iMath;
        tStudent[i].fAvg = tStudent[i].iTotal / 3.f;
    }

    // 학생 정보를 파일에 저장한다.
    int iStudentCount = STUDENT_MAX;
    FILE* pFile = NULL;

    pFile = fopen("student.std", "wb");

    if(pFile != NULL) {
        // 학생 수를 저장한다.
        fwrite(&iStudentCount, 4, 1, pFile);

        for(int i=0; i<iStudentCount; i++) {
            // 학생 구조체를 통으로 저장한다.
            fwrite(&tStudent[i], sizeof(STUDENT), 1, pFile);
        }

        fclose(pFile);
    }
#elif 1 // 학생 읽기
    STUDENT tStudent[STUDENT_MAX] = {};
    FILE* pFile = NULL;
    pFile = fopen("student.std", "rb");

    int iStudentCount = 0;

    if(pFile != NULL) {

        // 먼저 count 를 읽어옴
        fread(&iStudentCount, 4, 1, pFile);

        for(int i=0; i<iStudentCount; i++) {
            fread(&tStudent[i], sizeof(STUDENT), 1, pFile);
        }

        fclose(pFile);
    }

    // 읽어온 학생을 출력
    for(int i=0; i<iStudentCount; i++) {
        cout << "이름: " << tStudent[i].strName << endl;
        cout << "국어: " << tStudent[i].iKor << "\t";
        cout << "영어: " << tStudent[i].iEng << "\t";
        cout << "수학: " << tStudent[i].iMath << endl;
        cout << "총점: " << tStudent[i].iTotal << "\t";
        cout << "평균: " << tStudent[i].fAvg << endl << endl;
    }

#endif

    return 0;
}