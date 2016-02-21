ino build
sudo /etc/init.d/ser2net stop
sudo python tools/reset_arduino.py &
ino upload -m mega2560 -p /dev/ttyAMA0
sudo /etc/init.d/ser2net start
