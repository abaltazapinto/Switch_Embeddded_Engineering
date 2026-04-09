#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>


int serialOpen(const char *device, const int baud)
{
  struct termios options ;
  speed_t myBaud ;
  int     status, fd ;

  switch (baud)
  {
    case      50:	myBaud =      B50 ; break ;
    case      75:	myBaud =      B75 ; break ;
    case     110:	myBaud =     B110 ; break ;
    case     134:	myBaud =     B134 ; break ;
    case     150:	myBaud =     B150 ; break ;
    case     200:	myBaud =     B200 ; break ;
    case     300:	myBaud =     B300 ; break ;
    case     600:	myBaud =     B600 ; break ;
    case    1200:	myBaud =    B1200 ; break ;
    case    1800:	myBaud =    B1800 ; break ;
    case    2400:	myBaud =    B2400 ; break ;
    case    4800:	myBaud =    B4800 ; break ;
    case    9600:	myBaud =    B9600 ; break ;
    case   19200:	myBaud =   B19200 ; break ;
    case   38400:	myBaud =   B38400 ; break ;
    case   57600:	myBaud =   B57600 ; break ;
    case  115200:	myBaud =  B115200 ; break ;
    case  230400:	myBaud =  B230400 ; break ;
    case  460800:	myBaud =  B460800 ; break ;
    case  500000:	myBaud =  B500000 ; break ;
    case  576000:	myBaud =  B576000 ; break ;
    case  921600:	myBaud =  B921600 ; break ;
    case 1000000:	myBaud = B1000000 ; break ;
    case 1152000:	myBaud = B1152000 ; break ;
    case 1500000:	myBaud = B1500000 ; break ;
    case 2000000:	myBaud = B2000000 ; break ;
    case 2500000:	myBaud = B2500000 ; break ;
    case 3000000:	myBaud = B3000000 ; break ;
    case 3500000:	myBaud = B3500000 ; break ;
    case 4000000:	myBaud = B4000000 ; break ;

    default:
      return -2 ;
  }

  if ((fd = open (device, O_RDWR | O_NOCTTY | O_SYNC )) == -1) //| O_NONBLOCK
    return -1 ;

  fcntl (fd, F_SETFL, O_RDWR) ;

  tcgetattr (fd, &options) ;

    cfmakeraw   (&options) ;
    cfsetispeed (&options, myBaud) ;
    cfsetospeed (&options, myBaud) ;

    options.c_cflag |= (CLOCAL | CREAD) ; //Ignore modem control lines, Enable receiver 
    options.c_cflag &= ~PARENB ; //Disable parity generation on output and parity checking for input. 
    options.c_cflag &= ~CSTOPB ; //Just one stop bit
    options.c_cflag &= ~CSIZE ; //Cleans character size bits...
    options.c_cflag |= CS8 ; //...set 8 bits characters
    //disable canonical mode, echo, erase characterm, signal generation upon
    //receiving  INTR, QUIT, SUSP, or DSUSP characters, echo newline, extended input processing
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG | ECHONL | IEXTEN) ; 
    options.c_oflag = 0;
    options.c_iflag = 0;

    options.c_cc [VMIN]  =   1 ;
    options.c_cc [VTIME] = 0 ;	

  tcsetattr (fd, TCSANOW, &options) ;

  ioctl (fd, TIOCMGET, &status);

  status |= TIOCM_DTR ; //set "data terminal ready"
  status |= TIOCM_RTS ; //set "request to send"

  ioctl (fd, TIOCMSET, &status);

  ioctl(fd, TIOCEXCL, NULL);  //try exclusive access
	
  return fd ;
}

/*

TCSANOW
    the configuration is changed immediately.
TCSADRAIN
    the configuration is changed after all the output written to fd has been transmitted. This prevents the change from corrupting in-transmission data.
TCSAFLUSH
    same as above but any data received and not read will be discarded.
    
    
     
    
  ~ICANON
  
   In  noncanonical mode input is available immediately (without the user having to type a line-delimiter character), no input processing is performed, and line editing is disabled.
       The settings of MIN (c_cc[VMIN]) and TIME (c_cc[VTIME]) determine the circumstances in which a read(2) completes; there are four distinct cases:

       MIN == 0, TIME == 0 (polling read)
              If data is available, read(2) returns immediately, with the lesser of the number of bytes available, or the number of bytes requested.  If no data  is  available,  read(2)
              returns 0.

       MIN > 0, TIME == 0 (blocking read)
              read(2) blocks until MIN bytes are available, and returns up to the number of bytes requested.

       MIN == 0, TIME > 0 (read with timeout)
              TIME  specifies the limit for a timer in tenths of a second.  The timer is started when read(2) is called.  read(2) returns either when at least one byte of data is avail‐
              able, or when the timer expires.  If the timer expires without any input becoming available, read(2) returns 0.  If data is already available at the time of  the  call  to
              read(2), the call behaves as though the data was received immediately after the call.

       MIN > 0, TIME > 0 (read with interbyte timeout)
              TIME  specifies  the limit for a timer in tenths of a second.  Once an initial byte of input becomes available, the timer is restarted after each further byte is received.
              read(2) returns when any of the following conditions is met:

              *  MIN bytes have been received.

              *  The interbyte timer expires.

              *  The number of bytes requested by read(2) has been received.  (POSIX does not specify this termination condition, and on some  other  implementations  read(2)  does  not
                 return in this case.)

              Because  the  timer  is  started  only  after  the initial byte becomes available, at least one byte will be read.  If data is already available at the time of the call to
              read(2), the call behaves as though the data was received immediately after the call.

Raw mode

cfmakeraw() sets the terminal to something like the "raw" mode of the old Version 7 terminal driver: input is available character by character, echoing is disabled, and all special processing of terminal input and output characters is disabled. The terminal attributes are set as follows:

termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                | INLCR | IGNCR | ICRNL | IXON);
termios_p->c_oflag &= ~OPOST;
termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
termios_p->c_cflag &= ~(CSIZE | PARENB);
termios_p->c_cflag |= CS8;


*/