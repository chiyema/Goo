//
//  OPTIM.h
//  Goo
//
//  Created by 马驰也 on 2016/12/28.
//  Copyright © 2016年 马驰也. All rights reserved.
//

#ifndef OPTIM_h
#define OPTIM_h


#endif /* OPTIM_h */

int position;
int different;
int Loopadd;


void delQuad(int i){
    for (vector<quadElement>::iterator it0 = quad.begin(); it0 != quad.end();)
    {
        for (int j = 0; j < quad.size();){
            if (j == i)
            {
                j++;
                quad.erase(it0++);
            }
            else
            {
                j++;
                it0++;
            }
        }
    }
}

bool isFourthDiff(string first, string second, string third, string fourth, int loc){
    for (vector<quadElement>::iterator it = quad.begin(); it != quad.end();)
    {
        int j = 1;
        if (j == loc)
        {
            if (j != quad.size()){
                j++;
                it++;
            }
            else return false;
            
        }
        else
        {
            if (quad[j].first == quad[loc].first&&quad[j].second == quad[loc].second&&quad[j].third == quad[loc].third&&quad[j].fourth != quad[loc].fourth)
            {
                position = j;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}


int findEqu(string equ,int start){
    for (int i = start; i < quad.size(); i++){
        if (quad[i].first == equ){
            different = 1;
            return i;
        }
        else if (quad[i].second == equ){
            different = 2;
            return i;
        }
        else if (quad[i].third == equ){
            different = 3;
            return i;
        }
        else if (quad[i].fourth == equ){
            different = 4;
            return i;
        }
        else{
            return -1;
        }
    }
    return -1;
}

void insertQuad(int add, int pos){
    vector<quadElement>::iterator it1 = quad.begin();
    //    for (int i = 0; i < add; i++) it ++;
    it1 += add;
    quad.insert(it1, quad[pos]);
    delQuad(pos + 1);
}

bool isVarexp(int i){
    if (symbol[isSymbol(quad[i].second)].CAT == "tv"&&symbol[isSymbol(quad[i].third)].CAT == "tv") return true;
    else if (symbol[isSymbol(quad[i].second)].CAT == "tv"&&symbol[isSymbol(quad[i].third)].CAT == "v") return true;
    else if (symbol[isSymbol(quad[i].second)].CAT == "v"&&symbol[isSymbol(quad[i].third)].CAT == "tv") return true;
    else if (symbol[isSymbol(quad[i].second)].CAT == "v"&&symbol[isSymbol(quad[i].third)].CAT == "v") return true;
    else return false;
    return false;
}

void optim(){
    for (int i = 0; i < quad.size(); i++){
        if (isFourthDiff(quad[i].first, quad[i].second, quad[i].third, quad[i].fourth, i)) {
            if (isConstant(quad[i].second) != -1 && isConstant(quad[i].third) != -1){//常值表达式节省
                int pos1 = findEqu(quad[i].fourth, 0);
                if (different == 2){
                    quad[pos1].second = quad[i].fourth;
                }
                else if (different == 3){
                    quad[pos1].third = quad[i].fourth;
                }
                delQuad(position);
            }
            else if (isVarexp(i)){//公共子表达式节省
                int judg1;
                int judg2;
                int k = i;
                do{
                    judg1 = findEqu(quad[k].second, k);
                    k++;
                } while (different == 4 || (quad[judg1].first == "end"&&quad[judg1].second == "main"));
                if (different == 4){
                    delQuad(judg1);
                }
                do{
                    judg2 = findEqu(quad[k].third, k);
                    k++;
                } while (different == 4 || (quad[judg2].first == "end"&&quad[judg2].second == "main"));
                if (different == 4){
                    delQuad(judg2);
                }
            }
        }
        //删除无用赋值
        else if ((quad[i].first == "=" && quad[i].second != "res") || quad[i].first == ":"){
            int pos2 = findEqu(quad[i].fourth,0);
            if (pos2 == 0){
                delQuad(i);
            }
        }//不变表达式外提
        else if (quad[i].first == "while"){
            Loopadd = i;
            for (int j = i; j < quad.size(); j++){
                if (quad[j].first == "end"&&quad[j].second == "while") break;
                else{
                    if (isArithmeticalOperator(quad[j].first)){
                        if (isConstant(quad[j].second) && isConstant(quad[j].third)){
                            int pos3 = findEqu(quad[j].fourth,j);
                            if (different == 2){
                                quad[pos3].second = quad[j].fourth;
                            }
                            else if (different == 3){
                                quad[pos3].third = quad[j].fourth;
                            }
                            delQuad(j);
                        }
                        else{
                            int pos3;
                            int n = j;
                            if (different != 4){
                                do{
                                    pos3 = findEqu(quad[n].fourth, j);
                                    n++;
                                }while (different == 4 || (quad[pos3].first == "end"&&quad[pos3].second == "while"));
                                if (different == 4){
                                    insertQuad(Loopadd, pos3);
                                }
                            }
                        }
                    }
                }
            }
        }
        else{
            cout << "不需要优化" << endl;
        }
    }
}


void optimMain(){
    ridConstant();
    ridRepeat();
}

void ridConstant(){
    vector<quadElement>::iterator it;
    vector<vector<quadElement>::iterator> toBeDeleted;

    for (it = quad.begin(); it != quad.end(); it++) {
        if (isConstant((*it).second) != -1 && isConstant((*it).third) != -1){
            NSString* secondNSString = [NSString stringWithUTF8String:(*it).second.c_str()];
            NSString* thirdNSString = [NSString stringWithUTF8String:(*it).third.c_str()];
            float secondFloat = [secondNSString floatValue];
            float thirdFloat = [thirdNSString floatValue];
            if ((*it).first == "+") secondFloat += thirdFloat;
            else if ((*it).first == "-") secondFloat -= thirdFloat;
            else if ((*it).first == "*") secondFloat *= thirdFloat;
            else if ((*it).first == "/") secondFloat /= thirdFloat;
            const char* programChar;
            
            if (isDecimal((*it).second) || isDecimal((*it).third)) {
                NSString *stringFloat = [NSString stringWithFormat:@"%f",secondFloat];
                programChar = [stringFloat UTF8String];
            }
            else if (!isDecimal((*it).second) && !isDecimal((*it).third)) {
                int secondInt = (int) secondFloat;
                NSString *stringInt = [NSString stringWithFormat:@"%d",secondInt];
                programChar = [stringInt UTF8String];
            }
            
            vector<quadElement>::iterator it1;
            for (it1 = it; it1 != quad.end(); it1++) {
                if ((*it1).second == (*it).fourth) (*it1).second = programChar;
                if ((*it1).third == (*it).fourth) (*it1).third = programChar;
            }
            (*it).second = programChar;
            (*it).third = "";
            (*it).first = "=";
            toBeDeleted.push_back(it);
        }
    }
    
    vector<vector<quadElement>::iterator>::iterator it2;
    for (it2 = toBeDeleted.begin(); it2 != toBeDeleted.end(); it2++) {
        quad.erase(*it2);
    }

    
}

void ridRepeat(){
    vector<quadElement>::iterator it1;
    vector<quadElement>::iterator it2;
    vector<quadElement>::iterator it3;
    vector<vector<quadElement>::iterator> toBeDeleted;

    for (it1 = quad.begin(); it1 != quad.end() - 1; it1++) {
        for (it2 = it1 + 1; it2 != quad.end(); it2++) {
            if ((*it1).first == (*it2).first && (*it1).second == (*it2).second && (*it1).third == (*it2).third){
                if (symbol[isSymbol((*it1).fourth)].CAT == "tv" && symbol[isSymbol((*it2).fourth)].CAT == "tv"){
                    bool isEdited = false;
                    for (it3 = it1; it3 != it2; it3++)
                        if ((*it3).fourth == (*it1).second || (*it3).fourth == (*it1).third) isEdited = true;
                    if (!isEdited) {
                        for (it3 = it1 + 1; it3 != it2; it3++) {
                            if ((*it3).second == (*it1).fourth) (*it3).second = (*it2).fourth;
                            if ((*it3).third == (*it1).fourth) (*it3).third = (*it2).fourth;
                        }
                        (*it1).fourth = (*it2).fourth;
                        toBeDeleted.push_back(it2);
                    }
                }
            }
        }
    }
    vector<vector<quadElement>::iterator>::iterator it4;
    for (it4 = toBeDeleted.begin(); it4 != toBeDeleted.end(); it4++) {
        quad.erase(*it4);
    }

}
