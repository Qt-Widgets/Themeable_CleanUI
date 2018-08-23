/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#ifndef THEME_H
#define THEME_H

#include <QString>
#include <QVector>
#include "theme_configuration.h"

namespace xe {
namespace app {

enum ThemeRes { THEME_LOAD_OK = 0, THEME_NOT_FOUND, THEME_MISCONFIGURED };

/**
 * Represents a theme for xenia.
 *
 * On the FS a theme consists of a folder containing a
 * theme.json config file, and an optional sub-folder
 * called stylesheets containing QSS files.
 *
 * These QSS stylesheets support macros unlike default Qt
 * and have the format `$macro`.
 *
 * Macro values are defined in the config file.
 */
class Theme {
 public:
  Theme() = default;
  Theme(const QString &directory) : directory_(directory) {}
  Theme(const ThemeConfiguration &config) : config_(config) {}

  ThemeRes LoadTheme();

  const QString &directory() const { return directory_; }
  const ThemeConfiguration &config() const { return config_; }

 private:
  QString directory_;
  ThemeConfiguration config_;
};

}  // namespace app
}  // namespace xe

#endif  // THEME_H
