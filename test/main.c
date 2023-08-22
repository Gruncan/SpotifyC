#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

#include "http_request.h"
#include "spotify_config.h"




#define REQUEST_TIMEOUT 20

static volatile bool thread_finished = false;
static volatile bool should_exit = false;

void sig_handler(int i){
    should_exit = true;
}

void* execute_http(void* arg){
    HttpObject* obj = (HttpObject*) arg;
    printf("Obj: %s %s %d %d\n", obj->host, obj->path, obj->port, obj->method);
    HttpResponse* response = send_http_request(obj);
    DEB_LOG("Returning from thread");
    thread_finished = true;
    return response;
}


int main(){
    signal(SIGINT, sig_handler);
    printf("Version: %s\n", SPOTIFY_PROJECT_VERSION);
    HttpObject object = {.host="gruncan.dev", .path="spotifyC", .port=80, .method=GET };
    pthread_t thread;
    HttpResponse* response;
    pthread_create(&thread, NULL, &execute_http, (void*) &object);
    DEB_LOG("Create thread");
    int c = 1;
    while (!thread_finished){
        sleep(1);
        printf("Waiting for thread to retrieve data %d\n", c++);
        if(should_exit){
            printf("Stopping thread!\n");
            pthread_cancel(thread);
            printf("Exiting...\n\n\n");
            return 0;
        } else if (c > REQUEST_TIMEOUT){
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
