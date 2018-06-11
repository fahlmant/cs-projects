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
import okhttp3.RequestBody;
import okhttp3.Response;

public class deleteBook extends AppCompatActivity {

    private Button delBookSubmit;
    private EditText delBookTitle;
    private ListView delBookResponse;
    private OkHttpClient mOkHttpClient;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_delete_book);

        delBookTitle = findViewById(R.id.delBookTitle);
        delBookSubmit = findViewById(R.id.delBookSubmit);
        delBookResponse = findViewById(R.id.delBookResp);

        delBookSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String bookID = delBookTitle.getText().toString();
                delBookTitle.setText(null);

                //From class lecutres
                mOkHttpClient = new OkHttpClient();
                HttpUrl reqUrl = HttpUrl.parse("https://cs496-final-fahlmant.appspot.com/books/" + bookID);
                Request request = new Request.Builder()
                        .url(reqUrl)
                        .delete()
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
                            List<Map<String, String>> statusCode = new ArrayList<Map<String, String>>();
                            m.put("result", jobj.getString("Result"));
                            m.put("message", jobj.getString("Message"));
                            statusCode.add(m);

                            final SimpleAdapter statusAdapter = new SimpleAdapter(
                                    deleteBook.this,
                                    statusCode,
                                    R.layout.status_item,
                                    new String[]{"result","message"},
                                    new int[]{R.id.status_item_code,R.id.status_item_message});
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    delBookResponse.setAdapter(statusAdapter);
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
