#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"

#define MAX_INPUT_SIZE 1024


//function to check if input starts with '!' followed by a number
int is_history_command(char *input){
  if (input[0] == '!' && strlen(input)>1){
    for(int i = 1; input[i] != '\0'; i++){
      if(input[i] < '0' || input[i] > '9'){
	return 0; //not a valid number after '!'
      }
    }
    return 1; //valid command
  }
  return 0; // doesn't start with '!'
}

//function to extract the number from '!n' command

int extract_command_number(char *input){
  return atoi(&input[1]); //conver the part after '!' to an integer
}


int main(){
  char input[MAX_INPUT_SIZE];
  List *history = init_history(); //initialize the history list

  while(1){
    printf("Enter a string (or 'exit' to quit, 'history' to view history, 'iN' to recall history): ");
    fgets(input, MAX_INPUT_SIZE, stdin);

    //romove the trailing new line character from fgets
    input[strcspn(input, "\n")] = '\0';


    //exit conditions
    if(strcmp(input, "exit") == 0){
      break;
    }

    //view history command
    if (strcmp(input, "history") == 0){
      print_history(history);
      continue;
    }

    //check if the history command is valid
    if (is_history_command(input)){
      int command_number = extract_command_number(input);
      char *history_item = get_history(history, command_number);

      if(history_item != NULL){
	printf("Recalled: %s\n", history_item);

	//tokenize the recalled history item
	char **tokens = tokenize(history_item);
	print_tokens(tokens);

	//free tokenized string
	free_tokens(tokens);
      }
      else{
	printf("no history item with ID %d\n" , command_number);
      }
    }
    else{
      //tokenize and process the input
      char **tokens = tokenize(input);
      print_tokens(tokens);

      //add the input to the history
      add_history(history, input);

      //free the tokenized string
      free_tokens(tokens);
    }
  }

  //free the history list
  free_history(history);

  return 0;
}
