
#ifndef EXPRESSION_SCANNER_GRAMMAR_SCANNER_H
#define EXPRESSION_SCANNER_GRAMMAR_SCANNER_H

#endif //EXPRESSION_SCANNER_GRAMMAR_SCANNER_H



using namespace std;


/*初始化词法分析变量
 输入：无
 输出：无
 */
void morphologyInit() {
    symbolElement mainElement = {"main", "NULL", "p", {"F",0}};
    symbol.push_back(mainElement);
    
    currentLine = 1; //当前行数
    
    token.clear(); //token序列
    symbol.clear(); //符号表
    constl.clear();//常数表
    
    
    identifier.clear(); //标识符或常量栈
    action.clear(); //语义动作(关键字、界符)栈
    withend_stack.clear(); //end栈
    
    quad.clear(); //四元式栈
    
    p_number = 1;   //记录p的个数，参数
    p_stack.clear();     //p的栈
    
    t_number = 1;   //记录t的个数，表达式
    t_stack.clear();     //t的栈
    
    else_number = 1;   //记录else的个数
    else_stack.clear();     //else的栈
    
    end_number = 1;   //记录end的个数
    end_stack.clear();     //end的栈
    
    while_number = 1;   //记录end的个数
    while_stack.clear();     //end的栈
    
    errorMessage = "";    //错误信息
    errorLocation = "";   //错误位置
    
    targetCode = "";
    
    parameter.clear();
    
    REG = {"R3", "R2", "R1", "R0"};

}


/*词法分析主程序
 输入：无
 输出：无
 */
void morphologyMain(string programString)
{
    morphologyInit();   //初始化词法分析变量
    getToken(programString);   //生成Token序列
    fillType();     //填写符号表和常数表
}


/*生成Token序列
 输入：无
 输出：无
 */
int getToken(string programString)
{
    int tokennumber=0;
    int state = 1,state_before;
    int i = 0;
    char tempString[10];
    //FILE* fp;
    //fp=fopen(file_location,"r");

    token.clear();
    while (programString[i]!='\0')
    {
        state_before=state;
        state=stateChange(state,programString[i]);
        //cout<<programString[i]<<" "<<state_before<<" "<<state<<endl;
        if(state>0)
            tempString[tokennumber++]=programString[i];
        else
        {
            if (tokennumber)
            {
                tempString[tokennumber]='\0';
                //cout<<token<<" ";
                //fseek(fp,-1,SEEK_CUR);
                i--;
                tokenElement tempTE = searchElement(tempString);
                tempTE.LINE = currentLine;
                token.push_back(tempTE);

            }

            tokennumber=0;
            state=1;
        }
        i++;
    }
    return 0;
}


/*状态转换自动机
 输入：无
 输出：无
 */
int stateChange(int state, char ch)
{

    //end_state==正整数时，代表转移到当前状态
    //end_state==0时，代表空白符读入完毕
    //end_state==-1时，代表一个元素读入完毕
    //end_state==-2时，代表错误
    if (ch == '\n')  currentLine++;     //当前行数加1
    int end_state=0;
    if (state==1)
    {
        if (isCharacter(ch)) end_state=2;
        else if (isNumber(ch)) end_state=3;
        else if (ch == '>') end_state=4;
        else if (ch == '<') end_state=5;
        else if (ch == '=') end_state=6;
        else if (ch == '"') end_state=11;
        else if (ch == '\'') end_state=9;
        else if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') end_state=0;
        else end_state=18;
    }
    else if (state==2)
    {
        if (isCharacter(ch) || isNumber(ch)) end_state=2;
        else end_state=-1;
    }
    else if (state==3)
    {
        if (isNumber(ch)) end_state=3;
        else if (ch == '.') end_state=8;
        else end_state=-1;
    }
    else if (state==8)
    {
        if (isNumber(ch)) end_state=7;
        else end_state=-2;
    }
    else if (state==7)
    {
        if (isNumber(ch)) end_state=7;
        else end_state=-1;
    }
    else if (state==9)
    {
        if (isCharacter(ch) || isNumber(ch)) end_state=10;
        else end_state=-2;
    }
    else if (state==10)
    {
        if (ch == '\'') end_state=16;
        else end_state=-2;
    }
    else if (state==16)
    {
        end_state=-1;
    }
    else if (state==11)
    {
        if (isCharacter(ch) || isNumber(ch)) end_state=12;
        else end_state=-2;
    }
    else if (state==12)
    {
        if (isCharacter(ch) || isNumber(ch)) end_state=12;
        else if (ch == '"') end_state=17;
        else end_state=-2;
    }
    else if (state==17)
    {
        end_state=-1;
    }
    else if (state==4)
    {
        if (ch == '=') end_state=13;
        else end_state=-1;
    }
    else if (state==13)
    {
        end_state=-1;
    }
    else if (state==5)
    {
        if (ch == '=') end_state=14;
        else end_state=-1;
    }
    else if (state==14)
    {
        end_state=-1;
    }
    else if (state==6)
    {
        if (ch == '=') end_state=15;
        else end_state=-1;
    }
    else if (state==15)
    {
        end_state=-1;
    }
    else if (state==18)
    {
        end_state=-1;
    }

    if (end_state == -2) cout << "error: " << ch <<"can't be qualified to the state change." << endl;


    return end_state;
}


