#include <cstdlib>

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
  Move ret = actions[k%actions.size()]; // in case all the value is the same(not yet minimax / alpha prune)

  int max = 0;

  for(Move i : actions){
    
      tmp = state -> next_state(i);
      tmp -> evaluate();
    
      if(tmp -> state_value > max){
        max = tmp -> state_value;
        ret = i;
      }
    
  }

  return ret;
}