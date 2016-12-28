//
//  target code.h
//  Goo
//
//  Created by 马驰也 on 2016/12/26.
//  Copyright © 2016年 马驰也. All rights reserved.
//

#ifndef target_code_h
#define target_code_h



#endif /* target_code_h */




/*获取可用过的寄存器
 输入：无
 输出：可用的寄存器的名字（字符串
 */
string availableReg(){
    
    if (REG.size() == 0) return "error";
    string temp = REG.back();
    REG.pop_back();
    
    return temp;
}

/*取值名字
 输入：要取值的元素（字符串）
 输出：无
 */
string addHash(string st) {
    if (isSymbol(st) != -1) return "" + st;
    else if(isConstant(st) != -1) return "#" + st;
    return "error";
}

/*临时变量的操作
 输入：临时变量名字（字符串）， 活跃信息（字符串）
 输出：无
 */
void tempVarOp(string varName, string active){
    bool isExist = false;
    vector<projectionElement>::iterator j;
    
    if (projection.size() != 0)
    for (j = projection.begin(); j != projection.end(); j++) {
        if (varName == (*j).VAR) {
            isExist = true;
            break;
        }
    }
    
    if (isExist){
        targetCode += (*j).REG;
        if (active == "N") {
            REG.push_back((*j).REG);
            projection.erase(j);
        }

    }
    else {
        projectionElement tempPE = {availableReg(), varName};
        targetCode += tempPE.REG;
        projection.push_back(tempPE);
    }
    
}

/*目标代码生成主程序
 输入：无
 输出：无
 */
void targetMain(){
    fillActive();
    generateTargetCode();    
}


/*生成目标代码
 输入：无
 输出：无
 */
void generateTargetCode(){
   
    
    for (int i = 0; i < quad.size(); i++) {
        
        if (quad[i].first == "main") {
            targetCode += "main:\n";
        }
        else if ((quad[i].first == "=" && quad[i].second != "res")|| quad[i].first == ":"){
            targetCode += "MOV @" + quad[i].fourth + ", ";
            if (quad[i].second == "true") targetCode += "#1";
            else if (quad[i].second == "false") targetCode += "#0";
            else if (isSymbol(quad[i].second) != -1 && symbol[isSymbol(quad[i].second)].CAT == "tv")
            {
                tempVarOp(quad[i].second, quad[i].ACT2);
            }
            else targetCode += addHash(quad[i].second);
            targetCode += "\n";
        }
        else if (quad[i].first == "=" && quad[i].second == "res"){
            targetCode += "POP A\n";
            targetCode += "MOV @" + addHash(quad[i].fourth) + ", A\n";
        }
        else if (quad[i].first == "while"){
            targetCode += quad[i].third + ":\n";
        }
        else if (quad[i].first == "end" && quad[i].second == "while"){
            targetCode += quad[i].third + ":\n";
        }
        else if (quad[i].first == "if"){
            //跳过
        }
        else if (quad[i].first == "else"){
            targetCode += quad[i].third + ":\n";
        }
        else if (quad[i].first == "end" && quad[i].second == "if"){
            targetCode += quad[i].third + ":\n";
        }
        else if (quad[i].first == "call"){
            for (int j = 0; j < parameter.size(); j++){
                if (parameter[j].NAME == quad[i].fourth) {
                    for (int l = 0; l < parameter[j].P.size(); l++){
                        targetCode += "PUSH " + addHash(parameter[j].P[l]) + "\n";
                    }
                    break;
                }
            }
            targetCode += "CALL " +addHash(quad[i].third) + "\n";
        }
        else if (quad[i].first == "func"){
            targetCode += "JMP " + quad[i].second + "\n\n";
            targetCode += quad[i].third + ":\n";
            for (int j = 0; j < parameter.size(); j++){
                if (parameter[j].NAME == quad[i].fourth) {
                    for (int l = 0; l < parameter[j].P.size(); l++){
                        targetCode += "POP " + addHash(parameter[j].P[l]) + "\n";
                    }
                    break;
                }
            }

        }
        else if (quad[i].first == "rtn"){
            targetCode += "PUSH " + addHash(quad[i].third) + "\n";
        }
        else if (quad[i].first == "end" && quad[i].second == "func"){
            targetCode += "RET\n\n";
            targetCode += quad[i].third + ":\n";
        }
        else if (isArithmeticalOperator(quad[i].first)){     //算数运算符号
            
            targetCode += "MOV A, ";
            if (isSymbol(quad[i].second) != -1 && symbol[isSymbol(quad[i].second)].CAT == "tv")
            {
                tempVarOp(quad[i].second, quad[i].ACT2);
            }
            else targetCode += addHash(quad[i].second);
            targetCode += "\n";
            
            if (quad[i].first == "-") targetCode += "SUB";
            else if (quad[i].first == "+") targetCode += "ADD";
            else if (quad[i].first == "*") targetCode += "MUL";
            else if (quad[i].first == "/") targetCode += "DIV";
            
            targetCode += " A, ";
            if (isSymbol(quad[i].third) != -1 && symbol[isSymbol(quad[i].third)].CAT == "tv")
            {
                tempVarOp(quad[i].third, quad[i].ACT3);
            }
            else targetCode += addHash(quad[i].third);
            targetCode += "\n";
            
            
            targetCode += "MOV ";
            if (isSymbol(quad[i].fourth) != -1 && symbol[isSymbol(quad[i].fourth)].CAT == "tv")
            {
                tempVarOp(quad[i].fourth, quad[i].ACT4);
            }
            else if (isSymbol(quad[i].fourth) != -1) {
                targetCode += "@" + quad[i].fourth;
            }
            else targetCode += "error\n";
            targetCode += ", A\n";
        }
        else if (isLogicalOperator(quad[i].first)){     //逻辑运算符号
            targetCode += "MOV A, ";
            if (isSymbol(quad[i].third) != -1 && symbol[isSymbol(quad[i].third)].CAT == "tv")
            {
                tempVarOp(quad[i].third, quad[i].ACT3);
            }
            else targetCode += addHash(quad[i].third);
            targetCode += "\n";
            
            targetCode += "CMP ";
            if (isSymbol(quad[i].second) != -1 && symbol[isSymbol(quad[i].second)].CAT == "tv")
            {
                tempVarOp(quad[i].second, quad[i].ACT2);
            }
            else targetCode += addHash(quad[i].second);
            targetCode += ", A\n";
            
            if (quad[i].first == ">") targetCode += "JNA " + quad[i].fourth + "\n";
            else if (quad[i].first == "<") targetCode += "JNB " + quad[i].fourth + "\n";
            else if (quad[i].first == "<=") targetCode += "JA " + quad[i].fourth + "\n";
            else if (quad[i].first == ">=") targetCode += "JB " + quad[i].fourth + "\n";
            else if (quad[i].first == "==") targetCode += "JNE " + quad[i].fourth + "\n";
        }
        else if (quad[i].first == ",") {
            bool isExist = false;
            for (int j = 0; j < parameter.size(); j++) {
                if (parameter[j].NAME == quad[i].second) {
                    parameter[j].NAME = quad[i].fourth;
                    parameter[j].P.push_back(quad[i].third);
                    isExist = true;
                    break;
                }
            }
            if (!isExist) {
                parameterElement tempPE= {quad[i].fourth,{quad[i].second, quad[i].third}};
                parameter.push_back(tempPE);
            }
        }
        else if (quad[i].first == "end" && quad[i].second == "main"){
            targetCode += "INT \n";
            targetCode += "MAIN END\n";
         }
        
//        cout << "( " << quad[i].first << ", " << quad[i].second << ", " << quad[i].third << ", " << quad[i].fourth << " )" << endl;
//        cout << targetCode << endl;
//        targetCode = "";
    }
}







