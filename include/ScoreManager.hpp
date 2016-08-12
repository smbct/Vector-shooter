/*!
* \file ScoreManager.hpp
* \brief Score manager definition
* \author smbct
* \date 08.12.2016
*/

#ifndef SCORE_MANAGER_HPP
#define SCORE_MANAGER_HPP

class ScoreManager {

    public:
        ScoreManager();
        void increment();
        unsigned int score();

    private:
        unsigned int _score;

};

#endif /* SCORE_MANAGER_HPP */
