#include <stdio.h>
#include "http_request.h"


int main(){
    HttpObject object = {.host="gruncan.dev", .path="spotifyC", .port=80, .method=GET };
    HttpResponse* response = send_http_request(&object);
    
    printf("%s\n", response->response);

}
