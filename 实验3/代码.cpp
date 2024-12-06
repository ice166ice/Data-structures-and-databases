#include<iostream>
#include <cstdlib>
#include <string>
#include <queue>

using namespace std;

//定义菜单 
void showmenu(){
	cout<<endl;
	cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<endl; 
	cout<<"****0.退出此系统*******"<<endl;
	cout<<"****1.创建二叉树*******"<<endl;
	cout<<"****2.遍历二叉树******"<<endl;
	cout<<"****3.二叉树的计算****"<<endl;
	cout<<"****4.二叉树的处理****"<<endl;
	cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
}

/*
定义结构体 
*/ 
typedef int TElemType;//二叉树存储的数据类型设置为int 
typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree; 

/*
定义函数 
*/

////初始化一个带头结点的空树 
//void InitBitree(BiTree &T){
//	T = (BiTree) malloc(sizeof(BiTNode));
//	if(!T){
//		cout<<"初始化失败，分配内存失败,将退出这个程序"<<endl;
//		char x;
//		cout<<"摁任意字母退出程序"<<endl;
//		cin>>x;
//		exit(1);//终止整个程序 
//	}
//	T->lchild = NULL;
//	T->rchild = NULL;
//	return;
//}
void AlloSpace(BiTree &T){
	T = (BiTree) malloc(sizeof(BiTNode));
	if(!T){
		cout<<"初始化失败，分配内存失败,将退出这个程序"<<endl;
		char x;
		cout<<"摁任意字母退出程序"<<endl;
		cin>>x;
		exit(1);//终止整个程序 
	}
	return;
}

void CreateBitreeHelper(BiTree &T, string preorder, int &index){
	//cout<<"初始Index"<<index<<endl;
	//辅助创建二叉树，递归生成 
	if(index >= preorder.length()){
		
		return;
	}
	
	if (preorder[index] == '#'){   //这里最开始写成=而不是==，导致一直创建不成功，这个错误太经典了 
		T = NULL;
		index++;
		//cout<<"2 index:"<<index<<endl;
	}else{
		T->data = preorder[index]-'0';//将字符转换为整数 
		index++;
		//cout<<"T->data   index"<<T->data<<index<<endl;
		AlloSpace(T->lchild);  //一定要避免野指针 
		CreateBitreeHelper(T->lchild, preorder, index);
		AlloSpace(T->rchild);
		CreateBitreeHelper(T->rchild, preorder, index);  
	}
	
	
} 


// 1.创建二叉树
void CreateBitree(BiTree &T){
	//该函数输入为一个二叉树指针，并且会先让你输入一段前序遍历序列 
	//该函数没有输出，但是会将输入的序列的二叉树跟结点指针保存在指针数组中 
	//InitBitree(T);
	AlloSpace(T);
	string preorder; //先序遍历输入
	cout<<"请输入先序遍历序列（无节点的用 # 表示）："<<endl;
	cin>>preorder;
	
	int index = 0;//用于计数，变量位于preorder表达式的位置 
	CreateBitreeHelper(T, preorder, index);//辅助函数，写递归生成二叉树代码 
	cout<<"创建成功"<<endl;
	
	return;
} 

