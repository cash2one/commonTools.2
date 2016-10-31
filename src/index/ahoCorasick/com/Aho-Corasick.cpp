#include<iostream>
#include<string.h>
#include<malloc.h>
#include <map>
#include <queue>
#include "../../include/gary_common/gary_common.h"
#include "../../include/gary_common/gary_string.h"
#include "../../include/service_log.hpp"

using namespace std;

vector<string> pattern;
typedef struct node{
    //struct node *next[26];  //���յ�̬
	std::map<unsigned, node*> next;
    struct node *par;   //���׽ڵ�
    struct node *fail;  //ʧ�ܽڵ�
    unsigned inputchar;
    int patterTag;    //�Ƿ�Ϊ�ɽ���̬
    int patterNo;   //����̬��Ӧ�Ŀɽ���ģʽ
}*Tree,TreeNode;

/**
�����µĽڵ㣬�����г�ʼ��
*/
TreeNode *getNewNode()
{
    int i;
    TreeNode* tnode=(TreeNode*)malloc(sizeof(TreeNode));
    tnode->fail=NULL;
    tnode->par=NULL;
    tnode->patterTag=0;
    return tnode;
}

/**
��Trie���У�root�ڵ�ķ�֧�ڵ㣬�������
*/
int  nodeToQueue(Tree root,queue<Tree> &myqueue)
{
    int i;
    //for (i = 0; i < 26; i++)
    for (map<unsigned, node*>::iterator iter = root->next.begin(); iter != root->next.end(); iter++)
    {
		unsigned index = iter->first;
		Tree nodeC = iter->second;
        myqueue.push(nodeC);
    }
    return 0;
}

/**
����trie��
*/
Tree buildingTree()
{
    int i,j;
    Tree root=getNewNode();
    Tree tmp1=NULL,tmp2=NULL;
	int32_t size = pattern.size();
	cerr << "[buildingTree] size = " << size << endl;
	node *nn;
	int num = 1;
    for(i=0;i<size;i++)
    {
		cerr << "[buildingTree] i = " << num++ << endl;
        tmp1=root;
        for(j=0;j<strlen(pattern[i].c_str());j++)   ///��ÿ��ģʽ���д���
        {
			cerr << "-------1" << endl;
			unsigned index = (unsigned char)pattern[i][j];
			cerr << "-------2 " << index << " " << tmp1<< endl;
			for(map<unsigned, node*>::iterator it = tmp1->next.begin(); it != tmp1->next.end(); it++)
				cerr << "::"<< it->first << "\t"<<it->second << endl;
            //if(tmp1->next[index]==NULL) ///�Ƿ��Ѿ��з�֧��Trie���ýڵ�
            if(tmp1->next.find(index) == tmp1->next.end()) ///�Ƿ��Ѿ��з�֧��Trie���ýڵ�
            {
				cerr << "-------3" << endl;
                tmp2=getNewNode();
				cerr << "-------4" << endl;
                tmp2->inputchar=index;
                tmp2->par=tmp1;
                tmp1->next[index]= nn;
                tmp1=tmp2;
				cerr << "-------5" << endl;
            }
            else
                tmp1=tmp1->next[index];
			cerr << "-------=========" << endl;
        }
        tmp1->patterTag=1;
        tmp1->patterNo=i;
    }
    return root;
}

/**
����ʧ��ָ��
*/
int buildingFailPath(Tree root)
{
    int i;
    unsigned inputchar;
    queue<Tree> myqueue;
    root->fail=root;
    //for(i=0;i<26;i++)   ///��root����ĵڶ���������⴦��
	// ��root �µ�����child �����뵽 queue �С�
	// �����������߼��ǣ�������ȱ���
    map<unsigned, node*>::iterator iter;
	for(iter = root->next.begin(); iter != root->next.end(); iter++)   ///��root����ĵڶ���������⴦��
    {
		unsigned index = iter->first;// child Ԫ��
        root->next[index]->fail=root;	// Ϊ root��child ������fail��ָ����Ϊ root��
        nodeToQueue(root->next[index],myqueue);	// ��root��child ��child�ǲ���queue
    }

    Tree tmp=NULL,par=NULL;
    while(!myqueue.empty())
    {
        tmp=myqueue.front();
        myqueue.pop();
        nodeToQueue(tmp,myqueue);	// ɾ����ǰ�ڵ㣬�������tmp��child��ѹ��queue��������ȱ�����

        inputchar=tmp->inputchar;	// ��ǰԪ��
        par=tmp->par;				// ��ǰԪ�ص�parent ���

        node* failp = par->fail;
        while(failp != NULL)	// ���ڵ�ǰԪ�ز�����ָ����ֱ���ҵ������ҵ�rootΪֹ��
        {
            if(failp->next.find(inputchar) != failp->next.end())
            {
                tmp->fail=failp->next[inputchar];
                break;
            }
            else
                failp=failp->fail;
		}	
		if(failp == NULL)
        {
            tmp->fail=root;
        }
    }
    return 0;
}

