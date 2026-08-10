import org.jetbrains.kotlin.gradle.tasks.KotlinCompile
import org.jetbrains.kotlin.gradle.dsl.JvmTarget

plugins {
    id("com.android.application")
}

android {
    namespace = "com.madman.app"
    compileSdk = 37
    ndkVersion = "29.0.14206865"
    ndkPath = "/data/data/com.termux/files/home/android-ndk-r29"

    buildFeatures {
        prefab = true
    }

    defaultConfig {
        applicationId = "com.madman.app"
        minSdk = 24  
        targetSdk = 34
        versionCode = 1
        versionName = "0.0.1"

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
    
dependencies {
    implementation("androidx.games:games-activity:4.4.2")
    implementation("androidx.appcompat:appcompat:1.7.1")
    implementation("androidx.core:core-ktx:1.19.0")
    implementation(project(":engine"))
}

