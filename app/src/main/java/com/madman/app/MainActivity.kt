package com.madman.app

import android.os.Bundle
import android.app.Activity
import com.madman.engine.EngineRenderView 

class MainActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        
        val renderView = EngineRenderView(this)
        
        setContentView(renderView)
    }
}

