package com.example.taylor.afinal;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import org.json.JSONObject;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class storeBook extends AppCompatActivity {

    private EditText storeShelfID;
    private EditText storeBookID;
    private Button storeSubmitButton;
    private OkHttpClient mOkHttpClient;
    //From OKHTTP website
    public static final MediaType JSON = MediaType.parse("application/json; charset=utf-8");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_store_book);

        storeShelfID = findViewById(R.id.storeShelfID);
        storeBookID = findViewById(R.id.storeBookID);
        storeSubmitButton = findViewById(R.id.storeSubmit);

        storeSubmitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //https://stackoverflow.com/questions/20117148/how-to-create-json-object-using-string
                JSONObject requestBody = new JSONObject();
                try {
                    requestBody.put("book", storeBookID.getText().toString());
                } catch (Exception e) {
                    Log.d("JSONOBJ", e + "");
                }

                //OKHTTP website http://square.github.io/okhttp/
                RequestBody rb = RequestBody.create(JSON, requestBody.toString());

                //From class lecutres
                mOkHttpClient = new OkHttpClient();
                HttpUrl reqUrl = HttpUrl.parse("https://cs496-final-fahlmant.appspot.com/shelves/" + storeShelfID.getText().toString() + "/store");
                Request request = new Request.Builder()
                        .url(reqUrl)
                        .put(rb)
                        .build();
                mOkHttpClient.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Call call, IOException e) {

                    }

                    @Override
                    public void onResponse(Call call, Response response) throws IOException {

                    }
                });
            }
        });
    }
}
