#include <stdio.h>
#include <stdlib.h>

void logCmd(char* cmdLine, FILE *f) {
    if(f == NULL){
        printf("An error happened while logging the command line.");
        exit(1);
    }
    fprintf(f, "%s\n", cmdLine);
}
void resetLogFile(){
    FILE *f = fopen("logCmd.txt", "wb");
    if(!f){
        printf("An error happened while resetting the log file.");
        exit(1);
    }
}
// int main() {
//     char* cmd = "ls -l || echo 'good'";
//     FILE *f = fopen("logCmd.txt", "w");
//     resetLogFile();
//     for(int i = 0; i < 4; i++){
//         logCmd(cmd, f);
//     }
//     fclose(f);
//     return 0;
// }