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


/*目标代码生成主程序
 输入：无
 输出：无
 */
void targetMain(){
    fillActive();
    
    
    
    
}

/*生成目标代码
 输入：无
 输出：无
 */
string generateTargetCode(){
    string target = "SSEG SEGMENT STACK\n";
    target += "STK DB 100 DUP (0)\n";
    target += "SSEG END\nDSEG SEGMENT\n";
    target += "DSEG SEGMENT\n";
    
    target += "DATA DB " + intToString(dataLength) + " DUP (0)";
    target += "DSEG END\n";
    target += "CSEG SEGMENT\n";
    target += "ASSUME CS:CSEG\n";
    target += "ASSUME SS:SSEG\n";
    target += "ASSUME DS:DSEG\n";


    string mainTarget = "";
    
    string * cursor = &mainTarget;      // 指向哪个函数需要加
    
    
    for (int i = 0; i < quad.size(); i++) {
        if (quad[i].first == "main") {
            *cursor += "main: MOV AX,DSEG\n";
            *cursor += "MOV DS,AX\n";
            *cursor += "MOV AX,SSEG\n";
            *cursor += "MOV SS,AX\n";
            *cursor += "MOV SP,SIZE STK\n";
            *cursor += "LEA SI,DATA\n";
        }
        else if ((quad[i].first == "=" && quad[i].second != "res")|| quad[i].first == ":"){
            mainTarget += "MOV";
        }
        else if (quad[i].first == "=" && quad[i].second == "res"){
            
        }
        else if (quad[i].first == "while"){
    
        }
        else if (quad[i].first == "end" && quad[i].second == "while"){
            
        }
        else if (quad[i].first == "if"){
            
        }
        else if (quad[i].first == "else"){
            
        }
        else if (quad[i].first == "end" && quad[i].second == "if"){
            
        }
        else if (quad[i].first == "call"){
            
        }
        else if (quad[i].first == "func"){
            
        }
        else if (quad[i].first == "rtn"){
            
        }
        else if (quad[i].first == "end" && quad[i].second == "func"){
            
        }
        else if (isArithmeticalOperator(quad[i].first)){     //算数运算符号
            
        }
        else if (isLogicalOperator(quad[i].first)){     //逻辑运算符号
            
        }
        else if (quad[i].first == ",") {
            
        }
        else if (quad[i].first == "end" && quad[i].second == "main"){
            *cursor += "MOV AH,4CH\n";
            *cursor += "INT 21H\n";
            *cursor += "CSEG ENDS\n";
            *cursor += "END MAIN\n";
        }
    }
    
    return target;
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
    int max_layer = 1;
    vector<int>layer;
    bool isFunc = false;
    for (int i = (int)quad.size()-1 ; i >= 0; i--){  //分程序块并标号
        if (quad[i].first == "end") layer.push_back(max_layer++);
        else if (isFunc && quad[i].first != ",") {
            isFunc = false;
            layer.pop_back();
        }
        
        quad[i].part= layer.back();
        if (quad[i].first == "if" || quad[i].first == "while") layer.pop_back();
        else if (quad[i].first == "func") isFunc = true;
    }
    
    for (int i = 1; i < max_layer; i++){
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




