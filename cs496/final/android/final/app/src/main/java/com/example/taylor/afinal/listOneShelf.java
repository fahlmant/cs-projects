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
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class listOneShelf extends AppCompatActivity {

    private EditText submitText;
    private Button submitButton;
    private ListView listInfo;
    private OkHttpClient mOkHttpClient;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_one_shelf);

        submitText = findViewById(R.id.inputListShelf);
        submitButton = findViewById(R.id.submitListShelf);
        listInfo = findViewById(R.id.shelfRequestResults);

        submitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String shelfID = submitText.getText().toString();
                submitText.setText(null);

                //From class lecutres
                mOkHttpClient = new OkHttpClient();
                HttpUrl reqUrl = HttpUrl.parse("https://cs496-final-fahlmant.appspot.com/shelves/" + shelfID );
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
                            List<Map<String, String>> shelf = new ArrayList<Map<String, String>>();
                            m.put("number",jobj.getString("number"));
                            m.put("room", jobj.getString("room"));
                            m.put("wood", jobj.getString("wood"));
                            m.put("genre", jobj.getString("genre"));
                            m.put("book", jobj.getString("book"));
                            m.put("shelf_id", jobj.getString("shelf_id"));
                            shelf.add(m);

                            final SimpleAdapter shelfAdapter = new SimpleAdapter(
                                    listOneShelf.this,
                                    shelf,
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
                            e.printStackTrace();
                        }
                    }
                });
            }
        });
    }
}
