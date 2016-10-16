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
        intent.putExtra("GAME_MODE", 1);
        startActivity(intent);
    }

    public void startCheckpoints(View view) {
        Intent intent = new Intent(this, ARSimpleNativeCarsActivity.class);
        intent.putExtra("GAME_MODE", 0);
        startActivity(intent);
    }
}
