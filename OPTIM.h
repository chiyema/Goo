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


/*优化代码主程序
 输入：无
 输出：无
 */
void optimMain(){
    ridStep();
    ridConstant();
    ridRepeat();
    ridUnused();
    ridWhile();
}

/*优化代码（去除一步临时变量）
 输入：无
 输出：无
 */
void ridStep() {
    vector<quadElement>::iterator it1;
    vector<vector<quadElement>::iterator> toBeDeleted;
    
    for (it1 = quad.begin() + 1; it1 != quad.end(); it1++) {
        if ((*it1).first == "=" && isSymbol((*it1).second) != -1)
            if (symbol[isSymbol((*it1).second)].CAT == "tv") {
                if ((*(it1-1)).fourth == (*it1).second) {
                    (*(it1-1)).fourth = (*it1).fourth;
                    toBeDeleted.push_back(it1);
                }
            }
    }
    
    vector<vector<quadElement>::iterator>::iterator it4;
    for (it4 = toBeDeleted.end() - 1; it4 != toBeDeleted.begin() - 1; it4--) {
        quad.erase(*it4);
    }
}

/*优化代码（去除常数表达式）
 输入：无
 输出：无
 */
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
    
    vector<vector<quadElement>::iterator>::iterator it4;
    for (it4 = toBeDeleted.end() - 1; it4 != toBeDeleted.begin() - 1; it4--) {
        quad.erase(*it4);
    }

    
}

/*优化代码（去除重复表达式）
 输入：无
 输出：无
 */
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
    for (it4 = toBeDeleted.end() - 1; it4 != toBeDeleted.begin() - 1; it4--) {
        quad.erase(*it4);
    }
}

/*优化代码（去除未使用就重新赋值的变量）
 输入：无
 输出：无
 */
void ridUnused() {
    vector<quadElement>::iterator it1;
    vector<quadElement>::iterator it2;
    vector<quadElement>::iterator it3;
    vector<vector<quadElement>::iterator> toBeDeleted;
    
    for (it1 = quad.begin(); it1 != quad.end() - 1; it1++) {
        for (it2 = it1 + 1; it2 != quad.end(); it2++) {
            if (isSymbol((*it1).fourth) != -1)
            if ((*it1).fourth == (*it2).fourth){
                bool isUsed = false;
                for (it3 = it1 + 1; it3 != it2 + 1; it2++) {
                    if ((*it3).second == (*it1).fourth || (*it3).third == (*it1).fourth) isUsed = true;
                    break;
                }
                if (!isUsed) toBeDeleted.push_back(it1);
            }
        }
    }

    
//    for (it1 = quad.begin(); it1 != quad.end() - 1; it1++) {
//        if (isSymbol((*it1).fourth) != -1){
//            bool isUsed = false;
//            for (it2 = it1 + 1; it2 != quad.end(); it2++) {
//                if ((*it1).fourth == (*it2).second || (*it1).fourth == (*it2).third){
//                    isUsed = true;
//                    break;
//                }
//            }
//            if (!isUsed) {
//                toBeDeleted.push_back(it1);
//            }
//        }
//    }
    
    vector<vector<quadElement>::iterator>::iterator it4;
    for (it4 = toBeDeleted.end() - 1; it4 != toBeDeleted.begin() - 1; it4--) {
        quad.erase(*it4);
    }
}

/*优化代码（调整While中的表达式）
 输入：无
 输出：无
 */
void ridWhile() {
    typedef struct whileNo{
        vector<quadElement>::iterator wh;
        vector<quadElement> add;
        vector<vector<quadElement>::iterator> del;
    }whileNo;
    vector<quadElement>::iterator it1;
    vector<quadElement>::iterator it2;
    vector<quadElement>::iterator it3;
    vector<quadElement>::iterator it4;
    vector<vector<quadElement>::iterator> toBeDeleted;
    vector<whileNo> wn;
    
    for (it1 = quad.begin(); it1 != quad.end() - 1; it1++) {
        if ((*it1).first == "while"){
            whileNo tempWN;
            tempWN.wh = it1;
            wn.push_back(tempWN);
            for (it2 = it1 + 1; it2 != quad.end(); it2++) {
                if ((*it2).second == "while") break;
            }
            
            for (it3 = it1; it3 < it2; it3++ ) {
                if (isSymbol((*it3).fourth) != -1)
                    if (symbol[isSymbol((*it3).fourth)].CAT != "tv")
                {
                    bool isChanged = false;
                    for (it4 = it3; it4 < it2; it4++){
                        if ((*it3).second == (*it4).fourth || (*it3).third == (*it4).fourth){
                            isChanged = true;
                            break;
                        }
                    }
                    
                    if (!isChanged){
                        wn.back().add.push_back(*it3);
                        wn.back().del.push_back(it3);
                    }
                    
                }
            }

        }
    }

    vector<whileNo>::iterator it5;
    for (it5 = wn.end() - 1; it5 != wn.begin() - 1; it5--) {
        vector<vector<quadElement>::iterator>::iterator it6;
        for (it6 = (*it5).del.end()-1; it6 != (*it5).del.begin() -1; it6--) {
            quad.erase(*it6);
        };
        vector<quadElement>::iterator it7;
        for (it7 = (*it5).add.end() - 1; it7 != (*it5).add.begin() -1; it7--) quad.insert((*it5).wh, *it7);
    }
}



