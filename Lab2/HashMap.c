#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "HashMap.h"
#include "Node.h"
extern unsigned SemanticError;
void init_hash()
{
	for(int i=0;i<HASHMAP_SIZE;i++)
	{
	HashMap[i]=NULL;
	}
	
}
unsigned hash_pjw(char* name){
	unsigned val=0,i;
	for(;*name;++name)
	{
		val=(val<<2)+*name;
		if(i=val&~HASHMAP_SIZE)
			{
				val=(val^(i>>12))&HASHMAP_SIZE;
			}
	}
	return val;
}

HashNode insert_hash(FieldList field){
	if(field->type->kind==ERROR){return NULL;}
	unsigned i;
	if(field->name==NULL)
		i=1;
	else i=hash_pjw(field->name);
	//printf("%s,%d\n",field->name,i);
	HashNode Node=(HashNode)malloc(sizeof(struct HashNode_));
	Node->field=field;
	Node->next=NULL;
	if(HashMap[i]==NULL){
		HashMap[i]=Node;
	}
	else
	{
		HashNode tmp=HashMap[i];
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		tmp->next=Node;
	}
	return Node;
}

FieldList lookup_hash(char* name){
	if(name==NULL)return NULL;
	unsigned i=hash_pjw(name);
	HashNode tmp=HashMap[i];
	while(tmp!=NULL)
	{
		if(!strcmp(tmp->field->name,name))
		{
			return tmp->field;
		}
		tmp=tmp->next;
	}
	return NULL;
}

void AddStructMember(FieldList field,FieldList member){
	if(member->type->kind==ERROR){return;}
	if(field->type->kind==STRUCTTAG){
	FieldList tmp=field;
	if(tmp->type->u.structmember==NULL)
	{
		tmp->type->u.structmember=member;
	}
	else{
		tmp=tmp->type->u.structmember;
		while(tmp->tail!=NULL)
		{
			tmp=tmp->tail;
		}
		tmp->tail=member;
	}
	}
	
};
void AddFuncArgv(FieldList field,FieldList Argv){
	if(Argv->type->kind==ERROR){return;}
	if(field->type->kind==FUNCTION){
	FieldList tmp=field;
	if(tmp->type->u.func.argv==NULL)
	{
		tmp->type->u.func.argv=Argv;
		field->type->u.func.argc++;
	}
	else{
		tmp=tmp->type->u.func.argv;
		while(tmp->tail!=NULL)
		{
			tmp=tmp->tail;
		}
		tmp->tail=Argv;
		field->type->u.func.argc++;
	}
	}

};
void printType(Type type){
	if(type->kind==BASIC){
		if(type->u.basic==0)
			printf("Int\n");
		else 
			printf("Float\n");
	}
	else if(type->kind==ARRAY)
	{
		printf("size:%d\t",type->u.array.size);
		printType(type->u.array.elem);
	}
}
void printhashNode(FieldList Node){
	if(Node->type->kind==BASIC){
		if(Node->type->u.basic==0)
			printf("Int:%s\n",Node->name);
		else 
			printf("Float:%s\n",Node->name);
		}
	else if(Node->type->kind==ARRAY)
		{
		printf("Array:%s",Node->name);
		printSpace(1);
		printType(Node->type);
		}
	else if(Node->type->kind==STRUCTTAG){
			FieldList tmp=Node->type->u.structmember;
			printf("StructTag %s:\n",Node->name);
			if(tmp!=NULL){
			printSpace(1);
			printhashNode(tmp);
			while(tmp->tail!=NULL)
				{
					printSpace(1);
					tmp=tmp->tail;
					printhashNode(tmp);
				}
			}
		}
	else if(Node->type->kind==STRUCTURE){
			FieldList tmp=Node->type->u.structure;
			printf("Struct %s:\n",Node->name);
			if(tmp!=NULL)
			{
				printSpace(1);
				printhashNode(tmp);
			}
		}
	else if(Node->type->kind==FUNCTION){
			printf("function: %s,argc:%d,is_extern:%d,argv:\n",Node->name,Node->type->u.func.argc,Node->type->u.func.is_extern);
			FieldList tmp=Node->type->u.func.argv;
			if(tmp!=NULL){
			printf("Function %s:\n",Node->name);
			printSpace(1);
			printhashNode(tmp);
			while(tmp->tail!=NULL)
				{
					tmp=tmp->tail;
					printSpace(1);
					printhashNode(tmp);
				}
			}
		}
		
}	

