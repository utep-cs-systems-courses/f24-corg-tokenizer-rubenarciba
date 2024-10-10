#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

int space_char(char c) {
  return (c == ' ' || c == '\t');
}

int non_space_char(char c) {
  return (c != ' ' && c != '\t' && c != '\0');
}

char* token_start(char *str) {
  while (*str && space_char(*str)) {
    str++; //skip leading spaces
  }
  return *str ? str : NULL;//return null if no tokens were found
}

char* token_terminator(char *token) {
  while (*token && non_space_char(*token)) {
    token++;//keep going until a space or the null terminator is found
  }
  return token;// return the space or null terminal terminator
}

int count_tokens(char *str) {
  int count = 0;
  char *start = token_start(str);

  while (start) {
    count++;
    start = token_start(token_terminator(start));//find the start of the next token
  }
  return count;
}

char *copy_str(char *inStr, short len){
  char *newStr = (char*) malloc(len+1);//allocate memory for the new str
  strncpy(newStr, inStr, len);
  newStr[len] = '\0';// null terminate the token
  return newStr;
}

char **tokenize(char* str){
  int num_tokens = count_tokens(str);
  char **tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
  int i = 0;
  char *start = token_start(str);

  while(start){
    char *end = token_terminator(start);
    tokens[i++] = copy_str(start, end - start);
    start = token_start(end);
  }
  tokens[i] = NULL; //null terminate the array of tokens
  return tokens;
}

void print_tokens(char **tokens){
  for (int i = 0; tokens[i] != NULL; i++){
    printf("%s\n", tokens[i]);
  }
}

void free_tokens(char **tokens){
  for (int i = 0; tokens[i] != NULL; i++){
    free(tokens[i]);//free each of the tokens
  }
  free(tokens);//free the array of the token pointers
}
