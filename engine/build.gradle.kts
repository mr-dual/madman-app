import org.jetbrains.kotlin.gradle.tasks.KotlinCompile
import org.jetbrains.kotlin.gradle.dsl.JvmTarget

plugins {
    id("com.android.library")
    id("org.jetbrains.kotlin.android")
}

android {
    namespace = "com.madman.engine"
    compileSdk = 35
    buildToolsVersion = "35.0.1"
    ndkVersion = "29.0.14206865"
    ndkPath = "/data/data/com.termux/files/home/android-ndk-r29"

    defaultConfig {
        minSdk = 24  

        externalNativeBuild {
            cmake {
                arguments(
                    "-DANDROID_STL=c++_shared", 
                    "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
                )
                cppFlags("-std=c++20")
            }
        }
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }

    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1+"
        }
    }
}

// OUTSIDE the android block
tasks.withType<KotlinCompile>().configureEach {
    compilerOptions {
        jvmTarget.set(JvmTarget.JVM_17)
    }
}

