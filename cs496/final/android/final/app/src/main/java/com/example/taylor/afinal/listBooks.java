package com.example.taylor.afinal;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class listBooks extends AppCompatActivity {

    private Button allBooks;
    private Button oneBook;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_books);

        allBooks = findViewById(R.id.allBooks);
        oneBook = findViewById(R.id.oneBook);

        allBooks.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent listAllBookActivity = new Intent(getApplicationContext(), listAllBooks.class);
                startActivity(listAllBookActivity);
            }
        });

        oneBook.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                Intent listOneBookActivity = new Intent(getApplicationContext(), listOneBook.class);
                startActivity(listOneBookActivity);
            }
        });
    }
}
