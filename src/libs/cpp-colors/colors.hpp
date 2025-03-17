#pragma once
#ifndef CPP_COLORS_HPP
#define CPP_COLORS_HPP
#include <string>
#include <iostream>

/* ANSI escape code (See: http://en.wikipedia.org/wiki/ANSI_escape_code)
  1. Needs to start with Control Sequence Introducer (CSI) = \033[
  2. You can assign three comma-separated parameters like so: \033[1;2;3 (you don't need to use all of them)
  3. Ends with m character
*/

namespace cpp_colors
{

  /// @brief A collection of ANSI escape code to control foreground colors.
  namespace foreground {
    constexpr std::string_view black = "\033[30m";
    constexpr std::string_view red = "\033[31m";
    constexpr std::string_view green = "\033[32m";
    constexpr std::string_view yellow = "\033[33m";
    constexpr std::string_view blue = "\033[34m";
    constexpr std::string_view magenta = "\033[35m";
    constexpr std::string_view cyan = "\033[36m";
    constexpr std::string_view white = "\033[37m";

    constexpr std::string_view gray = "\033[90m";
    constexpr std::string_view bright_red = "\033[91m";
    constexpr std::string_view bright_green = "\033[92m";
    constexpr std::string_view bright_yellow = "\033[93m";
    constexpr std::string_view bright_blue = "\033[94m";
    constexpr std::string_view bright_magenta = "\033[95m";
    constexpr std::string_view bright_cyan = "\033[96m";
    constexpr std::string_view bright_white = "\033[97m";
  }

  /// @brief A collection of ANSI escape code to control background colors.
  namespace background {
    constexpr std::string_view black = "\033[40m";
    constexpr std::string_view red = "\033[41m";
    constexpr std::string_view green = "\033[42m";
    constexpr std::string_view yellow = "\033[43m";
    constexpr std::string_view blue = "\033[44m";
    constexpr std::string_view magenta = "\033[45m";
    constexpr std::string_view cyan = "\033[46m";
    constexpr std::string_view white = "\033[47m";

    constexpr std::string_view gray = "\033[100m";
    constexpr std::string_view bright_red = "\033[101m";
    constexpr std::string_view bright_green = "\033[102m";
    constexpr std::string_view bright_yellow = "\033[103m";
    constexpr std::string_view bright_blue = "\033[104m";
    constexpr std::string_view bright_magenta = "\033[105m";
    constexpr std::string_view bright_cyan = "\033[106m";
    constexpr std::string_view bright_white = "\033[107m";
  }

  /// @brief A collection of ANSI escape code to apply styles to output text.
  namespace style {
    constexpr std::string_view reset = "\033[0m";
    constexpr std::string_view bold = "\033[1m";
    constexpr std::string_view dim = "\033[2m";
    constexpr std::string_view normal = "\033[22m";
    constexpr std::string_view italic = "\033[3m";
    constexpr std::string_view strikethrough = "\033[9m";
    constexpr std::string_view underline = "\033[4m";

    /// @brief An alias for style::bold.
    constexpr std::string_view b = bold;

    /// @brief An alias for style::italic.
    constexpr std::string_view i = italic;

    /// @brief An alias for style::underline.
    constexpr std::string_view u = underline;

    /// @brief An alias for style::strikethrough.
    constexpr std::string_view st = strikethrough;
  }

  /// @brief Prints out a text with a style (color, bold...)
  /// @param text is the message to be displayed.
  /// @param color is an ANSI escape/color code. (Default is style::normal)
  /// @param eol is an end of line character. (Default is \\n)
  inline void colorful_print(
    const std::string& text,
    const std::string_view& color = style::normal,
    std::ostream& streamline = std::cout,
    const char eol = '\n'
  ) {
    streamline << color << text << style::reset << eol;
  }
}

#endif