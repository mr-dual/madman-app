package com.madman.engine

import android.view.Surface

class MadmanJni {
    companion object {
        init {
            System.loadLibrary("madman_engine")
        }
    }

    /** Initialize the renderer and loop
     * @param surface the android Surface view 
     **/
    external fun initialize(surface: Surface)

    /**Called when thw screen is resized
     * @param width the width of the new view
     * @param height the height of the new view
     **/
    external fun resize(width: Int, height: Int)

    /**
     * called when the screen is closed
     **/
    external fun terminate()
}

