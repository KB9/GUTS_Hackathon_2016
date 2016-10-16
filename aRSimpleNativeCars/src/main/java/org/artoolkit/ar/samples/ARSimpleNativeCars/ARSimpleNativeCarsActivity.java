/*
 *  ARSimpleNativeCarsActivity.java
 *  ARToolKit5
 *
 *  Disclaimer: IMPORTANT:  This Daqri software is supplied to you by Daqri
 *  LLC ("Daqri") in consideration of your agreement to the following
 *  terms, and your use, installation, modification or redistribution of
 *  this Daqri software constitutes acceptance of these terms.  If you do
 *  not agree with these terms, please do not use, install, modify or
 *  redistribute this Daqri software.
 *
 *  In consideration of your agreement to abide by the following terms, and
 *  subject to these terms, Daqri grants you a personal, non-exclusive
 *  license, under Daqri's copyrights in this original Daqri software (the
 *  "Daqri Software"), to use, reproduce, modify and redistribute the Daqri
 *  Software, with or without modifications, in source and/or binary forms;
 *  provided that if you redistribute the Daqri Software in its entirety and
 *  without modifications, you must retain this notice and the following
 *  text and disclaimers in all such redistributions of the Daqri Software.
 *  Neither the name, trademarks, service marks or logos of Daqri LLC may
 *  be used to endorse or promote products derived from the Daqri Software
 *  without specific prior written permission from Daqri.  Except as
 *  expressly stated in this notice, no other rights or licenses, express or
 *  implied, are granted by Daqri herein, including but not limited to any
 *  patent rights that may be infringed by your derivative works or by other
 *  works in which the Daqri Software may be incorporated.
 *
 *  The Daqri Software is provided by Daqri on an "AS IS" basis.  DAQRI
 *  MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION
 *  THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE, REGARDING THE DAQRI SOFTWARE OR ITS USE AND
 *  OPERATION ALONE OR IN COMBINATION WITH YOUR PRODUCTS.
 *
 *  IN NO EVENT SHALL DAQRI BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL
 *  OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION,
 *  MODIFICATION AND/OR DISTRIBUTION OF THE DAQRI SOFTWARE, HOWEVER CAUSED
 *  AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE),
 *  STRICT LIABILITY OR OTHERWISE, EVEN IF DAQRI HAS BEEN ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  Copyright 2015 Daqri, LLC.
 *  Copyright 2011-2015 ARToolworks, Inc.
 *
 *  Author(s): Julian Looser, Philip Lamb
 *
 */

package org.artoolkit.ar.samples.ARSimpleNativeCars;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.artoolkit.ar.base.ARActivity;
import org.artoolkit.ar.base.camera.CameraPreferencesActivity;
import org.artoolkit.ar.base.rendering.ARRenderer;

public class ARSimpleNativeCarsActivity extends ARActivity {

    // Load the native libraries.
    static {
        System.loadLibrary("c++_shared");
        System.loadLibrary("ARWrapper");
        System.loadLibrary("ARWrapperNativeCarsExample");
    }

    public static native void onSteerLeftDown();
    public static native void onSteerLeftUp();
    public static native void onSteerRightDown();
    public static native void onSteerRightUp();

    public static native void onAcceleratorDown();
    public static native void onAcceleratorUp();
    public static native void onBrakeDown();
    public static native void onBrakeUp();

    public static native void initCheckpoints();
    public static native void initCTF();

    private SimpleNativeRenderer simpleNativeRenderer = new SimpleNativeRenderer();

    private Timer timer = new Timer();

    private static final float TRANSPARENCY = 0.5f;

    private Handler handler = new Handler();
    private Runnable runnable = new Runnable() {
        @Override
        public void run() {
            TextView timerText = (TextView) findViewById(R.id.timer_text);
            timerText.setText(timer.toString());

            handler.postDelayed(this, 1000);
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.main);

        Bundle extras = getIntent().getExtras();
        if (extras.get("GAME_MODE") == 0) ARSimpleNativeCarsActivity.initCheckpoints();
        else if (extras.get("GAME_MODE") == 1) ARSimpleNativeCarsActivity.initCTF();

        timer.start();
        runnable.run();

        final ImageView left = (ImageView) findViewById(R.id.steer_left_image);
        left.setAlpha(TRANSPARENCY);
        left.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        left.setAlpha(1.0f);
                        ARSimpleNativeCarsActivity.onSteerLeftDown();
                        return true;
                    case MotionEvent.ACTION_UP:
                        left.setAlpha(TRANSPARENCY);
                        ARSimpleNativeCarsActivity.onSteerLeftUp();
                        return true;
                }
                return false;
            }
        });

        final ImageView right = (ImageView) findViewById(R.id.steer_right_image);
        right.setAlpha(TRANSPARENCY);
        right.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        right.setAlpha(1.0f);
                        ARSimpleNativeCarsActivity.onSteerRightDown();
                        return true;
                    case MotionEvent.ACTION_UP:
                        right.setAlpha(TRANSPARENCY);
                        ARSimpleNativeCarsActivity.onSteerRightUp();
                        return true;
                }
                return false;
            }
        });

        final ImageView brake = (ImageView) findViewById(R.id.brake_image);
        brake.setAlpha(TRANSPARENCY);
        brake.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        brake.setAlpha(1.0f);
                        ARSimpleNativeCarsActivity.onBrakeDown();
                        return true;
                    case MotionEvent.ACTION_UP:
                        brake.setAlpha(TRANSPARENCY);
                        ARSimpleNativeCarsActivity.onBrakeUp();
                        return true;
                }
                return false;
            }
        });

        final ImageView accelerator = (ImageView) findViewById(R.id.accelerator_image);
        accelerator.setAlpha(TRANSPARENCY);
        accelerator.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        accelerator.setAlpha(1.0f);
                        ARSimpleNativeCarsActivity.onAcceleratorDown();
                        return true;
                    case MotionEvent.ACTION_UP:
                        accelerator.setAlpha(TRANSPARENCY);
                        ARSimpleNativeCarsActivity.onAcceleratorUp();
                        return true;
                }
                return false;
            }
        });
    }

    public void onStop() {
        SimpleNativeRenderer.demoShutdown();

        super.onStop();
    }

    @Override
    protected ARRenderer supplyRenderer() {
        return simpleNativeRenderer;
    }

    @Override
    protected FrameLayout supplyFrameLayout() {
        return (FrameLayout) this.findViewById(R.id.mainLayout);

    }

    public void onSettingsPressed(View view) {
        Intent intent = new Intent(this, CameraPreferencesActivity.class);
        startActivity(intent);
    }
}