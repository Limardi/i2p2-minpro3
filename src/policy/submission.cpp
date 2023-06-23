#include <cstdlib>
#include<iostream>

#include "../state/state.hpp"
#include "./four.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int minimax2(State *state, int depth, bool mm, int alpha, int beta){

  if(!state->legal_actions.size())
    state->get_legal_actions();
    
  if(depth == 0 || !state->legal_actions.size()){
    return state->evaluate();
  }

  auto actions = state -> legal_actions;\
  
  State *tmp;
  int val;

  if(mm){
    for(auto i : actions){
        tmp = state -> next_state(i);
        val = minimax2(tmp, depth - 1, false, alpha, beta); 
        if(val > alpha){
          alpha = val;
        }
        if(alpha >= beta){
          break;
        }
    }
    return alpha;
  }
  else{
    for(auto i : actions){
        tmp = state -> next_state(i);
        val = minimax2(tmp, depth - 1, true, alpha, beta); 
        if(val < beta){
          beta = val;
        }
        if(alpha >= beta){
          break;
        }
    }

    return beta;
  }
  
}

Move four::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  State* tmp;
  Move ret; //= actions[k%actions.size()]; // in case all the value is the same(not yet minimax / alpha prune)


  int max;
  int alpha, beta;
  alpha = -1000000;
  beta = 1000000;

  if(!state -> player){
    max = -10000;
    for(Move i : actions){
      
      tmp = state -> next_state(i);
      int val = minimax2(tmp, depth - 1, false, alpha, beta);
      if(val > max){
        max = val;
        ret = i;
        alpha = val;
      }
      if(alpha > val){
        break;
      }
    
    }
  }
  else{
    max = 10000;
    for(Move i : actions){

      
      
      tmp = state -> next_state(i);
      int val = minimax2(tmp, depth - 1, true, alpha, beta);

      if(val < max){
        max = val;
        ret = i;
        beta = val;
      }

      if(beta < val){
          break;
      }
    
    }

  }
  

  return ret;
}