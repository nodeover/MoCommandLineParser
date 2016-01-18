#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void argumentUsage(char *myName){
    printf("usage: %s [-a foo --b=bar]\n",myName);
    printf("\t%s -a  : foo\n",myName);
    printf("\t%s --b  : bar\n",myName);
}

int setArgument(char *option, char* data){
    printf("%s = %s\n",option,data);
    return 1;
}

int parseArgument(int argc, char *argv[]){
    int strLen,strPos;
    char *dataStr, *optStr;
    for(int i=1;i<argc;i++){
        strLen = (int)strlen(argv[i]);
        //length of less than 2 character is exception. || didn't start with '-'
        if(strLen<2 || argv[i][0]!='-') return 0;
        else{ //option flag start.
            //Support for long option name(ex: --host=example.com)
            if(argv[i][1] == '-'){
                //only option name of '--' is ignored.
                if(strLen==2) return 0;
                else{
                    //search of split char '=' of between option and data.(without '--')
                    dataStr = strchr(&argv[i][2],'=');
                    // found
                    if(dataStr!=NULL){
                        //Position value of '=' in string. (ex: abc=123 -> 4)
                        strPos = (int)(dataStr-&argv[i][2])+1;
                        //option name string copy.
                        optStr = malloc(sizeof(char)*strPos);
                        strncpy(optStr, &argv[i][2], strPos-1);
                        //data string copy.
                        dataStr = malloc(sizeof(char)*(strlen(&argv[i][2])-strPos+1));
                        strncpy(dataStr, &argv[i][2]+strPos, strlen(&argv[i][2])-strPos);
                    }
                    // no found(it means this option isn't contain data.) (==NULL)
                    else{
                        //option name string copy.
                        optStr = malloc(sizeof(char)*(strLen-1));
                        strcpy(optStr,&argv[i][2]);
                        //data string set to default.
                        dataStr = malloc(sizeof(char));
                        *dataStr = '1';
                    }
                }
            }
            //one length option name.
            else{
                //Has a spacer between option name and data.
                if(strLen==2){
                    optStr = malloc(sizeof(char)*strLen);
                    strcpy(optStr,&argv[i][1]);
                    //next data none.
                    if(!(i+1 < argc)){
                        //data string set to default.
                        dataStr = malloc(sizeof(char));
                        *dataStr = '1';
                    }
                    else{
                        //next data none. new option starting.
                        if(argv[i+1][0]=='-'){
                            //data string set to default.
                            dataStr = malloc(sizeof(char));
                            *dataStr = '1';
                        }
                        else{
                            //data string set to default.
                            dataStr = malloc(sizeof(char) * (strlen(argv[++i])+1));
                            strcpy(dataStr,argv[i]);
                        }
                    }
                }
                //No spacer between option name and data.
                else{
                    optStr = malloc(sizeof(char)*2);
                    strncpy(optStr,&argv[i][1],1);
                    //data string set to default.
                    dataStr = malloc(sizeof(char)*strlen(&argv[i][1]));
                    strcpy(dataStr,&argv[i][1]+1);
                }
            }
        }
        
        //set options.
        setArgument(optStr,dataStr); //opt 설정.
        //freeing memory.
        free(dataStr);
        free(optStr);
    }
    
    return 1;
}

int main(int argc, char** argv){
    if(!parseArgument(argc, argv)){
        argumentUsage(argv[0]);
    }
    return 0;
}