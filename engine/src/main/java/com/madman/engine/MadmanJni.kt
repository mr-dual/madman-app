package com.madman.engine

import android.view.Surface

class MadmanJni {
    // Tells the system to load libmadman_engine.so
    companion object {
        init {
            System.loadLibrary("madman_engine")
        }
    }

    // Native C++ methods declared in Kotlin
    external fun initVulkan(surface: Surface)
    external fun resizeVulkan(width: Int, height: Int)
    external fun stepFrame()
    external fun terminateVulkan()
}