/**
���ж�ģʽ����������ѰAC�Զ���
*/
int searchAC(Tree root,char* str,int len) {
    TreeNode *tmp=root;
    int i=0;
    while(i < len)
    {
		unsigned pos = (unsigned char)str[i];
        if (tmp->next.find(pos) != tmp->next.end())
        {
            tmp=tmp->next[pos];
            if(tmp->patterTag==1)    ///���Ϊ����̬
            {
                cout<<i-strlen(pattern[tmp->patterNo].c_str())+1<<'\t'<<tmp->patterNo<<'\t'<<pattern[tmp->patterNo]<<endl;
            }
            i++;
        }
        else
        {
            if(tmp==root)
                i++;
            else
            {
                tmp=tmp->fail;
                if(tmp->patterTag==1)    //���Ϊ����̬
                    cout<<i-strlen(pattern[tmp->patterNo].c_str())+1<<'\t'<<tmp->patterNo<<'\t'<<pattern[tmp->patterNo]<<endl;
            }
        }
    }
    while(tmp!=root)
    {
        tmp=tmp->fail;
        if(tmp->patterTag==1)
            cout<<i-strlen(pattern[tmp->patterNo].c_str())+1<<'\t'<<tmp->patterNo<<'\t'<<pattern[tmp->patterNo]<<endl;
    }
    return 0;
}

/**
�ͷ��ڴ棬DFS
*/
int destory(Tree tree)
{
    if(tree==NULL)
        return 0;
    queue<Tree> myqueue;
    TreeNode *tmp=NULL;

    myqueue.push(tree);
    tree=NULL;
    while(!myqueue.empty())
    {
        tmp=myqueue.front();
        myqueue.pop();

        for (int i = 0; i < 26; i++)
        {
            if(tmp->next[i]!=NULL)
                myqueue.push(tmp->next[i]);
        }
        free(tmp);
    }
    return 0;
}
int main()
{
	string dictFile = "novel.zuozhe";
	ifstream infileDict;
	int ret = spaceGary::open_f(dictFile, infileDict);
	if(ret == -1)
		return -1;
	string line;
	cerr<<"[main::%s] Begin to read file to pattern.\n"<< endl;
	while(getline(infileDict,line))
	{
		spaceGary::StringTrim(line);
		pattern.push_back(line);
	}
	infileDict.close();
	cerr<<"[main::%s] Over reading file to pattern.\n" << endl;
	//
    char a[]="��Ů����ս���»�";
	cerr<<"[main::%s] Begin to buildingTree().\n"<< endl;
    Tree root=buildingTree();   ///����Trie��
	cerr<<"[main::%s] Over buildingTree().\nAnd to buildingFailPath()\n"<< endl;
    buildingFailPath(root); ///���ʧ��ת��
	cerr<<"[main::%s] Over buildingFailPath().\n" << endl;
    cout<<"��ƥ���ַ�����"<<a<<endl;
    cout<<"ģʽ"<<pattern[0]<<" "<<pattern[1]<<" "<<pattern[2]<<" "<<pattern[3]<<" "<<endl<<endl;
    cout<<"ƥ�������£�"<<endl<<"λ��\t"<<"���\t"<<"ģʽ"<<endl;
    searchAC(root,a,strlen(a)); ///����
    destory(root);  ///�ͷŶ�̬�����ڴ�
    return 0;
}
