import com.google.androidsdk.GameActivity

class MainActivity : GameActivity() {
    companion object {
        init{
            System.loadLibrary("app_main")
        }
    }
    
}
