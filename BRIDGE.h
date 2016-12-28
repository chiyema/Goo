//
//  Header.h
//  Goo
//
//  Created by 马驰也 on 2016/12/27.
//  Copyright © 2016年 马驰也. All rights reserved.
//

#ifndef BRDIGE_h
#define BRIDGE_h


#endif /* Header_h */

#include "BASE.h"
#include "MORPHOLOGY.h"
#include "QUAD.h"
#include "GRAMMAR.h"
#include "TARGET.h"


/*获取Token序列
 输入：无
 输出：Token序列（字符串）
 */
string getTokenResult() {
    string temp;
    for (int i = 0; i < token.size(); i++) {
        temp += "<" + token[i].ORI + "> ";
        temp += "<" + token[i].FORMNAME + "," + intToString(token[i].No) + "," + intToString(token[i].LINE) + ">\n";
    }
    
    return temp;
}


/*获取符号表
 输入：无
 输出：符号表（字符串）
 */
string getSymbolResult() {
    string temp;
    
    for (int i = 0; i < symbol.size(); i++) {
        temp += intToString(i) + "  " + symbol[i].NAME + "  " + symbol[i].TYP + "  " + symbol[i].CAT  + "  " + intToString(symbol[i].ORI) + "\n";
    }
    
    return temp;
}


/*获取四元式序列
 输入：无
 输出：四元式序列（字符串）
 */
string getQuadResult(){
    string temp;
    for (int i = 0; i < quad.size(); i++){
        temp += "(" + quad[i].first + "," + quad[i].second + "," + quad[i].third + "," + quad[i].fourth + "," + intToString(quad[i].part) + "," + quad[i].ACT1 + "," + quad[i].ACT2 + "," + quad[i].ACT3 + "," + quad[i].ACT4 + ")\n";
    }
    return temp;
}


/*获取错误信息
 输入：无
 输出：错误信息（字符串）
 */
string getErrorResult(){
    string temp = "";
    if (errorMessage != "") {
        temp = errorLocation + errorMessage;
    }
    return temp;
}

/*获取目标代码
 输入：无
 输出：目标代码（字符串）
 */
string getTargetResult(){
    return targetCode;
}

