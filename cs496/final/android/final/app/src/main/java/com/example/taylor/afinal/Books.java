package com.example.taylor.afinal;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class Books extends AppCompatActivity {

    private Button listBooks;
    private Button addBook;
    private Button editBook;
    private Button deleteBook;
    private Button storeBook;
    private Button unstoreBook;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_books);

        listBooks = findViewById(R.id.listBook);
        addBook = findViewById(R.id.addBook);
        editBook = findViewById(R.id.editBook);
        deleteBook = findViewById(R.id.deleteBook);
        storeBook = findViewById(R.id.storeButton);
        unstoreBook = findViewById(R.id.unstoreButton);

        listBooks.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent listBookActivity = new Intent(getApplicationContext(), listBooks.class);
                startActivity(listBookActivity);
            }
        });

        addBook.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent addBookActivity = new Intent(getApplicationContext(), addBook.class);
                startActivity(addBookActivity);

            }
        });
        editBook.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent editBookActivity = new Intent(getApplicationContext(), editBook.class);
                startActivity(editBookActivity);
            }
        });
        deleteBook.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent deleteBookActivity = new Intent(getApplicationContext(), deleteBook.class);
                startActivity(deleteBookActivity);
            }
        });

        storeBook.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent storeBookActivity = new Intent(getApplicationContext(), storeBook.class);
                startActivity(storeBookActivity);
            }
        });

        unstoreBook.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent unstoreBookActivity = new Intent(getApplicationContext(), unstoreBook.class);
                startActivity(unstoreBookActivity);
            }
        });

    }

}
