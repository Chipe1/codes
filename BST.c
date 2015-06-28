//requires stdlib.h

typedef struct BST{
	int val,h;
	struct BST *left,*right;
}BST;

void BST_insert(BST **,int);
void BST_updateh(BST **);
int BST_geth(BST *);
void BST_fixit(BST **);
void BST_rotl(BST **);
void BST_rotr(BST **);

void BST_insert(BST **tarp,int val){
	BST *target=*tarp;
	if(target==NULL){
		target=(BST *)malloc(sizeof(BST));
		target->val=val;
		target->h=0;
		target->left=NULL;target->right=NULL;
		*tarp=target;
		return ;
	}
	if(target->val==val){
		//equal action
	}
	else if(target->val>val){
		BST_insert(&(target->left),val);
	}
	else{
		BST_insert(&(target->right),val);
	}
	BST_updateh(tarp);
}

void BST_updateh(BST **tarp){
	BST *target=*tarp;
	int lh,rh;
	if(target==NULL){
		printf("Error :\tupdating NULL pointer");
	}
	lh=BST_geth(target->left);rh=BST_geth(target->right);
	if(lh>rh)
		target->h=lh+1;
	else
		target->h=rh+1;
	if(lh>rh+1||rh>lh+1)
		BST_fixit(tarp);
}

int BST_geth(BST *target){
	if(target==NULL)
		return -1;
	return target->h;
}

void BST_fixit(BST **tarp){
	BST *target=*tarp;
	if(BST_geth(target->left)>BST_geth(target->right)){
		if(BST_geth(target->left->left)>BST_geth(target->left->right)){
			BST_rotr(tarp);
			BST_updateh(&((*tarp)->right));
		}
		else{
			BST_rotl(&(target->left));
			BST_rotr(tarp);
			target=*tarp;
			BST_updateh(&(target->left));
			BST_updateh(&(target->right));
			BST_updateh(tarp);
		}
	}
	else{
		if(BST_geth(target->right->right)>BST_geth(target->right->left)){
			BST_rotl(tarp);
			BST_updateh(&((*tarp)->left));
		}
		else{
			BST_rotr(&(target->right));
			BST_rotl(tarp);
			target=*tarp;
			BST_updateh(&(target->right));
			BST_updateh(&(target->left));
			BST_updateh(tarp);
		}		
	}
}

void BST_rotl(BST **tarp){
	BST *r,*target;
	target=*tarp;r=target->right;
	*tarp=r;
	target->right=r->left;
	r->left=target;
}

void BST_rotr(BST **tarp){
	BST *l,*target;
	target=*tarp;l=target->left;
	*tarp=l;
	target->left=l->right;
	l->right=target;
}
