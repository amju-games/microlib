// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include "file.h"

#define FILE_DEBUG

file::~file()
{
  close();
}

std::string to_string(std::ios::openmode m)
{
  switch (m)
  {
  case std::ios::in:
    return "reading";
  case std::ios::out:
    return "writing";
  default:
    return std::to_string(m);
  }
}

bool file::open(const std::string& filename, std::ios::openmode mode)
{
  if (m_file.is_open())
  {
    if (filename != m_filename)
    {
      return false;
    }
    std::cout << "Already open for " << to_string(mode) << ": \"" << filename << "\"\n";
    return true;
  }
  m_filename = filename;
  m_file.open(filename, mode);
  if (m_file.is_open())
  {
#ifdef FILE_DEBUG
    std::cout << "Opening for " << to_string(mode) << ": \"" << filename << "\"\n";
#endif
    //    m_file.seekg(0, m_file.end);
    //    m_size = m_file.tellg();
    //    m_file.seekg(0, m_file.beg);
  }
  else
  {
    std::cout << "FAILED to open for " << to_string(mode) << ": \"" << filename << "\"\n";
    return false;
  }

  return m_file.is_open();
}

bool text_file::open_for_reading(const std::string& filename)
{
  return file::open(filename, std::ios::in);
}

bool text_file::open_for_writing(const std::string& filename)
{
  return file::open(filename, std::ios::out);
}

void file::report_error(const std::string& err)
{
  if (m_filename.empty())
  {
    std::cout << "File: no filename: error: " << err;
  }
  else
  {
    std::cout << "File: " << m_filename << ": error: " << err;
  }
}

bool text_file::read_int(int& i)
{
  std::string s;
  if (!read_string(s))
  {
    return false;
  }
  i = atoi(s.c_str());
  return true;
}

bool text_file::read_string(std::string& s)
{
  if (!m_file.is_open())
  {
    report_error("File not open");
    return false;
  }

  if (m_file.eof())
  {
    // Not an error if we are looping like this:
    //  while (f.read_string... 
    return false;
  }

  m_line++;
  std::getline(m_file, s);

  return true;
}

bool text_file::write_string(const std::string& s)
{
  if (!m_file.is_open())
  {
    report_error("File not open, can't write " + s);
    return false;
  }

  m_file << s << std::endl; //.write(s);
  return true;  
}

bool text_file::write_int(int i)
{
  return write_string(std::to_string(i));
}
  
void text_file::report_error(const std::string& err)
{
  if (m_filename.empty())
  {
    std::cout << "File: no filename: error: " << err << "\n";
  }
  else
  {
    std::cout << "File: " << m_filename << " line: " << m_line << ": error: " << err << "\n";
  }
}

void file::close()
{
  m_file.close();
}

bool file_exists(const std::string& filename)
{
  struct stat buf;
  bool exists = (stat(filename.c_str(), &buf) != -1);
  return exists;
}