/*寻找当前元素所在的表与位置
 输入：待测元素（字符串）
 输出：找到的表中元素（tokenElement）
 */
tokenElement searchElement(char* tempString)
{
    string temp = tempString;

    if (isNumber(temp[0]) || temp == "true" || temp == "false"){
        for (int i = 2; i < constl.size(); i++) {  //判断是不是常数表中出现过的
            if (constl[i] == tempString) {
                tokenElement tempTE = {"C",i,temp};
                return tempTE;
            }
        }
        
        //添加进入常数表中
        constl.push_back(tempString);
        tokenElement tempTE;
        tempTE.FORMNAME = "C";
        tempTE.No = (int)constl.size()-1;
        tempTE.ORI = temp;
        return tempTE;
    }
    else if (isCharacter(temp[0])) {
        for (int i = 0; i < sizeof(keyList); i++) { //判断是不是属于关键字表
            if (keyList[i] == temp) {
                tokenElement tempTE = {"K",i,temp};
                return tempTE;
            }
        }
        for (int j = 0; j < symbol.size(); j++) { //判断是不是符号表中出现过的
            if (symbol[j].NAME == temp) {
                tokenElement tempTE = {"S",j,temp};
                return tempTE;
            }
        }

                                                    //添加进入符号表当中
        symbolElement tempSE;
        tempSE = {temp,"","",""};
        symbol.push_back(tempSE);
        tokenElement tempTE;
        tempTE.FORMNAME = "S";
        tempTE.No = (int)symbol.size()-1;
        tempTE.ORI = temp;
        return tempTE;
    }
    else {
        for (int i = 0; i < sizeof(delimiterList); i++) {  //判断是不是界符中出现过的

            if (delimiterList[i] == temp) {
                tokenElement tempTE = {"D",i,temp};
                return tempTE;
            }
        }
    }
    cout << "error: \"" << temp <<"\" can't transform to token." << endl;
    
    
    tokenElement ttt;
    return ttt;

}


/*填符号表
 输入：无
 输出：无
 */
void fillType() {
    for (int i =0; i < token.size(); i++) {
        if (token[i].FORMNAME == "S") {    //是不是符号／标识符
            if (symbol[token[i].No].TYP == "") {    //是不是没有设置过类型
                if (token[i+1].ORI == ":") {                //常量类型
                    symbol[token[i].No].TYP = "const";
                    symbol[token[i].No].CAT = "c";
                }
                else if (token[i+1].ORI == "=") {           //变量类型
                    symbol[token[i].No].TYP = whatsTheType(token[i+2].ORI);
                    symbol[token[i].No].CAT = "v";
                }
//                else if ((token[i-1].ori == "(" && token[i+1].ori == ")") || token[i-1].ori == "," || token[i+1].ori == ","){
//                    symbol[token[i].No].CAT = "parameter";
//                }
            }
        }
    }

    for (int i =0; i < token.size(); i++) {
        if (token[i].FORMNAME == "S") {    //是不是符号／标识符
            if (token[i+1].ORI == "(" && token[i-1].ORI == "func") {           //函数类型
//                if (symbol[token[i].No].TYP == "") {    //是不是没有设置过类型
                    symbol[token[i].No].CAT = "p";
                    int j = i;
                    while (token[j].ORI != "rtn" && j < token.size()) j++;
                    if (token[j].ORI == "rtn")symbol[token[i].No].TYP = symbol[token[j+1].No].TYP;
                }
                else if (token[i+1].ORI == "("){                              //形参类型设置
                    int j = i + 1;
                    int l = 1;
                    while (token[j].ORI != ")" && token[j].LINE == token[j-1].LINE) {
                        if (symbol[token[i].No + l].TYP == "") {
                            symbol[token[i].No + l].CAT = "vf";
                            if (token[j+1].FORMNAME == "S") {
                                if (symbol[token[j+1].No].TYP == "const") symbol[token[i].No + l].TYP = whatsTheType(symbol[token[j+1].No].NAME);
                                else symbol[token[i].No + l].TYP = symbol[token[j+1].No].TYP;
                            }
                            else symbol[token[i].No + l].TYP = whatsTheType(token[j+1].ORI);
                        }
                        j = j + 2;
                        l++;
                    }
                }
//            }
        }
    }
    
    
    //为每个变量设置存储位置
    dataLength = 0;        //存储栈的其实位置设置
    for (int i = 0 ; i < symbol.size(); i++) {
        if (symbol[i].CAT == "v" || symbol[i].CAT == "vf" || symbol[i].CAT == "c"){
            symbol[i].ORI = dataLength;
            if (symbol[i].TYP == "bool") dataLength += 1;
            else if (symbol[i].TYP == "int") dataLength += 2;
            else if (symbol[i].TYP == "real") dataLength+= 4;
            else if (symbol[i].TYP == "const") dataLength += 4;
        }
        
    }
}