//先序遍历 
void PreOrder(BiTree T){
	if(T){ 
		cout<<T->data;
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
	return;
}
//中序遍历
void MidOrder(BiTree T){
	if(T){
		MidOrder(T->lchild);
		cout<<T->data;
		MidOrder(T->rchild);
	}
	return;
}

//后序遍历 
void PostOrder(BiTree T){
	if(T){
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		cout<<T->data;
	}
	return;
}

//层序遍历 
void LevelOrder(BiTree T){
	if(T){
		queue<BiTree> q;//设置一个辅助队列 
		q.push(T); //将T放入队列 
		while(! q.empty()){
			BiTree current = q.front();//访问队首元素 
			q.pop();//出队
			if(current){
				cout<<current->data;
				q.push(current->lchild);
				q.push(current->rchild);
			} 
		}

	}
	return;
}

// 2.遍历二叉树
void TravBitree(BiTree T){
	//函数输入是欲遍历的树的根结点指针
	//函数输出无，但是会打印遍历的结果 
	int select = 0;//选择是先序、中序、后序还是层序 
	
	while(true){
		cout<<endl;
		cout<<"请输入一个数字代表你将以什么形式遍历二叉树"<<endl;
		cout<<"****************0.退出遍历****************"<<endl;
		cout<<"****************1.先序遍历****************"<<endl;
		cout<<"****************2.中序遍历****************"<<endl;
		cout<<"****************3.后序遍历****************"<<endl;
		cout<<"****************4.层序遍历****************"<<endl;
		cin>>select;
		switch(select){
			case 0:
				return;
			case 1:
				//1.先序遍历
				PreOrder(T);
				break;
			case 2:
				//2.中序遍历
				MidOrder(T);
				break;
			case 3:
				//3.后序遍历
				PostOrder(T);
				break;
			case 4:
				//4.层序遍历
				LevelOrder(T);
				break;
			default:
				cout<<"输入有误"<<endl;
		}
		}
	return;
	
} 
// 3.1.计算结点数
int CountNode(BiTree T){
	if(!T){
		return 0;//结点为空就返回 0 
	}else{
		return 1 + CountNode(T->lchild) +CountNode(T->rchild);//递归计算 
	}
}
// 3.2.计算叶子数
void CountLeaves(BiTree T, int &n){
	//函数输入是查询的树的根节点指针和一个计数变量n
	//函数输出无，但是通过带回n的值可以输出叶子个数
	
	if(T){
		
		CountLeaves(T->lchild,n);
		CountLeaves(T->rchild,n);
		if(T->lchild ==NULL & T->rchild == NULL){
			n++;
//			cout<<"结点："<<T->data<<endl;
//			cout<<"叶子数量为："<<n<<endl; 	
		}
	} 
	return;
}
// 3.3.计算高度
int TreeHeight(BiTree T){
	//函数输入是查询的树的根节点指针
	//函数输出高度 
	int m;
	int n;
	if(T==NULL){
		return 0;//结点为空就返回 0
	}else{
		m = TreeHeight(T->lchild);//递归计算 
		n = TreeHeight(T->rchild);
		if(m>n){
			return m+1;
		}else{
			return n+1;//选择最大的高度返回 
		}
	}
}
// 3.4.计算宽度  :查询二叉树每一层的结点数，取最大值，有点类似层次遍历
int TreeWidth(BiTree T){
	if(!T){
		return 0;
	}
	queue<BiTree> q;//设置辅助队列 
	q.push(T);
	int width;//记录每一层的宽度
	int max = 0;
	
	while(! q.empty()){
		width = q.size();//记录该层的宽度

		for(int i =0; i<width; i++){
			BiTree current = q.front();//访问队首元素
			
			q.pop();//元素出队
			if(current){
				if(current->lchild){ //必须加上这个判断！！！不然就会把空指针也给放进队列，不仅会让width出错，在取出current->data时也会让程序崩溃！！！！ 
					q.push(current->lchild);
				}
				if(current->rchild){
					q.push(current->rchild);
				}
			} 	
		}
		if (width > max){
			max = width;
		}	
	}
	return max;
} 


// 3.二叉树计算
void CalcuBitree(BiTree T){
	//函数输入是欲遍历的树的根结点指针
	//函数输出无，但是会打印计算的结果
	int select = 0;//选择计算结点数、叶子数、高度还是宽度  
	while(true){
		int n_leaves = 0;//计数叶子结点个数
		cout<<"请输入一个数字代表你将以什么形式遍历二叉树"<<endl;
		cout<<"***************0.退出计算函数*************"<<endl;
		cout<<"***************1.计算结点数***************"<<endl;
		cout<<"***************2.计算叶子数***************"<<endl;
		cout<<"***************3.计算高度*****************"<<endl;
		cout<<"***************4.计算宽度*****************"<<endl;
		cin>>select;
	 
		switch(select){
		case 0:
			//退出函数 
			return;
		case 1:
			cout<<"结点个数为："<<CountNode(T)<<endl;
			break;
		case 2:
			//int n_leaves = 0; //不能在这里定义 
			CountLeaves(T, n_leaves);
			cout<<"叶子数量为："<<n_leaves<<endl; 
			break;
		case 3:
			cout<<"树高度为："<<TreeHeight(T)<<endl;
			break;
		case 4:
			cout<<"数的宽度为："<<TreeWidth(T)<<endl;
			break;
		default:
			cout<<"输入有误"<<endl;
	}
	}
	return;
} 


// 4.1 二叉树的复制
void CopyBitree(BiTree T, BiTree &copy){
	//先序复制二叉树 
	//输入：要复制的树的头结点指针，新生成的二叉树头结点指针
	//输出：无，但是生成了一个复制的二叉树 
	if(!T){
		copy = NULL;
		return;
	}
	if(T){
		AlloSpace(copy);
		copy->data = T->data;
		CopyBitree(T->lchild, copy->lchild);
		CopyBitree(T->rchild, copy->rchild);
	}
	return;
} 

// 4.2 二叉树的销毁
void DestroyBitree(BiTree &T){
	//后序销毁二叉树 
	//输入：要销毁的树的头结点指针
	//输出：无
	if(T){
		DestroyBitree(T->lchild);
		DestroyBitree(T->rchild);
		free(T);
		
	}
	T = NULL;   //free只是释放了malloc所申请的内存，并没有改变指针的值!!!!!!!!!  而且这里必须加这句代码，不然数组存的指针被free掉了，你又去访问，就会导致程序崩溃！！！！ 
	return;
}


int main(){
	const int MaxTrees = 10;//定义最大数组数量
	BiTree Forests[MaxTrees];//定义指针数组存放二叉树的头指针
	for(int i=0;i<MaxTrees;i++){
		Forests[i] = NULL;
	}//初始化数组 
	while(true){
		char x;//这里使用x来使程序在Linux中暂停
		showmenu();
		int select;
		cout<<"请输入数字，代表你要执行的功能"<<endl;
		cin>>select;
		
		while (cin.fail()) //如果输入类型和定义类型不一致为true
		{
			if (cin.fail())
			{
				cout << "输入选项不合法！！！" << endl;
				cin.clear();
				cout<<"请重新输入"<<endl; 
				while (cin.get() != '\n')
				{
					continue;
				}
				cin >>select;
			}
		}
		
		int ikun;//索引值，代表存指针数组的位置
		int jkun;//索引值，代表存指针数组的位置
		int select2;//功能4中选择复制还是销毁 
		switch(select){
			case 0:
				//退出系统
				cout<<"请确认是否退出系统 0.不退出   1.退出"<<endl;
				int a;
				cin>>a;
				if(a == 0){
					break;
				}else if (a == 1){
					cout<<"欢迎下次使用此系统"<<endl;
					return 0; 
					break;
				}else{
					cout<<"输入有误，默认不退出"<<endl;
					break;
				}
			case 1:
				//创建二叉树
				cout<<"请输入你要创建的二叉树的索引,最小值为0，最大不超过"<<MaxTrees-1<<endl;
				cin>>ikun;
				if(ikun>=0 && ikun<MaxTrees){
					CreateBitree(Forests[ikun]); 
				}else{
					cout<<"输入有误，超出索引范围"<<endl; 
				}
				
				break;
				
			case 2:
				//遍历二叉树
				cout<<"请输入你要遍历的二叉树的索引,最小值为0，最大不超过"<<MaxTrees-1<<endl;
				cin>>ikun;
				if(ikun>=0 & ikun<MaxTrees){
					TravBitree(Forests[ikun]);
				}else{
					cout<<"输入有误，超出索引范围"<<endl;
				}
				break;
			case 3:
				//二叉树的计算
				cout<<"请输入你要计算的二叉树的索引,最小值为0，最大不超过"<<MaxTrees-1<<endl;
				cin>>ikun;
				if(ikun>=0 & ikun<MaxTrees){
					CalcuBitree(Forests[ikun]);
				}else{
					cout<<"输入有误，超出索引范围"<<endl;
				}
				break;
			case 4:
				//二叉树的处理（复制、销毁）
				cout<<"请输入一个数字代表你将进行什么操作"<<endl;
				cout<<"*************1.复制树*************"<<endl;
				cout<<"*************2.销毁树*************"<<endl;
				cin>>select2;
				if(select2 == 1){
					cout<<"请输入你要处理的二叉树的索引,最小值为0，最大不超过"<<MaxTrees-1<<endl;
					cin>>ikun;
					cout<<"请输入你复制的新二叉树存放的索引,最小值为0，最大不超过"<<MaxTrees-1<<endl;
					cin>>jkun;
					if(ikun>=0 & ikun<MaxTrees &jkun>=0 & jkun<MaxTrees){
						
						CopyBitree(Forests[ikun], Forests[jkun]);  //这里最开始两个都写成ikun了。。。导致一直复制不成功
						cout<<"复制成功"<<endl; 
					}else{
						cout<<"输入有误，超出索引范围"<<endl;
					}
				}else if(select2 == 2){
					cout<<"请输入你要处理的二叉树的索引,最小值为0，最大不超过"<<MaxTrees-1<<endl;
					cin>>ikun;
					if(ikun>=0 & ikun<MaxTrees){
						
						DestroyBitree(Forests[ikun]);
						cout<<"销毁成功"<<endl;
					}else{
						cout<<"输入有误，超出索引范围"<<endl;
					}
				}
				
				
				break;
			default:
				cout<<"输入有误，请重新输入"<<endl;
				cout<<"程序暂停，按任意字母或者数字后再enter确认，可继续运行程序"<<endl; 
				cin>>x;
				break; 	
			
		}
		
		
	}
	
	
	return 0;//出循环之后没有代码需要执行，可以退出系统了
} 
