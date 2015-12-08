//README for Executing our task2.c firewall

1.  Launch a clean copy of the Ubuntu Seed VM (Running Ubuntu Trusty Tahr 14.04)

2.  Open the Ubuntu Software Center, search for "git" all lowercase.

3.  Install git "Fast,scalable, distributed revision control system"

4.  Open a new terminal session

5.  Ensure your current working directory is /home/seed (you can use command pwd)

6.  Run the command git init

7.  Run the command git clone https://github.com/ppoplawska/EnterpriseDefenseFirewall

**note: If you want to verify that the files we submitted are in fact the same as the github
        files, then you can use our submitted files. Please ensure that they are in the same directory.

8.  navigate to the directory /home/seed/EnterpriseDefenseFirewall

9.  We have provided scripts that will make it easy to insert/remove/build/clean our firewall program  (task2.c)

10. Enable a sudo shell (sudo -s)

11. Ensure you are still in /home/seed/EnterpriseDefenseFirewall

12. run our custom script sbuild (you can do so by simply running "sbuild" or "./sbuild" from the repo directory),
you should see a Done. as the script finishes.

**note: If the build script fails, please ensure that you have sudo rights, and that it is point to correct kernel directory
        we have designed it to work with a fresh install of the SEED VM

**note: the sbuild script, makes the task2.ko, and inserts it into the kernel**

13. The firewall is now active, to test it you can attempt to
    connect to any of the following ip addresses, the are all blocked by the firewall

    128.227.9.48 // www.ufl.edu
    128.227.248.40 // www.cise.ufl.edu
    206.190.36.45 // www.yahoo.com

14. To disable the firewall simply run rmmod task2.ko

**note: to rebuild the firewall, run sbuild again**
