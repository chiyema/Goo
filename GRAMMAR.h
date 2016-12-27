

#ifndef GOO_GRAMMAR_SCANNER_H
#define GOO_GRAMMAR_SCANNER_H

#endif //GOO_GRAMMAR_SCANNER_H





void outputCurrentLine (int LINE) {
    if (errorLocation == ""){
        errorLocation = "错误位置（第 " + intToString(LINE) +" 行）: ";
//        cout << "错误位置（第 " << LINE << " 行）: ";
        for (int i = 0; i < token.size(); i++) {
            if (token[i].LINE == LINE) {
                errorLocation += token[i].ORI + " ";
//                cout << token[i].ORI << " ";
            }
        }
        errorLocation += "\n错误信息：";
//        cout << endl << "错误信息：";
    }
}

/*文法分析主程序
 输入：无
 输出：无
 */
void grammarMain(){
    errorLocation = "";
    errorMessage = "";
    P(0);
    //cout << "开始进行语法分析..." << endl;
    //if (P(0)) cout << "语法符合!" << endl;
    //else cout << "语法不符合！" << endl;
}


/*递归下降子程序的各个函数
*/
bool P(int current) {
//    cout << "从" << token[current].ORI << "开始匹配P" << endl;
    string st = "P->main ( ) C end";
    if (token[current].ORI == "main"){
        current ++;
        if (token[current].ORI== "("){
            current ++;
            if (token[current].ORI == ")"){
                current ++;
                int temp = C(current);
                if (temp) {
                    current = temp;
                    if (token[current].ORI == "end") {
//                        cout << "成功匹配到" << st << endl;
                        return true;
                    }
                    else st = "缺少与main对应的end";
                }
            }
            else st = "缺少 )";
        }
        else st = "缺少 (";
    }
    else st = "缺少 main";


    if (token[current].LINE != token[current-1].LINE) outputCurrentLine(token[current-1].LINE);
    else outputCurrentLine(token[current].LINE);
    cout << st << endl;
    if (errorMessage == "") errorMessage = st + "\n";
    //exit(0);
    return false;
}

int F(int current) {
//    cout << "从" << token[current].ORI << "开始匹配F" << endl;
    string st = "F->func S ( V ) C rtn E ; end";
    if (token[current].ORI == "func"){
        current ++;
        if (token[current].FORMNAME == "S"){
            current ++;
            if (token[current].ORI == "("){
                current++;
                int temp = V(current);
                if (temp) {
                    current = temp;
                    if (token[current].ORI == ")") {
                        current++;
                        int temp = C(current);
                        if (temp) {
                            current = temp;
                            if (token[current].ORI == "rtn") {
                                current++;
                                int temp =E(current);
                                if (temp) {
                                    current = temp;
                                    if (token[current].ORI == ";") {
                                        current++;
                                        if (token[current].ORI == "end") {
                                            current++;
//                                            cout << "成功匹配到" << st << endl;
                                            return current;
                                        }
                                        else st = "缺少 end";
                                    }
                                    else st = "缺少 ;";
                                }
                            }
                            else st = "缺少 rtn";
                        }
                    }
                    else st = "缺少 )";
                }
                else st = "缺少函数参数";
            }
            else st = "缺少 (";
        }
        else st = st + " | current: <" + token[current].ORI + "> , 缺少函数名";
        if (token[current].LINE != token[current-1].LINE) outputCurrentLine(token[current-1].LINE);
        else outputCurrentLine(token[current].LINE);
        cout << st << endl;
        if (errorMessage == "") errorMessage = st + "\n";
//        exit(0);
    }

    return 0;
}

int C(int current) {
//    cout << "从" << token[current].ORI << "开始匹配C" << endl;
    string st = "C->C' C";
    int temp = C1(current);
    if (temp) {
        current = temp;
        int temp = C(current);
        if (temp) {
            current = temp;
//            cout << "成功匹配到" << st << endl;
            return current;
        }
    }
    else {
//        cout << "成功匹配到C->~" << endl;
        return current;
    }

    return 0;
}

