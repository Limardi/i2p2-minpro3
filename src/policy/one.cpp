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
  for(int i = 0; i < depth; i + 1){
    k = rand()/k;
  }

  return actions[k%actions.size()];
}