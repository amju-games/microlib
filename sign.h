#pragma once

template<typename RET, typename ARG>
inline RET sign(ARG f)
{
  if (f < 0)
  {
    return static_cast<RET>(-1);
  }
  else if (f > 0)
  {
    return static_cast<RET>(1);
  }
  return RET(0);
}

