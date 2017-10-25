#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool Win(int [4][10]);
bool Analyze(int [], bool);

int main()
{
    int allPai[4][10]={
                        {13,3,2,3,2,3,0,0,0,0},  //万
                        {0,0,0,0,0,0,0,0,0,0},  //筒
                        {0,0,0,0,0,0,0,0,0,0},  //条
                        {0,0,0,0,0,0,0,0},  //字
                        };

    for (int i = 0; i < 4; ++i){
        if(i!=3){
            allPai[i][0]++;
            for (int j = 1; j < 10; ++j){
                if(allPai[i][j]==4){
                    continue;
                }
                allPai[i][j]++;
                if(Win(allPai)){
                    printf("%d-%d\n",j,i);
                }
                allPai[i][j]--;
            }
            allPai[i][0]--;
        } else {
            allPai[i][0]++;
            for (int j = 1; j < 8; ++j){
                if(allPai[i][j]==4){
                    continue;
                }
                allPai[i][j]++;
                if(Win(allPai)){
                    printf("%d-%d\n",j,i);
                }
                allPai[i][j]--;
            }
            allPai[i][0]--;
        }
    }


    return 0;
}


bool Win (int allPai[4][10]) {
    int jiangPos;//“将”的位置
    int yuShu;//余数
    bool jiangExisted=false;

    //是否满足3，3，3，3，2模型
    int i;
    for(i=0;i<4;i++) {
        yuShu=(int)fmod(allPai[i][0],3);
        if (yuShu==1){
            return false;
        }
        if (yuShu==2){
            if (jiangExisted){
                return false;
            }
            jiangPos=i;
            jiangExisted=true;
        }
    }

    //判断不含将牌的花色是否符合胡牌条件
    for(i=0;i<4;i++) {
        if (i!=jiangPos){
            if (!Analyze(allPai[i],i==3)){
                return false;
            }
        }
    }

    //该类牌中要包含将，因为要对将进行轮询，效率较低，放在最后
    bool success=false;//指示除掉“将”后能否通过

    for(int j=1;j<10;j++)//对列进行操作，用j表示
    {
        if (allPai[jiangPos][j]>=2){
            //除去这2张将牌
            allPai[jiangPos][j]-=2;
            allPai[jiangPos][0]-=2;
            if(Analyze(allPai[jiangPos],jiangPos==3)){
                success=true;
            }
            //还原这2张将牌
            allPai[jiangPos][j]+=2;
            allPai[jiangPos][0]+=2;
            if (success) break;
        }
    }
    return success;
}




//分解成“刻”“顺”组合
bool Analyze(int aKindPai[],bool ziPai) {
    if (aKindPai[0]==0){
        return true;
    }
    //寻找第一张牌
    int j;
    for(j=1;j<10;j++){
        if (aKindPai[j]!=0){
            break;
        }
    }
    bool result;
    //作为刻牌
    if (aKindPai[j]>=3){
        //除去这3张刻牌
        aKindPai[j]-=3;
        aKindPai[0]-=3;
        result=Analyze(aKindPai,ziPai);
        //还原这3张刻牌
        aKindPai[j]+=3;
        aKindPai[0]+=3;
        return result;
    }
    //作为顺牌
    if ((!ziPai)&&(j<8)&&(aKindPai[j+1]>0)&&(aKindPai[j+2]>0)){
        //除去这3张顺牌
        aKindPai[j]--;
        aKindPai[j+1]--;
        aKindPai[j+2]--;
        aKindPai[0]-=3;
        result=Analyze(aKindPai,ziPai);
        //还原这3张顺牌
        aKindPai[j]++;
        aKindPai[j+1]++;
        aKindPai[j+2]++;
        aKindPai[0]+=3;
        return result;
    }
    return false;
}

