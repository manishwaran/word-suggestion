#include<iostream.h>
#include<conio.h>
#include<string.h>
struct tree
{
	char d[20];
	struct tree *l[26];
}*root,*target;
typedef struct tree node;
char stack[20][20],str[20];
int top=-1,c;
int isleaf(node *p)
{
	for(int i=0;i<26;i++)
	if(p->l[i]!=NULL)
		 return 0;
	return 1;
}
node *newnode(char *a,int t)
{
	char b[10];
	for(int i=0;i<=t;i++)
		b[i]=a[i];
	b[i]=NULL;
	node *q=new node;
	strcpy(q->d,b);
	for(i=0;i<26;i++)
		q->l[i]=NULL;
	return q;
}
void print(node *p,int lev)
{
	if(p!=NULL)
	{
		for(int i=25;i>=13;i--)
			if(p->l[i]!=NULL)
				print(p->l[i],lev+1);
		for(i=0;i<lev;i++)
			cout<<"   ";
		cout<<p->d<<'\n';
		for(i=12;i>=0;i--)
			if(p->l[i]!=NULL)
				print(p->l[i],lev+1);
	}
}
void put(node *all,int k)
{
	if(isleaf(all)&&strcmp(all->d,str)!=0)
	{
		for(int i=0;i<=top;i++)
			if(k>c)
				return;
			else if(k<c)
			{
				top=0;
				strcpy(stack[top],all->d);
				c=k;
				return;
			}
		top++;
		strcpy(stack[top],all->d);
		c=k;
		return;
	}
	for(int i=0;i<26;i++)
		if(all->l[i]!=NULL)
			put(all->l[i],k+1);
}
int minleaf(node *par,node *all,node *tar)
{
	int k=-1;
	if(all==NULL||tar==NULL)
	return -1;
	if(all==tar)
	{
		if(!isleaf(tar))
		{
			put(tar,0);
			put(par,1);
		}
		return 2;
	}
	for(int i=0;i<26;i++)
	{
		if(all->l[i]!=NULL)
			k=minleaf(all,all->l[i],tar);
		if(k>0)
		{
			if(par!=NULL)
				put(par,k);
			return k+1;
		}
	}
	return 0;
}

void search(node *all,char str[])
{
	if(strcmp(all->d,str)==0)
	{
		target=all;
		return;
	}
	for(int i=0;i<26;i++)
		if(all->l[i]!=NULL)
			search(all->l[i],str);
}

void suggest(node *dic,int lev,char *word,char *sug)
{
	if(word[lev]==NULL)
	{
		cout<<sug<<"   ";
		return;
	}
	for(int i=0;i<26;i++)
	{
		if(word[lev]=='*')
		{
			if(dic->l[i]!=NULL)
			{
				sug[lev]='a'+i;
				sug[lev+1]=NULL;
				suggest(dic->l[i],lev+1,word,sug);
			}
		}
		else
		{
			if(dic->l[word[lev]-'a']!=NULL)
			{
				sug[lev]=word[lev];
				sug[lev+1]=NULL;
				suggest(dic->l[word[lev]-'a'],lev+1,word,sug);
			}
			return;
		}
	}
}

void main()
{
	clrscr();
	char word[10];
	node *p;
	int n;
	root=newnode("#",0);
	cout<<"\nEnter number of strings : ";cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Enter the string "<<i+1<<" : ";cin>>str;
		p=root;
		for(int j=0;str[j]!=NULL;j++)
		{
			if(p->l[str[j]-'a']==NULL)
				p->l[str[j]-'a']=newnode(str,j);
			p=p->l[str[j]-'a'];
		}
		print(root,1);
	}
	cout<<"\nEnter the string to be searched : ";cin>>str;
	search(root,str);
	n=minleaf(NULL,root,target);
	cout<<"\Minimum distance : "<<c<<"\nWord(s) found : "<<top+1<<'\n';
	for(int j=0;j<=top;j++)
		cout<<stack[j]<<"  ";
	cout<<"\nEnter the pattern(*) : ";cin>>word;
	cout<<"\nFound Match : \n";
	suggest(root,0,word,"a");
	getch();
}





