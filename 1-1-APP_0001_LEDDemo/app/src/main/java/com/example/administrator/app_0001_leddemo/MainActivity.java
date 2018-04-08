package com.example.administrator.app_0001_leddemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.Toast;
import com.example.administrator.hardlibrary.*;

public class MainActivity extends AppCompatActivity {

    private Button btn = null;
    private CheckBox box1 = null;
    private CheckBox box2 = null;
    private CheckBox box3 = null;
    private CheckBox box4 = null;
    public boolean flag = false;

    HardControl hardcontrol1 = new HardControl();

    public void onCheckboxClicked(View view) {
        // Is the view now checked?
        boolean checked = ((CheckBox) view).isChecked();
        // Check which checkbox was clicked
        switch(view.getId()) {
            case R.id.box1:
                if (checked)
                {
                    hardcontrol1.ledCtrl(0,0);
                    Toast.makeText(getApplicationContext(), "LED1 ON", Toast.LENGTH_SHORT).show();
                }
                else
                {
                    hardcontrol1.ledCtrl(0,1);
                    Toast.makeText(getApplicationContext(), "LED1 OFF", Toast.LENGTH_SHORT).show();
                }
                break;
            case R.id.box2:
                if (checked)
                {
                    hardcontrol1.ledCtrl(1,0);
                    Toast.makeText(getApplicationContext(), "LED2 ON", Toast.LENGTH_SHORT).show();
                }
                else
                {
                    hardcontrol1.ledCtrl(1,1);
                    Toast.makeText(getApplicationContext(), "LED2 OFF", Toast.LENGTH_SHORT).show();
                }
                break;
            case R.id.box3:
                if (checked)
                {
                    hardcontrol1.ledCtrl(2,0);
                    Toast.makeText(getApplicationContext(), "LED3 ON", Toast.LENGTH_SHORT).show();
                }
                else
                {
                    hardcontrol1.ledCtrl(2,1);
                    Toast.makeText(getApplicationContext(), "LED3 OFF", Toast.LENGTH_SHORT).show();
                }
                break;
            case R.id.box4:
                if (checked)
                {
                    hardcontrol1.ledCtrl(3,0);
                    Toast.makeText(getApplicationContext(), "LED4 ON", Toast.LENGTH_SHORT).show();
                }
                else
                {
                    hardcontrol1.ledCtrl(3,1);
                    Toast.makeText(getApplicationContext(), "LED4 OFF", Toast.LENGTH_SHORT).show();
                }
                break;
        }
    }

    class MyButton implements View.OnClickListener {
        @Override
        public void onClick(View view) {
            if(flag)
            {
                btn.setText("ALL ON");
                box1.setChecked(false);
                box2.setChecked(false);
                box3.setChecked(false);
                box4.setChecked(false);
                for(int i=0; i<4; i++)
                {
                    hardcontrol1.ledCtrl(i,1);
                }
            }
            else {
                btn.setText("ALL OFF");
                box1.setChecked(true);
                box2.setChecked(true);
                box3.setChecked(true);
                box4.setChecked(true);
                for(int i=0; i<4; i++)
                {
                    hardcontrol1.ledCtrl(i,0);
                }
            }
            flag = ! flag;
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn = (Button)findViewById(R.id.btn);

        hardcontrol1.ledOpen();

        box1 = (CheckBox) findViewById(R.id.box1);
        box2 = (CheckBox) findViewById(R.id.box2);
        box3 = (CheckBox) findViewById(R.id.box3);
        box4 = (CheckBox) findViewById(R.id.box4);


        btn.setOnClickListener(new MyButton());

/*
        btn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                flag = ! flag;
                if(flag)
                    btn.setText("ALL ON");
                else
                    btn.setText("ALL OFF");
            }
        });
*/
    }
}
