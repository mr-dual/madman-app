package com.madman.engine

import android.content.Context
import android.util.AttributeSet
import android.view.SurfaceHolder
import android.view.SurfaceView
import kotlin.concurrent.thread

class EngineRenderView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null
) : SurfaceView(context, attrs), SurfaceHolder.Callback {

    private val jniBridge = MadmanJni()
    private var isRunning = false

    init {
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        // Sends the raw window handle directly down to Vulkan!
        jniBridge.initVulkan(holder.surface)
        
        isRunning = true
        thread(name = "MadmanRenderThread") {
            while (isRunning) {
                jniBridge.stepFrame()
                Thread.sleep(16)
            }
        }
        // Start your render loop worker thread here
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        jniBridge.resizeVulkan(width, height)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        isRunning = false
        jniBridge.terminateVulkan()
    }
}

