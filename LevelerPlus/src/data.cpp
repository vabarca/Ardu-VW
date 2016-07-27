
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/** @file  data.cpp
 *  @date  July, 2016
 *  @brief
 *
 *
 *  @author Original from (C) 2011 By P. Bauermeister
 *  @author Cooked by Vicente A. (TT)
 *  @bug No know bugs.
 */

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#include "data.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

CData::CData()
  :roll(0.0)
  ,pitch(0.0)
{}

//-----------------------------------------------------------------------------

CData& CData::operator=(const CData& other)
{
    if (this == &other) return *this;
    this->roll = other.roll;
    this->pitch = other.pitch;
    return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------