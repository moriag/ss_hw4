#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define num_of_letters 26

//tree node
typedef struct Letter_node{
char pre;
int count;
struct Letter_node** suf;
}Letter_node;

//allocate and creat new node 
Letter_node* new(char c){
    Letter_node* new=(Letter_node*)malloc(sizeof(Letter_node));
    new->pre=c;//the last letter so far  
    new->count=0;//num of words that ends here
    //words that continue from here
    new->suf=(Letter_node**)malloc(sizeof(Letter_node*)*num_of_letters);
    //initialize to null
    for(int i=0;i<num_of_letters;i++){
        new->suf[i]=NULL;
    }
    return new;
}
//print in order and free allcated memmory
void inOrder(Letter_node* root,char* s){
  int len=strlen(s);
  s[len]=root->pre;//add the root char
  s[len+1]='\0';//end string

  if(root->count)printf("%s\t%i\n",s,root->count);//the word that ends here
 
  for(int i=0;i<num_of_letters;i++){
      //words that continue after this sub word
      if(root->suf[i]!=NULL) inOrder(root->suf[i],s);
  }   

  //so that the the string will be the same as before entering this function
  s[len]='\0';

  //free the pointer to all children and the pointer to root
  free(root->suf);
  free(root);
}
//print in reversed order and free allcated memmory
void reverseOrder(Letter_node* root,char* s){
  int len=strlen(s);
  s[len]=root->pre;//add the root char
  s[len+1]='\0';//end string
 
  for(int i=num_of_letters-1 ;i>=0 ;i--){
     //print words that continue from this point and free the suffixes nodes  
     if(root->suf[i]!=NULL) reverseOrder(root->suf[i],s);
  }
  //if a word ends here print it and its count 
  if(root->count)printf("%s\t%i\n",s,root->count);   
  //revert to the former string
  s[len]='\0';
  //free the pointer to all children and pointer to root 
  free(root->suf);
  free(root);
}
void errRelease(Letter_node* root){

  for(int i=0;i<num_of_letters;i++){
      //free children's inner alocations 
      if(root->suf[i]!=NULL) errRelease(root->suf[i]);
  }   
  //free the pointer to all children and the pointer to root
  free(root->suf);
  free(root);
}
int main(int argc,char** argv){
    //verify leagl values
    if(!(argc==1||(argc==2&& !strcmp(argv[1],"r"))))return 0;
    //check if reverse
    int reverse=0;
    if(argc==2)reverse++; 
    
    char c=' ';
    int word_len=0;
    int max_len=0;
    //creat the main root of the tree
    Letter_node* main_root=new('\0');//empty word ends here, usfull in printing
    Letter_node* sub_root=main_root;//use to travel in the tree
    // free (main_root);
    // scanf("%c",&c);
    int i=0;
    
    while (i!=EOF){
       i=scanf("%c",&c);
       

       if(c==' '||c=='\n'){//end of word
            if (word_len){//not empty word
                if(word_len>max_len)max_len=word_len;//update max length 
                sub_root->count++;//add count
                word_len=0;//start count again
                sub_root=main_root;//return to start a new word
            }
            continue;
        }

        if(c>'Z')c-='a';
        else{c-='A';}
        if(c<0)continue;//not a letter
        word_len++;//add to length

        if(sub_root->suf[(int)c]==NULL){//first accurence of this prefix
            sub_root->suf[(int)c]=new(c+'a');
            }
        if(sub_root->suf[(int)c]==NULL){
          printf("ERR: alocation failed.\n Releasing alocated memmory...\n");
          errRelease(main_root);
          return 0;
        }
        sub_root=sub_root->suf[(int)c];//continue traveling down by char
        
    }
    //allocate memmory for string that can contain the longest word
    char* s=(char*)malloc(max_len+1);
    s[0]='\0';//start empty 
    if(reverse)reverseOrder(main_root,s);//print in reversed order and free
    else{inOrder(main_root,s);}//print and free
    //free the string
    free(s);
}
