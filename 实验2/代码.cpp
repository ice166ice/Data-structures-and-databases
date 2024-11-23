#include<iostream>
#include <cstdlib>
#include <cctype>
#include <stdexcept>

using namespace std;

//定义菜单 
void showmenu(){
	cout<<endl;
	cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<endl; 
	cout<<"****0.退出此系统*******"<<endl;
	cout<<"****1.波兰式计算*******"<<endl;
	cout<<"****2.逆波兰式计算*****"<<endl;
	cout<<"****3.中缀表达式计算***"<<endl;
	cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
}
/*
定义结构体 
*/ 
typedef struct SLNode{
	char data; 
	struct SLNode * next;
}SLNode, *LinkStack;


/*
定义函数 
*/

//入栈函数 
void push(LinkStack &LS, char e){
	LinkStack p = (LinkStack) malloc(sizeof(SLNode));
	p->data = e;
	p->next = LS;
	LS = p;
}
//出栈函数
void pop(LinkStack &LS, char &e){
	if(!LS){
		cout<<"空栈，错误操作"<<endl;
		return;
	}
	LinkStack p = LS;
	e = p->data;
	LS = LS->next;
	free(p);
}
void DestroyStack(LinkStack &LS){
	while (LS) {
        LinkStack temp = LS;
        LS = LS->next;
        free(temp);
    }
    LS = NULL;  // 将栈指针置为 NULL
} 

//判断是否是运算符 
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
// 计算函数
int operate(int a, char op, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}
//波兰式计算 
int PolishCalcu() {
    LinkStack OPND = NULL; 
    LinkStack InputStack = NULL;
    char c;
    int num = 0;
	bool is_num = true; 
	int n = 0;
    cout << "请一次性输入前缀表达式，每次输入都摁一个空格确认你的输入（以#结束）："<<endl;
    cout <<"数字之间没有空格就代表是同一个数，数字之间有空格就代表是不同的数 " <<endl;
	//读取输入并存放到输入栈中
	while((c = getchar()) != '#'){
		if (!isdigit(c) && !isOperator(c) && c != ' ' && c != '\n') {
			cout<<"输入非法字符，结果作废，请重新输入"<<endl; 
        }
		push(InputStack, c);
	}
	while(InputStack){
		pop(InputStack, c);
		if (n == 0){  //要把最开始的第一个空格给删除，可能有一个空格或者可能没有空格 
			if (c == ' '){
			pop(InputStack, c);
		}n = n+1;	
		} 
		if(isdigit(c)){//如果是数字就压入栈 
			is_num = true;
			num = num * 10 + c - '0';
//			push(OPND, c);
		}else if(c == ' '){  //这个==不能写成=啊！！ 
			if(is_num){
				push(OPND, num+'0');
				num = 0;
				is_num =false;
			}
		}else if(isOperator(c)){
			int a,b;
			char temp;//取两个操作数出来，都用temp表示 
			pop(OPND, temp);
			a = temp - '0'; // 将字符转换为数字
            pop(OPND, temp);
            b = temp - '0'; // 将字符转换为数字
            int result = operate(a, c, b); 
            push(OPND, result + '0');//将结果转换为字符并压入操作数栈中 
		}
//		// 清除输入缓冲区中的换行符
//        cin.ignore();
	}
	char resultChar;
	pop(OPND, resultChar);//最后操作数栈中的值就是结果 
	int result = resultChar -'0' ;
	if (OPND){
		cout<<"多数字："<<OPND->data<<endl; 
		cout<<"操作数过多，请重新输入"<<endl;//提示操作数过多 
	}
	DestroyStack(OPND);
	DestroyStack(InputStack);
	return result;
}
//逆波兰式计算
//和刚才类似，从左到右读取，如果是操作数，则直接入栈，如果是运算符，则取出栈顶的前两个数字进行运算，再把结果入栈，重复上述操作 
//int InversePolishCalcu(){
//	LinkStack OPND = NULL; 
//    char c;
//    int num = 0;//用于多位数的累加计数！！！！不然多位数会被识别为多个一位数！！！ 
//    bool is_num = false;//标记当前是否正在读取数字 
//    cout << "请一次性输入后缀表达式，每次输入都回车或空格确认你的输入（以#结束）："<<endl;
//	//读取输入并存放到输入栈中
//	while((c = getchar()) != '#'){
//		if(isdigit(c)){
//			num = num*10 + (c - '0');
//			is_num = true;
////			push(OPND, c); 
//		}else if(c== ' ' || isOperator(c)){
//			if(is_num){//说明上一个读取的是数字 
//				push(OPND, num);
//				num = 0;
//				is_num = false;
//			}
//			if(isOperator(c)){
//				int a,b;
//				pop(OPND,b);
//				pop(OPND,a);
//				int result = operate(a, c, b);
//				push(OPND, result);
//			}
//		}
//		// 清除输入缓冲区中的换行符
//        cin.ignore();
//	}
//	int final_resu
//	pop(OPND, final_result);
//	
//	return final_result;
//} 

