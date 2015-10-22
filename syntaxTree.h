#ifndef SYNTAXTREE_H_INCLUDED
#define SYNTAXTREE_H_INCLUDED

#include "stdafx.h"
#include "term.h"
#include "production.h"
#include "clUtils.h"

class Term;
class Token;
class syntaxNode;

/*
 * class Token
 * description: �ʷ�����������Ĵ�
 * data:    ��Ӧ���﷨�Ĵ�Term��ӵ�е��ۺ�����lexData
 * method:  print(����﷨�Ĵʺ��ۺ�����;��ѡ����)
 */
class Token {
public:
    Term* ptrTerm;
    string lexData;
    Token(Term* _ptr, const string& _str): ptrTerm(_ptr), lexData(_str) {}
    void print(bool breakLine = true) const;
};

class syntaxNode {
public:
    Token* ptrToken; ///���﷨�ڵ��Ӧ�������
    Production* ptrPdt; ///��Ҷ�ӽڵ���õĹ�Լ����ʽ
    syntaxNode* ptrParent; ///���ڵ�
    deque<syntaxNode*> child; ///���ӽڵ�
    D1Map<string,void*> hashData; ///�洢������������
    syntaxNode(Token* _ptr, Production* _pdt = NULL) : ptrToken(_ptr), ptrPdt(_pdt), ptrParent(NULL) {}
    ~syntaxNode();
    ///��ö�Ӧ����ʵľ����ı�
    string getLex() const;
    ///�ݹ�����﷨����dep = 0���ʾ���ڵ�, hasNext���ڷ�֧�ߵĻ���
    void print(bool breakLine = true, int dep = 0, bool hasNext = false) const;
};


#endif // SYNTAXTREE_H_INCLUDED