/*初始化活跃信息
 输入：无
 输出：无
 */
void fillActiveInit(){    //临时变量的活动先赋值N，其余先赋值Y
    for (int i =0; i < symbol.size(); i ++){
        if (symbol[i].CAT == "v" || symbol[i].CAT == "c" || symbol[i].CAT == "vf") symbol[i].ACT = "Y";
        else if (symbol[i].CAT == "tv") symbol[i].ACT = "N";
    }

}


/*填写活跃信息
 输入：无
 输出：无
 */
void fillActive(){
    int maxPart = 0;
    bool isIf = false;
    bool isWhile = false;
    for (int i = 0; i < quad.size(); i++){  //分程序块并标号
        if (isIf && quad[i].fourth.substr(0,4) != "else") {
            isIf = false;
            maxPart++;
        }
        else if (isWhile && quad[i].fourth.substr(0,3) != "end") {
            isWhile = false;
            maxPart++;
        }
        else if (quad[i].first == "main" || quad[i].first == "func" || quad[i].first == "end" || quad[i].first == "else") maxPart++;

        
        quad[i].part= maxPart;
        if (quad[i].first == "if")  isIf = true;
        else if (quad[i].first == "while") isWhile = true;
    }
    
    
    for (int i = 1; i < maxPart; i++){
        fillActiveInit();
        for (int j = (int)quad.size()-1; j >= 0; j--){
            if (quad[j].part == i) {
                int temp = isSymbol(quad[j].second);
                if (temp != -1) {
                    if (symbol[temp].CAT == "v" || symbol[temp].CAT == "vf" || symbol[temp].CAT == "c" || symbol[temp].CAT == "tv"){
                        quad[j].ACT2 = symbol[temp].ACT;
                        symbol[temp].ACT = "Y";
                        
                    }
                }
                temp = isSymbol(quad[j].third);
                if (temp != -1) {
                    if (symbol[temp].CAT == "v" || symbol[temp].CAT == "vf" || symbol[temp].CAT == "c" || symbol[temp].CAT == "tv"){
                        quad[j].ACT3 = symbol[temp].ACT;
                        symbol[temp].ACT = "Y";
                        
                    }
                }
                temp = isSymbol(quad[j].fourth);
                if (temp != -1) {
                    if (symbol[temp].CAT == "v" || symbol[temp].CAT == "vf" || symbol[temp].CAT == "c" || symbol[temp].CAT == "tv"){
                        quad[j].ACT4 = symbol[temp].ACT;
                        symbol[temp].ACT = "N";
                    }
                }

            }
        }
    }
    
}




