package com.example.taylor.cs496sqlite;


import android.Manifest;
import android.content.ContentValues;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.database.DatabaseUtils;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabaseLockedException;
import android.location.Location;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CursorAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;

public class MainActivity extends AppCompatActivity implements GoogleApiClient.ConnectionCallbacks, GoogleApiClient.OnConnectionFailedListener{


    private GoogleApiClient mGoogleApiClient;
    private LocationRequest mLocationRequest;
    private LocationListener mLocationListener;
    private int LOCATION_PERMISSIONS_REQUEST = 17;

    private SQLiteDatabase mDB;

    private TextView latitude;
    private TextView longitude;
    private EditText et;
    private SQLiteDatabase mSQLDB;
    private Cursor mSQLCursor;
    private CursorAdapter mSQLCursorAdapter;
    private Boolean location_perms = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Assign button
        final Button submit = findViewById(R.id.button);
        latitude = findViewById(R.id.latitude);
        longitude = findViewById(R.id.longitude);
        et = findViewById(R.id.plain_text_input);


        //Initialize Google Api Client
        if (mGoogleApiClient == null) {
            mGoogleApiClient = new GoogleApiClient.Builder(this)
                    .addConnectionCallbacks(this)
                    .addOnConnectionFailedListener(this)
                    .addApi(LocationServices.API)
                    .build();
        }

        //Set up location request
        mLocationRequest = LocationRequest.create();
        mLocationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
        mLocationRequest.setInterval(50);
        mLocationRequest.setFastestInterval(50);

        latitude.setText("44.5");
        longitude.setText("-123.2");

        //Set up location listener
        mLocationListener = new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                if (location != null) {
                    latitude.setText(String.valueOf(location.getLatitude()));
                    longitude.setText(String.valueOf(location.getLongitude()));

                }
            }
        };

        //Set up database
        SQLiteHelper helper = new SQLiteHelper(this, " ", null, 1);
        mSQLDB = helper.getWritableDatabase();

        //Set up button listener to submit data to database
        submit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String submitted_text = et.getText().toString();
                if(submitted_text != "") {
                    String lat = latitude.getText().toString();
                    String longi = longitude.getText().toString();

                    ContentValues submitted_data = new ContentValues();
                    submitted_data.put(SQLiteHelper.DBContract.DataTable.COLUMN_NAME_DATA_STRING, submitted_text);
                    submitted_data.put(SQLiteHelper.DBContract.DataTable.COLUMN_NAME_DATA_LAT, lat);
                    submitted_data.put(SQLiteHelper.DBContract.DataTable.COLUMN_NAME_DATA_LONG, longi);

                    mSQLDB.insert(SQLiteHelper.DBContract.DataTable.TABLE_NAME,null,submitted_data);
                    et.setText(null);
                    populateTable();
                }
            }
        });
        populateTable();
    }

    @Override
    protected void onStart() {
        mGoogleApiClient.connect();
        super.onStart();
    }

    @Override
    protected void onStop() {
        mGoogleApiClient.disconnect();
        super.onStop();
    }

    private void updateLocation() {
        if (ActivityCompat.checkSelfPermission(this,
                android.Manifest.permission.ACCESS_FINE_LOCATION) !=
                PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this,
                android.Manifest.permission.ACCESS_COARSE_LOCATION) !=
                PackageManager.PERMISSION_GRANTED) {
        }
        LocationServices.FusedLocationApi.requestLocationUpdates(
            mGoogleApiClient,mLocationRequest,mLocationListener);
    }

    @Override
    public void onConnected(@Nullable Bundle bundle) {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, LOCATION_PERMISSIONS_REQUEST);
            return;
        }
        updateLocation();

    }

    @Override
    public void onConnectionSuspended(int i) {

    }

    @Override
    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {

    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults){

        if(permissions[0].equals("android.permission.ACCESS_FINE_LOCATION") && grantResults[0] == 0) {
            location_perms = true;
        }
        else {
           location_perms = false;
        }

    }

    private void populateTable() {
        if(mSQLDB != null) {
            try {
                if(mSQLCursorAdapter != null && mSQLCursorAdapter.getCursor() != null) {
                    if(!mSQLCursorAdapter.getCursor().isClosed()) {
                        mSQLCursorAdapter.getCursor().close();
                    }
                }
                mSQLCursor = mSQLDB.query(SQLiteHelper.DBContract.DataTable.TABLE_NAME,
                        null,
                        null,
                        null,
                        null,
                        null,
                        null);
                ListView SQListView = findViewById(R.id.sql_list);
                mSQLCursorAdapter = new SimpleCursorAdapter(this,
                        R.layout.sql_item,
                        mSQLCursor,
                        new String[]{SQLiteHelper.DBContract.DataTable.COLUMN_NAME_DATA_STRING,
                                SQLiteHelper.DBContract.DataTable.COLUMN_NAME_DATA_LAT,
                                SQLiteHelper.DBContract.DataTable.COLUMN_NAME_DATA_LONG},
                        new int[]{R.id.sql_string_data, R.id.sql_int_lat, R.id.sql_int_long},
                        0);
                SQListView.setAdapter(mSQLCursorAdapter);
            }
            catch(Exception e) {
                Log.d("POPULATE", "Error loading db " + e );
            }
        }
    }
}

