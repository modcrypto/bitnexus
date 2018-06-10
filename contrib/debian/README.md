
Debian
====================
This directory contains files used to package bitnexusd/bitnexus-qt
for Debian-based Linux systems. If you compile bitnexusd/bitnexus-qt yourself, there are some useful files here.

## bitnexus: URI support ##


bitnexus-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitnexus-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitnexus-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitnexus128.png` to `/usr/share/pixmaps`

bitnexus-qt.protocol (KDE)

