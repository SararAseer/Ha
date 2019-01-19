#include "pipe_networking.h"

char * SERVER_PIPE = "WKP";


int server_handshake(int *to_client) {
  mkfifo(SERVER_PIPE,0666);
  printf("Server: Created connection to client pipe\n");
  int client_server = open(SERVER_PIPE,O_RDONLY);

  char pipe_name[HANDSHAKE_BUFFER_SIZE];
  read(client_server, pipe_name, HANDSHAKE_BUFFER_SIZE);
  printf("Server: Read server to client pipe name\n");

  remove(SERVER_PIPE);
  printf("Server: Removed server peipe\n");

  int f = fork();
  if(f) return 0;

  int server_client = open(pipe_name,O_WRONLY);
  write(server_client,ACK,HANDSHAKE_BUFFER_SIZE);
  printf("Server: sent %s to client\n",ACK);

  char acknowledgement[HANDSHAKE_BUFFER_SIZE];
  read(client_server, acknowledgement, HANDSHAKE_BUFFER_SIZE);
  printf("Server: Recieved %s\n", acknowledgement);

  *to_client = server_client;
  return client_server;
}

int client_handshake(int *to_server) {
  mkfifo("client_pi",0666);
  printf("Client: Created client to server pipe\n");

  int client_server = open(SERVER_PIPE,O_WRONLY);
  char pipe_name[HANDSHAKE_BUFFER_SIZE] = "client_pi";
  write(client_server, pipe_name, HANDSHAKE_BUFFER_SIZE);
  printf("Client: Sent client to server pipe name\n");

  int server_client = open("client_pi",O_RDONLY);
  char acknowledgement[HANDSHAKE_BUFFER_SIZE];
  read(server_client, acknowledgement, HANDSHAKE_BUFFER_SIZE);
  printf("Client: Recieved %s\n", acknowledgement);

  remove("client_pi");
  printf("Client: Removed client to server pipe\n");

  write(client_server, acknowledgement, HANDSHAKE_BUFFER_SIZE);
  printf("Client: Sent acknowledgement back to server\n");

  *to_server = client_server;
  return server_client;
}
