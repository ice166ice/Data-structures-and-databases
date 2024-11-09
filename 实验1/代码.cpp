#include<iostream>
#include <cstdlib>
using namespace std;

//定义菜单 
void showmenu(){
	cout<<endl;
	cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl; 
	cout<<"****0.退出此系统*********"<<endl;
	cout<<"****1.创建一元多项式*****"<<endl;
	cout<<"****2.显示一元多项式*****"<<endl;
	cout<<"****3.一元多项式求和*****"<<endl;
	cout<<"****4.求微分（N阶导数）**"<<endl;
	cout<<"****5.求不定积分*********"<<endl;
	cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
}

/*
定义结构体 
*/

//定义多项式的存储结构
typedef struct ElemType{
	float coef;
	int expn;
}ElemType; 
//定义链表存储多项式
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList; 
//将指针名字叫做polynomial
typedef LinkList polynomial; 

/*
定义相应的函数 
*/

//初始化一个带头节点的单链表
int InitList(LinkList &L){
	L = (LinkList) malloc(sizeof(LNode));//头节点指针               //这里是否需要传入指向指针的指针，会不会导致外面的没有因为里面的修改而修改，不会 
	if (!L){
		cout<<"初始化失败，内部分配失败"<<endl;
		exit(1);
	}
	L->next = NULL;
	return 0;
}
 

//1.创建一元多项式
void CreatePolyn(polynomial &p){
	//传入一个指针p作为头节点 
	InitList(p);
	p->data.coef = 0.0;
	p->data.expn = -1;//设置头节点
	
	cout<<"请设置欲输入的项数(准备输入几次)："<<endl; 
	int n;  
	cin>>n;
	
	float coef;
	int expn;//临时存储 
	for(int i=0; i<n; i++){
		cout<<"请输入第"<<i+1<<"项的系数和指数："<<endl;
		cin>>coef>>expn;
		
		//创建一个新节点存放这两个值
		LinkList newp = (LinkList) malloc(sizeof(LNode));
		if(!newp){
			cout<<"创建新节点失败，内部分配失败"<<endl;
			exit(1);
		}
		newp->data.coef = coef;
		newp->data.expn = expn;
		newp->next = NULL;

		//插入这一项到他该放置的位置;按照指数项递减来排列 
		LinkList q1 = p;
		//LinkList q2 = p;
		while(q1->next && q1->next->data.expn>expn){
			//q2 = q1; //存储前一个q1指针 
			q1 = q1->next;
		}
		//除了系数相同需要进行合并之外，其他情况都可以直接放进去 
		if(q1->next && q1->next->data.expn == expn){               //
			q1->next->data.coef += coef;
			if(q1->next->data.coef==0){
				LinkList temp = q1->next;                         //
				q1->next = q1->next->next;
				free(temp);                                       //
			}
			free(newp);
		}else if(q1->next==NULL){
			//直接插入 
			q1->next = newp;
		}else{
			//将他插入在q1之前 
			newp->next = q1->next;
			q1->next = newp;
		}	
	}	 
} 

// 2.显示一元多项式
void ShowPolyn(polynomial p,int m){
	//m这个值是在显示不定积分补常数C 时用到的 
	LinkList q = p->next;//跳过头节点 3
	while(q!=NULL){
		//cout<<q->data.coef<<endl;
		//cout<<q->data.expn<<endl;
		if(q->data.coef>0 && q!=p->next){
			cout<<"+"; //如果是系数项是正数且不是第一个项 ，那么需要打印+ 
		}
		if(q->data.expn == 0){
			cout<<q->data.coef;//如果是指数项为0，则不需要打印x 
		}else if(q->data.expn == 1){
			if(q->data.coef == 1){
				cout<<"X";
			}else if(q->data.coef == -1){
				cout<<"-X";
			}else{
				cout<<q->data.coef<<"X";//如果指数项为1，则不需要打印^指数 
			} 
		}else{
			if(q->data.coef == 1){
				cout<<"X^"<<q->data.expn;
			}else if(q->data.coef == -1){
				cout<<"-X^"<<q->data.expn;
			}else{
				cout<<q->data.coef<<"X^"<<q->data.expn;//其他情况需要打印x^指数项次方 
			}
		}
		q=q->next;
	}
	if(m==2){
		cout<<"+C (C为一个任意常数)";
	} 
	cout<<endl;
}

