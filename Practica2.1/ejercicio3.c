#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main() {
  int i;
  for (i = 0; i < 255; i++)
    if(setuid(i) == -1){
       printf("Error: %d, %s\n", i, strerror(i));
   return 1;
}

/*
A partir del error 133 ya solo aparece Error: i, Unknown error i

Error: 0, Success
Error: 1, Operation not permitted
Error: 2, No such file or directory
Error: 3, No such process
Error: 4, Interrupted system call
Error: 5, Input/output error
Error: 6, No such device or address
Error: 7, Argument list too long
Error: 8, Exec format error
Error: 9, Bad file descriptor
Error: 10, No child processes
Error: 11, Resource temporarily unavailable
Error: 12, Cannot allocate memory
Error: 13, Permission denied
Error: 14, Bad address
Error: 15, Block device required
Error: 16, Device or resource busy
Error: 17, File exists
Error: 18, Invalid cross-device link
Error: 19, No such device
Error: 20, Not a directory
Error: 21, Is a directory
Error: 22, Invalid argument
Error: 23, Too many open files in system
Error: 24, Too many open files
Error: 25, Inappropriate ioctl for device
Error: 26, Text file busy
Error: 27, File too large
Error: 28, No space left on device
Error: 29, Illegal seek
Error: 30, Read-only file system
Error: 31, Too many links
Error: 32, Broken pipe
Error: 33, Numerical argument out of domain
Error: 34, Numerical result out of range
Error: 35, Resource deadlock avoided
Error: 36, File name too long
Error: 37, No locks available
Error: 38, Function not implemented
Error: 39, Directory not empty
Error: 40, Too many levels of symbolic links
Error: 41, Unknown error 41
Error: 42, No message of desired type
Error: 43, Identifier removed
Error: 44, Channel number out of range
Error: 45, Level 2 not synchronized
Error: 46, Level 3 halted
Error: 47, Level 3 reset
Error: 48, Link number out of range
Error: 49, Protocol driver not attached
Error: 50, No CSI structure available
Error: 51, Level 2 halted
Error: 52, Invalid exchange
Error: 53, Invalid request descriptor
Error: 54, Exchange full
Error: 55, No anode
Error: 56, Invalid request code
Error: 57, Invalid slot
Error: 58, Unknown error 58
Error: 59, Bad font file format
Error: 60, Device not a stream
Error: 61, No data available
Error: 62, Timer expired
Error: 63, Out of streams resources
Error: 64, Machine is not on the network
Error: 65, Package not installed
Error: 66, Object is remote
Error: 67, Link has been severed
Error: 68, Advertise error
Error: 69, Srmount error
Error: 70, Communication error on send
Error: 71, Protocol error
Error: 72, Multihop attempted
Error: 73, RFS specific error
Error: 74, Bad message
Error: 75, Value too large for defined data type
Error: 76, Name not unique on network
Error: 77, File descriptor in bad state
Error: 78, Remote address changed
Error: 79, Can not access a needed shared library
Error: 80, Accessing a corrupted shared library
Error: 81, .lib section in a.out corrupted
Error: 82, Attempting to link in too many shared libraries
Error: 83, Cannot exec a shared library directly
Error: 84, Invalid or incomplete multibyte or wide character
Error: 85, Interrupted system call should be restarted
Error: 86, Streams pipe error
Error: 87, Too many users
Error: 88, Socket operation on non-socket
Error: 89, Destination address required
Error: 90, Message too long
Error: 91, Protocol wrong type for socket
Error: 92, Protocol not available
Error: 93, Protocol not supported
Error: 94, Socket type not supported
Error: 95, Operation not supported
Error: 96, Protocol family not supported
Error: 97, Address family not supported by protocol
Error: 98, Address already in use
Error: 99, Cannot assign requested address
Error: 100, Network is down
Error: 101, Network is unreachable
Error: 102, Network dropped connection on reset
Error: 103, Software caused connection abort
Error: 104, Connection reset by peer
Error: 105, No buffer space available
Error: 106, Transport endpoint is already connected
Error: 107, Transport endpoint is not connected
Error: 108, Cannot send after transport endpoint shutdown
Error: 109, Too many references: cannot splice
Error: 110, Connection timed out
Error: 111, Connection refused
Error: 112, Host is down
Error: 113, No route to host
Error: 114, Operation already in progress
Error: 115, Operation now in progress
Error: 116, Stale file handle
Error: 117, Structure needs cleaning
Error: 118, Not a XENIX named type file
Error: 119, No XENIX semaphores available
Error: 120, Is a named type file
Error: 121, Remote I/O error
Error: 122, Disk quota exceeded
Error: 123, No medium found
Error: 124, Wrong medium type
Error: 125, Operation canceled
Error: 126, Required key not available
Error: 127, Key has expired
Error: 128, Key has been revoked
Error: 129, Key was rejected by service
Error: 130, Owner died
Error: 131, State not recoverable
Error: 132, Operation not possible due to RF-kill
Error: 133, Memory page has hardware error

*/
