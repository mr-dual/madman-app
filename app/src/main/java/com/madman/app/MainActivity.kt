package com.madman.app

import com.google.androidgamesdk.GameActivity

class MainActivity : GameActivity() {
    companion object {
        init{
            System.loadLibrary("c++_shared")
            System.loadLibrary("app_main")
        }
    }
    
}
