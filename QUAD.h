//
// Created by 马驰也 on 2016/12/22.
//

#ifndef GOO_FOUR_ELEMENT_TYPE_H
#define GOO_FOUR_ELEMENT_TYPE_H

#endif //GOO_FOUR_ELEMENT_TYPE_H

vector<int> quadLine;

/*生成四元式主程序
 输入：无
 输出：无
 */
void quadMain(){
    action.push_back("#");
    int i = 0;
    while (i < token.size() - 1){

        //cout << token[i].ori<< endl;
        if (token[i].ORI == ";" && (action.back() == "=" || action.back() == "#") && identifier.size()>0){      //针对函数调用特殊写的
            if (identifier.back()[0] == 'p'){
                quadElement temp;
                temp.first = "call";
                if (action.back() == "=") temp.second = "res"; //如果语义动作栈是=，保留返回值
                temp.fourth = identifier.back();
                identifier.pop_back();
                temp.third = identifier.back();
                identifier.pop_back();
                if (action.back() == "=") identifier.push_back("res");  //如果语义动作栈是=，保留返回值
                quad.push_back(temp);
                //outputState();
            }
        }


        if (token[i].FORMNAME == "K" || token[i].FORMNAME
                                        == "D")  { //如果是关键字或者界符的话
            if(isPrior(action.back(),token[i].ORI)) {
                if (action.back() == "#") i++;
                else doAction(action.back());
            }
            else {
                action.push_back(token[i].ORI);
                quadLine.push_back(token[i].LINE);
                i++;
            }
        }
        else {  //如果是标识符的话
            identifier.push_back(token[i].ORI);
            i++;
        }
        //outputState();
    }

    doAction(action.back());
    
    if (errorMessage == ""){
        vector<quadElement>::iterator it;
        for (it = quad.begin(); it != quad.end(); it++){
            if ((*it).first == "=") {
                if (isSymbol((*it).fourth) == -1) outputCurrentLine((*it).LINE, "常数无法被赋值");
                else if (isSymbol((*it).second) != -1) {
                    if (symbol[isSymbol((*it).fourth)].TYP == "bool"){
                        if (whatsTheType((*it).second) == "int") outputCurrentLine((*it).LINE, "类型冲突，整型->布尔型");
                        else if (whatsTheType((*it).second) == "real") outputCurrentLine((*it).LINE, "类型冲突，实型变->布尔型");
                    }
                    else if (whatsTheType((*it).fourth) == "int"){
                        if (whatsTheType((*it).second) == "real") outputCurrentLine((*it).LINE, "类型冲突，实型->整型");
                    }
                    else if (whatsTheType((*it).fourth) == "const") outputCurrentLine((*it).LINE, "常量无法被再次赋值");
                }
                else if (whatsTheType((*it).fourth) == "const") outputCurrentLine((*it).LINE, "常量无法被再次赋值");
                else if (whatsTheType((*it).second) == "real" && symbol[isSymbol((*it).fourth)].TYP == "int") outputCurrentLine((*it).LINE, "类型冲突，实型->整型");
                else if (whatsTheType((*it).second) == "real" && symbol[isSymbol((*it).fourth)].TYP == "bool") outputCurrentLine((*it).LINE, "类型冲突，实型->布尔型");
                else if (whatsTheType((*it).second) == "int" && symbol[isSymbol((*it).fourth)].TYP == "bool") outputCurrentLine((*it).LINE, "类型冲突，整型->布尔型");
            }
            else if ((*it).first == ":") {
                if (isSymbol((*it).fourth) == -1) outputCurrentLine((*it).LINE, "常数无法被赋值");
                else if (whatsTheType((*it).fourth) != "const") outputCurrentLine((*it).LINE, "该类型变量无法做：运算");
            }
        }
    }
    
    if (errorMessage == "") targetMain();
}


/*判断语义动作优先级
 输入：语义动作栈顶元素(字符串），下一个元素（字符串）
 输出：如果语义动作栈顶元素优先则返回TRUE
 */
