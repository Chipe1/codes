//requires stdlib.h

typedef struct __BST{
  int v; // value. replace with required data type and modify CoMParisions
  int h, c, w; // height, count, weight
  struct __BST *l, *r;
}BST;

void BST_insert(BST **, int);
void BST_update(BST **);
int BST_geth(BST *);
int BST_getw(BST *);
void BST_fixit(BST **);
void BST_liftr(BST **);
void BST_liftl(BST **);
BST * BST_search(BST *, int);
void BST_delete(BST **, int);
int BST_lessthan(BST *, int);

void BST_insert(BST **tarp, int v){
  BST *t = *tarp;
  if(t == NULL){
    t=(BST *)malloc(sizeof(BST));
    t->v = v;
    t->h = 0;
    t->l = t->r = NULL;
    t->c = 1;
    t->w = 1;
    *tarp=t;
    return ;
  }
  if(t->v == v){ // cmp
    t->c++;
  }
  else if(t->v > v){ //cmp
    BST_insert(&(t->l),v);
  }
  else{
    BST_insert(&(t->r),v);
  }
  BST_update(tarp);
}

void BST_update(BST **tarp){
  if(t == NULL)return ;
  BST *t = *tarp;
  int lh, rh; // left&right height
  t->w = BST_getw(t->l) + BST_getw(t->r) + t->c;
  lh = BST_geth(t->l);
  rh = BST_geth(t->r);
  int mnh, mxh; // min&max of lh,rh
  mnh = lh < rh ? lh : rh;
  mxh = mnh^lh^rh;
  t->h = mxh + 1;
  
  if(mxh > mnh + 1) BST_fixit(tarp);
}

int BST_getw(BST *t){
  if(t == NULL) return 0;
  return t->w;
}

int BST_geth(BST *t){
  if(t == NULL) return -1;
  return t->h;
}

void BST_fixit(BST **tarp){
  BST *t = *tarp;
  if(BST_geth(t->l) > BST_geth(t->r)){
    if(BST_geth(t->l->l) > BST_geth(t->l->r)){
      BST_liftl(tarp);
      BST_update(&((*tarp)->r));
      BST_update(tarp);
    }
    else{
      BST_liftr(&(target->left));
      BST_liftl(tarp);
      target=*tarp;
      BST_update(&(target->left));
      BST_update(&(target->right));
      BST_update(tarp);
    }
  }
  else{
    if(BST_geth(target->right->right)>BST_geth(target->right->left)){
      BST_liftr(tarp);
      BST_update(&((*tarp)->left));
      BST_update(tarp);
    }
    else{
      BST_liftl(&(target->right));
      BST_liftr(tarp);
      target=*tarp;
      BST_update(&(target->right));
      BST_update(&(target->left));
      BST_update(tarp);
    }		
  }
}

void BST_liftr(BST **tarp){
  BST *r, *t;
  t = *tarp;r = t->r;
  *tarp = r;
  t->r = r->l;
  r->l = t;
}

void BST_liftl(BST **tarp){
  BST *l, *t;
  t = *tarp;l = t->l;
  *tarp = l;
  t->l = l->r;
  l->r = t;
}

BST * BST_search(BST *t, int v){
  if(t == NULL) return NULL;
  if(t->v == v) return t; // cmp
  else if(t->v > v) return BST_search(t->l, v); // cmp
  else return BST_search(t->r, v);
}

void BST_delete(BST *t,int v){
  if(t == NULL) return ;
  
  if(t->v == v){
    if(t->c > 0){
      target->c--;
    }
  }
  else if(t->v > v) BST_delete(t->l, v);
  else BST_delete(t->r, v);
  
  BST_update(&t); // only w will be updated. no rotations
}

int BST_lessthan(BST *t, int v){
  if(t == NULL) return 0;
  if(t->v >= v) return BST_lessthan(t->l, v); // cmp
  else return BST_lessthan(t->r, v) + t->c + BST_getw(t->l); // cmp
}
