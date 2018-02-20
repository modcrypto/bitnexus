
Debian
====================
This directory contains files used to package bitcoinnoded/bitcoinnode-qt
for Debian-based Linux systems. If you compile bitcoinnoded/bitcoinnode-qt yourself, there are some useful files here.

## bitcoinnode: URI support ##


bitcoinnode-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitcoinnode-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitcoinnode-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoinnode128.png` to `/usr/share/pixmaps`

bitcoinnode-qt.protocol (KDE)

