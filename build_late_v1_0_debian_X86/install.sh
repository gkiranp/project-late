#!/bin/bash
echo "------------------------------------------------------"
echo "Installing Log Analysis Tool and Engineering (LATE)..."
echo "------------------------------------------------------"
echo "Sorry, this is a dirty way of installation...."
echo "But, it works somehow !!!!"
echo "------------------------------------------------------"
echo "Author : Kiran Puranik (gkiranp@gmail.com)"
echo "License Terms :"
cat ./license.text
echo "------------------------------------------------------"
chmod 777 ./*
mkdir -p /opt/qt-5.4.2/
cp ./libQt5Core.so.5.4.2  ./libQt5Gui.so.5.4.2  ./libQt5Widgets.so.5.4.2 /usr/lib/i386-linux-gnu/
cp ./libicui18n.so.53.1 /usr/lib/i386-linux-gnu/
cp ./libicuuc.so.53.1 /usr/lib/i386-linux-gnu/
cp ./libicudata.so.53.1 /usr/lib/i386-linux-gnu/
cp ./libQt5DBus.so.5.4.2 /usr/lib/i386-linux-gnu/
tar -xf ./plugins.tar -C /opt/qt-5.4.2/
ln -s /usr/lib/i386-linux-gnu/libQt5Core.so.5.4.2 /usr/lib/i386-linux-gnu/libQt5Core.so.5
ln -s /usr/lib/i386-linux-gnu/libQt5Gui.so.5.4.2 /usr/lib/i386-linux-gnu/libQt5Gui.so.5
ln -s /usr/lib/i386-linux-gnu/libQt5Widgets.so.5.4.2 /usr/lib/i386-linux-gnu/libQt5Widgets.so.5
ln -s /usr/lib/i386-linux-gnu/libicui18n.so.53.1 /usr/lib/i386-linux-gnu/libicui18n.so.53
ln -s /usr/lib/i386-linux-gnu/libicuuc.so.53.1 /usr/lib/i386-linux-gnu/libicuuc.so.53
ln -s /usr/lib/i386-linux-gnu/libicudata.so.53.1 /usr/lib/i386-linux-gnu/libicudata.so.53
ln -s /usr/lib/i386-linux-gnu/libQt5DBus.so.5.4.2 /usr/lib/i386-linux-gnu/libQt5DBus.so.5.4
ln -s /usr/lib/i386-linux-gnu/libQt5DBus.so.5.4.2 /usr/lib/i386-linux-gnu/libQt5DBus.so.5
ln -s /usr/lib/i386-linux-gnu/libQt5DBus.so.5.4.2 /usr/lib/i386-linux-gnu/libQt5DBus.so
cp ./late /usr/bin/
cp ./qt.conf /usr/bin/
echo "Installation Complete !!"
echo "type late to run tool"
