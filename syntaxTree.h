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

/*
 * class SyntaxNode
 * description: �﷨���ڵ�
 * data:    ptrToken ���﷨�ڵ��Ӧ�������
 *          ptrPdt ��Ҷ�ӽڵ���õĹ�Լ����ʽ,Ҷ�ӽڵ�ΪNULL
 *          ptrParent ���﷨�ڵ�
 *          child �����﷨�ڵ�, ˫�����
 *          hashData �洢������������( ͨ�����ص��������clUtils�е�PASS��GET ���Լ��ز������ݶ��� )
 *
 * method:  ~syntaxNode deleteʱɾ����������
 *          getLex ���ػ�ȡ������ʵ��ַ���
 *          print ���,��ѡ����,dep = 0���ʾ���ڵ�, hasNext���ڷ�֧�ߵĻ���
 *          operator[ int ] ��ȡ���ӽڵ������, ������ֱ��throw
 *          operator[ string ] ��ȡ��Ӧstring����������, �����ڻᴴ��һ����NULL�����ã������޸�
 */
class syntaxNode {
public:
    Token* ptrToken;
    Production* ptrPdt;
    syntaxNode* ptrParent;
    deque<syntaxNode*> child;
    D1Map<string,void*> hashData;
    syntaxNode(Token* _ptr, Production* _pdt = NULL) : ptrToken(_ptr), ptrPdt(_pdt), ptrParent(NULL) {}
    ~syntaxNode();
    string getLex() const;
    void print(bool breakLine = true, int dep = 0, bool hasNext = false) const;
    void*& operator[](const string& key);
    syntaxNode& operator[](const int pos);
    template<typename _Key, typename _Ele>
    bool add(const _Key& key, const _Ele& ele, bool _replace = false) {
        return hashData.add(key,ele,_replace);
    }
};

#endif // SYNTAXTREE_H_INCLUDED
