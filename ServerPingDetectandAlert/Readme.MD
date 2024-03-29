Dashboard that shows who pings your linux box - PHP and TCPDUMP

Uses tcpdump and php to see who is pinging your linux box. 

Tcpdump buffers before it outputs to text file so I collect all tcpdump info and then use php to pull specific info.

tcpdump command - this can be setup on startup

sudo tcpdump -w > /var/www/html/dumpfile.txt
