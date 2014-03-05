1, the routine use of IWDG routine.

2, the use of
   (1) project file path: routine directory \ IWDG \ MDK-ARM \ Project.uvproj.
   (2) Please use the MDK 4.0 or later to open, MDK version is too low will lead to the identification project.
   (3) Download debugging tools ULINK.
   (4) Connect the USB cable plugged into the board CN3, and open HyperTerminal or serial debugging assistant, configure the baud rate 115200 bits, one stop bit, no parity.
   (5) HEX file is downloaded to the board, LED lights and port PB6 PB8 PC10 PC12 enemble cycle to move a stepper motors only one step at a time,using HyperTerminal or serial debugging assistant can see the debugging information indicates that routine run correctly.
 
3, note
   Be sure to download, debugging, running, keeping on board power, ULINK connected and plugged into the computer.
