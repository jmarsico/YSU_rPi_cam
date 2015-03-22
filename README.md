# YSU_rPi_cam
Youngstown State University workshop for building Raspberry Pi + openFrameworks digital camera. 

##Overview
This is a DIY digital camera designed to introduce workshop attendees the [Raspberry Pi computer][1], [openFrameworks C++ toolkit][2] and basic image processing. This repo includes an openFrameworks application that pulls in video from a webcam, processes that video into either an overlaid still image or a GIF. The application saves files to a different partition on the Pi's SD card. That way, users can turn off the pi, remove the SD card, plug the SD card into their computer and access the images, similar to a traditional digital camera. This has been developed and tested on `2015-02-16-raspbian-wheezy`. 




##Dependencies
You will need to download the following:

1. [openFrameworks for Raspberry Pi (linux armv6)][3]
2. [ofxGifEncoder][4]
3. [ofxWiringPi][5] (this was developed by Joshua Noble, but the linked branch has a different directory structure that works with the included configure.make)


##Installation
1. Download and install openframeworks. Follow the setup instructions [here][6]. 
2. Move into the addons folder within openFrameworks and clone ofxGifEncoder ofxWiringPi
3. Move into the apps/myApps/YSU_rPi_cam folder.  Make sure there is a copy of ofxWiringPi in the addons folder within YSU_rPi_cam. If the folder is empty, copy ofxWiringPi from the main openFrameworks addons folder to this addons folder


##Basic Usage
1. Hook up a button, connecting to a ground pin and pin 7 (using [wiringPi pin assignments][7])
2. Hook up an LED to another ground pin and pin 2 (again, using wiringPi pin assignments).
3. Within the ofApp.cpp, be sure to change the folder to which the files save. (look in the `saveGif()` and `saveOverlay()` functions)
4. Run the application!
5. A short press of the button will record a still image consisting of 10 overlaid images
6. A long (over 1 second) press of the button will record a 10 image GIF.

##Preparing 16gb SD Card
###Add a FAT32 Partition
  http://www.cenolan.com/2013/03/adding-a-fat32-partition-to-raspbian-on-a-rasperry-pi/

###Downlad and Install openFrameworks
 1. In the home directory, download oF:  `wget http://www.openframeworks.cc/versions/v0.8.4/of_v0.8.4_linuxarmv6l_release.tar.gz`
 2. unzip: `tar -zxvf of_v0.8.4_linuxarmv6l_release.tar.gz`
 3. delete the tar file (we need to conserve space on this little partition): `rm -r of_v0.8.4_linuxarmv6l_release.tar.gz`
 4. install dependencies: `./of_v0.8.4_linuxarmv6l_release/scripts/linux/debian_armv6l/install_dependencies.sh`


###Set up Samba
1. `sudo apt-get install samba`
2. `sudo apt-get install samba-common-bin`
3. go to samba folder: `cd /etc/samba`
4. make a copy original conf file: `cp smb.conf smb.conf.original`
5. delete old conf file and make new one: `sudo rm smb.conf && sudo nano smb.conf`
6. copy this into the file and modify username and path for sharing
```
    [global]
    workgroup = WORKGROUP
    netbios name = SAMBA
    server string = Samba Server %v
    map to guest = Bad User
    log file = /var/log/samba/log.%m
    max log size = 50
    socket options = TCP_NODELAY SO_RCVBUF=8192 SO_SNDBUF=8192
    preferred master = No
    local master = No
    dns proxy = No
    security = User

   # Share
   [Data]
   path = <path that you want to share>
   valid users = <username>
   read only = No
   create mask = 0755
   directory mask = 0755
   ```

7. Add your password   `sudo smbpasswd -a <username>`
8. Restart the samba service. `sudo service samba restart`
9. You should now be able to connect from you Mac.

###Setting up ofxWiringPi
1. create addons folder within project root
2. place ofxWiringPi into addons folder
3. add this to config.make:
```  
WIRINGPI_DIR = $(PROJECT_ROOT)/addons/ofxWiringPi/lib
WIRING_PI_LIB = $(WIRINGPI_DIR)/libwiringPi.a
PROJECT_LDFLAGS=-Wl,-rpath=./libs -L$(WIRINGPI_DIR) $(WIRING_PI_LIB)
```

##More Information
Check out the [workshop google doc][8] for more detailed usage and assembly information, links to .stl files for the case, and an overview of the workshop schedule.

Special thanks to [Dana Sperry][9] and [Youngstown State University][10] for funding the development of the camera and hosting the workshop. Thanks to [Dan Russo][11] for designing and fabricating the case for the camera.

[1]: http://www.raspberrypi.org/
[2]: http://www.openframeworks.cc/
[3]: http://www.openframeworks.cc/download/
[4]: https://github.com/jesusgollonet/ofxGifEncoder
[5]: https://github.com/jmarsico/ofxWiringPi  
[6]: http://www.openframeworks.cc/setup/raspberrypi/Raspberry-Pi-Getting-Started.html
[7]: https://projects.drogon.net/raspberry-pi/wiringpi/pins/
[8]: https://docs.google.com/document/d/1YMw73aOF5FGlJ_VMr5oSEBMXrsuZEWxUTwLzXXXZtwg/edit
[9]: http://www.danasperry.com/
[10]: http://www.ysu.edu/
[11]: http://solidhaptik.io/