int C1(int current) {
//    cout << "从" << token[current].ORI << "开始匹配C'" << endl;
    string st;
    if (token[current].FORMNAME == "S") {
        st = "C'->S A ;";
        current++;
        int temp = A(current);
        if (temp) {
            current = temp;
            if (token[current].ORI == ";"){
                current++;
//                cout << "成功匹配到" << st << endl;
                return current;
            }
            else st = "缺少 ;";
            if (token[current].LINE != token[current-1].LINE) outputCurrentLine(token[current-1].LINE);
            else outputCurrentLine(token[current].LINE);
            cout << st << endl;
            if (errorMessage == "") errorMessage = st + "\n";
//            exit(0);
            return 0;
        }
        current--;
    }

    int temp = I(current);
    if (temp) {
        st = "C'->I";
        current = temp;
//        cout << "成功匹配到" << st << endl;
        return current;
    }

    temp = W(current);
    if (temp) {
        st = "C'->W";
        current = temp;
//        cout << "成功匹配到" << st << endl;
        return current;
    }

    /*
    temp = V(current);
    if (temp) {
        st = "C'->V";
        current = temp;
//        cout << "成功匹配到" << st << endl;
        return current;
    }*/

    temp = F(current);
    if (temp) {
        st = "C'->F";
        current = temp;
//        cout << "成功匹配到" << st << endl;
        return current;
    }

    if (current == token.size()) {

    }
    else if (token[current].FORMNAME != "K" && token[current].FORMNAME != "D" && token[current].FORMNAME != "C") {
        if ((token[current].FORMNAME == "S" && symbol[token[current].No].TYP == "") || token[current].FORMNAME != "S") {
            outputCurrentLine(token[current].LINE);
            cout << "未定义 " << token[current].ORI << endl;
            if (errorMessage == "") errorMessage = "未定义 " + token[current].ORI + "\n";
//            exit(0);
        }
        else if (symbol[token[current].No].CAT == "p"){
            outputCurrentLine(token[current].LINE);
            cout << "没有保存函数返回值"<< endl;
            if (errorMessage == "") errorMessage = "没有保存函数返回值\n";
//            exit(0);
        }
        else {
            outputCurrentLine(token[current].LINE);
            cout << "未进行任何操作"<< endl;
            if (errorMessage == "") errorMessage = "未进行任何操作\n";
//            exit(0);
        }
    }
    return 0;
}

int A(int current) {
//    cout << "从" << token[current].ORI << "开始匹配A" << endl;
    string st;

    if (token[current].ORI == "="){
        st = "A->= E";
        current++;
        int temp = E(current);
        if (temp) {
            current = temp;
//            cout << "成功匹配到" << st << endl;
            return current;

        }
    }
    else if (token[current].ORI == ":"){
        st = "A->: E";
        current++;
        int temp = E(current);
        if (temp) {
            current = temp;
//            cout << "成功匹配到" << st << endl;
            return current;
        }
    }

    return 0;
}

int I(int current) {
//    cout << "从" << token[current].ORI << "开始匹配I" << endl;
    string st = "I->if ( I' ) C else C end";
    if (token[current].ORI == "if"){
        current ++;
        if (token[current].ORI == "("){
            current++;
            int temp = I1(current);
            if (temp) {
                current = temp;
                if (token[current].ORI == ")") {
                    current++;
                    int temp = C(current);
                    if (temp) {
                        current = temp;
                        if (token[current].ORI == "else") {
                            current++;
                            int temp = C(current);
                            if (temp) {
                                current = temp;
                                if (token[current].ORI == "end") {
                                    current++;
//                                    cout << "成功匹配到" << st << endl;
                                    return current;
                                } else st = "缺少 end";
                            }
                        } else st = "缺少 else";
                    }
                } else st = "缺少 )";
            }
        }
        else st = "缺少 (";
        if (token[current].LINE != token[current-1].LINE) outputCurrentLine(token[current-1].LINE);
        else outputCurrentLine(token[current].LINE);
        cout << st << endl;
        if (errorMessage == "") errorMessage = st + "\n";
//        exit(0);

    }

    return 0;
}

