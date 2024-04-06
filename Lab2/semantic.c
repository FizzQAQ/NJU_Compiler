#include"semantic.h"
#include"Node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned SemanticError=0;
void semantic_anyasis(struct Node* node)
{
	init_hash();
	//printf("1");
	Program(node);
}
void Program(struct Node*node){
	struct Node* child=node->child;
	ExtDefList(child);
};

void ExtDefList(struct Node*node){
	struct Node* child=node->child;
	if(child!=NULL){
	ExtDef(child);
	ExtDefList(child->brother);
	}
	
};
void ExtDef(struct Node*node){
	struct Node* child=node->child;
	struct Node* brother=child->brother;
	Type type=Specifier(child);
	if(!strcmp(brother->name,"ExtDecList\0")){
	ExtDecList(brother,type);
	}
	else if(!strcmp(brother->name,"FunDec\0")){
	FunDec(brother,type);
	CompSt(brother->brother,type);
	}
	
	

};
void ExtDecList(struct Node*node,Type type){
	struct Node* child=node->child;
	struct Node* brother=child->brother;
	if(brother==NULL){
	VarDec(child,type,NULL);
	}
	else{
	VarDec(child,type,NULL);
	struct Node* brother2=brother->brother;
	ExtDecList(brother2,type);
	}
	
};
Type Specifier(struct Node*node){
	struct Node* child=node->child;
	Type type=(Type)malloc(sizeof(struct Type_));
	if(!strcmp(child->name,"TYPE\0"))
	{
		if(child->is_type==1)
		{
			type->kind=BASIC;
			type->u.basic=INT;
		}
		if(child->is_type==2)
		{
			type->kind=BASIC;
			type->u.basic=FLOAT;
		}
	}
	else{
		StructSpecifier(child,type);
	}
	return type;
};
void StructSpecifier(struct Node*node,Type type){
	struct Node* child=node->child;
	struct Node* brother=child->brother;
	type->kind=STRUCTURE;
	if(!strcmp(brother->name,"OptTag\0"))
	{
		struct Node* brother1=child->brother;
		struct Node* brother2=brother1->brother->brother;
		FieldList field=(FieldList)malloc(sizeof(struct FieldList_));
		field->tail=NULL;
		field->type=(Type)malloc(sizeof(struct Type_));
		field->type->kind=STRUCTTAG;
		field->type->u.structmember=NULL;
		field->name=OptTag(brother);
		DefList(brother2,field);
		insert_hash(field);
		type->u.structure=field;
	}
	else{
		FieldList field=lookup_hash(Tag(brother));
		type->u.structure=field;
	}

};
char* OptTag(struct Node*node)
{
	struct Node*child=node->child;
	char*name=(char*)malloc(sizeof(char)*32);
	if(child!=NULL)
	{
		strcpy(name,child->TYPE_ID);
		return name;
	}
	else{
		return NULL;
	}

	
};
char* Tag(struct Node*node)
{
	struct Node* child=node->child;
	char*name=(char*)malloc(sizeof(char)*32);
	strcpy(name,child->TYPE_ID);
	return name;
	
};
FieldList VarDec(struct Node*node,Type type,FieldList field){
	struct Node*child=node->child;
	FieldList VarField=NULL;
	
	if(!strcmp(child->name,"ID\0"))
	{
		VarField=(FieldList)malloc(sizeof(struct FieldList_));
		VarField->name=(char*)malloc(sizeof(char)*32);
		strcpy(VarField->name,child->TYPE_ID);
		//printf("VarField:%s\n",VarField->name);
		VarField->type=type;
		VarField->tail=NULL;
		if(field==NULL)
			insert_hash(VarField);
		else if(field!=NULL&&field->type->kind!=STRUCTTAG)
			{
				insert_hash(VarField);
			}
	}
	else 
	{
		Type array=(Type)malloc(sizeof(struct Type_));
		array->kind=ARRAY;
		int num=child->brother->brother->TYPE_INT;
		array->u.array.size=num;
		array->u.array.elem=type;
		return VarDec(child,array,field);

	}
	return VarField;
	

	

};
void FunDec(struct Node*node,Type type){
	struct Node* child=node->child;
	FieldList field=(FieldList)malloc(sizeof(struct FieldList_));
	field->type=(Type)malloc(sizeof(struct Type_));
	field->type->kind=FUNCTION;
	field->name=(char*)malloc(sizeof(char)*32);
	field->type->u.func.ret=type;
	field->type->u.func.argc=0;
	field->type->u.func.argv=NULL;
	struct Node*brother=child->brother->brother;
	strcpy(field->name,child->TYPE_ID);
	if(!strcmp(brother->name,"VarList\0")){
	VarList(brother,field);
	}
	insert_hash(field);
};
void VarList(struct Node*node,FieldList field){
	struct Node* child=node->child;
	struct Node*brother=child->brother;
	if(brother!=NULL){
	FieldList argv=ParamDec(child,field);
	AddFuncArgv(field,argv);
	struct Node*brother1=brother->brother;
	VarList(brother1,field);
	}
	else{
	FieldList argv=ParamDec(child,field);
	AddFuncArgv(field,argv);
	}

};
FieldList ParamDec(struct Node*node,FieldList field){
	Type type=Specifier(node->child);
	if(field->type->kind==FUNCTION);
	return VarDec(node->child->brother,type,field);	
};
void CompSt(struct Node*node,Type type){
	struct Node* child=node->child;
	struct Node*brother=child->brother;
	struct Node*brother1=brother->brother;
	DefList(brother,NULL);
	StmtList(brother1,type);

};
void StmtList(struct Node*node,Type type){
	struct Node* child=node->child;
	if(child!=NULL)
	{
		struct Node* brother=child->brother;
		Stmt(child,type);
		StmtList(brother,type);
	}

};
void Stmt(struct Node*node,Type type){
	struct Node* child=node->child;
	if(!strcmp(child->name,"Exp\0"))
	{
		Exp(child);
	}
	else if(!strcmp(child->name,"RETURN\0"))
	{
		struct Node* brother=child->brother;
		Type returnType=Exp(brother);
	}
	else if(!strcmp(child->name,"IF\0"))
	{
		struct Node* exp1=child->brother->brother;
		struct Node* stmt1=(child->brother->brother->brother->brother);//IF LP Exp RP Stmt
		if(stmt1->brother==NULL){
				Exp(exp1);
				Stmt(stmt1,type);

		}
		else {//IF LP Exp RP Stmt ELSE Stmt
		struct Node* stmt2=stmt1->brother->brother;
		Exp(exp1);
		Stmt(stmt1,type);
		Stmt(stmt2,type);
		}
	}
	else if(!strcmp(child->name,"WHILE\0"))//WHILE LP Exp RP Stmt
	{
		struct Node* exp1=child->brother->brother;
		struct Node* stmt1=exp1->brother->brother;
		Stmt(stmt1,type);
	}




};
void DefList(struct Node*node,FieldList field){
	struct Node*child=node->child;
	if(child!=NULL)
	{
	Def(child,field);
	DefList(child->brother,field);
	}

};
void Def(struct Node*node,FieldList field){
	struct Node* child=node->child;
	Type type=Specifier(child);
	DecList(child->brother,type,field);
	
};
void DecList(struct Node*node,Type type,FieldList field){
	struct Node* child=node->child;
	struct Node*brother=child->brother;
	if(brother==NULL){
	Dec(child,type,field);
	}
	else{
	Dec(child,type,field);
	struct Node* brother2 =brother->brother;
	DecList(brother2,type,field);
	}
	
};

