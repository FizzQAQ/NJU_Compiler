#ifndef HASHMAP
#define HASHMAP
#include<stdbool.h>
#define HASHMAP_SIZE 0x3fff
#define INT 0
#define FLOAT 1
typedef struct Type_* Type;

typedef struct FieldList_* FieldList;

typedef struct HashNode_* HashNode;

HashNode HashMap[HASHMAP_SIZE];
struct Type_
{
	enum{BASIC,ARRAY,STRUCTURE,STRUCTTAG,FUNCTION,ERROR} kind;
	union
	{
	int basic;
	struct {Type elem;int size;}array;
	FieldList structure;
	FieldList structmember;
	struct {Type ret;int argc;FieldList argv;}func;
	}u;
	
};

struct FieldList_
{
	char* name;
	Type type;
	FieldList tail;
};

struct HashNode_
{
	FieldList field;
	HashNode next;
};

unsigned hash_pjw(char* name);

void init_hash();

HashNode insert_hash(FieldList field);

FieldList lookup_hash(char* name);

void AddStructMember(FieldList field,FieldList member);
void AddFuncArgv(FieldList field,FieldList Argv);

void printType(Type type);
void printhashNode(FieldList Node);
void PrintMap();
void PrintSemErr(unsigned type,unsigned linenum,char *elem);
bool TypeMatch(Type a,Type b);
bool ArgMatch(FieldList func,FieldList arg);
bool HaveMember(Type type,char *ID);
#endif
