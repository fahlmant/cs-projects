package com.example.taylor.afinal;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class listShelves extends AppCompatActivity {

    private Button allShelves;
    private Button oneShelf;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_shelves);

        allShelves = findViewById(R.id.allShelves);
        oneShelf = findViewById(R.id.oneShelf);

        allShelves.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent listAllShelvesActivity = new Intent(getApplicationContext(), listAllShelves.class);
                startActivity(listAllShelvesActivity);
            }
        });

        oneShelf.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                Intent listOneShelfActivity = new Intent(getApplicationContext(), listOneShelf.class);
                startActivity(listOneShelfActivity);
            }
        });
    }
}
