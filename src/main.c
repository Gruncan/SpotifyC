#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#include "http_request.h"

#define REQUEST_TIMEOUT 20

bool thread_finished = false;

void* execute_http(void* arg){
    HttpObject* obj = (HttpObject*) arg;
    printf("Obj: %s %s %d %d\n", obj->host, obj->path, obj->port, obj->method);
    HttpResponse* response = send_http_request(obj);
    DEB_LOG("Returning from thread");
    thread_finished = true;
    return response;
}


int main(){
    HttpObject object = {.host="gruncan.dev", .path="spotifyC", .port=80, .method=GET };
    pthread_t thread;
    HttpResponse* response;
    pthread_create(&thread, NULL, &execute_http, (void*) &object);
    DEB_LOG("Create thread");
    int c = 1;
    while (!thread_finished){
        sleep(1);
        printf("Waiting for thread to retrieve data %d\n", c++);
        if (c > REQUEST_TIMEOUT){
            printf("Timeout! Failed to send retrieve information from socket\n");
            pthread_cancel(thread);
            return 0;
        }
        
    }
    pthread_join(thread, (void**) &response);
    DEB_LOG("After join")
    printf("Response: %s\n", response->response);
    
    printf("%s\n", response->response);

    return 0;

}
