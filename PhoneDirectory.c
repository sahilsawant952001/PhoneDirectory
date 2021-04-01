#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//NUMBER OF SYMBOLS USED IN TRIE(PHONE DIRECTORY)
#define LETTERS (30)
//STRUCTURE FOR TRIE NODE
struct TrieNode
{
 //STRUCTURE POINTER OF TYPE TRIENODE TO STORE ALL CHILDREN
 struct TrieNode *children[LETTERS];
 //END OF WORD IS 1 OR 0
 //1 INDICATES PRESENCE OF THAT WORD
 //0 INDICATES ABSENCE OF THAT WORD
 int isEndOfWord;
 //CHAR ARRAY TO STORE NUMBER
 char number[11];
};
//FUNCTION TO DETERMINE ARRAY SIZE
int ARRAY_SIZE(int a[])
{
 return sizeof(a)/sizeof(a[0]);
}
//RETURNS A NEW TRIE NODE WITH ALL CHILDREN INITIALLIZED AS NULL
//AND ENDOFWORD AS 0
struct TrieNode *getNode()
{
 struct TrieNode *temp = NULL;
 temp = (struct TrieNode *)malloc(sizeof(struct TrieNode));
 if (temp!=NULL)
 {
 int i;
 temp->isEndOfWord = 0;
 for (i = 0; i < LETTERS; i++)
 temp->children[i] = NULL;
 }
 return temp;
}
//THIS FUNCTION GIVES INDEX TO CHARACTER FOR MAPPING IT IN CHILDREN ARRAY
int CHARACTER_TO_NUMBER(char ch)
{
 return ((int)ch - (int)'a');
}
//IF GIVEN CONTACT NAME IS PRESENT IN TRIE THEN IT JUST
//MARKS END OF WORD AS TRUE FOR LEAF NODE OF THAT WORD
//ELSE IT CREATES NEW NODE FOR EACH CHARACTER WHCIH IS NOT
//PRESENT IN TRIE AND THEN MARKS ENDOF WORD AS TRUE FOR LEAF NODE
void TrieInsert(struct TrieNode *root,char name[],char number[])
{
 int length = strlen(name);
 int index;
 struct TrieNode *temp = root;
 //LOOPING THROUGH GIVEN CONTACT NAME
 for (int l = 0; l < length; l++)
 {
 //FINDING INDEX FOR MAPPING IN CHILDREN ARRAY
 index = CHARACTER_TO_NUMBER(name[l]);
 //IF GIVEN CHARACTER IS NOT PRESENT IN TEMP NODE
 //CREATE NEW NODE FOR THAT CHARACTER
 if (temp->children[index]==NULL)
 temp->children[index] = getNode();
 //MOVE TEMP POINTER TO CHILDREN NODE OF CURRENT CHARACTER CHARACTER
 temp = temp->children[index];
 }
 //MARK ENDOFWORD OF LEAF NODE AS 1
 temp->isEndOfWord = 1;
 //STORE MOBILE NUMBER IN LEAF NODE
 strcpy(temp->number,number);
}
void ShowSuggestionsHelper(struct TrieNode *currentNode, char prefix[])
{
 // IF GIEVN NODE IS LEAF NODE THEN JUST PRINT CONTACT NAME AND NUMBER
 if (currentNode->isEndOfWord==1)
 {
 printf("|");
 printf("%s",prefix);
 if(strlen(prefix)>6)
 printf("\t\t|");
 else
 printf("\t\t\t|");
 printf("\t%s\t",currentNode->number);
 printf("\t|\n");
 }
 //CHECK ALL THE CHILDREN OF GIVEN NODE AND IF
 //ANY NODE IS NOT NULL THEN ADD CORRESPONDING CHARACTER IN PREFIX ARRAY
 //THEN CALL SHOWSUGGESTIONSHELPER
 //FUNCTION RECURSIVELY ON THAT CHILDREN
 //AFTER FUNCTION CALL ENDS REMOVE LAST CHARACTER FROM
 //PREFIX ARRAY
 for (char i = 'a'; i <= '~'; i++)
 {
 struct TrieNode *nextNode = currentNode->children[CHARACTER_TO_NUMBER(i)];
 if (nextNode != NULL)
 {
 strncat(prefix,&i,1);
 ShowSuggestionsHelper(nextNode, prefix);
 int len = strlen(prefix);
 prefix[len-1]='\0';
 }
 }
}
//THIS FUNCTIONS DISPLAYS ALL THE
//CONTACTS WHICH START WITH GIVEN STRING
void ShowSuggestions(struct TrieNode *root,char str[])
{
 struct TrieNode *previousNode = root;
 char prefix[200] = "";
 int len = strlen(str);
 int i;
 //LOOP THROUGH THE GIVEN STRING
 for (i=0; i<len; i++)
 {
 //STORE THE CURRENT CHARACTER IN PREFIX ARRAY
 strncat(prefix,&str[i],1);
 //LAST CHARACTER OF PREFIX ARRAY
 char lastChar = prefix[i];
 //CURRENTNODE IS NODE NODE WHICH POINTS TO LAST CHARACTER OF PREFIX
 struct TrieNode *currentNode = previousNode->children[CHARACTER_TO_NUMBER(lastChar)];
 //CURRENTNODE IS NULL IF LAST CHARACTER OF PREFIX IS NOT PRESENT IN TRIE
 //SO WE STOP OUR SEARCH
 if(currentNode==NULL)
 {
 printf("|No Suggestions For %s\t\t\t\t|\n",str);
 break;
 }
 //IF CURRENTNODE POINTS TO LAST CHARACTER OF GIVEN CONTACT NAME
 //CHECK WHETHER THAT CHARACTER IS PRESENT IN TRIE OR NOT IF PRESENT THEN CALL
 //SHOWSUGGESTIONSHELPER FUNCTION TO PRINT ALL CONTACTS STARTING WITH THAT PREFIX ELSE STOP
 if(i==len-1)
 {
 if (currentNode == NULL)
 {
 printf("|No Suggestions For %s\t\t\t\t|\n",str);
 i++;
 break;
 }
 ShowSuggestionsHelper(currentNode, prefix);
 }
 //MAKE CURRENT AS PREVIOUS NODE
 previousNode = currentNode;
 }
}
//CHECK WHEATHER TRIE NODE IS EMPTY OR NOT
//TRIE NODE IS EMPTY IF ALL ITS CHILDERN ARE NULL
int IsEmpty(struct TrieNode* root)
{
 for (int i = 0; i < LETTERS; i++)
 if (root->children[i]!=NULL)
 return 0;
 return 1;
}
//FUNCTION TO DISPLAY ALL THE CONTACTS OF TRIE
void DisplayDirectory(struct TrieNode* root, char str[], int level)
{
 //IF NODE IS LEAF NODE THEN
 //PRINT THE CONTACT AND NUMBER
 if (root->isEndOfWord==1)
 {
 str[level] = '\0';
 printf("|");
 printf("%s",str);
 if(strlen(str)>6)
 printf("\t\t|");
 else
 printf("\t\t\t|");
 printf("\t%s",root->number);
 printf("\t\t|\n");
 }
 //LOOP THROUGH ALL CHILDREN OF NODE
 int i;
 for (i = 0; i < LETTERS; i++)
 {
 //IF CHILD IS NOT NULL THEN ADD THAT CHARACTER IN STR
 //AND CALL FUNCTION RECURSIVELY ON ITS CHILDERN
 if (root->children[i]!=NULL)
 {
 str[level] = i + 'a';
 DisplayDirectory(root->children[i], str, level + 1);
 }
 }
}
int Edit(struct TrieNode *root, char *key,char *num)
{
 //ROOT NODE
 struct TrieNode *temp = root;
 //LOOPING THROUGH THE GIVEN STRING
 for (int i = 0; i < strlen(key); i++)
 {
 //FINDING INDEX OF CHARACTER IN ARRAY
 int index = CHARACTER_TO_NUMBER(key[i]);
 //IF TEMP DOES NOT CONTAINS CHARACTER
 //WITH ABOVE INDEX VALUE AS CHILDREN THEN RETUEN 0
 if (temp->children[index]==NULL)
 return 0;
 //ELSE MOVE TEMP POINTER TO CHILDREN
 //CONTAINIG THAT INDEX VALUE
 temp = temp ->children[index];
 }
 //IF TEMP IS NOT EQUAL TO NULL AND END OF WORD IS TRUE
 //EDIT NUMBER AND RETURN 1 ELSE RETURN 0
 if(temp != NULL && temp->isEndOfWord==1)
 {
 strcpy(temp->number,num);
 return 1;
 }
 else
 {
 return 0;
 }
}
//FUNCTION TO DELETE CONTACT FROM TRIE
struct TrieNode * TrieDelete(struct TrieNode * root, char key[], int depth)
{
 //IF NODE EMPTY RETURN NULL
 if (root==NULL)
 return NULL;
 //IF DEPTH IS EQUAL TO LENGTH OF GIVEN WORD
 if (depth == strlen(key))
 {
 //AND END OF WORD OF CURRENT NODE IS 1
 //MAKE END OF WORD OF CURRENT NODE AS 0
 if (root->isEndOfWord==1)
 root->isEndOfWord = 0;
 //IF ALL CHILDREN OF CURRENT NODE ARE NULL
 //DELETE CURRENT NODE AND MAKE IT NULL
 if (IsEmpty(root)) {
 free (root);
 root = NULL;
 }
 return root;
 }
 //IF DEPTH IS NOT EQUAL TO LENGTH OF GIVEN STRING THEN
 //FIND THE INDEX VALUE OF THAT CHARACTER
 //THEN CALL DELETE FUNCTION RECURSIVELY ON THE CHILDREN
 //OF NODE HAVING THAT INDEX VALUE
 int index = CHARACTER_TO_NUMBER(key[depth]);
 root->children[index] = TrieDelete(root->children[index], key, depth + 1);
 //IF NODE HAS NO CHILDREN AND ENDOFWORD IS 0 THEN
 //DELETE THAT NODE
 if (IsEmpty(root) && root->isEndOfWord == 0)
 {
 free (root);
 root = NULL;
 }
 return root;
}
// Driver
int main()
{
 struct TrieNode *root = getNode();
 char contacts[10][20][20] = {{"sahil~sawant","9874563215"},
 {"sahil~sodha","9856274125"},
 {"sahil~yadav","7458963215"},
 {"sarang~yogi","9874562183"},
 {"sarthak~nasith","8745963258"},
 {"rohan~sodha","8496517121"},
 {"rohini~yadav","7485906123"},
 {"akash~yadav","9696741202"},
 {"akhil~pathak","8204506203"},
 {"atharva~ranade","9021374890"}};
 for(int i=0;i<10;i++)
 {
 TrieInsert(root,contacts[i][0],contacts[i][1]);
 }
 printf("-----------------------------------------------------------------------------------\n");
 printf("|1 - INSERT | 2 - SEARCH | 3 - DISPLAY | 4 - DELETE | 5 - EDIT |\n");
 printf("--------------------------------------------------------------------------------\n\n");
 printf("Enter Lowercase Letters Only\n\n");
 printf("Use ~ Character In Place Of Space\n\n");
 while(1)
 {
 int option;
 printf("Enter Option : ");
 scanf("%d",&option);
 if(option==1)
 {
 if(root==NULL)
 {
 root = getNode();
 }
 printf("\n\n");
 int n;
 printf("How Many Contacts You Want To Insert : ");
 scanf("%d",&n);
 printf("\n");
 for(int i=0;i<n;i++)
 {
 char s[100],num[11];
 printf("Enter Name : ");
 scanf("%s",s);
 printf("Enter Phone Number : ");
 scanf("%s",num);
 TrieInsert(root,s,num);
 }
 printf("\n\n");
 }
 else if(option==2)
 {
 printf("\n\n");
 char x[20];
 printf("Enter String To Search : ");
 scanf("%s",x);
 printf("\n");
 printf("---------------------------------------------------------\n");
 printf("|Contacts\t\t|\tNumbers\t\t\t|\n");
 printf("---------------------------------------------------------\n");
 if(root!=NULL)
 ShowSuggestions(root,x);
 else
 printf("|\t\tNo Data Available\t\t\t|\n");
 printf("---------------------------------------------------------\n");
 printf("\n\n");
 }
 else if(option==3)
 {
 printf("\n\n");
 int level = 0;
 char str[20];
 printf("---------------------------------------------------------\n");
 printf("|Contacts\t\t|\tNumbers\t\t\t|\n");
 printf("---------------------------------------------------------\n");
 if(root!=NULL)
 DisplayDirectory(root, str, level);
 else
 printf("|\t\tNo Data Available\t\t\t|\n");
 printf("---------------------------------------------------------\n");
 printf("\n\n");
 }
 else if(option==4)
 {
 printf("\n\n");
 char d[20];
 printf("Enter The Contact Name To delete : ");
 scanf("%s",d);
 if(root!=NULL)
 root = TrieDelete(root,d,0);
 printf("\n\n");
 }
 else if(option==5)
 {
 printf("\n\n");
 char d[20],n[11];
 printf("Enter The Contact Name To Edit Number : ");
 scanf("%s",d);
 printf("Enter Number : ");
 scanf("%s",n);
 int res = Edit(root,d,n);
 if(res==1)
 printf("Number Edited Successfully !\n");
 else
 printf("Number Not Found!\n");
 printf("\n\n");
 }
 else
 {
 break;
 }
 }
 return 0;
}