//3.一元多项式求和
//为了后续的函数，这里不改变pa和pb这俩链表,生成一个新的pc的链表 
//值得注意的是，相比直接显示结果，这种做法会浪费内存，如果你不需要使用求和结果的话 
void AddPolyn(polynomial pa, polynomial pb, polynomial &pc){ 
	InitList(pc);
	LinkList qa = pa->next;
	LinkList qb = pb->next;
	LinkList qc = pc;                     //教训：这里一定要注意不能直接LinkList qc = pc->next，这样的qc是不能使用的，其实也就是未申请内存分配的节点是不能直接用LinkList定义之后就直接使用的！！！ 
	while(qa && qb){
		//创建一个新节点存放这qc的值 
		LinkList newp = (LinkList) malloc(sizeof(LNode));
			if(!newp){
				cout<<"创建新节点失败，pc内部分配失败"<<endl;
				exit(1);
		} 
		if(qa->data.expn>qb->data.expn){
			//存放qa的值
			newp->data.coef = qa->data.coef;
			newp->data.expn = qa->data.expn;
			newp->next = NULL;
			qa = qa->next;
			qc->next = newp;
			qc = newp; 
		
		}else if(qa->data.expn == qb->data.expn){
			//存放求和后的值
			if(qa->data.coef+qb->data.coef != 0){
				newp->data.coef = qa->data.coef + qb->data.coef;
				newp->data.expn = qa->data.expn;
				newp->next = NULL;
				qc->next = newp;
				qc = newp;
			}
			qa = qa->next;
			qb = qb->next;
			 
		}else{
			//存放qb的值
			newp->data.coef = qb->data.coef;
			newp->data.expn = qb->data.expn;
			qb = qb->next;
			newp->next = NULL;
			qc->next = newp;
			qc = newp;
		}
	}
	while(qa){
		qc->next = qa;
		qa = qa->next;
		qc = qc->next;
	}
	while(qb){
		qc->next = qb;
		qb = qb->next;
		qc = qc->next;
	}
	cout<<"求和结果是："<<endl;
	ShowPolyn(pc,1);
}

/*
// 4.求多项式的微分
// 在第三问的函数中已经演示过生成一个新的链表来存储和
// 因此该问，我们展示不生成新的链表，直接使用该链表来存储结果
// 这样做的好处是不浪费内存，坏处是，我们再也无法获得他原来的值了 
void DiffPolyn(polynomial p, int n){
	//n是求微分的次数
	for(int i=0;i<n;i++){
		LinkList q = p->next;//跳过头节点
		LinkList pre = p;//用于记录前一个节点
		while(q){
			//计算当前多项式节点一次微分后的结果 
			q->data.coef = q->data.coef * q->data.expn;
			q->data.expn -= 1;
			//如果指数小于0了，说明原来是常数，微分后就没了，应该删除，否则保留 
			if(q->data.expn<0){
				LinkList temp = q;
				pre->next = q->next;
				q = q->next;
				pre = pre->next;
				free(temp);
			}else{
				pre = q;
				q = q->next;
			}
		}
	} 
}
*/ 

// 4.求多项式的微分
//为了保留原有多项式 
//生成一个新的链表存储结果 
void DiffPolyn(polynomial p, int n, polynomial &result) {
    // n 是求微分的次数
    InitList(result); // 初始化结果链表
    LinkList q = p->next; // 跳过头节点
    LinkList qr = result; // 结果链表的指针

    // 复制原多项式到结果链表
    while (q) {
        LinkList newp = (LinkList)malloc(sizeof(LNode));
        if (!newp) {
            cout << "创建新节点失败，result内部分配失败" << endl;
            exit(1);
        }
        newp->data.coef = q->data.coef;
        newp->data.expn = q->data.expn;
        newp->next = NULL;
        qr->next = newp;
        qr = newp;
        q = q->next;
    }

    // 对结果链表进行 n 次微分
    for (int i = 0; i < n; i++) {
        q = result->next; // 跳过头节点
        LinkList pre = result; // 用于记录前一个节点
        while (q) {
            // 计算当前多项式节点一次微分后的结果
            q->data.coef = q->data.coef * q->data.expn;
            q->data.expn -= 1;
            // 如果指数小于 0 了，说明原来是常数，微分后就没了，应该删除，否则保留
            if (q->data.expn < 0) {
                LinkList temp = q;
                pre->next = q->next;
                q = q->next;
                free(temp);
            } else {
                pre = q;
                q = q->next;
            }
        }
    }
}

/*
//如果只用显示一次微分后的结果，则可以：
//先要判断是否输出+:系数大于0且不是第一项 
		while(q){
			if(q.data.coef>0 && q!=p->next){
				cout<<"+"
			} 
			if(q.data.expn>2){
				//系数为指数*系数，指数形式为X^(指数-1) 
				cout<<q.data.coef * q.data.expn<<"X^"<<q.data.expn-1
			}else if(q.data.expn == 2){
				//系数为指数*系数，指数形式为X  
				cout<<q.data.coef * q.data.expn<<"X"
			}else if(q.data.expn == 1){
				//系数为系数，指数为0不用显示 
				cout<<q.data.coef
			}
			//其余情况不用显示
			q = q->next;
		}
*/ 

/*
// 5.求多项式的不定积分 ,这里还是覆盖原来的多项式，并且假设只用求一次不定积分 
void IntegPolyn(polynomial p){
	LinkList q = p->next;//跳过头节点
	while(q){
		//系数=系数/（指数+1） 指数 = 指数+1 
		q->data.coef = q->data.coef/(q->data.expn+1);
		q->data.expn = q->data.expn+1;
		q = q->next; 
	}
	
} 
*/ 

