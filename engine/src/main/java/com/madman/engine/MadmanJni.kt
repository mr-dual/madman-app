package com.madman.engine

import android.view.Surface

class MadmanJni {
    companion object {
        init {
            System.loadLibrary("madman_engine")
        }
    }

    external fun initialize(surface: Surface)
    external fun resize(width: Int, height: Int)
    external fun terminate()
}