void Dec(struct Node*node,Type type,FieldList field){
	struct Node* child=node->child;
	struct Node*brother=child->brother;
	if(brother==NULL){
		if(field!=NULL&&field->type->kind==STRUCTTAG){
		FieldList member=VarDec(child,type,field);
		AddStructMember(field,member);
		}
		else{
		VarDec(child,type,field);
		}
	}
	else{
		if(field!=NULL&&field->type->kind==STRUCTTAG){
		FieldList member=VarDec(child,type,field);
		AddStructMember(field,member);
		}
		else{
		VarDec(child,type,field);
		}
	}


};
Type Exp(struct Node*node){
		struct Node* child=node->child;
		if(!strcmp(child->name,"LP\0"))//LP Exp RP
		{
			struct Node*brother=child->brother;
			return Exp(brother);
		}
		else if(!strcmp(child->name,"ID\0")){
			struct Node*brother=child->brother;
			FieldList result=lookup_hash(child->TYPE_ID);
			if(brother==NULL)//ID
			{
				struct Node*brother=child->brother;
				return result->type;
			}
			else if(!strcmp(brother->name,"LP\0")){
				struct Node*brother1=brother->brother;
				if(!strcmp(brother1->name,"Args\0")){//ID LP Args RP
					Args(brother1);
					return result->type;				
				}
				else{//ID LP RP
					return result->type;
				}			
			}
		}
		else if(!strcmp(child->name,"Exp\0")){
			Type type1=Exp(child);
			struct Node*brother=child->brother;
			if(!strcmp(brother->name,"LB\0"))//Exp LB Exp RB
			{
				struct Node*brother=child->brother;
				Type type2=Exp(brother->brother);
				return type1->u.array.elem;
			}
			else if(!strcmp(brother->name,"DOT\0"))//Exp DOT ID 
			{
				//TODO
			}
			else if(!strcmp(brother->name,"ASSIGNOP\0"))//Exp ASSIGNOP Exp
			{
				struct Node*brother=child->brother;
				Type type2=Exp(brother->brother);
				//TODO
			}
			else {
			/*
			Exp STAR Exp
			Exp DIV Exp
			Exp PLUS Exp
			Exp MINUS Exp
			Exp RELOP Exp
			Exp AND Exp
			Exp OR Exp			
			*/
			struct Node*brother=child->brother;
			Type type2=Exp(brother->brother);
			//TODO
			}
		}
		else if(!strcmp(child->name,"MINUS\0")){//MINUS Exp
			struct Node*brother=child->brother;
			return Exp(brother);
		}
		else if(!strcmp(child->name,"NOT\0")){//NOT Exp
			struct Node*brother=child->brother;
			return Exp(brother);
		}
		else if(!strcmp(child->name,"INT\0"))//INT
		{
			Type inttype=(Type)malloc(sizeof(struct Type_));
			inttype->kind=BASIC;
			inttype->u.basic=INT;
			return inttype;
		}
		else if(!strcmp(child->name,"FLOAT\0"))//FLOAT
		{
			Type floattype=(Type)malloc(sizeof(struct Type_));
			floattype->kind=BASIC;
			floattype->u.basic=FLOAT;
			return floattype;
		}
	
};
FieldList Args(struct Node*node){
	struct Node* child=node->child;
	struct Node* brother=child->brother;
	FieldList arg=(FieldList)malloc(sizeof(struct FieldList_));
	if(brother==NULL){//Exp
		arg->type=Exp(child);
		arg->tail=NULL;
		arg->name=NULL;
	}
	else{//Exp COMMA Args
		struct Node* brother1=brother->brother;
		arg->type=Exp(child);
		arg->tail=Args(brother1);
		arg->name=NULL;
	}

	return arg;
};
