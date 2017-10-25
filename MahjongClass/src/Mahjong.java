
import java.util.ArrayList;

public class Mahjong {
    private int[][] allPai = new int[4][10];

    private final String[] paiName={"万","筒","条"};
    private final String[] ziPaiName={"中","发","白","东","南","西","北"};
    private final String[] number={"一","二","三","四","五","六","七","八","九"};
    public Mahjong() {
    }

    public Mahjong(int[][] allPai) {
        this.allPai = allPai;
    }

    public ArrayList<String> getChosenPai(){
        int[][] allPai = this.allPai.clone();
        ArrayList<String> result = new ArrayList<String>();
        for (int i=0;i<4;i++){
            if(i!=3){
                allPai[i][0]++;
                for (int j=1;j<10;j++){
                    if (allPai[i][j]==4){
                        continue;
                    }
                    allPai[i][j]++;
                    if (Win(allPai)){
                        result.add(String.format("%s%s", number[j-1],paiName[i]));
                    }
                    allPai[i][j]--;
                }
                allPai[i][0]--;
            } else {
                allPai[i][0]++;
                for (int j=1;j<8;j++){
                    if (allPai[i][j]==4){
                        continue;
                    }
                    allPai[i][j]++;
                    if (Win(allPai)){
                        result.add(String.format("%s", ziPaiName[j-1]));
                    }
                    allPai[i][j]++;
                }
                allPai[i][0]--;
            }

        }
        return result;
    }

    private boolean Win(int[][] allPai){
        int jiangPos = 0;
        int yuShu;
        boolean jiangExisted = false;


        for (int i=0;i<4;i++){
            yuShu = allPai[i][0]%3;
            if (yuShu==1){
                return false;
            }
            if (yuShu==2) {
                if (jiangExisted) {
                    return false;
                }
                jiangPos = i;
                jiangExisted = true;
            }
        }
        
        for (int i=0;i<4;i++){
            if (i!=jiangPos){
                if (!Analyze(allPai[i],i==3)){
                    return false;
                }
            }
        }

        boolean success = false;
        for (int j=1;j<10;j++){
            if (allPai[jiangPos][j]>=2){
                allPai[jiangPos][j]-=2;
                allPai[jiangPos][0]-=2;
                if (Analyze(allPai[jiangPos],jiangPos==3)){
                    success=true;
                }
                allPai[jiangPos][j]+=2;
                allPai[jiangPos][0]+=2;
                if (success){
                    break;
                }
            }
        }
        return success;
    }

    private boolean Analyze(int[] aKindPai, boolean ziPai){
        if (aKindPai[0]==0){
            return true;
        }

        int j;
        for (j=1;j<10;j++){
            if (aKindPai[j]!=0){
                break;
            }
        }
        boolean result =false;
        if (aKindPai[j]>=3){
            aKindPai[j]-=3;
            aKindPai[0]-=3;
            result = Analyze(aKindPai,ziPai);
            aKindPai[j]+=3;
            aKindPai[0]+=3;
            return result;
        }
        if ((!ziPai)&&(j<8)&&(aKindPai[j+1]>0)&&(aKindPai[j+2]>0)){
            aKindPai[j]--;
            aKindPai[j+1]--;
            aKindPai[j+2]--;
            aKindPai[0]-=3;
            result=Analyze(aKindPai,ziPai);
            aKindPai[j]++;
            aKindPai[j+1]++;
            aKindPai[j+2]++;
            aKindPai[0]+=3;
            return result;
        }
        return false;
    }


    public static void main(String[] args) {
        int[][] a = {
                {13,3,2,3,2,3,0,0,0,0},  //万
                {0,0,0,0,0,0,0,0,0,0},  //筒
                {0,0,0,0,0,0,0,0,0,0},  //条
                {0,0,0,0,0,0,0,0},  //字
        };
        Mahjong mahjong = new Mahjong(a);
        ArrayList<String> result = mahjong.getChosenPai();
        for (String s : result) {
            System.out.println(s);
        }
    }

}
