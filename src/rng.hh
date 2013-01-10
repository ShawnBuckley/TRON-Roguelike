// TRON-Roguelike RNG.hh

#ifndef TRON_RLENGINEX_RNG_HH
#define TRON_RLENGINEX_RNG_HH

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include "object.hh"

class RNG : public Object
{
  public:
	RNG() : seed_(0), count_(0), zero_one_(0, 1), random_bool_(rng_, zero_one_) {};

	bool RandomBool()
	{
		++count_;

		return random_bool_();
	};

  	void Save(std::stringstream &_save)
  	{
  		_save << "rng" << " "
  			<< "a" << " " 
			<< id_ << " "
//			<< rng_ << " "
  			<< seed_ << " "
  			<< count_ << " "
  			<< std::endl;
  	}
  	
  	void Load() {};

  private:
  	int seed_;
  	uint32_t count_;

  	boost::random::mt19937 rng_;
  	boost::random::uniform_int_distribution<> zero_one_;
	boost::random::variate_generator<boost::random::mt19937&, boost::random::uniform_int_distribution<> > random_bool_;
};

#endif // TRON_RLENGINEX_RNG_HH
