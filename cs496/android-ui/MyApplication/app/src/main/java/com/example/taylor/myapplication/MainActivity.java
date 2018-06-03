package com.example.taylor.myapplication;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final Button buttonActivity1 = findViewById(R.id.button);
        final Button buttonActivity2 = findViewById(R.id.button2);
        final Button buttonActivity3 = findViewById(R.id.button3);
        final Button buttonActivity4 = findViewById(R.id.button4);

        buttonActivity1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), buttonActivity1.class);
                startActivity(intent);
            }
        });

        buttonActivity2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), buttonActivity2.class);
                startActivity(intent);

            }
        });
        buttonActivity3.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), buttonActivity3.class);
                startActivity(intent);
            }
        });
        buttonActivity4.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), buttonActivity4.class);
                startActivity(intent);
            }
        });
    }
}
