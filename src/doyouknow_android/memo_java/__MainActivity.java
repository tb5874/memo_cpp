package com.example.testapi32;

import android.os.Build;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;
import android.content.pm.PackageManager;
import androidx.appcompat.app.AppCompatActivity;

import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("tester_j2c");
        System.loadLibrary("tester_opencl");
    }

    // tester_j2c : -->
    public native String testCstrToJstr();
    public native int testCint32ToJint();
    public native void testJintToCint32(int get_jint);
    public native void testJbufToC(ByteBuffer get_jbuf);
    // tester_j2c : <--

    // tester_opencl : -->
    public native void openclopenlib();
    public native String openclmatmul();
    public native void openclcloselib();
    // tester_opencl : <--

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if( (checkSelfPermission(android.Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) ||
                (checkSelfPermission(android.Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) ){

                if( shouldShowRequestPermissionRationale(android.Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                    Toast.makeText(this, "외부 저장소 사용을 위해 읽기/쓰기 필요", Toast.LENGTH_SHORT).show();
                }

                requestPermissions(new String[]{android.Manifest.permission.WRITE_EXTERNAL_STORAGE, android.Manifest.permission.READ_EXTERNAL_STORAGE}, 1);

            }
        }

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView jtextview = findViewById(R.id.text_viewer);
        System.out.println("\n\n\n\n\n");

        ///////////////////////////////////////////////////////////////////////////////////////////

        // Test : testCstrToJstr()
        String jstr_from_cstr = testCstrToJstr();
        System.out.println("[ Speak java ] : " + "jstr_from_cstr : " + jstr_from_cstr);

        // Test : testCint32ToJint()
        int jint_from_cint32 = testCint32ToJint();
        System.out.println("[ Speak java ] : " + "Integer.toString( jint_from_cint32 )" + " : " + Integer.toString(jint_from_cint32));
        System.out.println("\n\n\n\n\n");

        // Test : testJintToCint32()
        int jint_to_cint32 = 1;
        testJintToCint32(jint_to_cint32);
        System.out.println("[ Speak java ] : " + "jint_to_cint32 : " + jint_to_cint32);
        System.out.println("\n\n\n\n\n");

        // Test : testJbufToC()
        ByteBuffer jbuf = ByteBuffer.allocateDirect(4); // jint is 4 byte
        jbuf.putInt(1234);
        jbuf.rewind(); // java buffer position, go to start
        int jint_from_jbuf = jbuf.getInt();
        jbuf.rewind(); // java buffer position, go to start
        testJbufToC(jbuf); // c++ modify jbuf
        int jbuf_from_c = jbuf.getInt();
        jbuf.rewind(); // java buffer position, go to start
        System.out.println("[ Speak java ] : " + "jint_from_jbuf : " + jint_from_jbuf);
        System.out.println("[ Speak java ] : " + "jbuf_from_c : " + jbuf_from_c);
        System.out.println("\n\n\n\n\n");

        ///////////////////////////////////////////////////////////////////////////////////////////

        // Test : openclopenlib()
        openclopenlib();

        // Test : openclmatmul()
        String jstr_opencl_result = openclmatmul();
        System.out.println("[ Speak java ] : below is c++ result" + "\n" + jstr_opencl_result);

        // Test : openclcloselib()
        openclcloselib();

        ///////////////////////////////////////////////////////////////////////////////////////////

        // app text view
        jtextview.setText(jstr_opencl_result);

        ///////////////////////////////////////////////////////////////////////////////////////////

    }

    @Override
    protected void onDestroy(){
        super.onDestroy();
    }

}