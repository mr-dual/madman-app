package com.madman.app

import android.os.Bundle
import android.app.Activity
import com.madman.engine.EngineRenderView // 1. We import our engine UI component

class MainActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        
        // 2. We instantly instantiate our custom engine view using the current screen context
        val renderView = EngineRenderView(this)
        
        // 3. Instead of loading a text file or standard XML UI, we tell the phone: 
        // "Make this Vulkan rendering surface fill the entire user's screen."
        setContentView(renderView)
    }
}

