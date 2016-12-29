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
        for (int j = 0; j < quad.size();){
            if (j == loc)
            {
                j++;
                it++;
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
    }
    return true;
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

void optimMain(){
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
                int k = i;
                int judg1;
                int judg2;
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
                            int pos3 = findEqu(quad[j].fourth,j);
                            if (different != 4){
                                do{
                                    findEqu(quad[j].fourth, pos3);
                                }
                                while (different == 4 || (quad[pos3].first == "end"&&quad[pos3].second == "while"));
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
