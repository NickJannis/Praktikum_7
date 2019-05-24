#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

/* copied from lecture */
template <typename T>
class StatContainer : public std::vector<T>
{
public:
  T getMean()
  {
    T valueSum= 0;
    //instead of: for (typename std::vector<T>::const_iterator it = this->begin()...
    for (auto it = this->begin(); it!= this->end(); ++it)
      {
         valueSum += *it;
      }
    return valueSum / this->size();
  }
  T getVariance()
  {
    T sum=0., sum2=0.;
    for (auto it = this->begin(); it!= this->end(); ++it)
      {
        sum  += (*it);
        sum2 += (*it)*(*it);
      }
    return  sum2/this->size() - (sum/this->size()*sum/this->size());
  }
  T getMedian()
  {
    std::vector <T> tmpVector(*this);
    std::sort(tmpVector.begin(), tmpVector.end());
    return tmpVector.at(tmpVector.size()/2);
  }
  T getStd()
  {
    return sqrt(getVariance());
  }  
  friend std::ostream& operator<< (std::ostream& stream, const StatContainer& statContainer)
  {
    for (auto it=statContainer.begin(); it!=statContainer.end(); ++it)
      {
         stream << "\t\t" << *it << std::endl;
      }
    return stream;
  }

  void getempQ(const double& p){
  	  std::vector<T> tmpVector(*this);
  	  std::sort(tmpVector.begin(), tmpVector.end());
  	  double a = tmpVector.size()*&p;
  	  double pQ;
  	  if(a != (double)((int)a))){
  		  pQ = tmpVector[(int)a+1];

  	  }else{
  		  pQ = 0.5*(tmpVector[a]+tmpVector[a+1]);
  	  }
  	  tmpVector[&p] = pQ;

    }

};


int main(){
	std::string dateiname;
	std::cout << "Dateiname" << std::endl;
	std::cin >> dateiname;

  std::ifstream infile(dateiname);
  std::string line, date;

  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
  boost::char_separator<char> sep(",");

  StatContainer<double> statContainer;

  infile >> line; // erste Zeile (Header) interessiert uns hier nicht
  while(infile >> date >> line){
    //std::cout << line << std::endl;
    tokenizer tokens(line, sep);
    auto tit = tokens.begin();
    std::advance(tit, 2); // now tit points at temperature field

    /*
    // Some test output to see what happens
    for(tokenizer::iterator it = tokens.begin(); it != tokens.end(); ++it){
      std::cout << "<" << *it << "> ";
    }
    std::cout << " -> " << *tit << std::endl;
    */

    statContainer.push_back(boost::lexical_cast<double>(*tit));
  }

  std::cout << statContainer << std::endl;
  std::cout << "    Mean: " << statContainer.getMean() << std::endl;
  std::cout << "     Std: " << statContainer.getStd() << std::endl;

  return 0;
}
