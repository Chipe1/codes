//requires stdlib.h

typedef struct __BST{
	int val,h,count,w;
	struct __BST *left,*right;
}BST;

void BST_insert(BST **,int);
void BST_update(BST **);
int BST_geth(BST *);
int BST_getw(BST *);
void BST_fixit(BST **);
void BST_rotl(BST **);
void BST_rotr(BST **);
BST * BST_search(BST *,int);
void BST_delete(BST **,int);
int BST_lessthan(BST *,int);

void BST_insert(BST **tarp,int val){
	BST *target=*tarp;
	if(target==NULL){
		target=(BST *)malloc(sizeof(BST));
		target->val=val;
		target->h=0;
		target->left=NULL;target->right=NULL;
		target->count=1;
		target->w=1;
		*tarp=target;
		return ;
	}
	if(target->val==val){
		target->count++;
		target->w++;
	}
	else if(target->val>val){
		BST_insert(&(target->left),val);
	}
	else{
		BST_insert(&(target->right),val);
	}
	BST_update(tarp);
}

void BST_update(BST **tarp){
	BST *target=*tarp;
	int lh,rh;
	if(target==NULL){
		return ;
	}
	target->w=BST_getw(target->left)+BST_getw(target->right)+target->count;
	lh=BST_geth(target->left);rh=BST_geth(target->right);
	if(lh>rh)
		target->h=lh+1;
	else
		target->h=rh+1;
	if(lh>rh+1||rh>lh+1)
		BST_fixit(tarp);
}

int BST_getw(BST *target){
	if(target==NULL)
		return 0;
	return target->w;
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
			BST_update(&((*tarp)->right));
			BST_update(tarp);
		}
		else{
			BST_rotl(&(target->left));
			BST_rotr(tarp);
			target=*tarp;
			BST_update(&(target->left));
			BST_update(&(target->right));
			BST_update(tarp);
		}
	}
	else{
		if(BST_geth(target->right->right)>BST_geth(target->right->left)){
			BST_rotl(tarp);
			BST_update(&((*tarp)->left));
			BST_update(tarp);
		}
		else{
			BST_rotr(&(target->right));
			BST_rotl(tarp);
			target=*tarp;
			BST_update(&(target->right));
			BST_update(&(target->left));
			BST_update(tarp);
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

BST * BST_search(BST *target,int val){
	if(target==NULL)
		return NULL;
	if(target->val==val)
		return target;
	else if(target->val>val){
		return BST_search(target->left,val);
	}
	else{
		return BST_search(target->right,val);
	}
}

void BST_delete(BST **tarp,int val){
	BST *target;
	if(tarp==NULL)
		return ;
	target=*tarp;
	if(target->val==val){
		if(target->count>0){
			target->count--;
			target->w--;
		}
	}
	else if(target->val>val){
		BST_insert(&(target->left),val);
	}
	else{
		BST_insert(&(target->right),val);
	}
	BST_update(tarp);
}

int BST_lessthan(BST *target,int val){
	if(target==NULL)
		return 0;
	if(target->val>=val){
		return BST_lessthan(target->left,val);
	}
	else{
		return BST_lessthan(target->right,val)+target->w+BST_getw(target->left);
	}
}