void PrintMap(){
	for(int i=0;i<HASHMAP_SIZE;i++){
		if(HashMap[i]!=NULL)
			{
				HashNode tmp=HashMap[i];
				printhashNode(tmp->field);
			}
	}

}
void PrintSemErr(unsigned type,unsigned linenum,char* elem){
	if(elem==NULL)
	{
	elem=(char*)malloc(sizeof(char));
	elem[0]=' ';
	}
	switch(type){
	case 1:printf("Error type %d at Line %d:Undefined variable '%s'.\n",type,linenum,elem);break;
	case 2:printf("Error type %d at Line %d:Undefined function '%s'.\n",type,linenum,elem);break;
	case 3:printf("Error type %d at Line %d:Redefined variable '%s'.\n",type,linenum,elem);break;
	case 4:printf("Error type %d at Line %d:Redefined function '%s'.\n",type,linenum,elem);break;
	case 5:printf("Error type %d at Line %d:Type mismatched for assignment.\n",type,linenum);break;
	case 6:printf("Error type %d at Line %d:The left-hand side of an assignment must be a  variable.\n",type,linenum);break;
	case 7:printf("Error type %d at Line %d:Type mismatched for operands.\n",type,linenum);break;
	case 8:printf("Error type %d at Line %d:Type mismatched for return.\n",type,linenum);break;
	case 9:printf("Error type %d at Line %d:Function '%s' is not applicable for arguments.\n",type,linenum,elem);break;
	case 10:printf("Error type %d at Line %d:'%s' is not an array.\n",type,linenum,elem);break;
	case 11:printf("Error type %d at Line %d:'%s' is not a function.\n",type,linenum,elem);break;
	case 12:printf("Error type %d at Line %d:'%s' is not an integer.\n",type,linenum,elem);break;
	case 13:printf("Error type %d at Line %d:Illegal use of '%s'.\n",type,linenum,elem);break;
	case 14:printf("Error type %d at Line %d:Non-existent field '%s'.\n",type,linenum,elem);break;
	case 15:printf("Error type %d at Line %d:Redefined field or Initialized struct field.\n",type,linenum);break;
	case 16:printf("Error type %d at Line %d:Duplicated name '%s'.\n",type,linenum,elem);break;
	case 17:printf("Error type %d at Line %d:Undefined structure '%s'.\n",type,linenum,elem);break;
	case 18:printf("Error type %d at Line %d:Undefined function '%s'\n",type,linenum,elem);break;
	case 19:printf("Error type %d at Line %d:Inconsistent declaration of function '%s'.\n",type,linenum,elem);break;
	default:printf("Undefined Error!\n");
	}
}
bool TypeMatch(Type a,Type b){
	if(a==NULL||b==NULL)return false;
	if(a==b)return true;
	if(a->kind!=b->kind)return false;
	if(a->kind==BASIC){
		return a->u.basic==b->u.basic;
	}
	else if(a->kind==ARRAY)
	{
		return TypeMatch(a->u.array.elem,b->u.array.elem);
	}
	else if(a->kind==STRUCTURE)
	{
		return TypeMatch(a->u.structure->type,b->u.structure->type);
	}
	return false;
};
bool ArgMatch(FieldList func,FieldList arg){
	FieldList argv1=func->type->u.func.argv;
	FieldList argv2=arg;	
	while(argv1!=NULL&&argv2!=NULL){
		if(!TypeMatch(argv1->type,argv2->type))
			return false;
		argv1=argv1->tail;
		argv2=argv2->tail;
	}
	if(argv1==NULL&&argv2==NULL)
		return true;
	else return false;
};
bool FuncArgMatch(FieldList func1,FieldList func2){
	if(!TypeMatch(func1->type->u.func.ret,func2->type->u.func.ret)){return false;}
	FieldList argv1=func1->type->u.func.argv;
	FieldList argv2=func2->type->u.func.argv;
	while(argv1!=NULL&&argv2!=NULL){
		if(!TypeMatch(argv1->type,argv2->type))
			return false;
		argv1=argv1->tail;
		argv2=argv2->tail;
	}
	if(argv1==NULL&&argv2==NULL)
		return true;
	else return false;
};
FieldList HaveMember(Type type,char *ID){
	FieldList member=type->u.structmember;
	while(member!=NULL)
	{
		if(!strcmp(member->name,ID))
			return member;
		member=member->tail;
	}
	return NULL;
};
void CheckUndefFunc(){
	for(int i=0;i<HASHMAP_SIZE;i++){
		if(HashMap[i]!=NULL)
			{
				
				HashNode tmp=HashMap[i];
				while(tmp!=NULL){
						if(tmp->field!=NULL&&tmp->field->type!=NULL&&tmp->field->type->kind==FUNCTION)
						{
							if(tmp->field->type->u.func.is_extern!=0)
							{
							PrintSemErr(18,tmp->field->type->u.func.is_extern,tmp->field->name);
							SemanticError++;
							}
						}
						tmp=tmp->next;
				}
			}
	}


}