int W(int current) {
//    cout << "从" << token[current].ORI << "开始匹配W" << endl;
    string st = "W->while ( I' ) C end";
    if (token[current].ORI == "while"){
        current ++;
        if (token[current].ORI == "("){
            current++;
            int temp = I1(current);
            if (temp) {
                current = temp;
                if (token[current].ORI == ")"){
                    current++;
                    int temp = C(current);
                    if (temp) {
                        current = temp;
                        if (token[current].ORI == "end") {
                            current++;
//                            cout << "成功匹配到" << st << endl;
                            return current;
                        }
                        else st = "缺少 end";
                    }
                }
                else st = "缺少 )";
            }
        }
        else st = "缺少 (";

        if (token[current].LINE != token[current-1].LINE) outputCurrentLine(token[current-1].LINE);
        else outputCurrentLine(token[current].LINE);
        cout << st << endl;
        if (errorMessage == "") errorMessage = st + "\n";
//        exit(0);
    }

    return 0;
}

int V(int current) {
//    cout << "从" << token[current].ORI << "开始匹配V" << endl;
    string st = "V->S V'";
    if (token[current].FORMNAME == "S") {
        current++;
        int temp = V1(current);
        if (temp) {
            current = temp;
//            cout << "成功匹配到" << st << endl;
            return current;
        }

    }
    return 0;
}

int V1(int current) {
//    cout << "从" << token[current].ORI << "开始匹配V'" << endl;
    string st = "V'->, S V'";
    if (token[current].ORI == ","){
        current ++;
        if (token[current].FORMNAME == "S") {
            current++;
            int temp = V1(current);
            if (temp) {
                current = temp;
//                cout << "成功匹配到" << st << endl;
                return current;
            }
        }
    }
    else {
//        cout << "成功匹配到V'->~" << endl;
        return current;
    }
    return 0;
}

int E(int current) {
//    cout << "从" << token[current].ORI << "开始匹配E" << endl;
    string st;

    if (token[current].FORMNAME == "S"  && symbol[token[current].No].CAT != ""){
        st = "E->S ( D D' )";
        current++;
        if (token[current].ORI == "("){
            current++;
            int temp = D(current);
            if (temp) {
                current = temp;
                int temp = D1(current);
                if (temp) {
                    current = temp;
                    if (token[current].ORI == ")"){
                        current++;
//                        cout << "成功匹配到" << st << endl;
                        return current;
                    }
                    else st = "缺少 )";
                }
            }
            else st = "缺少函数参数";
            if (token[current].LINE != token[current-1].LINE) outputCurrentLine(token[current-1].LINE);
            else outputCurrentLine(token[current].LINE);
            cout << st << endl;
            if (errorMessage == "") errorMessage = st + "\n";
//            exit(0);
        }
        current--;
    }

    int temp = T(current);
    if (temp) {
        st = "E->T E'";
        current = temp;
        int temp = E1(current);
        if (temp) {
            current = temp;
//            cout << "成功匹配到" << st << endl;
            return current;
        }
    }


    return 0;
}

int E1(int current) {
//    cout << "从" << token[current].ORI << "开始匹配E'" << endl;
    string st = "E'->W T E'";
    if (token[current].ORI == "+" || token[current].ORI == "-"){
        current ++;
        int temp = T(current);
        if (temp) {
            current = temp;
            int temp = E1(current);
            if (temp) {
                current = temp;
//                cout << "成功匹配到" << st << endl;
                return current;
            }
        }
    }
    else {
//        cout << "成功匹配到E'->~" << endl;
        return current;
    }

    return 0;
}

