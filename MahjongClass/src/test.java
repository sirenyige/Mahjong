class MyClass{
    private int[] a;

    public int[] getA() {
        return a;
    }

    public void setA(int[] a) {
        this.a = a;
    }

    public String testProcess(){
        int[] a =this.a.clone();
        change(a);
        for (int i : a) {
            System.out.print(i);
            System.out.println();
        }
        return "hello";
    }

    private void change(int[] a){
        a[0]=-1;
        a[1]=-2;
    }
}


public class test {
    public static void main(String[] args) {
        int[] a = {1,2,3,4,5};
        for (int i : a) {
            System.out.print(i);
            System.out.println();
        }
        MyClass myClass = new MyClass();
        myClass.setA(a);
        myClass.testProcess();
        for (int i : myClass.getA()) {
            System.out.print(i);
        }

    }

}
