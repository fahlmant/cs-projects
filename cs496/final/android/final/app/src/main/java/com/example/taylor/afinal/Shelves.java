package com.example.taylor.afinal;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class Shelves extends AppCompatActivity {
    private Button listShelf;
    private Button addShelf;
    private Button editShelf;
    private Button deleteShelf;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_shelves);

        listShelf = findViewById(R.id.listShelf);
        addShelf = findViewById(R.id.addShelf);
        editShelf = findViewById(R.id.editShelf);
        deleteShelf = findViewById(R.id.deleteShelf);

        listShelf.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent listShelfActivity = new Intent(getApplicationContext(), listShelves.class);
                startActivity(listShelfActivity);
            }
        });

        addShelf.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent addShelfActivity = new Intent(getApplicationContext(), addShelf.class);
                startActivity(addShelfActivity);

            }
        });
        editShelf.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent editShelfActivity = new Intent(getApplicationContext(), editShelf.class);
                startActivity(editShelfActivity);
            }
        });
        deleteShelf.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent deleteShelfActivity = new Intent(getApplicationContext(), deleteShelf.class);
                startActivity(deleteShelfActivity);
            }
        });


    }
}
