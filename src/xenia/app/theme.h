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

#include <QMap>
#include <QString>
#include <QVector>
#include "theme_configuration.h"

namespace xe {
namespace app {

enum ThemeStatus { THEME_LOAD_OK = 0, THEME_NOT_FOUND, THEME_MISCONFIGURED };

// Stylemap is in the format: {target, stylesheet}
// where target is component and stylesheet is qss for component
using StyleMap = QMap<QString, QString>;

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

  ThemeStatus LoadTheme();
  QString StylesheetForComponent(const QString &compoment);

  const QString &directory() const { return directory_; }
  const ThemeConfiguration &config() const { return config_; }

 private:
  QString PreprocessStylesheet(QString style);

  QString directory_;
  ThemeConfiguration config_;
  StyleMap styles_;
};

}  // namespace app
}  // namespace xe

#endif  // THEME_H
