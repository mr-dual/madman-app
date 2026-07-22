import org.jetbrains.kotlin.gradle.tasks.KotlinCompile
import org.jetbrains.kotlin.gradle.dsl.JvmTarget

plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")
}

android {
    namespace = "com.madman.app"
    compileSdk = 35
    buildToolsVersion = "35.0.1"
    ndkVersion = "29.0.14206865"
    ndkPath = "/data/data/com.termux/files/home/android-ndk-r29"

    defaultConfig {
        applicationId = "com.madman.app"
        minSdk = 24  
        targetSdk = 35
        versionCode = 1
        versionName = "0.0.1"
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
}

// OUTSIDE the android block
tasks.withType<KotlinCompile>().configureEach {
    compilerOptions {
        jvmTarget.set(JvmTarget.JVM_17)
    }
}

dependencies {
    implementation(project(":engine"))
}

