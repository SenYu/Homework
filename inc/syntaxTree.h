#ifndef SYNTAXTREE_H_INCLUDED
#define SYNTAXTREE_H_INCLUDED

#include "stdafx.h"
#include "term.h"
#include "production.h"
#include "clUtils.h"
#include "json/json.h"

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
    int tId;
    Token* ptrToken;
    Production* ptrPdt;
    syntaxNode* ptrParent;
    deque<syntaxNode*> child;
    Json::Value data;
    syntaxNode(Token* _ptr, Production* _pdt = NULL) : ptrToken(_ptr), ptrPdt(_pdt), ptrParent(NULL) {}
    ~syntaxNode();
    string getLex() const;
    void print(bool breakLine = true, int dep = 0, bool hasNext = false) const;
    syntaxNode& operator[](const int pos);
    Json::Value& operator[](const string& key) {
        return data[key];
    }
    const Json::Value& operator[](const string& key) const {
        return data[key];
    }

};

#endif // SYNTAXTREE_H_INCLUDED
