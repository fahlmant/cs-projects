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

public class unstoreBook extends AppCompatActivity {

    private EditText unstoreShelfID;
    private Button unstoreSubmitButton;
    private OkHttpClient mOkHttpClient;
    //From OKHTTP website
    public static final MediaType JSON = MediaType.parse("application/json; charset=utf-8");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_unstore_book);

        unstoreShelfID = findViewById(R.id.unstoreShelfID);
        unstoreSubmitButton = findViewById(R.id.unstoreSubmit);

        unstoreSubmitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                //From class lecutres
                mOkHttpClient = new OkHttpClient();
                HttpUrl reqUrl = HttpUrl.parse("https://cs496-final-fahlmant.appspot.com/shelves/" + unstoreShelfID.getText().toString() + "/store");
                unstoreShelfID.setText(null);
                Request request = new Request.Builder()
                        .url(reqUrl)
                        .delete()
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
