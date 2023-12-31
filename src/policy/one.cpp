#include <cstdlib>
#include<iostream>

#include "../state/state.hpp"
#include "./one.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move one::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;

  
  int k = depth;
  for(int i = 0; i < depth; i++){
    k = rand()/k;
  }
  
  State* tmp;
  Move ret; //= actions[k%actions.size()]; // in case all the value is the same(not yet minimax / alpha prune)

  int max;

  if(!state -> player){
    max = -100000;
    for(Move i : actions){
    
      tmp = state -> next_state(i);
      int val = tmp -> evaluate();

      if(val > max){
        max = val;
        ret = i;
      }
    }
  }
  else{
    max = 1000000;
    for(Move i : actions){
    
      tmp = state -> next_state(i);
      int val = tmp -> evaluate();

      if(val < max){
        max = val;
        ret = i;
      }
    }
  }
  

  return ret;
}