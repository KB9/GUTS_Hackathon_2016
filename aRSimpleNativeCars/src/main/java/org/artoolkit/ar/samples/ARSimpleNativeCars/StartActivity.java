package org.artoolkit.ar.samples.ARSimpleNativeCars;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class StartActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.start);
    }

    public void startCTF(View view) {
        Intent intent = new Intent(this, ARSimpleNativeCarsActivity.class);
        startActivity(intent);
    }

    public void startCheckpoints(View view) {
        Intent intent = new Intent(this, ARSimpleNativeCarsActivity.class);
        startActivity(intent);
    }
}
