/*!
* \file ScoreManager.hc<pp
* \brief ScoreManager implementation
* \author smbct
* \date 08.12.2016
*/

#include "ScoreManager.hpp"

/*----------------------------------------------------------------------------*/
ScoreManager::ScoreManager() :
_score(0)
{

}

/*----------------------------------------------------------------------------*/
void ScoreManager::increment() {
    _score ++;
}

/*----------------------------------------------------------------------------*/
unsigned int ScoreManager::score() {
    return _score;
}