bool isPrior(string st1, string st2){     //st1是语义动作栈顶元素，st2是下一个元素
    if (st1 == "func") {
        if(st2 == ")") return true;
        else if (st2 == "(") return false;
    }
    else if (st1 == "rtn"){
        if (st2 == ";") return true;
    }
    else if (st1 == "end"){
        return true;
    }
    else if (st1 == "if"){
        if (st2 == "(") return true;
    }
    else if (st1 == "else"){
        return true;
    }
    else if (st1 == "while"){
        if (st2 == "(") return true;
    }
    else if (st1 == "main"){
        return true;
    }
    else if (st1 == ","){
        if (st2 == ")") return true;
    }
    else if (st1 == ":"){
        if (st2 == ";") return true;
    }
    else if (st1 == "="){
        if (st2 == ";")
            return true;
        else if (st2 == "(" || st2 == ")" || st2 == "+"  || st2 == "-"  || st2 == "*"  || st2 == "/") return false;
    }
    else if (st1 == "*" || st1 == "/"){
        if (st2 == ")" || st2 == "+" || st2 == "-" || st2 == "*" || st2 == "/" || st2 == ";" || st2 == ">" || st2 == "<" || st2 == ">=" || st2 == "<=" || st2 == "==") return true;
        else if (st2 == "(") return false;
    }
    else if (st1 == "+" || st1 == "-"){
        if (st2 == ")"  || st2 == "+" || st2 == "-" || st2 == ";" || st2 == ">" || st2 == "<" || st2 == ">=" || st2 == "<=" || st2 == "==") return true;
        else if (st2 == "(" ||st2 == "*"  || st2 == "/") return false;
    }
    else if (st1 == "."){

    }
    else if (st1 == "("){
        if (st2 == ")") return true;
        else if (st2 =="," || st2 =="(" || st2 == ">" || st2 == "<" || st2 == ">=" || st2 == "<=" || st2 == "==" || st2 == "+" || st2 == "-" || st2 == "*" || st2 == "/" ) return false;
    }
    else if (st1 == ")"){
        if (st2 == ";" || st2 == ">" || st2 == "<" || st2 == ">=" || st2 == "<=" || st2 == "==" || st2 == "+" || st2 == "-" || st2 == "*" || st2 == "/") return true;
    }
    else if (st1 == "["){

    }
    else if (st1 == "]"){

    }
    else if (st1 == "\""){

    }
    else if (st1 == ">" || st1 == "<" || st1 == ">=" || st1 == "<=" || st1 == "=="){
        if (st2 == ")") return true;
        else if (st2 == "(") return false;

    }
    else if (st1 == ";"){

    }
    else if (st1 == "#"){
        if (st2 == "main") return false;
        else if (st2 == ")" || st2 == ";")return true;
        else return false;
    }
    cout << "两个关键字或界符" << st1 << "," << st2 << "从未出现" << endl;
    return true;
}


/*根据语义动作生成四元式
 输入：语义动作栈顶元素(字符串））
 输出：无
 */
