#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool Win(int [4][10]);
bool Analyze(int [], bool);

int main()
{
    int allPai[4][10]={
                        {13,3,2,3,2,3,0,0,0,0},  //��
                        {0,0,0,0,0,0,0,0,0,0},  //Ͳ
                        {0,0,0,0,0,0,0,0,0,0},  //��
                        {0,0,0,0,0,0,0,0},  //��
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
    int jiangPos;//��������λ��
    int yuShu;//����
    bool jiangExisted=false;

    //�Ƿ�����3��3��3��3��2ģ��
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

    //�жϲ������ƵĻ�ɫ�Ƿ���Ϻ�������
    for(i=0;i<4;i++) {
        if (i!=jiangPos){
            if (!Analyze(allPai[i],i==3)){
                return false;
            }
        }
    }

    //��������Ҫ����������ΪҪ�Խ�������ѯ��Ч�ʽϵͣ��������
    bool success=false;//ָʾ�������������ܷ�ͨ��

    for(int j=1;j<10;j++)//���н��в�������j��ʾ
    {
        if (allPai[jiangPos][j]>=2){
            //��ȥ��2�Ž���
            allPai[jiangPos][j]-=2;
            allPai[jiangPos][0]-=2;
            if(Analyze(allPai[jiangPos],jiangPos==3)){
                success=true;
            }
            //��ԭ��2�Ž���
            allPai[jiangPos][j]+=2;
            allPai[jiangPos][0]+=2;
            if (success) break;
        }
    }
    return success;
}




//�ֽ�ɡ��̡���˳�����
bool Analyze(int aKindPai[],bool ziPai) {
    if (aKindPai[0]==0){
        return true;
    }
    //Ѱ�ҵ�һ����
    int j;
    for(j=1;j<10;j++){
        if (aKindPai[j]!=0){
            break;
        }
    }
    bool result;
    //��Ϊ����
    if (aKindPai[j]>=3){
        //��ȥ��3�ſ���
        aKindPai[j]-=3;
        aKindPai[0]-=3;
        result=Analyze(aKindPai,ziPai);
        //��ԭ��3�ſ���
        aKindPai[j]+=3;
        aKindPai[0]+=3;
        return result;
    }
    //��Ϊ˳��
    if ((!ziPai)&&(j<8)&&(aKindPai[j+1]>0)&&(aKindPai[j+2]>0)){
        //��ȥ��3��˳��
        aKindPai[j]--;
        aKindPai[j+1]--;
        aKindPai[j+2]--;
        aKindPai[0]-=3;
        result=Analyze(aKindPai,ziPai);
        //��ԭ��3��˳��
        aKindPai[j]++;
        aKindPai[j+1]++;
        aKindPai[j+2]++;
        aKindPai[0]+=3;
        return result;
    }
    return false;
}

