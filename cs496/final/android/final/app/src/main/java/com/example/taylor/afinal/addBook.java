package com.example.taylor.afinal;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class addBook extends AppCompatActivity {

    private EditText addBookTitle;
    private EditText addBookAuthor;
    private EditText addBookLang;
    private EditText addBookISBN;
    private Button addBookButton;
    private LinearLayout addBookContainer;
    private ListView addBookResponse;
    private OkHttpClient mOkHttpClient;
    //From OKHTTP website
    public static final MediaType JSON = MediaType.parse("application/json; charset=utf-8");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_book);

        addBookTitle = findViewById(R.id.addBookTitle);
        addBookAuthor = findViewById(R.id.addbookAuthor);
        addBookLang = findViewById(R.id.addBookLang);
        addBookISBN = findViewById(R.id.addBookISBN);
        addBookButton = findViewById(R.id.addBookButton);
        addBookContainer = findViewById(R.id.addBookContainer);
        addBookResponse = findViewById(R.id.addBookResp);

        addBookButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                //https://stackoverflow.com/questions/20117148/how-to-create-json-object-using-string
                JSONObject requestBody = new JSONObject();
                try {
                    requestBody.put("title", addBookTitle.getText().toString());
                    requestBody.put("author", addBookAuthor.getText().toString());
                    requestBody.put("language", addBookLang.getText().toString());
                    requestBody.put("isbn",addBookISBN.getText().toString());

                } catch (Exception e) {
                    Log.d("JSONOBJ", e + "");
                }

                //OKHTTP website http://square.github.io/okhttp/
                RequestBody rb = RequestBody.create(JSON, requestBody.toString());

                //From class lecutres
                mOkHttpClient = new OkHttpClient();
                HttpUrl reqUrl = HttpUrl.parse("https://cs496-final-fahlmant.appspot.com/books");
                Request request = new Request.Builder()
                        .url(reqUrl)
                        .post(rb)
                        .build();
                mOkHttpClient.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Call call, IOException e) {
                        Log.d("JSON", e.toString());
                    }

                    @Override
                    public void onResponse(Call call, Response response) throws IOException {
                        Log.d("RESPCODE", response.code() + "");

                        String resp = response.body().string();
                        try {
                            JSONObject jobj = new JSONObject(resp);
                            HashMap<String, String> m = new HashMap<String, String>();
                            List<Map<String, String>> book = new ArrayList<Map<String, String>>();
                            m.put("title", jobj.getString("title"));
                            m.put("author", jobj.getString("author"));
                            m.put("language", jobj.getString("language"));
                            m.put("isbn", jobj.getString("isbn"));
                            m.put("shelf", jobj.getString("shelf"));
                            m.put("book_id", jobj.getString("book_id"));
                            book.add(m);

                            final SimpleAdapter bookAdapter = new SimpleAdapter(
                                    addBook.this,
                                    book,
                                    R.layout.book_item,
                                    new String[]{"title", "author", "language", "isbn", "shelf", "book_id"},
                                    new int[]{R.id.book_item_title, R.id.book_item_author, R.id.book_item_language, R.id.book_item_isbn, R.id.book_item_shelf, R.id.book_item_book_id});
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    addBookResponse.setAdapter(bookAdapter);
                                }
                            });
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                });
            }
        });

    }
}
