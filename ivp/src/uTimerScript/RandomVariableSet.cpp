/************************************************************/
/*    NAME: Michael Benjamin, H.Schmidt, J.Leonard          */
/*    ORGN: NAVSEA Newport RI and MIT Cambridge             */
/*    FILE: RandomVariableSet.cpp                           */
/*    DATE: Dec 18th 2009                                   */
/************************************************************/

#include <iostream>
#include <cstdlib>
#include "RandomVariableSet.h"
#include "MBUtils.h"

using namespace std;

//---------------------------------------------------------
// Procedure: contains

bool RandomVariableSet::contains(const string& varname)
{
  unsigned int i, vsize = m_rvar_vector.size();
  for(i=0; i<vsize; i++) {
    if(m_rvar_vector[i].getVarName() == varname)
      return(true);
  }
  return(false);
}

//---------------------------------------------------------
// Procedure: addRandomVar(RandomVariable)

void RandomVariableSet::addRandomVar(const RandomVariable& rvar)
{
  if(!contains(rvar.getVarName()))
    m_rvar_vector.push_back(rvar);
}

//---------------------------------------------------------
// Procedure: addRandomVar(string)

string RandomVariableSet::addRandomVar(const string& spec)
{
  string varname;
  string keyname;
  double minval=0;
  double maxval=1;
  bool   minval_set = false;
  bool   maxval_set = false;

  vector<string> svector = parseString(spec, ',');
  unsigned int i, vsize = svector.size();
  for(i=0; i<vsize; i++) {
    string left  = stripBlankEnds(biteString(svector[i], '='));
    string right = stripBlankEnds(svector[i]);
    if(left == "varname")
      varname = right;
    else if(left == "key")
      keyname = right;
    else if((left == "min") && isNumber(right)) {
      minval = atof(right.c_str());
      minval_set = true;
    }
    else if((left == "max") && isNumber(right)) {
      maxval = atof(right.c_str());
      maxval_set = true;
    }
    else 
      return("Bad parameter=value: " + left + "=" + right);
  }
  
  if(varname == "")
    return("Unset variable name");

  if(!minval_set)
    return("Lower value of the range not set");

  if(!maxval_set)
    return("Upper value of the range not set");
  
  if(minval > maxval)
    return("Minimum value greater than maximum value");

  unsigned int j, jsize = m_rvar_vector.size();
  for(j=0; j<jsize; j++) {
    if(m_rvar_vector[j].getVarName() == varname)
      return("Duplicate random variable");
  }
  
  RandomVariable rand_var;
  rand_var.setVarName(varname);
  if(keyname != "")
    rand_var.setKeyName(keyname);
  rand_var.setRange(minval, maxval);
  
  m_rvar_vector.push_back(rand_var);
  return("");
}

//---------------------------------------------------------
// Procedure: reset

void RandomVariableSet::reset(const string& key, double tstamp)
{
  unsigned int i, vsize = m_rvar_vector.size();
  for(i=0; i<vsize; i++) {
    if(m_rvar_vector[i].getKeyName() == key)
      m_rvar_vector[i].reset(tstamp);
  }
}

//---------------------------------------------------------
// Procedure: getVarName(index)

string RandomVariableSet::getVarName(unsigned int ix)
{
  if(ix < m_rvar_vector.size())
    return(m_rvar_vector[ix].getVarName());
  else
    return("");
}

//---------------------------------------------------------
// Procedure: getStringSummary(index)

string RandomVariableSet::getStringSummary(unsigned int ix)
{
  if(ix < m_rvar_vector.size())
    return(m_rvar_vector[ix].getStringSummary());
  else
    return("");
}

//---------------------------------------------------------
// Procedure: getStringValue(index)

string RandomVariableSet::getStringValue(unsigned int ix)
{
  if(ix < m_rvar_vector.size())
    return(m_rvar_vector[ix].getStringValue());
  else
    return("");
}

//---------------------------------------------------------
// Procedure: getValue(index)

double RandomVariableSet::getValue(unsigned int ix)
{
  if(ix < m_rvar_vector.size())
    return(m_rvar_vector[ix].getValue());
  else
    return(0);
}
