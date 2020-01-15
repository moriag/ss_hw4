#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define num_of_letters 26
typedef struct Letter_node{
char pre;
int count;
struct Letter_node** suf;
}Letter_node;

Letter_node* new(char c){
    Letter_node* new=(Letter_node*)malloc(sizeof(Letter_node));
    new->pre=c;
    new->count=0;
    new->suf=(Letter_node**)malloc(sizeof(Letter_node*)*num_of_letters);
    for(int i=0;i<num_of_letters;i++){
        new->suf[i]=NULL;
    }
    return new;
}

void inOrder(Letter_node* root,char* s){
  int len=strlen(s);
  s[len]=root->pre;
  s[len+1]='\0';

  if(root->count)printf("%s\t%i\n",s,root->count);
 
  for(int i=0;i<num_of_letters;i++){
      if(root->suf[i]!=NULL) inOrder(root->suf[i],s);
  }   
 
  s[len]='\0';
 
  free(root->suf);
  free(root);
}
void reverseOrder(Letter_node* root,char* s){
  int len=strlen(s);
  s[len]=root->pre;
  s[len+1]='\0';
 
  for(int i=num_of_letters-1 ;i>=0 ;i--){
     if(root->suf[i]!=NULL) reverseOrder(root->suf[i],s);
  }
 
  if(root->count)printf("%s\t%i\n",s,root->count);   
  s[len]='\0';
 
  free(root->suf);
  free(root);
}

int main(int argc,char** argv){
    
    if(!(argc==1||(argc==2&& !strcmp(argv[1],"r"))))return 0;

    int reverse=0;
    if(argc==2)reverse++; 
    
    char c=' ';
    int word_len=0;
    int max_len=0;
    
    Letter_node* main_root=new('\0');
    Letter_node* sub_root=main_root;
    // free (main_root);
    // scanf("%c",&c);
    int i=0;
    while (i!=EOF){
       i=scanf("%c",&c);

       if(c==' '||c=='\n'){
            if (word_len){
                if(word_len>max_len)max_len=word_len;
                sub_root->count++;
                word_len=0;
                sub_root=main_root;
            }
            continue;
        }
        

        
        if(c>'Z')c-='a';
        else{c-='A';}
        if(c<0)continue;
        word_len++;
        if(sub_root->suf[(int)c]==NULL){sub_root->suf[(int)c]=new(c+'a');}
        sub_root=sub_root->suf[(int)c];
        
    }
    char* s=(char*)malloc(max_len+1);
    s[0]='\0';
    if(reverse)reverseOrder(main_root,s);
    else{inOrder(main_root,s);}
    free(s);
}
