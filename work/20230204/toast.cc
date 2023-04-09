#include <windows.h>

#include <iostream>

void func(const char* title, const char* body);
void func1();

int main() {
  func("test title", "test_body!!!");
  return 0;
}

void func(const char* title, const char* body) {
  char cmd[1024];
  char cmd_[1024] =
      "powershell ^&{"
      "$title = '%s';"
      "$body = '%s';"
      "$TT02 = [Windows.UI.Notifications.ToastTemplateType, "
      "Windows.UI.Notifications, ContentType = WindowsRuntime]::ToastText02;"
      "$TempCont = [Windows.UI.Notifications.ToastNotificationManager, "
      "Windows.UI.Notifications, ContentType = "
      "WindowsRuntime]::GetTemplateContent($TT02);"
      "$TempCont.SelectSingleNode('//text[@id=\"1\"]').InnerText = $title;"
      "$TempCont.SelectSingleNode('//text[@id=\"2\"]').InnerText = $body;"
      "$AppId = "
      "'{1AC14E77-02E7-4E5D-B744-2EB1AE5198B7}\\WindowsPowerShell\\v1."
      "0\\powershell.exe';"
      "[Windows.UI.Notifications.ToastNotificationManager]::"
      "CreateToastNotifier($AppId).Show($TempCont);"
      "}";
  snprintf(cmd, sizeof(cmd), cmd_, title, body);
  system(cmd);
}

void func1() {
  char cmd[1024] =
      //"powershell ^&{"
      "powershell ^&{"
      "$xml =\'<toast><visual><binding "
      "template=\"ToastGeneric\"><text>Hello</text><text>message</text></"
      "binding></visual></toast>\';"
      "Write-Host $xml"
      "$XmlDocument = [Windows.Data.Xml.Dom.XmlDocument, "
      "Windows.Data.Xml.Dom.XmlDocument, ContentType = WindowsRuntime]::New();"
      "$Xmldocument.loadXml($xml);"
      "$AppId = "
      "'{1AC14E77-02E7-4E5D-B744-2EB1AE5198B7}\\WindowsPowerShell\\v1."
      "0\\powershell.exe';"
      "[Windows.UI.Notifications.ToastNotificationManager, "
      "Windows.UI.Notifications, ContentType = "
      "WindowsRuntime]::CreateToastNotifier($AppId).Show($XmlDocument);"
      "}";
  // std::cout << cmd << std::endl;
  system(cmd);
}