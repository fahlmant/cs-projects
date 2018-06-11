package com.example.taylor.afinal;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {


    private Button books;
    private Button shelves;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        books = findViewById(R.id.bookButton);
        shelves = findViewById(R.id.shelfButton);

        books.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                Intent bookTopActivity = new Intent(getApplicationContext(), Books.class);
                startActivity(bookTopActivity);
            }
        });

        shelves.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                Intent shelfTopActivity = new Intent(getApplicationContext(), Shelves.class);
                startActivity(shelfTopActivity);
            }
        });
    }
}
