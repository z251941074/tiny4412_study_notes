package com.example.administrator.app_addons_0001_message;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    public Button btn = null;
    public Button btn2 = null;
    private  String TAG = "Message";
    private int cnt1 = 0;
    private int cnt2 = 0;
    public Handler myHandle1 = null;
    public Looper myLoop1 = null;

    public Handler myHandle2 = null;
    public Looper myLoop2 = null;

    class myThread extends Thread {
        @Override
        public void run() {
            Looper.prepare();
            Looper.loop();
        }
        public Looper getLooper() {
          return  myLoop1  = Looper.myLooper();
        };
    }
    class myRunnable implements Runnable {
        @Override
        public void run() {
            Looper.prepare();
            Looper.loop();
        }
        public Looper getLooper() {
            return  myLoop2  = Looper.myLooper();
        };
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn = (Button)findViewById(R.id.btn);
        btn.setOnClickListener(new View.OnClickListener() {
            /*点击btn发送消息*/
            @Override
            public void onClick(View view) {
                Log.d(TAG, "sendMessage cnt "+cnt1);
                myHandle1.sendEmptyMessage(1);
                cnt1++;
            }
        });
       /*主线程创建handler1,指定线程Looper和处理函数*/
        myHandle1 = new Handler(new myThread().getLooper()) {
            @Override
            public void handleMessage(Message msg) {
               Log.d(TAG, "handleMessage1->"+msg.what);
            }
        };


        btn2 = (Button)findViewById(R.id.btn2);
        btn2.setOnClickListener(new View.OnClickListener() {
            /*点击btn发送消息*/
            @Override
            public void onClick(View view) {
                Log.d(TAG, "sendMessage2 cnt "+cnt2);
                //myHandle2.sendEmptyMessage(2);
                //myHandle2.sendMessage(new Message());
                /*延时3s 处理*/
                myHandle2.sendMessageDelayed(new Message(), 3000);
                Log.d(TAG, "sendMessage2 cnt end");
                cnt2++;
            }
        });

        /*主线程创建handler2,指定线程Looper和处理函数CallBack*/
        myHandle2 = new Handler((new myRunnable()).getLooper(), new Handler.Callback() {
            @Override
            public boolean handleMessage(Message message) {
                Log.d(TAG, "handleMessage2->"+message.what);
                return false;
            }
        });

        /*创建子线程1*/
        new myThread().start();

        /*创建线程2*/
        new Thread(new myRunnable(), "MessageTestThread2").start();

        /*创建子线程3*/
        new Thread("MessageTestThread3") {
            @Override
            public void run() {
            }
        }.start();
    }
}