int InversePolishCalcu(){
	LinkStack OPND = NULL; 
    char c;
    int num = 0;
    bool is_num = true;
    cout << "请一次性输入后缀表达式，每次输入都摁一个空格确认你的输入（以#结束）："<<endl;
    cout <<"数字之间没有空格就代表是同一个数，数字之间有空格就代表是不同的数 " <<endl; 
	//读取输入并存放到输入栈中
	while((c = getchar()) != '#'){
		if (!isdigit(c) && !isOperator(c) && c != ' ' && c != '\n') {
            cout<<"输入非法字符，结果作废，请重新输入"<<endl; 
        }
		if(isdigit(c)){
			num = num*10 + (c - '0');
			is_num = true;
//			push(OPND, c); 
		}else if(c ==' '){
			if (is_num){
				push(OPND, num+'0');
				num =0;
				is_num=false;
			}
		}else if (isOperator(c)){

			if(isOperator(c)){
				int a,b;
				char temp;//取两个操作数出来，都用temp表示 
				pop(OPND, temp);
				b = temp - '0'; // 将字符转换为数字
	            pop(OPND, temp);
	            a = temp - '0'; // 将字符转换为数字
	            int result = operate(a, c, b); 
	            push(OPND, result + '0');//将结果转换为字符并压入操作数栈中 
			}
		}
//		// 清除输入缓冲区中的换行符
//        cin.ignore();
	}
	char resultChar;

	pop(OPND, resultChar);//最后操作数栈中的值就是结果 

	int result = resultChar -'0' ;
	if (OPND){
		cout<<"多数字："<<OPND->data<<endl; 
		cout<<"操作数过多，请重新输入"<<endl;//提示操作数过多 
	}
	DestroyStack(OPND);
	return result;
}
// 获取栈顶元素
char getTop(LinkStack LS) {
    if (!LS) {
        cout << "空栈，取不了栈顶" << endl;
        return '\0';
    }
    return LS->data;
}

// 判断运算符优先级
char precede(char op1, char op2) {
    if (op1 == '#') return '<';
    if (op1 == '(') {
    	if(op2 == ')') return '=';
    	else return'<';
	}
    if (op1 == '+' || op1 == '-') {
        if (op2 == '*' || op2 == '/' || op2 == '(') return '<';
        else return '>';
    }
    if (op1 == '*' || op1 == '/') {
        if (op2 == '(') return '<';
        else return '>';
    }
//    if (op1 == ')') {
//        if (op2 == '(') return '=';
//        else return '>';
//    }
//    return '>';
	return 'e';
}
// 中缀表达式计算
int EvaluateExpression() {
    LinkStack OPTR = NULL; // 运算符栈
    LinkStack OPND = NULL; // 操作数栈
    char c;
    int num = 0;//操作数表示多位 
    bool is_num = true;// 操作数表示多位 ,前一个为数字或空格的情况 
    int is_end;//对大于操作判断是否结束
	int result; 
    cout << "请一次性输入中缀表达式，每次输入都回车或空格确认你的输入（以#结束）："<<endl;
    cout<<"注意："<<endl; 
    cout<<"这里一定要两个##结尾！！！少摁了#就再摁一次#！！！"<<endl;
    push(OPTR, '#'); // 初始化运算符栈，压入结束符 '#'
    while ((c = getchar()) != '#' || getTop(OPTR) != '#') {    //这里 (c = getchar()) != '#'绝对不能写成 c = getchar() != '#'也就是省略了那个括号 
    	if (!isdigit(c) && !isOperator(c) && c != ' ' && c != '\n' && c!='(' && c!=')' && c!='#') {
	            cout<<"输入非法字符，结果作废，请重新输入"<<endl; 	
	        }
	    	
			is_end = 0;//对大于操作判断是否结束 
	        if (!isOperator(c) && c !='(' && c != ')' && c!='#') {
	            // 不是运算符则进操作数栈
	//            int num = 0;
	            if (isdigit(c)) {
	            	num = num * 10 +( c- '0');
	            	is_num = true;
	//                push(OPND, c);
	            }
	            else if (c == ' '){
	            	if(is_num){
	            		push(OPND ,num+'0');
	            		num = 0;
	            		is_num = false;
					}
				}
	     // 将数字转换为字符并压入操作数栈
	        } else {
	        	while(is_end ==0 ){
	        		switch (precede(getTop(OPTR), c)) {
	                case '<': // 栈顶元素优先权低
	                    push(OPTR, c);
						is_end = 1;
	                    break;
	                case '=': // 脱括号并接收下一字符
	                    char x;
	                    pop(OPTR, x);
	                    is_end = 1;

                    break;
                case '>': // 退栈并将运算结果入栈
                    char theta, b, a;
                    pop(OPTR, theta);
                    pop(OPND, b);
                    pop(OPND, a);
                    result = operate(a - '0', theta, b - '0');
                    push(OPND, result + '0'); // 将结果转换为字符并压入操作数栈
                    break;
                case 'e':
                	cout<<"括号匹配有误，输入有误"<<endl;
//                	DestroyStack(OPND);
//    				DestroyStack(OPTR);
//                	cin.ignore();
                	return 0;//结束 
//                	break;
            }
        		
			}
            
        }
    }

    char resultChar;
    pop(OPND, resultChar); // 最后操作数栈中的值就是结果
    result = resultChar - '0';
    if (OPND && OPND->data != '0'){
    	cout<<"多数字："<<OPND->data<<endl; 
		cout<<"操作数过多，请重新输入"<<endl;//提示操作数过多 
	}
    DestroyStack(OPND);
    DestroyStack(OPTR);
    return result;
}


int main(){
	
	while(true){
		char x;//这里使用x来使程序在Linux中暂停 
		showmenu();
		int select;
		int result;//结果 
		cout<<"请输入数字，代表你要执行的功能"<<endl;
		cin>>select;
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
				//波兰式计算
//				// 清除输入缓冲区中的换行符，不然会出现崩溃的错误！！！ 
        		cin.ignore();
				result = PolishCalcu();
				cout<<"结果是"<<result<<endl;
				
				break;
				
			case 2:
				//逆波兰式计算 
//				cin.ignore();
				result = InversePolishCalcu();
				cout<<"结果是"<<result<<endl;
				break;
			case 3:
				//中缀表达式计算
				cin.ignore();
                result = EvaluateExpression();
                cout << "结果是" << result << endl;
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
