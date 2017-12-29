#pragma once
#include "../AbstractSyntaxTree/AbstrSynTree.h"
#include"TypeTable.h"
#include "../Parser/ActionsAndRules.h"
#include <iostream>
#include <functional>

//-----------------------Type Table Test Stub

#ifdef TEST_TYPETABLE
#define TEST_TYPETABLE
int main()
{
	CodeAnalysis::ASTNode* pNode=new CodeAnalysis::ASTNode();
	CodeAnalysis::ASTNode* aNode = new CodeAnalysis::ASTNode();
	CodeAnalysis::ASTNode* bNode = new CodeAnalysis::ASTNode();

	pNode->name_ = "Name1";
	pNode->package_ = "Package1";
	pNode->type_ = "Type1";

	aNode->name_ = "Name2";
	aNode->package_ = "Package2";
	aNode->type_ = "Type2";

	bNode->name_ = "Name3";
	bNode->package_ = "Package3";
	bNode->type_ = "Type3";

	TypeTable tt;
	tt.insertintable(pNode);
	tt.insertintable(aNode);
	tt.insertintable(bNode);
	tt.display();
}

#endif // TEST_TYPETABLE