void doAction(string st1) {
    quadElement temp;
    if (st1 == "func") {
        temp.first = "func";
        temp.LINE = quadLine.back();
        temp.fourth = identifier.back();
        identifier.pop_back();
        temp.third = identifier.back();
        identifier.pop_back();
        withend_stack.push_back("func");
        
        char end_char = end_number +'0';
        temp.second = "end";
        temp.second += end_char;
        end_number++;
        end_stack.push_back(temp.second);
        
        quad.push_back(temp);
    }
    else if (st1 == "rtn"){
        temp.first = "rtn";
        temp.LINE = quadLine.back();
        temp.third = identifier.back();
        identifier.pop_back();

        quad.push_back(temp);
    }
    else if (st1 == "end"){
        temp.first = "end";
        temp.LINE = quadLine.back();
        temp.second = withend_stack.back();
        withend_stack.pop_back();

        if (temp.second == "if" || temp.second == "while" || temp.second == "func") {
            temp.third = end_stack.back();
            end_stack.pop_back();
        }
        if (temp.second == "while") {
            temp.fourth = while_stack.back();
            while_stack.pop_back();
        }

        quad.push_back(temp);

    }
    else if (st1 == "if"){
        temp.first = "if";
        temp.LINE = quadLine.back();
        quad.push_back(temp);
        withend_stack.push_back("if");
    }
    else if (st1 == "else"){
        temp.first = "else";
        temp.LINE = quadLine.back();
        temp.third = else_stack.back();
        else_stack.pop_back();

        char end_char = end_number +'0';
        temp.fourth = "end";
        temp.fourth += end_char;
        end_number++;
        end_stack.push_back(temp.fourth);

        quad.push_back(temp);
    }
    else if (st1 == "while"){
        temp.first = "while";
        temp.LINE = quadLine.back();
        char while_char = while_number +'0';
        temp.third = "while";
        temp.third += while_char;
        while_number++;
        while_stack.push_back(temp.third);

        withend_stack.push_back("while");
        quad.push_back(temp);
    }
    else if (st1 == "main"){
        temp.first = "main";
        temp.LINE = quadLine.back();
        withend_stack.push_back("main");

        quad.push_back(temp);
    }
    else if (st1 == ","){
        temp.first = ",";
        temp.LINE = quadLine.back();
        temp.third = identifier.back();
        identifier.pop_back();
        temp.second = identifier.back();
        identifier.pop_back();
        char p_char = p_number +'0';
        temp.fourth = "p";
        temp.fourth += p_char;
        p_number++;
        p_stack.push_back(temp.fourth);
        identifier.push_back(temp.fourth);
        quad.push_back(temp);
    }
    else if (st1 == ":"){
        temp.first = ":";
        temp.LINE = quadLine.back();
        temp.second = identifier.back();
        identifier.pop_back();
        temp.fourth = identifier.back();
        identifier.pop_back();
        quad.push_back(temp);
    }
    else if (st1 == "="){
        temp.first = "=";
        temp.LINE = quadLine.back();
        temp.second = identifier.back();
        identifier.pop_back();
        temp.fourth = identifier.back();
        identifier.pop_back();
        quad.push_back(temp);
    }
    else if (st1 == "*" || st1 == "/" || st1 == "+" || st1 == "-"){
        symbolElement tempSE;
        tempSE.CAT = "tv";
        tempSE.ORI = 0;
        
        temp.first = st1;
        temp.LINE = quadLine.back();
        temp.third = identifier.back();
        identifier.pop_back();
        temp.second = identifier.back();
        identifier.pop_back();
        
        if (whatsTheType(temp.third) == "real" || whatsTheType(temp.second) == "real") tempSE.TYP = "real";
        else tempSE.TYP = "int";

        char t_char = t_number +'0';
        temp.fourth = 't';
        temp.fourth += t_char;
        tempSE.NAME = temp.fourth;
        symbol.push_back(tempSE);
        t_number++;
        t_stack.push_back(temp.fourth);
        identifier.push_back(temp.fourth);

        quad.push_back(temp);
    }
    else if (st1 == "."){

    }
    else if (st1 == "("){
    }
    else if (st1 == ")"){
    }
    else if (st1 == "["){

    }
    else if (st1 == "]"){

    }
    else if (st1 == "\""){

    }
    else if (st1 == ">" || st1 == "<" ||st1 == ">=" || st1 == "<=" || st1 == ";") {
        temp.first = st1;
        temp.LINE = quadLine.back();
        temp.third = identifier.back();
        identifier.pop_back();
        temp.second = identifier.back();
        identifier.pop_back();

        if (withend_stack.back() == "if") {
            char else_char = else_number +'0';
            temp.fourth = "else";
            temp.fourth += else_char;
            else_number++;
            else_stack.push_back(temp.fourth);
        }
        else if (withend_stack.back() == "while") {
            char end_char = end_number +'0';
            temp.fourth = "end";
            temp.fourth += end_char;
            end_number++;
            end_stack.push_back(temp.fourth);
        }



        quad.push_back(temp);
    }
    else if (st1 == ";"){
        action.pop_back();
        quadLine.pop_back();
    }

    action.pop_back();
    quadLine.pop_back();
    return;
}


/*输出当前状态（测试用）
 输入：无
 输出：无
 */
void outputState(){
    int i;
    
    
    cout << "标识符或常量: ";
    for (i = 0; i < identifier.size(); i++) cout << " <" << identifier[i] << "> ";
    cout << endl;
    
    cout << "关键字或界符: ";
    for (i = 0; i < action.size(); i++) cout << " <" << action[i] << "> ";
    cout << endl;
    
    cout << "有end的栈: ";
    for (i = 0; i < withend_stack.size(); i++) cout << " <" << withend_stack[i] << "> ";
    cout << endl;
    
    if (quad.size()>0) cout << "(" << quad.back().first << "," << quad.back().second << "," << quad.back().third << "," << quad.back().fourth << ")" << endl;
    
    cout << endl;
    
    
}


/*输出结果（测试用）
 输入：无
 输出：无
 */
void outputResult(){
    cout << endl;
    cout << "生成的四元式为：" << endl;
    for (int i = 0; i < quad.size(); i++){
        cout << "(" << quad[i].first << "," << quad[i].second << "," << quad[i].third << "," << quad[i].fourth << ")" << endl;
    }
    
}


