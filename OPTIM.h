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


void deletquad(int i){
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

bool isfourthdiff(string first, string second, string third, string fourth, int loc){
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
}
}

int findvt(string vtname){
    for (int i = 0; i < quad.size(); i++){
        if (quad[i].first == "="){
            if (quad[i].second==vtname)
            {
                return i;
            }
            else
            {
                return 0;
            }
        }
    }
}

int findequ(string equ,int start){
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
            return 0;
        }
    }
}

void insertquad(int add, int pos){
    vector<quadElement>::iterator it1 = quad[add];
    quad.insert(it1, quad[pos]);
    deletquad(pos + 1);
}

void optimizeMain(){
    for (int i = 0; i < quad.size(); i++){
        if (isArithmeticalOperator(quad[i].first)){
            if (isConstant(quad[i].second) && isConstant(quad[i].third)){
                int pos = findequ(quad[i].fourth,0);
                if (different == 2){
                    quad[pos].second = quad[i].fourth;
                }
                else if (different == 3){
                    quad[pos].third = quad[i].fourth;
                }
                deletquad(i);
            }
        }
        else if (isfourthdiff(quad[i].first, quad[i].second, quad[i].third, quad[i].fourth,i){
            int pos1 = findequ(quad[i].fourth,0);
            if (different == 2){
                quad[pos1].second = quad[i].fourth;
            }
            else if (different == 3){
                quad[pos1].third = quad[i].fourth;
            }
            deletquad(position);
        }
                 else if (quad[i].first == "=" && quad[i].second != "res") || quad[i].first == ":"){
            int pos2 = findequ(quad[i].fourth,0);
            if (pos2 == 0){
                deletquad(i);
            }
        }
        else if (quad[i].first == "while"){
            Loopadd = i;
            for (int j = i; j < quad.size(); j++){
                if (quad[j].first == "end"&&quad[j].second == "while") break;
                else{
                    if (isArithmeticalOperator(quad[j].first)){
                        if (isConstant(quad[j].second) && isConstant(quad[j].third)){
                            int pos3 = findequ(quad[j].fourth,j);
                            if (different == 2){
                                quad[pos1].second = quad[j].fourth;
                            }
                            else if (different == 3){
                                quad[pos1].third = quad[j].fourth;
                            }
                            deletquad(j);
                        }
                        else{
                            int pos3 = findequ(quad[j].fourth,j)
                            if (different != 4){
                                do{
                                    findequ(quad[j].fourth, pos3)
                                } while (different == 4 || (quad[pos3].first == "end"&&quad[pos3].second == "while"))
                                    if (different == 4){
                                        insertquad(Loopadd, pos3);
                                    }
                            }
                        }
                    }
                }
            }
        }
    }
