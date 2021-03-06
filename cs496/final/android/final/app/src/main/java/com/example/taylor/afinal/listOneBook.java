package com.example.taylor.afinal;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
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
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class listOneBook extends AppCompatActivity {

    private EditText submitText;
    private Button submitButton;
    private ListView listInfo;
    private OkHttpClient mOkHttpClient;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_one_book);

        submitText = findViewById(R.id.inputListBook);
        submitButton = findViewById(R.id.submitListBook);
        listInfo = findViewById(R.id.bookRequestResults);

        submitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String bookID = submitText.getText().toString();
                submitText.setText(null);

                //From class lecutres
                mOkHttpClient = new OkHttpClient();
                HttpUrl reqUrl = HttpUrl.parse("https://cs496-final-fahlmant.appspot.com/books/" + bookID );
                Request request = new Request.Builder()
                        .url(reqUrl)
                        .build();
                mOkHttpClient.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Call call, IOException e) {
                        e.printStackTrace();
                    }

                    @Override
                    public void onResponse(Call call, Response response) throws IOException {
                        String resp = response.body().string();
                        try {
                            JSONObject jobj = new JSONObject(resp);
                            HashMap<String, String> m = new HashMap<String,String>();
                            List<Map<String, String>> book = new ArrayList<Map<String, String>>();
                            m.put("title", jobj.getString("title"));
                            m.put("author", jobj.getString("author"));
                            m.put("language", jobj.getString("language"));
                            m.put("isbn", jobj.getString("isbn"));
                            m.put("shelf", jobj.getString("shelf"));
                            m.put("book_id", jobj.getString("book_id"));
                            book.add(m);

                            final SimpleAdapter bookAdapter = new SimpleAdapter(
                                    listOneBook.this,
                                    book,
                                    R.layout.book_item,
                                    new String[]{"title","author","language","isbn","shelf","book_id"},
                                    new int[]{R.id.book_item_title,R.id.book_item_author,R.id.book_item_language,R.id.book_item_isbn,R.id.book_item_shelf,R.id.book_item_book_id});
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    listInfo.setAdapter(bookAdapter);
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
