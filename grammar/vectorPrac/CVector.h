#pragma once

#include <iostream>

// vector 노드 클래
template <typename T>
class CVectorNode {

private:
    CVectorNode() {

    }
    ~CVectorNode() {

    }

private:
    template <typename T1>
    friend class CVector;

private:
    T m_Data;
    int m_iIndex;
};

// vector 클래스
template <typename T>
class CVector {

public:
    CVector() {
        m_iSize = 0;
        m_iCapacity = 2;

        m_pArray = new NODE[m_iCapacity + 2]; // 이전/이후 노드를 포함해서 2를 더해
    }

    // size 를 받아서 초기화 시킬수도 있다.
    CVector(unsigned int iSize) {
        m_pArray = new NODE[iSize + 2];
        m_iCapacity = iSize;
        m_iSize = 0;
    }

    ~CVector() {
        delete[] m_pArray;
    }

private:
    typedef CVectorNode<T> NODE;
    typedef CVectorNode<T>* PNODE;

private:
    PNODE m_pArray;
    unsigned int m_iSize;
    unsigned int m_iCapacity;

public:
    void push_back(const T& data) {
        if(full())
            resize(m_iSize * 2);

        // 0번 인덱스는 begin 이지만, 실제 1번 인덱스부터 노드가 추가되므로
        // 처음 추가된 노드는 0번부터 인덱스를 준다.
        m_pArray[m_iSize + 1].m_Data = data;
        m_pArray[m_iSize + 1].m_iIndex = m_iSize;
        m_iSize++;

    }

    void resize(unsigned int iSize) {
        // begin 과 end 를 포함시키기 위해 2를 더해줌
        PNODE pArray = new NODE[iSize +2];

        // 위에서 2배만큼 공간을 새로 할당하고 기본에 있는 노드의 데이터를 새로 할당한 공간에 복사해준다.
        // 1번 인덱스부터 시작하기 때문에 여기서 부터 복사하기 위해 1을 더함
        //   - 1번인자: 새로 만든 포인터
        //   - 2번인자: 복사할 포인터
        //   - 3번인자: 크기
        memcpy(pArray + 1, m_pArray + 1 ,sizeof(NODE) * m_iSize);

        // 기존 노드를 삭제
        delete[] m_pArray;

        // 새로 만든 노드를 기본 노드로 설정
        m_pArray = pArray;
        // capacity 를 변경
        m_iCapacity = iSize;
    }

    void clear() {
        delete[] m_pArray;
        m_iSize = 0;
        m_iCapacity =2;
        m_pArray = new NODE[m_iCapacity + 2];
    }

    bool full() {
        return m_iSize == m_iCapacity;
    }

    bool empty() {
        return m_iSize == 0;
    }

    unsigned int size() const {
        return m_iSize;
    }

    unsigned int capacity() const {
        return m_iCapacity;
    }

    // vector[1] 과 같이 나타내려면 연산자를 재정의 해주어야 한다.
    // 실제로 이 클래스에서 idx 를 1부터 시작시켰으므로 1을 더한값을 리턴한다.
    T operator [](int idx) {
        return m_pArray[idx+1].m_Data;
    }

    // size 에 맞게 vector를 초기화
    void reserve(unsigned int iSize) {
        delete[] m_pArray;
        m_pArray = new NODE[iSize + 2];

        m_iCapacity = iSize;
        m_iSize = 0;
    }

};