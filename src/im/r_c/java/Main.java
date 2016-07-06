package im.r_c.java;

/**
 * NatiflectTest
 * Created by richard on 7/5/16.
 */
public class Main {
    static {
        System.loadLibrary("natiflect-test");
    }

    public static native void nativeTestAll();

    public static void main(String[] args) {
        nativeTestAll();
    }
}
