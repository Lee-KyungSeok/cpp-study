//
// Created by Cory on 2018. 9. 2..
//
#include <iostream>
#pragma once

template <typename T>
class CListNode {
// 생성자와 소멸자를 private 하게 되면 외부에서 객체를 생성하고 객체를 해제할 수 없다.
// 생성자는 객체를 생성할 때 자동으로 호출되는 함수인데 private 이게 되면 객체를 생성하면서 호출시 접근이 불가능 하다.
private:
    CListNode():
        m_pNext(NULL),
        m_pPrev(NULL) {

    }
    ~CListNode() {

    }

private:
    // friend: 친구로 만들어 준다.
    //         friend 로 지정해준 클래스에서 이 클래스의 private 이나 protected 에 접근이 가능해진다.
    //         만약 friend 클래스가 template 클래스인 경우 이를 지정해 주어야 한다.
    template <typename T1>
    friend class CLinkedList;
    template <typename T1>
    friend class CListIterator;
    template <typename T1>
    friend class CListReverseIterator;

private:
    T m_Data;
    CListNode<T>* m_pNext;
    CListNode<T>* m_pPrev;
};

// 반복자 클래스: 리스트 노드를 반복해서 순회할 수 있는 기능을 제공하는 클래스
template <typename T>
class CListIterator {

public:
    CListIterator() {

    }
    ~CListIterator() {

    }

private:
    template <typename T1>
    friend class CLinkedList;

private:
    typedef CListNode<T> NODE;
    typedef CListNode<T>* PNODE;

private:
    PNODE m_pNode;

public:
    bool operator == (const CListIterator<T>& iter) {
        return m_pNode == iter.m_pNode;
    }

    bool operator != (const CListIterator<T>& iter) {
        return m_pNode != iter.m_pNode;
    }

    void operator ++ () {
        m_pNode = m_pNode->m_pNext;
    }

    void operator -- () {
        m_pNode = m_pNode->m_pPrev;
    }

    T operator *() {
        return m_pNode->m_Data;
    }
};

// reverse 반복자
template <typename T>
class CListReverseIterator {

public:
    CListReverseIterator() {

    }
    ~CListReverseIterator() {

    }

private:
    template <typename T1>
    friend class CLinkedList;

private:
    typedef CListNode<T> NODE;
    typedef CListNode<T> PNODE;

private:
    PNODE m_pNode;

public:
    bool operator == (const CListReverseIterator<T>& iter) {
         return m_pNode == iter.m_pNode;
    }

    bool operator != (const CListReverseIterator<T>& iter) {
        return m_pNode != iter.m_pNode;
    }

    void operator ++ () {
        m_pNode = m_pNode.m_pPrev;
    }

    void operator -- () {
        m_pNode = m_pNode.m_pNext;
    }

    T operator * () {
        return m_pNode.m_Data;
    }
};

template <typename T>
class CLinkedList {
public:
    CLinkedList() {
        m_pBegin = new NODE;
        m_pEnd = new NODE;

        m_pBegin->m_pNext = m_pEnd;
        m_pEnd->m_pPrev = m_pBegin;

        m_iSize = 0;
    }
    ~CLinkedList() {
        clear();
        delete m_pBegin;
        delete m_pEnd;
    }

    // inner class 이다 => 클래스 안에 클래스!
private:
    typedef CListNode<T> NODE;
    typedef CListNode<T>* PNODE;

public:
    typedef CListIterator<T> iterator;
    typedef CListReverseIterator<T> reverseIterator;

private:
    PNODE m_pBegin;
    PNODE m_pEnd;
    unsigned int m_iSize;

public:
    // 레퍼런스는 참조하는 대상의 값을 변경할 수 있다. 하지만 const 를 붙이면 참조하는 대상 값을 변경할 수 없다.
    void push_back(const T& data) {
        PNODE pNode = new NODE;
        pNode->m_Data = data;
        // end 의 이전노드가 가장 마지막 노드
        PNODE pPrev = m_pEnd->m_pNext;

        // 연결해준다.
        pNode->m_pPrev = pPrev;
        pNode->m_pNext = m_pEnd;
        pPrev->m_pNext = pNode;
        m_pEnd->m_pPrev = pNode;

        m_iSize++;
    }

    void push_front(const T& data) {
        PNODE pNode = new NODE;
        pNode->m_Data = data;
        // begin 의 다음 노드가 가장 첫번째 노드
        PNODE pNext = m_pBegin->m_pNext;

        pNode->m_pPrev = m_pBegin;
        pNode->m_pNext = pNext;
        pNext->m_pPrev = pNode;
        m_pBegin->m_pNext = pNode;

        m_iSize++;
    }

    // 멤버함수 뒤에 const 를 붙여주면 이 함수 내에서 멤버변수의 값을 변경할 수 없다.
    unsigned int size() const {
        return m_iSize;
    }

    bool empty() const {
        return m_iSize == 0;
    }

    void clear() {
        PNODE pNode = m_pBegin->m_pNext;

        while(pNode != m_pEnd) {
            PNODE pNext = pNode->m_pNext;
            delete pNode;
            pNode = pNext;
        }

        m_pBegin->m_pNext = m_pEnd;
        m_pEnd->m_pPrev = m_pBegin;
        m_iSize=0;
    }

    iterator begin() {
        iterator iter;
        iter.m_pNode = m_pBegin->m_pNext;
        return iter;
    }

    iterator end() {
        iterator iter;
        iter.m_pNode = m_pEnd;
        return iter;
    }

    reverseIterator rBegin() {
        reverseIterator iter;
        iter.m_pNode = m_pEnd->m_pPrev;
        return iter;
    }

    reverseIterator rEnd() {
        reverseIterator iter;
        iter.m_pNode = m_pBegin;
        return iter;
    }
};