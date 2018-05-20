package com.example.taylor.cs496sqlite;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.provider.BaseColumns;

import static com.example.taylor.cs496sqlite.SQLiteHelper.DBContract.DataTable.SQL_CREATE_TABLE;

public class SQLiteHelper extends SQLiteOpenHelper {

    public SQLiteHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, DBContract.DataTable.DB_NAME, factory, DBContract.DataTable.DB_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {

        db.execSQL(SQL_CREATE_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }

    public class DBContract {
        private DBContract(){};
        public final class DataTable implements BaseColumns {

            public static final String DB_NAME = "cs496";
            public static final String TABLE_NAME = "data";
            public static final String COLUMN_NAME_DATA_STRING = "data_string";
            public static final String COLUMN_NAME_DATA_LAT = "data_lat";
            public static final String COLUMN_NAME_DATA_LONG= "data_long";
            public static final int DB_VERSION = 1;


            public static final String SQL_CREATE_TABLE = "CREATE TABLE " +
                    DataTable.TABLE_NAME + "(" + DataTable._ID + " INTEGER PRIMARY KEY NOT NULL," +
                    DataTable.COLUMN_NAME_DATA_STRING + " VARCHAR(255)," +
                    DataTable.COLUMN_NAME_DATA_LONG + " VARCHAR(255)," +
                    DataTable.COLUMN_NAME_DATA_LAT + " VARCHAR(255));";

            public  static final String SQL_DROP_DEMO_TABLE = "DROP TABLE IF EXISTS " + DataTable.TABLE_NAME;
        }
    }

}
