package com.example.taylor.afinal;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import org.json.JSONArray;
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

public class listAllBooks extends AppCompatActivity {

    private ListView listInfo;
    private OkHttpClient mOkHttpClient;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_all_books);

        listInfo = findViewById(R.id.allBookList);

        //From class lecutres
        mOkHttpClient = new OkHttpClient();
        HttpUrl reqUrl = HttpUrl.parse("https://cs496-final-fahlmant.appspot.com/books/");
        Request request = new Request.Builder()
                .url(reqUrl)
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
                    JSONArray items = jobj.getJSONArray("Books");
                    List<Map<String, String>> books = new ArrayList<Map<String, String>>();
                    for(int i = 0; i < items.length(); i++) {
                        HashMap<String, String> m = new HashMap<String, String>();
                        m.put("title", items.getJSONObject(i).getString("title"));
                        m.put("author", items.getJSONObject(i).getString("author"));
                        m.put("language", items.getJSONObject(i).getString("language"));
                        m.put("isbn", items.getJSONObject(i).getString("isbn"));
                        m.put("shelf", items.getJSONObject(i).getString("shelf"));
                        m.put("book_id", items.getJSONObject(i).getString("book_id"));
                        books.add(m);
                    }
                    final SimpleAdapter bookAdapter = new SimpleAdapter(
                            listAllBooks.this,
                            books,
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
                    Log.d("JSON", e.toString());
                }
            }
        });
    }
}
