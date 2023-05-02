Param($Arg1, $Arg2, $Arg3)


Function main () {  
  $title = $Arg1
  $contents = $Arg2
  $sleep_time = $Arg3 #sec
  # $title = "aaaa"#$Arg1
  # $contents = "bbb"#$Arg2
  Start-Sleep -s $sleep_time
  toast_notification -title $title -contents $contents
}




Function toast_notification {
  Param (
    [string] $title,
    [string] $contents
  )
  $xml = @"
<toast>  
  <visual>
    <binding template="ToastGeneric">    
      <text>$title</text>
      <text>$contents</text>
    </binding>
  </visual>
  </toast>
"@ 
  #Write-Host $xml
    
  $XmlDocument = [Windows.Data.Xml.Dom.XmlDocument, Windows.Data.Xml.Dom.XmlDocument, ContentType = WindowsRuntime]::New()
  $XmlDocument.loadXml($xml)
  $AppId = '{1AC14E77-02E7-4E5D-B744-2EB1AE5198B7}\WindowsPowerShell\v1.0\powershell.exe'
  [Windows.UI.Notifications.ToastNotificationManager, Windows.UI.Notifications, ContentType = WindowsRuntime]::CreateToastNotifier($AppId).Show($XmlDocument)

  return 
}

main

  
