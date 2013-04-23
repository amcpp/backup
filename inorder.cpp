#include<iostream>
//#include<conio.h>
using namespace std;

struct node{
       int num;
       node *lt;
       node *rt;
       };

void add(node *r,int n)
{
     int n1;
      node *temp1;
     temp1=new node;
      temp1->num=n;
                   temp1->lt=NULL;
                   temp1->rt=NULL;
    if(r==NULL)
    {
                 r=temp1;      
    }
    else
    {    
      node *temp;
     
      temp=r;
    while(temp)
    {
                   if(temp->num>n )
                   {
                   if(temp->lt)   
                   temp=temp->lt;
                   else
                   {
                    temp->lt=temp1;
                   break;
                   }
                   }
                   else
                   {
                       if(temp->rt)
                       temp=temp->rt; 
                       else
                        {
                        temp->rt=temp1;
                       break;
                       }
                       } 
                   
    }

    }
} 


void inorder(node *r)
{
     int n;
     if(r)
     {  
           inorder(r->lt); 
           cout<<r->num<<" ";
           inorder(r->rt);
     }
}

void level_sum(node *root,int level,int *sum)
{
     if(root==NULL)
     return;
     else
     {
         sum[level]+=root->num;
         level_sum(root->lt,level+1,sum);
         level_sum(root->rt,level+1,sum);
     }
 }
 
node* mirror(node* root)
{
      if(root==NULL)
        return NULL;
      node *temp=root->rt;
      root->rt=mirror(root->lt);
      root->lt=mirror(temp);
      return root;
}

int max(int a,int b)
{
    return((a>b)?a:b);
}      
  
int height(node* root)
{
    if(root==NULL)
    return 0;
    
    return(1+ max(height(root->lt),height(root->rt)));
    
}    
int diameter(node* root) 
{
    int left,right,cur,d;
    if(root==NULL)
         return 0;
    left=diameter(root->lt);
    right=diameter(root->rt);
    cur=height(root->rt)+height(root->lt)+1;
    d=max(cur,max(left,right));
    return d;
    
}
int next_inorder(node* root,int n)
{
    int next=0;
    while(root->num!=n)
    {
       if((root->num)>n)
       {
          next=root->num;
          root=root->lt;
          //cout<<next;
          }
       else
        {
           //  cout<<root->num;
             root=root->rt;
          //   getch();
        }
    }
    //cout<<next;
    if(root->rt!=NULL)
    {
       root=root->rt;
       while(root->lt!=NULL)
        root=root->lt;
       next=root->num;
    }
    return next;   
}    
int kdistance(int k,int v,node *r)
{
    int d=-1;
    if(r==NULL)
    return d;
    if(r->num==v)
    { //cout<<v;
      return 0;}
    
    else
    {
        d=kdistance(k,v,r->lt);
        if(d==-1)
        d=kdistance(k,v,r->rt);
        if(d!=-1)
        d++;
        }
        if(d==k)
        cout<<r->num;
       
   return d; 
    
}

void iter_inorder(node* root)
{
     node* stack[100];
     int top=-1;
     while(root)
     {
         if(root->lt)   
         {
            top++;
            stack[top]=root;
            root=root->lt;
         }
         else
         {
             cout<<root->num<<" ";
             while(root->rt==NULL)
            {
             if(top<0)
             return;
             root=stack[top];
             top--;
             cout<<root->num<<" ";
             
             }
             root=root->rt;
         }
             
     }
         
}

void del_node(node* root,int val)
{
     node* temp,*temp1;
     
     temp=root;
     
     if(root->lt==NULL && root->rt==NULL)
         delete root; 
             
            while(root->num!=val)
            {
                 temp=root;
                 if(root->num>val)
                    root=root->lt;
                 else
                      root=root->rt;
            }
            if(root->lt==NULL && root->rt==NULL)
            {
                    if(temp->num>root->num)
                    temp->lt=NULL;
                 else
                    temp->rt=NULL;
                    delete root;
             }
            else if(root->lt==NULL)
            {
                 if(temp->num>root->num)
                    temp->lt=root->rt;
                 else
                    temp->rt=root->rt;
                 delete root;
            }
            else if(root->rt==NULL)
            {
                  if(temp->num>root->num)
                    temp->lt=root->lt;
                 else
                    temp->rt=root->lt;
                 delete root;
            }
            else
            {
                temp1=root->rt;
                while(temp1->lt!=NULL)
                 {
                   temp=temp1;
                   temp1=temp1->lt;
                   }
                root->num=temp1->num;
                del_node(temp,temp1->num);
               /* if(temp->rt!=NULL)
                 {
                       temp->num=temp->rt->num;
                       temp=temp->rt;
                 }
                 delete temp;*/
            }
}

int zig_zag(node* root)
{
    int top1=-1,top2=-1;
    node* cur[20];
    node* next[20];
    node* temp;
    cur[0]=root;
    top1=0;
    cout<<"Zig Zag"<<endl;
    while(top1>=0 || top2>=0)
    {
                  while(top1>=0)
                  {
                     temp=cur[top1];
                     if(temp->lt)
                     {
                        top2++;
                        next[top2]=temp->lt;
                        }
                     if(temp->rt)
                     {
                        top2++;
                        next[top2]=temp->rt;
                        }
                     top1--;
                     cout<<temp->num<<" ";
                  }
                  cout<<endl;
                  while(top2>=0)
                  {
                     temp=next[top2];
                     if(temp->rt)
                     {
                        top1++;
                        cur[top1]=temp->rt;
                        }
                     if(temp->lt)
                     {
                        top1++;
                        cur[top1]=temp->lt;
                        }
                     top2--;
                     cout<<temp->num<<" ";
                     
                  }
                  cout<<endl;
    }
}
                  

int rev_sum(node* root,int val)//converts the bst into binary tree where every key is the sum of all the keys 
{
	if(root)
	{
		val=rev_sum(root->rt,val);
		val+=root->num;
		root->num=val;
		val=rev_sum(root->lt,val);	
	}	
	return val;
}
       

int main()
{
    int n,i;
    int arr[20];
      for(i=0;i<5;i++)
      arr[i]=0;
    node *tree=NULL;
    tree=new node;
    tree->num=5;
    tree->rt=NULL;
    tree->lt=NULL;
    add(tree,10);
    add(tree,1);
    add(tree,20);
    add(tree,12);
    add(tree,5);
    add(tree,7);
    add(tree,26);
    inorder(tree);
    cout<<"\n";
    //inorder(tree);
    kdistance(3,26,tree);
    level_sum(tree,0,arr);
    for(i=0;i<5;i++)
    cout<<" "<<arr[i];
    cout<<endl;
    del_node(tree,5);
    inorder(tree);
    cout<<endl;
    mirror(tree);
    iter_inorder(tree);
    mirror(tree);
    cout<<endl<<diameter(tree)<<" ";
    cout<<next_inorder(tree,10);
    zig_zag(tree);
    inorder(tree);
    cout<<endl;
    rev_sum(tree,0);
    inorder(tree);
    //getch();
    return 0;
}
 
