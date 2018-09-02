#include <iostream>

#pragma once

template <typename T>
class CStackNode {

private:
    CStackNode():
        m_pNext(NULL) {

    }
    ~CStackNode() {

    }

private:
    template <typename T1>
    friend class CStack;

private:
    T m_Data;
    CStackNode<T>* m_pNext;
};

template <typename T>
class CStack {

public:
    CStack() {
        m_pBegin = new NODE;
        m_pEnd = new NODE;

        m_pBegin->m_pNext = m_pEnd;

        m_iSize = 0;
    }
    ~CStack() {
        PNODE pNode = m_pBegin;

        while(pNode != m_pEnd) {
            PNODE pNext = pNode->m_pNext;
            delete pNode;
            pNode = pNext;
        }

        m_iSize = 0;
    }

private:
    typedef CStackNode<T> NODE;
    typedef CStackNode<T>* PNODE;

private:
    PNODE m_pBegin;
    PNODE m_pEnd;
    unsigned int m_iSize;

public:
    void push(const T& data) {
        PNODE pNode = new NODE;
        pNode->m_Data = data;

        // begin 의 다음은 방금 들어간 노드
        // 만든 노드의 다음은 바로 직전에 들어간 노드로 설정한다.
        PNODE  pNext = m_pBegin->m_pNext;
        m_pBegin->m_pNext = pNode;
        pNode->m_pNext = pNext;

        m_iSize++;
    }

    T pop() {
        if(empty())
            return 0;

        // 뺄 노드는 begin 의 다음노드로 가장 마지막에 들어간 노드
        PNODE pNode = m_pBegin->m_pNext;
        PNODE pNext = pNode->m_pNext;
        T data = pNode->m_Data;

        // 노드를 지우고 그 다음 노드를 가장 처음의 노드로 설정한다.
        delete pNode;
        m_pBegin->m_pNext = pNext;

        m_iSize--;

        return data;

    }

    T top() {
        if(empty())
            return 0;

        return m_pBegin->m_pNext.m_Data;
    }

    bool empty() {
        return m_iSize == 0;
    }
};