// 5.求多项式的不定积分 
//这里不覆盖原来的多项式，生成一个新的链表存储结果 
void IntegPolyn(polynomial p, polynomial &result) {
    InitList(result); // 初始化结果链表
    LinkList q = p->next; // 跳过头节点
    LinkList qr = result; // 结果链表的指针

    // 复制原多项式到结果链表
    while (q) {
        LinkList newp = (LinkList)malloc(sizeof(LNode));
        if (!newp) {
            cout << "创建新节点失败，result内部分配失败" << endl;
            exit(1);
        }
        newp->data.coef = q->data.coef;
        newp->data.expn = q->data.expn;
        newp->next = NULL;
        qr->next = newp;
        qr = newp;
        q = q->next;
    }

    // 对结果链表进行不定积分
    q = result->next; // 跳过头节点
    while (q) {
        // 计算不定积分后的系数和指数
        q->data.coef /= (q->data.expn + 1);
        q->data.expn += 1;
        q = q->next;
    }
}




int main(){
	const int MaxPolynomials = 10;//定义最大多项式数量
	polynomial polyns[MaxPolynomials];//定义指针数组存放多项式的头指针
	//初始化指针
	for(int i=0;i<MaxPolynomials;i++){
		polyns[i] = NULL;
	}
	//polynomial p1,p2,p3;
	while(true){
		char x;//这里用x来使程序在Linux中暂停 
		showmenu();
		int select;
		cout<<"请输入数字，代表你要进行的功能"<<endl;
		cin>>select;
		int index;//索引值  
		switch(select){
			case 0:
				//退出系统 
				int a;
				cout<<"是否确认退出系统 0.不退出  1.退出"<<endl;
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
				//创建一元多项式
				
				cout<<"请输入你要创建的多项式的索引,最小值为0，最大不超过"<<MaxPolynomials-1<<endl;
				cin>>index;
				if(index>=0 && index< MaxPolynomials){
					CreatePolyn(polyns[index]);
				}else{
					cout<<"你的输入无效，超出索引范围"<<endl; 
				}
				cout<<"程序暂停，按任意字母或者数字后再enter确认，可继续运行程序"<<endl; 
				cin>>x; 
				break;
			
			case 2:
				//显示一元多项式
				cout<<"请输入你要显示的多项式的索引,最小值为0，最大不超过"<<MaxPolynomials-1<<endl;
				cin>>index;
				if(index>=0 && index< MaxPolynomials &&polyns[index]!=NULL){
					ShowPolyn(polyns[index],1);
				}else{
					cout<<"你的输入无效"<<endl; 
				}
				cout<<"程序暂停，按任意字母或者数字后再enter确认，可继续运行程序"<<endl; 
				cin>>x;
				break;
			case 3:
				//一元多项式求和
				cout<<"请输入你要相加的两个多项式的索引:"<<endl;
				int index1,index2;
				polynomial p3;
				cin>>index1>>index2;
				if(index1>=0 && index1<MaxPolynomials && index2>=0 && index2<MaxPolynomials \
				&& polyns[index1] != NULL && polyns[index2] != NULL ){
					AddPolyn(polyns[index1],polyns[index2],p3);
				}else{
					cout<<"你的输入无效"<<endl; 
				}
				cout<<"程序暂停，按任意字母或者数字后再enter确认，可继续运行程序"<<endl; 
				cin>>x;
				break;
				
			case 4:
				cout<<"请输入你要求微分的多项式的索引"<<endl;
				cin>>index;
				int n;
				cout<<"请输入你要微分的次数："<<endl;
				cin>>n; 
				cout<<"微分后的结果为："<<endl;
				polynomial result1;
				if(index>=0 && index< MaxPolynomials && polyns[index]!=NULL){
					DiffPolyn(polyns[index],n,result1);
					if(result1->next == NULL){
						cout<<"0"<<endl;//没有了，当然显示0了 
					}else{
						ShowPolyn(result1,1);
					}
				}else{
					cout<<"你的输入无效"<<endl; 
				}
				cout<<"程序暂停，按任意字母或者数字后再enter确认，可继续运行程序"<<endl; 
				cin>>x;
				break;
				//求微分（N阶导数）
			case 5:
				//求不定积分
				cout<<"请输入你要求不定积分的多项式的索引"<<endl;
				cin>>index;
				cout<<"不定积分后的结果为："<<endl;
				polynomial result2;
				if(index>=0 && index< MaxPolynomials && polyns[index]!=NULL){
					IntegPolyn(polyns[index],result2);
					ShowPolyn(result2,2);
				}else{
					cout<<"你的输入无效"<<endl; 
				}
				cout<<"程序暂停，按任意字母或者数字后再enter确认，可继续运行程序"<<endl; 
				cin>>x;
				break;
				//求微分（N阶导数）
			default:
				cout<<"输入有误，请重新输入"<<endl;
				cout<<"程序暂停，按任意字母或者数字后再enter确认，可继续运行程序"<<endl; 
				cin>>x;
				break;
		}
		}
		return 0;//出循环之后没有代码需要执行，可以退出系统了 
		
}
