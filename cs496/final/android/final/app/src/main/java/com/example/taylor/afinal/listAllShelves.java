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

public class listAllShelves extends AppCompatActivity {

    private ListView listInfo;
    private OkHttpClient mOkHttpClient;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_all_shelves);


        listInfo = findViewById(R.id.allShelvesList);

        //From class lecutres
        mOkHttpClient = new OkHttpClient();
        HttpUrl reqUrl = HttpUrl.parse("https://cs496-final-fahlmant.appspot.com/shelves/");
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
                    JSONArray items = jobj.getJSONArray("Shelves");
                    List<Map<String, String>> shelves = new ArrayList<Map<String, String>>();
                    for(int i = 0; i < items.length(); i++) {
                        HashMap<String, String> m = new HashMap<String, String>();
                        m.put("number", items.getJSONObject(i).getString("number"));
                        m.put("room", items.getJSONObject(i).getString("room"));
                        m.put("wood", items.getJSONObject(i).getString("wood"));
                        m.put("genre", items.getJSONObject(i).getString("genre"));
                        m.put("book", items.getJSONObject(i).getString("book"));
                        m.put("shelf_id", items.getJSONObject(i).getString("shelf_id"));
                        shelves.add(m);
                    }
                    final SimpleAdapter shelfAdapter = new SimpleAdapter(
                            listAllShelves.this,
                            shelves,
                            R.layout.shelf_item,
                            new String[]{"number","room","wood","genre","book","shelf_id"},
                            new int[]{R.id.shelf_item_number, R.id.shelf_item_room,R.id.shelf_item_wood,R.id.shelf_item_genre,R.id.shelf_item_book,R.id.shelf_item_shelf_id});
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            listInfo.setAdapter(shelfAdapter);
                        }
                    });


                } catch (JSONException e) {
                    Log.d("JSON", e.toString());
                }
            }
        });
    }
}
