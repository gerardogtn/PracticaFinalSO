#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <signal.h>

#define  PUERTO     8000     //numero del puerto
#define  MSGSIZE    1024   /* longitud de los mensajes */

main(argc, argv)
int argc;
char *argv[];
{
  char mensaje[MSGSIZE];
  int i;
  int s, ns;
  struct sockaddr_in sin;
  if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  { //asignacion
    perror("error socket");
    exit(1);
  }

  bzero(&sin, sizeof(sin)); // llenado de parametros del servidor

  sin.sin_family=AF_INET;
  sin.sin_port=htons(PUERTO);
  sin.sin_addr.s_addr=htonl(INADDR_ANY);

  if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) == -1) //creando socket
  {
    perror("tomd: bind");
    exit(1);
  }
  if (listen(s, 5) == -1) //escuchando por el socket
  {
    perror("tomd: listen");
    exit(1);
  }
/* i = 0; */
/*  while(i < 1) */
  while(1)
  {
    if ((ns = accept(s, 0, 0)) == -1) //peticion de servicio aceptada
    {
      perror("error en conexion");
      exit(1);
    }

/*    while(1)
    { */
      if ( recv(ns, mensaje, MSGSIZE, 0) == -1)
      {
        perror("recvfrom");
        exit(1);
      }
      ++i;
      printf("=> %s\n", mensaje);
/*      printf ("bye"); */
/*    } */
    close(ns);
  }
}
/*mata proceso padre con senial externa*/
