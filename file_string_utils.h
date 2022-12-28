// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include <string>

std::string just_path(const std::string& path_and_filename);

std::string just_filename(const std::string& path_and_filename);

std::string just_extension(const std::string& path_and_filename);

std::string without_extension(const std::string& path_and_filename);
