/*
A program to show the IP addresses for a host given on the command line

Pretty much a direct copy from the Beej tutorials

http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html

 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main( int argc, char *argv[] )
{
  struct addrinfo hints, *res, *p;
  int status;
  char ipstr[INET6_ADDRSTRLEN];

  if( argc != 2 )
	{
	  fprintf( stderr, "usage: showip hostname\n" );
	  return 1;

	}

  memset( &hints, 0, sizeof( hints ) );
  hints.ai_family = AF_UNSPEC;  //Can use AF_INET for IPv4 specifically, or AF_INET6 for IPv6
  hints.ai_socktype = SOCK_STREAM;  //TCP stream sockets

  if( (status = getaddrinfo( argv[1], NULL, &hints, &res ) ) != 0 )
	{
	  fprintf( stderr, "getaddrinfo: %s\n", gai_strerror( status ) );
	  return 2;

	}

  printf( "IP addresses for %s:\n\n", argv[1] );

  for( p = res; p != NULL; p = p->ai_next )
	{
	  void *addr;
	  char *ipver;

	  //Get the pointer to the address itself
	  //Defferent fields in IPv4 and IPv6

	  if( p->ai_family == AF_INET )  //This is IPv4
		{
		  struct sockaddr_in *ipv4 = ( struct sockaddr_in *)p->ai_addr;
		  addr = &( ipv4->sin_addr );
		  ipver = "IPv4";

		}
	  else  //Should be IPv6
		{
		  struct sockaddr_in6 *ipv6 = ( struct sockaddr_in6 *)p->ai_addr;
		  addr = &( ipv6->sin6_addr );
		  ipver = "IPv6";


		}

	  //The IP must be converted to a string in order to display it properly
	  inet_ntop( p->ai_family, addr, ipstr, sizeof( ipstr ) );
	  printf( "\t%s: %s\n", ipver, ipstr );

	}

  freeaddrinfo( res );  //Free the linked list

  return 0;

}
