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
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class addShelf extends AppCompatActivity {

    private EditText addShelfNumber;
    private EditText addShelfRoom;
    private EditText addShelfGenre;
    private EditText addShelfWood;
    private Button addShelfButton;
    private LinearLayout addShelfContainer;
    private ListView addShelfResponse;
    private OkHttpClient mOkHttpClient;
    //From OKHTTP website
    public static final MediaType JSON = MediaType.parse("application/json; charset=utf-8");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_shelf);

        addShelfNumber = findViewById(R.id.addShelfNumber);
        addShelfRoom = findViewById(R.id.addShelfRoom);
        addShelfGenre = findViewById(R.id.addShelfGenre);
        addShelfWood = findViewById(R.id.addShelfWood);
        addShelfButton = findViewById(R.id.addShelfButton);
        addShelfContainer = findViewById(R.id.addShelfContainer);
        addShelfResponse = findViewById(R.id.addShelfResp);

        addShelfButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {


                //https://stackoverflow.com/questions/20117148/how-to-create-json-object-using-string
                JSONObject requestBody = new JSONObject();
                try {
                    requestBody.put("number", addShelfNumber.getText().toString());
                    requestBody.put("room", addShelfRoom.getText().toString());
                    requestBody.put("genre", addShelfGenre.getText().toString());
                    requestBody.put("wood",addShelfWood.getText().toString());

                } catch (Exception e) {
                    Log.d("JSONOBJ", e + "");
                }

                //OKHTTP website http://square.github.io/okhttp/
                RequestBody rb = RequestBody.create(JSON, requestBody.toString());

                //From class lecutres
                mOkHttpClient = new OkHttpClient();
                HttpUrl reqUrl = HttpUrl.parse("https://cs496-final-fahlmant.appspot.com/shelves");
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
                                    addShelf.this,
                                    shelf,
                                    R.layout.shelf_item,
                                    new String[]{"number","room","wood","genre","book","shelf_id"},
                                    new int[]{R.id.shelf_item_number, R.id.shelf_item_room,R.id.shelf_item_wood,R.id.shelf_item_genre,R.id.shelf_item_book,R.id.shelf_item_shelf_id});
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    addShelfResponse.setAdapter(shelfAdapter);
                                }
                            });
                        } catch (JSONException e) {
                            Log.d("JSON", e.toString());
                        }
                    }
                });
            }
        });

    }
}
