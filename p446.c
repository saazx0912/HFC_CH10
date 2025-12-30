#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void open_url(char *url){
    char launch[255];
    sprintf(launch , "cmd /c start %s" , url);
    system(launch);
    sprintf(launch , "x-www-browser '%s' &" , url);
    system(launch);
    sprintf(launch , "open '%s'" , url);
    system(launch);
}

int main(){
    char *url = "https://tw.yahoo.com";
    open_url(url);
    return 0;
}