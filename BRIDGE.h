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
#include "OPTIM.h"
#include "TARGET.h"
#import <Cocoa/Cocoa.h>




/*获取Token序列
 输入：无
 输出：Token序列（字符串）
 */
string getTokenResult() {
    string temp;
    int format = 15;
    for (int i = 0; i < token.size() - 1; i++) {
        string st = "<" + token[i].ORI + ">";
        temp += st;
        for (int j = (int)st.length(); j <= format; j ++) {
            temp += " ";
        }
        temp += "<" + token[i].FORMNAME + "," + intToString(token[i].No) + ">\n";
    }
    
    return temp;
}


/*获取符号表
 输入：无
 输出：符号表（字符串）
 */
string getSymbolResult() {
    string temp;
    int format = 20;
    for (int i = 0; i < symbol.size(); i++) {
        string st = intToString(i);
        temp += st;
        for (int i = (int)st.length(); i < format; i ++) temp += " ";
        
        st = symbol[i].NAME;
        temp += st;
        for (int i = (int)st.length(); i < format; i ++) temp += " ";
        
        st = symbol[i].TYP;
        temp += st;
        for (int i = (int)st.length(); i < format; i ++) temp += " ";
        
        st = symbol[i].CAT;
        temp += st;
        for (int i = (int)st.length(); i < format; i ++) temp += " ";
        temp += "\n";
    }
    
    return temp;
}


/*获取四元式序列
 输入：无
 输出：四元式序列（字符串）
 */
string getQuadResult(){
    string temp;
    int format = 10;
    for (int i = 0; i < quad.size(); i++){
        temp += "( ";
        string st;
        
        st = quad[i].first;
        temp += st;
        for (int i = (int)st.length(); i < format; i ++) temp += " ";

        st = quad[i].second;
        temp += st;
        for (int i = (int)st.length(); i < format; i ++) temp += " ";
        
        st = quad[i].third;
        temp += st;
        for (int i = (int)st.length(); i < format; i ++) temp += " ";
        
        st = quad[i].fourth;
        temp += st;
        for (int i = (int)st.length(); i < format; i ++) temp += " ";
        
        temp += ")\n";
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

