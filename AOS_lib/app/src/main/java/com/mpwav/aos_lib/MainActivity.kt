package com.mpwav.aos_lib

import android.Manifest
import android.app.Activity
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.core.content.FileProvider
import com.mpwav.aos_lib.ui.theme.AOS_libTheme
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.io.File

class MainActivity : ComponentActivity() {
  external fun run(pathInput : String, pathOutput : String)
  init {
    // 네이티브 라이브러리 로드
    System.loadLibrary("ClearSenseProcessor")
  }

  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)
    checkAndRequestPermissions(this)
    enableEdgeToEdge()
    setContent {
      AOS_libTheme {
        Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
          var isButtonEnabled by remember { mutableStateOf(true) }
          var message by remember { mutableStateOf("RTF estimation") }

          Greeting(
            message = message,
            modifier = Modifier.padding(innerPadding),
            onButtonClick = {
              val pathInput = copyAssetToInternalStorage("input.wav")
              //val pathModel = copyAssetToInternalStorage("mpSE4_512_v21_mini.onnx")
              val dirOutput = getExternalFilesDir("")?.absolutePath
              val pathOutput = dirOutput + "/output.wav"
              Toast.makeText(this, "A", Toast.LENGTH_SHORT).show()
              isButtonEnabled = false

              CoroutineScope(Dispatchers.IO).launch {
                var totalTime  = 0
                var avgTime  = 0.0
                for( i in 1..10 ) {
                  val startTime = System.currentTimeMillis()
                  run(pathInput, pathOutput.toString())
                  val endTime = System.currentTimeMillis()
                  val elapsedTime = endTime - startTime
                  totalTime += elapsedTime.toInt()
                  avgTime = totalTime/i.toDouble()

                  withContext(Dispatchers.Main) {
                    Toast.makeText(this@MainActivity, "$i/10 : $avgTime ms", Toast.LENGTH_SHORT).show()
                    // TODO : set input data time
                    val curRTF = avgTime/29088
                    message = "$avgTime ms/ RTF : $curRTF / $i/10"
                  }
                }
                val RTF = avgTime/29088
                withContext(Dispatchers.Main) {
                  message = "Avg $avgTime ms/ RTF : $RTF"
                  isButtonEnabled = true
                }

              }

              //shareFile(this)
            },
            isButtonEnabled = isButtonEnabled
          )
        }
      }
    }
  }

  private fun copyAssetToInternalStorage(fileName: String): String {
    val file = File(filesDir, fileName)
    if (!file.exists()) {
      assets.open(fileName).use { inputStream ->
        file.outputStream().use { outputStream ->
          inputStream.copyTo(outputStream)
        }
      }
    }
    return file.absolutePath
  }
}



@Composable
fun Greeting(message: String, modifier: Modifier = Modifier,onButtonClick: () -> Unit, isButtonEnabled: Boolean) {
  Column( // 텍스트와 버튼을 수직 정렬
    modifier = modifier
      .fillMaxSize()
      .padding(16.dp), // 패딩 추가
    verticalArrangement = Arrangement.Center, // 수직 중앙 정렬
    horizontalAlignment = Alignment.CenterHorizontally // 수평 중앙 정렬
  ) {
    Text( // 기존 텍스트
      text = message
    )
    Spacer(modifier = Modifier.height(16.dp))
    Button( // 버튼 추가
      onClick = {
        onButtonClick()
      },
      enabled = isButtonEnabled
    ) {
      Text("Test")
    }
  }
}



@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
  AOS_libTheme {
    Greeting("Android",onButtonClick = {}, isButtonEnabled = true)
  }
}

fun shareFile(context: Context) {
  Log.i("MainActivity","shareFile()")
  val externalPath = File(context.getExternalFilesDir(null), "output.wav").absolutePath
  val file = File(context.filesDir, externalPath)
  if (!file.exists()) {
    Toast.makeText(context, "No File", Toast.LENGTH_SHORT).show()
    return
  }

  Log.i("MainActivity","shareFile() : set URI")
  val uri: Uri = FileProvider.getUriForFile(context, "${context.packageName}.fileprovider", file)

  val shareIntent = Intent(Intent.ACTION_SEND).apply {
    type = "text/plain" // 파일 MIME 타입
    putExtra(Intent.EXTRA_STREAM, uri)
    addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION) // URI 읽기 권한 부여
  }

  Log.i("MainActivity","shareFile() : shareIntent")
  context.startActivity(Intent.createChooser(shareIntent, "Share file via"))
}

fun checkAndRequestPermissions(activity: Activity) {
  val permissions = mutableListOf<String>()

  if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.Q) {
    if (ContextCompat.checkSelfPermission(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
      permissions.add(Manifest.permission.WRITE_EXTERNAL_STORAGE)
    }
  } else {
    if (ContextCompat.checkSelfPermission(activity, Manifest.permission.MANAGE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
      permissions.add(Manifest.permission.MANAGE_EXTERNAL_STORAGE)
    }
  }

  if (permissions.isNotEmpty()) {
    ActivityCompat.requestPermissions(activity, permissions.toTypedArray(), 1001)
  }
}