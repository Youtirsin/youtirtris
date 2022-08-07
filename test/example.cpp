#include <Windows.h>

#include <iostream>
#include <thread>

using namespace std;

int main() {
  HANDLE screenHandle = CreateConsoleScreenBuffer(
      GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  if (screenHandle == INVALID_HANDLE_VALUE) {
    cout << "error creating screen buffer handle\n";
    return -1;
  }
  SetConsoleActiveScreenBuffer(screenHandle);
  DWORD byteWritten;
  char buffer[24] = { 0 };
  char val;

  for (int i = 0; i < 10; ++i) {
    val = i + '0';
    for (int i = 0; i < 24; i++) {
      buffer[i] = val;
    }
    buffer[10] = '\n';
    buffer[11] = '\r';
    buffer[22] = '\n';
    buffer[23] = '\r';
    WriteConsoleOutputCharacter(screenHandle, buffer, 24, {0, 0}, &byteWritten);
    this_thread::sleep_for(1s);
  }

  CloseHandle(screenHandle);
  return 0;
}
