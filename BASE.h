//
// Created by 马驰也 on 2016/11/14.
//

#ifndef EXPRESSION_SCANNER_UNIVERSAL_VARIABLES_H
#define EXPRESSION_SCANNER_UNIVERSAL_VARIABLES_H

#endif //EXPRESSION_SCANNER_UNIVERSAL_VARIABLES_H
#include <string>
#include <vector>

#include<iostream>
#include<stdio.h>
#include<iomanip>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


#define file_location "/Users/machiye/Desktop/test.txt" //输入语句所在文件位置

/*Token序列中的元素的结构体*/
typedef struct tokenElement {
    string FORMNAME;    //所在表的名字
    int No;             //所在表中的位置
    string ORI;         //原本的元素
    int LINE;           //行数
}tokenElement;

/*符号表的元素的结构体*/
typedef struct symbolElement {
    string NAME;    //元素内容
    string TYP;     //元素类型
    string CAT;     //元素分类
    tokenElement ADDR;      //元素地址
    string ACT;     //元素活跃信息
    int ORI;     //存储起始位置
}symbolElement;

/*四元式的元素的结构体*/
typedef struct quadElement {
    string first;   //第一个元素
    string second;  //第二个元素
    string third;   //第三个元素
    string fourth;  //第四个元素
    int part;       //所属代码块
    string ACT1;    //第一个元素活跃信息
    string ACT2;    //第二个元素活跃信息
    string ACT3;    //第三个元素活跃信息
    string ACT4;    //第四个元素活跃信息
    int LINE;
}quadElement;

/*参数集合的结构体*/
typedef struct parameterElement {
    string NAME;
    vector<string> P;
}parameterElement;

/*临时变量与寄存器对应关系的结构体*/
typedef struct projectionElement{
    string REG;
    string VAR;
}projectionElement;

string keyList[7] = {"func","rtn","end","if","else","while","main"};
string delimiterList[19] = {",",":","=","*","/","+","-",".","(",")","[","]","\"",">","<",">=","<=","==",";"};


int currentLine = 1; //当前行数
int dataLength;     //数据长度

vector<tokenElement> token; //token序列
vector<symbolElement> symbol; //符号表
vector<string> constl;//常数表


vector<string> identifier; //标识符或常量栈
vector<string> action; //语义动作(关键字、界符)栈
vector<string> withend_stack; //包含end文法栈

vector<quadElement> quad; //四元式栈

int p_number = 1;   //记录p的个数，参数
vector<string> p_stack;     //p的栈

int t_number = 1;   //记录t的个数，表达式
vector<string> t_stack;     //t的栈

int else_number = 1;   //记录else的个数
vector<string> else_stack;     //else的栈

int end_number = 1;   //记录end的个数
vector<string> end_stack;     //end的栈

int while_number = 1;   //记录end的个数
vector<string> while_stack;     //end的栈

string errorMessage;    //错误信息
string errorLocation;   //错误位置

string targetCode;      //目标代码

vector<parameterElement> parameter;     //参数表

vector<string> REG;     //寄存器

vector<projectionElement> projection;   //临时变量与寄存器对应关系


/*判断是不是算数运算符号
 输入：待检测元素（字符串）
 输出：是否（布尔型）
 */
bool isArithmeticalOperator(string st) { 
    if (st == "+" || st == "-" || st == "*" || st == "/") return true;
    else return false;
}



/*判断是不是逻辑运算符号
 输入：待检测元素（字符串）
 输出：是否（布尔型）
 */
bool isLogicalOperator(string st) {
    if (st == ">" || st == "<" || st == ">=" || st == "<=" || st == "==") return true;
    else return false;
}


/*将整型转化成字符串
 输入：数字（整型）
 输出：字符串（字符串）
 */
string intToString(int temp){
    string result;
    
    if (temp == 0) return "0";
    while (temp != 0) {
        char ch = temp % 10 + '0';
        result = ch + result;
        temp = temp / 10;
    }
    return result;
}


/*判断是不是字母
 输入：待检测元素（字符）
 输出：是否（布尔型）
 */
bool isCharacter(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ) return true;
    else return false;
}


/*判断是不是数字
 输入：待检测元素（字符）
 输出：是否（布尔型）
 */
bool isNumber(char ch) {
    if (ch >= '0' && ch <= '9') return true;
    else return false;
}


/*判断是不是小数
 输入：待检测元素（字符串）
 输出：是否（布尔型）
 */
bool isDecimal(string st) {
    for (int i = 0; i < st.length(); i++) {
        if (st[i] == '.') return true;
    }
    return false;
}


/*判断数据类型
 输入：待检测元素（字符串）
 输出：类型（字符串）
 */
string whatsTheType(string st) {
    if (isSymbol(st) != -1) return symbol[isSymbol(st)].TYP;
    else if (st == "true" || st == "false") return "bool";
    else if (isDecimal(st)) return "real";
    else return "int";
}


/*判断是否是符号
 输入：待检测元素（字符串）
 输出：若是返回编号，不是返回-1（整型）
 */
int isSymbol(string st){
    for (int i = 0; i < symbol.size(); i++){
        if (st == symbol[i].NAME) return i;
    }
    return -1;
}


/*判断是否是常数
 输入：待检测元素（字符串）
 输出：若是返回编号，不是返回-1（整型）
 */
int isConstant(string st){
    for (int i = 0; i < constl.size(); i++){
        if (st == constl[i]) return i;
    }
    return -1;
}

/*判断是否是Token元素
 输入：待检测元素（字符串）
 输出：若是返回编号，不是返回-1（整型）
 */
int isToken(string st){
    for (int i = 0; i < token.size(); i++){
        if (st == token[i].ORI) return i;
    }
    return -1;
}


/*输出错误信息
 输入：错误行数（整型），错误类型（字符串）
 输出：无
 */
void outputCurrentLine (int LINE, string errorType) {
    if (errorMessage == ""){
        if (LINE == -1) {
            errorLocation = "";
            errorMessage = "错误信息：" + errorType;
        }
        else {
            errorMessage = "\n错误信息：" + errorType;
            errorLocation = "错误位置（第 " + intToString(LINE) +" 行）: ";
            //        cout << "错误位置（第 " << LINE << " 行）: ";
            for (int i = 0; i < token.size(); i++) {
                if (token[i].LINE == LINE) {
                    errorLocation += token[i].ORI + " ";
                    //                cout << token[i].ORI << " ";
                }
            }
            //        cout << endl << "错误信息：";
        }

    }
}
