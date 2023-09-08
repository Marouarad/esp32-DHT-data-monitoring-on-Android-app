package com......;// Replace with package name

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends Activity {
    TextView temp, hum, datetime;
    DatabaseReference db;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        datetime = (TextView) findViewById(R.id.datetime);
        temp = (TextView) findViewById(R.id.temp);
        hum = (TextView) findViewById(R.id.hum);

        //DHTSensor reference
        db = FirebaseDatabase.getInstance().getReference().child("DHT");

        try {
            db.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(DataSnapshot dataSnapshot) {
                    
                    String datetimeData = dataSnapshot.child("datetime").getValue().toString();
                    String tempData = dataSnapshot.child("temp").getValue().toString();
                    String humData = dataSnapshot.child("hum").getValue().toString();

                    // set the data
                    temp.setText(tempData);
                    hum.setText(humData);
                    datetime.setText(datetimeData);
                }

                @Override
                public void onCancelled(DatabaseError error) {
                    //
                }
            });
        } catch (Exception e) {

        }
    }
}