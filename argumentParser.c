#include <stdio.h>
#include <string.h>

void argumentUsage(char *myName){
    printf("Usage: %s [-a foo --b=bar]\n",myName);
    printf("-a  : foo\n");
    printf("--b  : bar\n");
}

void setArgument(char *option, char* data){
    printf("%s = %s\n",option,data);
}

int parseArgument(int argc, char *argv[]){
    int strLen,strPos;
    char *dataStr, *optStr, *argStr;
    for(int i=1;i<argc;i++){
        //Option flag start.
        if(argv[i][0] == '-'){
            strLen = (int)strlen(argv[i]);
            //length of less than 1 character is exception.
            if(strLen < 2)
                return 0;
            //Support for long option name(ex: --host=example.com)
            if(argv[i][1] == '-'){
                //Copy string to temporary variable. not contained option flag '-'
                argStr = malloc(sizeof(char)*(strLen-1));
                strcpy(argStr, &argv[i][2]);
                //search of split char '=' of between option and data.
                dataStr = strchr(argStr,'=');
                // found
                if(dataStr!=NULL){
                    //Position value of '=' in string. (ex: abc=123 -> 4)
                    strPos = (int)(dataStr-argStr)+1;
                    //option name string copy.
                    optStr = malloc(sizeof(char)*strPos);
                    strncpy(optStr, argStr, strPos-1);
                    //data string copy.
                    dataStr = malloc(sizeof(char)*(strlen(argStr)-strPos+1));
                    strncpy(dataStr, argStr+strPos, strlen(argStr)-strPos);
                }
                // no found(it means this option isn't contain data.) (==NULL)
                else{
                    //option name string copy.
                    optStr = malloc(sizeof(char)*(strLen-1));
                    strcpy(optStr,argStr);
                    //data string set to default.
                    dataStr = malloc(sizeof(char));
                    *dataStr = 1;
                }
                //set options.
                setArgument(optStr,dataStr);
                //freeing memory.
                free(argStr);
                free(dataStr);
                free(optStr);
            }
            //one length option name.
            else{
                argStr = malloc(sizeof(char)*strLen);
                //Copy string to temporary variable. not contained option flag '-'
                strcpy(argStr, &argv[i][1]);
                //No spacer between option name and data.
                if(strLen>2){
                    optStr = malloc(sizeof(char)*2);
                    strncpy(optStr,argStr,1);
                    //data string set to default.
                    dataStr = malloc(sizeof(char)*strlen(argStr));
                    strcpy(dataStr,argStr+1);
                }
                //Has a spacer between option name and data.
                else{
                    optStr = malloc(sizeof(char)*strLen);
                    strcpy(optStr,argStr);
                    //next data none.
                    if(!(i+1 < argc)){
                        //data string set to default.
                        dataStr = malloc(sizeof(char));
                        *dataStr = 1;
                    }
                    else{
                        //next data none. new option starting.
                        if(argv[i+1][0]=='-'){
                            //data string set to default.
                            dataStr = malloc(sizeof(char));
                            *dataStr = 1;
                        }
                        else{
                            //data string set to default.
                            dataStr = malloc(sizeof(char) * (strlen(argv[++i])+1));
                            strcpy(dataStr,argv[i]);
                        }
                    }
                }
                //set options.
                setArgument(optStr,dataStr); //opt 설정.
                //freeing memory.
                free(argStr);
                free(dataStr);
                free(optStr);
            }
        }
        else{ //didn't start with '-'
            return 0;
        }
    }
    
    return 1;
}

int main(int argc, char** argv){
    if(!parseArgument(argc,argv)){
        argumentUsage(argv[0]);
    }
    
    return 0;
}