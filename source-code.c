#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	struct node *children[26];
	char meaning[250];
	int wordEnd;
}dict;

dict* getnode(){
	int i;
	dict *n = (dict *)malloc(sizeof(dict));
	for(i=0;i<26;i++)
		n->children[i] = NULL;
	n->wordEnd = 0;
        return n;
}

dict* insert(char word[],char meaning[],dict *root){
	dict *crawl = root;
	int i;
	if(crawl == NULL) root = crawl = getnode();
	for( i = 0;word[i] != '\0' ;i++ ){
		int indx = word[i] - 'a';
		if(crawl->children[indx] == NULL)
			crawl->children[indx] = getnode();
		crawl = crawl->children[indx];
	}

	if(crawl->wordEnd == 1)
		printf("Word already present\n");
	else{
	       	crawl->wordEnd = 1;
		strcpy(crawl->meaning,meaning);
		printf("Word added\n");
		printf("%s :- %s\n",word,meaning);
	}
	return root;
}


void search(char word[],dict *root){
	dict *crawl = root;
        int i,f=0;
	if(root==NULL) return;
        for( i = 0;word[i] != '\0' ;i++ ){
                int indx = word[i] - 'a';
                if(crawl->children[indx] == NULL)
                	f=1;
                crawl = crawl->children[indx];
        }

        if(crawl->wordEnd == 0 || f==1)
                printf("Word is not in the dictionary\n");
        else{
                printf("THe meaning of the word is :- %s\n",crawl->meaning);
        }
}

dict* delete(char word[],dict *root){
	dict *crawl = root;
        int i;
        if(crawl == NULL) {
		printf("Word was not present\n");
		return root;
	}
        for( i = 0;word[i] != '\0' ;i++ ){
                int indx = word[i] - 'a';
                if(crawl->children[indx] == NULL)
                        crawl->children[indx] = getnode();
                crawl = crawl->children[indx];
        }

        if(crawl->wordEnd == 1){
		crawl-> wordEnd =0;
		printf("Word Deleted\n");
	}
        else{
              printf("Word not present\n");
        }

	return root;
}

void print(dict *root,char word[],int indx){
	if(root->wordEnd == 1){
		printf("Word :- %s Meaning:- %s\n",word,root->meaning);
	}
	int i;
	word[indx+1] = '\0';
	for(i=0;i<26;i++){
		if(root->children[i]!=NULL){
			word[indx] = 'a'+i;
			print(root->children[i],word,indx+1);
		}
	}
}

int main(){
	dict *root=NULL;
	int choice=1;
	char word[50],meaning[250],ch;
	while(choice){
		printf("1.Add word\n2.Delete word\n3.Search word\n4.Display all words\n");
		printf("Enter your choice :- ");
		scanf("%d",&choice);
		//scanf("%c",&ch);
		switch(choice){
			case 1 : printf("Enter a word to add :- ");
				scanf("%s",word);
				printf("Enter the meaning :- ");
				scanf("%c",&ch);
			       	scanf("%[^\n]%*c",meaning);
				root = insert(word,meaning,root);
				break;

			case 2: printf("Enter a word to delete :- ");
                                scanf("%s",word);
                                root = delete(word,root);
                                break;


			case 3: printf("Enter a word to search :- ");
				scanf("%s",word);
				search(word,root);
				break;

			case 4: printf("The words in the dictionary are \n");
				print(root,word,0);
		}

	}

	return 0;
}
