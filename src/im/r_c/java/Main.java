package im.r_c.java;

public class Main {
    static {
        System.loadLibrary("natiflect-test");
    }

    public static native void nativeTestAll();

    public static void main(String[] args) {
        nativeTestAll();
    }
}
