These are the working files up to a working HR monitor.
There are 3 relevant files, code for the Arduino working as a master over I2C (Arduino_double), the program on the ATtiny 85 working as a slave over I2C while also collecting the difference from beat to beat from the Heart rate monitor (i2c_difference), and the final file of relevance is (HR board.fzz) which is a fritzing file that is of the hardware I am using.
Arduino_double - for the Arduino using I2C acting as master on it
i2c_difference - for the ATtiny 85 using I2C acting as a slave while also in communication with a polar heart rate monitor
HR board.fzz - a layout of the hardware I am using
i2c_HR - is an other method I tried to use to send the heart rates in packets of 8 bytes.
i2c_counter - was just a demonstration that the ATtiny works 