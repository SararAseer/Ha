#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  char input[BUFFER_SIZE];

  from_server = client_handshake( &to_server );
  while(1){
    printf("%s\n", "Please put in something, so i may be of use");
    fgets(input, BUFFER_SIZE, stdin);
    strtok(input, "\n");
    write(to_server, input, BUFFER_SIZE);

    read(from_server, input, BUFFER_SIZE);
    printf("Recieved %s\n", input);
  }
}
