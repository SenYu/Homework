#include "syntaxTree.h"

void* syntaxNode::nullHashData = NULL;

void Token::print(bool breakLine) const{
    ptrTerm->print(false);
    cout<<" "<<lexData;
    breakLine && printf("\n");
}

syntaxNode::~syntaxNode() {
    for(auto ptrSNode : child) {
        for(auto item: hashData  ) {
            delete item.second;
        }
        delete ptrSNode;
    }
}
string syntaxNode::getLex() const {
    if ( NULL == ptrToken ) return "";
    return ptrToken->lexData;
}
void syntaxNode::print(bool breakLine, int dep, bool hasNext) const {
    static bool vis[1000];
    if ( 0 == dep ) memset(vis,false,sizeof(vis));
    ///��Ǹò�Ӧ������.
    vis[dep] = true;
    for(int i=0;i<dep-1;i++) printf( vis[i] ? " ��" : "  ");
    ///hasNext��ʾ���ĸ��׵ĺ��ӻ�û��
    if ( dep > 0 ) printf( hasNext ? " ��" : " ��");

    if( 0 == child.size() )
        ptrToken->print(false);
    else
        ptrPdt->ptrTerm->print(false);
    printf("\n");
    int cnt = 0;
    ///������һ�㺢�ӣ����һ��hasNext = false, �����һ��֮ǰ�ѵ�ǰvis[dep]��false
    for(auto ptrSNode : child) {
        if ( cnt == child.size()-1 ) vis[dep] = false;
        ptrSNode->print(false, dep+1, cnt != child.size()-1);
        cnt++;
    }
}

void*& syntaxNode::operator[](const string& key) {
    if ( NULL == hashData.get( key ) )
        hashData.add( key, NULL );
    return *hashData.get(key);
}

syntaxNode& syntaxNode::operator[](const int pos) {
    if ( pos < child.size() )
        return *child[pos];
    else throw "syntaxNode Out of Range";
}