int T(int current) {
//    cout << "从" << token[current].ORI << "开始匹配T" << endl;
    string st = "T->D T'";
    int temp = D(current);
    if (temp) {
        current = temp;
        int temp = T1(current);
        if (temp) {
            current = temp;
//            cout << "成功匹配到" << st << endl;
            return current;
        }
    }
    else  st = "缺少变量、常量或常数";

    outputCurrentLine(token[current].LINE);
    cout << st << endl;
    if (errorMessage == "") errorMessage = st + "\n";
//    exit(0);
    return 0;
}

int T1(int current) {
//    cout << "从" << token[current].ORI << "开始匹配T'" << endl;
    string st = "T'->V D T'";
    if (token[current].ORI == "*" || token[current].ORI == "/"){
        current ++;
        int temp = D(current);
        if (temp) {
            current = temp;
            int temp = T1(current);
            if (temp) {
                current = temp;
//                cout << "成功匹配到" << st << endl;
                return  current;
            }
        }
        else st = "缺少变量、常量或常数";
    }
    else {
//        cout << "成功匹配到T'->~" << endl;
        return current;
    }

    outputCurrentLine(token[current].LINE);
    cout << st << endl;
    if (errorMessage == "") errorMessage = st + "\n";
//    exit(0);
    return 0;
}

int D(int current) {
//    cout << "从" << token[current].ORI << "开始匹配D" << endl;
    string st;
    if (token[current].FORMNAME == "S" && symbol[token[current].No].CAT != ""){
        st = "D->S";
        current ++;
//        cout << "成功匹配到" << st << endl;
        return current;
    }
    else if (token[current].FORMNAME == "C"){
        st = "D->Const";
        current ++;
//        cout << "成功匹配到" << st << endl;
        return current;
    }
    else if (token[current].ORI == "("){
        st = "D->( E )";
        current ++;
        int temp = E(current);
        if (temp) {
            current = temp;
            if (token[current].ORI == ")"){
                current++;
//                cout << "成功匹配到" << st << endl;
                return current;
            }
            else st = "缺少 )";
        }
        outputCurrentLine(token[current].LINE);
        cout << st << endl;
        if (errorMessage == "") errorMessage = st + "\n";
//        exit(0);
    }

    if (token[current].FORMNAME != "K" && token[current].FORMNAME != "D" && token[current].FORMNAME != "C") {
        outputCurrentLine(token[current].LINE );
        cout << "未定义 " << token[current].ORI<< endl;
        if (errorMessage == "") errorMessage = "未定义 " + token[current].ORI + "\n";
//        exit(0);
    }
    return 0;
}

int D1(int current) {
//    cout << "从" << token[current].ORI << "开始匹配D'" << endl;
    string st = "D'->, D D'";
    if (token[current].ORI == ","){
        current ++;
        int temp = D(current);
        if (temp) {
            current = temp;
            int temp = D1(current);
            if (temp) {
                current = temp;
//                cout << "成功匹配到" << st << endl;
                return current;
            }
        }
        else st = "函数参数格式错误";

    }
    else {
//        cout << "成功匹配到D'->~" << endl;
        return current;
    }



    outputCurrentLine(token[current].LINE);
    cout << st << endl;
    if (errorMessage == "") errorMessage = st + "\n";
//    exit(0);
    return 0;
}

int I1(int current) {
//    cout << "从" << token[current].ORI << "开始匹配I'" << endl;
    string st = "I'->E L E";
    int temp = E(current);
    if (temp) {
        current = temp;
        if (token[current].ORI == "<" || token[current].ORI == ">" || token[current].ORI == "<=" || token[current].ORI == ">=" || token[current].ORI == "=="){
            current++;
            int temp = E(current);
            if (temp) {
                current = temp;
//                cout << "成功匹配到" << st << endl;
                return current;
            }
        }
        else st = "缺少逻辑符号";
    }

    outputCurrentLine(token[current].LINE);
    cout << st << endl;
    if (errorMessage == "") errorMessage = st + "\n";
//    exit(0);
    return 0;
}
