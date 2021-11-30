#include<unistd.h>
void plot(char * fname) {
    int pid;
    if((pid = fork())==0){
        if(execlp("python", "python","hasse.py", fname, (char*) NULL) == -1)
        {
        	execlp("python3", "python3", "hasse.py", fname, (char*) NULL);
        };
    }
}

/* int main(){
    plot("SampleInput.csv");
    return 0;
} */
